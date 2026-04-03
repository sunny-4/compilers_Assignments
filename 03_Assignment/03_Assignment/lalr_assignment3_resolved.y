%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int yylex(void);
int yyerror(const char *s);
extern FILE *yyin;
extern int line_number;
extern int column_number;
extern char last_lexeme[];
extern int last_token_line;
extern int last_token_col;

static FILE *report_fp = NULL;
static const char *current_input_path = NULL;
static int reduction_index = 0;
static char **reduction_rules = NULL;
static int reduction_count = 0;
static int reduction_capacity = 0;

static void free_reduction_rules(void) {
    int i;
    for (i = 0; i < reduction_count; i++) {
        free(reduction_rules[i]);
    }
    free(reduction_rules);
    reduction_rules = NULL;
    reduction_count = 0;
    reduction_capacity = 0;
}

static void store_reduction_rule(const char *rule_text) {
    char *rule_copy;
    size_t len;
    if (reduction_count == reduction_capacity) {
        int new_capacity = (reduction_capacity == 0) ? 64 : reduction_capacity * 2;
        char **new_rules = (char **)realloc(reduction_rules, (size_t)new_capacity * sizeof(char *));
        if (!new_rules) {
            fprintf(stderr, "Warning: failed to grow reduction rule storage.\n");
            return;
        }
        reduction_rules = new_rules;
        reduction_capacity = new_capacity;
    }

    len = strlen(rule_text);
    rule_copy = (char *)malloc(len + 1);
    if (!rule_copy) {
        fprintf(stderr, "Warning: failed to store reduction rule text.\n");
        return;
    }
    memcpy(rule_copy, rule_text, len + 1);
    reduction_rules[reduction_count++] = rule_copy;
}

static void print_reverse_derivation(FILE *out) {
    int i;
    fprintf(out, "\nReverse Derivation Tree (Reduction Sequence in Reverse):\n");
    if (reduction_count == 0) {
        fprintf(out, "(no reductions recorded)\n");
        return;
    }

    for (i = reduction_count - 1; i >= 0; i--) {
        fprintf(out, "%d. %s\n", reduction_count - i, reduction_rules[i]);
    }
}

#define MAX_TABLE_STATES 1024
#define MAX_TABLE_COLS 256
#define MAX_NAME_LEN 64
#define MAX_CELL_LEN 24

static char table_cols[MAX_TABLE_COLS][MAX_NAME_LEN];
static int table_col_is_nonterminal[MAX_TABLE_COLS];
static int table_col_count = 0;
static char table_cells[MAX_TABLE_STATES][MAX_TABLE_COLS][MAX_CELL_LEN];
static int table_state_seen[MAX_TABLE_STATES];
static int max_table_state = -1;

static void reset_table_data(void) {
    memset(table_cols, 0, sizeof(table_cols));
    memset(table_col_is_nonterminal, 0, sizeof(table_col_is_nonterminal));
    memset(table_cells, 0, sizeof(table_cells));
    memset(table_state_seen, 0, sizeof(table_state_seen));
    table_col_count = 0;
    max_table_state = -1;
}

static int is_nonterminal_symbol(const char *sym) {
    return islower((unsigned char)sym[0]) ? 1 : 0;
}

static int get_or_add_col(const char *sym, int is_nonterminal) {
    int i;
    for (i = 0; i < table_col_count; i++) {
        if (strcmp(table_cols[i], sym) == 0 && table_col_is_nonterminal[i] == is_nonterminal) {
            return i;
        }
    }
    if (table_col_count >= MAX_TABLE_COLS) {
        return -1;
    }
    strncpy(table_cols[table_col_count], sym, MAX_NAME_LEN - 1);
    table_cols[table_col_count][MAX_NAME_LEN - 1] = '\0';
    table_col_is_nonterminal[table_col_count] = is_nonterminal;
    table_col_count++;
    return table_col_count - 1;
}

static void set_table_cell(int state, const char *sym, int is_nonterminal, const char *value) {
    int col;
    if (state < 0 || state >= MAX_TABLE_STATES) {
        return;
    }
    col = get_or_add_col(sym, is_nonterminal);
    if (col < 0) {
        return;
    }
    strncpy(table_cells[state][col], value, MAX_CELL_LEN - 1);
    table_cells[state][col][MAX_CELL_LEN - 1] = '\0';
    table_state_seen[state] = 1;
    if (state > max_table_state) {
        max_table_state = state;
    }
}

