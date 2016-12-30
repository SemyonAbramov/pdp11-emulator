#include "cpu.h"
#include <stdio.h>
#include <sys/mman.h>	// for mmap
#include <stdlib.h>	// for abort
#include <decode/decode.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>


uint8_t exec_array[] = 
{
	0b01000000, 0b00011100, 0b00001010, 0b00000000,
	0b10000000, 0b10001100, 0b00000001, 0b00000001, 
	0b01111111, 0b01111111, 0b10010001, 0b10000000,
	0b01111111, 0b01111111, 0b01111111, 0b01111111,
	0b01111111, 0b01111111, 0b01111111, 0b01111111, 
	0b00000011, 0b00000000, 0b01111111, 0b01111111
};

void hex_to_bin(char sym, char* buf)
{
	switch (sym)
	{
		case '0':
			memcpy(buf, "0000", 4);
			break;
		case '1':
			memcpy(buf, "0001", 4);
			break;
		case '2':
			memcpy(buf, "0010", 4);
			break;
		case '3':
			memcpy(buf, "0011", 4);
			break;
		case '4':
			memcpy(buf, "0100", 4);
			break;
		case '5':
			memcpy(buf, "0101", 4);
			break;		
		case '6':
			memcpy(buf, "0110", 4);
			break;		
		case '7':
			memcpy(buf, "0111", 4);
			break;	
		case '8':
			memcpy(buf, "1000", 4);
			break;
		case '9':
			memcpy(buf, "1001", 4);
			break;
		case 'a':
			memcpy(buf, "1010", 4);
			break;		
		case 'b':
			memcpy(buf, "1011", 4);
			break;		
		case 'c':
			memcpy(buf, "1100", 4);
			break;	
		case 'd':
			memcpy(buf, "1101", 4);
			break;
		case 'e':
			memcpy(buf, "1110", 4);
			break;
		case 'f':
			memcpy(buf, "1111", 4);
			break;
		default:
			break;
	}
}


typedef struct storage
{
	uint8_t val;
	union
	{
		uint8_t hi : 4;
		uint8_t lo : 4;
	}
} __attribute__((packed)) storage_t;


int load_from_rom(char* path, void* mem)
{
	int fd = open(path, O_RDONLY);

	if (fd == -1)
	{
		printf("Can not open file\n");
		abort();
	}

	long long size = lseek(fd, 0, SEEK_END);
	printf("size: %lld\n", size);

	void* mapped_area = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);

/*
	storage_t* buf = malloc(sizeof(storage_t) * ((size * 4)/sizeof(uint8_t)));

	char* num = malloc(sizeof(char) * 4);


	int i = 0, j = 0;
	int res = 0;
	int is_hi = 0;
	int k = 0;

	for (i = 0; i < size * 4; i++)
	{
 		res = 0;	

		for (k = 0; k < 2; k ++)	
	 	{
	 		hex_to_bin(((char*)mapped_area)[i * 2 + k], num);
		 		
	 		for (j = 0; j < 4; j++)
	  		{	
	  			res += (num[j] - '0') * ((1 << 4 - j - 1));
	  		}

	 		if (!is_hi)
	 		{	
	 			(buf[i]).hi = res;
				is_hi = 1;
			}
			else
			{	
				(buf[i]).lo = res;
				is_hi = 0;			
			}
		}
	}	

	printf("buf: %x\n", buf[0]);
	printf("buf: %x\n", buf[1]);
	printf("buf: %x\n", buf[2]);
	printf("buf: %x\n", buf[3]);		

	memcpy((uint8_t*)mem + 0x200, buf, size/sizeof(uint8_t));

	printf("mem: %x\n", *(uint8_t*)((uint8_t*)mem + 0x200));
	printf("mem: %x\n", *(uint8_t*)((uint8_t*)mem + 0x201));
	printf("mem: %x\n", *(uint8_t*)((uint8_t*)mem + 0x202));
	printf("mem: %x\n", *(uint8_t*)((uint8_t*)mem + 0x203));
*/


	uint8_t* buf = malloc(sizeof(uint8_t) * (size/sizeof(uint8_t))); 

	int i = 0, j = 0;
	int res = 0;

	for (i = 0; i < size / 8; i++)
	{
 		res = 0;	
 		
 		for (j = 0; j < 8; j++)
  			res += (((uint8_t*)mapped_area)[i * 8 + j] - '0') * ((1 << (8 - j - 1)));

		buf[i] = res;
	}

	
	memcpy((uint8_t*)mem + 0x200, buf, size/sizeof(uint8_t));

	return 0;
}



