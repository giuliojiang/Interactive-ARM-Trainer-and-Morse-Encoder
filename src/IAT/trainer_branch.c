#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#include "references.h"
#include "onePass.h"
#include "../memutils.h"
#include "../secondPass.h"
#include "interpret.h"
#include "../stringutils.h"
#include "../ioutils.h"
#include "trainer_dp.h"

static int askContinue(void);
void trainer_branch_1_launcher(void);
void trainer_branch_1(int retry);
void trainer_branch_2(void);
void trainer_branch_3(void);
static void trainer_sdt_1_launcher(void);
static void trainer_sdt_2_launcher(void);
static void trainer_sdt_3_launcher(void);
void trainer_sdt_1(int retry);
void trainer_sdt_2(int retry);
void trainer_sdt_3(int retry);
static void trainer_mul_1_launcher(void);
static void trainer_mul_2_launcher(void);
void trainer_mul_1(int retry);
void trainer_mul_2(int retry);
void call_dp_levels(void);


int main(int argc, char** argv)
{
    void (*levels[14]) (void);

    levels[0] = trainer_branch_1_launcher;
    levels[1] = trainer_branch_2;
    levels[2] = trainer_branch_3;
    levels[3] = trainer_sdt_1_launcher;
    levels[4] = trainer_sdt_2_launcher;
    levels[5] = trainer_sdt_3_launcher;
    levels[6] = trainer_mul_1_launcher;
    levels[7] = trainer_mul_2_launcher;
    levels[8] = trainer_dp_1_launcher;	
    levels[9] = trainer_dp_2_launcher;
    levels[10] = trainer_dp_3_launcher;
    levels[11] = trainer_dp_4_launcher;
    levels[12] = trainer_dp_5_launcher;
    levels[13] = trainer_dp_6_launcher;


    if (argc == 2) // 1 argument
    {
        if (strcmp(argv[1],"-s") == 0) // sdt tests
        {
            trainer_sdt_1_launcher();

            if (!askContinue())
            {
                goto end;
            }
            trainer_sdt_2_launcher();
            
            if (!askContinue())
            {
              goto end;
            }
            trainer_sdt_3_launcher();

        } else if (strcmp(argv[1],"-b") == 0) // branch tests
        {
            trainer_branch_1(0);

            if (!askContinue())
            {
                goto end;
            }
            trainer_branch_2();

            if (!askContinue())
            {
                goto end;
            }
            trainer_branch_3();
	} else if (strcmp(argv[1], "-d") == 0) //data processing test
	{
		call_dp_levels();
	} else if (strcmp(argv[1], "-m") == 0) // multiply tests
	{
	    trainer_mul_1_launcher();
	    
	    if (!askContinue())
	    {
	      goto end;
	    }
	    trainer_mul_2_launcher();
	} else {
		int number = atoi(argv[1]);
		if (number < 1 || number > 14)
		{
			printf("Invalid level number chosen\n");
			exit(EXIT_SUCCESS);
		}

		// call level
		(*levels[number-1])();
	}
    } else
    {
        printf("arguments:\n-s for SDT trainer\n-b for Branch trainer\n-m for Multiply trainer\n-d for Dataprocessing trainer\n");
   	printf("or choose a level number - \n");
	printf("1 - 3 : Branch Training\n");
	printf("4 - 6 : Single Data Transfer Training\n");
	printf("7 - 8 : Multiply Training\n");
	printf("9 - 14: Dataprocessing Training\n\n");	
    }

    end:
    return 0;

}

/* TODO: look for a more efficient way to do this! */
void call_dp_levels(void) 
{
		trainer_dp_1_launcher();
		if (!askContinue())
		{
				return;
		}
		trainer_dp_2_launcher();

		if (!askContinue())
		{
				return;
		}
		trainer_dp_3_launcher();

		if (!askContinue())
		{
				return;
		}
		trainer_dp_4_launcher();

		if (!askContinue())
		{
				return;
		}
		trainer_dp_5_launcher();
		if (!askContinue())
		{
				return;
		}
		trainer_dp_6_launcher();
}

static void trainer_sdt_1_launcher(void)
{
    trainer_sdt_1(0);
}

static void trainer_sdt_2_launcher(void)
{
    trainer_sdt_2(0);
}

static void trainer_sdt_3_launcher(void)
{
    trainer_sdt_3(0);
}

static int askContinue(void)
{
    // do you want to continue?
    printf("Do you want to load next level? [y/n] ");
    char buffer[10];
    if (fgets(buffer, 10, stdin) == NULL)
    {
        perror("Fgets error\n");
        exit(EXIT_FAILURE);
    }
    removeEndLine(buffer);
    if (strcmp(buffer, "y") == 0)
    {
        return 1;
    }
    return 0;
}

void trainer_branch_1_launcher(void)
{
    trainer_branch_1(0);
}