static void parse_output_and_build_table(const char *output_path) {
    FILE *fp;
    char line[1024];
    int current_state = -1;

    fp = fopen(output_path, "r");
    if (!fp) {
        fprintf(stderr, "Warning: cannot open automaton report '%s' for table printing.\n", output_path);
        return;
    }

    reset_table_data();

    while (fgets(line, sizeof(line), fp)) {
        int state_id;
        char sym[MAX_NAME_LEN];
        int number;

        if (sscanf(line, "State %d", &state_id) == 1) {
            current_state = state_id;
            continue;
        }

        if (current_state < 0) {
            continue;
        }

        if (sscanf(line, " %63s shift, and go to state %d", sym, &number) == 2) {
            char display_sym[MAX_NAME_LEN];
            char value[MAX_CELL_LEN];
            if (strcmp(sym, "$end") == 0) {
                strcpy(display_sym, "$");
            } else {
                strncpy(display_sym, sym, MAX_NAME_LEN - 1);
                display_sym[MAX_NAME_LEN - 1] = '\0';
            }
            snprintf(value, sizeof(value), "s%d", number);
            set_table_cell(current_state, display_sym, 0, value);
            continue;
        }

        if (sscanf(line, " %63s go to state %d", sym, &number) == 2) {
            char value[MAX_CELL_LEN];
            snprintf(value, sizeof(value), "%d", number);
            set_table_cell(current_state, sym, is_nonterminal_symbol(sym), value);
            continue;
        }

        if (strstr(line, "reduce using rule") != NULL) {
            if (sscanf(line, " %63s reduce using rule %d", sym, &number) == 2 ||
                sscanf(line, " %63s [reduce using rule %d", sym, &number) == 2) {
                char display_sym[MAX_NAME_LEN];
                char value[MAX_CELL_LEN];
                if (strcmp(sym, "$default") == 0) {
                    strcpy(display_sym, "default");
                } else if (strcmp(sym, "$end") == 0) {
                    strcpy(display_sym, "$");
                } else {
                    strncpy(display_sym, sym, MAX_NAME_LEN - 1);
                    display_sym[MAX_NAME_LEN - 1] = '\0';
                }
                snprintf(value, sizeof(value), "r%d", number);
                set_table_cell(current_state, display_sym, 0, value);
                continue;
            }
        }

        if (strstr(line, " accept") != NULL) {
            char keyword[MAX_NAME_LEN];
            if (sscanf(line, " %63s %63s", sym, keyword) == 2 && strcmp(keyword, "accept") == 0) {
                char display_sym[MAX_NAME_LEN];
                if (strcmp(sym, "$default") == 0 || strcmp(sym, "$end") == 0) {
                    strcpy(display_sym, "$");
                } else {
                    strncpy(display_sym, sym, MAX_NAME_LEN - 1);
                    display_sym[MAX_NAME_LEN - 1] = '\0';
                }
                set_table_cell(current_state, display_sym, 0, "acc");
            }
        }
    }

    fclose(fp);
}

static void print_parsing_table_matrix(FILE *out) {
    int i, state;
    int action_cols[MAX_TABLE_COLS];
    int goto_cols[MAX_TABLE_COLS];
    int action_count = 0;
    int goto_count = 0;

    for (i = 0; i < table_col_count; i++) {
        if (table_col_is_nonterminal[i]) {
            goto_cols[goto_count++] = i;
        } else {
            action_cols[action_count++] = i;
        }
    }

    fprintf(out, "\nLALR(1) Parsing Table (Matrix Format)\n");
    fprintf(out, "--------------------------------------------------------------------------------\n");
    fprintf(out, "%-8s", "State");
    for (i = 0; i < action_count; i++) {
        fprintf(out, "| %-10s", table_cols[action_cols[i]]);
    }
    for (i = 0; i < goto_count; i++) {
        fprintf(out, "| %-10s", table_cols[goto_cols[i]]);
    }
    fprintf(out, "\n");
    fprintf(out, "--------------------------------------------------------------------------------\n");

    for (state = 0; state <= max_table_state; state++) {
        if (!table_state_seen[state]) {
            continue;
        }
        fprintf(out, "%-8d", state);
        for (i = 0; i < action_count; i++) {
            const char *cell = table_cells[state][action_cols[i]];
            fprintf(out, "| %-10s", (cell[0] != '\0') ? cell : "-");
        }
        for (i = 0; i < goto_count; i++) {
            const char *cell = table_cells[state][goto_cols[i]];
            fprintf(out, "| %-10s", (cell[0] != '\0') ? cell : "-");
        }
        fprintf(out, "\n");
    }
    fprintf(out, "--------------------------------------------------------------------------------\n");
}

