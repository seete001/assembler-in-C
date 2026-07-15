#include "IO/read_file.h"
#include "IO/write_file.h"
#include "../include/parser.h"
#include "../include/assembler.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: assembler <file>\n");
        return 1;
    }

    
    char *source = read_file(argv[1]);

    Parser parser = parser_init(source);

    Program program = parser_program(&parser);

    MachineCode code = assemble_program(program);

    write_file("/bin/program.bin", code);

    free(source); 

    return 0;
}
