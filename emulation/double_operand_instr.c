#include "emulation.h"
#include "cpu/cpu.h"
#include "decode/decode.h"
#include <stdio.h>
#include <stdlib.h>
#include "emu_helper.h"


exec_status_t mov_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op)
{
	/* decoding */

	uint16_t dst_disp = 0, src_disp = 0;
	uint16_t dst = 0, src = 0;
	uint16_t dst_mode = 0, src_mode = 0;	
	uint16_t opcode = 0, isa_mode = 0;

	ISA_MODE(op, isa_mode);

	ADDRESS_MODE_LOW(op, dst_mode);
	ADDRESS_MODE_HIGH(op, src_mode);

	GET_SOURCE(op, src_disp);
	GET_DST(op, dst_disp);

	printf("dst mode: %d\n", dst_mode);
	printf("src mode: %d\n", src_mode);

	printf("dst disp: %d\n", dst_disp);
	printf("src disp: %d\n", src_disp);

	/* fetch operands */
	
	uint8_t* src_addr;
/*
	printf("src addr ** %p\n", src_addr);
	printf("src addr * %p\n", *src_addr);
*/
	src = fetch_op_general(vcpu, src_disp, src_mode, isa_mode, &src_addr);

	uint8_t* dst_addr;
//	printf("dst addr ** %p\n", dst_addr);
//	printf("dst addr * %p\n", *dst_addr);

//	printf("dst addr")

	fetch_op_general(vcpu, dst_disp, dst_mode, isa_mode, &dst_addr);

	printf("src: %d\n", src);

	/* execute */

	dst = src;

	/* writeback (not implemented yet) */

	writeback_src_ops(vcpu, src_disp, src_mode, isa_mode);	
	writeback_src_ops(vcpu, dst_disp, dst_mode, isa_mode);
	writeback_dst_ops(vcpu, dst, dst_disp, dst_mode, isa_mode, dst_addr);

	if (src < 0)
		SET_N(vcpu);

	if (src == 0)
		SET_Z(vcpu);

	CLEAR_V(vcpu);

	return EXEC_SUCCESS;
}


exec_status_t add_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op)
{
	/* decoding */

	uint16_t dst_disp = 0, src_disp = 0;
	uint16_t dst = 0, src = 0, src_dst = 0;
	uint16_t dst_mode = 0, src_mode = 0;	
	uint16_t opcode = 0, isa_mode = 0;	

	ADDRESS_MODE_LOW(op, dst_mode);
	ADDRESS_MODE_HIGH(op, src_mode);

	GET_SOURCE(op, src_disp);
	GET_DST(op, dst_disp);

	printf("dst mode: %d\n", dst_mode);
	printf("src mode: %d\n", src_mode);

	printf("dst disp: %d\n", dst_disp);
	printf("src disp: %d\n", src_disp);

	/* fetch operands */
	
	uint8_t* src_addr;
	uint8_t* dst_addr;

	src = fetch_op_general(vcpu, src_disp, src_mode, isa_mode, &src_addr);
	dst = fetch_op_general(vcpu, dst_disp, dst_mode, isa_mode, &dst_addr);		

	src_dst = dst;

	printf("src: %d\n", src);
	printf("dst: %d\n", dst);

	/* execution */

	dst = dst + src;

	/* writeback */

	writeback_src_ops(vcpu, src_disp, src_mode, isa_mode);	
	writeback_src_ops(vcpu, dst_disp, dst_mode, isa_mode);
	writeback_dst_ops(vcpu, dst, dst_disp, dst_mode, isa_mode, dst_addr);	

	if (dst < 0)
		SET_N(vcpu);
	else
		CLEAR_N(vcpu);

	if (dst == 0)
		SET_Z(vcpu);
	else
		CLEAR_Z(vcpu);

	if ((src_dst * src >= 0 && dst < 0) || (src_dst * src > 0 && dst <= 0))
		SET_V(vcpu);
	else
		CLEAR_V(vcpu);

	/* Need to handle carry issue */

	return EXEC_SUCCESS;
}

exec_status_t sub_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op)
{
	uint16_t dst_disp = 0, src_disp = 0;
	uint16_t dst = 0, src = 0, src_dst = 0;
	uint16_t dst_mode = 0, src_mode = 0;	
	uint16_t opcode = 0, isa_mode = 0;	

	ADDRESS_MODE_LOW(op, dst_mode);
	ADDRESS_MODE_HIGH(op, src_mode);

	GET_SOURCE(op, src_disp);
	GET_DST(op, dst_disp);

	printf("dst mode: %d\n", dst_mode);
	printf("src mode: %d\n", src_mode);

	printf("dst disp: %d\n", dst_disp);
	printf("src disp: %d\n", src_disp);

	/* fetch operands */
	
	uint8_t* src_addr;
	uint8_t* dst_addr;

	src = fetch_op_general(vcpu, src_disp, src_mode, isa_mode, &src_addr);
	dst = fetch_op_general(vcpu, dst_disp, dst_mode, isa_mode, &dst_addr);	

	src_dst = dst;

	/* execution */

	dst = dst + (~(src)) + 1;

	/* writeback */

	writeback_src_ops(vcpu, src_disp, src_mode, isa_mode);	
	writeback_src_ops(vcpu, dst_disp, dst_mode, isa_mode);
	writeback_dst_ops(vcpu, dst, dst_disp, dst_mode, isa_mode, dst_addr);
	
	if (dst < 0)
		SET_N(vcpu);
	else
		CLEAR_N(vcpu);	

	if (dst == 0)
		SET_Z(vcpu);
	else
		CLEAR_Z(vcpu);

	if ((src_dst * src <= 0) && (src * dst >= 0))
		SET_V(vcpu);
	else
		CLEAR_V(vcpu);

	/* Carry flag handle */

	return EXEC_SUCCESS;
}


