%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex(void);
int yyerror(const char *s);
extern FILE *yyin;
extern int line_number;
extern int column_number;
extern char last_lexeme[];
extern int last_token_line;
extern int last_token_col;

#define MAX_TEXT 128

typedef struct {
    char op[24];
    char arg1[MAX_TEXT];
    char arg2[MAX_TEXT];
    char result[MAX_TEXT];
} Quad;

typedef struct IRNode {
    Quad *quads;
    int count;
    int cap;
    char place[MAX_TEXT];
    int has_place;
} IRNode;

static IRNode *final_ir = NULL;
static int temp_counter = 0;
static int label_counter = 0;
static int had_error = 0;
static char error_log[4096] = "";

static char *xstrdup(const char *s) {
    size_t n;
    char *p;
    if (!s) {
        return NULL;
    }
    n = strlen(s);
    p = (char *)malloc(n + 1);
    if (!p) {
        fprintf(stderr, "Fatal: out of memory.\n");
        exit(1);
    }
    memcpy(p, s, n + 1);
    return p;
}

static IRNode *node_new(void) {
    IRNode *n = (IRNode *)calloc(1, sizeof(IRNode));
    if (!n) {
        fprintf(stderr, "Fatal: out of memory.\n");
        exit(1);
    }
    return n;
}

static IRNode *node_from_place(const char *p) {
    IRNode *n = node_new();
    if (p && p[0] != '\0') {
        snprintf(n->place, sizeof(n->place), "%s", p);
        n->has_place = 1;
    }
    return n;
}

static void node_reserve(IRNode *n, int need) {
    int new_cap;
    Quad *new_quads;
    if (!n) {
        return;
    }
    if (n->cap >= need) {
        return;
    }
    new_cap = (n->cap == 0) ? 32 : n->cap;
    while (new_cap < need) {
        new_cap *= 2;
    }
    new_quads = (Quad *)realloc(n->quads, (size_t)new_cap * sizeof(Quad));
    if (!new_quads) {
        fprintf(stderr, "Fatal: out of memory while growing IR.\n");
        exit(1);
    }
    n->quads = new_quads;
    n->cap = new_cap;
}

static void node_emit(IRNode *n, const char *op, const char *a1, const char *a2, const char *res) {
    Quad *q;
    if (!n) {
        return;
    }
    node_reserve(n, n->count + 1);
    q = &n->quads[n->count++];
    snprintf(q->op, sizeof(q->op), "%s", op ? op : "");
    snprintf(q->arg1, sizeof(q->arg1), "%s", a1 ? a1 : "");
    snprintf(q->arg2, sizeof(q->arg2), "%s", a2 ? a2 : "");
    snprintf(q->result, sizeof(q->result), "%s", res ? res : "");
}

static void node_append(IRNode *dst, const IRNode *src) {
    int i;
    if (!dst || !src || src->count == 0) {
        return;
    }
    node_reserve(dst, dst->count + src->count);
    for (i = 0; i < src->count; i++) {
        dst->quads[dst->count++] = src->quads[i];
    }
}

static char *new_temp(void) {
    char buf[32];
    snprintf(buf, sizeof(buf), "t%d", ++temp_counter);
    return xstrdup(buf);
}

static char *new_label(void) {
    char buf[32];
    snprintf(buf, sizeof(buf), "L%d", ++label_counter);
    return xstrdup(buf);
}

static IRNode *pass_node(IRNode *n) {
    return n ? n : node_new();
}

static IRNode *make_binary(IRNode *l, const char *op, IRNode *r) {
    IRNode *out = node_new();
    char *t = new_temp();
    node_append(out, l);
    node_append(out, r);
    node_emit(out, op, l && l->has_place ? l->place : "", r && r->has_place ? r->place : "", t);
    snprintf(out->place, sizeof(out->place), "%s", t);
    out->has_place = 1;
    free(t);
    return out;
}

static IRNode *make_unary(const char *op, IRNode *e) {
    IRNode *out = node_new();
    char *t = new_temp();
    node_append(out, e);
    node_emit(out, op, e && e->has_place ? e->place : "", "", t);
    snprintf(out->place, sizeof(out->place), "%s", t);
    out->has_place = 1;
    free(t);
    return out;
}

