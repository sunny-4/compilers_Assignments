%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
int yyerror(const char *s);
extern FILE *yyin;
extern int line_number;
extern int column_number;

static FILE *report_fp = NULL;
static int reduction_index = 0;

static void log_reduction(const char *rule_text) {
    reduction_index++;
    printf("[reduce %d] %s\n", reduction_index, rule_text);
    if (report_fp) {
        fprintf(report_fp, "%d. %s\n", reduction_index, rule_text);
    }
}
%}

%define parse.error verbose

%start program

%token INT LONG SHORT FLOAT DOUBLE VOID CHAR STRUCT EXTERN
%token IF ELSE SWITCH CASE DEFAULT FOR WHILE DO BREAK CONTINUE RETURN SIZEOF

%token IDENTIFIER INTEGER_CONSTANT HEX_CONSTANT FLOAT_CONSTANT CHAR_CONSTANT STRING_LITERAL

%token PLUS MINUS MULTIPLY DIVIDE MODULO
%token LESS_THAN GREATER_THAN LESS_EQUAL GREATER_EQUAL EQUAL NOT_EQUAL
%token LOGICAL_AND LOGICAL_OR
%token BITWISE_AND BITWISE_OR BITWISE_XOR BITWISE_NOT
%token ASSIGN INCREMENT DECREMENT
%token DOT ARROW SPACESHIP

%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET
%token SEMICOLON COMMA COLON

%%

program
    : external_list                                      { log_reduction("program -> external_list"); }
    ;

external_list
    : external_list external                             { log_reduction("external_list -> external_list external"); }
    | external                                           { log_reduction("external_list -> external"); }
    ;

external
    : function_definition                                { log_reduction("external -> function_definition"); }
    | declaration SEMICOLON                              { log_reduction("external -> declaration ;"); }
    ;

function_definition
    : type_specifier declarator compound_statement       { log_reduction("function_definition -> type_specifier declarator compound_statement"); }
    | EXTERN type_specifier declarator compound_statement { log_reduction("function_definition -> extern type_specifier declarator compound_statement"); }
    ;

declaration
    : type_specifier init_declarator_list_opt            { log_reduction("declaration -> type_specifier init_declarator_list_opt"); }
    ;

init_declarator_list_opt
    : init_declarator_list                               { log_reduction("init_declarator_list_opt -> init_declarator_list"); }
    | /* empty */                                        { log_reduction("init_declarator_list_opt -> epsilon"); }
    ;

init_declarator_list
    : init_declarator                                    { log_reduction("init_declarator_list -> init_declarator"); }
    | init_declarator_list COMMA init_declarator         { log_reduction("init_declarator_list -> init_declarator_list , init_declarator"); }
    ;

init_declarator
    : declarator                                         { log_reduction("init_declarator -> declarator"); }
    | declarator ASSIGN initializer                      { log_reduction("init_declarator -> declarator = initializer"); }
    ;

initializer
    : assignment_expression                              { log_reduction("initializer -> assignment_expression"); }
    ;

type_specifier
    : INT                                                { log_reduction("type_specifier -> int"); }
    | LONG                                               { log_reduction("type_specifier -> long"); }
    | SHORT                                              { log_reduction("type_specifier -> short"); }
    | FLOAT                                              { log_reduction("type_specifier -> float"); }
    | DOUBLE                                             { log_reduction("type_specifier -> double"); }
    | VOID                                               { log_reduction("type_specifier -> void"); }
    | CHAR                                               { log_reduction("type_specifier -> char"); }
    | STRUCT IDENTIFIER                                  { log_reduction("type_specifier -> struct identifier"); }
    ;

declarator
    : pointer_opt direct_declarator                      { log_reduction("declarator -> pointer_opt direct_declarator"); }
    ;

pointer_opt
    : pointer                                            { log_reduction("pointer_opt -> pointer"); }
    | /* empty */                                        { log_reduction("pointer_opt -> epsilon"); }
    ;

pointer
    : MULTIPLY                                           { log_reduction("pointer -> *"); }
    | MULTIPLY pointer                                   { log_reduction("pointer -> * pointer"); }
    ;

direct_declarator
    : IDENTIFIER                                         { log_reduction("direct_declarator -> identifier"); }
    | IDENTIFIER LPAREN parameter_list_opt RPAREN        { log_reduction("direct_declarator -> identifier ( parameter_list_opt )"); }
    | LPAREN declarator RPAREN                           { log_reduction("direct_declarator -> ( declarator )"); }
    ;

