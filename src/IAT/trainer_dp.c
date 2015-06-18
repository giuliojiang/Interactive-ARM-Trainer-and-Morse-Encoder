#include <stdlib.h>
#include <stdio.h>
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

//TODO: Following successful compilation, make the dp check functions static

/* arithmatic tests */

//sub
void trainer_dp_1(int retry) {
	printf("DATA PROCESSING LEVEL 1\n\n");

	printf("INSTRUCTION : SUB\n\n");

	printf("===CODE====\n");
	printf("mov r0, #24\n");
	printf("mov r1, #51\n");
	printf("?????????????		; r2 = r1 - r0\n\n");
	
	printf("Note that you are only allowed to use the 'sub' instruction\n");

	// initialize CPU and references
  	References* r = initReferences();
    	CPUStatus* cpu = initCPU();

   	// add initializing instructions
    	int status = 0;
    	assert(onePass(r, cpu, "mov r0, #24") == ASSEMBLE_OK);
     	interpret(r, cpu, &status);

	assert(onePass(r, cpu, "mov r1, #51") == ASSEMBLE_OK);
	interpret(r, cpu, &status);

	// prompt
	do
	{
		interpretPrompt(r, cpu, &status);
	} while (status == RUN_COMMAND);

	//check for result 
	int result = 0;
	if (cpu->regs->r_general[2] == 27)
	{
		result = 1;
	}

	//return or retry
	if (!result) 
	{
		trainer_dp_1(retry + 1);
	}

	printRegisters(cpu);
	printf("Your program:\n");
	printInstructions(r);
	printf("CONGRATULATIONS, you solved level 1\n\n");

	// garbage collection
	destroyReferences(r);
	destroyCPU(cpu);
	return;
}

// returns 1 for allowed instructions, 0 otherwise
int dp_1_check(char *line) 
{
	char** splitted = createStringArray();
	int n = 0;
	splitString(line, splitted, &n);

	if (n == 4) 
	{
		if (strcmp(splitted[0],"sub") == 0 &&
				strcmp(splitted[1],"r2") == 0 &&
				strcmp(splitted[2],"r1") == 0 &&
				strcmp(splitted[3],"r0") == 0 )
		{
			destroyStringArray(splitted);
			return 1;
		}
	}
	destroyStringArray(splitted);
	return 0;

}


void trainer_dp_1_launcher(void) 
{
	trainer_dp_1(0);
}

//rsb
void trainer_dp_2(int retry) {
	//mov r0, #24
	//mov r1, #51
	//???????????		; do the same as above using rsb
	
	printf("DATA PROCESSING LEVEL 2\n\n");

	printf("INSTRUCTION : RSB\n\n");
	
	printf("===CODE===\n");
	printf("mov r0, #24\n");
	printf("mov r1, #51\n");
	printf("?????????????		; r2 = r1 - r0\n\n");
	
	printf("Note that you are only allowed to use the 'rsb' instruction\n");

	// initialize CPU and references
  	References* r = initReferences();
    	CPUStatus* cpu = initCPU();

   	// add initializing instructions
    	int status = 0;
    	assert(onePass(r, cpu, "mov r0, #24") == ASSEMBLE_OK);
     	interpret(r, cpu, &status);

	assert(onePass(r, cpu, "mov r1, #51") == ASSEMBLE_OK);
	interpret(r, cpu, &status);

	// prompt
	do
	{
		interpretPrompt(r, cpu, &status);
	} while (status == RUN_COMMAND);

	//check for result
	int result = 0; 
	if (cpu->regs->r_general[2] == 27)
	{
		result = 1;
	}

	//return or retry
	if (!result) 
	{
		trainer_dp_1(retry + 1);
	}

	printRegisters(cpu);
	printf("Your program:\n");
	printInstructions(r);
	printf("CONGRATULATIONS, you solved level 2\n\n");

	// garbage collection
	destroyReferences(r);
	destroyCPU(cpu);
	return;

}

// returns 1 for allowed instructions, 0 otherwise
int dp_2_check(char *line) 
{
	char** splitted = createStringArray();
	int n = 0;
	splitString(line, splitted, &n);

	if (n == 4) 
	{
		if (strcmp(splitted[0],"rsb") == 0 &&
				strcmp(splitted[1],"r2") == 0 &&
				strcmp(splitted[2],"r0") == 0 &&
				strcmp(splitted[3],"r1") == 0 )
		{
			destroyStringArray(splitted);
			return 1;
		}
	}
	destroyStringArray(splitted);
	return 0;

}
void trainer_dp_2_launcher(void) 
{
	trainer_dp_2(0);
}

