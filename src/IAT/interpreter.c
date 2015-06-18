#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>

#include "../dataStructure.h"
#include "references.h"
#include "interpret.h"
#include "onePass.h"
#include "../memutils.h"
#include "../execute.h"
#include "../ioutils.h"
#include "../stringutils.h"
#include "../secondPass.h"

int main(void)
{
    // print welcome message
    char* pathbuffer = (char*) calloc(MAX_LINE_LENGTH, sizeof(char));
    if (pathbuffer == NULL)
    {
        perror("calloc error in interpreter\n");
        exit(EXIT_FAILURE);
    }

    assert(readlink("/proc/self/exe", pathbuffer, MAX_LINE_LENGTH) != -1);
    removeExecutableName(pathbuffer);
    strcat(pathbuffer, "/msg/interpreter_welcome.txt");

    // print welcome message
    // assert(system("cat IAT/msg/interpreter_welcome.txt\n") != -1);
    printTextFile(pathbuffer);
    free(pathbuffer);

    // initialize references and cpu
    References* references = initReferences();
    CPUStatus* cpu = initCPU();
    int status = 0;

    // main loop
    while (1)
    {
        interpretPrompt(references, cpu, &status);
        if (status == EXECUTE_HALT)
        {
            break;
        }
    }

    // print status
    printRegisters(cpu);
    printMemory(cpu);

    // garbage collecting
    destroyReferences(references);
    destroyCPU(cpu);

    return EXIT_SUCCESS;
}
