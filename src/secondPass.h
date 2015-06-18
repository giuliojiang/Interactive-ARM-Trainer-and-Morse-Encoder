#ifndef SECOND_PASS_H
#define SECOND_PASS_H


#define ASSEMBLE_OK     0
#define ASSEMBLE_HALT   1
#define ASSEMBLE_ERROR -1
#define ASSEMBLE_NO_REF 2
#define ASSEMBLE_LABEL  4
#define RUN_COMMAND     3
#define COMMAND_EXIT    1
#define EXECUTE_OK      0
#define EXECUTE_HALT    1
#define EXECUTE_ERROR  -1

#include "orderedList.h"

void secondPass(char *fileName, CPUStatus *cpu, OrderedList *map,
        OrderedList *consts);

int getOpID(char *code, OrderedList *table);

OrderedList *createMnemonicTable(void);

void secondPass_getOpIDTest(void);

#endif
