#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include "dataStructure.h"

#define MAX_LINE_LENGTH 512

static const int MAX_NO_ARGUMENTS = 16;
static const int MAX_CONSTS = 16;

// static const int MAX_LINE_LENGTH = 512;

typedef struct labeltuple
{
    int lineNumber;
    char label[MAX_LINE_LENGTH];
    char* labelPtr;
} LabelTuple;

int stringEquals(char *s1, char *s2);

int isLabel(char *s);

void getLabel(char *line, char *destination, int sourceLineNumber);

// Splits a string into tokens, stored in the
// String Array out, and the number of the elements
// split is in n
// the out array should be created using
// char **createStringArray(void)
// and destroyed with destroyStringArray(out)
void splitString(char *input, char **output, int *n);

// the out array should be created using
// char **createStringArray(void)
// and destroyed with destroyStringArray(out)
void splitStringBracketed(char *input, char **out, int *n);

int isReg(char *s);

int getRegID(char *s);

int nextLine(char *s, FILE *stream);

int isHex(char *token);

word_t getHex(char *token);

int isDec(char *s);

int isAddr(char *s);

int getAddr(char *s);

word_t getDec(char *s);

//int isAddr(char *s);

//word_t getAddr(char *s);

int isBaseRegister(char *token);

int isBaseRegisterAndOffset(char *token);

int isEmptyLine(char *s);

char **createStringArray(void);

void destroyStringArray(char **in);

char **createStringArrayLong(void);

void destroyStringArrayLong(char **in);

int isStringElem(char *s, char **table, int n);

void removeEndLine(char* s);

void removeExecutableName(char* s);

#endif