static IRNode *make_assign(IRNode *lhs, IRNode *rhs) {
    IRNode *out = node_new();
    node_append(out, lhs);
    node_append(out, rhs);
    node_emit(out, "=", rhs && rhs->has_place ? rhs->place : "", "", lhs && lhs->has_place ? lhs->place : "");
    if (rhs && rhs->has_place) {
        snprintf(out->place, sizeof(out->place), "%s", rhs->place);
        out->has_place = 1;
    }
    return out;
}

static void print_quads(FILE *out, const IRNode *n) {
    int i;

    fprintf(out, "\nGenerated Intermediate Code (Three Address Code - Quadruples)\n");
  fprintf(out, "-----------------------------------------------------------------------\n");
  fprintf(out, "%-6s | %-12s | %-12s | %-12s | %-12s\n", "row", "op", "arg1", "arg2", "result");
  fprintf(out, "-----------------------------------------------------------------------\n");
    if (!n || n->count == 0) {
        fprintf(out, "(no quadruples generated)\n");
        return;
    }
    for (i = 0; i < n->count; i++) {
      fprintf(out, "%-6d | %-12s | %-12s | %-12s | %-12s\n",
        i,
        n->quads[i].op,
        n->quads[i].arg1,
        n->quads[i].arg2,
        n->quads[i].result);
    }
}

static void print_source(FILE *out, const char *path) {
    FILE *fp;
    char buf[1024];
    if (!path) {
        fprintf(out, "Input Source Program\n");
        fprintf(out, "--------------------\n");
        fprintf(out, "(stdin input was used)\n");
        return;
    }
    fp = fopen(path, "r");
    if (!fp) {
        fprintf(out, "Input Source Program\n");
        fprintf(out, "--------------------\n");
        fprintf(out, "(could not open source file: %s)\n", path);
        return;
    }
    fprintf(out, "Input Source Program\n");
    fprintf(out, "--------------------\n");
    while (fgets(buf, sizeof(buf), fp)) {
        fputs(buf, out);
    }
    fclose(fp);
}

static const char *guess_error_hint(const char *msg, const char *lexeme) {
    if (lexeme && strcmp(lexeme, "switch") == 0) {
        return "Hint: switch-case TAC is not implemented in this Assignment 4 solution.";
    }
    if (lexeme && strcmp(lexeme, "do") == 0) {
        return "Hint: do-while TAC is not implemented in this Assignment 4 solution.";
    }
    if (msg && strstr(msg, "expecting SEMICOLON")) {
        return "Hint: a statement/declaration is likely missing ';'.";
    }
    if (msg && strstr(msg, "expecting RPAREN")) {
        return "Hint: check for a missing ')' in an expression or condition.";
    }
    if (msg && strstr(msg, "expecting RBRACE")) {
        return "Hint: check for an unclosed '{' block.";
    }
    return "Hint: inspect the token near the reported line/column.";
}

  static void record_error(const char *msg) {
    if (!msg || msg[0] == '\0') {
      return;
    }

    if (error_log[0] == '\0') {
      snprintf(error_log, sizeof(error_log), "%s", msg);
      return;
    }

    if (strlen(error_log) + strlen(msg) + 2 < sizeof(error_log)) {
      strcat(error_log, "\n");
      strcat(error_log, msg);
    }
  }
%}

%define parse.error verbose

%code requires {
typedef struct IRNode IRNode;
}

%union {
    char *str;
    IRNode *node;
}

%start program

%token INT LONG SHORT FLOAT DOUBLE VOID CHAR STRUCT EXTERN
%token IF ELSE SWITCH CASE DEFAULT FOR WHILE DO BREAK CONTINUE RETURN SIZEOF

%token <str> IDENTIFIER INTEGER_CONSTANT HEX_CONSTANT FLOAT_CONSTANT CHAR_CONSTANT STRING_LITERAL

%token PLUS MINUS MULTIPLY DIVIDE MODULO
%token LESS_THAN GREATER_THAN LESS_EQUAL GREATER_EQUAL EQUAL NOT_EQUAL
%token LOGICAL_AND LOGICAL_OR
%token BITWISE_AND BITWISE_OR BITWISE_XOR BITWISE_NOT
%token ASSIGN INCREMENT DECREMENT
%token DOT ARROW SPACESHIP

