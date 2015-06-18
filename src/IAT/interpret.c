#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#include "../stringutils.h"
#include "../dataStructure.h"
#include "../execute.h"
#include "../memutils.h"
#include "onePass.h"
#include "../secondPass.h"
#include "../ioutils.h"
#include "interpret.h"

// runs the execution pipeline up to and INCLUDING
// address limit
void executeUntil(CPUStatus* cpu, word_t limit, int* status)
{
    *status = EXECUTE_OK;
    int instructionTypeID = -1;

    while (1)
    {

        // execute
        if (cpu->pip->isDecoded)
        {
            // stop when limit reached
            if (cpu->pip->decoded > limit)
            {
                return;
            }

            word_t instruction = readWord(cpu, cpu->pip->decoded);

            /* send decoded instruction to execute */
            instructionTypeID = execute(cpu, instruction);

            if (instructionTypeID == 0)
            {
                *status = EXECUTE_HALT;
                break;
            }

            cpu->pip->isDecoded = 0;
        }

        // decode
        if (cpu->pip->isFetched)
        {
            cpu->pip->decoded = cpu->pip->fetched;

            cpu->pip->isDecoded = 1;

            cpu->pip->isFetched = 0;
        }

        // fetch
        // check for invalid address is done by memutils
        cpu->pip->fetched = cpu->regs->PC;

        cpu->regs->PC += 4;

        cpu->pip->isFetched = 1;

    }
}

// calculates the limit you can execute to
word_t calculateExecuteLimit(References* r)
{
    word_t limit = 0x0;
    int i = 0;

    for (i = 0; i < r->currentI; i++)
    {
        if (r->entries[i]->resolved)
        {
            if (!isLabel(r->entries[i]->instruction))
            {
                limit = r->entries[i]->address;
            } else if (r->currentAddress > 0)
            {
                limit = r->entries[i]->address - 4;
            }
        } else
        {
            return limit;
        }
    }
    return limit;
}

// runs the emulator
void interpret(References* r, CPUStatus* cpu, int* interpretStatus)
{

    word_t limit = calculateExecuteLimit(r);

    int executeStatus = EXECUTE_OK;
    executeUntil(cpu, limit, &executeStatus);

    *interpretStatus = executeStatus;

}

void printInstructions(References* r)
{
    if (r->currentI == 0)
    {
        printf("No program lines written yet\n");
    }

    int i = 0;
    for (i = 0; i < r->currentI; i++)
    {
        char* toPrint = r->entries[i]->instruction;
        printf("%s\n", toPrint);
    }
}

void interpretPrompt(References* r, CPUStatus* cpu, int* status)
{
    // show prompt ready
    printf("> ");
    fflush(stdout);

    // get new command
    char* line = (char*) calloc(MAX_STRING_LENGTH, sizeof(char));
    if (line == NULL)
    {
        perror("calloc error in interpretPrompt\n");
        exit(EXIT_FAILURE);
    }
    if (fgets(line, MAX_STRING_LENGTH, stdin) == NULL)
    {
        perror("fgets error in interpretPrompt\n");
        exit(EXIT_FAILURE);
    }

    // remove endline
    removeEndLine(line);

    int assembleCode = 0;

    // interpreter commands
    if (stringEquals(line, "regs") == 0)
    {
        printRegisters(cpu);
        *status = RUN_COMMAND;
        free(line);
        return;
    } else if (stringEquals(line, "mem") == 0)
    {
        printMemory(cpu);
        *status = RUN_COMMAND;
        free(line);
        return;
    } else if (stringEquals(line, "exit") == 0)
    {
        *status = EXECUTE_HALT;
        free(line);
        return;
    } else if (stringEquals(line, "show") == 0)
    {
        printInstructions(r);
        *status = RUN_COMMAND;
        free(line);
        return;
    } else
    {
        // assemble One Pass
        assembleCode = onePass(r, cpu, line);
    }

    // execute interpreter
    if (assembleCode == ASSEMBLE_OK ||
        (assembleCode == ASSEMBLE_LABEL && r->currentAddress > 4))
    {
        interpret(r, cpu, status);
    }

    free(line);
}
