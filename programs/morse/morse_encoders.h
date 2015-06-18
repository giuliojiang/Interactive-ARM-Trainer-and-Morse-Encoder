#ifndef MORSE_ENCODERS_H
#define MORSE_ENCODERS_H

#define IO_OK 0
#define IO_ERROR -1

char *encodeLetter(char c);


void encodeDot(FILE *fp, int loopNumber);


void encodeDash(FILE *fp, int loopNumber);


void encodeSpace(FILE *fp, int loopNumber);


void encode7Spaces(FILE *fp, int loopNumber);


void encode3Spaces(FILE *fp, int loopNumber);


int dumpString(char *s, FILE *stream);


void armInitializationCode(FILE *fp);


void armFinalizationCode(FILE *fp);




#endif
