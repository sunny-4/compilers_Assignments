/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "ir_codegen.y"

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

#line 319 "ir_codegen.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_IR_CODEGEN_TAB_H_INCLUDED
# define YY_YY_IR_CODEGEN_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 252 "ir_codegen.y"

typedef struct IRNode IRNode;

#line 366 "ir_codegen.tab.c"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    LONG = 259,
    SHORT = 260,
    FLOAT = 261,
    DOUBLE = 262,
    VOID = 263,
    CHAR = 264,
    STRUCT = 265,
    EXTERN = 266,
    IF = 267,
    ELSE = 268,
    SWITCH = 269,
    CASE = 270,
    DEFAULT = 271,
    FOR = 272,
    WHILE = 273,
    DO = 274,
    BREAK = 275,
    CONTINUE = 276,
    RETURN = 277,
    SIZEOF = 278,
    IDENTIFIER = 279,
    INTEGER_CONSTANT = 280,
    HEX_CONSTANT = 281,
    FLOAT_CONSTANT = 282,
    CHAR_CONSTANT = 283,
    STRING_LITERAL = 284,
    PLUS = 285,
    MINUS = 286,
    MULTIPLY = 287,
    DIVIDE = 288,
    MODULO = 289,
    LESS_THAN = 290,
    GREATER_THAN = 291,
    LESS_EQUAL = 292,
    GREATER_EQUAL = 293,
    EQUAL = 294,
    NOT_EQUAL = 295,
    LOGICAL_AND = 296,
    LOGICAL_OR = 297,
    BITWISE_AND = 298,
    BITWISE_OR = 299,
    BITWISE_XOR = 300,
    BITWISE_NOT = 301,
    ASSIGN = 302,
    INCREMENT = 303,
    DECREMENT = 304,
    DOT = 305,
    ARROW = 306,
    SPACESHIP = 307,
    LPAREN = 308,
    RPAREN = 309,
    LBRACE = 310,
    RBRACE = 311,
    LBRACKET = 312,
    RBRACKET = 313,
    SEMICOLON = 314,
    COMMA = 315,
    COLON = 316,
    IFX = 317
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 256 "ir_codegen.y"

    char *str;
    IRNode *node;

#line 445 "ir_codegen.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_IR_CODEGEN_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  18
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   332

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  120
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  208

#define YYUNDEFTOK  2
#define YYMAXUTOK   317


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   298,   298,   305,   310,   316,   319,   325,   329,   336,
     342,   345,   351,   354,   362,   365,   371,   377,   378,   379,
     380,   381,   382,   383,   384,   391,   397,   400,   406,   409,
     415,   419,   423,   429,   432,   438,   441,   449,   455,   461,
     464,   470,   473,   481,   484,   490,   493,   496,   506,   521,
     535,   553,   557,   564,   567,   571,   575,   583,   586,   592,
     595,   607,   610,   622,   628,   631,   637,   640,   646,   649,
     655,   658,   664,   667,   673,   676,   679,   685,   688,   691,
     694,   697,   700,   706,   709,   712,   718,   721,   724,   727,
     733,   736,   745,   754,   757,   760,   763,   766,   769,   772,
     778,   781,   793,   806,   818,   830,   842,   857,   860,   866,
     871,   879,   883,   886,   889,   895,   899,   903,   907,   914,
     918
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "LONG", "SHORT", "FLOAT",
  "DOUBLE", "VOID", "CHAR", "STRUCT", "EXTERN", "IF", "ELSE", "SWITCH",
  "CASE", "DEFAULT", "FOR", "WHILE", "DO", "BREAK", "CONTINUE", "RETURN",
  "SIZEOF", "IDENTIFIER", "INTEGER_CONSTANT", "HEX_CONSTANT",
  "FLOAT_CONSTANT", "CHAR_CONSTANT", "STRING_LITERAL", "PLUS", "MINUS",
  "MULTIPLY", "DIVIDE", "MODULO", "LESS_THAN", "GREATER_THAN",
  "LESS_EQUAL", "GREATER_EQUAL", "EQUAL", "NOT_EQUAL", "LOGICAL_AND",
  "LOGICAL_OR", "BITWISE_AND", "BITWISE_OR", "BITWISE_XOR", "BITWISE_NOT",
  "ASSIGN", "INCREMENT", "DECREMENT", "DOT", "ARROW", "SPACESHIP",
  "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACKET", "RBRACKET",
  "SEMICOLON", "COMMA", "COLON", "IFX", "$accept", "program",
  "external_list", "external", "function_definition", "declaration",
  "init_declarator_list_opt", "init_declarator_list", "init_declarator",
  "initializer", "type_specifier", "declarator", "pointer_opt", "pointer",
  "direct_declarator", "parameter_list_opt", "parameter_list",
  "parameter_declaration", "compound_statement", "block_item_list_opt",
  "block_item_list", "block_item", "statement", "simple_statement",
  "expr_opt", "expression", "assignment_expression",
  "conditional_expression", "logical_or_expression",
  "logical_and_expression", "bitwise_or_expression",
  "bitwise_xor_expression", "bitwise_and_expression",
  "equality_expression", "relational_expression", "additive_expression",
  "multiplicative_expression", "unary_expression", "postfix_expression",
  "argument_expression_list_opt", "argument_expression_list",
  "primary_expression", "constant", "string_literal_sequence", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317
};
# endif

