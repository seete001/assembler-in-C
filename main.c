#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    char *name;
    unsigned char code;
} Register;

typedef struct
{
    char *name;
    unsigned char opcode;
} Instruction;

Instruction instructions[] =
{
    {"ADD", 0x83},
    {"SUB", 0x81},
    {"MOV", 0xB8}
};

Register registers[] =
{
    {"eax", 0},
    {"ebx", 1},
    {"ecx", 2},
    {"edx", 3},
    {"hlt",4}
};

unsigned char find_opcode(char *name)
{
    for (int i = 0; i < 3; i++)
        if (strcmp(name, instructions[i].name) == 0)
            return instructions[i].opcode;

    return 0;
}

unsigned char find_register(char *name)
{
    for (int i = 0; i < 4; i++)
        if (strcmp(name, registers[i].name) == 0)
            return registers[i].code;

    return 0xFF;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: assembler <file>\n");
        return 1;
    }

    FILE *f_in = fopen(argv[1], "r");
    FILE *f_out = fopen("bin.hex", "w");

    if (!f_in || !f_out)
    {
        perror("Failed to open file");
        return 1;
    }

    char source[256];

    while (fgets(source, sizeof(source), f_in))
    {
        int value = 0;
        char instruction[32];
        char reg[32];

        int parsed = sscanf(source,
                             "%s %[^,], %d",
                             instruction,
                             reg,
                             &value);

        if (parsed == 3)
        {
            printf("%s", source);
            unsigned char opcode = find_opcode(instruction);
            unsigned char rcode  = find_register(reg);

            printf("%02X %02X %02X\n",
                   opcode, rcode, value);

            fprintf(f_out,
                    "%02X %02X %02X\n",
                    opcode, rcode, value);
        }
    }

    fclose(f_in);
    fclose(f_out);

    return 0;
}
