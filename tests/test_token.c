#include "../include/token.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    Token token;

    token.type = TOKEN_IDENTIFIER;
    token.value = "MOV";
    token.line = 1;
    token.column = 0;


    printf("Testing token...\n");

    token_print(token);


    printf("Token name: %s\n",
           token_type_name(token.type));


    printf("Token test finished\n");

    return 0;
}
