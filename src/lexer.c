#include "../include/lexer.h"

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/*
 * It returns the current character
 */
static char current_char(Lexer *lexer)
{
    return lexer->source[lexer->position];
}

/*
 * This function would move the postion of current pointer 
 * whenever it is called and it keeps tracking of the position
 */
static void advance(Lexer *lexer)
{
    if(current_char(lexer) == '\n')
    {
        lexer->column = 0;
        lexer->line++;
    }
    else 
    {
        lexer->column++;
    }

    lexer->position++;
}

/*
 * Let postion start to be at the start of the source and going through
 * it until it comes out of while loop then we return it
 */
static char *read_identifier(Lexer *lexer)
{
    int start = lexer->position;

    while(isalnum(current_char(lexer)) ||
          current_char(lexer) == '_')
    {
        advance(lexer);
    }

    int length = lexer->position - start;

    char *text = malloc(length + 1);

    if(!text)
    {
        return NULL;
    }

    memcpy(text, 
            lexer->source + start, 
            length);

    text[length] = '\0';

    return text;
}

/*
 * Reading number exactly like read_identifier function
 */
static char *read_number(Lexer *lexer)
{
    int start = lexer->position;

    while(isdigit(current_char(lexer)))
    {
        advance(lexer);
    }

    int length = lexer->position - start;

    char *text = malloc(length + 1);

    memcpy(text, 
            lexer->source + start, 
            length);

    text[length] = '\0';

    return text;
    
}


static void skip_spaces(Lexer *lexer)
{
    while(current_char(lexer) == ' ' ||
          current_char(lexer) == '\t' ||
          current_char(lexer) == '\r')
    {
        advance(lexer);
    }
}

/*
 * This function initializes the lexer with assigning the source to the lexer
 */
Lexer lexer_init(const char *source)
{
    Lexer lexer;

    lexer.source = source;
    lexer.position = 0;
    lexer.line = 1;
    lexer.column = 0;

    return lexer;
}

Token next_token(Lexer *lexer)
{
    skip_spaces(lexer);

    char c = current_char(lexer);

    int line = lexer->line;
    int column = lexer->column;

    // Null termiator means enf of our source
    if(c == '\0')
    {
        return (Token)
        {
            .type = TOKEN_EOF,
            .value = NULL,
            .column = column,
            .line = line
        };
    }

    // Number
    if(isdigit(c))
    {
        return (Token)
        {
            .type = TOKEN_NUMBER,
            .value = read_number(lexer),
            .column = column,
            .line = line
        };
    }

    // Identifier
    if(isalpha(c) || c == '_')
    {
        return (Token)
        {
            .type = TOKEN_IDENTIFIER,
            .value = read_identifier(lexer),
            .column = column,
            .line = line
        };
    }

    switch (c) 
    {
        case ',':
            advance(lexer);
            return (Token)
            {
                .type = TOKEN_COMMA,
                .column = column,
                .line = line
            };

        case ':':
            advance(lexer);
            return (Token)
            {
                .type = TOKEN_COLON,
                .column = column,
                .line = line
            };

        case '[':
            advance(lexer);
            return (Token)
            {
                .type = TOKEN_LBRACKET,
                .line = line,
                .column = column
            };

        case ']':
            advance(lexer);
            return (Token)
            {
                .type = TOKEN_RBRACKET,
                .line = line,
                .column = column
            };

        case '\n':
            advance(lexer);
            return (Token)
            {
                .type = TOKEN_NEWLINE,
                .line = line,
                .column = column
            };
    }

    // End Of File after checking for number and identifiers
    advance(lexer);
    return (Token)
    {
        .type = TOKEN_UNKNOWN,
        .column = column,
        .line = line,
        .value = strdup((char[]){ c, '\0' })
    };       
}
