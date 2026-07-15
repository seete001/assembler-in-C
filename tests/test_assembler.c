#include "../include/parser.h"
#include "../include/assembler.h"

#include <stdio.h>


int main()
{
    const char *source =
        "MOV r1, r2\n"
        "ADD r3, 5\n";


    Parser parser = parser_init(source);


    Program program =
        parser_program(&parser);


    printf("Instructions: %d\n",
            program.count);


    MachineCode code =
        assemble_program(program);


    for(int i = 0; i < code.size; i++)
    {
        printf("%02X ", code.bytes[i]);
    }

    printf("\n");


    return 0;
}
