#ifndef DATAPROCESSING_H
#define DATAPROCESSING_H

void execute_dataprocessing(CPUStatus *cpu, word_t instruction);

int getOperand2(CPUStatus *cpu, word_t instruction, word_t *operand2);

int notBorrow(word_t num1, word_t num2);

#endif 
