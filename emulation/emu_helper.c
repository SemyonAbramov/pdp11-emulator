//#include "emu_helper.h"
#include "cpu/cpu.h"
#include "decode/decode.h"
#include "stdlib.h"
#include "stdio.h"
#include <stdint.h>

uint16_t fetch_word_from_mem(vcpu_t* vcpu)
{
	uint16_t operand = *(uint16_t*)((uint8_t*)vcpu->mem_entry + vcpu->regs[PC]);			// FIXME: Need to check
	vcpu->regs[PC] += 2;
	return operand;
}

uint16_t get_reg(vcpu_t* vcpu, uint16_t disp, uint16_t isa_mode)
{
	if (isa_mode)
		return ((uint8_t*)(vcpu->regs))[disp];			// FIXME: Here need to check bytes and words trouble 
	else
		return vcpu->regs[disp];

	return 0;
}

uint16_t get_reg_def(vcpu_t* vcpu, uint16_t disp, uint16_t isa_mode, uint8_t** address)
{
	if (isa_mode)
	{
		*address = ((uint8_t*)vcpu->mem_entry + vcpu->regs[disp] - 1);
		return *((uint8_t*)vcpu->mem_entry + vcpu->regs[disp] - 1);;
	}	
	else
	{
		*address = ((uint8_t*)vcpu->mem_entry + vcpu->regs[disp]);
		return *(uint16_t*)((uint8_t*)vcpu->mem_entry + vcpu->regs[disp]);
	}	
	
	return 0;
}

uint16_t get_autoinc(vcpu_t* vcpu, uint16_t disp, uint16_t isa_mode, uint8_t** address)
{
	uint16_t operand = 0;	

	if (isa_mode)
	{
//		printf("autoincrement\n");	
		*address = ((uint8_t*)vcpu->mem_entry + vcpu->regs[disp] - 1);
//		printf("address: %o\n", vcpu->regs[disp]);
//		printf("address - 1: %o\n", vcpu->regs[disp] - 1);
//		operand = *((uint8_t*)vcpu->mem_entry + vcpu->regs[disp] - 1);						// FIXME: Need to check
		operand = *((uint8_t*)vcpu->mem_entry + vcpu->regs[disp]);
		vcpu->regs[disp] +=1;			
	}
	else
	{
		*address = ((uint8_t*)vcpu->mem_entry + vcpu->regs[disp]);
		operand = *(uint16_t*)((uint8_t*)vcpu->mem_entry + vcpu->regs[disp]);		// FIXME: Need to check this line's correctness		
		vcpu->regs[disp] +=2;		
	}

	return operand;
}


uint16_t get_autodec(vcpu_t* vcpu, uint16_t disp, uint16_t isa_mode, uint8_t** address)
{
	uint16_t operand = 0;	
	uint16_t reg_val = 0;

	if (isa_mode)
	{
		vcpu->regs[disp] -= 1;
		*address = ((uint8_t*)vcpu->mem_entry + vcpu->regs[disp] - 1);
		operand = *((uint8_t*)vcpu->mem_entry + vcpu->regs[disp] - 1);		// FIXME: Need to check this line's correctness
	}
	else
	{
		vcpu->regs[disp] -=2;
		*address = ((uint8_t*)vcpu->mem_entry + vcpu->regs[disp]);
		operand = *(uint16_t*)((uint8_t*)vcpu->mem_entry + vcpu->regs[disp]);		// FIXME: Need to check this line's correctness		
	}

	return operand;	
}


uint16_t get_autoinc_def(vcpu_t* vcpu, uint16_t disp, uint16_t isa_mode, uint8_t** address)
{
	uint16_t operand_addr = 0;
	uint16_t operand = 0;															
	
	/* FIXME: Issue of byte instructions is not explored yet*/

	operand_addr = *(uint16_t*)((uint8_t*)vcpu->mem_entry + vcpu->regs[disp]);		// FIXME: Need to check this line's correctness
	
	if (isa_mode) 
	{
		*address = ((uint8_t*)vcpu->mem_entry + operand_addr - 1);
		operand = *((uint8_t*)vcpu->mem_entry + operand_addr - 1);
	}	

	else
	{
		*address = ((uint8_t*)vcpu->mem_entry + operand_addr);
		operand = *(uint16_t*)((uint8_t*)vcpu->mem_entry + operand_addr);
	}
		
	vcpu->regs[disp] += 2;

	return operand;
}

