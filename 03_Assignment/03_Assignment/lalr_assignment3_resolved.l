%{
#include <stdio.h>
#include <string.h>
#include "lalr_assignment3_resolved.tab.h"

int line_number = 1;
int column_number = 1;
int last_token_line = 1;
int last_token_col = 1;
char last_lexeme[256] = "";

static int comment_start_line = 0;

#define YY_USER_ACTION \
  do { \
    last_token_line = line_number; \
    last_token_col = column_number; \
    snprintf(last_lexeme, sizeof(last_lexeme), "%s", yytext); \
  } while (0);

static void lex_error(const char *kind, const char *lexeme) {
    fprintf(stderr, "[%s] '%s' at line %d, col %d\n", kind, lexeme, line_number, column_number);
}
%}

%option noyywrap

%x COMMENT

%%
[ \t\r]+                               { column_number += yyleng; }
\n                                     { line_number++; column_number = 1; }
"//"[^\n]*                             { column_number += yyleng; }
"/*"                                   { comment_start_line = line_number; column_number += 2; BEGIN(COMMENT); }
<COMMENT>"*/"                          { column_number += 2; BEGIN(INITIAL); }
<COMMENT>\n                            { line_number++; column_number = 1; }
<COMMENT>.                              { column_number++; }
<COMMENT><<EOF>>                        {
                                          fprintf(stderr,
                                                  "*** lexing terminated *** [lexer error]: ill-formed comment starting at line %d\n",
                                                  comment_start_line);
                                          return 0;
                                        }

"#"[^\n]*                              { lex_error("UNSUPPORTED_PREPROCESSOR", yytext); column_number += yyleng; return yytext[0]; }
"<<="|">>="|"<<"|">>"               { lex_error("UNSUPPORTED_OPERATOR", yytext); column_number += yyleng; return yytext[0]; }
"+="|"-="|"*="|"/="|"%="             { lex_error("UNSUPPORTED_OPERATOR", yytext); column_number += yyleng; return yytext[0]; }
"&="|"|="|"^="                        { lex_error("UNSUPPORTED_OPERATOR", yytext); column_number += yyleng; return yytext[0]; }
"..."|"?"                              { lex_error("UNSUPPORTED_OPERATOR", yytext); column_number += yyleng; return yytext[0]; }

"int"                                   { column_number += yyleng; return INT; }
"long"                                  { column_number += yyleng; return LONG; }
"short"                                 { column_number += yyleng; return SHORT; }
"float"                                 { column_number += yyleng; return FLOAT; }
"double"                                { column_number += yyleng; return DOUBLE; }
"void"                                  { column_number += yyleng; return VOID; }
"char"                                  { column_number += yyleng; return CHAR; }
"struct"                                { column_number += yyleng; return STRUCT; }
"extern"                                { column_number += yyleng; return EXTERN; }
"if"                                    { column_number += yyleng; return IF; }
"else"                                  { column_number += yyleng; return ELSE; }
"switch"                                { column_number += yyleng; return SWITCH; }
"case"                                  { column_number += yyleng; return CASE; }
"default"                               { column_number += yyleng; return DEFAULT; }
"for"                                   { column_number += yyleng; return FOR; }
"while"                                 { column_number += yyleng; return WHILE; }
"do"                                    { column_number += yyleng; return DO; }
"break"                                 { column_number += yyleng; return BREAK; }
"continue"                              { column_number += yyleng; return CONTINUE; }
"return"                                { column_number += yyleng; return RETURN; }
"sizeof"                                { column_number += yyleng; return SIZEOF; }

"<=>"                                   { column_number += yyleng; return SPACESHIP; }
"->"                                    { column_number += yyleng; return ARROW; }
"++"                                    { column_number += yyleng; return INCREMENT; }
"--"                                    { column_number += yyleng; return DECREMENT; }
"<="                                    { column_number += yyleng; return LESS_EQUAL; }
">="                                    { column_number += yyleng; return GREATER_EQUAL; }
"=="                                    { column_number += yyleng; return EQUAL; }
"!="                                    { column_number += yyleng; return NOT_EQUAL; }
"&&"                                    { column_number += yyleng; return LOGICAL_AND; }
"||"                                    { column_number += yyleng; return LOGICAL_OR; }
"+"                                     { column_number += yyleng; return PLUS; }
"-"                                     { column_number += yyleng; return MINUS; }
"*"                                     { column_number += yyleng; return MULTIPLY; }
"/"                                     { column_number += yyleng; return DIVIDE; }
"%"                                     { column_number += yyleng; return MODULO; }
"<"                                     { column_number += yyleng; return LESS_THAN; }
">"                                     { column_number += yyleng; return GREATER_THAN; }
"&"                                     { column_number += yyleng; return BITWISE_AND; }
"|"                                     { column_number += yyleng; return BITWISE_OR; }
"^"                                     { column_number += yyleng; return BITWISE_XOR; }
"~"                                     { column_number += yyleng; return BITWISE_NOT; }
"="                                     { column_number += yyleng; return ASSIGN; }
"."                                     { column_number += yyleng; return DOT; }

"("                                     { column_number += yyleng; return LPAREN; }
")"                                     { column_number += yyleng; return RPAREN; }
"{"                                     { column_number += yyleng; return LBRACE; }
"}"                                     { column_number += yyleng; return RBRACE; }
"["                                     { column_number += yyleng; return LBRACKET; }
"]"                                     { column_number += yyleng; return RBRACKET; }
";"                                     { column_number += yyleng; return SEMICOLON; }
","                                     { column_number += yyleng; return COMMA; }
":"                                     { column_number += yyleng; return COLON; }

0[xX][0-9A-Fa-f]+                       { column_number += yyleng; return HEX_CONSTANT; }
[0-9]*\.[0-9]+                          { column_number += yyleng; return FLOAT_CONSTANT; }
[0-9]+                                   { column_number += yyleng; return INTEGER_CONSTANT; }
'([^'\\]|\\n|\\t|\\r|\\0|\\\\|\\')'    { column_number += yyleng; return CHAR_CONSTANT; }
\"([^\"\\\n]|\\.)*\"                 { column_number += yyleng; return STRING_LITERAL; }

[A-Za-z_][A-Za-z0-9_]*                  { column_number += yyleng; return IDENTIFIER; }

.                                       {
                                          lex_error("UNKNOWN_TOKEN", yytext);
                                          column_number += yyleng;
                                          return yytext[0];
                                        }
%%
