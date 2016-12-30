#ifndef ASM_H
#define ASM_H

#include <stdint.h>

#define DEF_INSTR_LEN	20

int count;

struct asm_instr
{
	char* instr;
	uint16_t* address;
	uint8_t breakpoint;
} asm_instr_t;


/*
struct asm_arr
{
	asm_instr_t* array;
	int count;
} asm_arr_t;
*/

char** reg_mode = {"R0", "R1", "R2", "R3", "R4", "R5", "R6", "R7"};

char** reg_def_mode = {"(R0)", "(R1)", "(R2)", "(R3)", "(R4)", "(R5)", "(R6)", "(R7)"};
char** autoinc_mode = {"(R0)+", "(R1)+", "(R2)+", "(R3)+", "(R4)+", "(R5)+", "(R6)+", "(R7)+"};
char** autoinc_def_mode = {"@(R0)+", "@(R1)+", "@(R2)+", "@(R3)+", "@(R4)+", "@(R5)+", "@(R6)+", "@(R7)+"};
char** autodec_mode = {"-(R0)", "-(R1)", "-(R2)", "-(R3)", "-(R4)", "-(R5)", "-(R6)", "-(R7)"};
char** autodec_def_mode = {"@-(R0)", "@-(R1)", "@-(R2)", "@-(R3)", "@-(R4)", "@-(R5)", "@-(R6)", "@-(R7)"};



#endif // ASM_H