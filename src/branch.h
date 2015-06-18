#ifndef BRANCH_H
#define BRANCH_H

void branchSignExtend26_32(word_t *x);

word_t branchGetOffset(word_t instruction);

void executeBranch(CPUStatus *cpu, word_t instruction);

#endif
