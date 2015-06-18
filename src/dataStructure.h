#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include <stdint.h>

// CONSTANTS
enum
{
    MEMORY_SIZE = 65536, NO_OF_REGISTERS = 13
};

// definitions of word, byte, and address
typedef uint32_t word_t;
typedef uint8_t byte_t;
typedef uint16_t address_t;

// Structure for registers
typedef struct Reg
{
    word_t r_general[NO_OF_REGISTERS]; /* r0-r12 */
    word_t r13; /* ignored */
    word_t r14; /* ignored */
    word_t PC;
    word_t RFLAGS;
} Regs;

// Structure for pipeline
typedef struct pipeline
{
    word_t decoded;
    word_t fetched;
    int isDecoded;
    int isFetched;
} Pipeline;

// structure for the CPU Status
typedef struct cpuStatus
{
    Regs *regs;
    byte_t *memory;
    Pipeline *pip;
} CPUStatus;



#endif