int read_file(char* path, void* mem)
{

	int size = sizeof(exec_array);

	printf("array size: %d\n", size);

	memcpy(mem, exec_array, size);

	int i = 0;

	for (i = 0; i < size; i++)
	{
		printf("mem: 0x%x\n", ((uint8_t*)mem)[i]);

	}

	return 0;
}

void interrupt_handler(vcpu_t* vcpu)
{
	*(uint16_t*)((uint8_t*)vcpu->mem_entry + vcpu->regs[SP]) = (*(vcpu->psw)).reg_val; 
	vcpu->regs[SP] -= 2;
	*(uint16_t*)((uint8_t*)vcpu->mem_entry + vcpu->regs[SP]) = vcpu->regs[PC];	
	vcpu->regs[SP] -= 2;

	vcpu->regs[PC] = *(uint16_t*)((uint8_t*)vcpu->mem_entry + KB_INTERRUPT_VEC);
	(*(vcpu->psw)).reg_val = *(uint16_t*)((uint8_t*)vcpu->mem_entry + KB_INTERRUPT_VEC + 2);	
}

int vcpu_init(vcpu_t* vcpu, void* mem, char* path_to_rom)
{
	printf("vcpu init\n");	
	vcpu->mem_entry = mem;
	vcpu->regs = (uint16_t*)((uint8_t*)mem + MEM_SPACE_SIZE);

//	vcpu->regs[SP];			// FIXME: Need to deal with it 

	vcpu->regs[PC] = 0x200;

	vcpu->psw = (uint16_t*)((uint8_t*)mem + PS_ADDR);
	vcpu->br_points = (uint8_t*)((uint8_t*)mem + BR_POINT_ADDR);
	vcpu->kb_stat_reg = (uint16_t*)((uint8_t*)mem + KB_STAT_REG);
	vcpu->kb_data_reg = (uint16_t*)((uint8_t*)mem + KB_DATA_REG);

	PS_INIT(vcpu);

	vcpu->stop_flag = 0;
//	vcpu->is_running = 0;
	vcpu->is_running = 1;

	vcpu->step_flag = 0;

	load_from_rom(path_to_rom, vcpu->mem_entry);

	return 0;
}

int vcpu_restore(vcpu_t* vcpu, char* path_to_rom)	// FIXME: Need to check 
{
	memset((uint8_t*)vcpu->regs, 0, sizeof(uint16_t) * 8);
	memset(vcpu->mem_entry, 0, MEM_SPACE_SIZE);
//	memset(vcpu->br_points, 0, )		// TODO: Need to deal with brakpoints issue

	vcpu->regs[PC] = 0x200;

	vcpu->stop_flag = 0;
	vcpu->is_running = 0;
	vcpu->step_flag = 0;

	load_from_rom(path_to_rom, vcpu->mem_entry);	

	return 0;
}


int emu_init(vcpu_t* vcpu, char* path_to_rom)
{
	void* mem_entry = mmap(NULL, ADDR_SPACE_SIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0); 

	if (mem_entry == (void*)-1)
	{
		printf("Mem allocation failed (mmap)\n");
		abort();
	}

	vcpu_init(vcpu, mem_entry, path_to_rom);

	return 0;
}

