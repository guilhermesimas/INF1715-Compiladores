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




/* Copy the first part of user declarations.  */
#line 15 "monga.y" /* yacc.c:339  */



#line 70 "monga.tab.c" /* yacc.c:339  */

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
   by #include "monga.tab.h".  */
#ifndef YY_YY_MONGA_TAB_H_INCLUDED
# define YY_YY_MONGA_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "monga.y" /* yacc.c:355  */

	#include "absSyntaxTree.h"	
	#include "types.h"

#line 105 "monga.tab.c" /* yacc.c:355  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TK_VOID = 258,
    TK_CHAR = 259,
    TK_INT = 260,
    TK_FLOAT = 261,
    TK_IF = 262,
    TK_ELSE = 263,
    TK_WHILE = 264,
    TK_NEW = 265,
    TK_RETURN = 266,
    TK_GE = 267,
    TK_LE = 268,
    TK_CE = 269,
    TK_NE = 270,
    TK_AND = 271,
    TK_OR = 272,
    TK_ID = 273,
    TK_NUM_CHAR = 274,
    TK_NUM_INT = 275,
    TK_NUM_FLOAT = 276,
    TK_STRING = 277,
    WO_ELSE = 278
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 20 "monga.y" /* yacc.c:355  */

    char* 	vString;
    int 	vInt;	
    float 	vFloat;
 
    struct id {
        char* 	name;
        int 	lineNumber;
    } vId;

    ABS_node* vNode;	

#line 154 "monga.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_MONGA_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 171 "monga.tab.c" /* yacc.c:358  */
/* Unqualified %code blocks.  */
#line 6 "monga.y" /* yacc.c:359  */

	#include <stdio.h>
		
	int yylex(void);
	void yyerror(char *);
	
	ABS_node* programNode = NULL;

#line 182 "monga.tab.c" /* yacc.c:359  */

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   147

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  124

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   278

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    31,     2,     2,     2,     2,     2,     2,
      28,    29,    32,    34,    26,    30,     2,    33,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    27,
      36,    37,    35,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    24,     2,    25,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    38,     2,    39,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    69,    69,    73,    74,    75,    79,    80,    84,    85,
      89,    93,    94,    98,    99,   103,   104,   105,   106,   107,
     108,   109,   113,   114,   115,   119,   120,   121,   125,   126,
     127,   131,   132,   133,   134,   135,   136,   137,   141,   142,
     146,   147,   151,   152,   156,   157,   161,   165,   166,   170,
     171,   172,   173,   174,   175,   176,   180,   181,   185,   189,
     193,   194,   198,   199,   203,   204,   208,   209,   213,   214
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TK_VOID", "TK_CHAR", "TK_INT",
  "TK_FLOAT", "TK_IF", "TK_ELSE", "TK_WHILE", "TK_NEW", "TK_RETURN",
  "TK_GE", "TK_LE", "TK_CE", "TK_NE", "TK_AND", "TK_OR", "TK_ID",
  "TK_NUM_CHAR", "TK_NUM_INT", "TK_NUM_FLOAT", "TK_STRING", "WO_ELSE",
  "'['", "']'", "','", "';'", "'('", "')'", "'-'", "'!'", "'*'", "'/'",
  "'+'", "'>'", "'<'", "'='", "'{'", "'}'", "$accept", "program",
  "primitiveType", "type", "idList", "variableDeclaration",
  "variableDeclarationChain", "variable", "expBase", "expUnary", "expMult",
  "expAdd", "expCmp", "expAnd", "expLogic", "expressionList",
  "expressionListNonEmpty", "cmdCall", "cmdReturn", "command",
  "commandChain", "block", "parameter", "parameterList",
  "parameterListNonEmpty", "functionDeclaration", "declaration",
  "declarationChain", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,    91,    93,    44,    59,    40,    41,
      45,    33,    42,    47,    43,    62,    60,    61,   123,   125
};
# endif