void trainer_branch_1(int retry)
{
    // print welcome messages
    if (retry == 0)
    {
        printf("Welcome to Branching Level 1. You are given the following code:\n");
        printf("cmp r0,#0\n");
        printf("????????\n");
        printf("mov r1,#100\n");
        printf("b end\n");
        printf("target:\n");
        printf("mov r1,#200\n");
        printf("end:\n");
        printf("andeq r0,r0,r0\n");
        printf("Your aim is to type in the missing line so that Register R1 contains value\n");
        printf("200.\n");
    }
    if (retry > 2)
    {
        printf("Hint: you may wish to use branching instructions such as\n");
        printf("beq bne b bgt blt ble\n");
    }
    if (retry > 0)
    {
        printf("Try again:\n");
    }

    // initialize CPU and references
    References* r = initReferences();
    CPUStatus* cpu = initCPU();

    // add initializing instructions
    int status = 0;
    assert(onePass(r, cpu, "mov r0, #1") == ASSEMBLE_OK);
    interpret(r, cpu, &status);
    assert(onePass(r, cpu, "cmp r0, #0") == ASSEMBLE_OK);
    interpret(r, cpu, &status);

    // prompt
    do
    {
        interpretPrompt(r, cpu, &status);
    } while (status == RUN_COMMAND);

    // add finalizing instructions
    assert(onePass(r, cpu, "mov r1,#100") == ASSEMBLE_OK);
    interpret(r, cpu, &status);
    assert(onePass(r, cpu, "b end") != ASSEMBLE_ERROR);
    interpret(r, cpu, &status);
    assert(onePass(r, cpu, "target:") == ASSEMBLE_LABEL);
    interpret(r, cpu, &status);
    assert(onePass(r, cpu, "mov r1,#200") == ASSEMBLE_OK);
    interpret(r, cpu, &status);
    assert(onePass(r, cpu, "end:") == ASSEMBLE_LABEL);
    interpret(r, cpu, &status);
    assert(onePass(r, cpu, "andeq r0,r0,r0") == ASSEMBLE_OK);
    interpret(r, cpu, &status);

    // check for result
    int result = 0;
    if (cpu->regs->r_general[1] == 200)
    {
        result = 1;
    }

    // return, or retry
    if (!result)
    {
        trainer_branch_1(retry + 1);
    }

    printRegisters(cpu);
    printf("Your program:\n");
    printInstructions(r);
    printf("CONGRATULATIONS, you solved level 1\n\n");

    // garbage collecting
    destroyReferences(r);
    destroyCPU(cpu);

}

// checks that only allowed instructions are used
static int branch_2_check(char* line)
{
    char** splitted = createStringArray();
    int n = 0;
    splitString(line, splitted, &n);

    if (n == 3)
    {
        if (strcmp(splitted[0], "cmp") == 0 &&
            strcmp(splitted[1], "r0") == 0 &&
            strcmp(splitted[2], "#0") == 0)
        {
            destroyStringArray(splitted);
            return 1;
        }
    }

    if (n == 4)
    {
        if (strcmp(splitted[0],"sub") == 0 &&
            strcmp(splitted[1],"r0") == 0 &&
            strcmp(splitted[2],"r0") == 0 &&
            strcmp(splitted[3],"#1") == 0 )
        {
            destroyStringArray(splitted);
            return 1;
        }
    }

    if (isLabel(splitted[0]))
    {
        destroyStringArray(splitted);
        return 1;
    }

    if (n == 2)
    {
        if (strcmp(splitted[0], "ble") == 0 ||
            strcmp(splitted[0], "bgt") == 0 ||
            strcmp(splitted[0], "b") == 0 )
        {
            destroyStringArray(splitted);
            return 1;
        }
    }

    destroyStringArray(splitted);
    return 0;
}

void trainer_branch_2(void)
{
    // print messages
    printf("\n\n\n===================================================================\n");
    printf("Welcome to Branching Level 2. Translate the following code into\n");
    printf("assembler:\n");
    printf("=======================\n");
    printf("while (r0 > 0)\n");
    printf("{\n");
    printf("    r0 = r0 - 1\n");
    printf("}\n");
    printf("=======================\n");
    printf("You are provided the following code:\n");
    printf("mov r0,#100\n");
    printf("=======================\n");
    printf("AIM: r0 = 0\n");
    printf("=======================\n");
    printf("You can ONLY Use the following:\n");
    printf("cmp r0,#0\n");
    printf("sub r0,r0,#1\n");
    printf("(label)\n");
    printf("ble (label)\n");
    printf("bgt (label)\n");
    printf("b (label)\n");
    printf("=======================\n");

    // initialize CPU and references
    References* r = initReferences();
    CPUStatus* cpu = initCPU();

    // add initializing instructions
    int status = 0;
    assert(onePass(r, cpu, "mov r0, #100") == ASSEMBLE_OK);
     interpret(r, cpu, &status);

    const int ALLOWED_ATTEMPTS = 12;
    for (int i = 0; i < ALLOWED_ATTEMPTS; i++)
    {
        // prompt
        do
        {
            interpretPrompt(r, cpu, &status);
        } while (status == RUN_COMMAND);

        // check last instruction
        if (!branch_2_check(r->entries[r->currentI-1]->instruction))
        {
            printf("you can't use that\n");
            goto retry;
        }

        // check result
        if (cpu->regs->r_general[0] == 0)
        {
            goto success;
        }
    }

    // garbage collecting
    destroyReferences(r);
    destroyCPU(cpu);

    // do you want to retry?
    printf("The program should be shorter than this\n");
    retry:
    printf("Do you want to retry? [y/n] ");
    char buffer[10];
    if (fgets(buffer, 10, stdin) == NULL)
    {
        perror("Fgets error\n");
        exit(EXIT_FAILURE);
    }
    removeEndLine(buffer);
    if (strcmp(buffer, "y") == 0)
    {
        trainer_branch_2();
    }
    return;

    // success!
    success:
    printRegisters(cpu);
    printf("Your program:\n");
    printInstructions(r);
    printf("CONGRATULATIONS, you solved level 2\n\n\n");

    // garbage collecting
    destroyReferences(r);
    destroyCPU(cpu);
}


