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
#line 1 "lalr_assignment3.y"

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

#line 92 "lalr_assignment3.tab.c"

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
#ifndef YY_YY_LALR_ASSIGNMENT3_TAB_H_INCLUDED
# define YY_YY_LALR_ASSIGNMENT3_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

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
    COLON = 316
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_LALR_ASSIGNMENT3_TAB_H_INCLUDED  */



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
#define YYLAST   457

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  123
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  214

#define YYUNDEFTOK  2
#define YYMAXUTOK   316


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
      55,    56,    57,    58,    59,    60,    61
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    45,    45,    49,    50,    54,    55,    59,    60,    64,
      68,    69,    73,    74,    78,    79,    83,    87,    88,    89,
      90,    91,    92,    93,    94,    98,   102,   103,   107,   108,
     112,   113,   114,   118,   119,   123,   124,   128,   132,   136,
     137,   141,   142,   146,   147,   151,   152,   153,   154,   156,
     157,   159,   161,   166,   167,   168,   169,   173,   174,   178,
     179,   183,   184,   188,   192,   193,   197,   198,   202,   203,
     207,   211,   215,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   255,   256,   257,   259,   260,   261,   262,
     266,   267,   271,   272,   276,   277,   278,   279,   283,   284,
     285,   286,   290,   291
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
  "SEMICOLON", "COMMA", "COLON", "$accept", "program", "external_list",
  "external", "function_definition", "declaration",
  "init_declarator_list_opt", "init_declarator_list", "init_declarator",
  "initializer", "type_specifier", "declarator", "pointer_opt", "pointer",
  "direct_declarator", "parameter_list_opt", "parameter_list",
  "parameter_declaration", "compound_statement", "block_item_list_opt",
  "block_item_list", "block_item", "statement", "simple_statement",
  "expr_opt", "case_sections_opt", "case_sections", "case_section",
  "default_section_opt", "statement_list_opt", "statement_list",
  "expression", "assignment_expression", "constant_expression",
  "ambiguous_expression", "unary_expression", "postfix_expression",
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
     315,   316
};
# endif

