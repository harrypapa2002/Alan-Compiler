/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_byte = 258,
     T_else = 259,
     T_false = 260,
     T_if = 261,
     T_int = 262,
     T_proc = 263,
     T_reference = 264,
     T_return = 265,
     T_while = 266,
     T_true = 267,
     T_lte = 268,
     T_gte = 269,
     T_eq = 270,
     T_neq = 271,
     T_string = 272,
     T_const = 273,
     T_id = 274,
     T_char = 275,
     UNOP = 276
   };
#endif
/* Tokens.  */
#define T_byte 258
#define T_else 259
#define T_false 260
#define T_if 261
#define T_int 262
#define T_proc 263
#define T_reference 264
#define T_return 265
#define T_while 266
#define T_true 267
#define T_lte 268
#define T_gte 269
#define T_eq 270
#define T_neq 271
#define T_string 272
#define T_const 273
#define T_id 274
#define T_char 275
#define UNOP 276




/* Copy the first part of user declarations.  */
#line 1 "parser/parser.y"

#include <stdio.h>
#include <stdlib.h>
#include "../lexer/lexer.hpp"
#include "../ast/ast.hpp"
#include "../symbol/types.hpp"
#include "../symbol/symbol.hpp"
#include "../symbol/symbol_table.hpp"

Type *typeInteger = new IntType();
Type *typeByte = new ByteType();
Type *typeVoid = new VoidType();




