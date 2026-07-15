#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    // End Of File
    TOKEN_EOF,
    TOKEN_UNKNOWN,

    // Values
    TOKEN_NUMBER,
    TOKEN_IDENTIFIER,
    TOKEN_STRING,

    // Symbols
    TOKEN_COMMA,
    TOKEN_COLON,
    TOKEN_LBRACKET,
    TOKEN_RBRACKET,

    // Line handling
    TOKEN_NEWLINE
} TokenType;

typedef struct {
    TokenType type;
    char *value;

    // for tracking the errors
    int line;
    int column;
} Token;


// Token utilities
void token_free(Token *token);

const char *token_type_name(TokenType type);

void token_print(Token token);


#endif
