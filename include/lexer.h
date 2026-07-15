#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <stddef.h>

typedef struct 
{
    const char *source;
    
    size_t position;

    int line;
    int column;

} Lexer;


// Create lexer
Lexer lexer_init(const char *source);

// Get next token
Token next_token(Lexer *lexer);

#endif