/*
int vcpu_init(vcpu_t* vcpu, void* mem, char* path_to_rom)
{
	printf("vcpu init\n");	
	vcpu->mem_entry = mem;
	vcpu->regs = (uint16_t*)((uint8_t*)mem + MEM_SPACE_SIZE);

//	vcpu->regs[PC] = 0x0000;

//	vcpu->regs[SP];			// FIXME: Need to deal with it 

	vcpu->regs[PC] = 0x200;

	vcpu->psw = (uint16_t*)((uint8_t*)mem + PS_ADDR);
	vcpu->br_points = (uint8_t*)((uint8_t*)mem + BR_POINT_ADDR);
	vcpu->kb_stat_reg = (uint16_t*)((uint8_t*)mem + KB_STAT_REG);
	vcpu->kb_data_reg = (uint16_t*)((uint8_t*)mem + KB_DATA_REG);

	PS_INIT(vcpu);

	vcpu->stop_flag = 0;
	vcpu->step_flag = 0;

	// FIXME: if to write LOAD_N() here 
	// SEGMENTATION FAULT WILL OCCUR						

//	read_file("rom_file.txt", vcpu->mem_entry);

	load_from_rom(path_to_rom, vcpu->mem_entry);

		

	return 0;
}
*/
/*
int emu_init(vcpu_t* vcpu, char* path_to_rom)
{
	void* mem_entry = mmap(NULL, ADDR_SPACE_SIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0); 

	if (mem_entry == (void*)-1)
	{
		printf("Mem allocation failed (mmap)\n");
		abort();
	}

	vcpu_init(vcpu, mem_entry, path_to_rom);

	return 0;
}
*/


uint16_t fetch_instr(vcpu_t* vcpu)
{
	printf(" ------- \n");

	printf("Instruction fetch \n");
		
	uint16_t op = 0;

	if (GET_KB_STAT_REG(vcpu))
	{
		printf("Keyboard interrupt was caught\n");
		printf("Previous PC: 0x%llx\n", vcpu->regs[PC]);
		interrupt_handler(vcpu);	
		printf("PC switched to: 0x%llx\n", vcpu->regs[PC]);
	}
	else
	{
//		printf("PC: 0x%llx\n", vcpu->regs[PC]);
		printf("PC: %o\n", vcpu->regs[PC]);	
	}

	memcpy(&op, (uint8_t*)(vcpu->mem_entry) + vcpu->regs[PC], sizeof(uint8_t) * 2);
	printf("op: 0x%x\n", op);

	vcpu->regs[PC] += 2;

	return op;
}

void vcpu_print(vcpu_t* vcpu)
{
/*
	printf("REG 0: 0x%x\n", vcpu->regs[REG0]);
	printf("REG 1: 0x%x\n", vcpu->regs[REG1]);
	printf("REG 2: 0x%x\n", vcpu->regs[REG2]);
	printf("REG 3: 0x%x\n", vcpu->regs[REG3]);
	printf("REG 4: 0x%x\n", vcpu->regs[REG4]);
	printf("REG 5: 0x%x\n", vcpu->regs[REG5]);
	printf("REG 6: 0x%x\n", vcpu->regs[SP]);
	printf("REG 7: 0x%x\n", vcpu->regs[PC]);						
*/

	printf("REG 0: %o\n", vcpu->regs[REG0]);
	printf("REG 1: %o\n", vcpu->regs[REG1]);
	printf("REG 2: %o\n", vcpu->regs[REG2]);
	printf("REG 3: %o\n", vcpu->regs[REG3]);
	printf("REG 4: %o\n", vcpu->regs[REG4]);
	printf("REG 5: %o\n", vcpu->regs[REG5]);
	printf("REG 6: %o\n", vcpu->regs[SP]);
	printf("REG 7: %o\n", vcpu->regs[PC]);

	uint8_t n = 0, z = 0, v = 0, c = 0;

	GET_N(vcpu, n);
	GET_Z(vcpu, z);
	GET_V(vcpu, v);
	GET_C(vcpu, c);	

	printf("\nflags: n:%d z:%d v:%d c:%d\n", n, z, v, c);

}

int is_break(vcpu_t* vcpu, uint16_t address)		 // FIXME: Need to check 
{
	int set = address / 8;
	int disp = address % 8;
	uint8_t mask = vcpu->br_points[set];
	
	mask &= (0x01 << (8 - disp));
	mask = (mask >> (8 - disp)); //

	if (mask)
	{	
		printf("Breakpoint was set at address: 0x%x\n", address);
	}

	return mask;
}

exec_status_t cpu_exec(vcpu_t* vcpu)
{
	instr_t op = fetch_instr(vcpu);

	instr_desc_t* instr;
	lookup_table(op, &instr);

	if (instr == NULL)				// FIXME: Need to deal with it properly
		return EXEC_UNDEFINED;

	exec_status_t st = instr->execute(vcpu, instr, op);

	return st;
}