parameter_list_opt
    : parameter_list                                     { log_reduction("parameter_list_opt -> parameter_list"); }
    | /* empty */                                        { log_reduction("parameter_list_opt -> epsilon"); }
    ;

parameter_list
    : parameter_declaration                              { log_reduction("parameter_list -> parameter_declaration"); }
    | parameter_list COMMA parameter_declaration         { log_reduction("parameter_list -> parameter_list , parameter_declaration"); }
    ;

parameter_declaration
    : type_specifier declarator                          { log_reduction("parameter_declaration -> type_specifier declarator"); }
    ;

compound_statement
    : LBRACE block_item_list_opt RBRACE                  { log_reduction("compound_statement -> { block_item_list_opt }"); }
    ;

block_item_list_opt
    : block_item_list                                    { log_reduction("block_item_list_opt -> block_item_list"); }
    | /* empty */                                        { log_reduction("block_item_list_opt -> epsilon"); }
    ;

block_item_list
    : block_item                                         { log_reduction("block_item_list -> block_item"); }
    | block_item_list block_item                         { log_reduction("block_item_list -> block_item_list block_item"); }
    ;

block_item
    : declaration SEMICOLON                              { log_reduction("block_item -> declaration ;"); }
    | statement                                          { log_reduction("block_item -> statement"); }
    ;

statement
    : simple_statement                                   { log_reduction("statement -> simple_statement"); }
    | compound_statement                                 { log_reduction("statement -> compound_statement"); }
    | IF LPAREN expression RPAREN statement              { log_reduction("statement -> if ( expression ) statement"); }
    | IF LPAREN expression RPAREN statement ELSE statement
                                                        { log_reduction("statement -> if ( expression ) statement else statement"); }
    | WHILE LPAREN expression RPAREN statement           { log_reduction("statement -> while ( expression ) statement"); }
    | DO statement WHILE LPAREN expression RPAREN SEMICOLON
                                                        { log_reduction("statement -> do statement while ( expression ) ;"); }
    | FOR LPAREN expr_opt SEMICOLON expr_opt SEMICOLON expr_opt RPAREN statement
                                                        { log_reduction("statement -> for ( expr_opt ; expr_opt ; expr_opt ) statement"); }
    | SWITCH LPAREN expression RPAREN LBRACE case_sections_opt default_section_opt RBRACE
                                                        { log_reduction("statement -> switch ( expression ) { case_sections_opt default_section_opt }"); }
    ;

simple_statement
    : expr_opt SEMICOLON                                 { log_reduction("simple_statement -> expr_opt ;"); }
    | BREAK SEMICOLON                                    { log_reduction("simple_statement -> break ;"); }
    | CONTINUE SEMICOLON                                 { log_reduction("simple_statement -> continue ;"); }
    | RETURN expr_opt SEMICOLON                          { log_reduction("simple_statement -> return expr_opt ;"); }
    ;

expr_opt
    : expression                                         { log_reduction("expr_opt -> expression"); }
    | /* empty */                                        { log_reduction("expr_opt -> epsilon"); }
    ;

case_sections_opt
    : case_sections                                      { log_reduction("case_sections_opt -> case_sections"); }
    | /* empty */                                        { log_reduction("case_sections_opt -> epsilon"); }
    ;

case_sections
    : case_section                                       { log_reduction("case_sections -> case_section"); }
    | case_sections case_section                         { log_reduction("case_sections -> case_sections case_section"); }
    ;

case_section
    : CASE constant_expression COLON statement_list_opt  { log_reduction("case_section -> case constant_expression : statement_list_opt"); }
    ;

default_section_opt
    : DEFAULT COLON statement_list_opt                   { log_reduction("default_section_opt -> default : statement_list_opt"); }
    | /* empty */                                        { log_reduction("default_section_opt -> epsilon"); }
    ;

statement_list_opt
    : statement_list                                     { log_reduction("statement_list_opt -> statement_list"); }
    | /* empty */                                        { log_reduction("statement_list_opt -> epsilon"); }
    ;

statement_list
    : statement                                          { log_reduction("statement_list -> statement"); }
    | statement_list statement                           { log_reduction("statement_list -> statement_list statement"); }
    ;

expression
    : ambiguous_expression                               { log_reduction("expression -> ambiguous_expression"); }
    ;

assignment_expression
    : ambiguous_expression                               { log_reduction("assignment_expression -> ambiguous_expression"); }
    ;

