#ifndef ASSEMBLE_BRANCH_H
#define ASSEMBLE_BRANCH_H

word_t assembleBranch(char *line, OrderedList *table, word_t address,
                      int lineNumber, int* status);

void assembleBranch_cond(char *mnemonic, word_t *instruction);

void assembleBranch_offset(char *label, OrderedList *table,
                           word_t *instruction, word_t address, int fileLine,
                           int* status);

word_t assembleBranch_calculateOffset(word_t start, address_t target);

void assembleBranch_test(void);


#endif

