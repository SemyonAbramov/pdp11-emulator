#ifndef PROCESS_H
#define PROCESS_H

#include "formain.h"

class Process
{
public:
    Process(SharedMem *sharedMem);
    ~Process();

    void run();
    void stopReset();
    void step(); // step enable when process stop

    int numberOfPixel; // 100
    unsigned char *matrix; // vidio memory
    short int *registers; // 8 registers
    short int *flags;
    // TODO: added information about breakepoints
    int numberOfCommand;
    AsmCommand *asmCommand; // >= 8

    void setBreakePoint(int address); // 2 set is delete
    SharedMem getGlobal();
};

#endif // PROCESS_H
