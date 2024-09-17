/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* "%code top" blocks.  */
#line 1 "bison/cm.y" /* yacc.c:316  */

#include <stdio.h> 
#include <stdlib.h>
#define YYDEBUG 1

#line 69 "src/parse.c" /* yacc.c:316  */



/* Copy the first part of user declarations.  */

#line 75 "src/parse.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parse.h".  */
#ifndef YY_YY_SRC_PARSE_H_INCLUDED
# define YY_YY_SRC_PARSE_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 7 "bison/cm.y" /* yacc.c:355  */

#include "tables.h"
typedef struct strpair {char* str1; char* str2;} strpair;

#line 110 "src/parse.c" /* yacc.c:355  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NUM = 258,
    ID = 259,
    EQUAL = 260,
    PLUS = 261,
    MINUS = 262,
    ASTERISK = 263,
    SLASH = 264,
    LPAREN = 265,
    RPAREN = 266,
    LCURLY = 267,
    RCURLY = 268,
    LBRACK = 269,
    RBRACK = 270,
    SEMICOLON = 271,
    GT = 272,
    LT = 273,
    GT_EQ = 274,
    LT_EQ = 275,
    EQ_EQ = 276,
    NEQ = 277,
    IF = 278,
    ELSE = 279,
    WHILE = 280,
    RETURN = 281,
    COMMA = 282,
    INT = 283,
    VOID = 284
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 12 "bison/cm.y" /* yacc.c:355  */

	int num;
	char *id;
	tac_address addr;
	type_t type_var;
	strpair pair;

#line 160 "src/parse.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_PARSE_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 177 "src/parse.c" /* yacc.c:358  */
/* Unqualified %code blocks.  */
#line 20 "bison/cm.y" /* yacc.c:359  */

int yylex(void);
int yyerror(char* s);
extern int yylineno;
extern FILE *yyin;

void print_tac_address(FILE *stream, tac_address addr);
void print_ft_cell(ft_cell fun);
void print_st_cell(st_cell symbol);

st_cell **symbol_table;
ft_cell fun_table[4096];
tac_cell tac_table[4096];

int st_counter = 0;
int fun_counter = 0;
int tac_counter = 0;
int label_counter = 0;
char *new_label();

#line 200 "src/parse.c" /* yacc.c:359  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   104

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  30
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  65
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  111

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   284

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
      25,    26,    27,    28,    29
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    87,    87,    91,    92,    96,    97,   101,   104,   110,
     114,   110,   121,   122,   126,   127,   131,   132,   136,   139,
     144,   146,   148,   150,   154,   155,   156,   157,   158,   162,
     166,   167,   171,   177,   181,   186,   190,   195,   200,   205,
     210,   214,   219,   224,   228,   233,   238,   242,   243,   244,
     245,   248,   262,   283,   283,   298,   309,   298,   328,   328,
     349,   359,   374,   376,   380,   381
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUM", "ID", "EQUAL", "PLUS", "MINUS",
  "ASTERISK", "SLASH", "LPAREN", "RPAREN", "LCURLY", "RCURLY", "LBRACK",
  "RBRACK", "SEMICOLON", "GT", "LT", "GT_EQ", "LT_EQ", "EQ_EQ", "NEQ",
  "IF", "ELSE", "WHILE", "RETURN", "COMMA", "INT", "VOID", "$accept",
  "tipo", "fator", "termo", "expr_ad", "expr_simples", "expr", "var",
  "programa", "lista_declaracoes", "declaracao", "declaracao_var",
  "declaracao_fun", "$@1", "$@2", "parametros", "lista_parametros",
  "param", "declaracoes_locais", "lista_cmds", "cmd", "bloco_cmd",
  "expr_cmd", "if_cmd", "@3", "@4", "$@5", "while_cmd", "@6", "ret_cmd",
  "chamada_funcao", "argumentos", "lista_argumentos", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284
};
# endif

#define YYPACT_NINF -36

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-36)))