// checks that only allowed instructions are used
static int branch_3_check(char* line)
{
    char** splitted = createStringArray();
    int n = 0;
    splitString(line, splitted, &n);

    if (n == 3)
    {
        if (strcmp(splitted[0], "mov") == 0 &&
            strcmp(splitted[1], "r0") == 0 &&
            strcmp(splitted[2], "#0") == 0)
        {
            destroyStringArray(splitted);
            return 1;
        }

        if (strcmp(splitted[0], "cmp") == 0 &&
            strcmp(splitted[1], "r0") == 0 &&
            strcmp(splitted[2], "#100") == 0)
        {
            destroyStringArray(splitted);
            return 1;
        }
    }

    if (n == 4)
    {
        if (strcmp(splitted[0],"add") == 0 &&
            strcmp(splitted[1],"r0") == 0 &&
            strcmp(splitted[2],"r0") == 0 &&
            strcmp(splitted[3],"#1") == 0 )
        {
            destroyStringArray(splitted);
            return 1;
        }

        if (strcmp(splitted[0],"add") == 0 &&
            strcmp(splitted[1],"r5") == 0 &&
            strcmp(splitted[2],"r5") == 0 &&
            strcmp(splitted[3],"#1") == 0 )
        {
            destroyStringArray(splitted);
            return 1;
        }
    }

    if (isLabel(splitted[0]))
    {
        destroyStringArray(splitted);
        return 1;
    }

    if (n == 2)
    {
        if (strcmp(splitted[0], "blt") == 0 ||
            strcmp(splitted[0], "bge") == 0 ||
            strcmp(splitted[0], "bne") == 0 ||
            strcmp(splitted[0], "beq") == 0 ||
            strcmp(splitted[0], "b") == 0)
        {
            destroyStringArray(splitted);
            return 1;
        }
    }

    destroyStringArray(splitted);
    return 0;
}

void trainer_branch_3(void)
{
    // print messages
    printf("\n\n===================================================================\n");
    printf("Welcome to Branchineg Level 3. Translate the following code into\n");
    printf("assembler:\n");
    printf("==============\n");
    printf("for (int i = 0; i < 100; i++) {\n");
    printf("    r5 = r5 + 1;\n");
    printf("}\n");
    printf("==============\n");
    printf("AIM: r5 = 100\n");
    printf("==============\n");
    printf("You can use r0 to represent i. You may ONLY use the following:\n");
    printf("(label)\n");
    printf("blt (label)\n");
    printf("bge (label)\n");
    printf("bne (label)\n");
    printf("beq (label)\n");
    printf("b   (label)\n");
    printf("mov r0,#0\n");
    printf("cmp r0,#100\n");
    printf("add r0,r0,#1\n");
    printf("add r5,r5,#1\n");
    printf("==============\n");

    // initialize CPU and references
    References* r = initReferences();
    CPUStatus* cpu = initCPU();

    // add initializing instructions
    int status = 0;
    // (none)

    const int ALLOWED_ATTEMPTS = 20;
    for (int i = 0; i < ALLOWED_ATTEMPTS; i++)
    {
        // prompt
        do
        {
            interpretPrompt(r, cpu, &status);
        } while (status == RUN_COMMAND);

        // check last instruction
        if (!branch_3_check(r->entries[r->currentI-1]->instruction))
        {
            printf("you can't use that\n");
            goto retry;
        }

        // check result
        if (cpu->regs->r_general[5] == 100)
        {
            goto success;
        }
    }

    // garbage collecting
    destroyReferences(r);
    destroyCPU(cpu);

    // do you want to retry?
    printf("The program should be shorter than this\n");
    retry:
    printf("Do you want to retry? [y/n] ");
    char buffer[10];
    if (fgets(buffer, 10, stdin) == NULL)
    {
        perror("Fgets error\n");
        exit(EXIT_FAILURE);
    }
    removeEndLine(buffer);
    if (strcmp(buffer, "y") == 0)
    {
        trainer_branch_2();
    }
    return;

    // success!
    success:
    printRegisters(cpu);
    printf("Your program:\n");
    printInstructions(r);
    printf("CONGRATULATIONS, you solved level 3\n\n\n");

    // garbage collecting
    destroyReferences(r);
    destroyCPU(cpu);
}

