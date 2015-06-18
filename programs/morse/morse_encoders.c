#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "morse_base.h"
#include "morse_encoders.h"


// takes a char and returns the correspondin
// sequence of -.-...
// . 1 unit ON     dot
// - 3 units ON    dash
//   1 unit OFF    space
// _ 3 units OFF   underscore
// \t 7 units OFF  tab
// the returned string is HEAP allocated
char *encodeLetter(char c)
{

    // malloc
    char *out = (char*) calloc(MAX_CODE_LENGTH, sizeof(char));
    if (out == NULL)
    {
        perror("ERROR calloc in encodeLetter\n");
        exit(EXIT_FAILURE);
    }

    // mega if-else
    if (c == ' ' || c == '\n' || c == '\t')
    {
        strncpy(out, "\t", MAX_CODE_LENGTH);
    } else if (c == '1')
    {
        strncpy(out, ". - - - -_", MAX_CODE_LENGTH);
    } else if (c == '2')
    {
        strncpy(out, ". . - - -_", MAX_CODE_LENGTH);
    } else if (c == '3')
    {
        strncpy(out, ". . . - -_", MAX_CODE_LENGTH);
    } else if (c == '4')
    {
        strncpy(out, ". . . . -_", MAX_CODE_LENGTH);
    } else if (c == '5')
    {
        strncpy(out, ". . . . ._", MAX_CODE_LENGTH);
    } else if (c == '6')
    {
        strncpy(out, "- . . . ._", MAX_CODE_LENGTH);
    } else if (c == '7')
    {
        strncpy(out, "- - . . ._", MAX_CODE_LENGTH);
    } else if (c == '8')
    {
        strncpy(out, "- - - . ._", MAX_CODE_LENGTH);
    } else if (c == '9')
    {
        strncpy(out, "- - - - ._", MAX_CODE_LENGTH);
    } else if (c == '0')
    {
        strncpy(out, "- - - - -_", MAX_CODE_LENGTH);
    } else if (c == 's')
    {
        strncpy(out, ". . ._", MAX_CODE_LENGTH);
    }
    else if (c == 't')
    {
        strncpy(out, "-_", MAX_CODE_LENGTH);
    }
    else if (c == 'u')
    {
        strncpy(out, ". . -_", MAX_CODE_LENGTH);
    }
    else if (c == 'v')
    {
        strncpy(out, ". . . -_", MAX_CODE_LENGTH);
    }
    else if (c == 'w')
    {
        strncpy(out, ". - -_", MAX_CODE_LENGTH);
    }
    else if (c == 'x')
    {
        strncpy(out, "- . . -_", MAX_CODE_LENGTH);
    }
    else if (c == 'y')
    {
        strncpy(out, "- . - -_", MAX_CODE_LENGTH);
    }
    else if (c == 'z')
    {
        strncpy(out, "- - . ._", MAX_CODE_LENGTH);
    } 
    else if (c == 'a' || c == 'A') 
    {
      strncpy(out, ". -_", MAX_CODE_LENGTH);
    }
    else if (c == 'b' || c == 'B') 
    {
      strncpy(out, "- . . ._", MAX_CODE_LENGTH);
    }
    else if (c == 'c' || c == 'C') 
    {
      strncpy(out, "- . - ._", MAX_CODE_LENGTH);
    } 
    else if (c == 'd' || c == 'D') 
    {
      strncpy(out, "- . ._", MAX_CODE_LENGTH);
    } 
    else if (c == 'e' || c == 'E') 
    {
      strncpy(out, "._", MAX_CODE_LENGTH);
    } 
    else if (c == 'f' || c == 'F') 
    {
      strncpy(out, ". . - ._", MAX_CODE_LENGTH);
    } 
    else if (c == 'g' || c == 'G') 
    {
      strncpy(out, "- - ._", MAX_CODE_LENGTH);
    } 
    else if (c == 'h' || c == 'H') 
    {
      strncpy(out, ". . . ._", MAX_CODE_LENGTH);
    } 
    else if (c == 'i' || c == 'I') 
    {
      strncpy(out, ". ._", MAX_CODE_LENGTH);
    } 
    else if (c == 'j' || c == 'J') 
    {
      strncpy(out, ". - - -_", MAX_CODE_LENGTH);
    } 
    else if (c == 'k' || c == 'K') 
    {
      strncpy(out, "- . -_", MAX_CODE_LENGTH);
    } 
    else if (c == 'l' || c == 'L') 
    {
      strncpy(out, ". - . ._", MAX_CODE_LENGTH);
    } 
    else if (c == 'm' || c == 'M') 
    {
      strncpy(out, "- -_", MAX_CODE_LENGTH);
    } 
    else if (c == 'n' || c == 'N') 
    {
      strncpy(out, "- ._", MAX_CODE_LENGTH);
    } 
    else if (c == 'o' || c == 'O') 
    {
      strncpy(out, "- - -_", MAX_CODE_LENGTH);
    } 
    else if (c == 'p' || c == 'P') 
    {
      strncpy(out, ". - - ._", MAX_CODE_LENGTH);
    } 
    else if (c == 'q' || c == 'Q') 
    {
      strncpy(out, "- - . -_", MAX_CODE_LENGTH);
    } 
    else if (c == 'r' || c == 'R')
    {
      strncpy(out, ". - ._", MAX_CODE_LENGTH);
    } 
    else  
    {       
        fprintf(stderr, "encodeLetter: unsupported letter %c\n", c);
        strncpy(out, "", MAX_CODE_LENGTH);
    }

    return out;
}

