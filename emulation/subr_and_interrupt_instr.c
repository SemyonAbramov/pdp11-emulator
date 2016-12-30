#include "emulation.h"
#include "cpu/cpu.h"
#include "decode/decode.h"
#include <stdio.h>
#include <stdlib.h>
#include "emu_helper.h"



exec_status_t rti_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op)	
{
	uint16_t sp = 0;
	uint8_t* sp_addr;

	sp = fetch_op_general(vcpu, 0b110, AUTOINC_ADDR, 0, &sp_addr);	// FIXME: Need to implement separate function 
	SET_PC(vcpu, sp);												// special for this calback to fetch in same time pc and psw 
	writeback_src_ops(vcpu, 0b110, AUTOINC_ADDR, 0);				// from the stack because now pipelining for this insruction 
																	// is not possible
	sp = fetch_op_general(vcpu, 0b110, AUTOINC_ADDR, 0, &sp_addr);
	SET_PSW(vcpu, sp);		
	writeback_src_ops(vcpu, 0b110, AUTOINC_ADDR, 0);

	return EXEC_SUCCESS;
}

exec_status_t jsr_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op)	
{
	uint16_t sp = 0;
	uint8_t* sp_addr;

		

	sp = fetch_op_general(vcpu, 0b110, AUTOINC_ADDR, 0, &sp_addr);	// FIXME: Need to implement separate function 
	SET_PC(vcpu, sp);												// special for this calback to fetch in same time pc and psw 
	writeback_src_ops(vcpu, 0b110, AUTOINC_ADDR, 0);				// from the stack because now pipelining for this insruction 
																	// is not possible
	sp = fetch_op_general(vcpu, 0b110, AUTOINC_ADDR, 0, &sp_addr);
	SET_PSW(vcpu, sp);		
	writeback_src_ops(vcpu, 0b110, AUTOINC_ADDR, 0);

	return EXEC_SUCCESS;
}