// checks that only allowed instructions are used
static int sdt_1_check(char* line)
{
    char** splitted = createStringArray();
    int n = 0;
    splitString(line, splitted, &n);

    if (n == 3)
    {
        if (strcmp(splitted[0], "str") == 0 &&
            strcmp(splitted[1], "r0") == 0 &&
            strcmp(splitted[2], "[r3]") == 0)
        {
            destroyStringArray(splitted);
            return 1;
        }

        if (strcmp(splitted[0], "str") == 0 &&
            strcmp(splitted[1], "r0") == 0 &&
            strcmp(splitted[2], "[r3, #0]") == 0)
        {
            destroyStringArray(splitted);
            return 1;
        }

        if (strcmp(splitted[0], "ldr") == 0 &&
            strcmp(splitted[1], "r1") == 0 &&
            strcmp(splitted[2], "[r3]") == 0)
        {
            destroyStringArray(splitted);
            return 1;
        }

        if (strcmp(splitted[0], "ldr") == 0 &&
            strcmp(splitted[1], "r1") == 0 &&
            strcmp(splitted[2], "[r3, #0]") == 0)
        {
            destroyStringArray(splitted);
            return 1;
        }

        if (strcmp(splitted[0], "str") == 0 &&
            strcmp(splitted[1], "r0") == 0 &&
            strcmp(splitted[2], "[r3, #0x0]") == 0)
        {
            destroyStringArray(splitted);
            return 1;
        }

        if (strcmp(splitted[0], "ldr") == 0 &&
            strcmp(splitted[1], "r1") == 0 &&
            strcmp(splitted[2], "[r3, #0x0]") == 0)
        {
            destroyStringArray(splitted);
            return 1;
        }

    }

    if (n == 4)
    {
        if (strcmp(splitted[0],"str") == 0 &&
            strcmp(splitted[1],"r0") == 0 &&
            strcmp(splitted[2],"[r3]") == 0 &&
            strcmp(splitted[3],"#0") == 0 )
        {
            destroyStringArray(splitted);
            return 1;
        }

        if (strcmp(splitted[0],"ldr") == 0 &&
            strcmp(splitted[1],"r1") == 0 &&
            strcmp(splitted[2],"[r3]") == 0 &&
            strcmp(splitted[3],"#0") == 0 )
        {
            destroyStringArray(splitted);
            return 1;
        }

        if (strcmp(splitted[0],"str") == 0 &&
            strcmp(splitted[1],"r0") == 0 &&
            strcmp(splitted[2],"[r3]") == 0 &&
            strcmp(splitted[3],"#0x0") == 0 )
        {
            destroyStringArray(splitted);
            return 1;
        }

        if (strcmp(splitted[0],"ldr") == 0 &&
            strcmp(splitted[1],"r1") == 0 &&
            strcmp(splitted[2],"[r3]") == 0 &&
            strcmp(splitted[3],"#0x0") == 0 )
        {
            destroyStringArray(splitted);
            return 1;
        }
    }

    destroyStringArray(splitted);
    return 0;
}

void trainer_sdt_1(int retry)
{
    // print welcome messages
    if (retry == 0)
    {
        printf("Welcome to SDT Level 1. You are given the following code:\n");
        printf("mov r3, #10\n");
        printf("mov r0, #666\n");
        printf("????????\n");
        printf("????????\n");
        printf("andeq r0,r0,r0\n");
        printf("Your aim is to type in the missing lines such that the program acts like\n");
        printf("\'mov r1, #666\'.\n");
        printf("You may ONLY use STORE and LOAD instructions. Assume no distinction between\n");
        printf("pre and post indexing\n");
    }
    if (retry > 2)
    {
        printf("Hint: you are trying to LOAD in Register 1 a value which should already\n");
        printf("be STORED at a certain memory address -you may want to use address 10-.\n");
    }
    if (retry > 0)
    {
        printf("Try again:\n");
    }

    // initialize CPU and references
    References* r = initReferences();
    CPUStatus* cpu = initCPU();

    // add initializing instructions
    int status = 0;
    assert(onePass(r, cpu, "mov r3,#10") == ASSEMBLE_OK);
    interpret(r, cpu, &status);
    assert(onePass(r, cpu, "ldr r0,=0x29a") == ASSEMBLE_OK);
    interpret(r, cpu, &status);

    const int ALLOWED_ATTEMPTS = 10;
    for (int i = 0; i < ALLOWED_ATTEMPTS; i++)
    {
        // prompt
        do
        {
            interpretPrompt(r, cpu, &status);
        } while (status == RUN_COMMAND);

        // check last instruction
        if (!sdt_1_check(r->entries[r->currentI-1]->instruction))
        {
            printf("you can't use that\n");
            goto retry;
        }

        // check result
        if (cpu->regs->r_general[1] == 666)
        {
            goto success;
        }
    }

    // garbage collecting
    destroyReferences(r);
    destroyCPU(cpu);

    // do you want to retry?
    printf("The program should be shorter than this\n");
    retry:
    printf("Do you want to retry? [y/n] ");
    char buffer[10];
    if (fgets(buffer, 10, stdin) == NULL)
    {
        perror("Fgets error\n");
        exit(EXIT_FAILURE);
    }
    removeEndLine(buffer);
    if (strcmp(buffer, "y") == 0)
    {
      trainer_sdt_1(retry + 1);
    }
    return;

    // success!
    success:
    printRegisters(cpu);
    printf("Your program:\n");
    printInstructions(r);
    printf("CONGRATULATIONS, you solved SDT level 1\n\n\n");

    // garbage collecting
    destroyReferences(r);
    destroyCPU(cpu);
}

