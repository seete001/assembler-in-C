#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "instruction.h"
#include "program.h"

#include <stdint.h>

#define MAX_BYTES 256

typedef struct
{
    uint8_t bytes[MAX_BYTES];

    int size;

} MachineCode;

MachineCode assemble_instruction(Instruction inst);

MachineCode assemble_program(Program program);

#endif