static void print_source_context(FILE *out, const char *path, int err_line, int err_col) {
    FILE *fp;
    char buf[1024];
    int line = 0;
    int i;
    int caret_col = (err_col > 0) ? err_col : 1;

    if (!path) {
        return;
    }

    fp = fopen(path, "r");
    if (!fp) {
        return;
    }

    while (fgets(buf, sizeof(buf), fp)) {
        line++;
        if (line == err_line) {
            size_t n = strlen(buf);
            while (n > 0 && (buf[n - 1] == '\n' || buf[n - 1] == '\r')) {
                buf[--n] = '\0';
            }
            fprintf(out, "Source line %d: %s\n", err_line, buf);
            fprintf(out, "             ");
            for (i = 1; i < caret_col; i++) {
                fputc(' ', out);
            }
            fprintf(out, "^\n");
            break;
        }
    }

    fclose(fp);
}

static const char *guess_error_hint(const char *msg, const char *lexeme) {
    if (msg && strstr(msg, "unexpected ELSE")) {
        return "Hint: `else` must follow a complete `if` statement.";
    }
    if (msg && strstr(msg, "expecting SEMICOLON")) {
        return "Hint: a statement/declaration is likely missing ';' before this token.";
    }
    if (msg && strstr(msg, "expecting RPAREN")) {
        return "Hint: check for a missing ')' in this expression or condition.";
    }
    if (msg && strstr(msg, "expecting RBRACE")) {
        return "Hint: check for an unclosed '{' block.";
    }
    if (msg && strstr(msg, "expecting COLON")) {
        return "Hint: in switch-case, `case <expr> :` and `default :` must include ':' .";
    }
    if (msg && strstr(msg, "unexpected $end")) {
        return "Hint: input ended early; check for missing ';', ')', or '}'.";
    }
    if (lexeme && strcmp(lexeme, "+=") == 0) {
        return "Hint: '+=' is unsupported in this language subset; use `x = x + y`.";
    }
    return "Hint: inspect tokens around the caret and compare with grammar rules.";
}

static void emit_diagnostic(FILE *out, const char *msg) {
    int err_line = (last_token_line > 0) ? last_token_line : line_number;
    int err_col = (last_token_col > 0) ? last_token_col : column_number;
    const char *lexeme = (last_lexeme[0] != '\0') ? last_lexeme : "<none>";
    const char *hint = guess_error_hint(msg, lexeme);

    fprintf(out, "\n[ERROR] Syntax error at line %d, col %d\n", err_line, err_col);
    fprintf(out, "Message: %s\n", msg ? msg : "syntax error");
    fprintf(out, "Unexpected token/lexeme: '%s'\n", lexeme);
    print_source_context(out, current_input_path, err_line, err_col);
    fprintf(out, "%s\n", hint);
}

