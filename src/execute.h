#ifndef EXECUTE_H
#define EXECUTE_H



int checkFlags(CPUStatus *cpu, word_t instruction);

int execute(CPUStatus *cpu, word_t instruction);

#endif
