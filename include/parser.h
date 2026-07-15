#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>

#include "program.h"
#include "instruction.h"
#include "lexer.h"
#include "token.h"

typedef struct
{
    Lexer lexer;
    Token current;

} Parser ;

Parser parser_init(const char *source);

Instruction parser_instruction(Parser *parser);

void parser_advance(Parser *parser);

void parser_expect(Parser *parser, TokenType type);

Program parser_program(Parser *parser);

#endif
