%{
/*
 * Lexical Analyzer for C-like Language Subset
 * Group ID: 22
 * 
 * This lexer recognizes tokens for a simplified C-like programming language
 * including keywords, identifiers, constants, operators, and comments.
 */

#include <stdio.h>
#include <string.h>

int line_number = 1;
int column_number = 1;
int comment_start_line = 0;
int comment_start_col = 0;
char comment_buffer[10000];
int comment_length = 0;

void print_token(const char* token_type, const char* lexeme, int line, int column, int length) {
    printf("%-20s %-15s %4d %4d %4d\n", token_type, lexeme, line, column, length);
}

%}

/* Options */
%option noyywrap

/* Definitions */
DIGIT           [0-9]
LETTER          [A-Za-z]
IDENTIFIER      [A-Za-z_][A-Za-z0-9_]*
DECIMAL_INT     [0-9]+
HEX_INT         0[xX][0-9A-Fa-f]+
FLOAT_CONST     [0-9]*\.[0-9]+
WHITESPACE      [ \t\r]+
NEWLINE         \n

/* Comment state */
%x COMMENT

%%

    /* ===== COMMENTS ===== */
    /* Single-line comment */
"//".*                  { 
                          print_token("SINGLE_LINE_CMT", yytext, line_number, column_number, yyleng); 
                          column_number += yyleng;
                        }

    /* Multi-line comment start */
"/*"                    { 
                          comment_start_line = line_number;
                          comment_start_col = column_number;
                          comment_length = 0;
                          strcpy(comment_buffer, "/*");
                          comment_length = 2;
                          column_number += 2;
                          BEGIN(COMMENT); 
                        }

<COMMENT>"*/"           { 
                          strcat(comment_buffer, "*/");
                          comment_length += 2;
                          print_token("MULTI_LINE_CMT", comment_buffer, comment_start_line, comment_start_col, comment_length); 
                          column_number += 2; 
                          BEGIN(INITIAL); 
                        }
<COMMENT>\n             { 
                          strcat(comment_buffer, "\n");
                          comment_length++;
                          line_number++; 
                          column_number = 1; 
                        }
<COMMENT>.              { 
                          strncat(comment_buffer, yytext, 1);
                          comment_length++;
                          column_number++; 
                        }
<COMMENT><<EOF>>        { 
                          fprintf(stderr, "*** lexing terminated *** [lexer error]: ill-formed comment starting at line %d\n", comment_start_line);
                          return 0;
                        }


    /* ===== KEYWORDS ===== */
"int"                   { print_token("INT", yytext, line_number, column_number, yyleng); column_number += yyleng; }
"long"                  { print_token("LONG", yytext, line_number, column_number, yyleng); column_number += yyleng; }
"short"                 { print_token("SHORT", yytext, line_number, column_number, yyleng); column_number += yyleng; }
"float"                 { print_token("FLOAT", yytext, line_number, column_number, yyleng); column_number += yyleng; }
"double"                { print_token("DOUBLE", yytext, line_number, column_number, yyleng); column_number += yyleng; }
"void"                  { print_token("VOID", yytext, line_number, column_number, yyleng); column_number += yyleng; }
"char"                  { print_token("CHAR", yytext, line_number, column_number, yyleng); column_number += yyleng; }
"struct"                { print_token("STRUCT", yytext, line_number, column_number, yyleng); column_number += yyleng; }
"extern"                { print_token("EXTERN", yytext, line_number, column_number, yyleng); column_number += yyleng; }
"if"                    { print_token("IF", yytext, line_number, column_number, yyleng); column_number += yyleng; }
"else"                  { print_token("ELSE", yytext, line_number, column_number, yyleng); column_number += yyleng; }
"switch"                { print_token("SWITCH", yytext, line_number, column_number, yyleng); column_number += yyleng; }
"case"                  { print_token("CASE", yytext, line_number, column_number, yyleng); column_number += yyleng; }
"default"               { print_token("DEFAULT", yytext, line_number, column_number, yyleng); column_number += yyleng; }
"for"                   { print_token("FOR", yytext, line_number, column_number, yyleng); column_number += yyleng; }
"while"                 { print_token("WHILE", yytext, line_number, column_number, yyleng); column_number += yyleng; }
"do"                    { print_token("DO", yytext, line_number, column_number, yyleng); column_number += yyleng; }
"break"                 { print_token("BREAK", yytext, line_number, column_number, yyleng); column_number += yyleng; }
"continue"              { print_token("CONTINUE", yytext, line_number, column_number, yyleng); column_number += yyleng; }
"return"                { print_token("RETURN", yytext, line_number, column_number, yyleng); column_number += yyleng; }
"sizeof"                { print_token("SIZEOF", yytext, line_number, column_number, yyleng); column_number += yyleng; }


    /* ===== OPERATORS ===== */
    /* Multi-character operators (must come before single-character) */
    
    /* Special Operator */
"<=>"                   { print_token("SPACESHIP", yytext, line_number, column_number, yyleng); column_number += yyleng; }

    /* Structure Access Operators */
"->"                    { print_token("ARROW", yytext, line_number, column_number, yyleng); column_number += yyleng; }

    /* Increment/Decrement Operators */
"++"                    { print_token("INCREMENT", yytext, line_number, column_number, yyleng); column_number += yyleng; }
"--"                    { print_token("DECREMENT", yytext, line_number, column_number, yyleng); column_number += yyleng; }

    /* Relational Operators - Two character */