uint16_t get_autodec_def(vcpu_t* vcpu, uint16_t disp, uint16_t isa_mode, uint8_t** address)
{
	uint16_t operand_addr = 0;
	uint16_t operand = 0;
	uint16_t reg_val = 0;

	vcpu->regs[disp] -= 2;															// FIXME: ATTENTION	!!! what to do for byte operations ???
//	reg_val = vcpu->regs[disp] - 2;

	operand_addr = *(uint16_t*)((uint8_t*)vcpu->mem_entry + vcpu->regs[disp]);		// FIXME: Need to check this line's correctness
	
	if (isa_mode)
	{
		*address = ((uint8_t*)vcpu->mem_entry + operand_addr - 1);
		operand = *((uint8_t*)vcpu->mem_entry + operand_addr - 1);
	}
	else
	{
		*address = ((uint8_t*)vcpu->mem_entry + operand_addr);
		operand = *(uint16_t*)((uint8_t*)vcpu->mem_entry + operand_addr);
	}
		
	return operand;
}

uint16_t get_index(vcpu_t* vcpu, uint16_t disp, uint16_t isa_mode, uint8_t** address)
{
	uint16_t operand = 0, post_word = 0;
	
	post_word = fetch_word_from_mem(vcpu);

	if (isa_mode)
	{
		*address = ((uint8_t*)vcpu->mem_entry + vcpu->regs[disp] + post_word - 1);
		return *((uint8_t*)vcpu->mem_entry + vcpu->regs[disp] + post_word - 1);
	}
	else
	{	
		*address = ((uint8_t*)vcpu->mem_entry + vcpu->regs[disp] + post_word);
		return *(uint16_t*)((uint8_t*)vcpu->mem_entry + vcpu->regs[disp] + post_word);	
	}

	return 0;
}

uint16_t get_index_def(vcpu_t* vcpu, uint16_t disp, uint16_t isa_mode, uint8_t** address)
{
	uint16_t operand = 0, post_word = 0, operand_addr = 0;
	post_word = fetch_word_from_mem(vcpu);

	operand_addr = *(uint16_t*)((uint8_t*)vcpu->mem_entry + vcpu->regs[disp] + post_word);	

	if (isa_mode)
	{
		*address = ((uint8_t*)vcpu->mem_entry + vcpu->regs[disp] + post_word - 1);
		operand = *((uint8_t*)vcpu->mem_entry + vcpu->regs[disp] + post_word - 1);
	}
	else
	{
		*address = ((uint8_t*)vcpu->mem_entry + vcpu->regs[disp] + post_word);
		operand = *(uint16_t*)((uint8_t*)vcpu->mem_entry + vcpu->regs[disp] + post_word);
	}	
	
	return operand;
}

uint16_t get_imm_pc(vcpu_t* vcpu)  						// FIXME: Need to check all PC helpers
{
	uint16_t post_word = 0;
	post_word = fetch_word_from_mem(vcpu);
//	printf("vcpu PC: %o\n", vcpu->regs[PC]);

	return post_word;
}

uint16_t get_abs_pc(vcpu_t* vcpu, uint8_t** address)
{
	uint16_t post_word = 0, operand_addr = 0;
	
	post_word = fetch_word_from_mem(vcpu);
	*address = ((uint8_t*)vcpu->mem_entry + post_word);
//	printf("post word: %o\n", post_word);

	return *(uint16_t*)((uint8_t*)vcpu->mem_entry + post_word);	
}