%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET
%token SEMICOLON COMMA COLON

%precedence IFX
%precedence ELSE

%type <node> program external_list external function_definition declaration
%type <node> init_declarator_list_opt init_declarator_list init_declarator initializer
%type <node> declarator pointer_opt pointer direct_declarator
%type <node> parameter_list_opt parameter_list parameter_declaration
%type <node> compound_statement block_item_list_opt block_item_list block_item
%type <node> statement simple_statement expr_opt
%type <node> expression assignment_expression constant_expression conditional_expression
%type <node> logical_or_expression logical_and_expression bitwise_or_expression
%type <node> bitwise_xor_expression bitwise_and_expression equality_expression
%type <node> relational_expression additive_expression multiplicative_expression
%type <node> unary_expression postfix_expression argument_expression_list_opt
%type <node> argument_expression_list primary_expression constant string_literal_sequence
%type <node> type_specifier

%%

program
    : external_list {
        final_ir = $1;
        $$ = $1;
      }
    ;

external_list
    : external_list external {
        $$ = node_new();
        node_append($$, $1);
        node_append($$, $2);
      }
    | external {
        $$ = pass_node($1);
      }
    ;

external
    : function_definition {
        $$ = pass_node($1);
      }
    | declaration SEMICOLON {
        $$ = pass_node($1);
      }
    ;

function_definition
    : type_specifier declarator compound_statement {
        $$ = node_new();
        node_append($$, $3);
      }
    | EXTERN type_specifier declarator compound_statement {
        $$ = node_new();
        node_append($$, $4);
      }
    ;

declaration
    : type_specifier init_declarator_list_opt {
        $$ = pass_node($2);
      }
    ;

init_declarator_list_opt
    : init_declarator_list {
        $$ = pass_node($1);
      }
    | /* empty */ {
        $$ = node_new();
      }
    ;

init_declarator_list
    : init_declarator {
        $$ = pass_node($1);
      }
    | init_declarator_list COMMA init_declarator {
        $$ = node_new();
        node_append($$, $1);
        node_append($$, $3);
      }
    ;

init_declarator
    : declarator {
        $$ = pass_node($1);
      }
    | declarator ASSIGN initializer {
        $$ = make_assign($1, $3);
      }
    ;

initializer
    : assignment_expression {
        $$ = pass_node($1);
      }
    ;

type_specifier
    : INT { $$ = node_new(); }
    | LONG { $$ = node_new(); }
    | SHORT { $$ = node_new(); }
    | FLOAT { $$ = node_new(); }
    | DOUBLE { $$ = node_new(); }
    | VOID { $$ = node_new(); }
    | CHAR { $$ = node_new(); }
    | STRUCT IDENTIFIER {
        $$ = node_new();
        free($2);
      }
    ;

declarator
    : pointer_opt direct_declarator {
        $$ = pass_node($2);
      }
    ;

pointer_opt
    : pointer {
        $$ = pass_node($1);
      }
    | /* empty */ {
        $$ = node_new();
      }
    ;

pointer
    : MULTIPLY {
        $$ = node_new();
      }
    | MULTIPLY pointer {
        $$ = pass_node($2);
      }
    ;

direct_declarator
    : IDENTIFIER {
        $$ = node_from_place($1);
        free($1);
      }
    | IDENTIFIER LPAREN parameter_list_opt RPAREN {
        $$ = node_from_place($1);
        free($1);
      }
    | LPAREN declarator RPAREN {
        $$ = pass_node($2);
      }
    ;

parameter_list_opt
    : parameter_list {
        $$ = pass_node($1);
      }
    | /* empty */ {
        $$ = node_new();
      }
    ;

parameter_list
    : parameter_declaration {
        $$ = pass_node($1);
      }
    | parameter_list COMMA parameter_declaration {
        $$ = node_new();
        node_append($$, $1);
        node_append($$, $3);
      }
    ;

parameter_declaration
    : type_specifier declarator {
        $$ = pass_node($2);
      }
    ;

compound_statement
    : LBRACE block_item_list_opt RBRACE {
        $$ = pass_node($2);
      }
    ;