#define YYPACT_NINF -42

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-42)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -42,     4,    95,   -42,     5,   -42,   -42,   -42,   -42,     8,
     -42,   -42,   -42,   -22,    15,    20,    97,   116,   116,   -42,
      36,   -42,    58,   -42,    89,   -42,    90,   -42,   -42,   116,
      18,    18,   -42,   -42,   -42,   -42,   116,    70,   -42,     0,
     -42,    38,    43,   116,    75,    76,   -42,   -42,   -42,    75,
      42,    42,   -42,    94,   112,   -42,    93,    83,     1,    98,
     -15,   -42,   110,   -42,   -42,    75,    75,   114,   -42,   122,
      75,   -12,   112,   112,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,   -42,   -42,
      24,    32,    59,   122,   111,   115,   -42,    23,     2,   -42,
     -42,    93,    93,    83,    83,    83,    83,    83,    83,     1,
      98,    37,    37,    61,   -42,    75,   -42,   -42,   134,   -42,
     -42,   122,    37,   -42
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      69,     0,     2,     1,     0,     3,     4,     5,     6,     0,
      66,    67,    68,     0,     8,     0,     0,    61,    61,     7,
       0,    10,     0,    62,     0,    60,     0,     9,    59,     0,
       0,     0,    63,    12,    65,    64,    57,     0,    11,     0,
       8,     0,     0,     0,    47,    13,    15,    16,    17,     0,
       0,     0,    58,    18,    22,    25,    28,    31,    38,    40,
       0,    20,     0,    56,    49,     0,     0,     0,    18,    48,
      43,     0,    23,    24,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    50,    51,
       0,     0,     0,    44,     0,    42,    19,     0,     0,    26,
      27,    30,    29,    34,    35,    32,    33,    36,    37,    39,
      41,     0,     0,     0,    46,     0,    52,    14,    54,    53,
      21,    45,     0,    55
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -42,   -42,   -42,    -1,   -42,   107,   -42,   -39,    77,    53,
      54,    27,    60,    57,   -41,   -42,   -42,   -42,   -42,   -20,
     -42,   104,   118,   127,   -42,   -42,   -42,   -42
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     8,    22,    16,    10,    36,    68,    54,    55,
      56,    57,    58,    59,    60,    94,    95,    61,    62,    63,
      39,    64,    23,    24,    25,    11,    12,     2
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      53,     9,    87,    69,     3,    87,    17,    41,    71,    42,
      43,    44,    88,    80,    81,    82,    83,    96,    45,    87,
      46,    47,    48,    13,    90,    91,    14,   117,    49,    93,
      50,    51,    15,    97,    98,    37,    84,    85,    33,    52,
      87,    87,    67,    18,    41,    19,    42,    43,    44,    87,
     116,   113,    43,   111,    27,    45,    33,    46,    47,    48,
      45,   112,    46,    47,    48,    49,    65,    50,    51,    43,
      49,    66,    53,    53,   121,    33,    28,    45,    87,    46,
      47,    48,    15,    53,    19,    43,   120,    49,    40,    50,
      51,   118,   119,    45,    15,    46,    47,    48,     4,     5,
       6,     7,   123,    49,    70,    50,    51,   103,   104,   105,
     106,   107,   108,    78,    86,    29,    29,    79,    30,    31,
       5,     6,     7,    20,    21,    76,    77,    72,    73,    99,
     100,    74,   101,   102,    34,    35,    75,    89,    92,    87,
     114,   115,   122,    38,   110,    26,   109,    32
};

