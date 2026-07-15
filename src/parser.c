#include "../include/parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Parser parser_init(const char *source)
{
    Parser parser;

    parser.lexer = lexer_init(source);
    parser.current = next_token(&parser.lexer);

    return parser;
}

static void parser_error(Parser *parser, const char *message)
{
    fprintf(stderr, "Parser Error at %d:%d : %s",
            parser->current.line,
            parser->current.column,
            message);
    exit(EXIT_FAILURE);
}

static bool parser_match(Parser *parser, TokenType type)
{
    return parser->current.type == type;
}

void parser_advance(Parser *parser)
{
    token_free(&parser->current);
    parser->current = next_token(&parser->lexer);
}

static bool is_register(const char *text)
{
    if(text[0] != 'r')
    {
        return false;
    }
    if(text[2] != '\0')
    {
        return false;
    }

    return text[1] >= '1' && text[1] <= '8';
}

static Operand parser_operand(Parser *parser)
{
    Operand op = {0};

    Token current = parser->current;

    if(current.type == TOKEN_NUMBER)
    {
        op.type = OP_IMMEDIATE;
        op.value = strdup(current.value);
    
        parser_advance(parser);

        return op;
    }

    if(current.type == TOKEN_IDENTIFIER)
    {
        op.value = strdup(current.value);
        
        if(is_register(current.value))
        {
            op.type = OP_REGISTER;
        }
        else
        {
            op.type = OP_LABEL;
        }

        parser_advance(parser);

        return op;
    }

    parser_error(parser, "expected operand");
    
    return op;
}

void parser_expect(Parser *parser, TokenType type)
{
    if(parser_match(parser, type))
    {
        parser_advance(parser);
    }
    else 
    {
        char buffer[128];
        
        snprintf(buffer,
                sizeof(buffer),
                "expected %s, got %s",
                token_type_name(type),
                token_type_name(parser->current.type));

        parser_error(parser,buffer);
    }
}

Instruction parser_instruction(Parser *parser)
{
   Instruction inst = {0};

   if(parser->current.type != TOKEN_IDENTIFIER)
   {
       parser_error(parser, "expected Instruction");
   }

   inst.opcode = strdup(parser->current.value);

   parser_advance(parser);

   while(parser->current.type != TOKEN_EOF &&
         parser->current.type != TOKEN_NEWLINE)
   {
       if(parser->current.type == TOKEN_COMMA)
       {
           parser_advance(parser);
           continue;
       }
       if(inst.operand_count >= 2)
       {
           parser_error(parser, "too many operands");
       }

       inst.operands[inst.operand_count] = parser_operand(parser);
       inst.operand_count++;
   }

   if(parser->current.type == TOKEN_NEWLINE)
   {
       parser_advance(parser);
   }


   return inst;
}

Program parser_program(Parser *parser)
{
    Program program = {0};

    while(parser->current.type != TOKEN_EOF)
    {
        if(parser->current.type == TOKEN_NEWLINE)
        {
            parser_advance(parser);
            continue;
        }
        program.instructions[program.count++] = parser_instruction(parser);
    }
    return program;
}

