#ifndef CPU_API_H
#define CPU_API_H

#include "cpu.h"

#ifdef __cplusplus
	extern "C" {
#endif

	int emulator_initialized;

	void throw_kb_interrupt(vcpu_t* vcpu, uint8_t data);
	int cpu_emulation(vcpu_t* vcpu, char* path);
	void stop_emulator(vcpu_t* vcpu);
	void step_emulator(vcpu_t* vcpu);
	void run_emulator(vcpu_t* vcpu);
	void reset_emulator(vcpu_t* vcpu);
	void set_breakpoint(vcpu_t* vcpu, uint16_t address);
	void remove_breakpoint(vcpu_t* vcpu, uint16_t address);
	uint16_t get_register(vcpu_t* vcpu, uint8_t num);
	
#ifdef __cplusplus
}
#endif




#endif // CPU_API_H