//swap mov
void trainer_dp_3(int retry) 
{

	
	printf("DATAPROCESSING LEVEL 3\n\n");

	printf("SWAP : MOVE\n");
	printf("PROBLEM: Using only the mov command, swap the contents of registers r0 and r1\n\n");
	
	printf("===CODE====\n");
	printf("mov r0, #21\n");
	printf("mov r1, #26\n");
	printf("??????????????			;swap the contents of register r0 and r1\n\n");

	printf("Note that you are only allowed to use the 'mov' instruction\n");
	// initialize CPU and references
  	References* r = initReferences();
    	CPUStatus* cpu = initCPU();

   	// add initializing instructions
    	int status = 0;
    	assert(onePass(r, cpu, "mov r0, #21") == ASSEMBLE_OK);
     	interpret(r, cpu, &status);

	assert(onePass(r, cpu, "mov r1, #26") == ASSEMBLE_OK);
	interpret(r, cpu, &status);

	const int ALLOWED_ATTEMPTS = 6;
	for (int i = 0; i < ALLOWED_ATTEMPTS; i++) 
	{
		//prompt
		do
		{
			interpretPrompt(r, cpu, &status);
		} while (status == RUN_COMMAND);

		//check last instruction
		if (!dp_3_check(r->entries[r->currentI-1]->instruction))
		{
			printf("you can't use that\n");
			goto retry;
		}

		//check result
		if (cpu->regs->r_general[0] == 26 && cpu->regs->r_general[1] == 21)
		{
			goto success;
		}

	}

	// garbage collection
	destroyReferences(r);
	destroyCPU(cpu);
	
	printRegisters(cpu);

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
		trainer_dp_3(retry + 1);
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
int dp_3_check(char *line)
{
	char** splitted = createStringArray();
	int n = 0;
	splitString(line, splitted, &n);

	//it is mandatory to only use the mov command 
	if (strcmp(splitted[0], "mov") == 0) 
	{
		return 1;
	}

	destroyStringArray(splitted);
	return 0;
}
void trainer_dp_3_launcher(void) 
{
	trainer_dp_3(0);
}
 
//swap integer
void trainer_dp_4(int retry) 
{
		
	printf("DATA PROCESSING LEVEL 4\n\n");

	printf("INTEGER SWAP : ADD, SUB and RSB\n");
	printf("PROBLEM: Using only the add, sub and/or rsb commands, and no temporary variables ");
	printf("(use only r0 and r1), swap the contents of registers r0 and r1\n\n");
	
	printf("===CODE====\n");
	printf("mov r0, #12\n");
	printf("mov r1, #15\n");
	printf("??????????????			;swap the contents of register r0 and r1\n\n");

	printf("Note that you are only allowed to use the 'add', 'sub' and 'rsb' commands\n");

	// initialize CPU and references
  	References* r = initReferences();
    	CPUStatus* cpu = initCPU();

   	// add initializing instructions
    	int status = 0;
    	assert(onePass(r, cpu, "mov r0, #12") == ASSEMBLE_OK);
     	interpret(r, cpu, &status);

	assert(onePass(r, cpu, "mov r1, #15") == ASSEMBLE_OK);
	interpret(r, cpu, &status);

	const int ALLOWED_ATTEMPTS = 6;
	for (int i = 0; i < ALLOWED_ATTEMPTS; i++) 
	{
		//prompt
		do
		{
			interpretPrompt(r, cpu, &status);
		} while (status == RUN_COMMAND);

		//check last instruction
		if (!dp_4_check(r->entries[r->currentI-1]->instruction))
		{
			printf("you can't use that\n");
			goto retry;
		}
		//check result
		if (cpu->regs->r_general[0] == 15 && cpu->regs->r_general[1] == 12)
		{
			goto success;
		}

	}

	// garbage collection
	destroyReferences(r);
	destroyCPU(cpu);
	
	printRegisters(cpu);

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
		trainer_dp_4(retry + 1);
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
int dp_4_check(char *line)
{
	char** splitted = createStringArray();
	int n = 0;
	splitString(line, splitted, &n);
	//boolean variable that is set to 1 only when the opcode is add, sub or rsb
	int asr = 0;
	//boolean variable that is set to 1 only if r0 and r1 are the registers used
	//i.e no temporary variables
	int noTemp = 0;

	//it is mandatory to only use the mov command 
	if (strcmp(splitted[0], "add") == 0 || 
		strcmp(splitted[0], "sub") == 0 ||
		strcmp(splitted[0], "rsb") == 0)  
	{
		asr = 1;
	}
	if ((strcmp(splitted[1], "r1") == 0 || strcmp(splitted[1], "r0") == 0) &&
		(strcmp(splitted[2], "r1") == 0 || strcmp(splitted[2], "r0") == 0) &&
		(strcmp(splitted[3], "r1") == 0 || strcmp(splitted[3], "r0") == 0)) 
	{
		noTemp = 1;
	}
	return noTemp * asr;
} 
void trainer_dp_4_launcher(void) 
{
	trainer_dp_4(0);
}

//swap eor
void trainer_dp_5(int retry) 
{
	
	printf("DATA PROCESSING LEVEL 5\n\n");

	printf("SWAP : EOR\n");
	printf("PROBLEM: Using only the eor command, and no temporary variables");
	printf("(use only registers r0 and r1), swap the contents of register r0 and r1\n\n");
	
	printf("===CODE====\n");
	printf("mov r0, #41\n");
	printf("mov r1, #62\n");
	printf("??????????????			;swap the contents of register r0 and r1\n\n");	

	printf("Note that you are only allowed to use the 'eor' instruction\n");

	// initialize CPU and references
  	References* r = initReferences();
    	CPUStatus* cpu = initCPU();

   	// add initializing instructions
    	int status = 0;
    	assert(onePass(r, cpu, "mov r0, #41") == ASSEMBLE_OK);
     	interpret(r, cpu, &status);

	assert(onePass(r, cpu, "mov r1, #62") == ASSEMBLE_OK);
	interpret(r, cpu, &status);

	const int ALLOWED_ATTEMPTS = 6;
	for (int i = 0; i < ALLOWED_ATTEMPTS; i++) 
	{
		//prompt
		do
		{
			interpretPrompt(r, cpu, &status);
		} while (status == RUN_COMMAND);

		//check last instruction
		if (!dp_5_check(r->entries[r->currentI-1]->instruction))
		{
			printf("you can't use that\n");
			goto retry;
		}
		//check result
		if (cpu->regs->r_general[0] == 62 && cpu->regs->r_general[1] == 41)
		{
			goto success;
		}

	}

	// garbage collection
	destroyReferences(r);
	destroyCPU(cpu);
	
	printRegisters(cpu);

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
		trainer_dp_5(retry + 1);
	}
	return;

	// success!
success:
	printRegisters(cpu);
	printf("Your program:\n");
	printInstructions(r);
	printf("CONGRATULATIONS, you solved level 3\n\n");
	
	printf("NOTE: this method does not use extra storage space through the use of a temp\n");
	printf("variable and is also free from the danger of overflow that could be caused\n");
	printf("due to the addition in the previous swap\n");

	printf("GENIUS!\n");
	
	// garbage collecting
	destroyReferences(r);
	destroyCPU(cpu);
	return;
}
int dp_5_check(char *line) 
{
	char** splitted = createStringArray();
	int n = 0;
	splitString(line, splitted, &n);
	int isEor = !strcmp(splitted[0], "eor");
	//boolean variable that is set to 1 only if r0 and r1 are the registers used
	//i.e no temporary variables
	int noTemp = 0;

	//it is mandatory to only use the mov command 
	if ((strcmp(splitted[1], "r1") == 0 || strcmp(splitted[1], "r0") == 0) &&
		(strcmp(splitted[2], "r1") == 0 || strcmp(splitted[2], "r0") == 0) &&
		(strcmp(splitted[3], "r1") == 0 || strcmp(splitted[3], "r0") == 0)) 
	{
		noTemp = 1;
	}
	return noTemp * isEor;
} 
void trainer_dp_5_launcher(void) 
{
	trainer_dp_5(0);
}

/* bitwise tests */

//tst
void trainer_dp_6(int retry) 
{
	printf("DATA PROCESSING LEVEL 6\n\n");

	printf("INSTRUCTION : TST\n");
	printf("PROBLEM: In the following code, r0 is not equal to 21. What must it be equal to then?\n\n");
	printf("===CODE====\n");
	printf("tst r0, r0\n");	
	printf("jz end\n");
	printf("mov r0, #21\n");
	printf("end: \n\n");

	printf("answer : ");
	char buffer[10];
	if (fgets(buffer, 10, stdin) == NULL)
	{
		perror("Fgets error\n");
		exit(EXIT_FAILURE);
	}
	removeEndLine(buffer);
	if (atoi(buffer) == 0 && strlen(buffer) > 0) {
		printf("Yes! tst with the variable itself is a way to check if it is zero.\n");
		return;
	} 
	else 
	{
		printf("Sorry, wrong answer!\n");
	}
	
	printf("Do you want to retry? [y/n] ");
	char retryBuffer[10];
	if (fgets(retryBuffer, 10, stdin) == NULL)
	{
		perror("Fgets error\n");
		exit(EXIT_FAILURE);
	}
	removeEndLine(retryBuffer);
	if (strcmp(retryBuffer, "y") == 0)
	{
		trainer_dp_6(retry + 1);
	}

}
void trainer_dp_6_launcher(void) 
{
	trainer_dp_6(0);
}

