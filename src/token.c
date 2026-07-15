#include "../include/token.h"
#include <stdio.h>
#include <stdlib.h>


void token_free(Token *token)
{
    if (token->value != NULL) {
        free(token->value);
        token->value = NULL;
    }
}


const char *token_type_name(TokenType type)
{
    switch(type)
    {
        case TOKEN_EOF:
            return "EOF";

        case TOKEN_IDENTIFIER:
            return "IDENTIFIER";

        case TOKEN_NUMBER:
            return "NUMBER";

        case TOKEN_STRING:
            return "STRING";

        case TOKEN_COMMA:
            return "COMMA";

        case TOKEN_COLON:
            return "COLON";

        case TOKEN_LBRACKET:
            return "LBRACKET";

        case TOKEN_RBRACKET:
            return "RBRACKET";

        case TOKEN_NEWLINE:
            return "NEWLINE";
        case TOKEN_UNKNOWN:
            return "UNKNOWN";
    }

    return "UNKNOWN";
}


void token_print(Token token)
{
    printf(
        "%s: %s (line %d, column %d)\n",
        token_type_name(token.type),
        token.value ? token.value : "",
        token.line,
        token.column
    );
}
