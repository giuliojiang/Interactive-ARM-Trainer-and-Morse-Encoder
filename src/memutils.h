#ifndef MEMUTILS_H
#define MEMUTILS_H

void endl(void);

int isPortAddress(word_t address);

int checkAddress(word_t address, CPUStatus *cpu);

void writeByte(CPUStatus *cpu, byte_t data, word_t address);

byte_t readByte(CPUStatus *cpu, word_t address);

word_t endianConverter(word_t in);

void writeWord(CPUStatus *cpu, word_t data, word_t address);

word_t readWord(CPUStatus *cpu, word_t address);

void writeReg(CPUStatus *cpu, word_t data, int regID);

word_t readReg(CPUStatus *cpu, int regID);

int getBit(word_t word, int position);

void writeBit(word_t *word, int position, int data);

int checkSet(word_t word, word_t bitsToCheck);

byte_t getInstructionCond(word_t instruction);

word_t getBits(word_t word, int startBit, int endBit);

int getNFlag(CPUStatus *cpu);

void setNFlag(CPUStatus *cpu);

void clearNFlag(CPUStatus *cpu);

int getZFlag(CPUStatus *cpu);

void setZFlag(CPUStatus *cpu);

void clearZFlag(CPUStatus *cpu);

int getCFlag(CPUStatus *cpu);

void setCFlag(CPUStatus *cpu);

void clearCFlag(CPUStatus *cpu);

int getVFlag(CPUStatus *cpu);

void setVFlag(CPUStatus *cpu);

void clearVFlag(CPUStatus *cpu);

byte_t getOpcode(word_t instruction);

//word_t getBits(word_t instruction, int initialBitPosition, int finalBitPosition);

word_t rotateRight(word_t word);

word_t rotateRightN(word_t word, int n);

word_t rotateLeft(word_t word);

word_t rotateLeftN(word_t word, int n);

word_t rotateOperand(word_t instruction);

word_t getOffset(word_t from, word_t to);

CPUStatus *initCPU(void);

void destroyCPU(CPUStatus *cpu);

void writeBits(word_t *instruction, word_t word, int startBit, int n);

#endif 
