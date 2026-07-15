#ifndef INSTRUCTION_H
#define INSTRUCTION_H

typedef enum 
{
    OP_REGISTER,
    OP_IMMEDIATE,
    OP_LABEL,
    OP_MEMORY,

} OperandType;

typedef struct
{
    OperandType type;
    char *value;

} Operand;

typedef struct
{
    char *opcode;
    Operand operands[2];
    int operand_count;

} Instruction ;

#endif