#define YYPACT_NINF (-113)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-68)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      97,  -113,  -113,  -113,  -113,  -113,  -113,  -113,   -16,   142,
      15,    97,  -113,  -113,   -40,   -12,  -113,   -11,  -113,  -113,
    -113,   -11,  -113,   -28,  -113,    -1,    -8,  -113,    -7,  -113,
     -11,    12,   161,  -113,    -3,   -11,  -113,  -113,  -113,     4,
     404,  -113,  -113,  -113,  -113,  -113,  -113,    12,    12,    12,
      12,    12,    12,    12,    12,  -113,  -113,   366,  -113,   -39,
    -113,  -113,    23,     0,     3,     9,    11,   340,    -2,    36,
      12,    37,   -12,  -113,    18,   161,  -113,  -113,  -113,    38,
    -113,   366,   142,    14,   218,  -113,  -113,  -113,  -113,  -113,
    -113,  -113,  -113,    17,    12,    12,    12,    12,    12,    12,
      12,    12,    12,    12,    12,    12,    12,    12,    12,    12,
      12,    12,    12,  -113,  -113,    74,    85,    12,    12,  -113,
      12,    12,    12,    12,    92,  -113,  -113,    53,  -113,  -113,
    -113,  -113,   -11,    59,    55,  -113,  -113,    63,  -113,   366,
     366,   366,   366,   366,   366,   366,   366,   366,   366,   366,
     366,   366,   366,   366,   366,   366,   366,   366,  -113,  -113,
    -113,    64,    60,    66,    67,    68,    69,    71,    73,  -113,
    -113,  -113,   142,  -113,  -113,    12,  -113,   340,    72,    12,
     340,    12,  -113,  -113,   116,   117,    75,  -113,    79,   340,
      12,   119,   117,  -113,    12,    77,  -113,    76,   366,    81,
      84,  -113,    89,  -113,   256,   300,  -113,   340,  -113,  -113,
     256,  -113,  -113,  -113
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
       0,   114,   118,   119,   120,   121,   122,     0,     0,     0,
       0,     0,     0,     0,     0,    15,    16,    71,    73,    93,
     103,   115,   116,     0,     0,     0,     0,    58,     0,     0,
      58,     0,    27,    46,     0,    39,    41,    44,    45,     0,
      57,    70,    34,     0,     0,   101,    96,    97,   100,    99,
      98,    94,    95,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   108,   109,     0,     0,   111,     0,   123,
       0,     0,    58,     0,     0,    54,    55,     0,    43,    38,
      42,    53,    27,     0,    33,    35,    32,     0,   117,    88,
      89,    90,    91,    92,    83,    84,    85,    86,    81,    82,
      77,    76,    80,    78,    79,    75,    87,    74,   106,   107,
     112,     0,   110,     0,     0,     0,     0,     0,     0,    56,
      37,    31,     0,   102,   105,     0,   104,    58,     0,    58,
      58,     0,    36,   113,    47,    60,     0,    49,     0,    58,
       0,    65,    59,    61,    58,     0,    48,     0,    72,     0,
       0,    62,     0,    50,    67,    58,    52,    58,    68,    63,
      66,    64,    51,    69
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -113,  -113,  -113,   143,  -113,   -26,  -113,  -113,   123,  -113,
      -9,   -13,  -113,   134,  -113,  -113,  -113,   -14,     6,  -113,
    -113,    86,   -66,  -113,   -63,  -113,  -113,   -36,  -113,   -46,
    -113,   -51,  -112,  -113,   -18,   -23,  -113,  -113,  -113,  -113,
    -113,  -113
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    10,    11,    12,    13,    14,    22,    23,    24,    55,
      15,    39,    26,    27,    36,   133,   134,   135,    73,    74,
      75,    76,    77,    78,    79,   191,   192,   193,   200,   209,
     210,    80,    56,   197,    81,    58,    59,   161,   162,    60,
      61,    62
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      17,   124,    25,    93,    28,   160,    71,   127,    16,   113,
     114,   115,   116,    57,   117,    18,    34,    85,   118,    20,
      21,    21,    83,    72,    86,    87,    88,    89,    90,    91,
      92,    33,    30,    93,    37,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    35,    31,   -11,    32,    71,
      82,    31,   119,   120,    32,    50,   121,   125,    51,   166,
      52,    53,   122,   183,   123,    54,    72,   163,   136,   164,
     165,   138,   167,   132,   129,   137,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   126,   128,   131,   158,    57,
       1,     2,     3,     4,     5,     6,     7,     8,     9,   159,
     168,   184,   169,   171,   187,   172,   186,   173,   174,   170,
     175,   177,   178,   196,   176,   180,   181,   185,   179,   189,
     188,   202,   190,   195,   194,   199,   203,   204,   208,   208,
     206,   212,   205,   207,   213,     1,     2,     3,     4,     5,
       6,     7,     8,    38,    19,    29,   201,    57,   182,   211,
       0,   130,     0,   132,     1,     2,     3,     4,     5,     6,
       7,     8,   198,    63,     0,    64,     0,     0,    65,    66,
      67,    68,    69,    70,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    50,     0,     0,    51,     0,    52,
      53,     0,     0,     0,    54,     0,    32,     0,     0,     0,
     -58,     1,     2,     3,     4,     5,     6,     7,     8,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    50,     0,     0,    51,     0,    52,    53,    63,     0,
      64,    54,     0,    65,    66,    67,    68,    69,    70,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    50,
       0,     0,    51,     0,    52,    53,     0,     0,     0,    54,
       0,    32,    63,     0,    64,   -58,     0,    65,    66,    67,
      68,    69,    70,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    50,     0,     0,    51,     0,    52,    53,
       0,     0,    63,    54,    64,    32,   -67,    65,    66,    67,
      68,    69,    70,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    50,     0,     0,    51,     0,    52,    53,
       0,     0,     0,    54,     0,    32,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,     0,   110,     0,     0,     0,     0,   111,     0,
       0,     0,     0,     0,     0,     0,   112,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    50,     0,     0,
      51,     0,    52,    53,     0,     0,     0,    84
};

