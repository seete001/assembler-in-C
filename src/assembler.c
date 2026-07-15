#include "../include/assembler.h"
#include "../include/opcode.h"
#include "../include/program.h"

#include <stdlib.h>
#include <stdint.h>


static uint8_t register_number(const char *name)
{
    return name[1] - '0';
}

MachineCode assemble_instruction(Instruction inst)
{
    MachineCode code = {0};
    
    code.bytes[0] = opcode_lookup(inst.opcode);

    code.size = 1;
    
    for(int i = 0; i < inst.operand_count; i++)
    {
        Operand op = inst.operands[i];

        if(op.type == OP_REGISTER)
        {
            code.bytes[code.size] = register_number(op.value);
            code.size++;
        }
        else if(op.type == OP_IMMEDIATE)
        {
            code.bytes[code.size] = atoi(op.value);
            code.size++;
        }

    }
    
    return code;
}

MachineCode assemble_program(Program program)
{
    MachineCode output = {0};

    for(int i = 0; i < program.count; i++)
    {
        MachineCode instruction =
            assemble_instruction(program.instructions[i]);


        for(int j = 0; j < instruction.size; j++)
        {
            output.bytes[output.size] =
                instruction.bytes[j];

            output.size++;
        }
    }

    return output;
}