#define YYPACT_NINF (-75)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-59)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      62,   -75,   -75,   -75,   -75,   -75,   -75,   -75,    19,   137,
      38,    62,   -75,   -75,   -12,   -15,   -75,    18,   -75,   -75,
     -75,    18,   -75,    -3,   -75,   -29,    -8,   -75,    25,   -75,
      18,   248,   171,   -75,    -1,    18,   -75,   -75,   -75,    13,
     279,   -75,   -75,   -75,   -75,   -75,   -75,   248,   248,   248,
     248,   248,   248,   248,   248,   -75,   -75,   -75,    41,    66,
      50,    54,    68,    46,    26,    58,    64,    65,    71,   -75,
     -75,    84,    63,    70,    72,    76,   215,    59,    73,   248,
      89,   -15,   -75,    75,   171,   -75,   -75,   -75,    90,    91,
     -75,   137,    96,     5,   -75,   -75,   -75,   -75,   -75,   -75,
     -75,   -75,   -35,   248,   248,   248,   248,   248,   248,   248,
     248,   248,   248,   248,   248,   248,   248,   248,   248,   248,
     248,   -75,   -75,   128,   129,   248,   248,   -75,   248,   248,
     248,   248,   136,   -75,   -75,   123,   -75,   -75,   -75,   -75,
     248,    18,   130,   126,   -75,   -75,   133,   -75,    66,   -75,
      50,    54,    68,    46,    26,    26,    58,    58,    58,    58,
      58,    64,    64,   -75,   -75,   -75,   -75,   -75,   -75,   -75,
     150,   145,   -38,   -33,   -14,   147,    -5,   154,   -75,   -75,
     -75,   -75,   137,   -75,   -75,   248,   -75,   215,   153,   248,
     215,   248,   -75,   -75,   196,   155,   151,   -75,    27,   215,
     -75,   248,   156,   -75,   158,   -75,   215,   -75
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    17,    18,    19,    20,    21,    22,    23,     0,     0,
       0,     2,     4,     5,     0,    27,    24,    27,     1,     3,
       6,    28,     9,    10,    12,    14,     0,    26,     0,    29,
      27,     0,    40,     7,    30,    27,    25,     8,    13,    14,
       0,   111,   115,   116,   117,   118,   119,     0,     0,     0,
       0,     0,     0,     0,     0,    15,    16,    61,    63,    64,
      66,    68,    70,    72,    74,    77,    83,    86,    90,   100,
     112,   113,     0,     0,     0,     0,    58,     0,     0,    58,
       0,    27,    46,     0,    39,    41,    44,    45,     0,    57,
      59,    34,     0,     0,    98,    93,    94,    97,    96,    95,
      91,    92,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   105,   106,     0,     0,   108,     0,   120,     0,     0,
      58,     0,     0,    54,    55,     0,    43,    38,    42,    53,
       0,    27,     0,    33,    35,    32,     0,   114,    65,    86,
      67,    69,    71,    73,    75,    76,    78,    79,    80,    81,
      82,    84,    85,    87,    88,    89,    62,   103,   104,   109,
       0,   107,     0,     0,     0,     0,     0,     0,    56,    60,
      37,    31,     0,    99,   102,     0,   101,    58,     0,    58,
      58,     0,    36,   110,    47,     0,     0,    49,     0,    58,
      52,    58,     0,    48,     0,    51,    58,    50
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -75,   -75,   -75,   202,   -75,   -25,   -75,   -75,   186,   -75,
      -9,   -11,   -75,   197,   -75,   -75,   -75,    39,    14,   -75,
     -75,   138,   -73,   -75,   -74,   -52,   -30,   -75,   -75,   120,
     121,   143,   122,   124,   -17,    24,    -7,    53,   -75,   -75,
     -75,   -75,   -75,   -75
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    10,    11,    12,    13,    14,    22,    23,    24,    55,
      15,    39,    26,    27,    36,   142,   143,   144,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,   170,
     171,    69,    70,    71
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      17,    56,   102,   132,    25,   135,    28,    80,     1,     2,
       3,     4,     5,     6,     7,     8,    34,    21,    31,   147,
     186,   187,   140,    81,    92,   140,    32,   140,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    18,    33,
     188,   102,    37,    16,   -11,    35,   140,    20,    50,   190,
      21,    51,    91,    52,    53,   140,   175,    30,    54,    80,
      31,   110,   111,   112,   113,     1,     2,     3,     4,     5,
       6,     7,     8,     9,   172,    81,   173,   174,   114,   176,
      32,   202,   141,   103,   146,   108,   109,   140,   115,   116,
     166,   154,   155,    94,   105,   169,   117,   118,   119,   106,
      95,    96,    97,    98,    99,   100,   101,   104,   161,   162,
     179,   107,   120,   127,   194,   196,   128,   197,   133,   121,
     122,   123,   124,   129,   125,   130,   203,   204,   126,   131,
     180,   137,   134,   207,   156,   157,   158,   159,   160,   198,
       1,     2,     3,     4,     5,     6,     7,     8,   136,   139,
     145,   140,   167,   168,   177,   193,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     163,   164,   165,   141,     1,     2,     3,     4,     5,     6,
       7,     8,   178,    72,   181,    73,   182,   183,    74,    75,
      76,    77,    78,    79,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,   184,   185,   189,   191,   195,   199,
     201,   200,   206,    19,    50,   205,    38,    51,    29,    52,
      53,   192,   138,   148,    54,   150,    32,    72,   152,    73,
     -58,   153,    74,    75,    76,    77,    78,    79,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,   151,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    50,     0,
       0,    51,     0,    52,    53,     0,     0,     0,    54,     0,
      32,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    50,     0,     0,    51,     0,    52,    53,     0,     0,
       0,    54,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    50,     0,     0,    51,     0,    52,    53,     0,
       0,     0,    93
};

