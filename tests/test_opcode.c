#include "../include/opcode.h"

#include <stdio.h>

int main(void)
{
    printf("Opcde test running ...\n");

    printf("MOV: %d\n", opcode_lookup("MOV"));

    printf("JMP: %d\n", opcode_lookup("JMP"));

    return 0;
}
