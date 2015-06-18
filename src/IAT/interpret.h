#ifndef IAT_INTERPRET_H
#define IAT_INTERPRET_H

#include "../dataStructure.h"
#include "references.h"

void executeUntil(CPUStatus* cpu, word_t limit, int* status);

word_t calculateExecuteLimit(References* r);

void interpret(References* r, CPUStatus* cpu, int* interpretStatus);

void printInstructions(References* r);

void interpretPrompt(References* r, CPUStatus* cpu, int* status);

#endif // IAT_INTERPRET_H