#define YYTABLE_NINF -16

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -13,   -36,   -36,    -1,    14,   -13,   -36,   -36,   -36,    -5,
     -36,   -36,    23,   -36,    21,    19,   -11,    24,    26,    39,
      36,    29,   -36,   -36,    47,   -36,   -13,    50,    54,   -36,
     -36,   -36,   -36,   -13,    64,   -36,    32,    -5,   -36,    -6,
       3,   -36,   -36,    61,    63,    66,   -36,    12,    71,   -36,
      68,    74,   -36,   -36,   -36,   -36,   -36,   -36,   -36,     3,
       3,    69,     3,     3,   -36,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,   -36,     3,   -36,    76,    67,
      80,   -36,    85,    86,   -36,   -36,   -36,    12,    12,    16,
      16,    16,    16,    16,    16,   -36,   -36,     3,   -36,   -36,
     -36,   -36,    54,    54,    60,   -36,   -36,   -36,    75,    54,
     -36
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    13,    12,     0,     0,     2,     3,     5,     6,     9,
       1,     4,     0,     7,     0,     0,     0,     0,    12,     0,
       0,    14,    16,     8,    19,    10,     0,     0,     0,    17,
      18,    20,    11,    22,     0,    21,     0,     0,    49,    51,
       0,    29,    31,     0,     0,     0,    46,    43,    40,    33,
       0,    48,    23,    25,    24,    26,    27,    28,    50,    62,
       0,     0,     0,     0,    60,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    30,     0,    64,     0,    63,
       0,    47,     0,     0,    44,    48,    45,    41,    42,    34,
      35,    36,    37,    38,    39,    32,    61,     0,    52,    53,
      58,    65,     0,     0,     0,    54,    56,    59,     0,     0,
      57
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -36,   -14,   -27,    -8,   -20,   -36,   -30,   -35,   -36,   -36,
      93,    70,   -36,   -36,   -36,   -36,   -36,    78,   -36,   -36,
      -4,   -28,   -36,   -36,   -36,   -36,   -36,   -36,   -36,   -36,
     -36,   -36,   -36
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,    46,    47,    48,    49,    50,    85,     4,     5,
       6,     7,     8,    14,    28,    20,    21,    22,    33,    36,
      52,    53,    54,    55,   102,   103,   108,    56,   104,    57,
      58,    78,    79
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      32,    51,    19,     9,    59,    51,    38,    39,    60,    12,
      61,    13,    19,    40,    10,     1,     2,     1,    18,    34,
      65,    66,    67,    68,    51,    51,    15,    51,    51,    77,
      80,    16,    82,    83,    17,    38,    39,   -15,    84,    86,
      23,    51,    40,    24,    31,    41,    95,    25,    42,    89,
      90,    91,    92,    93,    94,    43,    26,    44,    45,    87,
      88,    27,    51,    38,    39,    30,    31,   101,    37,    51,
      40,    62,    31,    63,   105,   106,    42,    67,    68,    76,
      81,   110,    64,    43,    75,    44,    45,    96,    69,    70,
      71,    72,    73,    74,    97,    98,    99,   100,    11,   109,
     107,     0,     0,    35,    29
};

