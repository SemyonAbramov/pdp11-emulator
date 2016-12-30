#include "emulation.h"
#include "cpu/cpu.h"
#include "decode/decode.h"
#include <stdio.h>
#include <stdlib.h>
#include "emu_helper.h"


exec_status_t clr_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op)
{
	uint16_t dst_disp = 0, dst = 0, dst_mode = 0, isa_mode = 0;

	ISA_MODE(op, isa_mode);	
	ADDRESS_MODE_LOW(op, dst_mode);
	GET_DST(op, dst_disp);

	uint8_t* dst_addr;

	fetch_op_general(vcpu, dst_disp, dst_mode, isa_mode, &dst_addr);		

	dst = 0;
	
	writeback_src_ops(vcpu, dst_disp, dst_mode, isa_mode);
	writeback_dst_ops(vcpu, dst, dst_disp, dst_mode, isa_mode, dst_addr);	

	CLEAR_N(vcpu);
	SET_Z(vcpu);
	CLEAR_V(vcpu);
	CLEAR_C(vcpu);

	return EXEC_SUCCESS;
}

exec_status_t com_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op)
{
	uint16_t dst_disp = 0, dst = 0, dst_mode = 0, isa_mode = 0;

	ISA_MODE(op, isa_mode);	
	ADDRESS_MODE_LOW(op, dst_mode);
	GET_DST(op, dst_disp);

	uint8_t* dst_addr;

	dst = fetch_op_general(vcpu, dst_disp, dst_mode, isa_mode, &dst_addr);		

	dst = ~(dst);
	
	writeback_src_ops(vcpu, dst_disp, dst_mode, isa_mode);
	writeback_dst_ops(vcpu, dst, dst_disp, dst_mode, isa_mode, dst_addr);	

	LOAD_N(vcpu, dst & (0x8000 >> (isa_mode * 8)));

	if (dst == 0)
		LOAD_Z(vcpu, 1);
	else
		LOAD_Z(vcpu, 0);

	LOAD_V(vcpu, 0);
	LOAD_C(vcpu, 1);

	return EXEC_SUCCESS;
}

exec_status_t inc_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op)
{
	uint16_t dst_disp = 0, dst = 0, dst_mode = 0, isa_mode = 0;

	ISA_MODE(op, isa_mode);	
	ADDRESS_MODE_LOW(op, dst_mode);
	GET_DST(op, dst_disp);

	uint8_t* dst_addr;

	dst = fetch_op_general(vcpu, dst_disp, dst_mode, isa_mode, &dst_addr);	

	dst = dst + 1;

	writeback_src_ops(vcpu, dst_disp, dst_mode, isa_mode);
	writeback_dst_ops(vcpu, dst, dst_disp, dst_mode, isa_mode, dst_addr);

	LOAD_N(vcpu, dst & (0x8000 >> (isa_mode * 8)));

	if (dst == 0)
		LOAD_Z(vcpu, 1);
	else
		LOAD_Z(vcpu, 0);	

	if (dst == 0x7FFF)		// 077777 in octal
		LOAD_V(vcpu, 1);
	else
		LOAD_V(vcpu, 0);

	return EXEC_SUCCESS;
}

exec_status_t dec_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op)
{
	uint16_t dst_disp = 0, dst = 0, dst_mode = 0, isa_mode = 0, src_dst = 0;

	ISA_MODE(op, isa_mode);	
	ADDRESS_MODE_LOW(op, dst_mode);
	GET_DST(op, dst_disp);

	uint8_t* dst_addr;

	dst = fetch_op_general(vcpu, dst_disp, dst_mode, isa_mode, &dst_addr);	
	src_dst = dst;

	dst = dst - 1;

	writeback_src_ops(vcpu, dst_disp, dst_mode, isa_mode);
	writeback_dst_ops(vcpu, dst, dst_disp, dst_mode, isa_mode, dst_addr);

	LOAD_N(vcpu, dst & (0x8000 >> (isa_mode * 8)));

	if (dst == 0)
		LOAD_Z(vcpu, 1);
	else
		LOAD_Z(vcpu, 0);	

	if (src_dst == 0x8000)		// 100000 in octal
		LOAD_V(vcpu, 1);
	else
		LOAD_V(vcpu, 0);

	return EXEC_SUCCESS;
}