// checks that only allowed instructions are used
static int sdt_2_check(char* line)
{
    char** splitted = createStringArray();
    int n = 0;
    splitString(line, splitted, &n);

    if (n == 4)
    {
        if (strcmp(splitted[0],"str") == 0 &&
            strcmp(splitted[1],"r0") == 0 &&
            strcmp(splitted[2],"[r0]") == 0 &&
            strcmp(splitted[3],"#2") == 0 )
        {
            destroyStringArray(splitted);
            return 1;
        }

        if (strcmp(splitted[0],"str") == 0 &&
            strcmp(splitted[1],"r0") == 0 &&
            strcmp(splitted[2],"[r0]") == 0 &&
            strcmp(splitted[3],"#0x2") == 0 )
        {
            destroyStringArray(splitted);
            return 1;
        }
    }

    destroyStringArray(splitted);
    return 0;
}

void trainer_sdt_2(int retry)
{
    // print welcome messages
    if (retry == 0)
    {
        printf("Welcome to SDT Level 2. This is going to be a bit treaky!\n");
        printf("You are given the following code:\n");
        printf("mov r0, #8\n");
        printf("????????\n");
        printf("andeq r0,r0,r0\n");
        printf("Your aim is to put value '8' at address '8' and then store value '10'\n");
        printf("inside Register 0 WITH A SINGLE OPERATION.\n");
        printf("You may ONLY use one STORE or LOAD instruction.\n");
    }
    if (retry > 2)
    {
        printf("Hint: ever heard about POST INDEXING?\n");
    }
    if (retry > 0)
    {
        printf("Try again:\n");
    }

    // initialize CPU and references
    References* r = initReferences();
    CPUStatus* cpu = initCPU();

    // add initializing instructions
    int status = 0;
    assert(onePass(r, cpu, "mov r0,#8") == ASSEMBLE_OK);
    interpret(r, cpu, &status);

    const int ALLOWED_ATTEMPTS = 10;
    for (int i = 0; i < ALLOWED_ATTEMPTS; i++)
    {
        // prompt
        do
        {
            interpretPrompt(r, cpu, &status);
        } while (status == RUN_COMMAND);

        // check last instruction
        if (!sdt_2_check(r->entries[r->currentI-1]->instruction))
        {
            printf("you can't use that\n");
            goto retry;
        }

        // check result
        if (cpu->regs->r_general[0] == 10)
        {
            goto success;
        }
    }

    // garbage collecting
    destroyReferences(r);
    destroyCPU(cpu);

    // do you want to retry?
    printf("The program should be shorter than this\n");
    retry:
    printf("Do you want to retry? [y/n] ");
    char buffer[10];
    if (fgets(buffer, 10, stdin) == NULL)
    {
        perror("Fgets error\n");
        exit(EXIT_FAILURE);
    }
    removeEndLine(buffer);
    if (strcmp(buffer, "y") == 0)
    {
        trainer_sdt_2(retry + 1);
    }
    return;

    // success!
    success:
    printRegisters(cpu);
    printf("Your program:\n");
    printInstructions(r);
    printf("CONGRATULATIONS, you solved SDT level 2\n\n\n");

    // garbage collecting
    destroyReferences(r);
    destroyCPU(cpu);
}

