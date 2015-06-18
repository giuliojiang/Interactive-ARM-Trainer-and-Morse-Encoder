#ifndef ASSEMBLEDATAPROCESSING_H
#define ASSEMBLEDATAPROCESSING_H

/*	OPCODES -

	 0000	and
	 0001	eor
	 0010	sub
	 0011	rsb
	 0100	add
	 1100	orr
	 1101	mov
	 1000	tst
	 1001	teq
	 1010	cmp  */

static const byte_t opcode_and = 0x0;
static const byte_t opcode_eor = 0x1;
static const byte_t opcode_sub = 0x2;
static const byte_t opcode_rsb = 0x3;
static const byte_t opcode_add = 0x4;
static const byte_t opcode_orr = 0xC;
static const byte_t opcode_mov = 0xD;
static const byte_t opcode_tst = 0x8;
static const byte_t opcode_teq = 0x9;
static const byte_t opcode_cmp = 0xA;  //=10!!

/* instruction format */
static const int condPos = 31;
static const int condLength = 4;

static const int IBitPos = 25;

static const int opcodePos = 24;
static const int opcodeLength = 4;

static const int SBitPos = 20;

static const int RnPos = 19;
static const int RnLength = 4;

static const int RdPos = 15;
static const int RdLength = 4;


/* operand2 general */
static const int operand2Pos = 11;
static const int operand2Length = 12;

/* operand2 immediate operand case */
static const int operand2_rotatePos = 11;
static const int operand2_rotateLength = 4;
static const int operand2_immPos = 7;
static const int operand2_immLength = 8;

/* operand2 obtained from a register case */
static const int operand2_registerRmPos = 3;
static const int operand2_registerRmLength = 4;
static const int operand2_registerTypePos = 4;
static const int operand2_registerShiftTypePos = 6;
static const int operand2_registerShiftTypeLength = 2;

/* constant shift case */
static const int operand2_registerConstantPos = 11;
static const int operand2_registerConstantLength = 5;

/* shifted register case */
static const int operand2_registerRsPos = 11;
static const int operand2_registerRsLength = 4;

/*Code		Shift Type
  00	logical left (lsl)
  01 	logical right (lsr)
  10 	arithmetic right (asr)
  11	rotate right (ror) */

static const word_t shiftCode_lsl = 0x0;
static const word_t shiftCode_lsr = 0x1;
static const word_t shiftCode_asr = 0x2;
static const word_t shiftCode_ror = 0x3;

static const int bitsPerByte = 8;


/* converts a line of assembly code into its corresponding dataprocessing instruction */
word_t assemble_dataprocessing(char *assemblyLine, int* status);

/* returns a word whose least significant 12 bits are the encoding of operand2 */
word_t getOperand2Immediate(char *operand2String, int *IBitVal, int* status);

/* returns true if and only if the given word can be represented as an 8 bit operand with
a 4 bit shift factor. Also sets the representation if the condition is true. */
int getRepresentation(word_t word, word_t *representation);

/* returns operand2 in the case that it is obtained from a register (optional case) */
word_t getOperand2Register(char **asseblyLineOperands, int length, int* status);

/* returns the shift code */
word_t getShiftCode(char *shiftString, int* status);

/* tests for operand2 immediate value case */
void executeDataprocessing_getRepresentationTests(void);

/* tests for operand2 register case */
void executeDataprocessing_getOperand2RegisterTests(void);

/* testing instructions as a whole */
void executeDataprocessingTests(void);

void assembleDataprocessing_callTests(void);

/* returns the corresponding move instruction */
char *lslGetMoveInstr(char **splitStringArray);

/* testing the lslGetMovInstr */
//void getMoveInstrTests(void);

#endif