exec_status_t neg_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op)
{
	uint16_t dst_disp = 0, dst = 0, dst_mode = 0, isa_mode = 0;

	ISA_MODE(op, isa_mode);	
	ADDRESS_MODE_LOW(op, dst_mode);
	GET_DST(op, dst_disp);

	uint8_t* dst_addr;

	dst = fetch_op_general(vcpu, dst_disp, dst_mode, isa_mode, &dst_addr);	

	dst = -dst;

	writeback_src_ops(vcpu, dst_disp, dst_mode, isa_mode);
	writeback_dst_ops(vcpu, dst, dst_disp, dst_mode, isa_mode, dst_addr);

	LOAD_N(vcpu, dst & (0x8000 >> (isa_mode * 8)));

	if (dst == 0)
	{	
		LOAD_Z(vcpu, 1);
		LOAD_C(vcpu, 0);	
	}
	else
	{	
		LOAD_Z(vcpu, 0);	
		LOAD_C(vcpu, 1);
	}

	if (dst == 0x8000)		// 100000 in octal
		LOAD_V(vcpu, 1);
	else
		LOAD_V(vcpu, 0);

	return EXEC_SUCCESS;
}


exec_status_t tst_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op)
{
	uint16_t dst_disp = 0, dst = 0, dst_mode = 0, isa_mode = 0;

	ISA_MODE(op, isa_mode);	
	ADDRESS_MODE_LOW(op, dst_mode);
	GET_DST(op, dst_disp);

	printf("dst mode: %d\n", dst_mode);

	printf("dst disp: %d\n", dst_disp);

	uint8_t* dst_addr;

	dst = fetch_op_general(vcpu, dst_disp, dst_mode, isa_mode, &dst_addr);	

//	dst = dst;

//	writeback_src_ops(vcpu, dst_disp, dst_mode, isa_mode);

//	writeback_dst_ops(vcpu, dst, dst_disp, dst_mode, isa_mode, dst_addr);

	printf("here 2\n");
	LOAD_N(vcpu, dst & (0x8000 >> (isa_mode * 8)));

	if (dst == 0)	
		LOAD_Z(vcpu, 1);
	else
		LOAD_Z(vcpu, 0);	
	
	LOAD_V(vcpu, 0);
	LOAD_C(vcpu, 0);

	return EXEC_SUCCESS;
}

exec_status_t asr_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op)
{
	uint16_t dst_disp = 0, dst_mode = 0, isa_mode = 0;
	int16_t dst = 0;

	ISA_MODE(op, isa_mode);	
	ADDRESS_MODE_LOW(op, dst_mode);
	GET_DST(op, dst_disp);

	uint8_t* dst_addr;

	dst = fetch_op_general(vcpu, dst_disp, dst_mode, isa_mode, &dst_addr);

	uint16_t high_bit = 0;
	uint16_t low_bit = 0;	

	high_bit = dst & (0x8000 >> (isa_mode * 8));
	low_bit = (dst & 0x0001);	
	dst = (dst >> 1) | high_bit;
	high_bit = high_bit >> (15 - (8 * isa_mode));
	
	writeback_src_ops(vcpu, dst_disp, dst_mode, isa_mode);
	writeback_dst_ops(vcpu, dst, dst_disp, dst_mode, isa_mode, dst_addr);	

	LOAD_N(vcpu, high_bit);

	if (dst == 0)
		LOAD_Z(vcpu, 1);
	else
		LOAD_Z(vcpu, 0);

	LOAD_V(vcpu, high_bit ^ low_bit);
	LOAD_C(vcpu, low_bit);

	return EXEC_SUCCESS;
}

exec_status_t asl_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op)
{
	uint16_t dst_disp = 0, dst = 0, dst_mode = 0, isa_mode = 0;

	ISA_MODE(op, isa_mode);	
	ADDRESS_MODE_LOW(op, dst_mode);
	GET_DST(op, dst_disp);

	uint8_t* dst_addr;

	dst = fetch_op_general(vcpu, dst_disp, dst_mode, isa_mode, &dst_addr);

	uint16_t high_bit = 0;
	uint16_t neg_bit = 0;

	high_bit = dst & (0x8000 >> (8 * isa_mode));
	dst = dst << 1;
	neg_bit = (dst & (0x8000 >> (8 * isa_mode))) >> (15 - (8 * isa_mode));

	writeback_src_ops(vcpu, dst_disp, dst_mode, isa_mode);
	writeback_dst_ops(vcpu, dst, dst_disp, dst_mode, isa_mode, dst_addr);

	LOAD_N(vcpu, neg_bit);

	if (dst == 0)
		LOAD_Z(vcpu, 1);
	else
		LOAD_Z(vcpu, 0);

	LOAD_V(vcpu, neg_bit ^ high_bit);
	LOAD_C(vcpu, high_bit);

	return EXEC_SUCCESS;
}


