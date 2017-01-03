#ifndef DECODE_H
#define DECODE_H

#include "cpu/cpu.h"

struct instr_desc;


typedef enum decode_status
{
	DECODE_SUCCESS,
	DECODE_UNDEFINED	
} decode_status_t;

typedef decode_status_t (*decode_call_t)(vcpu_t *vcpu, struct instr_desc *instr, instr_t op);
typedef exec_status_t (*emu_call_t)(vcpu_t *vcpu, struct instr_desc *instr, instr_t op);

typedef struct instr_desc
{
	uint16_t mask;
	uint16_t value;
	const char *name;
	emu_call_t execute;
} instr_desc_t;

/* ADDRESSING MODES */

#define REG_ADDR			00
#define REG_DEF_ADDR		01
#define AUTOINC_ADDR		02
#define AUTOINC_DEF_ADDR	03
#define AUTODEC_ADDR		04
#define AUTODEC_DEF_ADDR	05
#define INDEX_ADDR			06
#define INDEX_DEF_ADDR		07

#define IMM_PC				027
#define ABS_PC				037
#define REL_PC				067
#define REL_DEF_PC			077
								
#define SP_DEF				016
#define SP_AUTOINC			026
#define SP_AUTOINC_DEF		036
#define SP_AUTODEC			046
#define SP_INDEX			066
#define SP_INDEX_DEF		076


#define ISA_MODE(op, isa_mode)	\
	do {	\
		isa_mode = (op & 0x8000) >> 15;	\
	} while (0)

#define ADDRESS_MODE_LOW(op, mode) \
	do {	\
		if (op & 0x0007 == 0b111)	\
		{	\
			uint16_t hi = (op & 0x0038) >> 3;	\
			if (hi == 2 || hi == 3 || hi == 6 || hi == 7)	\
				mode = op & 0x003f;	\
			else	\
				mode = hi;	\
			break;	\
		}	\
		if (op & 0x0007 == 0b110)	\
		{	\
			uint16_t hi = (op & 0x0038) >> 3;	\
			if (hi == 1 || hi == 2 || hi == 3 || hi == 4 || hi == 6 || hi == 7)	\
				mode = op & 0x003f;	\
			else	\
				mode = hi;	\
			break;	\
		}	\
		else	\
		{	\
			mode = (op & 0x0038) >> 3;	\
		}	\
	} while (0)

/*
#define ADDRESS_MODE_LOW(op, mode) \
	do {	\
		(((op & 0x0007) == 0b111) || ((op & 0x0007) == 0b110)) ? (mode = op & 0x003f) : (mode = (op & 0x0038) >> 3);	\
	} while (0)
*/

#define ADDRESS_MODE_HIGH(op, mode)	\
	do {	\
		((((op & 0x01C0) >> 6) == 0b111) || (((op & 0x01C0) >> 6) == 0b110)) ? (mode = ((op & 0x0FC0) >> 6)) : (mode = (op & 0x0E00) >> 9);	\
	} while (0)

#define GET_SOURCE(op, src)	\
	do {	\
		src = (op & 0x01C0) >> 6;	\
	} while(0)

#define GET_DST(op, dst)	\
	do {	\
		dst = op & 0x0007;	\
	} while(0)

#define GET_REG(op, src)	\
	do {	\
		src = op & 0x01C0;	\
	} while(0)

#define GET_DST_SRC(op, dst)	\
	do {	\
		dst = op & 0x0007;	\
	} while(0)

#define GET_OFFSET(op, offset)	\
	do {	\
		offset = op & 0x00ff;	\
	} while (0)

#define GET_REG_JSR(op, reg)	\
	do {	\
		reg = (op & 0x01c0) >> 6;	\
	} while (0)

#endif // DECODE_H