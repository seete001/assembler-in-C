#include <stdlib.h>
#include <stdio.h>

char *read_file(const char *file_name)
{
    FILE *f = fopen(file_name, "r");

    if(!f)
    {
        return NULL;
    }

    fseek(f , 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char *buffer = malloc(size + 1);

    if(!buffer)
    {
        return NULL;
    }

    fread(buffer, 1, size, f);

    fclose(f);

    return buffer;
}
