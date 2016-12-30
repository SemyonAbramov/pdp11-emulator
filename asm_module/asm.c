
/*
#include "asm.h"
#include "decode.h"
#include "cpu.h"
#include <stdlib.h>
#include <string.h>
*/


/*
asm_arr_t* init_instr_array(int arr_size)
{
	asm_arr_t* arr = (asm_arr_t*)malloc(sizeof(asm_arr_t));
	arr->array = (asm_instr_t*)malloc(sizeof(asm_instr_t) * arr_size);
	arr->count = 0;

	if (arr == NULL)
	{
		printf("Can not create instruction array, malloc failed ! \n");
		abort();
	}

	return arr;
}

void deinit_instr_array(asm_instr_t* arr)
{
	free(arr->array);
	free(arr);
}
*/

asm_instr_t* init_instr_array(int arr_size)
{
	arr= (asm_instr_t*)malloc(sizeof(asm_instr_t) * arr_size);
	arr->instr = (char*)malloc(sizeof(char) * DEF_INSTR_LEN);
	count = 0;

	if (arr == NULL)
	{
		printf("Can not create instruction array, malloc failed ! \n");
		abort();
	}

	return arr;
}

void deinit_instr_array(asm_instr_t* arr)
{
	free(arr->instr);	
	free(arr);
}

char* get_reg(uint16_t mode, uint16_t reg)
{
	switch (mode)
	{
		case REG_ADDR:
			return reg_mode[reg];
			
		case REG_DEF_ADDR:
			return reg_def_mode[reg];

		case AUTOINC_ADDR:
			return autoinc_mode[reg];

		case AUTOINC_DEF_ADDR:
			return autoinc_def_mode[reg];

		case AUTODEC_ADDR:
			return autodec_mode[reg];

		case AUTODEC_DEF_ADDR:
			return autodec_def_mode[reg];

		case INDEX_ADDR:

		case INDEX_DEF_ADDR:
		
		case IMM_PC:

		case ABS_PC:

		case REL_PC:

		case REL_DEF_PC:

		printf("Asm module: Reg reg pc not implemented yet\n");
		abort();

		default:
			printf("Get reg asm error \n");
			abort();		
	}
}


void gen_single_op_instr(char** instr, char* name, uint16_t byte_mode, uint16_t mode, uint16_t reg)
{
	int len = strlen(name);
	srncpy(*instr, name, len);

	if (byte_mode)
	{
		strncpy((*instr) + len, "b", 1);
		len += 1;
	}

	char* dst = get_reg(mode, reg);

	strncpy((*instr) + len, dst, strlen(dst));	

	return;
}

void gen_double_op_instr(char** instr, char* name, uint16_t byte_mode, uint16_t mode, uint16_t reg)
{
	int len = strlen(name);
	srncpy(*instr, name, len);

	if (byte_mode)
	{
		strncpy((*instr) + len, "b", 1);
		len += 1;
	}

	char* dst = get_reg(mode, reg);

	strncpy((*instr) + len, dst, strlen(dst));	

	return;
}


void asm_module_single(asm_arr_t* arr, char* name, uint16_t* addr, uint8_t breakpoint, uint16_t byte_mode, uint16_t mode, uint16_t reg)
{
	gen_single_op_instr(&(arr->instr), name,  


}