/*
uint16_t get_rel_pc(vcpu_t* vcpu, uint8_t** address)
{
	uint16_t post_word = 0, operand_addr = 0;
	
	post_word = fetch_word_from_mem(vcpu);
	printf("post word %o\n", post_word);

	printf("pc: %o\n", vcpu->regs[PC]);

	*address = ((uint8_t*)vcpu->mem_entry + vcpu->regs[PC] + post_word);	

	printf("value in mem: %o\n", *((uint8_t*)vcpu->mem_entry + vcpu->regs[PC] + post_word));

	return *((uint8_t*)vcpu->mem_entry + vcpu->regs[PC] + post_word);
}
*/

uint16_t get_rel_pc(vcpu_t* vcpu, uint8_t** address)
{
	uint16_t post_word = 0, operand_addr = 0;
	
	post_word = fetch_word_from_mem(vcpu);
//	printf("post word %o\n", post_word);

//	printf("pc: %o\n", vcpu->regs[PC]);

//	*address = ((uint8_t*)vcpu->mem_entry + vcpu->regs[PC] + post_word);	

//	printf("value in mem: %o\n", *((uint8_t*)vcpu->mem_entry + vcpu->regs[PC] + post_word));

//	return *((uint8_t*)vcpu->mem_entry + vcpu->regs[PC] + post_word);
	return (vcpu->regs[PC] + post_word);
}

uint16_t get_rel_def_pc(vcpu_t* vcpu, uint8_t** address)
{
	uint16_t post_word = 0, operand_addr = 0;
	
	post_word = fetch_word_from_mem(vcpu);
	operand_addr = *((uint8_t*)vcpu->mem_entry + vcpu->regs[PC] + post_word);
	*address = ((uint8_t*)vcpu->mem_entry + operand_addr);	

	return *((uint8_t*)vcpu->mem_entry + operand_addr);	
}

uint16_t get_autoinc_sp(vcpu_t* vcpu, uint16_t isa_mode, uint8_t** address)
{
	uint16_t operand = 0;	

	if (isa_mode)
	{
		*address = ((uint8_t*)vcpu->mem_entry + vcpu->regs[SP] - 1);
		operand = *((uint8_t*)vcpu->mem_entry + vcpu->regs[SP] - 1);						// FIXME: Need to check			
	}
	else
	{
		*address = ((uint8_t*)vcpu->mem_entry + vcpu->regs[SP]);
		operand = *(uint16_t*)((uint8_t*)vcpu->mem_entry + vcpu->regs[SP]);		// FIXME: Need to check this line's correctness				
	}

	vcpu->regs[SP] +=2;
	
	return operand;
}

uint16_t get_autodec_sp(vcpu_t* vcpu, uint16_t isa_mode, uint8_t** address)
{
	uint16_t operand = 0;	
	uint16_t reg_val = 0;

	vcpu->regs[SP] -=2;

	if (isa_mode)
	{
		*address = ((uint8_t*)vcpu->mem_entry + vcpu->regs[SP] - 1);
		operand = *((uint8_t*)vcpu->mem_entry + vcpu->regs[SP] - 1);		// FIXME: Need to check this line's correctness
	}
	else
	{
		*address = ((uint8_t*)vcpu->mem_entry + vcpu->regs[SP]);
		operand = *(uint16_t*)((uint8_t*)vcpu->mem_entry + vcpu->regs[SP]);		// FIXME: Need to check this line's correctness		
	}

	return operand;	
}

