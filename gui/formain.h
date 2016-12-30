#ifndef FORMAIN_H
#define FORMAIN_H

#include <QApplication>
#include <pthread.h>
#include <errno.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

typedef struct AsmCommand {
    char *command; // or char[*magic*]
    int address;
    int breakePointIsSet;
} AsmCommand;

typedef struct SharedMem {
    int isFull;
    unsigned char *vidio_memory;
    short int *registers; // 8 registers
    short int *flags;
    AsmCommand *asmCommand;
} SharedMem;

typedef struct Arg {
    int argc;
    char **argv;
    SharedMem *sharedMem;
    pthread_mutex_t *mutex;
} Arg;

#endif // FORMAIN_H
