#include "../include/parser.h"

#include <stdio.h>

int main(void)
{
    const char *source =
        "MOV r1, r2\n"
        "ADD r3, 5\n"
        "JMP loop\n";

    Parser parser = parser_init(source);

    Program program = parser_program(&parser);

    printf("Instructions: %d\n\n", program.count);

    for (int i = 0; i < program.count; i++)
    {
        Instruction inst = program.instructions[i];

        printf("Instruction %d\n", i + 1);
        printf("Opcode: %s\n", inst.opcode);

        for (int j = 0; j < inst.operand_count; j++)
        {
            printf("Operand %d: %s (", j + 1, inst.operands[j].value);

            switch (inst.operands[j].type)
            {
                case OP_REGISTER:
                    printf("REGISTER");
                    break;

                case OP_IMMEDIATE:
                    printf("IMMEDIATE");
                    break;

                case OP_LABEL:
                    printf("LABEL");
                    break;

                case OP_MEMORY:
                    printf("MEMORY");
                    break;
            }

            printf(")\n");
        }

        printf("\n");
    }

    return 0;
}
