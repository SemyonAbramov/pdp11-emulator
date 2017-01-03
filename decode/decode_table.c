#include "decode.h"
#include "cpu/cpu.h"
#include <stdlib.h>
#include "emulation/emulation.h"

/*
typedef struct instr_desc
{
	uint16_t mask;
	uint16_t value;
	const char *name;
	emu_call_t execute;
} instr_desc_t;
*/

// 0 111111111 000000
// 0 000101000 000000				

instr_desc_t instr_table[] = 
{
	{0x7000, 0x1000, "mov", mov_emu},
	{0xf000, 0x6000, "add", add_emu},	
	{0xf000, 0xe000, "sub", sub_emu},
	{0x7fc0, 0x0a00, "clr", clr_emu},
	{0x7FC0, 0x0A40, "com", com_emu},
	{0x7FC0, 0x0A80, "inc", inc_emu},
	{0x7FC0, 0x0AC0, "dec", dec_emu},
	{0x7FC0, 0x0B00, "neg", neg_emu},
	{0x7FC0, 0x0BC0, "tst", tst_emu},
	{0x7FC0, 0x0C80, "asr", asr_emu},
	{0x7FC0, 0x0CC0, "asl", asl_emu},
	{0x7FC0, 0x0C00, "ror", ror_emu},
	{0x7FC0, 0x0C40, "rol", rol_emu},
	{0xffc0, 0x00C0, "swab", swab_emu},
	{0xff00, 0x0100, "br", br_emu},
	{0xff00, 0x0200, "bne", bne_emu},
	{0xff00, 0x0300, "beq", beq_emu},
	{0xff00, 0x8000, "bpl", bpl_emu},
	{0xff00, 0x8100, "bmi", bmi_emu},
	{0xff00, 0x8400, "bvc", bvc_emu},
	{0xff00, 0x8500, "bvs", bvs_emu},
	{0xff00, 0x8600, "bcc", bcc_emu},
	{0xff00, 0x8700, "bcs", bcs_emu},
	{0xff00, 0x0400, "bge", bge_emu},
	{0xff00, 0x0500, "blt", blt_emu},
	{0xff00, 0x0600, "bgt", bgt_emu},
	{0xff00, 0x0700, "ble", ble_emu},
	{0xff00, 0x8200, "bhi", bhi_emu},
	{0xff00, 0x8300, "blos", blos_emu},
	{0xff00, 0x8600, "bhis", bhis_emu},
	{0xff00, 0x8700, "blo", blo_emu},
	{0x7FC0, 0x0040, "jmp", jmp_emu},
	{0xffff, 0x0002, "rti", rti_emu},
	{0xfe00, 0x0800, "jsr", jsr_emu},
	{0xfff8, 0x0080, "rts", rts_emu},
	{0xffff, 0x0000, "halt", halt_emu},
	{0x0, 0x0, NULL, NULL}
};


//br   0000000100000000    
//mask 1111111100000000