block_item_list_opt
    : block_item_list {
        $$ = pass_node($1);
      }
    | /* empty */ {
        $$ = node_new();
      }
    ;

block_item_list
    : block_item {
        $$ = pass_node($1);
      }
    | block_item_list block_item {
        $$ = node_new();
        node_append($$, $1);
        node_append($$, $2);
      }
    ;

block_item
    : declaration SEMICOLON {
        $$ = pass_node($1);
      }
    | statement {
        $$ = pass_node($1);
      }
    ;

statement
    : simple_statement {
        $$ = pass_node($1);
      }
    | compound_statement {
        $$ = pass_node($1);
      }
    | IF LPAREN expression RPAREN statement %prec IFX {
        IRNode *out = node_new();
        char *lend = new_label();
        node_append(out, $3);
        node_emit(out, "iffalse", ($3 && $3->has_place) ? $3->place : "", "", lend);
        node_append(out, $5);
        node_emit(out, "label", "", "", lend);
        free(lend);
        $$ = out;
      }
    | IF LPAREN expression RPAREN statement ELSE statement {
        IRNode *out = node_new();
        char *lelse = new_label();
        char *lend = new_label();
        node_append(out, $3);
        node_emit(out, "iffalse", ($3 && $3->has_place) ? $3->place : "", "", lelse);
        node_append(out, $5);
        node_emit(out, "goto", "", "", lend);
        node_emit(out, "label", "", "", lelse);
        node_append(out, $7);
        node_emit(out, "label", "", "", lend);
        free(lelse);
        free(lend);
        $$ = out;
      }
    | WHILE LPAREN expression RPAREN statement {
        IRNode *out = node_new();
        char *lstart = new_label();
        char *lend = new_label();
        node_emit(out, "label", "", "", lstart);
        node_append(out, $3);
        node_emit(out, "iffalse", ($3 && $3->has_place) ? $3->place : "", "", lend);
        node_append(out, $5);
        node_emit(out, "goto", "", "", lstart);
        node_emit(out, "label", "", "", lend);
        free(lstart);
        free(lend);
        $$ = out;
      }
    | FOR LPAREN expr_opt SEMICOLON expr_opt SEMICOLON expr_opt RPAREN statement {
        IRNode *out = node_new();
        char *lstart = new_label();
        char *lend = new_label();
        node_append(out, $3);
        node_emit(out, "label", "", "", lstart);
        node_append(out, $5);
        if ($5 && $5->has_place) {
            node_emit(out, "iffalse", $5->place, "", lend);
        }
        node_append(out, $9);
        node_append(out, $7);
        node_emit(out, "goto", "", "", lstart);
        node_emit(out, "label", "", "", lend);
        free(lstart);
        free(lend);
        $$ = out;
      }
    | DO statement WHILE LPAREN expression RPAREN SEMICOLON {
        yyerror("unsupported construct: do-while loop");
        $$ = node_new();
      }
    | SWITCH LPAREN expression RPAREN LBRACE RBRACE {
        yyerror("unsupported construct: switch statement");
        $$ = node_new();
      }
    ;

simple_statement
    : expr_opt SEMICOLON {
        $$ = pass_node($1);
      }
    | BREAK SEMICOLON {
        $$ = node_new();
        node_emit($$, "break", "", "", "");
      }
    | CONTINUE SEMICOLON {
        $$ = node_new();
        node_emit($$, "continue", "", "", "");
      }
    | RETURN expr_opt SEMICOLON {
        $$ = node_new();
        node_append($$, $2);
        node_emit($$, "return", ($2 && $2->has_place) ? $2->place : "", "", "");
      }
    ;

expr_opt
    : expression {
        $$ = pass_node($1);
      }
    | /* empty */ {
        $$ = node_new();
      }
    ;

expression
    : assignment_expression {
        $$ = pass_node($1);
      }
    | expression COMMA assignment_expression {
        $$ = node_new();
        node_append($$, $1);
        node_append($$, $3);
        if ($3 && $3->has_place) {
            snprintf($$->place, sizeof($$->place), "%s", $3->place);
            $$->has_place = 1;
        }
      }
    ;