// writes to output the ARM code for the DOT
void encodeDot(FILE *fp, int loopNumber)
{
  fprintf(fp, "; ON 1 unit\nstr r1, [r0, #40]\nldr r2, =%s\nwait%i:\nsub r2, r2, #0x1\ncmp r2, #0\nbge wait%i\n", MORSE_1UNITS, loopNumber, loopNumber);
  if (ferror(fp))
  {
    perror("fprint error in encodeDot");
    exit(EXIT_FAILURE);
  }
}

// writes to output the ARM code for the DASH
void encodeDash(FILE *fp, int loopNumber)
{
  fprintf(fp, "; ON 3 units\nstr r1, [r0, #40]\nldr r2, =%s\nwait%i:\nsub r2, r2, #0x1\ncmp r2, #0\nbge wait%i\n", MORSE_3UNITS, loopNumber, loopNumber);
  if (ferror(fp))
  {
    perror("fprint error in encodeDot");
    exit(EXIT_FAILURE);
  }  
}

// writes to output the ARM code for the SPACE
void encodeSpace(FILE *fp, int loopNumber)
{
    fprintf(fp, "; OFF 1 units\nstr r1, [r0, #28]\nldr r2, =%s\nwait%i:\nsub r2, r2, #0x1\ncmp r2, #0\nbge wait%i\n", MORSE_1UNITS, loopNumber, loopNumber);
    if (ferror(fp))
    {
        perror("fprintf error in encode1Space\n");
        exit(EXIT_FAILURE);
    }
}

// writes to output the ARM code for the WORDBREAK
void encode7Spaces(FILE *fp, int loopNumber)
{
    fprintf(fp, "; OFF 7 units\nstr r1, [r0, #28]\nldr r2, =%s\nwait%i:\nsub r2, r2, #0x1\ncmp r2, #0\nbge wait%i\n", MORSE_7UNITS, loopNumber, loopNumber);
    if (ferror(fp))
    {
        perror("fprintf error in encode7Spaces\n");
        exit(EXIT_FAILURE);
    }   
}

// writes to output the ARM code for the UNDERSCORE
void encode3Spaces(FILE *fp, int loopNumber)
{
    fprintf(fp, "; OFF 3 units\nstr r1, [r0, #28]\nldr r2, =%s\nwait%i:\nsub r2, r2, #0x1\ncmp r2, #0\nbge wait%i\n", MORSE_3UNITS, loopNumber, loopNumber);
    if (ferror(fp))
    {
        perror("fprintf error in encode3Spaces\n");
        exit(EXIT_FAILURE);
    }
}

// writes to output a given string
int dumpString(char *s, FILE *stream)
{
    if (fputs(s, stream) == EOF)
    {
        perror("Error in dumpString\n");
        return IO_ERROR;
    }
    return IO_OK;
}

// writes to output the ARM code for INITIALIZATION
void armInitializationCode(FILE *fp)
{
    fprintf(fp, "; initialization\nldr r0, =0x20200000\nmov r1, #1\nlsl r1, #18\nstr r1, [r0, #4]\nmov r1, #1\nlsl r1, #16\nbeginning:\n");
    if (ferror(fp))
    {
        perror("fprintf error in armInitializationCode\n");
        exit(EXIT_FAILURE);
    }
}

// writes to output the ARM code for FINALIZATION
void armFinalizationCode(FILE *fp)
{
    fprintf(fp, "; finalization\nb beginning\nandeq r0, r0, r0\n");
    if (ferror(fp))
    {
        perror("fprintf error in armFinalizationCode\n");
        exit(EXIT_FAILURE);
    }
}

// ====================================
// TESTS
// ====================================