uint16_t fetch_op_general(vcpu_t* vcpu, uint16_t disp, uint16_t mode, uint16_t isa_mode, uint8_t** addr)  		// FIXME: Need to review this function
{
	uint16_t operand = 0;

	switch (mode)
	{
		case REG_ADDR:
			return get_reg(vcpu, disp, isa_mode);
			
		case REG_DEF_ADDR:
			return get_reg_def(vcpu, disp, isa_mode, addr);

		case AUTOINC_ADDR:
			return get_autoinc(vcpu, disp, isa_mode, addr);

		case AUTOINC_DEF_ADDR:
			return get_autoinc_def(vcpu, disp, isa_mode, addr);

		case AUTODEC_ADDR:
			return get_autodec(vcpu, disp, isa_mode, addr);

		case AUTODEC_DEF_ADDR:
			return get_autodec_def(vcpu, disp, isa_mode, addr);

		case INDEX_ADDR:
//			printf("here 2\n");
			return get_index(vcpu, disp, isa_mode, addr);

		case INDEX_DEF_ADDR:
			return get_index_def(vcpu, disp, isa_mode, addr);
		
		case IMM_PC:
//			printf("here 0\n");
			return get_imm_pc(vcpu);

		case ABS_PC:
			return get_abs_pc(vcpu, addr);

		case REL_PC:
//			printf("relative pc\n");
			return get_rel_pc(vcpu, addr);

		case REL_DEF_PC:
			return get_rel_def_pc(vcpu, addr);		

		case SP_DEF:
			return get_reg_def(vcpu, disp, isa_mode, addr);
		
		case SP_AUTOINC:
			return	get_autoinc_sp(vcpu, isa_mode, addr);

		case SP_AUTOINC_DEF:
			return get_autoinc_def(vcpu, disp, isa_mode, addr);

		case SP_AUTODEC:
			return get_autodec_sp(vcpu, isa_mode, addr);

		case SP_INDEX:
			return get_index(vcpu, disp, isa_mode, addr);

		case SP_INDEX_DEF:
			return get_index_def(vcpu, disp, isa_mode, addr);

		default:
			printf("Operands' fetch failed\n");
			abort();
	}	

	return 0;
}

void writeback_src_ops(vcpu_t* vcpu, uint16_t disp, uint16_t mode, uint16_t isa_mode)
{
	switch (mode)
	{
		case AUTOINC_ADDR:

			if (isa_mode)
				vcpu->regs[disp] += 1;
			else
				vcpu->regs[disp] += 2;				

			break;

		case AUTOINC_DEF_ADDR:
			
			vcpu->regs[disp] += 2;			
			break;

		case AUTODEC_ADDR:
		
			if (isa_mode)
				vcpu->regs[disp] -= 1;
			else
				vcpu->regs[disp] -= 2;				

			break;

		case AUTODEC_DEF_ADDR:
		
			vcpu->regs[disp] -= 2;			
			break;

		default:
			break;
	}
}

void set_reg_op(vcpu_t* vcpu, uint16_t disp, uint16_t val, uint16_t isa_mode)
{
	if (isa_mode)
		((uint8_t*)(vcpu->regs))[disp] = val;
	else
		vcpu->regs[disp] = val;			// FIXME: Is there byte mode ???
}

void set_mem_op(vcpu_t* vcpu, uint8_t* addr, uint16_t* val, uint16_t isa_mode)
{
	if (isa_mode)
		*(uint8_t*)addr = *(uint8_t*)val;
	else
		*(uint16_t*)addr = *(uint16_t*)val;
}

void writeback_dst_ops(vcpu_t* vcpu, uint16_t val, uint16_t disp, uint16_t mode, uint16_t isa_mode, uint8_t* addr)
{
	switch (mode)
	{
		case REG_ADDR:
			set_reg_op(vcpu, disp, val, isa_mode);
			break;

		case REG_DEF_ADDR:
		case AUTOINC_ADDR:
		case AUTOINC_DEF_ADDR:
		case AUTODEC_ADDR:
		case AUTODEC_DEF_ADDR:
		case INDEX_ADDR:
		case INDEX_DEF_ADDR:
		case ABS_PC:
		case REL_PC:
		case REL_DEF_PC:
		case SP_DEF:
		case SP_AUTOINC:
		case SP_AUTOINC_DEF:
		case SP_AUTODEC:
		case SP_INDEX:
		case SP_INDEX_DEF:
			set_mem_op(vcpu, addr, &val, isa_mode);
			break;

		default:
			printf("Operands' fetch failed\n");
			abort();
	}	
}