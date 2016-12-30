#include <stdio.h>
#include "cpu/cpu.h"
#include <stdlib.h>	// for malloc
#include <string.h>

/* TODO:
	Implement sp addressing
	Check byte operations
*/

int main(int argc, char** argv)
{
	cpu_emulation(&vcpu, argv[1]);	

	return 0;
}