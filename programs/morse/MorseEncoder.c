#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "morse_base.h"
#include "morse_encoders.h"

int main(int argc, char **argv)
{
    // check for arguments
    if (argc != 3)
    {
        printf("Usage: ./MorseEncoder <input> <output.s>\n");
        exit(EXIT_SUCCESS);
    }

    // open input file
    FILE *in = fopen(argv[1], "r");
    if (in == NULL)
    {
        fprintf(stderr, "Error opening file %s\n", argv[1]);
    }

    // open output file
    FILE *out = fopen(argv[2], "w");
    if (out == NULL)
    {
        fprintf(stderr, "Error opening file %s\n", argv[2]);
    }

    // create buffer string
    char *buffer = (char*) calloc(MAX_LINE_LENGTH, sizeof(char));
    if (buffer == NULL)
    {
        perror("ERROR calloc for buffer\n");
        goto endmain;
    }

    // write the ARM initialization code
    armInitializationCode(out);

    // wait number counter
    int loopNumber = 1;

    // while not EOF:
    while (!feof(in))
    {
        // read line from input file to buffer
        if (fgets(buffer, MAX_LINE_LENGTH, in) == NULL)
        {
            goto endmain;
        }

        // loop through the read string
        for (int i = 0; buffer[i] != '\0'; i++)
        {
            char *morseCode = encodeLetter(buffer[i]);

            // loop through the morse code and write to file
            for (int j = 0; morseCode[j] != '\0'; j++)
            {

                // read morse code and encode them to ARM
                if (morseCode[j] == ' ')
                {
                    encodeSpace(out, loopNumber++);
                } else if (morseCode[j] == '\t')
                {
                    encode7Spaces(out, loopNumber++);
                } else if (morseCode[j] == '.')
                {
                    encodeDot(out, loopNumber++);
                } else if (morseCode[j] == '-')
                {
                    encodeDash(out, loopNumber++);
                } else if (morseCode[j] == '_')
                {
                    encode3Spaces(out, loopNumber++);
                } else {
                    fprintf(stderr, "Invalid morse token %c\n", morseCode[j]);
                }
            }

            free(morseCode);
        }
    }

    endmain:

    // write ARM finalizing code
    armFinalizationCode(out);


    // garbage collecting
    free(buffer);

    // close the 2 files
    fclose(in);
    fclose(out);

    return 0;
}