"<="                    { print_token("LESS_EQUAL", yytext, line_number, column_number, yyleng); column_number += yyleng; }
">="                    { print_token("GREATER_EQUAL", yytext, line_number, column_number, yyleng); column_number += yyleng; }
"=="                    { print_token("EQUAL", yytext, line_number, column_number, yyleng); column_number += yyleng; }
"!="                    { print_token("NOT_EQUAL", yytext, line_number, column_number, yyleng); column_number += yyleng; }

    /* Logical Operators */
"&&"                    { print_token("LOGICAL_AND", yytext, line_number, column_number, yyleng); column_number += yyleng; }
"||"                    { print_token("LOGICAL_OR", yytext, line_number, column_number, yyleng); column_number += yyleng; }

    /* Arithmetic Operators - Single character */
"+"                     { print_token("PLUS", yytext, line_number, column_number, yyleng); column_number += yyleng; }
"-"                     { print_token("MINUS", yytext, line_number, column_number, yyleng); column_number += yyleng; }
"*"                     { print_token("MULTIPLY", yytext, line_number, column_number, yyleng); column_number += yyleng; }
"/"                     { print_token("DIVIDE", yytext, line_number, column_number, yyleng); column_number += yyleng; }
"%"                     { print_token("MODULO", yytext, line_number, column_number, yyleng); column_number += yyleng; }

    /* Relational Operators - Single character */
"<"                     { print_token("LESS_THAN", yytext, line_number, column_number, yyleng); column_number += yyleng; }
">"                     { print_token("GREATER_THAN", yytext, line_number, column_number, yyleng); column_number += yyleng; }

    /* Bitwise Operators */
"&"                     { print_token("BITWISE_AND", yytext, line_number, column_number, yyleng); column_number += yyleng; }
"|"                     { print_token("BITWISE_OR", yytext, line_number, column_number, yyleng); column_number += yyleng; }
"^"                     { print_token("BITWISE_XOR", yytext, line_number, column_number, yyleng); column_number += yyleng; }
"~"                     { print_token("BITWISE_NOT", yytext, line_number, column_number, yyleng); column_number += yyleng; }

    /* Assignment Operator */
"="                     { print_token("ASSIGN", yytext, line_number, column_number, yyleng); column_number += yyleng; }

    /* Structure Access - Dot */
"."                     { print_token("DOT", yytext, line_number, column_number, yyleng); column_number += yyleng; }


    /* ===== DELIMITERS / PUNCTUATORS ===== */
"("                     { print_token("LPAREN", yytext, line_number, column_number, yyleng); column_number += yyleng; }
")"                     { print_token("RPAREN", yytext, line_number, column_number, yyleng); column_number += yyleng; }
"{"                     { print_token("LBRACE", yytext, line_number, column_number, yyleng); column_number += yyleng; }
"}"                     { print_token("RBRACE", yytext, line_number, column_number, yyleng); column_number += yyleng; }
"["                     { print_token("LBRACKET", yytext, line_number, column_number, yyleng); column_number += yyleng; }
"]"                     { print_token("RBRACKET", yytext, line_number, column_number, yyleng); column_number += yyleng; }
";"                     { print_token("SEMICOLON", yytext, line_number, column_number, yyleng); column_number += yyleng; }
","                     { print_token("COMMA", yytext, line_number, column_number, yyleng); column_number += yyleng; }
":"                     { print_token("COLON", yytext, line_number, column_number, yyleng); column_number += yyleng; }


    /* ===== CONSTANTS ===== */
    /* Hexadecimal Integer (must come before decimal) */
{HEX_INT}               { print_token("HEX_CONSTANT", yytext, line_number, column_number, yyleng); column_number += yyleng; }

    /* Floating Point Constant */
{FLOAT_CONST}           { print_token("FLOAT_CONSTANT", yytext, line_number, column_number, yyleng); column_number += yyleng; }

    /* Decimal Integer */
{DECIMAL_INT}           { print_token("INTEGER_CONSTANT", yytext, line_number, column_number, yyleng); column_number += yyleng; }

    /* Character Constant */
'([^'\\]|\\n|\\t|\\r|\\0|\\\\|\\')'  { print_token("CHAR_CONSTANT", yytext, line_number, column_number, yyleng); column_number += yyleng; }

    /* String Literal */
\"([^\"\\\n]|\\.)*\"    { print_token("STRING_LITERAL", yytext, line_number, column_number, yyleng); column_number += yyleng; }


    /* ===== IDENTIFIERS ===== */
{IDENTIFIER}            { print_token("IDENTIFIER", yytext, line_number, column_number, yyleng); column_number += yyleng; }


    /* ===== WHITESPACE ===== */
{WHITESPACE}            { column_number += yyleng; /* Ignore whitespace */ }
{NEWLINE}               { line_number++; column_number = 1; }


    /* ===== ERROR HANDLING ===== */
.                       { 
                          fprintf(stderr, "UNKNOWN_TOKEN, %s, %d, %d, %d\n", yytext, line_number, column_number, yyleng);
                          column_number += yyleng;
                        }

%%

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            fprintf(stderr, "Error: Could not open file '%s'\n", argv[1]);
            return 1;
        }
        yyin = file;
    }
    
    printf("%-20s %-15s %4s %4s %4s\n", "TOKEN_TYPE", "LEXEME", "LINE", "COL", "LEN");
    printf("--------------------------------------------------------------------------------\n");
    yylex();
    
    if (argc > 1) {
        fclose(yyin);
    }
    
    return 0;
}
