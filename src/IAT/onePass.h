#ifndef IAT_ONEPASS_H
#define IAT_ONEPASS_H

#include "references.h"
#include "../dataStructure.h"
#include "../orderedList.h"

References* initReferences(void);

void destroyReferences(References* r);

RefEntry* initRefEntry(void);

void destroyRefEntry(RefEntry* r);

void addReferenceEntry(References* self, char* instruction, int resolved,
    int isLdrLong);

void solveReferences(References* r, CPUStatus* cpu);

void solveReference(References* r, RefEntry* entry, CPUStatus* cpu);

int onePass(References* references, CPUStatus* cpu, char* line);




#endif
