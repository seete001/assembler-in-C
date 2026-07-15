#ifndef PROGRAM_H
#define PROGRAM_H


#include "instruction.h"

#define MAX_INSTRUCTIONS 1024 

typedef struct
{
    Instruction instructions[MAX_INSTRUCTIONS];
    int count;

} Program;

#endif