static const yytype_int16 yycheck[] =
{
       9,    67,    15,    54,    17,   117,    32,    70,    24,    48,
      49,    50,    51,    31,    53,     0,    24,    40,    57,    59,
      32,    32,    35,    32,    47,    48,    49,    50,    51,    52,
      53,    25,    60,    84,    28,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    53,    47,    59,    55,    75,
      53,    47,    29,    53,    55,    43,    53,    59,    46,   122,
      48,    49,    53,   175,    53,    53,    75,   118,    54,   120,
     121,    54,   123,    82,    56,    84,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,    59,    59,    59,    24,   117,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    24,
      18,   177,    59,    54,   180,    60,   179,    54,    54,   132,
      60,    54,    54,   189,    58,    54,    53,    55,    59,    13,
     181,   194,    15,    54,    59,    16,    59,    61,   204,   205,
      56,   207,    61,    54,   210,     3,     4,     5,     6,     7,
       8,     9,    10,    30,    11,    21,   192,   175,   172,   205,
      -1,    75,    -1,   172,     3,     4,     5,     6,     7,     8,
       9,    10,   190,    12,    -1,    14,    -1,    -1,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    -1,    -1,    46,    -1,    48,
      49,    -1,    -1,    -1,    53,    -1,    55,    -1,    -1,    -1,
      59,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    -1,    -1,    46,    -1,    48,    49,    12,    -1,
      14,    53,    -1,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      -1,    -1,    46,    -1,    48,    49,    -1,    -1,    -1,    53,
      -1,    55,    12,    -1,    14,    59,    -1,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    -1,    -1,    46,    -1,    48,    49,
      -1,    -1,    12,    53,    14,    55,    56,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    -1,    -1,    46,    -1,    48,    49,
      -1,    -1,    -1,    53,    -1,    55,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    -1,    47,    -1,    -1,    -1,    -1,    52,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    60,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,    -1,
      46,    -1,    48,    49,    -1,    -1,    -1,    53
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      63,    64,    65,    66,    67,    72,    24,    72,     0,    65,
      59,    32,    68,    69,    70,    73,    74,    75,    73,    75,
      60,    47,    55,    80,    24,    53,    76,    80,    70,    73,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      43,    46,    48,    49,    53,    71,    94,    96,    97,    98,
     101,   102,   103,    12,    14,    17,    18,    19,    20,    21,
      22,    67,    72,    80,    81,    82,    83,    84,    85,    86,
      93,    96,    53,    73,    53,    97,    97,    97,    97,    97,
      97,    97,    97,    93,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      47,    52,    60,    48,    49,    50,    51,    53,    57,    29,
      53,    53,    53,    53,    84,    59,    59,    86,    59,    56,
      83,    59,    72,    77,    78,    79,    54,    72,    54,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    24,    24,
      94,    99,   100,    93,    93,    93,    86,    93,    18,    59,
      73,    54,    60,    54,    54,    60,    58,    54,    54,    59,
      54,    53,    79,    94,    84,    55,    86,    84,    93,    13,
      15,    87,    88,    89,    59,    54,    84,    95,    96,    16,
      90,    89,    86,    59,    61,    61,    56,    54,    84,    91,
      92,    91,    84,    84
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    62,    63,    64,    64,    65,    65,    66,    66,    67,
      68,    68,    69,    69,    70,    70,    71,    72,    72,    72,
      72,    72,    72,    72,    72,    73,    74,    74,    75,    75,
      76,    76,    76,    77,    77,    78,    78,    79,    80,    81,
      81,    82,    82,    83,    83,    84,    84,    84,    84,    84,
      84,    84,    84,    85,    85,    85,    85,    86,    86,    87,
      87,    88,    88,    89,    90,    90,    91,    91,    92,    92,
      93,    94,    95,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    98,    98,    98,    98,    98,    98,    98,
      99,    99,   100,   100,   101,   101,   101,   101,   102,   102,
     102,   102,   103,   103
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     2,     3,     4,     2,
       1,     0,     1,     3,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     1,     0,     1,     2,
       1,     4,     3,     1,     0,     1,     3,     2,     3,     1,
       0,     1,     2,     2,     1,     1,     1,     5,     7,     5,
       7,     9,     8,     2,     2,     2,     3,     1,     0,     1,
       0,     1,     2,     4,     3,     0,     1,     0,     1,     2,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     2,     2,     2,     2,     2,     2,
       2,     2,     4,     1,     4,     4,     3,     3,     2,     2,
       1,     0,     1,     3,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     2
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
#line 45 "lalr_assignment3.y"
                                                         { log_reduction("program -> external_list"); }
#line 1593 "lalr_assignment3.tab.c"
    break;

  case 3:
#line 49 "lalr_assignment3.y"
                                                         { log_reduction("external_list -> external_list external"); }
#line 1599 "lalr_assignment3.tab.c"
    break;

  case 4:
#line 50 "lalr_assignment3.y"
                                                         { log_reduction("external_list -> external"); }
#line 1605 "lalr_assignment3.tab.c"
    break;

  case 5:
#line 54 "lalr_assignment3.y"
                                                         { log_reduction("external -> function_definition"); }
#line 1611 "lalr_assignment3.tab.c"
    break;

  case 6:
#line 55 "lalr_assignment3.y"
                                                         { log_reduction("external -> declaration ;"); }
#line 1617 "lalr_assignment3.tab.c"
    break;

  case 7:
#line 59 "lalr_assignment3.y"
                                                         { log_reduction("function_definition -> type_specifier declarator compound_statement"); }
#line 1623 "lalr_assignment3.tab.c"
    break;

  case 8:
#line 60 "lalr_assignment3.y"
                                                          { log_reduction("function_definition -> extern type_specifier declarator compound_statement"); }
#line 1629 "lalr_assignment3.tab.c"
    break;

  case 9:
#line 64 "lalr_assignment3.y"
                                                         { log_reduction("declaration -> type_specifier init_declarator_list_opt"); }
#line 1635 "lalr_assignment3.tab.c"
    break;

  case 10:
#line 68 "lalr_assignment3.y"
                                                         { log_reduction("init_declarator_list_opt -> init_declarator_list"); }
#line 1641 "lalr_assignment3.tab.c"
    break;

  case 11:
#line 69 "lalr_assignment3.y"
                                                         { log_reduction("init_declarator_list_opt -> epsilon"); }
#line 1647 "lalr_assignment3.tab.c"
    break;

  case 12:
#line 73 "lalr_assignment3.y"
                                                         { log_reduction("init_declarator_list -> init_declarator"); }
#line 1653 "lalr_assignment3.tab.c"
    break;

  case 13:
#line 74 "lalr_assignment3.y"
                                                         { log_reduction("init_declarator_list -> init_declarator_list , init_declarator"); }
#line 1659 "lalr_assignment3.tab.c"
    break;

  case 14:
#line 78 "lalr_assignment3.y"
                                                         { log_reduction("init_declarator -> declarator"); }
#line 1665 "lalr_assignment3.tab.c"
    break;

  case 15:
#line 79 "lalr_assignment3.y"
                                                         { log_reduction("init_declarator -> declarator = initializer"); }
#line 1671 "lalr_assignment3.tab.c"
    break;

  case 16:
#line 83 "lalr_assignment3.y"
                                                         { log_reduction("initializer -> assignment_expression"); }
#line 1677 "lalr_assignment3.tab.c"
    break;

  case 17:
#line 87 "lalr_assignment3.y"
                                                         { log_reduction("type_specifier -> int"); }
#line 1683 "lalr_assignment3.tab.c"
    break;

  case 18:
#line 88 "lalr_assignment3.y"
                                                         { log_reduction("type_specifier -> long"); }
#line 1689 "lalr_assignment3.tab.c"
    break;

  case 19:
#line 89 "lalr_assignment3.y"
                                                         { log_reduction("type_specifier -> short"); }
#line 1695 "lalr_assignment3.tab.c"
    break;

  case 20:
#line 90 "lalr_assignment3.y"
                                                         { log_reduction("type_specifier -> float"); }
#line 1701 "lalr_assignment3.tab.c"
    break;

  case 21:
#line 91 "lalr_assignment3.y"
                                                         { log_reduction("type_specifier -> double"); }
#line 1707 "lalr_assignment3.tab.c"
    break;

  case 22:
#line 92 "lalr_assignment3.y"
                                                         { log_reduction("type_specifier -> void"); }
#line 1713 "lalr_assignment3.tab.c"
    break;

  case 23:
#line 93 "lalr_assignment3.y"
                                                         { log_reduction("type_specifier -> char"); }
#line 1719 "lalr_assignment3.tab.c"
    break;

  case 24:
#line 94 "lalr_assignment3.y"
                                                         { log_reduction("type_specifier -> struct identifier"); }
#line 1725 "lalr_assignment3.tab.c"
    break;

  case 25:
#line 98 "lalr_assignment3.y"
                                                         { log_reduction("declarator -> pointer_opt direct_declarator"); }
#line 1731 "lalr_assignment3.tab.c"
    break;

  case 26:
#line 102 "lalr_assignment3.y"
                                                         { log_reduction("pointer_opt -> pointer"); }
#line 1737 "lalr_assignment3.tab.c"
    break;

  case 27:
#line 103 "lalr_assignment3.y"
                                                         { log_reduction("pointer_opt -> epsilon"); }
#line 1743 "lalr_assignment3.tab.c"
    break;

  case 28:
#line 107 "lalr_assignment3.y"
                                                         { log_reduction("pointer -> *"); }
#line 1749 "lalr_assignment3.tab.c"
    break;

  case 29:
#line 108 "lalr_assignment3.y"
                                                         { log_reduction("pointer -> * pointer"); }
#line 1755 "lalr_assignment3.tab.c"
    break;

  case 30:
#line 112 "lalr_assignment3.y"
                                                         { log_reduction("direct_declarator -> identifier"); }
#line 1761 "lalr_assignment3.tab.c"
    break;

  case 31:
#line 113 "lalr_assignment3.y"
                                                         { log_reduction("direct_declarator -> identifier ( parameter_list_opt )"); }
#line 1767 "lalr_assignment3.tab.c"
    break;

  case 32:
#line 114 "lalr_assignment3.y"
                                                         { log_reduction("direct_declarator -> ( declarator )"); }
#line 1773 "lalr_assignment3.tab.c"
    break;

  case 33:
#line 118 "lalr_assignment3.y"
                                                         { log_reduction("parameter_list_opt -> parameter_list"); }
#line 1779 "lalr_assignment3.tab.c"
    break;

  case 34:
#line 119 "lalr_assignment3.y"
                                                         { log_reduction("parameter_list_opt -> epsilon"); }
#line 1785 "lalr_assignment3.tab.c"
    break;

  case 35:
#line 123 "lalr_assignment3.y"
                                                         { log_reduction("parameter_list -> parameter_declaration"); }
#line 1791 "lalr_assignment3.tab.c"
    break;

  case 36:
#line 124 "lalr_assignment3.y"
                                                         { log_reduction("parameter_list -> parameter_list , parameter_declaration"); }
#line 1797 "lalr_assignment3.tab.c"
    break;

  case 37:
#line 128 "lalr_assignment3.y"
                                                         { log_reduction("parameter_declaration -> type_specifier declarator"); }
#line 1803 "lalr_assignment3.tab.c"
    break;

  case 38:
#line 132 "lalr_assignment3.y"
                                                         { log_reduction("compound_statement -> { block_item_list_opt }"); }
#line 1809 "lalr_assignment3.tab.c"
    break;

  case 39:
#line 136 "lalr_assignment3.y"
                                                         { log_reduction("block_item_list_opt -> block_item_list"); }
#line 1815 "lalr_assignment3.tab.c"
    break;

  case 40:
#line 137 "lalr_assignment3.y"
                                                         { log_reduction("block_item_list_opt -> epsilon"); }
#line 1821 "lalr_assignment3.tab.c"
    break;

  case 41:
#line 141 "lalr_assignment3.y"
                                                         { log_reduction("block_item_list -> block_item"); }
#line 1827 "lalr_assignment3.tab.c"
    break;

  case 42:
#line 142 "lalr_assignment3.y"
                                                         { log_reduction("block_item_list -> block_item_list block_item"); }
#line 1833 "lalr_assignment3.tab.c"
    break;

  case 43:
#line 146 "lalr_assignment3.y"
                                                         { log_reduction("block_item -> declaration ;"); }
#line 1839 "lalr_assignment3.tab.c"
    break;

  case 44:
#line 147 "lalr_assignment3.y"
                                                         { log_reduction("block_item -> statement"); }
#line 1845 "lalr_assignment3.tab.c"
    break;

  case 45:
#line 151 "lalr_assignment3.y"
                                                         { log_reduction("statement -> simple_statement"); }
#line 1851 "lalr_assignment3.tab.c"
    break;

  case 46:
#line 152 "lalr_assignment3.y"
                                                         { log_reduction("statement -> compound_statement"); }
#line 1857 "lalr_assignment3.tab.c"
    break;

  case 47:
#line 153 "lalr_assignment3.y"
                                                         { log_reduction("statement -> if ( expression ) statement"); }
#line 1863 "lalr_assignment3.tab.c"
    break;

  case 48:
#line 155 "lalr_assignment3.y"
                                                        { log_reduction("statement -> if ( expression ) statement else statement"); }
#line 1869 "lalr_assignment3.tab.c"
    break;

  case 49:
#line 156 "lalr_assignment3.y"
                                                         { log_reduction("statement -> while ( expression ) statement"); }
#line 1875 "lalr_assignment3.tab.c"
    break;

  case 50:
#line 158 "lalr_assignment3.y"
                                                        { log_reduction("statement -> do statement while ( expression ) ;"); }
#line 1881 "lalr_assignment3.tab.c"
    break;

  case 51:
#line 160 "lalr_assignment3.y"
                                                        { log_reduction("statement -> for ( expr_opt ; expr_opt ; expr_opt ) statement"); }
#line 1887 "lalr_assignment3.tab.c"
    break;

  case 52:
#line 162 "lalr_assignment3.y"
                                                        { log_reduction("statement -> switch ( expression ) { case_sections_opt default_section_opt }"); }
#line 1893 "lalr_assignment3.tab.c"
    break;

  case 53:
#line 166 "lalr_assignment3.y"
                                                         { log_reduction("simple_statement -> expr_opt ;"); }
#line 1899 "lalr_assignment3.tab.c"
    break;

  case 54:
#line 167 "lalr_assignment3.y"
                                                         { log_reduction("simple_statement -> break ;"); }
#line 1905 "lalr_assignment3.tab.c"
    break;

  case 55:
#line 168 "lalr_assignment3.y"
                                                         { log_reduction("simple_statement -> continue ;"); }
#line 1911 "lalr_assignment3.tab.c"
    break;

  case 56:
#line 169 "lalr_assignment3.y"
                                                         { log_reduction("simple_statement -> return expr_opt ;"); }
#line 1917 "lalr_assignment3.tab.c"
    break;

  case 57:
#line 173 "lalr_assignment3.y"
                                                         { log_reduction("expr_opt -> expression"); }
#line 1923 "lalr_assignment3.tab.c"
    break;

  case 58:
#line 174 "lalr_assignment3.y"
                                                         { log_reduction("expr_opt -> epsilon"); }
#line 1929 "lalr_assignment3.tab.c"
    break;

  case 59:
#line 178 "lalr_assignment3.y"
                                                         { log_reduction("case_sections_opt -> case_sections"); }
#line 1935 "lalr_assignment3.tab.c"
    break;

  case 60:
#line 179 "lalr_assignment3.y"
                                                         { log_reduction("case_sections_opt -> epsilon"); }
#line 1941 "lalr_assignment3.tab.c"
    break;

  case 61:
#line 183 "lalr_assignment3.y"
                                                         { log_reduction("case_sections -> case_section"); }
#line 1947 "lalr_assignment3.tab.c"
    break;

  case 62:
#line 184 "lalr_assignment3.y"
                                                         { log_reduction("case_sections -> case_sections case_section"); }
#line 1953 "lalr_assignment3.tab.c"
    break;

  case 63:
#line 188 "lalr_assignment3.y"
                                                         { log_reduction("case_section -> case constant_expression : statement_list_opt"); }
#line 1959 "lalr_assignment3.tab.c"
    break;

  case 64:
#line 192 "lalr_assignment3.y"
                                                         { log_reduction("default_section_opt -> default : statement_list_opt"); }
#line 1965 "lalr_assignment3.tab.c"
    break;

  case 65:
#line 193 "lalr_assignment3.y"
                                                         { log_reduction("default_section_opt -> epsilon"); }
#line 1971 "lalr_assignment3.tab.c"
    break;

  case 66:
#line 197 "lalr_assignment3.y"
                                                         { log_reduction("statement_list_opt -> statement_list"); }
#line 1977 "lalr_assignment3.tab.c"
    break;

  case 67:
#line 198 "lalr_assignment3.y"
                                                         { log_reduction("statement_list_opt -> epsilon"); }
#line 1983 "lalr_assignment3.tab.c"
    break;

  case 68:
#line 202 "lalr_assignment3.y"
                                                         { log_reduction("statement_list -> statement"); }
#line 1989 "lalr_assignment3.tab.c"
    break;

  case 69:
#line 203 "lalr_assignment3.y"
                                                         { log_reduction("statement_list -> statement_list statement"); }
#line 1995 "lalr_assignment3.tab.c"
    break;

  case 70:
#line 207 "lalr_assignment3.y"
                                                         { log_reduction("expression -> ambiguous_expression"); }
#line 2001 "lalr_assignment3.tab.c"
    break;

  case 71:
#line 211 "lalr_assignment3.y"
                                                         { log_reduction("assignment_expression -> ambiguous_expression"); }
#line 2007 "lalr_assignment3.tab.c"
    break;

  case 72:
#line 215 "lalr_assignment3.y"
                                                         { log_reduction("constant_expression -> ambiguous_expression"); }
#line 2013 "lalr_assignment3.tab.c"
    break;

  case 73:
#line 219 "lalr_assignment3.y"
                                                         { log_reduction("ambiguous_expression -> unary_expression"); }
#line 2019 "lalr_assignment3.tab.c"
    break;

  case 74:
#line 220 "lalr_assignment3.y"
                                                         { log_reduction("ambiguous_expression -> ambiguous_expression , ambiguous_expression"); }
#line 2025 "lalr_assignment3.tab.c"
    break;

  case 75:
#line 221 "lalr_assignment3.y"
                                                         { log_reduction("ambiguous_expression -> ambiguous_expression = ambiguous_expression"); }
#line 2031 "lalr_assignment3.tab.c"
    break;

  case 76:
#line 222 "lalr_assignment3.y"
                                                           { log_reduction("ambiguous_expression -> ambiguous_expression || ambiguous_expression"); }
#line 2037 "lalr_assignment3.tab.c"
    break;

  case 77:
#line 223 "lalr_assignment3.y"
                                                            { log_reduction("ambiguous_expression -> ambiguous_expression && ambiguous_expression"); }
#line 2043 "lalr_assignment3.tab.c"
    break;

  case 78:
#line 224 "lalr_assignment3.y"
                                                           { log_reduction("ambiguous_expression -> ambiguous_expression | ambiguous_expression"); }
#line 2049 "lalr_assignment3.tab.c"
    break;

  case 79:
#line 225 "lalr_assignment3.y"
                                                            { log_reduction("ambiguous_expression -> ambiguous_expression ^ ambiguous_expression"); }
#line 2055 "lalr_assignment3.tab.c"
    break;

  case 80:
#line 226 "lalr_assignment3.y"
                                                            { log_reduction("ambiguous_expression -> ambiguous_expression & ambiguous_expression"); }
#line 2061 "lalr_assignment3.tab.c"
    break;

  case 81:
#line 227 "lalr_assignment3.y"
                                                         { log_reduction("ambiguous_expression -> ambiguous_expression == ambiguous_expression"); }
#line 2067 "lalr_assignment3.tab.c"
    break;

  case 82:
#line 228 "lalr_assignment3.y"
                                                          { log_reduction("ambiguous_expression -> ambiguous_expression != ambiguous_expression"); }
#line 2073 "lalr_assignment3.tab.c"
    break;

  case 83:
#line 229 "lalr_assignment3.y"
                                                          { log_reduction("ambiguous_expression -> ambiguous_expression < ambiguous_expression"); }
#line 2079 "lalr_assignment3.tab.c"
    break;

  case 84:
#line 230 "lalr_assignment3.y"
                                                             { log_reduction("ambiguous_expression -> ambiguous_expression > ambiguous_expression"); }
#line 2085 "lalr_assignment3.tab.c"
    break;

  case 85:
#line 231 "lalr_assignment3.y"
                                                           { log_reduction("ambiguous_expression -> ambiguous_expression <= ambiguous_expression"); }
#line 2091 "lalr_assignment3.tab.c"
    break;

  case 86:
#line 232 "lalr_assignment3.y"
                                                              { log_reduction("ambiguous_expression -> ambiguous_expression >= ambiguous_expression"); }
#line 2097 "lalr_assignment3.tab.c"
    break;

  case 87:
#line 233 "lalr_assignment3.y"
                                                          { log_reduction("ambiguous_expression -> ambiguous_expression <=> ambiguous_expression"); }
#line 2103 "lalr_assignment3.tab.c"
    break;

  case 88:
#line 234 "lalr_assignment3.y"
                                                         { log_reduction("ambiguous_expression -> ambiguous_expression + ambiguous_expression"); }
#line 2109 "lalr_assignment3.tab.c"
    break;

  case 89:
#line 235 "lalr_assignment3.y"
                                                         { log_reduction("ambiguous_expression -> ambiguous_expression - ambiguous_expression"); }
#line 2115 "lalr_assignment3.tab.c"
    break;

  case 90:
#line 236 "lalr_assignment3.y"
                                                         { log_reduction("ambiguous_expression -> ambiguous_expression * ambiguous_expression"); }
#line 2121 "lalr_assignment3.tab.c"
    break;

  case 91:
#line 237 "lalr_assignment3.y"
                                                         { log_reduction("ambiguous_expression -> ambiguous_expression / ambiguous_expression"); }
#line 2127 "lalr_assignment3.tab.c"
    break;

  case 92:
#line 238 "lalr_assignment3.y"
                                                         { log_reduction("ambiguous_expression -> ambiguous_expression % ambiguous_expression"); }
#line 2133 "lalr_assignment3.tab.c"
    break;

  case 93:
#line 242 "lalr_assignment3.y"
                                                         { log_reduction("unary_expression -> postfix_expression"); }
#line 2139 "lalr_assignment3.tab.c"
    break;

  case 94:
#line 243 "lalr_assignment3.y"
                                                         { log_reduction("unary_expression -> ++ unary_expression"); }
#line 2145 "lalr_assignment3.tab.c"
    break;

  case 95:
#line 244 "lalr_assignment3.y"
                                                         { log_reduction("unary_expression -> -- unary_expression"); }
#line 2151 "lalr_assignment3.tab.c"
    break;

  case 96:
#line 245 "lalr_assignment3.y"
                                                         { log_reduction("unary_expression -> + unary_expression"); }
#line 2157 "lalr_assignment3.tab.c"
    break;

  case 97:
#line 246 "lalr_assignment3.y"
                                                         { log_reduction("unary_expression -> - unary_expression"); }
#line 2163 "lalr_assignment3.tab.c"
    break;

  case 98:
#line 247 "lalr_assignment3.y"
                                                         { log_reduction("unary_expression -> ~ unary_expression"); }
#line 2169 "lalr_assignment3.tab.c"
    break;

  case 99:
#line 248 "lalr_assignment3.y"
                                                         { log_reduction("unary_expression -> & unary_expression"); }
#line 2175 "lalr_assignment3.tab.c"
    break;

  case 100:
#line 249 "lalr_assignment3.y"
                                                         { log_reduction("unary_expression -> * unary_expression"); }
#line 2181 "lalr_assignment3.tab.c"
    break;

  case 101:
#line 250 "lalr_assignment3.y"
                                                         { log_reduction("unary_expression -> sizeof unary_expression"); }
#line 2187 "lalr_assignment3.tab.c"
    break;

  case 102:
#line 251 "lalr_assignment3.y"
                                                         { log_reduction("unary_expression -> sizeof ( type_specifier )"); }
#line 2193 "lalr_assignment3.tab.c"
    break;

  case 103:
#line 255 "lalr_assignment3.y"
                                                         { log_reduction("postfix_expression -> primary_expression"); }
#line 2199 "lalr_assignment3.tab.c"
    break;

  case 104:
#line 256 "lalr_assignment3.y"
                                                         { log_reduction("postfix_expression -> postfix_expression [ expression ]"); }
#line 2205 "lalr_assignment3.tab.c"
    break;

  case 105:
#line 258 "lalr_assignment3.y"
                                                        { log_reduction("postfix_expression -> postfix_expression ( argument_expression_list_opt )"); }
#line 2211 "lalr_assignment3.tab.c"
    break;

  case 106:
#line 259 "lalr_assignment3.y"
                                                         { log_reduction("postfix_expression -> postfix_expression . identifier"); }
#line 2217 "lalr_assignment3.tab.c"
    break;

  case 107:
#line 260 "lalr_assignment3.y"
                                                         { log_reduction("postfix_expression -> postfix_expression -> identifier"); }
#line 2223 "lalr_assignment3.tab.c"
    break;

  case 108:
#line 261 "lalr_assignment3.y"
                                                         { log_reduction("postfix_expression -> postfix_expression ++"); }
#line 2229 "lalr_assignment3.tab.c"
    break;

  case 109:
#line 262 "lalr_assignment3.y"
                                                         { log_reduction("postfix_expression -> postfix_expression --"); }
#line 2235 "lalr_assignment3.tab.c"
    break;

  case 110:
#line 266 "lalr_assignment3.y"
                                                         { log_reduction("argument_expression_list_opt -> argument_expression_list"); }
#line 2241 "lalr_assignment3.tab.c"
    break;

  case 111:
#line 267 "lalr_assignment3.y"
                                                         { log_reduction("argument_expression_list_opt -> epsilon"); }
#line 2247 "lalr_assignment3.tab.c"
    break;

  case 112:
#line 271 "lalr_assignment3.y"
                                                         { log_reduction("argument_expression_list -> assignment_expression"); }
#line 2253 "lalr_assignment3.tab.c"
    break;

  case 113:
#line 272 "lalr_assignment3.y"
                                                           { log_reduction("argument_expression_list -> argument_expression_list , assignment_expression"); }
#line 2259 "lalr_assignment3.tab.c"
    break;

  case 114:
#line 276 "lalr_assignment3.y"
                                                         { log_reduction("primary_expression -> identifier"); }
#line 2265 "lalr_assignment3.tab.c"
    break;

  case 115:
#line 277 "lalr_assignment3.y"
                                                         { log_reduction("primary_expression -> constant"); }
#line 2271 "lalr_assignment3.tab.c"
    break;

  case 116:
#line 278 "lalr_assignment3.y"
                                                         { log_reduction("primary_expression -> string_literal_sequence"); }
#line 2277 "lalr_assignment3.tab.c"
    break;

  case 117:
#line 279 "lalr_assignment3.y"
                                                         { log_reduction("primary_expression -> ( expression )"); }
#line 2283 "lalr_assignment3.tab.c"
    break;

  case 118:
#line 283 "lalr_assignment3.y"
                                                         { log_reduction("constant -> integer_constant"); }
#line 2289 "lalr_assignment3.tab.c"
    break;

  case 119:
#line 284 "lalr_assignment3.y"
                                                         { log_reduction("constant -> hex_constant"); }
#line 2295 "lalr_assignment3.tab.c"
    break;

  case 120:
#line 285 "lalr_assignment3.y"
                                                         { log_reduction("constant -> float_constant"); }
#line 2301 "lalr_assignment3.tab.c"
    break;

  case 121:
#line 286 "lalr_assignment3.y"
                                                         { log_reduction("constant -> char_constant"); }
#line 2307 "lalr_assignment3.tab.c"
    break;

  case 122:
#line 290 "lalr_assignment3.y"
                                                         { log_reduction("string_literal_sequence -> string_literal"); }
#line 2313 "lalr_assignment3.tab.c"
    break;

  case 123:
#line 291 "lalr_assignment3.y"
                                                         { log_reduction("string_literal_sequence -> string_literal_sequence string_literal"); }
#line 2319 "lalr_assignment3.tab.c"
    break;


#line 2323 "lalr_assignment3.tab.c"

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
#line 294 "lalr_assignment3.y"


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
