#include "cpu_api.h"

#include <stdio.h>
#include <sys/mman.h>	// for mmap
#include <stdlib.h>	// for abort
#include <decode/decode.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


/* TODO: Parallel syncronisation on mutex */


void throw_kb_interrupt(vcpu_t* vcpu, uint8_t data)
{
	SET_KB_DATA_REG(vcpu, data);	

	if (GET_KB_STAT_REG(vcpu))
	{
		printf("Keyboard interrupt is not proc yet\n Need to implement buffer\n");	// FIXME: Need to implement buffer
		abort();
	}

	SET_KB_STAT_REG(vcpu);
}


/*
int cpu_emulation(vcpu_t* vcpu, char* path)
{
	emu_init(vcpu, path);	
	vcpu_print(vcpu);	

	exec_status_t exec_st = EXEC_SUCCESS;
	
	while (1)
	{
		if (is_break(vcpu, vcpu->regs[PC]))
			SET_STOP_FLAG(vcpu);

		if (!vcpu->stop_flag || vcpu->step_flag)
		{
			if (vcpu->stop_flag)			
				RESET_STEP_FLAG(vcpu);	

			exec_st = cpu_exec(vcpu);			
			vcpu_print(vcpu);
			
			if (exec_st == EXEC_UNDEFINED)
				return 1;	
		
			if (exec_st == EXEC_END)
				break;
		}
	}

	return 0;
}
*/



void run_emulator(vcpu_t* vcpu)
{
	if (!(vcpu->is_running))
		vcpu->is_running = 1;
	else
		vcpu->stop_flag = 0;
}

void reset_emulator(vcpu_t* vcpu)
{
	CLEAR_RUN_FLAG(vcpu);
}


/* TODO: Need to solve halt and deinit issue */ 

/*
void halt_emulator(vcpu_t* vcpu)
{

}

void emu_deinit(vcpu_t* vcpu)
{
	
} 

*/

int cpu_emulation(vcpu_t* vcpu, char* path)
{
	emu_init(vcpu, path);	
	vcpu_print(vcpu);

	emulator_initialized = 1;

	while (1)
	{
		if (vcpu->is_running)
		{
			exec_status_t exec_st = EXEC_SUCCESS;
			
			while (1)
			{
				if (!(vcpu->is_running))
					break; 

				if (is_break(vcpu, vcpu->regs[PC]))
					SET_STOP_FLAG(vcpu);

				if (!vcpu->stop_flag || vcpu->step_flag)
				{
					if (vcpu->stop_flag)			
						RESET_STEP_FLAG(vcpu);	

					exec_st = cpu_exec(vcpu);			
					vcpu_print(vcpu);
					
					if (exec_st == EXEC_UNDEFINED)
						break;	
				
					if (exec_st == EXEC_END)
						break;
				}
			}			
			
//			if (!(vcpu->is_running))
//				vcpu_restore(vcpu, path);				

//			if (exec_st == EXEC_END || exec_st == EXEC_UNDEFINED)
//				vcpu_restore(vcpu, path); 

			if (exec_st == EXEC_END || exec_st == EXEC_UNDEFINED)
				break;
		}	
	}

	return 0;
}


void stop_emulator(vcpu_t* vcpu)
{
	vcpu->stop_flag = 1;
}

void step_emulator(vcpu_t* vcpu)
{
	vcpu->step_flag = 1;
}


void set_breakpoint(vcpu_t* vcpu, uint16_t address)		// FIXME: Need to check
{
	int set = address / 8;
	int disp = address % 8;
	vcpu->br_points[set] |= (0x01 << (8 - disp)); 
}

void remove_breakpoint(vcpu_t* vcpu, uint16_t address)
{
	int set = address / 8;
	int disp = address % 8;
	vcpu->br_points[set] &= (0xff ^ (0x1 << (8 - disp)));	
}

uint16_t get_register(vcpu_t* vcpu, uint8_t num)
{
	return GET_CPU_REG(vcpu, num);
}