static const yytype_uint8 yycheck[] =
{
      39,     2,    17,    44,     0,    17,    28,     7,    49,     9,
      10,    11,    27,    12,    13,    14,    15,    29,    18,    17,
      20,    21,    22,    18,    65,    66,    18,    25,    28,    70,
      30,    31,    24,    74,    75,    36,    35,    36,    38,    39,
      17,    17,    43,    28,     7,    25,     9,    10,    11,    17,
      27,    92,    10,    29,    18,    18,    38,    20,    21,    22,
      18,    29,    20,    21,    22,    28,    28,    30,    31,    10,
      28,    28,   111,   112,   115,    38,    18,    18,    17,    20,
      21,    22,    24,   122,    25,    10,    25,    28,    18,    30,
      31,   111,   112,    18,    24,    20,    21,    22,     3,     4,
       5,     6,   122,    28,    28,    30,    31,    80,    81,    82,
      83,    84,    85,    30,    16,    26,    26,    34,    29,    29,
       4,     5,     6,    26,    27,    32,    33,    50,    51,    76,
      77,    37,    78,    79,    30,    31,    24,    27,    24,    17,
      29,    26,     8,    36,    87,    18,    86,    29
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    41,    67,     0,     3,     4,     5,     6,    42,    43,
      45,    65,    66,    18,    18,    24,    44,    28,    28,    25,
      26,    27,    43,    62,    63,    64,    63,    18,    18,    26,
      29,    29,    62,    38,    61,    61,    46,    43,    45,    60,
      18,     7,     9,    10,    11,    18,    20,    21,    22,    28,
      30,    31,    39,    47,    48,    49,    50,    51,    52,    53,
      54,    57,    58,    59,    61,    28,    28,    43,    47,    54,
      28,    54,    48,    48,    37,    24,    32,    33,    30,    34,
      12,    13,    14,    15,    35,    36,    16,    17,    27,    27,
      54,    54,    24,    54,    55,    56,    29,    54,    54,    49,
      49,    50,    50,    51,    51,    51,    51,    51,    51,    52,
      53,    29,    29,    54,    29,    26,    27,    25,    59,    59,
      25,    54,     8,    59
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    40,    41,    42,    42,    42,    43,    43,    44,    44,
      45,    46,    46,    47,    47,    48,    48,    48,    48,    48,
      48,    48,    49,    49,    49,    50,    50,    50,    51,    51,
      51,    52,    52,    52,    52,    52,    52,    52,    53,    53,
      54,    54,    55,    55,    56,    56,    57,    58,    58,    59,
      59,    59,    59,    59,    59,    59,    60,    60,    61,    62,
      63,    63,    64,    64,    65,    65,    66,    66,    67,    67
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     3,     1,     3,
       3,     2,     0,     1,     4,     1,     1,     1,     1,     3,
       1,     5,     1,     2,     2,     1,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     3,     3,     1,     3,
       1,     3,     1,     0,     1,     3,     4,     1,     2,     1,
       2,     2,     4,     5,     5,     7,     2,     0,     4,     2,
       1,     0,     1,     3,     6,     6,     1,     1,     2,     0
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
  YYUSE (yytype);
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
#line 69 "monga.y" /* yacc.c:1646  */
    { programNode = (yyval.vNode); }
#line 1349 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 73 "monga.y" /* yacc.c:1646  */
    { (yyval.vInt) = TYP_getID( CHAR ); }
#line 1355 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 74 "monga.y" /* yacc.c:1646  */
    { (yyval.vInt) = TYP_getID( INT ); }
#line 1361 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 75 "monga.y" /* yacc.c:1646  */
    { (yyval.vInt) = TYP_getID( FLOAT ); }
#line 1367 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 79 "monga.y" /* yacc.c:1646  */
    { (yyval.vInt) = (yyvsp[0].vInt); }
#line 1373 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 80 "monga.y" /* yacc.c:1646  */
    { (yyval.vInt) = TYP_array((yyvsp[-2].vInt)); }
#line 1379 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 84 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_id((yyvsp[0].vId).name); }
#line 1385 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 85 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_mergeList((yyvsp[-2].vNode), ABS_id((yyvsp[0].vId).name)); }
#line 1391 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 89 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_declVar((yyvsp[-2].vInt), (yyvsp[-1].vNode)); }
#line 1397 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 93 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_mergeList((yyvsp[-1].vNode), (yyvsp[0].vNode)); }
#line 1403 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 94 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = NULL; }
#line 1409 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 98 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_varMono( ABS_id((yyvsp[0].vId).name) ); }
#line 1415 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 99 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_varArray((yyvsp[-3].vNode), (yyvsp[-1].vNode)); }
#line 1421 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 103 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_literalInt((yyvsp[0].vInt)); }
#line 1427 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 104 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_literalFloat((yyvsp[0].vFloat)); }
#line 1433 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 105 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_literalString((yyvsp[0].vString)); }
#line 1439 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 106 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_expVar((yyvsp[0].vNode)); }
#line 1445 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 107 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_expParented((yyvsp[-1].vNode)); }
#line 1451 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 108 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = (yyvsp[0].vNode); }
#line 1457 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 109 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_expNew((yyvsp[-3].vInt), (yyvsp[-1].vNode)); }
#line 1463 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 113 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = (yyvsp[0].vNode); }
#line 1469 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 114 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_expOpr('-', (yyvsp[0].vNode), NULL); }
#line 1475 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 115 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_expOpr('!', (yyvsp[0].vNode), NULL); }
#line 1481 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 119 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = (yyvsp[0].vNode); }
#line 1487 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 120 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_expOpr('*', (yyvsp[-2].vNode), (yyvsp[0].vNode)); }
#line 1493 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 121 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_expOpr('/', (yyvsp[-2].vNode), (yyvsp[0].vNode)); }
#line 1499 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 125 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = (yyvsp[0].vNode); }
#line 1505 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 126 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_expOpr('+', (yyvsp[-2].vNode), (yyvsp[0].vNode)); }
#line 1511 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 127 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_expOpr('-', (yyvsp[-2].vNode), (yyvsp[0].vNode)); }
#line 1517 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 131 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = (yyvsp[0].vNode); }
#line 1523 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 132 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_expOpr(TK_CE, (yyvsp[-2].vNode), (yyvsp[0].vNode)); }
#line 1529 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 133 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_expOpr(TK_NE, (yyvsp[-2].vNode), (yyvsp[0].vNode)); }
#line 1535 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 134 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_expOpr(TK_GE, (yyvsp[-2].vNode), (yyvsp[0].vNode)); }
#line 1541 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 135 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_expOpr(TK_LE, (yyvsp[-2].vNode), (yyvsp[0].vNode)); }
#line 1547 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 136 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_expOpr('>', (yyvsp[-2].vNode), (yyvsp[0].vNode)); }
#line 1553 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 137 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_expOpr('<', (yyvsp[-2].vNode), (yyvsp[0].vNode)); }
#line 1559 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 141 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = (yyvsp[0].vNode); }
#line 1565 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 142 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_expOpr(TK_AND, (yyvsp[-2].vNode), (yyvsp[0].vNode)); }
#line 1571 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 146 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = (yyvsp[0].vNode); }
#line 1577 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 147 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_expOpr(TK_OR, (yyvsp[-2].vNode), (yyvsp[0].vNode)); }
#line 1583 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 151 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = (yyvsp[0].vNode); }
#line 1589 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 152 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = NULL; }
#line 1595 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 156 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = (yyvsp[0].vNode); }
#line 1601 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 157 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_mergeList((yyvsp[-2].vNode), (yyvsp[0].vNode)); }
#line 1607 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 161 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_expCall( ABS_id((yyvsp[-3].vId).name) , (yyvsp[-1].vNode)); }
#line 1613 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 165 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_cmdRet(NULL); }
#line 1619 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 166 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_cmdRet((yyvsp[0].vNode)); }
#line 1625 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 170 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = (yyvsp[0].vNode); }
#line 1631 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 171 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_cmdExp((yyvsp[-1].vNode)); }
#line 1637 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 172 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = (yyvsp[-1].vNode); }
#line 1643 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 173 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_cmdAttr((yyvsp[-3].vNode), (yyvsp[-1].vNode)); }
#line 1649 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 174 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_cmdWhile((yyvsp[-2].vNode), (yyvsp[0].vNode)); }
#line 1655 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 175 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_cmdIf((yyvsp[-2].vNode), (yyvsp[0].vNode), NULL); }
#line 1661 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 176 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_cmdIf((yyvsp[-4].vNode), (yyvsp[-2].vNode), (yyvsp[0].vNode)); }
#line 1667 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 180 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_mergeList((yyvsp[-1].vNode), (yyvsp[0].vNode)); }
#line 1673 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 181 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = NULL; }
#line 1679 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 185 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_block((yyvsp[-2].vNode), (yyvsp[-1].vNode)); }
#line 1685 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 189 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_declVar((yyvsp[-1].vInt), ABS_id((yyvsp[0].vId).name)); }
#line 1691 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 193 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = (yyvsp[0].vNode); }
#line 1697 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 194 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = NULL; }
#line 1703 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 198 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = (yyvsp[0].vNode); }
#line 1709 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 199 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_mergeList((yyvsp[-2].vNode), (yyvsp[0].vNode)); }
#line 1715 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 203 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_declFunc((yyvsp[-5].vInt), ABS_id((yyvsp[-4].vId).name), (yyvsp[-2].vNode), (yyvsp[0].vNode)); }
#line 1721 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 204 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_declFunc( TYP_getID( VOID ) , ABS_id((yyvsp[-4].vId).name), (yyvsp[-2].vNode), (yyvsp[0].vNode)); }
#line 1727 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 208 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = (yyvsp[0].vNode); }
#line 1733 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 209 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = (yyvsp[0].vNode); }
#line 1739 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 213 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = ABS_mergeList((yyvsp[-1].vNode), (yyvsp[0].vNode)); }
#line 1745 "monga.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 214 "monga.y" /* yacc.c:1646  */
    { (yyval.vNode) = NULL; }
#line 1751 "monga.tab.c" /* yacc.c:1646  */
    break;


#line 1755 "monga.tab.c" /* yacc.c:1646  */
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
#line 217 "monga.y" /* yacc.c:1906  */


void yyerror(char *s) {
	fprintf(stderr, "%s\n", s);
}