// checks that only allowed instructions are used
static int sdt_3_check(char* line)
{
    char** splitted = createStringArray();
    int n = 0;
    splitString(line, splitted, &n);
    
    if (n == 2) 
    {
      if (strcmp(splitted[0], "blt") ||
          strcmp(splitted[0], "bge") ||
          strcmp(splitted[0], "b")   ||
          strcmp(splitted[0], "bgt") ||
          strcmp(splitted[0], "ble"))
      {
        destroyStringArray(splitted);
        return 1;
      }
    }
     
    if (n == 3) 
    {
      if (strcmp(splitted[0], "mov") == 0 &&
          strcmp(splitted[1], "r2") == 0 &&
          strcmp(splitted[2], "#10") == 0)
      {
        destroyStringArray(splitted);
        return 1;
      }
      
      if (strcmp(splitted[0], "mov") == 0 &&
          strcmp(splitted[1], "r0") == 0 &&
          strcmp(splitted[2], "#0") == 0)
      {
        destroyStringArray(splitted);
        return 1;
      }   
      
      if (strcmp(splitted[0], "mov") == 0 &&
          strcmp(splitted[1], "r0") == 0 &&
          strcmp(splitted[2], "#12") == 0)
      {
        destroyStringArray(splitted);
        return 1;
      }   
      
      if (strcmp(splitted[0], "cmp") == 0 &&
          strcmp(splitted[1], "r0") == 0 &&
          strcmp(splitted[2], "#12") == 0)
      {
        destroyStringArray(splitted);
        return 1;
      }
      
      if (strcmp(splitted[0], "cmp") == 0 &&
          strcmp(splitted[1], "r0") == 0 &&
          strcmp(splitted[2], "#0") == 0)
      {
        destroyStringArray(splitted);
        return 1;
      }

      if (strcmp(splitted[0], "bgt") == 0 &&
          strcmp(splitted[1], "r0") == 0 &&
          strcmp(splitted[2], "#0") == 0)
      {
        destroyStringArray(splitted);
        return 1;
      }

      if (strcmp(splitted[0],"str") == 0 &&
            strcmp(splitted[1],"r2") == 0 &&
            strcmp(splitted[2],"[r0, #128]") == 0 )
        {
            destroyStringArray(splitted);
            return 1;
      }

      if (strcmp(splitted[0],"ldr") == 0 &&
            strcmp(splitted[1],"r1") == 0 &&
            strcmp(splitted[2],"[r0, #128]") == 0 )
        {
            destroyStringArray(splitted);
            return 1;
      }

    }
  
    if (n == 4)
    {
        if (strcmp(splitted[0],"add") == 0 &&
            strcmp(splitted[1],"r5") == 0 &&
            strcmp(splitted[2],"r5") == 0 &&
            strcmp(splitted[3],"r1") == 0 )
        {
            destroyStringArray(splitted);
            return 1;
        }
        
        if (strcmp(splitted[0],"add") == 0 &&
            strcmp(splitted[1],"r0") == 0 &&
            strcmp(splitted[2],"r0") == 0 &&
            strcmp(splitted[3],"#4") == 0 )
        {
            destroyStringArray(splitted);
            return 1;
        }

        if (strcmp(splitted[0],"sub") == 0 &&
            strcmp(splitted[1],"r0") == 0 &&
            strcmp(splitted[2],"r0") == 0 &&
            strcmp(splitted[3],"#4") == 0 )
        {
            destroyStringArray(splitted);
            return 1;
        }
        
        if (strcmp(splitted[0],"add") == 0 &&
            strcmp(splitted[1],"r2") == 0 &&
            strcmp(splitted[2],"r2") == 0 &&
            strcmp(splitted[3],"r0") == 0 )
        {
            destroyStringArray(splitted);
            return 1;
        }
        
    }

    if (isLabel(splitted[0]))
    {
        destroyStringArray(splitted);
        return 1;
    }

    destroyStringArray(splitted);
    return 0;
}

void trainer_sdt_3(int retry)
{
    // print welcome messages
    if (retry == 0)
    {
        printf("Welcome to SDT Level 3.\n");
        printf("Translate the following code into\n");
        printf("assembler:\n");
        printf("=============\n");
        printf("for (int i = 0; i < 13; i+4) {\n");
        printf("  mem[i + 128] = 10 + i;\n");
        printf("}\n");
        printf("int temp, r;\n");
        printf("for (i = 12; i >= 0; i-4) {\n");
        printf("   temp = mem[i + 128];\n");
        printf("   r += temp;\n");
        printf("}\n");
        printf("=============\n");
        printf("AIM: r5 = 64\n");
        printf("=============\n");
        printf("You are allowed to use r0 and r1 to represent i\n");
        printf("and temp respectively, plus r2 to hold the intermediate\n");
        printf("result to store in mem at the firtst for loop\n");
        printf("and, of course, r5 to hold r.\n");
        printf("Assume all Regs are initialized to 0.\n");
        printf("You may ONLY use the following instructions,\n");
        printf("even more than once:\n");
        printf("add, str, ldr (both WITHOUT altering the base Register!),\n");
        printf("cmp, b, blt, bge, (label).\n");
    }

    if (retry > 2)
    {
      printf("Hint: did you rember to reset r2 to 10 before every iteration\n");
      printf("of the first loop?\n");
    }

    if (retry > 0)
    {
        printf("Try again:\n");
    }

    // initialize CPU and references
    References* r = initReferences();
    CPUStatus* cpu = initCPU();

    // add initializing instructions
    int status = 0;
    assert(onePass(r, cpu, "mov r0,#0") == ASSEMBLE_OK);
    interpret(r, cpu, &status);
    assert(onePass(r, cpu, "mov r1,#0") == ASSEMBLE_OK);
    interpret(r, cpu, &status);
    assert(onePass(r, cpu, "mov r2,#0") == ASSEMBLE_OK);
    interpret(r, cpu, &status);
    assert(onePass(r, cpu, "mov r5,#0") == ASSEMBLE_OK);
    interpret(r, cpu, &status);
    

    const int ALLOWED_ATTEMPTS = 22;
    for (int i = 0; i < ALLOWED_ATTEMPTS; i++)
    {
        // prompt
        do
        {
            interpretPrompt(r, cpu, &status);
        } while (status == RUN_COMMAND);

        // check last instruction
        if (!sdt_3_check(r->entries[r->currentI-1]->instruction))
        {
            printf("you can't use that\n");
            goto retry;
        }

        // check result
        if (cpu->regs->r_general[5] == 64)
        {
            goto success;
        }
    }

    // garbage collecting
    destroyReferences(r);
    destroyCPU(cpu);

    // do you want to retry?
    printf("The program should be shorter than this\n");
    retry:
    printf("Do you want to retry? [y/n] ");
    char buffer[10];
    if (fgets(buffer, 10, stdin) == NULL)
    {
        perror("Fgets error\n");
        exit(EXIT_FAILURE);
    }
    removeEndLine(buffer);
    if (strcmp(buffer, "y") == 0)
    {
        trainer_sdt_3(retry + 1);
    }
    return;

    // success!
    success:
    printRegisters(cpu);
    printf("Your program:\n");
    printInstructions(r);
    printf("CONGRATULATIONS, you solved the superPro(ca) SDT level 3!\n");
    printf("Gimmie five, bro!\n\n\n");

    // garbage collecting
    destroyReferences(r);
    destroyCPU(cpu);
}

