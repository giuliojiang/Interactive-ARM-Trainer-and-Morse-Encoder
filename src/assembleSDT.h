#ifndef ASSEMBLESDT_H
#define ASSEMBLESDT_H

word_t assemble_SDT(char *cmd, OrderedList *consts, word_t address,
                    int* status);

void shiftBits(word_t *instruction, char *shiftName, char *rsOrExpr);

void assembleSDT_test(void);

/* Constants */
static const int baseRPos = 19;
static const int srcDstPos = 15;
static const int rmPos = 3;
static const int commFieldLength = 4;
static const int offsetPos = 11;
static const int shiftTPos = 6;
static const int shiftTLength = 2;
static const int lsl = 0;
static const int lsr = 1;
static const int asr = 2;
static const int ror = 3;
static const int offsetLength = 12;
static const word_t MOV_THRESHOLD = 0xFF;
static const int pc = 15;

#endif


