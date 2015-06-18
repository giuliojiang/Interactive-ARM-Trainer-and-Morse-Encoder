#ifndef SINGLEDATA_H
#define SINGLEDATA_H

void executeSDT(CPUStatus *cpu, word_t instruction);

void transfer(CPUStatus *cpu, int lFlag, word_t address, word_t srcDstR);

word_t applyOffset(CPUStatus *cpu, int uFlag, int pFlag, word_t offset,
        word_t baseRegister);

word_t shift(CPUStatus *cpu, byte_t shiftType, word_t rm, 
              word_t rs, word_t constant, int bit4);

#endif
