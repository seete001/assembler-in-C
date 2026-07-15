#include "../include/lexer.h"

#include <stdio.h>


int main()
{
    const char *source =
        "MOV r1, r2\n"
        "ADD r3, 5\n";


    Lexer lexer = lexer_init(source);


    printf("Testing lexer...\n");


    while(1)
    {
        Token token = next_token(&lexer);

        token_print(token);


        if(token.type == TOKEN_EOF)
        {
            break;
        }

        token_free(&token);
    }


    printf("Lexer test finished\n");


    return 0;
}