assignment_expression
    : conditional_expression {
        $$ = pass_node($1);
      }
    | unary_expression ASSIGN assignment_expression {
        $$ = make_assign($1, $3);
      }
    ;

constant_expression
    : conditional_expression {
        $$ = pass_node($1);
      }
    ;

conditional_expression
    : logical_or_expression {
        $$ = pass_node($1);
      }
    ;

logical_or_expression
    : logical_and_expression {
        $$ = pass_node($1);
      }
    | logical_or_expression LOGICAL_OR logical_and_expression {
        $$ = make_binary($1, "||", $3);
      }
    ;

logical_and_expression
    : bitwise_or_expression {
        $$ = pass_node($1);
      }
    | logical_and_expression LOGICAL_AND bitwise_or_expression {
        $$ = make_binary($1, "&&", $3);
      }
    ;

bitwise_or_expression
    : bitwise_xor_expression {
        $$ = pass_node($1);
      }
    | bitwise_or_expression BITWISE_OR bitwise_xor_expression {
        $$ = make_binary($1, "|", $3);
      }
    ;

bitwise_xor_expression
    : bitwise_and_expression {
        $$ = pass_node($1);
      }
    | bitwise_xor_expression BITWISE_XOR bitwise_and_expression {
        $$ = make_binary($1, "^", $3);
      }
    ;

bitwise_and_expression
    : equality_expression {
        $$ = pass_node($1);
      }
    | bitwise_and_expression BITWISE_AND equality_expression {
        $$ = make_binary($1, "&", $3);
      }
    ;

equality_expression
    : relational_expression {
        $$ = pass_node($1);
      }
    | equality_expression EQUAL relational_expression {
        $$ = make_binary($1, "==", $3);
      }
    | equality_expression NOT_EQUAL relational_expression {
        $$ = make_binary($1, "!=", $3);
      }
    ;

relational_expression
    : additive_expression {
        $$ = pass_node($1);
      }
    | relational_expression LESS_THAN additive_expression {
        $$ = make_binary($1, "<", $3);
      }
    | relational_expression GREATER_THAN additive_expression {
        $$ = make_binary($1, ">", $3);
      }
    | relational_expression LESS_EQUAL additive_expression {
        $$ = make_binary($1, "<=", $3);
      }
    | relational_expression GREATER_EQUAL additive_expression {
        $$ = make_binary($1, ">=", $3);
      }
    | relational_expression SPACESHIP additive_expression {
        $$ = make_binary($1, "<=>", $3);
      }
    ;

additive_expression
    : multiplicative_expression {
        $$ = pass_node($1);
      }
    | additive_expression PLUS multiplicative_expression {
        $$ = make_binary($1, "+", $3);
      }
    | additive_expression MINUS multiplicative_expression {
        $$ = make_binary($1, "-", $3);
      }
    ;

multiplicative_expression
    : unary_expression {
        $$ = pass_node($1);
      }
    | multiplicative_expression MULTIPLY unary_expression {
        $$ = make_binary($1, "*", $3);
      }
    | multiplicative_expression DIVIDE unary_expression {
        $$ = make_binary($1, "/", $3);
      }
    | multiplicative_expression MODULO unary_expression {
        $$ = make_binary($1, "%", $3);
      }
    ;

unary_expression
    : postfix_expression {
        $$ = pass_node($1);
      }
    | INCREMENT unary_expression {
        $$ = node_new();
        node_append($$, $2);
        node_emit($$, "+", ($2 && $2->has_place) ? $2->place : "", "1", ($2 && $2->has_place) ? $2->place : "");
        if ($2 && $2->has_place) {
            snprintf($$->place, sizeof($$->place), "%s", $2->place);
            $$->has_place = 1;
        }
      }
    | DECREMENT unary_expression {
        $$ = node_new();
        node_append($$, $2);
        node_emit($$, "-", ($2 && $2->has_place) ? $2->place : "", "1", ($2 && $2->has_place) ? $2->place : "");
        if ($2 && $2->has_place) {
            snprintf($$->place, sizeof($$->place), "%s", $2->place);
            $$->has_place = 1;
        }
      }
    | PLUS unary_expression {
        $$ = pass_node($2);
      }
    | MINUS unary_expression {
        $$ = make_unary("minus", $2);
      }
    | BITWISE_NOT unary_expression {
        $$ = make_unary("~", $2);
      }
    | BITWISE_AND unary_expression {
        $$ = make_unary("addr", $2);
      }
    | MULTIPLY unary_expression {
        $$ = make_unary("deref", $2);
      }
    | SIZEOF unary_expression {
        $$ = make_unary("sizeof", $2);
      }
    | SIZEOF LPAREN type_specifier RPAREN {
        $$ = node_from_place("sizeof(type)");
      }
    ;