static void log_reduction(const char *rule_text) {
    reduction_index++;
    store_reduction_rule(rule_text);
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

/* Dangling-else conflict resolution */
%precedence IFX
%precedence ELSE

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
    | IF LPAREN expression RPAREN statement %prec IFX    { log_reduction("statement -> if ( expression ) statement"); }
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
    : assignment_expression                              { log_reduction("expression -> assignment_expression"); }
    | expression COMMA assignment_expression             { log_reduction("expression -> expression , assignment_expression"); }
    ;

assignment_expression
    : conditional_expression                             { log_reduction("assignment_expression -> conditional_expression"); }
    | unary_expression ASSIGN assignment_expression      { log_reduction("assignment_expression -> unary_expression = assignment_expression"); }
    ;

constant_expression
    : conditional_expression                             { log_reduction("constant_expression -> conditional_expression"); }
    ;

conditional_expression
    : logical_or_expression                              { log_reduction("conditional_expression -> logical_or_expression"); }
    ;

logical_or_expression
    : logical_and_expression                             { log_reduction("logical_or_expression -> logical_and_expression"); }
    | logical_or_expression LOGICAL_OR logical_and_expression
                                                        { log_reduction("logical_or_expression -> logical_or_expression || logical_and_expression"); }
    ;

logical_and_expression
    : bitwise_or_expression                              { log_reduction("logical_and_expression -> bitwise_or_expression"); }
    | logical_and_expression LOGICAL_AND bitwise_or_expression
                                                        { log_reduction("logical_and_expression -> logical_and_expression && bitwise_or_expression"); }
    ;

bitwise_or_expression
    : bitwise_xor_expression                             { log_reduction("bitwise_or_expression -> bitwise_xor_expression"); }
    | bitwise_or_expression BITWISE_OR bitwise_xor_expression
                                                        { log_reduction("bitwise_or_expression -> bitwise_or_expression | bitwise_xor_expression"); }
    ;

bitwise_xor_expression
    : bitwise_and_expression                             { log_reduction("bitwise_xor_expression -> bitwise_and_expression"); }
    | bitwise_xor_expression BITWISE_XOR bitwise_and_expression
                                                        { log_reduction("bitwise_xor_expression -> bitwise_xor_expression ^ bitwise_and_expression"); }
    ;

bitwise_and_expression
    : equality_expression                                { log_reduction("bitwise_and_expression -> equality_expression"); }
    | bitwise_and_expression BITWISE_AND equality_expression
                                                        { log_reduction("bitwise_and_expression -> bitwise_and_expression & equality_expression"); }
    ;

equality_expression
    : relational_expression                              { log_reduction("equality_expression -> relational_expression"); }
    | equality_expression EQUAL relational_expression    { log_reduction("equality_expression -> equality_expression == relational_expression"); }
    | equality_expression NOT_EQUAL relational_expression { log_reduction("equality_expression -> equality_expression != relational_expression"); }
    ;

relational_expression
    : additive_expression                                { log_reduction("relational_expression -> additive_expression"); }
    | relational_expression LESS_THAN additive_expression { log_reduction("relational_expression -> relational_expression < additive_expression"); }
    | relational_expression GREATER_THAN additive_expression { log_reduction("relational_expression -> relational_expression > additive_expression"); }
    | relational_expression LESS_EQUAL additive_expression { log_reduction("relational_expression -> relational_expression <= additive_expression"); }
    | relational_expression GREATER_EQUAL additive_expression { log_reduction("relational_expression -> relational_expression >= additive_expression"); }
    | relational_expression SPACESHIP additive_expression { log_reduction("relational_expression -> relational_expression <=> additive_expression"); }
    ;

additive_expression
    : multiplicative_expression                          { log_reduction("additive_expression -> multiplicative_expression"); }
    | additive_expression PLUS multiplicative_expression { log_reduction("additive_expression -> additive_expression + multiplicative_expression"); }
    | additive_expression MINUS multiplicative_expression { log_reduction("additive_expression -> additive_expression - multiplicative_expression"); }
    ;

multiplicative_expression
    : unary_expression                                   { log_reduction("multiplicative_expression -> unary_expression"); }
    | multiplicative_expression MULTIPLY unary_expression { log_reduction("multiplicative_expression -> multiplicative_expression * unary_expression"); }
    | multiplicative_expression DIVIDE unary_expression  { log_reduction("multiplicative_expression -> multiplicative_expression / unary_expression"); }
    | multiplicative_expression MODULO unary_expression  { log_reduction("multiplicative_expression -> multiplicative_expression % unary_expression"); }
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
    emit_diagnostic(stderr, s);
    if (report_fp) {
        emit_diagnostic(report_fp, s);
        fflush(report_fp);
    }
    return 0;
}

int main(int argc, char **argv) {
    int result;
    const char *input_path = NULL;
    const char *report_path = "derivation_report.txt";
    const char *automaton_path = "lalr_assignment3_resolved.output";

    if (argc >= 2) {
        input_path = argv[1];
        current_input_path = input_path;
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

    parse_output_and_build_table(automaton_path);
    print_parsing_table_matrix(stdout);
    if (report_fp) {
        print_parsing_table_matrix(report_fp);
        fflush(report_fp);
    }

    result = yyparse();
    if (result == 0) {
        printf("\nResult: ACCEPTED\n");
        print_reverse_derivation(stdout);
        if (report_fp) {
            fprintf(report_fp, "\nResult: ACCEPTED\n");
            print_reverse_derivation(report_fp);
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
    free_reduction_rules();

    return result;
}