constant_expression
    : ambiguous_expression                               { log_reduction("constant_expression -> ambiguous_expression"); }
    ;

ambiguous_expression
    : unary_expression                                   { log_reduction("ambiguous_expression -> unary_expression"); }
    | ambiguous_expression COMMA ambiguous_expression    { log_reduction("ambiguous_expression -> ambiguous_expression , ambiguous_expression"); }
    | ambiguous_expression ASSIGN ambiguous_expression   { log_reduction("ambiguous_expression -> ambiguous_expression = ambiguous_expression"); }
    | ambiguous_expression LOGICAL_OR ambiguous_expression { log_reduction("ambiguous_expression -> ambiguous_expression || ambiguous_expression"); }
    | ambiguous_expression LOGICAL_AND ambiguous_expression { log_reduction("ambiguous_expression -> ambiguous_expression && ambiguous_expression"); }
    | ambiguous_expression BITWISE_OR ambiguous_expression { log_reduction("ambiguous_expression -> ambiguous_expression | ambiguous_expression"); }
    | ambiguous_expression BITWISE_XOR ambiguous_expression { log_reduction("ambiguous_expression -> ambiguous_expression ^ ambiguous_expression"); }
    | ambiguous_expression BITWISE_AND ambiguous_expression { log_reduction("ambiguous_expression -> ambiguous_expression & ambiguous_expression"); }
    | ambiguous_expression EQUAL ambiguous_expression    { log_reduction("ambiguous_expression -> ambiguous_expression == ambiguous_expression"); }
    | ambiguous_expression NOT_EQUAL ambiguous_expression { log_reduction("ambiguous_expression -> ambiguous_expression != ambiguous_expression"); }
    | ambiguous_expression LESS_THAN ambiguous_expression { log_reduction("ambiguous_expression -> ambiguous_expression < ambiguous_expression"); }
    | ambiguous_expression GREATER_THAN ambiguous_expression { log_reduction("ambiguous_expression -> ambiguous_expression > ambiguous_expression"); }
    | ambiguous_expression LESS_EQUAL ambiguous_expression { log_reduction("ambiguous_expression -> ambiguous_expression <= ambiguous_expression"); }
    | ambiguous_expression GREATER_EQUAL ambiguous_expression { log_reduction("ambiguous_expression -> ambiguous_expression >= ambiguous_expression"); }
    | ambiguous_expression SPACESHIP ambiguous_expression { log_reduction("ambiguous_expression -> ambiguous_expression <=> ambiguous_expression"); }
    | ambiguous_expression PLUS ambiguous_expression     { log_reduction("ambiguous_expression -> ambiguous_expression + ambiguous_expression"); }
    | ambiguous_expression MINUS ambiguous_expression    { log_reduction("ambiguous_expression -> ambiguous_expression - ambiguous_expression"); }
    | ambiguous_expression MULTIPLY ambiguous_expression { log_reduction("ambiguous_expression -> ambiguous_expression * ambiguous_expression"); }
    | ambiguous_expression DIVIDE ambiguous_expression   { log_reduction("ambiguous_expression -> ambiguous_expression / ambiguous_expression"); }
    | ambiguous_expression MODULO ambiguous_expression   { log_reduction("ambiguous_expression -> ambiguous_expression % ambiguous_expression"); }
    ;

unary_expression
    : postfix_expression                                 { log_reduction("unary_expression -> postfix_expression"); }
    | INCREMENT unary_expression                         { log_reduction("unary_expression -> ++ unary_expression"); }
    | DECREMENT unary_expression                         { log_reduction("unary_expression -> -- unary_expression"); }
    | PLUS unary_expression                              { log_reduction("unary_expression -> + unary_expression"); }
    | MINUS unary_expression                             { log_reduction("unary_expression -> - unary_expression"); }
    | BITWISE_NOT unary_expression                       { log_reduction("unary_expression -> ~ unary_expression"); }
    | BITWISE_AND unary_expression                       { log_reduction("unary_expression -> & unary_expression"); }
    | MULTIPLY unary_expression                          { log_reduction("unary_expression -> * unary_expression"); }
    | SIZEOF unary_expression                            { log_reduction("unary_expression -> sizeof unary_expression"); }
    | SIZEOF LPAREN type_specifier RPAREN                { log_reduction("unary_expression -> sizeof ( type_specifier )"); }
    ;