/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 18 "parser/parser.y"
{
    ExprList *exprlist;
    LocalDefList *localdefs;
    FparList *fparlist;
    StmtList *stmtlist;
    Type *type;
    int num;
    std::string *str;
    unsigned char chr;
    char op;
    compare comp;
    std::string *var;
    AST *ast;
    FuncDef *funcdef;
    VarDef *vardef;
    LocalDef *localdef;
    Fpar *fpardef;
    Stmt *stmt;
    Expr *expr;
    Cond *cond;
    Lval *lvalue;
    FuncCall *fun;
}
/* Line 193 of yacc.c.  */
#line 178 "parser/parser.cpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 191 "parser/parser.cpp"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   201

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  65
/* YYNRULES -- Number of states.  */
#define YYNSTATES  135

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   276

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    41,     2,     2,     2,    29,    21,     2,
      31,    32,    27,    25,    34,    26,     2,    28,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    33,    37,
      23,    38,    24,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    35,     2,    36,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    39,    22,    40,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    30
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,    14,    22,    25,    30,    34,    35,
      39,    41,    43,    47,    49,    51,    53,    55,    57,    58,
      61,    69,    74,    76,    81,    83,    86,    94,   100,   106,
     110,   113,   114,   117,   121,   126,   130,   133,   135,   137,
     139,   143,   145,   148,   151,   155,   159,   163,   167,   171,
     172,   176,   181,   183,   185,   187,   189,   193,   196,   200,
     204,   208,   212,   216,   220,   224
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      43,     0,    -1,    44,    -1,    19,    31,    45,    32,    33,
      50,    52,    56,    -1,    19,    31,    32,    33,    50,    52,
      56,    -1,    46,    47,    -1,    19,    33,     9,    49,    -1,
      19,    33,    49,    -1,    -1,    34,    46,    47,    -1,     7,
      -1,     3,    -1,    48,    35,    36,    -1,    48,    -1,    48,
      -1,     8,    -1,    44,    -1,    53,    -1,    -1,    51,    52,
      -1,    19,    33,    48,    35,    18,    36,    37,    -1,    19,
      33,    48,    37,    -1,    37,    -1,    61,    38,    59,    37,
      -1,    56,    -1,    57,    37,    -1,     6,    31,    62,    32,
      54,     4,    54,    -1,     6,    31,    62,    32,    54,    -1,
      11,    31,    62,    32,    54,    -1,    10,    59,    37,    -1,
      10,    37,    -1,    -1,    54,    55,    -1,    39,    55,    40,
      -1,    19,    31,    58,    32,    -1,    19,    31,    32,    -1,
      59,    60,    -1,    18,    -1,    20,    -1,    61,    -1,    31,
      59,    32,    -1,    57,    -1,    25,    59,    -1,    26,    59,
      -1,    59,    25,    59,    -1,    59,    26,    59,    -1,    59,
      27,    59,    -1,    59,    28,    59,    -1,    59,    29,    59,
      -1,    -1,    34,    59,    60,    -1,    19,    35,    59,    36,
      -1,    19,    -1,    17,    -1,    12,    -1,     5,    -1,    31,
      62,    32,    -1,    41,    62,    -1,    59,    15,    59,    -1,
      59,    16,    59,    -1,    59,    23,    59,    -1,    59,    24,
      59,    -1,    59,    13,    59,    -1,    59,    14,    59,    -1,
      62,    21,    62,    -1,    62,    22,    62,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    90,    90,    98,    99,   102,   105,   106,   109,   110,
     113,   114,   117,   118,   121,   122,   125,   126,   129,   130,
     133,   134,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   148,   149,   152,   155,   156,   159,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   176,
     177,   180,   181,   182,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "\"byte\"", "\"else\"", "\"false\"",
  "\"if\"", "\"int\"", "\"proc\"", "\"reference\"", "\"return\"",
  "\"while\"", "\"true\"", "\"<=\"", "\">=\"", "\"==\"", "\"!=\"",
  "T_string", "T_const", "T_id", "T_char", "'&'", "'|'", "'<'", "'>'",
  "'+'", "'-'", "'*'", "'/'", "'%'", "UNOP", "'('", "')'", "':'", "','",
  "'['", "']'", "';'", "'='", "'{'", "'}'", "'!'", "$accept", "program",
  "funcdef", "fparlist", "fpardef", "fpardefs", "datatype", "type",
  "rtype", "localdef", "localdefs", "vardef", "stmt", "stmts",
  "compoundstmt", "funccall", "exprlist", "expr", "exprs", "lvalue",
  "cond", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,    38,   124,    60,    62,    43,    45,    42,    47,    37,
     276,    40,    41,    58,    44,    91,    93,    59,    61,   123,
     125,    33
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    42,    43,    44,    44,    45,    46,    46,    47,    47,
      48,    48,    49,    49,    50,    50,    51,    51,    52,    52,
      53,    53,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    55,    55,    56,    57,    57,    58,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    60,
      60,    61,    61,    61,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     8,     7,     2,     4,     3,     0,     3,
       1,     1,     3,     1,     1,     1,     1,     1,     0,     2,
       7,     4,     1,     4,     1,     2,     7,     5,     5,     3,
       2,     0,     2,     3,     4,     3,     2,     1,     1,     1,
       3,     1,     2,     2,     3,     3,     3,     3,     3,     0,
       3,     4,     1,     1,     1,     1,     3,     2,     3,     3,
       3,     3,     3,     3,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     0,     1,     0,     0,     0,     8,
       0,     0,     0,     0,     5,    11,    10,     0,    13,     7,
      15,    14,    18,     0,     8,     6,     0,     0,    16,    18,
       0,    17,    18,     9,    12,     0,    19,    31,     4,     0,
       0,     0,     0,     0,    53,    52,    22,    31,     0,    24,
       0,     0,     3,     0,    21,     0,    37,    38,     0,     0,
       0,    30,    41,     0,    39,     0,     0,     0,    32,    33,
      25,     0,     0,    55,    54,     0,     0,     0,     0,    42,
      43,     0,     0,     0,     0,     0,     0,    29,     0,    35,
       0,    49,     0,     0,     0,     0,     0,    57,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    40,    44,    45,
      46,    47,    48,     0,    34,     0,    36,    51,    23,    20,
      56,    62,    63,    58,    59,    60,    61,    64,    65,    27,
      28,    49,     0,    50,    26
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,    28,     8,     9,    14,    18,    19,    22,    29,
      30,    31,    47,    48,    49,    62,    90,    77,   116,    64,
      78
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -101
static const yytype_int16 yypact[] =
{
     -15,   -22,    24,  -101,    -4,  -101,    -8,     0,    16,    40,
     100,   113,    34,    74,  -101,  -101,  -101,    82,    53,  -101,
    -101,  -101,    85,   113,    40,  -101,    83,    77,  -101,    85,
      79,  -101,    85,  -101,  -101,    82,  -101,    -3,  -101,    79,
     159,    98,    80,   110,  -101,    33,  -101,    -3,    90,  -101,
     122,   127,  -101,   142,  -101,    61,  -101,  -101,   136,   136,
     136,  -101,  -101,    12,  -101,    61,   132,   136,  -101,  -101,
    -101,   136,   130,  -101,  -101,    61,    61,   119,    50,  -101,
    -101,   158,   136,   136,   136,   136,   136,  -101,    62,  -101,
     146,   148,   143,    28,   144,    99,    69,  -101,   136,   136,
     136,   136,   136,   136,    61,    61,    -3,  -101,   164,   164,
    -101,  -101,  -101,    -3,  -101,   136,  -101,  -101,  -101,  -101,
    -101,   111,   111,   111,   111,   111,   111,  -101,  -101,   176,
    -101,   148,    -3,  -101,  -101
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -101,  -101,   188,  -101,   182,   165,    -6,   180,   175,  -101,
      18,  -101,  -100,   152,    -9,   -37,  -101,   -40,    70,   -36,
     -53
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      50,    51,    63,    41,     1,    21,   129,    42,    43,     4,
      50,    51,    88,   130,    44,     6,    45,    21,    79,    80,
      81,    38,    96,    97,     5,    10,    91,    92,     7,    40,
      52,    93,   134,    11,    46,    95,    37,    82,    83,    84,
      85,    86,   108,   109,   110,   111,   112,    36,    12,    87,
      39,   127,   128,    82,    83,    84,    85,    86,   121,   122,
     123,   124,   125,   126,    66,   118,    73,    23,    67,    50,
      51,   104,   105,    74,    13,   131,    50,    51,    44,    56,
      45,    57,   106,   104,   105,    15,    58,    59,    26,    16,
     104,   105,    75,     6,   113,    50,    51,    44,    56,    45,
      57,   120,    76,    15,    27,    58,    59,    16,     4,    17,
      35,    60,    98,    99,   100,   101,    15,    61,    37,    34,
      16,    20,   102,   103,    82,    83,    84,    85,    86,    55,
      69,   107,    98,    99,   100,   101,    82,    83,    84,    85,
      86,    65,   102,   103,    82,    83,    84,    85,    86,    44,
      56,    45,    57,    44,    56,    45,    57,    58,    59,    70,
      72,    58,    59,    60,    89,    71,    94,    60,    82,    83,
      84,    85,    86,    82,    83,    84,    85,    86,   114,   117,
     132,   119,   115,    82,    83,    84,    85,    86,     3,    33,
     107,    84,    85,    86,    53,    24,    54,    25,    32,    68,
       0,   133
};