postfix_expression
    : primary_expression {
        $$ = pass_node($1);
      }
    | postfix_expression LBRACKET expression RBRACKET {
        $$ = node_new();
        node_append($$, $1);
        node_append($$, $3);
        {
            char *t = new_temp();
            node_emit($$, "[]", ($1 && $1->has_place) ? $1->place : "", ($3 && $3->has_place) ? $3->place : "", t);
            snprintf($$->place, sizeof($$->place), "%s", t);
            $$->has_place = 1;
            free(t);
        }
      }
    | postfix_expression LPAREN argument_expression_list_opt RPAREN {
        $$ = node_new();
        node_append($$, $1);
        node_append($$, $3);
        node_emit($$, "call", ($1 && $1->has_place) ? $1->place : "", "", "");
        {
            char *t = new_temp();
            node_emit($$, "ret", "", "", t);
            snprintf($$->place, sizeof($$->place), "%s", t);
            $$->has_place = 1;
            free(t);
        }
      }
    | postfix_expression DOT IDENTIFIER {
        $$ = node_new();
        node_append($$, $1);
        {
            char *t = new_temp();
            node_emit($$, ".", ($1 && $1->has_place) ? $1->place : "", $3, t);
            snprintf($$->place, sizeof($$->place), "%s", t);
            $$->has_place = 1;
            free(t);
        }
        free($3);
      }
    | postfix_expression ARROW IDENTIFIER {
        $$ = node_new();
        node_append($$, $1);
        {
            char *t = new_temp();
            node_emit($$, "->", ($1 && $1->has_place) ? $1->place : "", $3, t);
            snprintf($$->place, sizeof($$->place), "%s", t);
            $$->has_place = 1;
            free(t);
        }
        free($3);
      }
    | postfix_expression INCREMENT {
        $$ = node_new();
        node_append($$, $1);
        if ($1 && $1->has_place) {
            char *t = new_temp();
            node_emit($$, "=", $1->place, "", t);
            node_emit($$, "+", $1->place, "1", $1->place);
            snprintf($$->place, sizeof($$->place), "%s", t);
            $$->has_place = 1;
            free(t);
        }
      }
    | postfix_expression DECREMENT {
        $$ = node_new();
        node_append($$, $1);
        if ($1 && $1->has_place) {
            char *t = new_temp();
            node_emit($$, "=", $1->place, "", t);
            node_emit($$, "-", $1->place, "1", $1->place);
            snprintf($$->place, sizeof($$->place), "%s", t);
            $$->has_place = 1;
            free(t);
        }
      }
    ;

argument_expression_list_opt
    : argument_expression_list {
        $$ = pass_node($1);
      }
    | /* empty */ {
        $$ = node_new();
      }
    ;

argument_expression_list
    : assignment_expression {
        $$ = node_new();
        node_append($$, $1);
        node_emit($$, "param", ($1 && $1->has_place) ? $1->place : "", "", "");
      }
    | argument_expression_list COMMA assignment_expression {
        $$ = pass_node($1);
        node_append($$, $3);
        node_emit($$, "param", ($3 && $3->has_place) ? $3->place : "", "", "");
      }
    ;

primary_expression
    : IDENTIFIER {
        $$ = node_from_place($1);
        free($1);
      }
    | constant {
        $$ = pass_node($1);
      }
    | string_literal_sequence {
        $$ = pass_node($1);
      }
    | LPAREN expression RPAREN {
        $$ = pass_node($2);
      }
    ;

