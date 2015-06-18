#ifndef FIRST_PASS_H
#define FIRST_PASS_H

OrderedList *firstPass(char *fileName, CPUStatus *cpu, OrderedList *consts,
    word_t *finalAddress);

void firstPass_test(CPUStatus *cpu);

#endif
