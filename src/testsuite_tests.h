#ifndef TESTSUITE_TESTS_H
#define TESTSUITE_TESTS_H

CPUStatus *createTestCPU(void);

void memutils_ByteTest(CPUStatus *cpu);

void memutils_EndianConverterTest(void);

void memutils_WordTest(CPUStatus *cpu);

void memutils_getBitTest(void);

void memutils_getBitsTest(void);

void memutils_checkSet(void);

void memutils_writeBitsTest(void);

void execute_checkFlags(CPUStatus *cpu);

void execute_executeTest(CPUStatus *cpu);

void branch_executeTest(CPUStatus *cpu);

void memutils_getOpcodeTest(void);

void ioutils_loadToMemoryTest(CPUStatus *cpu);

void memutils_writeRegs(CPUStatus *cpu);

void multiply_updateFlags(CPUStatus *cpu);

uint32_t multiply_multiplyHelper(uint32_t a, uint32_t b);

uint32_t multiply_multiplyAccumulateHelper(uint32_t a, uint32_t b, uint32_t c);

void multiply_performMultiply(void);

void SDT_executeTest(CPUStatus *cpu);

void dataprocessing_getOperand2Test(CPUStatus *cpu);

#endif
