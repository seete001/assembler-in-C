#ifndef OPCODE_H
#define OPCODE_H

#include <stdint.h>

typedef struct
{
    const char *name;
    uint8_t code;

} Opcode;

uint8_t opcode_lookup(const char *name);

#endif