static const yytype_int16 yycheck[] =
{
       9,    31,    54,    76,    15,    79,    17,    32,     3,     4,
       5,     6,     7,     8,     9,    10,    24,    32,    47,    54,
      58,    54,    60,    32,    35,    60,    55,    60,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,     0,    25,
      54,    93,    28,    24,    59,    53,    60,    59,    43,    54,
      32,    46,    53,    48,    49,    60,   130,    60,    53,    84,
      47,    35,    36,    37,    38,     3,     4,     5,     6,     7,
       8,     9,    10,    11,   126,    84,   128,   129,    52,   131,
      55,    54,    91,    42,    93,    39,    40,    60,    30,    31,
     120,   108,   109,    40,    44,   125,    32,    33,    34,    45,
      47,    48,    49,    50,    51,    52,    53,    41,   115,   116,
     140,    43,    47,    29,   187,   189,    53,   190,    59,    48,
      49,    50,    51,    53,    53,    53,   199,   201,    57,    53,
     141,    56,    59,   206,   110,   111,   112,   113,   114,   191,
       3,     4,     5,     6,     7,     8,     9,    10,    59,    59,
      54,    60,    24,    24,    18,   185,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   182,     3,     4,     5,     6,     7,     8,
       9,    10,    59,    12,    54,    14,    60,    54,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    54,    60,    59,    53,    55,    13,
      59,    56,    54,    11,    43,    59,    30,    46,    21,    48,
      49,   182,    84,   103,    53,   104,    55,    12,   106,    14,
      59,   107,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,   105,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,
      -1,    46,    -1,    48,    49,    -1,    -1,    -1,    53,    -1,
      55,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    -1,    -1,    46,    -1,    48,    49,    -1,    -1,
      -1,    53,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    -1,    -1,    46,    -1,    48,    49,    -1,
      -1,    -1,    53
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      64,    65,    66,    67,    68,    73,    24,    73,     0,    66,
      59,    32,    69,    70,    71,    74,    75,    76,    74,    76,
      60,    47,    55,    81,    24,    53,    77,    81,    71,    74,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      43,    46,    48,    49,    53,    72,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   104,
     105,   106,    12,    14,    17,    18,    19,    20,    21,    22,
      68,    73,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    53,    74,    53,   100,   100,   100,   100,   100,   100,
     100,   100,    88,    42,    41,    44,    45,    43,    39,    40,
      35,    36,    37,    38,    52,    30,    31,    32,    33,    34,
      47,    48,    49,    50,    51,    53,    57,    29,    53,    53,
      53,    53,    85,    59,    59,    87,    59,    56,    84,    59,
      60,    73,    78,    79,    80,    54,    73,    54,    92,   100,
      93,    94,    95,    96,    97,    97,    98,    98,    98,    98,
      98,    99,    99,   100,   100,   100,    89,    24,    24,    89,
     102,   103,    88,    88,    88,    87,    88,    18,    59,    89,
      74,    54,    60,    54,    54,    60,    58,    54,    54,    59,
      54,    53,    80,    89,    85,    55,    87,    85,    88,    13,
      56,    59,    54,    85,    87,    59,    54,    85
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    63,    64,    65,    65,    66,    66,    67,    67,    68,
      69,    69,    70,    70,    71,    71,    72,    73,    73,    73,
      73,    73,    73,    73,    73,    74,    75,    75,    76,    76,
      77,    77,    77,    78,    78,    79,    79,    80,    81,    82,
      82,    83,    83,    84,    84,    85,    85,    85,    85,    85,
      85,    85,    85,    86,    86,    86,    86,    87,    87,    88,
      88,    89,    89,    90,    91,    91,    92,    92,    93,    93,
      94,    94,    95,    95,    96,    96,    96,    97,    97,    97,
      97,    97,    97,    98,    98,    98,    99,    99,    99,    99,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     101,   101,   101,   101,   101,   101,   101,   102,   102,   103,
     103,   104,   104,   104,   104,   105,   105,   105,   105,   106,
     106
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     2,     3,     4,     2,
       1,     0,     1,     3,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     1,     0,     1,     2,
       1,     4,     3,     1,     0,     1,     3,     2,     3,     1,
       0,     1,     2,     2,     1,     1,     1,     5,     7,     5,
       9,     7,     6,     2,     2,     2,     3,     1,     0,     1,
       3,     1,     3,     1,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     3,     1,     3,     3,     1,     3,     3,     3,
       1,     2,     2,     2,     2,     2,     2,     2,     2,     4,
       1,     4,     4,     3,     3,     2,     2,     1,     0,     1,
       3,     1,     1,     1,     3,     1,     1,     1,     1,     1,
       2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 298 "ir_codegen.y"
                    {
        final_ir = (yyvsp[0].node);
        (yyval.node) = (yyvsp[0].node);
      }
#line 1815 "ir_codegen.tab.c"
    break;

  case 3:
#line 305 "ir_codegen.y"
                             {
        (yyval.node) = node_new();
        node_append((yyval.node), (yyvsp[-1].node));
        node_append((yyval.node), (yyvsp[0].node));
      }
#line 1825 "ir_codegen.tab.c"
    break;

  case 4:
#line 310 "ir_codegen.y"
               {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 1833 "ir_codegen.tab.c"
    break;

  case 5:
#line 316 "ir_codegen.y"
                          {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 1841 "ir_codegen.tab.c"
    break;

  case 6:
#line 319 "ir_codegen.y"
                            {
        (yyval.node) = pass_node((yyvsp[-1].node));
      }
#line 1849 "ir_codegen.tab.c"
    break;

  case 7:
#line 325 "ir_codegen.y"
                                                   {
        (yyval.node) = node_new();
        node_append((yyval.node), (yyvsp[0].node));
      }
#line 1858 "ir_codegen.tab.c"
    break;

  case 8:
#line 329 "ir_codegen.y"
                                                          {
        (yyval.node) = node_new();
        node_append((yyval.node), (yyvsp[0].node));
      }
#line 1867 "ir_codegen.tab.c"
    break;

  case 9:
#line 336 "ir_codegen.y"
                                              {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 1875 "ir_codegen.tab.c"
    break;

  case 10:
#line 342 "ir_codegen.y"
                           {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 1883 "ir_codegen.tab.c"
    break;

  case 11:
#line 345 "ir_codegen.y"
                  {
        (yyval.node) = node_new();
      }
#line 1891 "ir_codegen.tab.c"
    break;

  case 12:
#line 351 "ir_codegen.y"
                      {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 1899 "ir_codegen.tab.c"
    break;

  case 13:
#line 354 "ir_codegen.y"
                                                 {
        (yyval.node) = node_new();
        node_append((yyval.node), (yyvsp[-2].node));
        node_append((yyval.node), (yyvsp[0].node));
      }
#line 1909 "ir_codegen.tab.c"
    break;

  case 14:
#line 362 "ir_codegen.y"
                 {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 1917 "ir_codegen.tab.c"
    break;

  case 15:
#line 365 "ir_codegen.y"
                                    {
        (yyval.node) = make_assign((yyvsp[-2].node), (yyvsp[0].node));
      }
#line 1925 "ir_codegen.tab.c"
    break;

  case 16:
#line 371 "ir_codegen.y"
                            {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 1933 "ir_codegen.tab.c"
    break;

  case 17:
#line 377 "ir_codegen.y"
          { (yyval.node) = node_new(); }
#line 1939 "ir_codegen.tab.c"
    break;

  case 18:
#line 378 "ir_codegen.y"
           { (yyval.node) = node_new(); }
#line 1945 "ir_codegen.tab.c"
    break;

  case 19:
#line 379 "ir_codegen.y"
            { (yyval.node) = node_new(); }
#line 1951 "ir_codegen.tab.c"
    break;

  case 20:
#line 380 "ir_codegen.y"
            { (yyval.node) = node_new(); }
#line 1957 "ir_codegen.tab.c"
    break;

  case 21:
#line 381 "ir_codegen.y"
             { (yyval.node) = node_new(); }
#line 1963 "ir_codegen.tab.c"
    break;

  case 22:
#line 382 "ir_codegen.y"
           { (yyval.node) = node_new(); }
#line 1969 "ir_codegen.tab.c"
    break;

  case 23:
#line 383 "ir_codegen.y"
           { (yyval.node) = node_new(); }
#line 1975 "ir_codegen.tab.c"
    break;

  case 24:
#line 384 "ir_codegen.y"
                        {
        (yyval.node) = node_new();
        free((yyvsp[0].str));
      }
#line 1984 "ir_codegen.tab.c"
    break;

  case 25:
#line 391 "ir_codegen.y"
                                    {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 1992 "ir_codegen.tab.c"
    break;

  case 26:
#line 397 "ir_codegen.y"
              {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 2000 "ir_codegen.tab.c"
    break;

  case 27:
#line 400 "ir_codegen.y"
                  {
        (yyval.node) = node_new();
      }
#line 2008 "ir_codegen.tab.c"
    break;

  case 28:
#line 406 "ir_codegen.y"
               {
        (yyval.node) = node_new();
      }
#line 2016 "ir_codegen.tab.c"
    break;

  case 29:
#line 409 "ir_codegen.y"
                       {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 2024 "ir_codegen.tab.c"
    break;

  case 30:
#line 415 "ir_codegen.y"
                 {
        (yyval.node) = node_from_place((yyvsp[0].str));
        free((yyvsp[0].str));
      }
#line 2033 "ir_codegen.tab.c"
    break;

  case 31:
#line 419 "ir_codegen.y"
                                                  {
        (yyval.node) = node_from_place((yyvsp[-3].str));
        free((yyvsp[-3].str));
      }
#line 2042 "ir_codegen.tab.c"
    break;

  case 32:
#line 423 "ir_codegen.y"
                               {
        (yyval.node) = pass_node((yyvsp[-1].node));
      }
#line 2050 "ir_codegen.tab.c"
    break;

  case 33:
#line 429 "ir_codegen.y"
                     {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 2058 "ir_codegen.tab.c"
    break;

  case 34:
#line 432 "ir_codegen.y"
                  {
        (yyval.node) = node_new();
      }
#line 2066 "ir_codegen.tab.c"
    break;

  case 35:
#line 438 "ir_codegen.y"
                            {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 2074 "ir_codegen.tab.c"
    break;

  case 36:
#line 441 "ir_codegen.y"
                                                 {
        (yyval.node) = node_new();
        node_append((yyval.node), (yyvsp[-2].node));
        node_append((yyval.node), (yyvsp[0].node));
      }
#line 2084 "ir_codegen.tab.c"
    break;

  case 37:
#line 449 "ir_codegen.y"
                                {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 2092 "ir_codegen.tab.c"
    break;

  case 38:
#line 455 "ir_codegen.y"
                                        {
        (yyval.node) = pass_node((yyvsp[-1].node));
      }
#line 2100 "ir_codegen.tab.c"
    break;

  case 39:
#line 461 "ir_codegen.y"
                      {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 2108 "ir_codegen.tab.c"
    break;

  case 40:
#line 464 "ir_codegen.y"
                  {
        (yyval.node) = node_new();
      }
#line 2116 "ir_codegen.tab.c"
    break;

  case 41:
#line 470 "ir_codegen.y"
                 {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 2124 "ir_codegen.tab.c"
    break;

  case 42:
#line 473 "ir_codegen.y"
                                 {
        (yyval.node) = node_new();
        node_append((yyval.node), (yyvsp[-1].node));
        node_append((yyval.node), (yyvsp[0].node));
      }
#line 2134 "ir_codegen.tab.c"
    break;

  case 43:
#line 481 "ir_codegen.y"
                            {
        (yyval.node) = pass_node((yyvsp[-1].node));
      }
#line 2142 "ir_codegen.tab.c"
    break;

  case 44:
#line 484 "ir_codegen.y"
                {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 2150 "ir_codegen.tab.c"
    break;

  case 45:
#line 490 "ir_codegen.y"
                       {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 2158 "ir_codegen.tab.c"
    break;

  case 46:
#line 493 "ir_codegen.y"
                         {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 2166 "ir_codegen.tab.c"
    break;

  case 47:
#line 496 "ir_codegen.y"
                                                      {
        IRNode *out = node_new();
        char *lend = new_label();
        node_append(out, (yyvsp[-2].node));
        node_emit(out, "iffalse", ((yyvsp[-2].node) && (yyvsp[-2].node)->has_place) ? (yyvsp[-2].node)->place : "", "", lend);
        node_append(out, (yyvsp[0].node));
        node_emit(out, "label", "", "", lend);
        free(lend);
        (yyval.node) = out;
      }
#line 2181 "ir_codegen.tab.c"
    break;

  case 48:
#line 506 "ir_codegen.y"
                                                           {
        IRNode *out = node_new();
        char *lelse = new_label();
        char *lend = new_label();
        node_append(out, (yyvsp[-4].node));
        node_emit(out, "iffalse", ((yyvsp[-4].node) && (yyvsp[-4].node)->has_place) ? (yyvsp[-4].node)->place : "", "", lelse);
        node_append(out, (yyvsp[-2].node));
        node_emit(out, "goto", "", "", lend);
        node_emit(out, "label", "", "", lelse);
        node_append(out, (yyvsp[0].node));
        node_emit(out, "label", "", "", lend);
        free(lelse);
        free(lend);
        (yyval.node) = out;
      }
#line 2201 "ir_codegen.tab.c"
    break;

  case 49:
#line 521 "ir_codegen.y"
                                               {
        IRNode *out = node_new();
        char *lstart = new_label();
        char *lend = new_label();
        node_emit(out, "label", "", "", lstart);
        node_append(out, (yyvsp[-2].node));
        node_emit(out, "iffalse", ((yyvsp[-2].node) && (yyvsp[-2].node)->has_place) ? (yyvsp[-2].node)->place : "", "", lend);
        node_append(out, (yyvsp[0].node));
        node_emit(out, "goto", "", "", lstart);
        node_emit(out, "label", "", "", lend);
        free(lstart);
        free(lend);
        (yyval.node) = out;
      }
#line 2220 "ir_codegen.tab.c"
    break;

  case 50:
#line 535 "ir_codegen.y"
                                                                                 {
        IRNode *out = node_new();
        char *lstart = new_label();
        char *lend = new_label();
        node_append(out, (yyvsp[-6].node));
        node_emit(out, "label", "", "", lstart);
        node_append(out, (yyvsp[-4].node));
        if ((yyvsp[-4].node) && (yyvsp[-4].node)->has_place) {
            node_emit(out, "iffalse", (yyvsp[-4].node)->place, "", lend);
        }
        node_append(out, (yyvsp[0].node));
        node_append(out, (yyvsp[-2].node));
        node_emit(out, "goto", "", "", lstart);
        node_emit(out, "label", "", "", lend);
        free(lstart);
        free(lend);
        (yyval.node) = out;
      }
#line 2243 "ir_codegen.tab.c"
    break;

  case 51:
#line 553 "ir_codegen.y"
                                                            {
        yyerror("unsupported construct: do-while loop");
        (yyval.node) = node_new();
      }
#line 2252 "ir_codegen.tab.c"
    break;

  case 52:
#line 557 "ir_codegen.y"
                                                    {
        yyerror("unsupported construct: switch statement");
        (yyval.node) = node_new();
      }
#line 2261 "ir_codegen.tab.c"
    break;

  case 53:
#line 564 "ir_codegen.y"
                         {
        (yyval.node) = pass_node((yyvsp[-1].node));
      }
#line 2269 "ir_codegen.tab.c"
    break;

  case 54:
#line 567 "ir_codegen.y"
                      {
        (yyval.node) = node_new();
        node_emit((yyval.node), "break", "", "", "");
      }
#line 2278 "ir_codegen.tab.c"
    break;

  case 55:
#line 571 "ir_codegen.y"
                         {
        (yyval.node) = node_new();
        node_emit((yyval.node), "continue", "", "", "");
      }
#line 2287 "ir_codegen.tab.c"
    break;

  case 56:
#line 575 "ir_codegen.y"
                                {
        (yyval.node) = node_new();
        node_append((yyval.node), (yyvsp[-1].node));
        node_emit((yyval.node), "return", ((yyvsp[-1].node) && (yyvsp[-1].node)->has_place) ? (yyvsp[-1].node)->place : "", "", "");
      }
#line 2297 "ir_codegen.tab.c"
    break;

  case 57:
#line 583 "ir_codegen.y"
                 {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 2305 "ir_codegen.tab.c"
    break;

  case 58:
#line 586 "ir_codegen.y"
                  {
        (yyval.node) = node_new();
      }
#line 2313 "ir_codegen.tab.c"
    break;

  case 59:
#line 592 "ir_codegen.y"
                            {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 2321 "ir_codegen.tab.c"
    break;

  case 60:
#line 595 "ir_codegen.y"
                                             {
        (yyval.node) = node_new();
        node_append((yyval.node), (yyvsp[-2].node));
        node_append((yyval.node), (yyvsp[0].node));
        if ((yyvsp[0].node) && (yyvsp[0].node)->has_place) {
            snprintf((yyval.node)->place, sizeof((yyval.node)->place), "%s", (yyvsp[0].node)->place);
            (yyval.node)->has_place = 1;
        }
      }
#line 2335 "ir_codegen.tab.c"
    break;

  case 61:
#line 607 "ir_codegen.y"
                             {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 2343 "ir_codegen.tab.c"
    break;

  case 62:
#line 610 "ir_codegen.y"
                                                    {
        (yyval.node) = make_assign((yyvsp[-2].node), (yyvsp[0].node));
      }
#line 2351 "ir_codegen.tab.c"
    break;

  case 63:
#line 622 "ir_codegen.y"
                            {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 2359 "ir_codegen.tab.c"
    break;

  case 64:
#line 628 "ir_codegen.y"
                             {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 2367 "ir_codegen.tab.c"
    break;

  case 65:
#line 631 "ir_codegen.y"
                                                              {
        (yyval.node) = make_binary((yyvsp[-2].node), "||", (yyvsp[0].node));
      }
#line 2375 "ir_codegen.tab.c"
    break;

  case 66:
#line 637 "ir_codegen.y"
                            {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 2383 "ir_codegen.tab.c"
    break;

  case 67:
#line 640 "ir_codegen.y"
                                                               {
        (yyval.node) = make_binary((yyvsp[-2].node), "&&", (yyvsp[0].node));
      }
#line 2391 "ir_codegen.tab.c"
    break;

  case 68:
#line 646 "ir_codegen.y"
                             {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 2399 "ir_codegen.tab.c"
    break;

  case 69:
#line 649 "ir_codegen.y"
                                                              {
        (yyval.node) = make_binary((yyvsp[-2].node), "|", (yyvsp[0].node));
      }
#line 2407 "ir_codegen.tab.c"
    break;

  case 70:
#line 655 "ir_codegen.y"
                             {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 2415 "ir_codegen.tab.c"
    break;

  case 71:
#line 658 "ir_codegen.y"
                                                                {
        (yyval.node) = make_binary((yyvsp[-2].node), "^", (yyvsp[0].node));
      }
#line 2423 "ir_codegen.tab.c"
    break;

  case 72:
#line 664 "ir_codegen.y"
                          {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 2431 "ir_codegen.tab.c"
    break;

  case 73:
#line 667 "ir_codegen.y"
                                                             {
        (yyval.node) = make_binary((yyvsp[-2].node), "&", (yyvsp[0].node));
      }
#line 2439 "ir_codegen.tab.c"
    break;

  case 74:
#line 673 "ir_codegen.y"
                            {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 2447 "ir_codegen.tab.c"
    break;

  case 75:
#line 676 "ir_codegen.y"
                                                      {
        (yyval.node) = make_binary((yyvsp[-2].node), "==", (yyvsp[0].node));
      }
#line 2455 "ir_codegen.tab.c"
    break;

  case 76:
#line 679 "ir_codegen.y"
                                                          {
        (yyval.node) = make_binary((yyvsp[-2].node), "!=", (yyvsp[0].node));
      }
#line 2463 "ir_codegen.tab.c"
    break;

  case 77:
#line 685 "ir_codegen.y"
                          {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 2471 "ir_codegen.tab.c"
    break;

  case 78:
#line 688 "ir_codegen.y"
                                                          {
        (yyval.node) = make_binary((yyvsp[-2].node), "<", (yyvsp[0].node));
      }
#line 2479 "ir_codegen.tab.c"
    break;

  case 79:
#line 691 "ir_codegen.y"
                                                             {
        (yyval.node) = make_binary((yyvsp[-2].node), ">", (yyvsp[0].node));
      }
#line 2487 "ir_codegen.tab.c"
    break;

  case 80:
#line 694 "ir_codegen.y"
                                                           {
        (yyval.node) = make_binary((yyvsp[-2].node), "<=", (yyvsp[0].node));
      }
#line 2495 "ir_codegen.tab.c"
    break;

  case 81:
#line 697 "ir_codegen.y"
                                                              {
        (yyval.node) = make_binary((yyvsp[-2].node), ">=", (yyvsp[0].node));
      }
#line 2503 "ir_codegen.tab.c"
    break;

  case 82:
#line 700 "ir_codegen.y"
                                                          {
        (yyval.node) = make_binary((yyvsp[-2].node), "<=>", (yyvsp[0].node));
      }
#line 2511 "ir_codegen.tab.c"
    break;

  case 83:
#line 706 "ir_codegen.y"
                                {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 2519 "ir_codegen.tab.c"
    break;

  case 84:
#line 709 "ir_codegen.y"
                                                         {
        (yyval.node) = make_binary((yyvsp[-2].node), "+", (yyvsp[0].node));
      }
#line 2527 "ir_codegen.tab.c"
    break;

  case 85:
#line 712 "ir_codegen.y"
                                                          {
        (yyval.node) = make_binary((yyvsp[-2].node), "-", (yyvsp[0].node));
      }
#line 2535 "ir_codegen.tab.c"
    break;

  case 86:
#line 718 "ir_codegen.y"
                       {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 2543 "ir_codegen.tab.c"
    break;

  case 87:
#line 721 "ir_codegen.y"
                                                          {
        (yyval.node) = make_binary((yyvsp[-2].node), "*", (yyvsp[0].node));
      }
#line 2551 "ir_codegen.tab.c"
    break;

  case 88:
#line 724 "ir_codegen.y"
                                                        {
        (yyval.node) = make_binary((yyvsp[-2].node), "/", (yyvsp[0].node));
      }
#line 2559 "ir_codegen.tab.c"
    break;

  case 89:
#line 727 "ir_codegen.y"
                                                        {
        (yyval.node) = make_binary((yyvsp[-2].node), "%", (yyvsp[0].node));
      }
#line 2567 "ir_codegen.tab.c"
    break;

  case 90:
#line 733 "ir_codegen.y"
                         {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 2575 "ir_codegen.tab.c"
    break;

  case 91:
#line 736 "ir_codegen.y"
                                 {
        (yyval.node) = node_new();
        node_append((yyval.node), (yyvsp[0].node));
        node_emit((yyval.node), "+", ((yyvsp[0].node) && (yyvsp[0].node)->has_place) ? (yyvsp[0].node)->place : "", "1", ((yyvsp[0].node) && (yyvsp[0].node)->has_place) ? (yyvsp[0].node)->place : "");
        if ((yyvsp[0].node) && (yyvsp[0].node)->has_place) {
            snprintf((yyval.node)->place, sizeof((yyval.node)->place), "%s", (yyvsp[0].node)->place);
            (yyval.node)->has_place = 1;
        }
      }
#line 2589 "ir_codegen.tab.c"
    break;

  case 92:
#line 745 "ir_codegen.y"
                                 {
        (yyval.node) = node_new();
        node_append((yyval.node), (yyvsp[0].node));
        node_emit((yyval.node), "-", ((yyvsp[0].node) && (yyvsp[0].node)->has_place) ? (yyvsp[0].node)->place : "", "1", ((yyvsp[0].node) && (yyvsp[0].node)->has_place) ? (yyvsp[0].node)->place : "");
        if ((yyvsp[0].node) && (yyvsp[0].node)->has_place) {
            snprintf((yyval.node)->place, sizeof((yyval.node)->place), "%s", (yyvsp[0].node)->place);
            (yyval.node)->has_place = 1;
        }
      }
#line 2603 "ir_codegen.tab.c"
    break;

  case 93:
#line 754 "ir_codegen.y"
                            {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 2611 "ir_codegen.tab.c"
    break;

  case 94:
#line 757 "ir_codegen.y"
                             {
        (yyval.node) = make_unary("minus", (yyvsp[0].node));
      }
#line 2619 "ir_codegen.tab.c"
    break;

  case 95:
#line 760 "ir_codegen.y"
                                   {
        (yyval.node) = make_unary("~", (yyvsp[0].node));
      }
#line 2627 "ir_codegen.tab.c"
    break;

  case 96:
#line 763 "ir_codegen.y"
                                   {
        (yyval.node) = make_unary("addr", (yyvsp[0].node));
      }
#line 2635 "ir_codegen.tab.c"
    break;

  case 97:
#line 766 "ir_codegen.y"
                                {
        (yyval.node) = make_unary("deref", (yyvsp[0].node));
      }
#line 2643 "ir_codegen.tab.c"
    break;

  case 98:
#line 769 "ir_codegen.y"
                              {
        (yyval.node) = make_unary("sizeof", (yyvsp[0].node));
      }
#line 2651 "ir_codegen.tab.c"
    break;

  case 99:
#line 772 "ir_codegen.y"
                                          {
        (yyval.node) = node_from_place("sizeof(type)");
      }
#line 2659 "ir_codegen.tab.c"
    break;

  case 100:
#line 778 "ir_codegen.y"
                         {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 2667 "ir_codegen.tab.c"
    break;

  case 101:
#line 781 "ir_codegen.y"
                                                      {
        (yyval.node) = node_new();
        node_append((yyval.node), (yyvsp[-3].node));
        node_append((yyval.node), (yyvsp[-1].node));
        {
            char *t = new_temp();
            node_emit((yyval.node), "[]", ((yyvsp[-3].node) && (yyvsp[-3].node)->has_place) ? (yyvsp[-3].node)->place : "", ((yyvsp[-1].node) && (yyvsp[-1].node)->has_place) ? (yyvsp[-1].node)->place : "", t);
            snprintf((yyval.node)->place, sizeof((yyval.node)->place), "%s", t);
            (yyval.node)->has_place = 1;
            free(t);
        }
      }
#line 2684 "ir_codegen.tab.c"
    break;

  case 102:
#line 793 "ir_codegen.y"
                                                                    {
        (yyval.node) = node_new();
        node_append((yyval.node), (yyvsp[-3].node));
        node_append((yyval.node), (yyvsp[-1].node));
        node_emit((yyval.node), "call", ((yyvsp[-3].node) && (yyvsp[-3].node)->has_place) ? (yyvsp[-3].node)->place : "", "", "");
        {
            char *t = new_temp();
            node_emit((yyval.node), "ret", "", "", t);
            snprintf((yyval.node)->place, sizeof((yyval.node)->place), "%s", t);
            (yyval.node)->has_place = 1;
            free(t);
        }
      }
#line 2702 "ir_codegen.tab.c"
    break;

  case 103:
#line 806 "ir_codegen.y"
                                        {
        (yyval.node) = node_new();
        node_append((yyval.node), (yyvsp[-2].node));
        {
            char *t = new_temp();
            node_emit((yyval.node), ".", ((yyvsp[-2].node) && (yyvsp[-2].node)->has_place) ? (yyvsp[-2].node)->place : "", (yyvsp[0].str), t);
            snprintf((yyval.node)->place, sizeof((yyval.node)->place), "%s", t);
            (yyval.node)->has_place = 1;
            free(t);
        }
        free((yyvsp[0].str));
      }
#line 2719 "ir_codegen.tab.c"
    break;

  case 104:
#line 818 "ir_codegen.y"
                                          {
        (yyval.node) = node_new();
        node_append((yyval.node), (yyvsp[-2].node));
        {
            char *t = new_temp();
            node_emit((yyval.node), "->", ((yyvsp[-2].node) && (yyvsp[-2].node)->has_place) ? (yyvsp[-2].node)->place : "", (yyvsp[0].str), t);
            snprintf((yyval.node)->place, sizeof((yyval.node)->place), "%s", t);
            (yyval.node)->has_place = 1;
            free(t);
        }
        free((yyvsp[0].str));
      }
#line 2736 "ir_codegen.tab.c"
    break;

  case 105:
#line 830 "ir_codegen.y"
                                   {
        (yyval.node) = node_new();
        node_append((yyval.node), (yyvsp[-1].node));
        if ((yyvsp[-1].node) && (yyvsp[-1].node)->has_place) {
            char *t = new_temp();
            node_emit((yyval.node), "=", (yyvsp[-1].node)->place, "", t);
            node_emit((yyval.node), "+", (yyvsp[-1].node)->place, "1", (yyvsp[-1].node)->place);
            snprintf((yyval.node)->place, sizeof((yyval.node)->place), "%s", t);
            (yyval.node)->has_place = 1;
            free(t);
        }
      }
#line 2753 "ir_codegen.tab.c"
    break;

  case 106:
#line 842 "ir_codegen.y"
                                   {
        (yyval.node) = node_new();
        node_append((yyval.node), (yyvsp[-1].node));
        if ((yyvsp[-1].node) && (yyvsp[-1].node)->has_place) {
            char *t = new_temp();
            node_emit((yyval.node), "=", (yyvsp[-1].node)->place, "", t);
            node_emit((yyval.node), "-", (yyvsp[-1].node)->place, "1", (yyvsp[-1].node)->place);
            snprintf((yyval.node)->place, sizeof((yyval.node)->place), "%s", t);
            (yyval.node)->has_place = 1;
            free(t);
        }
      }
#line 2770 "ir_codegen.tab.c"
    break;

  case 107:
#line 857 "ir_codegen.y"
                               {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 2778 "ir_codegen.tab.c"
    break;

  case 108:
#line 860 "ir_codegen.y"
                  {
        (yyval.node) = node_new();
      }
#line 2786 "ir_codegen.tab.c"
    break;

  case 109:
#line 866 "ir_codegen.y"
                            {
        (yyval.node) = node_new();
        node_append((yyval.node), (yyvsp[0].node));
        node_emit((yyval.node), "param", ((yyvsp[0].node) && (yyvsp[0].node)->has_place) ? (yyvsp[0].node)->place : "", "", "");
      }
#line 2796 "ir_codegen.tab.c"
    break;

  case 110:
#line 871 "ir_codegen.y"
                                                           {
        (yyval.node) = pass_node((yyvsp[-2].node));
        node_append((yyval.node), (yyvsp[0].node));
        node_emit((yyval.node), "param", ((yyvsp[0].node) && (yyvsp[0].node)->has_place) ? (yyvsp[0].node)->place : "", "", "");
      }
#line 2806 "ir_codegen.tab.c"
    break;

  case 111:
#line 879 "ir_codegen.y"
                 {
        (yyval.node) = node_from_place((yyvsp[0].str));
        free((yyvsp[0].str));
      }
#line 2815 "ir_codegen.tab.c"
    break;

  case 112:
#line 883 "ir_codegen.y"
               {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 2823 "ir_codegen.tab.c"
    break;

  case 113:
#line 886 "ir_codegen.y"
                              {
        (yyval.node) = pass_node((yyvsp[0].node));
      }
#line 2831 "ir_codegen.tab.c"
    break;

  case 114:
#line 889 "ir_codegen.y"
                               {
        (yyval.node) = pass_node((yyvsp[-1].node));
      }
#line 2839 "ir_codegen.tab.c"
    break;

  case 115:
#line 895 "ir_codegen.y"
                       {
        (yyval.node) = node_from_place((yyvsp[0].str));
        free((yyvsp[0].str));
      }
#line 2848 "ir_codegen.tab.c"
    break;

  case 116:
#line 899 "ir_codegen.y"
                   {
        (yyval.node) = node_from_place((yyvsp[0].str));
        free((yyvsp[0].str));
      }
#line 2857 "ir_codegen.tab.c"
    break;

  case 117:
#line 903 "ir_codegen.y"
                     {
        (yyval.node) = node_from_place((yyvsp[0].str));
        free((yyvsp[0].str));
      }
#line 2866 "ir_codegen.tab.c"
    break;

  case 118:
#line 907 "ir_codegen.y"
                    {
        (yyval.node) = node_from_place((yyvsp[0].str));
        free((yyvsp[0].str));
      }
#line 2875 "ir_codegen.tab.c"
    break;

  case 119:
#line 914 "ir_codegen.y"
                     {
        (yyval.node) = node_from_place((yyvsp[0].str));
        free((yyvsp[0].str));
      }
#line 2884 "ir_codegen.tab.c"
    break;

  case 120:
#line 918 "ir_codegen.y"
                                             {
        (yyval.node) = pass_node((yyvsp[-1].node));
        if ((yyval.node) && (yyval.node)->has_place) {
            size_t need = strlen((yyval.node)->place) + strlen((yyvsp[0].str)) + 1;
            char *buf = (char *)malloc(need + 1);
            if (!buf) {
                fprintf(stderr, "Fatal: out of memory while joining strings.\n");
                exit(1);
            }
            snprintf(buf, need + 1, "%s%s", (yyval.node)->place, (yyvsp[0].str));
            snprintf((yyval.node)->place, sizeof((yyval.node)->place), "%s", buf);
            free(buf);
        }
        free((yyvsp[0].str));
      }
#line 2904 "ir_codegen.tab.c"
    break;


#line 2908 "ir_codegen.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 935 "ir_codegen.y"


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
