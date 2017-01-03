#include "emulation.h"
#include "cpu/cpu.h"
#include "decode/decode.h"
#include <stdio.h>
#include <stdlib.h>
#include "emu_helper.h"


/*
	printf("dst mode: %o\n", dst_mode);
	printf("src mode: %o\n", src_mode);

	printf("dst disp: %d\n", dst_disp);
	printf("src disp: %d\n", src_disp);
*/

/*
exec_status_t mov_exec(vcpu_t* vcpu, uint16_t src, uint16_t dst_disp, uint16_t dst_mode, uint8_t* dst_addr, instr_mode_t mode)
{
	uint16_t dst = src;

	writeback_dst_ops(vcpu, dst, dst_disp, dst_mode, mode, dst_addr);

	LOAD_N(vcpu, (src & (0x8000 >> (mode * 8))) >> (15 - 8 * mode));

	if (src == 0)	
		LOAD_Z(vcpu, 1);
	else
		LOAD_Z(vcpu, 0);

	CLEAR_V(vcpu);	

	return EXEC_SUCCESS;
}
*/


exec_status_t mov_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode)
{
	uint16_t dst_disp = 0, src_disp = 0;
	uint16_t dst = 0, src = 0;
	uint16_t dst_mode = 0, src_mode = 0;	

	ADDRESS_MODE_LOW(op, dst_mode);
	ADDRESS_MODE_HIGH(op, src_mode);

	GET_SOURCE(op, src_disp);
	GET_DST(op, dst_disp);

	printf("dst mode: %o\n", dst_mode);
	printf("src mode: %o\n", src_mode);

	printf("dst disp: %d\n", dst_disp);
	printf("src disp: %d\n", src_disp);
	printf("mode: %o\n", mode);


	uint8_t* src_addr;
	src = fetch_op_general(vcpu, src_disp, src_mode, mode, &src_addr);

	uint8_t* dst_addr;
	fetch_op_general(vcpu, dst_disp, dst_mode, mode, &dst_addr);

	dst = src;

	writeback_dst_ops(vcpu, dst, dst_disp, dst_mode, mode, dst_addr);

	LOAD_N(vcpu, (src & (0x8000 >> (mode * 8))) >> (15 - 8 * mode));

	if (src == 0)	
		LOAD_Z(vcpu, 1);
	else
		LOAD_Z(vcpu, 0);

	CLEAR_V(vcpu);	

	return EXEC_SUCCESS;

}

exec_status_t add_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode)
{
	uint16_t dst_disp = 0, src_disp = 0;
	uint16_t dst = 0, src = 0, src_dst = 0;
	uint16_t dst_mode = 0, src_mode = 0;	
	
	ADDRESS_MODE_LOW(op, dst_mode);
	ADDRESS_MODE_HIGH(op, src_mode);

	GET_SOURCE(op, src_disp);
	GET_DST(op, dst_disp);

	uint8_t* src_addr;
	uint8_t* dst_addr;

	src = fetch_op_general(vcpu, src_disp, src_mode, mode, &src_addr);
	dst = fetch_op_general(vcpu, dst_disp, dst_mode, mode, &dst_addr);		

	src_dst = dst;

	dst = dst + src;
	
	writeback_dst_ops(vcpu, dst, dst_disp, dst_mode, mode, dst_addr);	

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

exec_status_t sub_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode)
{
	uint16_t dst_disp = 0, src_disp = 0;
	uint16_t dst = 0, src = 0, src_dst = 0;
	uint16_t dst_mode = 0, src_mode = 0;	

	ADDRESS_MODE_LOW(op, dst_mode);
	ADDRESS_MODE_HIGH(op, src_mode);

	GET_SOURCE(op, src_disp);
	GET_DST(op, dst_disp);

	uint8_t* src_addr;
	uint8_t* dst_addr;

	src = fetch_op_general(vcpu, src_disp, src_mode, mode, &src_addr);
	dst = fetch_op_general(vcpu, dst_disp, dst_mode, mode, &dst_addr);	

	src_dst = dst;

	dst = dst + (~(src)) + 1;

	writeback_dst_ops(vcpu, dst, dst_disp, dst_mode, mode, dst_addr);
	
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


