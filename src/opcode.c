#include "../include/opcode.h"

#include <string.h>
#include <stdint.h>

static Opcode table[] = 
{
    {"MOV",0x01},
    {"ADD",0x02},
    {"SUB",0x03},
    {"LOAD",0x04},
    {"STORE",0x05},
    {"JMP",0x06},
    {"HLT",0xFF}
};

uint8_t opcode_lookup(const char *name)
{
    int count = sizeof(table) / sizeof(table[0]);

    for(int i = 0; i < count; i++)
    {
        if(strcmp(name, table[i].name) == 0)
        {
            return table[i].code;
        }
    }
    
    return 0;
}