static void trainer_mul_1_launcher(void)
{
    trainer_mul_1(0);
}

static void trainer_mul_2_launcher(void)
{
    trainer_mul_2(0);

}

static int multiply_1_check(char *line)
{
    char **splitted = createStringArray();
    int n = 0;
    splitString(line, splitted, &n);
    
    // case mul
    if (n == 4)
    {
        if (strcmp(splitted[0], "mul") == 0 &&
	    isReg(splitted[1]) && isReg(splitted[2]) 
	    && isReg(splitted[3]))
	{
	  destroyStringArray(splitted);
	  return 1;
	}
    }
    
    // case mla
    if (n == 5)
    {
        if (strcmp(splitted[0], "mla") == 0 && 
	    isReg(splitted[1]) && isReg(splitted[2]) 
	    && isReg(splitted[3]) && isReg(splitted[4]))
	{
	  destroyStringArray(splitted);
	  return 1;
	}
    }
    
    destroyStringArray(splitted);
    return 0;
}

void trainer_mul_1(int retry)
{
    // print welcome messages
    if (retry == 0)
    {
        printf("Welcome to Multiplying Level 1. You are given the following code:\n");
	printf("mov r0 #1\n");
	printf("mov r1 #3\n");
	printf("mov r2 #6\n");
	printf("????????\n");
	printf("andeq r0 r0 r0\n");
	printf("Your goal is to complete the missing line so that register r3\n");
	printf("contains 19 using either mul or mla\n");
    }
    
    if (retry > 2)
    {
        printf("Given that 19 is prime, you should discard using mul and use mla\n");
    }
    
    if (retry > 0)
    {
        printf("Try again:\n");
    }
    
    // initialize CPU and references
    References* r = initReferences();
    CPUStatus* cpu = initCPU();
    
    // add initializing instructions
    int status = 0;
    assert(onePass(r, cpu, "mov r0, #1") == ASSEMBLE_OK);
    interpret(r, cpu, &status);
    assert(onePass(r, cpu, "mov r1, #3") == ASSEMBLE_OK);
    interpret(r, cpu, &status);
    assert(onePass(r, cpu, "mov r2, #6") == ASSEMBLE_OK);
    interpret(r, cpu, &status);
    
    // prompt
    const int ALLOWED_ATTEMPTS = 12;
    for (int i = 0; i < ALLOWED_ATTEMPTS; i++)
    {
        // prompt
        do
        {
            interpretPrompt(r, cpu, &status);
        } while (status == RUN_COMMAND);

        // check last instruction
        if (!multiply_1_check(r->entries[r->currentI-1]->instruction))
        {
            printf("you can't use that\n");
            goto retry;
        }

        // check result
        if (cpu->regs->r_general[3] == 19)
        {
            goto success;
        }
    }
    
    // garbage collecting
    destroyReferences(r);
    destroyCPU(cpu);
    
    // do you want to retry?
    retry:
    printf("Do you want to retry? [y/n] ");
    char buffer[10];
    if (fgets(buffer, 10, stdin) == NULL)
    {
        perror("Fgets error\n");
        exit(EXIT_FAILURE);
    }
    removeEndLine(buffer);
    if (strcmp(buffer, "y") == 0)
    {
        trainer_mul_1_launcher();
    }
    return;
    
    // success
     success:
    printRegisters(cpu);
    printf("Your program:\n");
    printInstructions(r);
    printf("CONGRATULATIONS, you solved level 1\n\n\n");
    
    // garbage collecting
    destroyReferences(r);
    destroyCPU(cpu);
}