static const yytype_int8 yycheck[] =
{
      28,    36,    16,     4,    10,    40,     3,     4,    14,    14,
      40,    16,    26,    10,     0,    28,    29,    28,    29,    33,
       8,     9,     6,     7,    59,    60,     3,    62,    63,    59,
      60,    10,    62,    63,    15,     3,     4,    11,    65,    66,
      16,    76,    10,     4,    12,    13,    76,    11,    16,    69,
      70,    71,    72,    73,    74,    23,    27,    25,    26,    67,
      68,    14,    97,     3,     4,    15,    12,    97,     4,   104,
      10,    10,    12,    10,   102,   103,    16,     6,     7,     5,
      11,   109,    16,    23,    16,    25,    26,    11,    17,    18,
      19,    20,    21,    22,    27,    15,    11,    11,     5,    24,
     104,    -1,    -1,    33,    26
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    28,    29,    31,    38,    39,    40,    41,    42,     4,
       0,    40,    14,    16,    43,     3,    10,    15,    29,    31,
      45,    46,    47,    16,     4,    11,    27,    14,    44,    47,
      15,    12,    51,    48,    31,    41,    49,     4,     3,     4,
      10,    13,    16,    23,    25,    26,    32,    33,    34,    35,
      36,    37,    50,    51,    52,    53,    57,    59,    60,    10,
      14,    36,    10,    10,    16,     8,     9,     6,     7,    17,
      18,    19,    20,    21,    22,    16,     5,    36,    61,    62,
      36,    11,    36,    36,    32,    37,    32,    33,    33,    34,
      34,    34,    34,    34,    34,    36,    11,    27,    15,    11,
      11,    36,    54,    55,    58,    51,    51,    50,    56,    24,
      51
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    30,    38,    39,    39,    40,    40,    41,    41,    43,
      44,    42,    31,    31,    45,    45,    46,    46,    47,    47,
      48,    48,    49,    49,    50,    50,    50,    50,    50,    51,
      52,    52,    36,    36,    35,    35,    35,    35,    35,    35,
      35,    34,    34,    34,    33,    33,    33,    32,    32,    32,
      32,    37,    37,    54,    53,    55,    56,    53,    58,    57,
      59,    60,    61,    61,    62,    62
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     3,     6,     0,
       0,     8,     1,     1,     1,     1,     1,     3,     4,     2,
       0,     2,     0,     2,     1,     1,     1,     1,     1,     4,
       2,     1,     3,     1,     3,     3,     3,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     1,     3,     1,     1,
       1,     1,     4,     0,     6,     0,     0,     9,     0,     6,
       2,     4,     0,     1,     1,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  switch (yytype)
    {
          case 3: /* NUM  */
#line 79 "bison/cm.y" /* yacc.c:684  */
      { fprintf(yyo, "%d", ((*yyvaluep).num)); }
#line 767 "src/parse.c" /* yacc.c:684  */
        break;

    case 4: /* ID  */
#line 80 "bison/cm.y" /* yacc.c:684  */
      { fprintf(yyo, "%s", ((*yyvaluep).id)); }
#line 773 "src/parse.c" /* yacc.c:684  */
        break;

    case 31: /* tipo  */
#line 82 "bison/cm.y" /* yacc.c:684  */
      { fprintf(yyo, "%s", str_type[((*yyvaluep).type_var)]); }
#line 779 "src/parse.c" /* yacc.c:684  */
        break;

    case 32: /* fator  */
#line 81 "bison/cm.y" /* yacc.c:684  */
      { print_tac_address(yyo, ((*yyvaluep).addr)); }
#line 785 "src/parse.c" /* yacc.c:684  */
        break;

    case 33: /* termo  */
#line 81 "bison/cm.y" /* yacc.c:684  */
      { print_tac_address(yyo, ((*yyvaluep).addr)); }
#line 791 "src/parse.c" /* yacc.c:684  */
        break;

    case 34: /* expr_ad  */
#line 81 "bison/cm.y" /* yacc.c:684  */
      { print_tac_address(yyo, ((*yyvaluep).addr)); }
#line 797 "src/parse.c" /* yacc.c:684  */
        break;

    case 35: /* expr_simples  */
#line 81 "bison/cm.y" /* yacc.c:684  */
      { print_tac_address(yyo, ((*yyvaluep).addr)); }
#line 803 "src/parse.c" /* yacc.c:684  */
        break;

    case 36: /* expr  */
#line 81 "bison/cm.y" /* yacc.c:684  */
      { print_tac_address(yyo, ((*yyvaluep).addr)); }
#line 809 "src/parse.c" /* yacc.c:684  */
        break;

    case 37: /* var  */
#line 80 "bison/cm.y" /* yacc.c:684  */
      { fprintf(yyo, "%s", ((*yyvaluep).id)); }
#line 815 "src/parse.c" /* yacc.c:684  */
        break;


      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

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
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
          yyp++;
          yyformat++;
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

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
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
#line 87 "bison/cm.y" /* yacc.c:1646  */
    {printf("Programa sintaticamente correto\n");}
#line 1414 "src/parse.c" /* yacc.c:1646  */
    break;

  case 3:
#line 91 "bison/cm.y" /* yacc.c:1646  */
    {;}
#line 1420 "src/parse.c" /* yacc.c:1646  */
    break;

  case 4:
#line 92 "bison/cm.y" /* yacc.c:1646  */
    {;}
#line 1426 "src/parse.c" /* yacc.c:1646  */
    break;

  case 5:
#line 96 "bison/cm.y" /* yacc.c:1646  */
    {;}
#line 1432 "src/parse.c" /* yacc.c:1646  */
    break;

  case 6:
#line 97 "bison/cm.y" /* yacc.c:1646  */
    {;}
#line 1438 "src/parse.c" /* yacc.c:1646  */
    break;

  case 7:
#line 101 "bison/cm.y" /* yacc.c:1646  */
    {
			insert_sym(symbol_table, (yyvsp[-1].id), INT_T, 0);
		}
#line 1446 "src/parse.c" /* yacc.c:1646  */
    break;

  case 8:
#line 104 "bison/cm.y" /* yacc.c:1646  */
    {
			insert_sym(symbol_table, (yyvsp[-4].id), INT_ARR_T, (yyvsp[-2].num));
		}
#line 1454 "src/parse.c" /* yacc.c:1646  */
    break;

  case 9:
#line 110 "bison/cm.y" /* yacc.c:1646  */
    {
			ft_cell new_fun = (ft_cell){.name=(yyvsp[0].id)};
			fun_table[fun_counter] = new_fun;
		}
#line 1463 "src/parse.c" /* yacc.c:1646  */
    break;

  case 10:
#line 114 "bison/cm.y" /* yacc.c:1646  */
    {
			fun_counter++;
		}
#line 1471 "src/parse.c" /* yacc.c:1646  */
    break;

  case 11:
#line 117 "bison/cm.y" /* yacc.c:1646  */
    {;}
#line 1477 "src/parse.c" /* yacc.c:1646  */
    break;

  case 12:
#line 121 "bison/cm.y" /* yacc.c:1646  */
    {(yyval.type_var) = VOID_T;}
#line 1483 "src/parse.c" /* yacc.c:1646  */
    break;

  case 13:
#line 122 "bison/cm.y" /* yacc.c:1646  */
    {(yyval.type_var) = INT_T;}
#line 1489 "src/parse.c" /* yacc.c:1646  */
    break;

  case 14:
#line 126 "bison/cm.y" /* yacc.c:1646  */
    {;}
#line 1495 "src/parse.c" /* yacc.c:1646  */
    break;

  case 15:
#line 127 "bison/cm.y" /* yacc.c:1646  */
    {;}
#line 1501 "src/parse.c" /* yacc.c:1646  */
    break;

  case 16:
#line 131 "bison/cm.y" /* yacc.c:1646  */
    {;}
#line 1507 "src/parse.c" /* yacc.c:1646  */
    break;

  case 17:
#line 132 "bison/cm.y" /* yacc.c:1646  */
    {;}
#line 1513 "src/parse.c" /* yacc.c:1646  */
    break;

  case 18:
#line 136 "bison/cm.y" /* yacc.c:1646  */
    {
			insert_sym(symbol_table, (yyvsp[-2].id), INT_ARR_T, 0);
		}
#line 1521 "src/parse.c" /* yacc.c:1646  */
    break;

  case 19:
#line 139 "bison/cm.y" /* yacc.c:1646  */
    {
			insert_sym(symbol_table, (yyvsp[0].id), INT_T, 0);
		}
#line 1529 "src/parse.c" /* yacc.c:1646  */
    break;

  case 21:
#line 146 "bison/cm.y" /* yacc.c:1646  */
    {;}
#line 1535 "src/parse.c" /* yacc.c:1646  */
    break;

  case 23:
#line 150 "bison/cm.y" /* yacc.c:1646  */
    {;}
#line 1541 "src/parse.c" /* yacc.c:1646  */
    break;

  case 24:
#line 154 "bison/cm.y" /* yacc.c:1646  */
    {;}
#line 1547 "src/parse.c" /* yacc.c:1646  */
    break;

  case 25:
#line 155 "bison/cm.y" /* yacc.c:1646  */
    {;}
#line 1553 "src/parse.c" /* yacc.c:1646  */
    break;

  case 26:
#line 156 "bison/cm.y" /* yacc.c:1646  */
    {;}
#line 1559 "src/parse.c" /* yacc.c:1646  */
    break;

  case 27:
#line 157 "bison/cm.y" /* yacc.c:1646  */
    {;}
#line 1565 "src/parse.c" /* yacc.c:1646  */
    break;

  case 28:
#line 158 "bison/cm.y" /* yacc.c:1646  */
    {;}
#line 1571 "src/parse.c" /* yacc.c:1646  */
    break;

  case 29:
#line 162 "bison/cm.y" /* yacc.c:1646  */
    {;}
#line 1577 "src/parse.c" /* yacc.c:1646  */
    break;

  case 30:
#line 166 "bison/cm.y" /* yacc.c:1646  */
    {;}
#line 1583 "src/parse.c" /* yacc.c:1646  */
    break;

  case 31:
#line 167 "bison/cm.y" /* yacc.c:1646  */
    {;}
#line 1589 "src/parse.c" /* yacc.c:1646  */
    break;

  case 32:
#line 171 "bison/cm.y" /* yacc.c:1646  */
    {
			tac_address id = {.name = (yyvsp[-2].id), .addr_type = NAME};
			tac_cell tmp = {.source1=id, .source2=(yyvsp[0].addr), .inst=CPY};
			tac_table[tac_counter] = tmp;
			(yyval.addr) = make_tmp(tac_counter++);}
#line 1599 "src/parse.c" /* yacc.c:1646  */
    break;

  case 33:
#line 177 "bison/cm.y" /* yacc.c:1646  */
    {;}
#line 1605 "src/parse.c" /* yacc.c:1646  */
    break;

  case 34:
#line 181 "bison/cm.y" /* yacc.c:1646  */
    {
			tac_cell tmp = {.source1=(yyvsp[-2].addr), .source2=(yyvsp[0].addr), .inst=SGT};
			tac_table[tac_counter] = tmp;
			(yyval.addr) = make_tmp(tac_counter++);}
#line 1614 "src/parse.c" /* yacc.c:1646  */
    break;

  case 35:
#line 186 "bison/cm.y" /* yacc.c:1646  */
    {
			tac_cell tmp = {.source1=(yyvsp[-2].addr), .source2=(yyvsp[0].addr), .inst=SLT};
			tac_table[tac_counter] = tmp;
			(yyval.addr) = make_tmp(tac_counter++);}
#line 1623 "src/parse.c" /* yacc.c:1646  */
    break;

  case 36:
#line 190 "bison/cm.y" /* yacc.c:1646  */
    {
			tac_cell tmp = {.source1=(yyvsp[-2].addr), .source2=(yyvsp[0].addr), .inst=SGTE};
			tac_table[tac_counter] = tmp;
			(yyval.addr) = make_tmp(tac_counter++);}
#line 1632 "src/parse.c" /* yacc.c:1646  */
    break;

  case 37:
#line 195 "bison/cm.y" /* yacc.c:1646  */
    {
			tac_cell tmp = {.source1=(yyvsp[-2].addr), .source2=(yyvsp[0].addr), .inst=SLTE};
			tac_table[tac_counter] = tmp;
			(yyval.addr) = make_tmp(tac_counter++);}
#line 1641 "src/parse.c" /* yacc.c:1646  */
    break;

  case 38:
#line 200 "bison/cm.y" /* yacc.c:1646  */
    {
			tac_cell tmp = {.source1=(yyvsp[-2].addr), .source2=(yyvsp[0].addr), .inst=SEQ};
			tac_table[tac_counter] = tmp;
			(yyval.addr) = make_tmp(tac_counter++);}
#line 1650 "src/parse.c" /* yacc.c:1646  */
    break;

  case 39:
#line 205 "bison/cm.y" /* yacc.c:1646  */
    {
			tac_cell tmp = {.source1=(yyvsp[-2].addr), .source2=(yyvsp[0].addr), .inst=SNEQ};
			tac_table[tac_counter] = tmp;
			(yyval.addr) = make_tmp(tac_counter++);}
#line 1659 "src/parse.c" /* yacc.c:1646  */
    break;

  case 40:
#line 210 "bison/cm.y" /* yacc.c:1646  */
    {;}
#line 1665 "src/parse.c" /* yacc.c:1646  */
    break;

  case 41:
#line 214 "bison/cm.y" /* yacc.c:1646  */
    {
			tac_cell tmp = {.source1=(yyvsp[-2].addr), .source2=(yyvsp[0].addr), .inst=ADD};
			tac_table[tac_counter] = tmp;
			(yyval.addr) = make_tmp(tac_counter++);}
#line 1674 "src/parse.c" /* yacc.c:1646  */
    break;

  case 42:
#line 219 "bison/cm.y" /* yacc.c:1646  */
    {
			tac_cell tmp = {.source1=(yyvsp[-2].addr), .source2=(yyvsp[0].addr), .inst=SUB};
			tac_table[tac_counter] = tmp;
			(yyval.addr) = make_tmp(tac_counter++);}
#line 1683 "src/parse.c" /* yacc.c:1646  */
    break;

  case 43:
#line 224 "bison/cm.y" /* yacc.c:1646  */
    {;}
#line 1689 "src/parse.c" /* yacc.c:1646  */
    break;

  case 44:
#line 228 "bison/cm.y" /* yacc.c:1646  */
    {
			tac_cell tmp = {.source1=(yyvsp[-2].addr), .source2=(yyvsp[0].addr), .inst=MUL};
			tac_table[tac_counter] = tmp;
			(yyval.addr) = make_tmp(tac_counter++);}
#line 1698 "src/parse.c" /* yacc.c:1646  */
    break;

  case 45:
#line 233 "bison/cm.y" /* yacc.c:1646  */
    {
			tac_cell tmp = {.source1=(yyvsp[-2].addr), .source2=(yyvsp[0].addr), .inst=DIV};
			tac_table[tac_counter] = tmp;
			(yyval.addr) = make_tmp(tac_counter++);}
#line 1707 "src/parse.c" /* yacc.c:1646  */
    break;

  case 46:
#line 238 "bison/cm.y" /* yacc.c:1646  */
    {;}
#line 1713 "src/parse.c" /* yacc.c:1646  */
    break;

  case 47:
#line 242 "bison/cm.y" /* yacc.c:1646  */
    {(yyval.addr) = (yyvsp[-1].addr);}
#line 1719 "src/parse.c" /* yacc.c:1646  */
    break;

  case 48:
#line 243 "bison/cm.y" /* yacc.c:1646  */
    {(yyval.addr) = (tac_address){.name = (yyvsp[0].id), .addr_type = NAME};}
#line 1725 "src/parse.c" /* yacc.c:1646  */
    break;

  case 49:
#line 244 "bison/cm.y" /* yacc.c:1646  */
    {(yyval.addr) = (tac_address){.constant = (yyvsp[0].num), .addr_type = CONST};}
#line 1731 "src/parse.c" /* yacc.c:1646  */
    break;

  case 50:
#line 245 "bison/cm.y" /* yacc.c:1646  */
    {;}
#line 1737 "src/parse.c" /* yacc.c:1646  */
    break;

  case 51:
#line 248 "bison/cm.y" /* yacc.c:1646  */
    {/* checar se ID foi declarada */
	 		int found = 0;
			st_cell *symbol = find_sym(symbol_table, (yyvsp[0].id));
			if (symbol) {
				found = 1;
				symbol->usado = 1;
			}

			if(!found) {
				printf("%d: ERRO: Variavel %s nao foi declarada!\n", yylineno, (yyvsp[0].id));
				exit(1);
			}
			}
#line 1755 "src/parse.c" /* yacc.c:1646  */
    break;

  case 52:
#line 262 "bison/cm.y" /* yacc.c:1646  */
    {
	 		int found = 0;
	 		for (int i=st_counter; i>=0; i--) {
				st_cell *symbol = find_sym(symbol_table, (yyvsp[-3].id));
				if (symbol) {
					found = 1;
					symbol->usado = 1;
					break;
				}
			}

			if(!found) {
				printf("%d: ERRO: Variavel %s nao foi declarada!\n", yylineno, (yyvsp[-3].id));
				exit(1);
			}
			}
#line 1776 "src/parse.c" /* yacc.c:1646  */
    break;

  case 53:
#line 283 "bison/cm.y" /* yacc.c:1646  */
    {

      char* exit_label = new_label();

      tac_cell jmp_exit = {.jmp_addr=exit_label, .source1=(yyvsp[-1].addr), .inst=JF};
      tac_table[tac_counter++] = jmp_exit;

      (yyval.id) = exit_label;
     }
#line 1790 "src/parse.c" /* yacc.c:1646  */
    break;

  case 54:
#line 291 "bison/cm.y" /* yacc.c:1646  */
    {

      tac_cell opr_exit = { .line_addr = (yyvsp[-1].id), .inst=NOP};
      tac_table[tac_counter++] = opr_exit;

    }
#line 1801 "src/parse.c" /* yacc.c:1646  */
    break;

  case 55:
#line 298 "bison/cm.y" /* yacc.c:1646  */
    {

      char* exit_label = new_label();
      char* else_label = new_label();


      tac_cell jmp_else = {.jmp_addr=else_label, .source1=(yyvsp[-1].addr), .inst=JF};
      tac_table[tac_counter++] = jmp_else;

      (yyval.pair) = (strpair){.str1 = exit_label, .str2 = else_label};

     }
#line 1818 "src/parse.c" /* yacc.c:1646  */
    break;

  case 56:
#line 309 "bison/cm.y" /* yacc.c:1646  */
    {

         tac_cell jump_exit = { .jmp_addr = ((yyvsp[-1].pair).str1), .inst=JMP};
         tac_table[tac_counter++] = jump_exit;

         tac_cell label_else = { .line_addr = (yyvsp[-1].pair).str2, .inst=NOP};
         tac_table[tac_counter++] = label_else;

     }
#line 1832 "src/parse.c" /* yacc.c:1646  */
    break;

  case 57:
#line 318 "bison/cm.y" /* yacc.c:1646  */
    {

        tac_cell opr_exit = { .line_addr = (yyvsp[-4].pair).str1, .inst=NOP};
        tac_table[tac_counter++] = opr_exit;
     }
#line 1842 "src/parse.c" /* yacc.c:1646  */
    break;

  case 58:
#line 328 "bison/cm.y" /* yacc.c:1646  */
    {

        char* top_label = new_label();
        char* botton_label = new_label();

        tac_cell tmp1 = {.jmp_addr=botton_label, .line_addr = top_label, .source1=(yyvsp[-1].addr), .inst=JF};
        tac_table[tac_counter++] = tmp1;

        (yyval.pair) = (strpair){.str1 = top_label, .str2 = botton_label};
    }
#line 1857 "src/parse.c" /* yacc.c:1646  */
    break;

  case 59:
#line 337 "bison/cm.y" /* yacc.c:1646  */
    {

        tac_cell tmp2 = {.jmp_addr=(yyvsp[-1].pair).str1, .inst=JMP};
        tac_table[tac_counter++] = tmp2;

        tac_cell tmp3 = { .line_addr = (yyvsp[-1].pair).str2, .inst=NOP};
        tac_table[tac_counter++] = tmp3;
    }
#line 1870 "src/parse.c" /* yacc.c:1646  */
    break;

  case 60:
#line 349 "bison/cm.y" /* yacc.c:1646  */
    {

        tac_cell op_ret = { .inst=RET};
        tac_table[tac_counter++] = op_ret;
    }
#line 1880 "src/parse.c" /* yacc.c:1646  */
    break;

  case 61:
#line 359 "bison/cm.y" /* yacc.c:1646  */
    {
			int flag = 0;
			for (int i=0; i<fun_counter; i++) {
				if (fun_table[i].name == (yyvsp[-3].id)) {
					flag = 1;
					fun_table[i].usado = 1;
					break;
				}
			}
			if (!flag) {
				printf("%d: ERRO: Funcao %s nao foi declarada!\n", yylineno, (yyvsp[-3].id));
			exit(1);
		}}
#line 1898 "src/parse.c" /* yacc.c:1646  */
    break;

  case 63:
#line 376 "bison/cm.y" /* yacc.c:1646  */
    {;}
#line 1904 "src/parse.c" /* yacc.c:1646  */
    break;

  case 64:
#line 380 "bison/cm.y" /* yacc.c:1646  */
    {;}
#line 1910 "src/parse.c" /* yacc.c:1646  */
    break;

  case 65:
#line 381 "bison/cm.y" /* yacc.c:1646  */
    {;}
#line 1916 "src/parse.c" /* yacc.c:1646  */
    break;


#line 1920 "src/parse.c" /* yacc.c:1646  */
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

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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
                  yystos[*yyssp], yyvsp);
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
#line 384 "bison/cm.y" /* yacc.c:1906  */

void print_st_cell(st_cell symbol) {
	printf("%s: %s", symbol.name, str_type[symbol.sym_type]);
	if (symbol.sym_type == INT_ARR_T)
		printf("[%d]", symbol.len);
	printf(" (usado: %s)\n", symbol.usado?"sim":"nao");
}

void print_ft_cell(ft_cell fun) {
	printf("%s\n", fun.name);
}

void print_tac_address(FILE *stream, tac_address addr) {
	switch (addr.addr_type) {
		case TEMP:
			fprintf(stream, "(%d)", addr.temporary);
			break;

		case CONST:
			fprintf(stream, "%d", addr.constant);
			break;

		case NAME:
			fprintf(stream, "%s", addr.name);
			break;
	}
}

void print_tac_cell(tac_cell cell, int lineno) {
	printf("%d\t", lineno);
	if (cell.line_addr)
		printf("%s: ", cell.line_addr);
	printf(" %s ", str_inst[cell.inst]);
	print_tac_address(stdout, cell.source1);
	printf(" ");
	print_tac_address(stdout, cell.source2);
	if (cell.inst >= JMP && cell.inst <= BLE)
		printf(" %s", cell.jmp_addr);
	printf("\n");
}

char *new_label(){
    char *l = malloc(10);
    if(!l)
        printf("Erro alocando label \n");
    sprintf(l, "L%d", label_counter++);
    return l;
}


int main(int argc, char **argv) {
	if (argc == 2) {
		if (!(yyin = fopen(argv[1], "r"))) {
			perror("Error reading file.\n");
			return 1;
		}
	}
	symbol_table = malloc(sizeof(st_cell*));

//	yydebug = 1;
	yyparse();

	st_cell *current = *symbol_table;
	if (current) {
		while (current) {
			print_st_cell(*current);
			if (!current->usado)
				printf("WARNING: Variavel %s declarada mas nao utilizada!\n", current->name);
			current = current->next;
		}
	}

	for (int i=0; i<fun_counter; i++) {
		if (strcmp(fun_table[i].name, "main") == 0)
			fun_table[i].usado = 1;
		if (!fun_table[i].usado)
			printf("WARNING: Funcao %s declarada mas nao utilizada!\n", fun_table[i].name);
	}

	for (int i = 0; i < tac_counter; i++) {
		print_tac_cell(tac_table[i], i);
	}

}
int yyerror (char *s) /* Called by yyparse on error */
{
	printf ("Erro na linha %d\n", yylineno);
	exit(1);
}
