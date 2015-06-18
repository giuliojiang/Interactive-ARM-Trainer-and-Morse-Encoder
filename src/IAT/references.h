#ifndef IAT_REFERENCES_H
#define IAT_REFERENCES_H

#include "../dataStructure.h"
#include "../orderedList.h"

// structures for OnePass references

typedef struct ref_entry_t
{
    char* instruction;                   // holds instruction string
    int resolved;                        // 1 iff no dependencies pending
    word_t address;                      // holds address of instruction
} RefEntry;

typedef struct references_t
{
    OrderedList* labels;
    OrderedList* consts;
    RefEntry** entries;

    int currentI;
    word_t currentAddress;
    word_t dataAddress;         // constants location
} References;

#endif