static const yytype_int16 yycheck[] =
{
      37,    37,    42,     6,    19,    11,   106,    10,    11,    31,
      47,    47,    65,   113,    17,    19,    19,    23,    58,    59,
      60,    30,    75,    76,     0,    33,    66,    67,    32,    35,
      39,    71,   132,    33,    37,    75,    39,    25,    26,    27,
      28,    29,    82,    83,    84,    85,    86,    29,    32,    37,
      32,   104,   105,    25,    26,    27,    28,    29,    98,    99,
     100,   101,   102,   103,    31,    37,     5,    33,    35,   106,
     106,    21,    22,    12,    34,   115,   113,   113,    17,    18,
      19,    20,    32,    21,    22,     3,    25,    26,    35,     7,
      21,    22,    31,    19,    32,   132,   132,    17,    18,    19,
      20,    32,    41,     3,    19,    25,    26,     7,    31,     9,
      33,    31,    13,    14,    15,    16,     3,    37,    39,    36,
       7,     8,    23,    24,    25,    26,    27,    28,    29,    31,
      40,    32,    13,    14,    15,    16,    25,    26,    27,    28,
      29,    31,    23,    24,    25,    26,    27,    28,    29,    17,
      18,    19,    20,    17,    18,    19,    20,    25,    26,    37,
      18,    25,    26,    31,    32,    38,    36,    31,    25,    26,
      27,    28,    29,    25,    26,    27,    28,    29,    32,    36,
       4,    37,    34,    25,    26,    27,    28,    29,     0,    24,
      32,    27,    28,    29,    35,    13,    37,    17,    23,    47,
      -1,   131
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    19,    43,    44,    31,     0,    19,    32,    45,    46,
      33,    33,    32,    34,    47,     3,     7,     9,    48,    49,
       8,    48,    50,    33,    46,    49,    35,    19,    44,    51,
      52,    53,    50,    47,    36,    33,    52,    39,    56,    52,
      48,     6,    10,    11,    17,    19,    37,    54,    55,    56,
      57,    61,    56,    35,    37,    31,    18,    20,    25,    26,
      31,    37,    57,    59,    61,    31,    31,    35,    55,    40,
      37,    38,    18,     5,    12,    31,    41,    59,    62,    59,
      59,    59,    25,    26,    27,    28,    29,    37,    62,    32,
      58,    59,    59,    59,    36,    59,    62,    62,    13,    14,
      15,    16,    23,    24,    21,    22,    32,    32,    59,    59,
      59,    59,    59,    32,    32,    34,    60,    36,    37,    37,
      32,    59,    59,    59,    59,    59,    59,    62,    62,    54,
      54,    59,     4,    60,    54
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
     `$$ = $1'.

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
#line 90 "parser/parser.y"
    {   
            (yyvsp[(1) - (1)].funcdef)->sem();
            (yyvsp[(1) - (1)].funcdef)->llvm_igen();
        ;}
    break;

  case 3:
#line 98 "parser/parser.y"
    { (yyval.funcdef) = new FuncDef((yyvsp[(1) - (8)].str), (yyvsp[(6) - (8)].type), (yyvsp[(7) - (8)].localdefs), (yyvsp[(8) - (8)].stmtlist), (yyvsp[(3) - (8)].fparlist)); ;}
    break;

  case 4:
#line 99 "parser/parser.y"
    { (yyval.funcdef) = new FuncDef((yyvsp[(1) - (7)].str), (yyvsp[(5) - (7)].type), (yyvsp[(6) - (7)].localdefs), (yyvsp[(7) - (7)].stmtlist)); ;}
    break;

  case 5:
#line 102 "parser/parser.y"
    { (yyvsp[(2) - (2)].fparlist)->append((yyvsp[(1) - (2)].fpardef)); (yyval.fparlist) = (yyvsp[(2) - (2)].fparlist); ;}
    break;

  case 6:
#line 105 "parser/parser.y"
    { (yyval.fpardef) = new Fpar((yyvsp[(1) - (4)].str), (yyvsp[(4) - (4)].type), ParameterType::REFERENCE); ;}
    break;

  case 7:
#line 106 "parser/parser.y"
    { (yyval.fpardef) = new Fpar((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].type), ParameterType::VALUE); ;}
    break;

  case 8:
#line 109 "parser/parser.y"
    { (yyval.fparlist) = new FparList(); ;}
    break;

  case 9:
#line 110 "parser/parser.y"
    { (yyvsp[(3) - (3)].fparlist)->append((yyvsp[(2) - (3)].fpardef)); (yyval.fparlist) = (yyvsp[(3) - (3)].fparlist); ;}
    break;

  case 10:
#line 113 "parser/parser.y"
    { (yyval.type) = typeInteger; ;}
    break;

  case 11:
#line 114 "parser/parser.y"
    { (yyval.type) = typeByte; ;}
    break;

  case 12:
#line 117 "parser/parser.y"
    {  (yyval.type) = new ArrayType((yyvsp[(1) - (3)].type));;}
    break;

  case 13:
#line 118 "parser/parser.y"
    { (yyval.type) = (yyvsp[(1) - (1)].type); ;}
    break;

  case 14:
#line 121 "parser/parser.y"
    { (yyval.type) = (yyvsp[(1) - (1)].type); ;}
    break;

  case 15:
#line 122 "parser/parser.y"
    { (yyval.type) = typeVoid; ;}
    break;

  case 16:
#line 125 "parser/parser.y"
    { (yyval.localdef) = (yyvsp[(1) - (1)].funcdef); ;}
    break;

  case 17:
#line 126 "parser/parser.y"
    { (yyval.localdef) = (yyvsp[(1) - (1)].vardef); ;}
    break;

  case 18:
#line 129 "parser/parser.y"
    { (yyval.localdefs) = new LocalDefList(); ;}
    break;

  case 19:
#line 130 "parser/parser.y"
    { (yyvsp[(2) - (2)].localdefs)->append((yyvsp[(1) - (2)].localdef)); (yyval.localdefs) = (yyvsp[(2) - (2)].localdefs); ;}
    break;

  case 20:
#line 133 "parser/parser.y"
    { (yyval.vardef) = new VarDef((yyvsp[(1) - (7)].str), (yyvsp[(3) - (7)].type), true, (yyvsp[(5) - (7)].num)); ;}
    break;

  case 21:
#line 134 "parser/parser.y"
    { (yyval.vardef) = new VarDef((yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].type), false); ;}
    break;

  case 22:
#line 137 "parser/parser.y"
    { (yyval.stmt) = new Empty();;}
    break;

  case 23:
#line 138 "parser/parser.y"
    { (yyval.stmt) = new Let((yyvsp[(1) - (4)].lvalue), (yyvsp[(3) - (4)].expr)); ;}
    break;

  case 24:
#line 139 "parser/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmtlist); ;}
    break;

  case 25:
#line 140 "parser/parser.y"
    { (yyval.stmt) = new ProcCall((yyvsp[(1) - (2)].fun)); ;}
    break;

  case 26:
#line 141 "parser/parser.y"
    { (yyval.stmt) = new If((yyvsp[(3) - (7)].cond), (yyvsp[(5) - (7)].stmt), (yyvsp[(7) - (7)].stmt)); ;}
    break;

  case 27:
#line 142 "parser/parser.y"
    { (yyval.stmt) = new If((yyvsp[(3) - (5)].cond), (yyvsp[(5) - (5)].stmt)); ;}
    break;

  case 28:
#line 143 "parser/parser.y"
    { (yyval.stmt) = new While((yyvsp[(3) - (5)].cond), (yyvsp[(5) - (5)].stmt)); ;}
    break;

  case 29:
#line 144 "parser/parser.y"
    { (yyval.stmt) = new Return((yyvsp[(2) - (3)].expr)); ;}
    break;

  case 30:
#line 145 "parser/parser.y"
    { (yyval.stmt) = new Return(); ;}
    break;

  case 31:
#line 148 "parser/parser.y"
    { (yyval.stmtlist) = new StmtList(); ;}
    break;

  case 32:
#line 149 "parser/parser.y"
    { (yyvsp[(2) - (2)].stmtlist)->append((yyvsp[(1) - (2)].stmt)); (yyval.stmtlist) = (yyvsp[(2) - (2)].stmtlist); ;}
    break;

  case 33:
#line 152 "parser/parser.y"
    { (yyval.stmtlist) = (yyvsp[(2) - (3)].stmtlist); ;}
    break;

  case 34:
#line 155 "parser/parser.y"
    { (yyval.fun) = new FuncCall((yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].exprlist));;}
    break;

  case 35:
#line 156 "parser/parser.y"
    { (yyval.fun) = new FuncCall((yyvsp[(1) - (3)].str)); ;}
    break;

  case 36:
#line 159 "parser/parser.y"
    { (yyvsp[(2) - (2)].exprlist)->append((yyvsp[(1) - (2)].expr)); (yyval.exprlist) = (yyvsp[(2) - (2)].exprlist); ;}
    break;

  case 37:
#line 162 "parser/parser.y"
    { (yyval.expr) = new IntConst((yyvsp[(1) - (1)].num)); ;}
    break;

  case 38:
#line 163 "parser/parser.y"
    { (yyval.expr) = new CharConst((yyvsp[(1) - (1)].chr)); ;}
    break;

  case 39:
#line 164 "parser/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].lvalue);;}
    break;

  case 40:
#line 165 "parser/parser.y"
    { (yyval.expr) = (yyvsp[(2) - (3)].expr);;}
    break;

  case 41:
#line 166 "parser/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].fun);;}
    break;

  case 42:
#line 167 "parser/parser.y"
    { (yyval.expr) = new UnOp((yyvsp[(1) - (2)].op), (yyvsp[(2) - (2)].expr)); ;}
    break;

  case 43:
#line 168 "parser/parser.y"
    { (yyval.expr) = new UnOp((yyvsp[(1) - (2)].op), (yyvsp[(2) - (2)].expr)); ;}
    break;

  case 44:
#line 169 "parser/parser.y"
    { (yyval.expr) = new BinOp((yyvsp[(1) - (3)].expr), (yyvsp[(2) - (3)].op), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 45:
#line 170 "parser/parser.y"
    { (yyval.expr) = new BinOp((yyvsp[(1) - (3)].expr), (yyvsp[(2) - (3)].op), (yyvsp[(3) - (3)].expr));  ;}
    break;

  case 46:
#line 171 "parser/parser.y"
    { (yyval.expr) = new BinOp((yyvsp[(1) - (3)].expr), (yyvsp[(2) - (3)].op), (yyvsp[(3) - (3)].expr));  ;}
    break;

  case 47:
#line 172 "parser/parser.y"
    { (yyval.expr) = new BinOp((yyvsp[(1) - (3)].expr), (yyvsp[(2) - (3)].op), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 48:
#line 173 "parser/parser.y"
    { (yyval.expr) = new BinOp((yyvsp[(1) - (3)].expr), (yyvsp[(2) - (3)].op), (yyvsp[(3) - (3)].expr));  ;}
    break;

  case 49:
#line 176 "parser/parser.y"
    { (yyval.exprlist) = new ExprList(); ;}
    break;

  case 50:
#line 177 "parser/parser.y"
    { (yyvsp[(3) - (3)].exprlist)->append((yyvsp[(2) - (3)].expr)); (yyval.exprlist) = (yyvsp[(3) - (3)].exprlist); ;}
    break;

  case 51:
#line 180 "parser/parser.y"
    { (yyval.lvalue) = new ArrayAccess((yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].expr)); ;}
    break;

  case 52:
#line 181 "parser/parser.y"
    { (yyval.lvalue) = new Id((yyvsp[(1) - (1)].str)); ;}
    break;

  case 53:
#line 182 "parser/parser.y"
    { (yyval.lvalue) = new StringConst((yyvsp[(1) - (1)].str)); ;}
    break;

  case 54:
#line 185 "parser/parser.y"
    { (yyval.cond) = new BoolConst(true); ;}
    break;

  case 55:
#line 186 "parser/parser.y"
    { (yyval.cond) = new BoolConst(false);;}
    break;

  case 56:
#line 187 "parser/parser.y"
    { (yyval.cond) = (yyvsp[(2) - (3)].cond); ;}
    break;

  case 57:
#line 188 "parser/parser.y"
    { (yyval.cond) = new CondUnOp('!',(yyvsp[(2) - (2)].cond)); ;}
    break;

  case 58:
#line 189 "parser/parser.y"
    { (yyval.cond) = new CondCompOp((yyvsp[(1) - (3)].expr), (yyvsp[(2) - (3)].comp), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 59:
#line 190 "parser/parser.y"
    { (yyval.cond) = new CondCompOp((yyvsp[(1) - (3)].expr), (yyvsp[(2) - (3)].comp), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 60:
#line 191 "parser/parser.y"
    { (yyval.cond) = new CondCompOp((yyvsp[(1) - (3)].expr), (yyvsp[(2) - (3)].comp), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 61:
#line 192 "parser/parser.y"
    { (yyval.cond) = new CondCompOp((yyvsp[(1) - (3)].expr), (yyvsp[(2) - (3)].comp), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 62:
#line 193 "parser/parser.y"
    { (yyval.cond) = new CondCompOp((yyvsp[(1) - (3)].expr), (yyvsp[(2) - (3)].comp), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 63:
#line 194 "parser/parser.y"
    { (yyval.cond) = new CondCompOp((yyvsp[(1) - (3)].expr), (yyvsp[(2) - (3)].comp), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 64:
#line 195 "parser/parser.y"
    { (yyval.cond) = new CondBoolOp((yyvsp[(1) - (3)].cond), (yyvsp[(2) - (3)].op), (yyvsp[(3) - (3)].cond)); ;}
    break;

  case 65:
#line 196 "parser/parser.y"
    { (yyval.cond) = new CondBoolOp((yyvsp[(1) - (3)].cond), (yyvsp[(2) - (3)].op), (yyvsp[(3) - (3)].cond)); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 1836 "parser/parser.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 199 "parser/parser.y"


int main() {
  int result = yyparse();
  if (result == 0) printf("Success.\n");
  return result;
}
