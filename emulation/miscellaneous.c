#include "emulation.h"
#include "cpu/cpu.h"
#include "decode/decode.h"
#include <stdio.h>
#include <stdlib.h>
#include "emu_helper.h"


exec_status_t halt_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op)
{
	return EXEC_END;
}

// 0001010111000110

// 1000101111 011111 tstb 
// 10000000 11111101

// bpl  10000000 00000000 
// swab 0000000011 000000