static int multiply_2_check(char *line)
{
    char **splitted = createStringArray();
    int n = 0;
    splitString(line, splitted, &n);
    
    // case is label
    if (isLabel(splitted[0]))
    {
        destroyStringArray(splitted);
        return 1;
    }
    
    // case jump command 
    if (n == 2)
    {
        if (strcmp(splitted[0], "b") == 0 ||
	    strcmp(splitted[0], "ble") == 0 ||
	    strcmp(splitted[0], "bgt") == 0 ||
	    strcmp(splitted[0], "blt") == 0 ||
	    strcmp(splitted[0], "bge") == 0 ||
	    strcmp(splitted[0], "bne") == 0 ||
	    strcmp(splitted[0], "beq") == 0)
	{
	    destroyStringArray(splitted);
	    return 1;
	}
    }
    
    // cmp or sub
    if (n == 3)
    {
        if ((strcmp(splitted[0], "cmp") == 0) &&
	    isReg(splitted[1]))
	{
	    destroyStringArray(splitted);
	    return 1;
	}
    }
    
    // case mul
    if (n == 4)
    {
        if (strcmp(splitted[0], "mul") == 0 &&
	    isReg(splitted[1]) && isReg(splitted[2]) 
	    && isReg(splitted[3]))
	{
	    destroyStringArray(splitted);
	    return 1;
	}
	
	if ((strcmp(splitted[0], "sub") == 0 ||
	     strcmp(splitted[0], "add") == 0) &&
	    isReg(splitted[1]) && isReg(splitted[2]))
	{
	    destroyStringArray(splitted);
	    return 1;
	}
    }
    
    // case mla
    if (n == 5)
    {
        if (strcmp(splitted[0], "mla") == 0 && 
	    isReg(splitted[1]) && isReg(splitted[2]) 
	    && isReg(splitted[3]) && isReg(splitted[4]))
	{
	    destroyStringArray(splitted);
	    return 1;
	}
    }
    
    destroyStringArray(splitted);
    return 0;
}

void trainer_mul_2(int retry)
{
    // print welcome messages
    if (retry == 0)
    {
        printf("Welcome to Multiplying Level 2. You are given the following code:\n");
	printf("mov r0 #7\n");
	printf("mov r1 #5\n");
	printf("mov r2 #2\n");
	printf("mov r3 #1\n");
	printf("=========\n");
	printf("INSERT CODE HERE\n");
	printf("=========\n");
	printf("andeq r0 r0 r0\n");
	printf("Your goal is to complete the missing lines so that register r3\n");
	printf("contains 16809 using mul or mla to change the values of the register.\n");
	printf("One way to solve this is to perform 7 to the power of 5 plus 2\n");
	printf("using a loop.\n");
    }
    
    if (retry > 2)
    {
        printf("HINT: You need to know basic branching before attempting this question\n");
    }
    
    if (retry > 0)
    {
        printf("Try again:\n");
    }
    
    // initialize CPU and references
    References* r = initReferences();
    CPUStatus* cpu = initCPU();
    
    // add initializing instructions
    int status = 0;
    assert(onePass(r, cpu, "mov r0, #7") == ASSEMBLE_OK);
    interpret(r, cpu, &status);
    assert(onePass(r, cpu, "mov r1, #5") == ASSEMBLE_OK);
    interpret(r, cpu, &status);
    assert(onePass(r, cpu, "mov r2, #2") == ASSEMBLE_OK);
    interpret(r, cpu, &status);
    assert(onePass(r, cpu, "mov r3, #1") == ASSEMBLE_OK);
    interpret(r, cpu, &status);
    
    // prompt
    const int ALLOWED_ATTEMPTS = 10;
    for (int i = 0; i < ALLOWED_ATTEMPTS; i++)
    {
        // prompt
        do
        {
            interpretPrompt(r, cpu, &status);
        } while (status == RUN_COMMAND);

        // check last instruction
        if (!multiply_2_check(r->entries[r->currentI-1]->instruction))
        {
            printf("you can't use that\n");
            goto retry;
        }

        // check result
        if (cpu->regs->r_general[3] == 16809)
        {
            goto success;
        }
    }
    
    // garbage collecting
    destroyReferences(r);
    destroyCPU(cpu);
    
    // do you want to retry?
    retry:
    printf("Do you want to retry? [y/n]");
    char buffer[10];
    if (fgets(buffer, 10, stdin) == NULL)
    {
        perror("Fgets error\n");
        exit(EXIT_FAILURE);
    }
    removeEndLine(buffer);
    if (strcmp(buffer, "y") == 0)
    {
        trainer_mul_2(retry + 1);
    }
    return;
    
    // success
     success:
    printRegisters(cpu);
    printf("Your program:\n");
    printInstructions(r);
    printf("CONGRATULATIONS, you solved level 2\n\n\n");
    
    // garbage collecting
    destroyReferences(r);
    destroyCPU(cpu);
}


