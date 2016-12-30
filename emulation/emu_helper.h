#ifndef EMU_HELPER
#define EMU_HELPER

#include "cpu/cpu.h"
#include "decode/decode.h"
#include "stdint.h"

uint16_t fetch_word_from_mem(vcpu_t* vcpu);
uint16_t get_reg_op(vcpu_t* vcpu, uint16_t disp, uint16_t isa_mode);
uint16_t get_reg_def_op(vcpu_t* vcpu, uint16_t disp, uint16_t isa_mode, uint8_t** address);
uint16_t get_autoinc_op(vcpu_t* vcpu, uint16_t disp, uint16_t isa_mode, uint8_t** address);
uint16_t get_autodec_op(vcpu_t* vcpu, uint16_t disp, uint16_t isa_mode, uint8_t** address);
uint16_t get_autoinc_def_op(vcpu_t* vcpu, uint16_t disp, uint16_t isa_mode, uint8_t** address);
uint16_t get_autodec_def_op(vcpu_t* vcpu, uint16_t disp, uint16_t isa_mode, uint8_t** address);
uint16_t get_index_op(vcpu_t* vcpu, uint16_t disp, uint16_t isa_mode, uint8_t** address);
uint16_t get_index_def_op(vcpu_t* vcpu, uint16_t disp, uint16_t isa_mode, uint8_t** address);
uint16_t fetch_op_general(vcpu_t* vcpu, uint16_t disp, uint16_t mode, uint16_t isa_mode, uint8_t** addr);
void writeback_src_ops(vcpu_t* vcpu, uint16_t disp, uint16_t mode, uint16_t isa_mode);
void set_reg_op(vcpu_t* vcpu, uint16_t disp, uint16_t val);
void set_mem_op(vcpu_t* vcpu, uint8_t* addr, uint16_t* val, uint16_t isa_mode);
void writeback_dst_ops(vcpu_t* vcpu, uint16_t val, uint16_t disp, uint16_t mode, uint16_t isa_mode, uint8_t* addr);



#endif // EMU_HELPER