postfix_expression
    : primary_expression                                 { log_reduction("postfix_expression -> primary_expression"); }
    | postfix_expression LBRACKET expression RBRACKET    { log_reduction("postfix_expression -> postfix_expression [ expression ]"); }
    | postfix_expression LPAREN argument_expression_list_opt RPAREN
                                                        { log_reduction("postfix_expression -> postfix_expression ( argument_expression_list_opt )"); }
    | postfix_expression DOT IDENTIFIER                  { log_reduction("postfix_expression -> postfix_expression . identifier"); }
    | postfix_expression ARROW IDENTIFIER                { log_reduction("postfix_expression -> postfix_expression -> identifier"); }
    | postfix_expression INCREMENT                       { log_reduction("postfix_expression -> postfix_expression ++"); }
    | postfix_expression DECREMENT                       { log_reduction("postfix_expression -> postfix_expression --"); }
    ;

argument_expression_list_opt
    : argument_expression_list                           { log_reduction("argument_expression_list_opt -> argument_expression_list"); }
    | /* empty */                                        { log_reduction("argument_expression_list_opt -> epsilon"); }
    ;

argument_expression_list
    : assignment_expression                              { log_reduction("argument_expression_list -> assignment_expression"); }
    | argument_expression_list COMMA assignment_expression { log_reduction("argument_expression_list -> argument_expression_list , assignment_expression"); }
    ;

primary_expression
    : IDENTIFIER                                         { log_reduction("primary_expression -> identifier"); }
    | constant                                           { log_reduction("primary_expression -> constant"); }
    | string_literal_sequence                            { log_reduction("primary_expression -> string_literal_sequence"); }
    | LPAREN expression RPAREN                           { log_reduction("primary_expression -> ( expression )"); }
    ;

constant
    : INTEGER_CONSTANT                                   { log_reduction("constant -> integer_constant"); }
    | HEX_CONSTANT                                       { log_reduction("constant -> hex_constant"); }
    | FLOAT_CONSTANT                                     { log_reduction("constant -> float_constant"); }
    | CHAR_CONSTANT                                      { log_reduction("constant -> char_constant"); }
    ;

string_literal_sequence
    : STRING_LITERAL                                     { log_reduction("string_literal_sequence -> string_literal"); }
    | string_literal_sequence STRING_LITERAL             { log_reduction("string_literal_sequence -> string_literal_sequence string_literal"); }
    ;

%%

int yyerror(const char *s) {
    fprintf(stderr, "\n[ERROR] %s at line %d, col %d\n", s, line_number, column_number);
    if (report_fp) {
        fprintf(report_fp, "\n[ERROR] %s at line %d, col %d\n", s, line_number, column_number);
        fflush(report_fp);
    }
    return 0;
}

int main(int argc, char **argv) {
    int result;
    const char *input_path = NULL;
    const char *report_path = "derivation_report.txt";

    if (argc >= 2) {
        input_path = argv[1];
    }
    if (argc >= 3) {
        report_path = argv[2];
    }

    if (input_path != NULL) {
        yyin = fopen(input_path, "r");
        if (!yyin) {
            fprintf(stderr, "Error: cannot open input file '%s'\n", input_path);
            return 1;
        }
    }

    report_fp = fopen(report_path, "w");
    if (!report_fp) {
        fprintf(stderr, "Warning: cannot open report file '%s'\n", report_path);
    } else {
        fprintf(report_fp, "CS327 LALR(1) reduction report\n");
        fprintf(report_fp, "Input source: %s\n\n", input_path ? input_path : "stdin");
    }

    printf("CS327 LALR(1) parser run started.\n");
    printf("Tip: run bison with -v to inspect states/conflicts and parsing table details.\n\n");
    if (input_path) {
        printf("Reading input from: %s\n", input_path);
    } else {
        printf("Reading input from stdin (type code and press Ctrl+D to end).\n");
    }
    printf("Writing reductions to: %s\n", report_path);

    result = yyparse();
    if (result == 0) {
        printf("\nResult: ACCEPTED\n");
        if (report_fp) {
            fprintf(report_fp, "\nResult: ACCEPTED\n");
            fflush(report_fp);
        }
    } else {
        printf("\nResult: REJECTED\n");
        if (report_fp) {
            fprintf(report_fp, "\nResult: REJECTED\n");
            fflush(report_fp);
        }
    }

    if (report_fp) {
        fclose(report_fp);
    }
    if (yyin && input_path != NULL) {
        fclose(yyin);
    }

    return result;
}