constant
    : INTEGER_CONSTANT {
        $$ = node_from_place($1);
        free($1);
      }
    | HEX_CONSTANT {
        $$ = node_from_place($1);
        free($1);
      }
    | FLOAT_CONSTANT {
        $$ = node_from_place($1);
        free($1);
      }
    | CHAR_CONSTANT {
        $$ = node_from_place($1);
        free($1);
      }
    ;

string_literal_sequence
    : STRING_LITERAL {
        $$ = node_from_place($1);
        free($1);
      }
    | string_literal_sequence STRING_LITERAL {
        $$ = pass_node($1);
        if ($$ && $$->has_place) {
            size_t need = strlen($$->place) + strlen($2) + 1;
            char *buf = (char *)malloc(need + 1);
            if (!buf) {
                fprintf(stderr, "Fatal: out of memory while joining strings.\n");
                exit(1);
            }
            snprintf(buf, need + 1, "%s%s", $$->place, $2);
            snprintf($$->place, sizeof($$->place), "%s", buf);
            free(buf);
        }
        free($2);
      }
    ;

%%

int yyerror(const char *s) {
    int err_line = (last_token_line > 0) ? last_token_line : line_number;
    int err_col = (last_token_col > 0) ? last_token_col : column_number;
    const char *lexeme = (last_lexeme[0] != '\0') ? last_lexeme : "<none>";
    const char *hint = guess_error_hint(s, lexeme);
  char formatted[1024];
    had_error = 1;

    fprintf(stderr, "[ERROR] line %d, col %d\n", err_line, err_col);
    fprintf(stderr, "Message: %s\n", s ? s : "syntax error");
    fprintf(stderr, "Unexpected token/lexeme: '%s'\n", lexeme);
    fprintf(stderr, "%s\n", hint);

  snprintf(formatted,
       sizeof(formatted),
       "[ERROR] line %d, col %d\nMessage: %s\nUnexpected token/lexeme: '%s'\n%s",
       err_line,
       err_col,
       s ? s : "syntax error",
       lexeme,
       hint);
  record_error(formatted);
    return 0;
}

int main(int argc, char **argv) {
    const char *input_path = NULL;
    const char *report_path = "ir_report.txt";
    FILE *report_fp = NULL;
    int parse_result;

    if (argc >= 2) {
        input_path = argv[1];
    }
    if (argc >= 3) {
        report_path = argv[2];
    }

    if (input_path) {
        yyin = fopen(input_path, "r");
        if (!yyin) {
            fprintf(stderr, "Error: cannot open input file '%s'\n", input_path);
            return 1;
        }
    }

    report_fp = fopen(report_path, "w");
    if (!report_fp) {
        fprintf(stderr, "Warning: cannot open report file '%s'\n", report_path);
    }

    printf("CS327 Assignment 4 - Intermediate Code Generation\n");
    printf("No optimization is applied.\n\n");
    print_source(stdout, input_path);

    if (report_fp) {
        fprintf(report_fp, "CS327 Assignment 4 - Intermediate Code Generation\n");
        fprintf(report_fp, "No optimization is applied.\n\n");
        print_source(report_fp, input_path);
    }

    parse_result = yyparse();

    if (parse_result == 0 && !had_error) {
        print_quads(stdout, final_ir);
        printf("\nResult: ACCEPTED\n");
        if (report_fp) {
            print_quads(report_fp, final_ir);
            fprintf(report_fp, "\nResult: ACCEPTED\n");
        }
    } else {
        printf("\nResult: REJECTED\n");
      if (error_log[0] != '\0') {
        printf("\nDiagnostics\n-----------\n%s\n", error_log);
      } else {
        printf("\nDiagnostics\n-----------\n[ERROR] parsing failed due to invalid or unsupported input.\n");
      }
        if (report_fp) {
            fprintf(report_fp, "\nResult: REJECTED\n");
        if (error_log[0] != '\0') {
          fprintf(report_fp, "\nDiagnostics\n-----------\n%s\n", error_log);
        } else {
          fprintf(report_fp, "\nDiagnostics\n-----------\n[ERROR] parsing failed due to invalid or unsupported input.\n");
        }
        }
    }

    if (yyin && input_path) {
        fclose(yyin);
    }
    if (report_fp) {
        fclose(report_fp);
    }
    return (parse_result == 0 && !had_error) ? 0 : 1;
}
