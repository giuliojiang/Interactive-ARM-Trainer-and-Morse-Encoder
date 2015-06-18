#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#include "../dataStructure.h"
#include "../stringutils.h"
#include "references.h"
#include "../orderedList.h"
#include "../secondPass.h"
#include "../memutils.h"
#include "../assembleDataprocessing.h"
#include "../assembleBranch.h"
#include "../assembleMultiply.h"
#include "../assembleSDT.h"
#include "onePass.h"

// creates a heap allocated reference data structure
References* initReferences(void)
{
    // allocate memory for References
    References* out = (References*) malloc(sizeof(References));
    if (out == NULL)
    {
        perror("malloc error in initReferences\n");
        exit(EXIT_FAILURE);
    }

    // initialize labels
    OrderedList* labels = orderedList_init();

    // initialize consts
    OrderedList* consts = orderedList_init();

    // initialize entries array
    RefEntry** entries = (RefEntry**) calloc(MEMORY_SIZE, sizeof(RefEntry*));

    out->labels = labels;
    out->consts = consts;
    out->entries = entries;
    out->currentI = 0;
    out->currentAddress = 0x0;
    out->dataAddress = 0x1000; // TO TEST

    return out;
}

// frees a References
void destroyReferences(References* r)
{
    orderedList_destroy(r->labels);
    orderedList_destroy(r->consts);

    for (int i = 0; i < r->currentI; i++)
    {
        destroyRefEntry(r->entries[i]);
    }
    free(r->entries);

    free(r);
}

// initializes RefEntry
RefEntry* initRefEntry(void)
{
    RefEntry* out = (RefEntry*) calloc(1, sizeof(RefEntry));
    if (out == NULL)
    {
        perror("calloc error in initRefEntry\n");
        exit(EXIT_SUCCESS);
    }

    return out;
}

// frees a RefEntry
void destroyRefEntry(RefEntry* r)
{
    if (r != NULL)
    {
        free(r->instruction);
        free(r);
    }
}

// adds an entry to References
void addReferenceEntry(References* self, char* instruction, int resolved,
    int isLdrLong)
{
    RefEntry* out = initRefEntry();

    out->address = self->currentAddress;
    out->instruction = strdup(instruction);
    out->resolved = resolved;

    self->entries[self->currentI] = out;

    if (!isLabel(instruction))
    {
        if (isLdrLong)
        {
            self->currentAddress = self->currentAddress + 12;
        } else
        {
            self->currentAddress = self->currentAddress + 4;
        }
    }
    self->currentI = self->currentI + 1;
}

// checks for unsolved references and tries to solve them
void solveReferences(References* r, CPUStatus* cpu)
{
    for (int i = 0; i < r->currentI; i++)
    {
        RefEntry* entry = r->entries[i];
        if (!(entry->resolved))
        {
            solveReference(r, entry, cpu);
        }
    }
}

// tries to assemble an instruction with missing reference
void solveReference(References* r, RefEntry* entry, CPUStatus* cpu)
{
    char* line = entry->instruction;
    int status = ASSEMBLE_OK;
    word_t assembled = assembleBranch(line, r->labels, entry->address, 0, &status);

    if (status == ASSEMBLE_OK)
    {
        printf("Dependency resolved for %s.\n", line);
        writeWord(cpu, assembled, entry->address);
        entry->resolved = 1;
    }
}

int onePass(References* references, CPUStatus* cpu, char* line)
{
    // create string array for splitting
    char** splitted = createStringArray();
    int splittedN = 0;
    int isLdrLong = 0;

    // return code by assemblers
    int returnCode = ASSEMBLE_OK;

    // split string into tokens
    splitString(line, splitted, &splittedN);

    // check for empty line
    if (splittedN == 0)
    {
        return ASSEMBLE_LABEL;
    }

    // ==============================================
    // FIRST PASS equivalent

    // handle label
    if (isLabel(line))
    {

        // get the label name
        char* label = (char*) calloc(MAX_STRING_LENGTH, sizeof(char));
        if (label == NULL)
        {
            perror("calloc\n");
            exit(EXIT_FAILURE);
        }
        getLabel(line, label, 0);


        // add label to map
        orderedList_add(references->labels, label, references->currentAddress);

        free(label);
        returnCode = ASSEMBLE_LABEL;
    }

    // ==============================================
    // SECOND PASS equivalent

    word_t assembledInstruction = 0x0;

    // table for all supported mnemonics
    OrderedList *mnemonicTable = createMnemonicTable();



    if (!(isEmptyLine(line) || isLabel(line)))
    {

        // assemble

        // get instruction type code, and assemble status
        int opID = getOpID(splitted[0], mnemonicTable);

        // forward to correct assembler
        if (opID == 0)
        { // all-zero instruction
            assembledInstruction = 0x0;
        } else if (opID == 1)
        { // data processing
            assembledInstruction =
                assemble_dataprocessing(line, &returnCode);
        } else if (opID == 2)
        { // multiply
            assembledInstruction =
                assembleMultiply(line, &returnCode);
        } else if (opID == 3)
        { // single data

            if (splittedN == 3 && splitted[2][0] == '='
                && getHex(splitted[2]) > 0xFF)
            {
                isLdrLong = 1;

                // write jmp
                writeWord(cpu, 0xEA000000, references->currentAddress + 4);

                // write const and add to list
                writeWord(cpu, getHex(splitted[2]),
                          references->currentAddress + 8);
                orderedList_add(references->consts,
                                splitted[2], references->currentAddress + 8);

                assembledInstruction = assemble_SDT(line,
                    references->consts, references->currentAddress, &returnCode);

            } else
            {
                assembledInstruction = assemble_SDT(line,
                    references->consts, references->currentAddress, &returnCode);

            }
        } else if (opID == 4)
        { // branch
            assembledInstruction = assembleBranch(line,
                references->labels, references->currentAddress, 0, &returnCode);

            if (returnCode == ASSEMBLE_NO_REF)
            {
                printf("Label dependencies pending, deferring execution...\n");
            }
        } else if (opID == 5)
        { // lsl
            assembledInstruction =
                assemble_dataprocessing(line, &returnCode);
        } else
        {
            fprintf(stderr, "Invalid instruction %s\n",
                    splitted[0]);
            returnCode = ASSEMBLE_ERROR;
            goto endOnePass;
        }

    }


    // check assemble errors
    if (returnCode == ASSEMBLE_ERROR)
    {
        perror("Invalid instruction!\n");
        goto endOnePass;
    }

    // store references entry (if not empty line)
    // if (!(isEmptyLine(line) || isLabel(line)))
    if (!isEmptyLine(line))
    {
        if (returnCode == ASSEMBLE_OK)
        {
            writeWord(cpu, assembledInstruction, references->currentAddress);
            addReferenceEntry(references, line, 1, isLdrLong);
        } else if (returnCode == ASSEMBLE_NO_REF)
        {
            addReferenceEntry(references, line, 0, isLdrLong);
        } else if (returnCode == ASSEMBLE_LABEL)
        {
            addReferenceEntry(references, line, 1, isLdrLong);
        } else
        {
            printf("invalid instruction\n");
        }
    }

    // try to solve unsolved references (if is label) TODO
    solveReferences(references, cpu);

    // free memory of string array
    endOnePass:
    orderedList_destroy(mnemonicTable);
    destroyStringArray(splitted);

    return returnCode;
}
