#ifndef ASSEMBLEMULTIPLY_H
#define ASSEMBLEMULTIPLY_H

static const word_t cond = 0xE << 28;
static const word_t mid = 0x9 << 4;

word_t assembleMultiply(char* string, int* status);

#endif
