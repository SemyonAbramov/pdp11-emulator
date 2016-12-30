#include "process.h"
#include <malloc.h>
#include <string.h>


Process::Process(SharedMem *sharedMem) {
    numberOfPixel = 100;
    matrix = (unsigned char *)calloc(sizeof(unsigned char), numberOfPixel*numberOfPixel);
    if (!matrix) {
        printf("error with alloc memory\n");
        return;
    }

    int size_string = 100;
    numberOfCommand = 8;
    asmCommand = (AsmCommand *)malloc(sizeof(AsmCommand) * numberOfCommand);
    if (!asmCommand) {
        printf("error with alloc memory\n");
        return;
    }
    for (int i = 0; i < numberOfCommand; i++) {
        asmCommand[i].command = (char *)malloc(sizeof(char) * size_string);
        if (!asmCommand[i].command) {
            printf("error with alloc memory\n");
            return;
        }
    }

    strcpy(asmCommand[0].command, "HELLO: MOV    #MSG,R1");
    strcpy(asmCommand[1].command, "1$:    MOVB   (R1)+,R0");
    strcpy(asmCommand[2].command, "       BEQ    DONE");
    strcpy(asmCommand[3].command, "       .TTYOUT");
    strcpy(asmCommand[4].command, "       BR     1$");
    strcpy(asmCommand[5].command, "DONE:  .EXIT");
    strcpy(asmCommand[6].command, "MSG:   .ASCIZ /Hello, world!/");
    strcpy(asmCommand[7].command, "       .END    HELLO");

    for (int i = 0; i < numberOfCommand; i++)
        asmCommand[i].address = i+100;

    registers = (short int *)malloc(sizeof(short int) * 8);
    if (!registers) {
        printf("error with alloc memory\n");
        return;
    }
    for (int i = 0; i < 8; i++)
        registers[i] = i+14;

    flags = (short int *)malloc(sizeof(short int));
    if (!flags) {
        printf("error with alloc memory\n");
        return;
    }
    *flags = 129;
    sharedMem->asmCommand = asmCommand;
    sharedMem->flags = flags;
    sharedMem->vidio_memory = matrix;
    sharedMem->registers = registers;
    sharedMem->isFull = 1;

    printf("sharedMem in process = %p\n vidio_mem = %p\t asmCommand = %p\n",
           sharedMem, sharedMem->vidio_memory, sharedMem->asmCommand);
    for (int i = 0; i < numberOfCommand; i++)
        printf("command[%d] = \"%s\"\n", i, sharedMem->asmCommand[i].command);
}

Process::~Process() {
/*
    free(matrix);

    for (int i = 0; i < numberOfCommand; i++)
        free(asmCommand[i].command);
    free(asmCommand);
    free(registers);
    free(flags);
*/
}

void Process::run() {
    unsigned char c = 0;
    for (int x = 0; x < numberOfPixel; x++)
    for (int y = 0; y < numberOfPixel; y++) {
        matrix[x*numberOfPixel + y] = c++;
    }

}

void Process::stopReset() {
    for (int x = 0; x < numberOfPixel; x++)
    for (int y = 0; y < numberOfPixel; y++) {
        matrix[x*numberOfPixel + y] = 0;
    }
}


void Process::step() {

}