exec_status_t ror_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op)
{
	uint16_t dst_disp = 0, dst = 0, dst_mode = 0, isa_mode = 0;

	ISA_MODE(op, isa_mode);	
	ADDRESS_MODE_LOW(op, dst_mode);
	GET_DST(op, dst_disp);

	uint8_t* dst_addr;

	dst = fetch_op_general(vcpu, dst_disp, dst_mode, isa_mode, &dst_addr);	

	uint16_t prev_bit_c = 0, low_bit = 0;;

	GET_C(vcpu, prev_bit_c);
	low_bit = dst & 0x0001;

	dst = dst >> 1;
	
	dst = dst | (prev_bit_c << (15 - (8 * isa_mode)));

	writeback_src_ops(vcpu, dst_disp, dst_mode, isa_mode);
	writeback_dst_ops(vcpu, dst, dst_disp, dst_mode, isa_mode, dst_addr);

	LOAD_N(vcpu, prev_bit_c);

	if (dst == 0)
		LOAD_Z(vcpu, 1);
	else
		LOAD_Z(vcpu, 0);

	LOAD_V(vcpu, prev_bit_c ^ low_bit);
	LOAD_C(vcpu, low_bit);	

	return EXEC_SUCCESS;
}


exec_status_t rol_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op)
{
	uint16_t dst_disp = 0, dst_mode = 0, isa_mode = 0;
	int16_t dst = 0;

	ISA_MODE(op, isa_mode);	
	ADDRESS_MODE_LOW(op, dst_mode);
	GET_DST(op, dst_disp);

	uint8_t* dst_addr;

	dst = fetch_op_general(vcpu, dst_disp, dst_mode, isa_mode, &dst_addr);	

	uint16_t prev_bit_c = 0, high_bit = 0;

	GET_C(vcpu, prev_bit_c);
	
	high_bit = dst & (0x8000 >> (8 * isa_mode));

	dst = dst << 1;
	dst = dst | prev_bit_c;

	uint16_t neg_bit = 0;
	neg_bit = dst & (0x8000 >> (8 * isa_mode)); 

	writeback_src_ops(vcpu, dst_disp, dst_mode, isa_mode);
	writeback_dst_ops(vcpu, dst, dst_disp, dst_mode, isa_mode, dst_addr);

	LOAD_N(vcpu, neg_bit);	

	if (dst == 0)
		LOAD_Z(vcpu, 1);
	else
		LOAD_Z(vcpu, 0);

	LOAD_V(vcpu, neg_bit ^ high_bit);
	LOAD_C(vcpu, high_bit);

	return EXEC_SUCCESS;
}


exec_status_t swab_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op)
{
	uint16_t dst_disp = 0, dst_mode = 0, isa_mode = 0;
	int16_t dst = 0;

	ISA_MODE(op, isa_mode);	
	ADDRESS_MODE_LOW(op, dst_mode);
	GET_DST(op, dst_disp);

	uint8_t* dst_addr;

	dst = fetch_op_general(vcpu, dst_disp, dst_mode, isa_mode, &dst_addr);	

	uint8_t low_byte = dst; 
	uint8_t high_byte = dst >> 8;
	uint16_t res = 0;

	dst = low_byte;
	dst = (dst << 8) | high_byte;	
	
	writeback_src_ops(vcpu, dst_disp, dst_mode, isa_mode);
	writeback_dst_ops(vcpu, dst, dst_disp, dst_mode, isa_mode, dst_addr);


	LOAD_N(vcpu, (dst & 0x0080) >> 7);

	if ((dst & 0x00ff) == 0)
		LOAD_Z(vcpu, 1);
	else
		LOAD_Z(vcpu, 0);

	LOAD_V(vcpu, 0);
	LOAD_C(vcpu, 0);

	return EXEC_SUCCESS;
}



