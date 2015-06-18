#ifndef MULTIPLY_H
#define MULTIPLY_H

static const int accumulateBit = 21;
static const int bitSetFlags = 20;

enum regsconsts
{
    RM_MAX = 3,
    RM_MIN = 0,
    RS_MAX = 11,
    RS_MIN = 8,
    RN_MAX = 15,
    RN_MIN = 12,
    RD_MAX = 19,
    RD_MIN = 16
};

void updateFlags(CPUStatus *cpu, int bitSet, word_t result);

void performMultiply(CPUStatus *cpu, word_t instruction);

#endif
