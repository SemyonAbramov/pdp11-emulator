#ifndef EMULATION_H
#define EMULATION_H

#include "decode/decode.h"
#include "cpu/cpu.h"

/* double operand */

exec_status_t mov_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
exec_status_t movb_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);

exec_status_t add_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
exec_status_t sub_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);


/* single operand */

exec_status_t clr_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
exec_status_t com_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
exec_status_t inc_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
exec_status_t dec_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
exec_status_t neg_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
exec_status_t tst_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
exec_status_t asr_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
exec_status_t asl_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
exec_status_t ror_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
exec_status_t rol_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
exec_status_t swab_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);


/* branches */

exec_status_t br_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
exec_status_t bne_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
exec_status_t beq_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
exec_status_t bpl_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
exec_status_t bmi_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
exec_status_t bvc_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
exec_status_t bvs_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
exec_status_t bcc_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
exec_status_t bcs_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
exec_status_t bge_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
exec_status_t blt_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
exec_status_t bgt_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
exec_status_t ble_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
exec_status_t bhi_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
exec_status_t blos_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
exec_status_t bhis_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
exec_status_t blo_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
exec_status_t jmp_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);


/* subroutine and instr_mode_terrupts */

exec_status_t rti_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
exec_status_t jsr_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);
exec_status_t rts_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);

/* miscellaneous */

exec_status_t halt_emu(vcpu_t* vcpu, struct instr_desc *instr, instr_t op, instr_mode_t mode);

#endif //EMULATION_H