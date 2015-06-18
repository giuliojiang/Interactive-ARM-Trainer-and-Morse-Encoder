#ifndef IOUTILS_H
#define IOUTILS_H

#define MEMORY_OK 1
#define MEMORY_ERROR 0

void loadToMemory(char *filePath, CPUStatus *cpu);

void printRegisters(CPUStatus *cpu);

void printMemory(CPUStatus *cpu);

int dumpMemory(char *fileName, CPUStatus *cpu, int debugMode, word_t address);

void handleIOError(int errorCode, char *errorMessage, FILE *fp);

void printTextFile(char *fileName);

#endif
