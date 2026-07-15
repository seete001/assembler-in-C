#include "write_file.h"

#include <stdio.h>


void write_file(const char *filename, MachineCode code)
{
    FILE *file = fopen(filename, "wb");

    if (file == NULL)
    {
        return;
    }

    fwrite(code.bytes,
           1,
           code.size,
           file);

    fclose(file);
}
