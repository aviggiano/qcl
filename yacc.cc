/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "qcl.y"


/**********************************************************************

This file is part of the Quantum Computation Language QCL.

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/


#include <stdlib.h>
#include "syntax.h"
#include "parse.h"

extern int yyerror (const char *s);  /* Called by yyparse on error */
extern objlist *yyObjList;

extern int yylex();

#define YYERROR_VERBOSE 1



/* Line 268 of yacc.c  */
#line 102 "yacc.cc"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     tokTYPE = 400,
     tokTENSOR = 401,
     tokID = 402,
     tokCONS = 403,
     tokBASEFUNCT = 404,
     tokLISTFUNCT = 405,
     tokINCLUDE = 406,
     tokSET = 407,
     tokIDCALL = 408,
     tokCONST = 500,
     tokCOND = 501,
     tokEXTERN = 502,
     tokOP = 503,
     tokPROC = 504,
     tokQUFUN = 505,
     tokFOR = 506,
     tokTO = 507,
     tokWHILE = 508,
     tokUNTIL = 509,
     tokBREAK = 510,
     tokRETURN = 511,
     tokIF = 512,
     tokELSE = 513,
     tokRANGE_LENGTH = 514,
     tokRANGE_END = 515,
     tokSTEP = 516,
     tokINPUT = 517,
     tokPRINT = 518,
     tokEXIT = 519,
     tokMEASURE = 520,
     tokRESET = 521,
     tokDUMP = 601,
     tokINSPECT = 602,
     tokLOAD = 603,
     tokSAVE = 604,
     tokPLOT = 605,
     tokSHELL = 606,
     tokEOF = 900,
     tokERROR = 901,
     tokSWAP = 903,
     tokINVTRANS = 904,
     tokTRANS = 905,
     tokXOR = 906,
     tokOR = 907,
     tokAND = 908,
     tokNOT = 909,
     tokNOTEQ = 910,
     tokGREQ = 911,
     tokLEEQ = 912,
     tokEQ = 913,
     tokMOD = 914,
     tokNEG = 915
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 32 "qcl.y"

  objlist* OBJLIST;
  BaseType TYPE;
  int TENSOR;
  ObjType OBJTYPE;
  tId* ID;
  sObject* OBJ;
  sConst* CONST;
  sExpr* EXPR;
  sExprList* EXPRLIST;
  sStmt* STMT;
  sStmtList* STMTLIST;
  sDef* DEF;
  sDefList* DEFLIST;
  string* STRING;



/* Line 293 of yacc.c  */
#line 211 "yacc.cc"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 223 "yacc.cc"

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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
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
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  112
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1560

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  124
/* YYNRULES -- Number of states.  */
#define YYNSTATES  325

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   915

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    72,     2,    63,     2,     2,    57,     2,
      73,    65,    59,    55,    71,    56,     2,    60,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    64,
      49,    68,    50,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    66,     2,    67,    62,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    69,     2,    70,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     2,     2,
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
       3,     4,     5,     6,     7,     8,     9,    10,    11,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    34,    35,    36,    37,    38,    39,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      40,    41,     2,    42,    43,    44,    45,    46,    47,    48,
      51,    52,    53,    54,    58,    61
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    13,    15,    18,    20,
      22,    24,    26,    28,    30,    32,    34,    37,    40,    47,
      55,    62,    69,    77,    85,    92,    99,   107,   115,   123,
     132,   139,   145,   149,   156,   164,   170,   177,   183,   189,
     193,   196,   199,   201,   204,   206,   208,   210,   213,   216,
     219,   223,   225,   229,   231,   234,   239,   243,   249,   254,
     262,   267,   272,   277,   285,   295,   299,   305,   309,   314,
     317,   321,   325,   331,   334,   338,   341,   345,   349,   355,
     358,   361,   365,   368,   372,   378,   381,   385,   388,   392,
     395,   399,   402,   405,   409,   411,   415,   417,   419,   424,
     431,   438,   442,   445,   448,   451,   455,   459,   463,   467,
     471,   475,   479,   483,   487,   491,   495,   499,   503,   507,
     511,   515,   519,   523,   527
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      75,     0,    -1,    77,    -1,    76,    -1,    75,    77,    -1,
      75,    76,    -1,    40,    -1,    64,    76,    -1,    78,    -1,
      79,    -1,    80,    -1,    81,    -1,    82,    -1,    83,    -1,
      91,    -1,    84,    -1,     9,    64,    -1,    64,    77,    -1,
       3,    11,    89,    65,    85,    86,    -1,     3,     4,    11,
      89,    65,    85,    86,    -1,    15,    11,    89,    65,    85,
      86,    -1,    14,    15,    11,    89,    65,    64,    -1,    13,
      15,    11,    89,    65,    85,    86,    -1,    14,    13,    15,
      11,    89,    65,    64,    -1,    17,    11,    89,    65,    85,
      86,    -1,    14,    17,    11,    89,    65,    64,    -1,    13,
      17,    11,    89,    65,    85,    86,    -1,    14,    13,    17,
      11,    89,    65,    64,    -1,    17,    15,    11,    89,    65,
      85,    86,    -1,    13,    17,    15,    11,    89,    65,    85,
      86,    -1,    16,    11,    89,    65,    85,    86,    -1,    16,
      11,    65,    85,    86,    -1,     3,     5,    64,    -1,     3,
       5,    66,    93,    67,    64,    -1,     3,     4,     5,    66,
      93,    67,    64,    -1,     3,     5,    68,    93,    64,    -1,
       3,     4,     5,    68,    93,    64,    -1,     3,     5,    68,
      13,    64,    -1,    12,     5,    68,    93,    64,    -1,    69,
      90,    70,    -1,    69,    70,    -1,    69,    87,    -1,    69,
      -1,    90,    70,    -1,    70,    -1,    82,    -1,    83,    -1,
      87,    82,    -1,    87,    83,    -1,     3,     5,    -1,     3,
       4,     5,    -1,    88,    -1,    89,    71,    88,    -1,    91,
      -1,    90,    91,    -1,    11,    92,    65,    64,    -1,    11,
      65,    64,    -1,    72,    11,    92,    65,    64,    -1,     5,
      68,    93,    64,    -1,     5,    66,    92,    67,    68,    93,
      64,    -1,    93,    42,    93,    64,    -1,    93,    44,    93,
      64,    -1,    93,    43,    93,    64,    -1,    18,     5,    68,
      93,    19,    93,    84,    -1,    18,     5,    68,    93,    19,
      93,    28,    93,    84,    -1,    24,    93,    84,    -1,    24,
      93,    84,    25,    84,    -1,    20,    93,    84,    -1,    84,
      21,    93,    64,    -1,    22,    64,    -1,    23,    93,    64,
      -1,    29,     5,    64,    -1,    29,    93,    71,     5,    64,
      -1,    30,    64,    -1,    30,    92,    64,    -1,    31,    64,
      -1,    31,    93,    64,    -1,    32,    93,    64,    -1,    32,
      93,    71,     5,    64,    -1,    33,    64,    -1,    34,    64,
      -1,    34,    93,    64,    -1,    38,    64,    -1,    38,    93,
      64,    -1,    38,    93,    71,    93,    64,    -1,    35,    64,
      -1,    35,    92,    64,    -1,    36,    64,    -1,    36,    93,
      64,    -1,    37,    64,    -1,    37,    93,    64,    -1,    39,
      64,    -1,    10,    64,    -1,    10,    93,    64,    -1,    93,
      -1,    92,    71,    93,    -1,     6,    -1,     5,    -1,     5,
      66,    92,    67,    -1,     5,    66,    93,    26,    93,    67,
      -1,     5,    66,    93,    27,    93,    67,    -1,    11,    92,
      65,    -1,    56,    93,    -1,    48,    93,    -1,    63,    93,
      -1,    93,    46,    93,    -1,    93,    45,    93,    -1,    93,
      47,    93,    -1,    93,    54,    93,    -1,    93,    53,    93,
      -1,    93,    52,    93,    -1,    93,    51,    93,    -1,    93,
      49,    93,    -1,    93,    50,    93,    -1,    93,    55,    93,
      -1,    93,    56,    93,    -1,    93,    57,    93,    -1,    93,
      58,    93,    -1,    93,    59,    93,    -1,    93,    60,    93,
      -1,    93,    62,    93,    -1,    73,    93,    65,    -1,     7,
      93,    65,    -1,     8,    92,    65,    -1,     8,    65,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   116,   116,   117,   118,   119,   122,   123,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   138,   140,
     144,   146,   148,   150,   154,   156,   158,   160,   162,   165,
     170,   172,   176,   177,   178,   179,   180,   181,   187,   189,
     190,   193,   194,   197,   198,   201,   202,   203,   204,   207,
     208,   211,   212,   215,   216,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   260,   261,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "tokTYPE", "tokTENSOR", "tokID",
  "tokCONS", "tokBASEFUNCT", "tokLISTFUNCT", "tokINCLUDE", "tokSET",
  "tokIDCALL", "tokCONST", "tokCOND", "tokEXTERN", "tokOP", "tokPROC",
  "tokQUFUN", "tokFOR", "tokTO", "tokWHILE", "tokUNTIL", "tokBREAK",
  "tokRETURN", "tokIF", "tokELSE", "tokRANGE_LENGTH", "tokRANGE_END",
  "tokSTEP", "tokINPUT", "tokPRINT", "tokEXIT", "tokMEASURE", "tokRESET",
  "tokDUMP", "tokINSPECT", "tokLOAD", "tokSAVE", "tokPLOT", "tokSHELL",
  "tokEOF", "tokERROR", "tokSWAP", "tokINVTRANS", "tokTRANS", "tokXOR",
  "tokOR", "tokAND", "tokNOT", "'<'", "'>'", "tokNOTEQ", "tokGREQ",
  "tokLEEQ", "tokEQ", "'+'", "'-'", "'&'", "tokMOD", "'*'", "'/'",
  "tokNEG", "'^'", "'#'", "';'", "')'", "'['", "']'", "'='", "'{'", "'}'",
  "','", "'!'", "'('", "$accept", "objlist", "eof", "obj", "functdef",
  "quopdef", "qufundef", "procdef", "vardef", "constdef", "block",
  "bodydef", "bodystm", "deflist", "arg", "arglist", "stmtlist", "stmt",
  "exprlist", "expr", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   902,   400,   401,   402,   403,   404,   405,   406,
     407,   408,   500,   501,   502,   503,   504,   505,   506,   507,
     508,   509,   510,   511,   512,   513,   514,   515,   516,   517,
     518,   519,   520,   521,   601,   602,   603,   604,   605,   606,
     900,   901,   903,   904,   905,   906,   907,   908,   909,    60,
      62,   910,   911,   912,   913,    43,    45,    38,   914,    42,
      47,   915,    94,    35,    59,    41,    91,    93,    61,   123,
     125,    44,    33,    40
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    74,    75,    75,    75,    75,    76,    76,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    78,    78,
      79,    79,    79,    79,    80,    80,    80,    80,    80,    80,
      81,    81,    82,    82,    82,    82,    82,    82,    83,    84,
      84,    85,    85,    86,    86,    87,    87,    87,    87,    88,
      88,    89,    89,    90,    90,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    92,    92,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     2,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     6,     7,
       6,     6,     7,     7,     6,     6,     7,     7,     7,     8,
       6,     5,     3,     6,     7,     5,     6,     5,     5,     3,
       2,     2,     1,     2,     1,     1,     1,     2,     2,     2,
       3,     1,     3,     1,     2,     4,     3,     5,     4,     7,
       4,     4,     4,     7,     9,     3,     5,     3,     4,     2,
       3,     3,     5,     2,     3,     2,     3,     3,     5,     2,
       2,     3,     2,     3,     5,     2,     3,     2,     3,     2,
       3,     2,     2,     3,     1,     3,     1,     1,     4,     6,
       6,     3,     2,     2,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    97,    96,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     6,     0,     0,     0,     0,     0,     0,     0,     0,
       3,     2,     8,     9,    10,    11,    12,    13,    15,    14,
       0,     0,     0,     0,     0,     0,    97,     0,     0,   124,
       0,    94,    16,    92,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    69,
       0,     0,    97,     0,    73,     0,    75,     0,     0,    79,
      80,     0,    85,     0,    87,     0,    89,     0,    82,     0,
      91,   103,   102,   104,     7,    17,    40,     0,     0,    53,
       0,     0,     1,     5,     4,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    32,     0,     0,
       0,    51,     0,     0,    94,     0,     0,     0,   122,   123,
       0,    93,    56,   101,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    67,    70,
      65,    71,     0,    74,    76,    77,     0,    81,    86,    88,
      90,    83,     0,    39,    54,     0,   121,     0,     0,     0,
       0,   106,   105,   107,   112,   113,   111,   110,   109,   108,
     114,   115,   116,   117,   118,   119,   120,     0,     0,     0,
       0,     0,     0,     0,    49,     0,     0,    98,     0,     0,
      58,     0,   101,    95,    55,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    42,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    68,    60,    62,    61,     0,
       0,     0,     0,    37,    35,    50,     0,    52,     0,     0,
       0,    98,    38,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    45,    46,    41,    44,    31,     0,     0,     0,
       0,     0,    66,    72,    78,    84,    57,     0,    36,     0,
      33,    18,     0,    99,   100,     0,     0,     0,     0,     0,
      21,    25,    20,     0,    47,    48,    43,    30,    24,     0,
       0,    34,    19,    59,    22,    26,     0,    23,    27,    28,
       0,    63,    29,     0,    64
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    39,    40,    41,    42,    43,    44,    45,    46,    47,
     107,   235,   276,   274,   141,   142,   277,   109,    60,    50
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -225
static const yytype_int16 yypact[] =
{
     323,    52,   141,  -225,   778,    36,   -63,   178,   625,    23,
     193,   155,    29,    37,    49,    54,   778,   -27,   778,   778,
     804,   636,   659,   778,     3,   671,   697,   731,   743,   757,
      11,  -225,   778,   778,   778,   323,   383,    72,   778,   252,
    -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,    67,  -225,
    1090,    63,   109,   104,   778,   778,    44,   778,  1108,  -225,
       6,  1470,  -225,  -225,  1150,    82,    15,    70,   146,    61,
     196,   147,   165,   104,     1,   104,   179,   128,   986,  -225,
    1170,   986,   156,   963,  -225,   -10,  -225,  1190,   917,  -225,
    -225,  1210,  -225,    -6,  -225,  1230,  -225,  1250,  -225,   940,
    -225,   843,   159,  -225,  -225,  -225,  -225,    67,   452,  -225,
     778,  1129,  -225,  -225,  -225,   778,   778,   778,   778,   778,
     778,   778,   778,   778,   778,   778,   778,   778,   778,   778,
     778,   778,   778,   778,   778,   157,   104,  -225,   778,   769,
     195,  -225,    20,   -22,   899,  1270,   778,    22,  -225,  -225,
     778,  -225,  -225,   150,   778,   104,   104,   213,   216,   217,
     104,   104,    31,   160,    32,    33,   104,   778,  -225,  -225,
     205,  -225,   226,  -225,  -225,  -225,   228,  -225,  -225,  -225,
    -225,  -225,   778,  -225,  -225,    40,  -225,  1290,  1310,  1330,
    1350,  1484,  1484,   843,  1498,  1498,  1498,  1498,  1498,  1498,
     -47,   -47,   -47,   135,   159,   159,  -225,   778,   778,    41,
    1007,   171,  1370,   231,  -225,   160,   104,   169,   778,   778,
    -225,   107,  -225,  1470,  -225,  1390,    69,    74,   104,   104,
     104,    76,    78,   160,    26,   521,   160,   160,    85,   829,
     174,   180,   181,  1410,   182,  -225,  -225,  -225,  -225,  1026,
    1430,   160,   183,  -225,  -225,  -225,   521,  -225,   778,  1045,
    1064,  -225,  -225,   160,   160,    88,    95,    96,   184,   185,
     521,   199,  -225,  -225,    26,  -225,  -225,   590,   521,   521,
     160,   778,  -225,  -225,  -225,  -225,  -225,   186,  -225,   521,
    -225,  -225,  1450,  -225,  -225,   521,   521,   160,   189,   190,
    -225,  -225,  -225,   233,  -225,  -225,  -225,  -225,  -225,   521,
     862,  -225,  -225,  -225,  -225,  -225,   521,  -225,  -225,  -225,
     778,  -225,  -225,   986,  -225
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -225,  -225,   152,   153,  -225,  -225,  -225,  -225,  -224,  -212,
       0,   -82,   -77,  -225,    55,   -66,   237,    34,    25,    -2
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_int16 yytable[] =
{
      48,    62,    58,    61,   140,    64,    61,   162,   164,   165,
     272,   131,   132,   133,    78,   134,    80,    81,    83,    61,
      87,    88,   273,    91,    61,    95,    97,    99,    67,   271,
     101,   102,   103,    66,    49,    48,   111,    79,     9,    48,
      73,    56,     3,     4,     5,   217,    85,    57,    74,   150,
     304,    93,   144,   145,   173,    61,    51,    52,   178,    77,
      75,   150,   305,    53,    76,   150,   163,    89,   135,    49,
     209,   149,   156,    49,   136,   100,   157,   150,   168,   143,
     153,   170,   147,   110,    32,   215,   150,   222,   115,   226,
     227,   216,    33,   150,   231,   232,   233,   236,   237,    34,
     238,    59,   216,   216,   216,   244,   251,   140,    61,    38,
     146,   150,   216,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   256,   263,   185,   210,   212,   154,   264,
     216,   268,   184,   269,   144,   216,   152,   216,   223,   216,
     280,   270,   225,   297,   278,   279,   216,   155,   160,   216,
     298,   299,   265,   266,   267,   239,   216,   216,    70,   289,
      71,   221,    72,   137,   261,   138,   161,   139,   150,   291,
     243,   295,   296,    56,     3,     4,     5,   104,   105,    57,
     166,   113,   114,   302,   132,   133,   167,   134,   309,   213,
     214,   307,   308,   303,    52,   249,   250,    54,    68,    55,
      69,   158,   312,   159,   224,   316,   259,   260,   314,   315,
     171,   134,   146,   207,   228,   208,    32,   229,   230,   234,
     240,   241,   319,   242,    33,   253,   255,   258,   135,   322,
     282,    34,    63,    36,   283,   284,   286,   290,   300,   301,
     311,    38,   112,   317,   318,     1,   292,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,   257,    16,   108,    17,    18,    19,     0,     0,   310,
       0,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,     0,     0,     0,     0,     0,     0,     0,
      32,     0,     0,     0,     0,     0,     0,     0,    33,     0,
     321,   184,     0,     0,     0,    34,    35,     0,   323,     0,
       0,    36,     0,   324,    37,    38,     1,     0,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,     0,    16,     0,    17,    18,    19,     0,     0,
       0,     0,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,     0,     0,     0,     0,     0,     0,
       0,    32,     0,     0,     0,     0,     0,     0,     0,    33,
       0,     0,     0,     0,     0,     0,    34,    35,     2,     3,
       4,     5,    36,     7,     8,    37,    38,     0,     0,     0,
       0,    15,     0,    16,     0,    17,    18,    19,     0,     0,
       0,     0,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,     0,     0,     0,     0,     0,     0,     0,
       0,    32,     0,     0,     0,     0,     0,     0,     0,    33,
       0,     0,     0,     0,     0,     0,    34,     0,     0,     0,
       0,     0,    36,   106,     0,    37,    38,     2,     3,     4,
       5,     0,     7,     8,     0,     0,     0,     0,     0,     0,
      15,     0,    16,     0,    17,    18,    19,     0,     0,     0,
       0,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,     0,     0,     0,     0,     0,     0,     0,     0,
      32,     0,     0,     0,     0,     0,     0,     0,    33,     0,
       0,     0,     0,     0,     0,    34,     0,     0,     0,     0,
       0,    36,   183,     0,    37,    38,     2,     3,     4,     5,
       0,     7,     8,     0,     0,     0,     0,     0,     0,    15,
       0,    16,     0,    17,    18,    19,     0,     0,     0,     0,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,     0,     0,     0,     0,     0,     0,     0,     0,    32,
       0,     0,     0,     0,     0,     0,     0,    33,     0,     0,
       0,     0,     0,     0,    34,     0,     0,     0,     0,     0,
      36,   275,     0,    37,    38,     2,     3,     4,     5,     0,
       7,     8,     0,     0,     0,     0,     0,     0,    15,     0,
      16,     0,    17,    18,    19,     0,     0,     0,     0,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      56,     3,     4,     5,     0,     0,    57,     0,    32,     0,
       0,    56,     3,     4,     5,     0,    33,    57,     0,     0,
       0,     0,     0,    34,     0,     0,     0,     0,     0,    36,
     306,     0,    37,    38,    56,     3,     4,     5,     0,     0,
      57,     0,     0,    32,     0,     0,    56,     3,     4,     5,
       0,    33,    57,     0,    32,     0,     0,     0,    34,     0,
      65,     0,    33,     0,     0,     0,     0,     0,    38,    34,
      84,     0,    56,     3,     4,     5,     0,    32,    57,    38,
       0,     0,     0,     0,     0,    33,     0,     0,     0,    32,
       0,     0,    34,    86,     0,     0,     0,    33,     0,     0,
       0,     0,    38,     0,    34,    90,    56,     3,     4,     5,
       0,     0,    57,     0,    38,    32,     0,     0,    56,     3,
       4,     5,     0,    33,    57,     0,     0,     0,     0,     0,
      34,    92,    56,     3,     4,     5,     0,     0,    57,     0,
      38,     0,     0,     0,    56,     3,     4,     5,     0,    32,
      57,     0,   211,    56,     3,     4,     5,    33,     0,    57,
       0,    32,     0,     0,    34,    94,     0,     0,     0,    33,
       0,     0,     0,     0,    38,    32,    34,    96,     0,    82,
       3,     4,     5,    33,     0,    57,    38,    32,     0,     0,
      34,    98,     0,     0,     0,    33,    32,     0,     0,     0,
      38,     0,    34,     0,    33,     0,     0,     0,     0,     0,
       0,    34,    38,     0,     0,     0,     0,     0,   281,     0,
       0,    38,    32,     0,     0,     0,     0,     0,     0,     0,
      33,     0,     0,     0,     0,     0,     0,    34,     0,     0,
       0,     0,     0,     0,   119,   120,   121,    38,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     320,   134,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,     0,   134,     0,   119,   120,   121,
       0,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,     0,   134,   218,   219,     0,     0,     0,
       0,    36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   119,   120,   121,     0,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
       0,   134,   119,   120,   121,     0,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,     0,   134,
       0,   175,     0,     0,     0,   119,   120,   121,   176,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,     0,   134,     0,   181,     0,     0,     0,   119,   120,
     121,   182,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,     0,   134,     0,     0,     0,     0,
       0,   119,   120,   121,   172,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,     0,   134,     0,
       0,     0,   119,   120,   121,    36,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,     0,   134,
       0,   119,   120,   121,   252,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,     0,   134,     0,
     119,   120,   121,   287,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,     0,   134,     0,   119,
     120,   121,   293,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,     0,   134,     0,     0,     0,
       0,   294,   116,   117,   118,   119,   120,   121,     0,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,     0,   134,   119,   120,   121,     0,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,     0,
     134,     0,     0,   148,   119,   120,   121,     0,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
       0,   134,     0,     0,   186,   119,   120,   121,     0,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,     0,   134,     0,   151,   119,   120,   121,     0,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,     0,   134,     0,   169,   119,   120,   121,     0,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,     0,   134,     0,   174,   119,   120,   121,     0,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,     0,   134,     0,   177,   119,   120,   121,     0,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,     0,   134,     0,   179,   119,   120,   121,     0,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,     0,   134,     0,   180,   119,   120,   121,     0,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,     0,   134,     0,   220,   119,   120,   121,     0,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,     0,   134,     0,   245,   119,   120,   121,     0,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,     0,   134,     0,   246,   119,   120,   121,     0,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,     0,   134,     0,   247,   119,   120,   121,     0,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,     0,   134,     0,   248,   119,   120,   121,     0,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,     0,   134,     0,   254,   119,   120,   121,     0,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,     0,   134,     0,   262,   119,   120,   121,     0,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,     0,   134,     0,   285,   119,   120,   121,     0,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,     0,   134,     0,   288,   119,   120,   121,     0,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,     0,   134,     0,   313,   119,   120,   121,     0,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   121,   134,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,     0,   134,    -1,    -1,    -1,
      -1,    -1,    -1,   128,   129,   130,   131,   132,   133,     0,
     134
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-225))

#define yytable_value_is_error(yytable_value) \
  ((yytable_value) == (-1))

static const yytype_int16 yycheck[] =
{
       0,    64,     4,     5,     3,     7,     8,    73,    74,    75,
     234,    58,    59,    60,    16,    62,    18,    19,    20,    21,
      22,    23,   234,    25,    26,    27,    28,    29,     5,     3,
      32,    33,    34,     8,     0,    35,    38,    64,    12,    39,
      11,     5,     6,     7,     8,    67,    21,    11,    11,    71,
     274,    26,    54,    55,    64,    57,     4,     5,    64,     5,
      11,    71,   274,    11,    15,    71,    65,    64,     5,    35,
     136,    65,    11,    39,    11,    64,    15,    71,    78,    54,
      65,    81,    57,    11,    48,    65,    71,    65,    21,   155,
     156,    71,    56,    71,   160,   161,    65,    65,    65,    63,
     166,    65,    71,    71,    71,    65,    65,     3,   110,    73,
      66,    71,    71,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   215,    65,   110,   138,   139,    68,    65,
      71,    65,   108,    65,   146,    71,    64,    71,   150,    71,
      65,   233,   154,    65,   236,   237,    71,    11,    11,    71,
      65,    65,   228,   229,   230,   167,    71,    71,    13,   251,
      15,   146,    17,    64,    67,    66,    11,    68,    71,   256,
     182,   263,   264,     5,     6,     7,     8,    35,    35,    11,
      11,    39,    39,   270,    59,    60,    68,    62,   280,     4,
       5,   278,   279,     4,     5,   207,   208,    66,    15,    68,
      17,    15,   289,    17,    64,   297,   218,   219,   295,   296,
      64,    62,    66,    66,    11,    68,    48,    11,    11,    69,
      25,     5,   309,     5,    56,    64,     5,    68,     5,   316,
     240,    63,    64,    69,    64,    64,    64,    64,    64,    64,
      64,    73,     0,    64,    64,     3,   258,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,   216,    20,    36,    22,    23,    24,    -1,    -1,   281,
      -1,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,
     310,   277,    -1,    -1,    -1,    63,    64,    -1,   320,    -1,
      -1,    69,    -1,   323,    72,    73,     3,    -1,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    -1,    20,    -1,    22,    23,    24,    -1,    -1,
      -1,    -1,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    63,    64,     5,     6,
       7,     8,    69,    10,    11,    72,    73,    -1,    -1,    -1,
      -1,    18,    -1,    20,    -1,    22,    23,    24,    -1,    -1,
      -1,    -1,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,    -1,
      -1,    -1,    69,    70,    -1,    72,    73,     5,     6,     7,
       8,    -1,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      18,    -1,    20,    -1,    22,    23,    24,    -1,    -1,    -1,
      -1,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,    -1,    -1,
      -1,    69,    70,    -1,    72,    73,     5,     6,     7,     8,
      -1,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    18,
      -1,    20,    -1,    22,    23,    24,    -1,    -1,    -1,    -1,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    63,    -1,    -1,    -1,    -1,    -1,
      69,    70,    -1,    72,    73,     5,     6,     7,     8,    -1,
      10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    18,    -1,
      20,    -1,    22,    23,    24,    -1,    -1,    -1,    -1,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
       5,     6,     7,     8,    -1,    -1,    11,    -1,    48,    -1,
      -1,     5,     6,     7,     8,    -1,    56,    11,    -1,    -1,
      -1,    -1,    -1,    63,    -1,    -1,    -1,    -1,    -1,    69,
      70,    -1,    72,    73,     5,     6,     7,     8,    -1,    -1,
      11,    -1,    -1,    48,    -1,    -1,     5,     6,     7,     8,
      -1,    56,    11,    -1,    48,    -1,    -1,    -1,    63,    -1,
      65,    -1,    56,    -1,    -1,    -1,    -1,    -1,    73,    63,
      64,    -1,     5,     6,     7,     8,    -1,    48,    11,    73,
      -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    48,
      -1,    -1,    63,    64,    -1,    -1,    -1,    56,    -1,    -1,
      -1,    -1,    73,    -1,    63,    64,     5,     6,     7,     8,
      -1,    -1,    11,    -1,    73,    48,    -1,    -1,     5,     6,
       7,     8,    -1,    56,    11,    -1,    -1,    -1,    -1,    -1,
      63,    64,     5,     6,     7,     8,    -1,    -1,    11,    -1,
      73,    -1,    -1,    -1,     5,     6,     7,     8,    -1,    48,
      11,    -1,    13,     5,     6,     7,     8,    56,    -1,    11,
      -1,    48,    -1,    -1,    63,    64,    -1,    -1,    -1,    56,
      -1,    -1,    -1,    -1,    73,    48,    63,    64,    -1,     5,
       6,     7,     8,    56,    -1,    11,    73,    48,    -1,    -1,
      63,    64,    -1,    -1,    -1,    56,    48,    -1,    -1,    -1,
      73,    -1,    63,    -1,    56,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    73,    -1,    -1,    -1,    -1,    -1,    19,    -1,
      -1,    73,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    46,    47,    73,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      28,    62,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,    -1,    45,    46,    47,
      -1,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    -1,    62,    26,    27,    -1,    -1,    -1,
      -1,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    46,    47,    -1,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,    45,    46,    47,    -1,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    -1,    62,
      -1,    64,    -1,    -1,    -1,    45,    46,    47,    71,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,    -1,    64,    -1,    -1,    -1,    45,    46,
      47,    71,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,    -1,    -1,    -1,    -1,
      -1,    45,    46,    47,    71,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    -1,    62,    -1,
      -1,    -1,    45,    46,    47,    69,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    -1,    62,
      -1,    45,    46,    47,    67,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    -1,    62,    -1,
      45,    46,    47,    67,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,    -1,    45,
      46,    47,    67,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    -1,    62,    -1,    -1,    -1,
      -1,    67,    42,    43,    44,    45,    46,    47,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,    45,    46,    47,    -1,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    -1,
      62,    -1,    -1,    65,    45,    46,    47,    -1,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,    -1,    -1,    65,    45,    46,    47,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,    -1,    64,    45,    46,    47,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,    -1,    64,    45,    46,    47,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,    -1,    64,    45,    46,    47,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,    -1,    64,    45,    46,    47,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,    -1,    64,    45,    46,    47,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,    -1,    64,    45,    46,    47,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,    -1,    64,    45,    46,    47,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,    -1,    64,    45,    46,    47,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,    -1,    64,    45,    46,    47,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,    -1,    64,    45,    46,    47,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,    -1,    64,    45,    46,    47,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,    -1,    64,    45,    46,    47,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,    -1,    64,    45,    46,    47,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,    -1,    64,    45,    46,    47,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,    -1,    64,    45,    46,    47,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,    -1,    64,    45,    46,    47,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    47,    62,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    -1,    62,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    -1,
      62
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    20,    22,    23,    24,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    48,    56,    63,    64,    69,    72,    73,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    91,
      93,     4,     5,    11,    66,    68,     5,    11,    93,    65,
      92,    93,    64,    64,    93,    65,    92,     5,    15,    17,
      13,    15,    17,    11,    11,    11,    15,     5,    93,    64,
      93,    93,     5,    93,    64,    92,    64,    93,    93,    64,
      64,    93,    64,    92,    64,    93,    64,    93,    64,    93,
      64,    93,    93,    93,    76,    77,    70,    84,    90,    91,
      11,    93,     0,    76,    77,    21,    42,    43,    44,    45,
      46,    47,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    62,     5,    11,    64,    66,    68,
       3,    88,    89,    92,    93,    93,    66,    92,    65,    65,
      71,    64,    64,    65,    68,    11,    11,    15,    15,    17,
      11,    11,    89,    65,    89,    89,    11,    68,    84,    64,
      84,    64,    71,    64,    64,    64,    71,    64,    64,    64,
      64,    64,    71,    70,    91,    92,    65,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    66,    68,    89,
      93,    13,    93,     4,     5,    65,    71,    67,    26,    27,
      64,    92,    65,    93,    64,    93,    89,    89,    11,    11,
      11,    89,    89,    65,    69,    85,    65,    65,    89,    93,
      25,     5,     5,    93,    65,    64,    64,    64,    64,    93,
      93,    65,    67,    64,    64,     5,    85,    88,    68,    93,
      93,    67,    64,    65,    65,    89,    89,    89,    65,    65,
      85,     3,    82,    83,    87,    70,    86,    90,    85,    85,
      65,    19,    84,    64,    64,    64,    64,    67,    64,    85,
      64,    86,    93,    67,    67,    85,    85,    65,    65,    65,
      64,    64,    86,     4,    82,    83,    70,    86,    86,    85,
      93,    64,    86,    64,    86,    86,    85,    64,    64,    86,
      28,    84,    86,    93,    84
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
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


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
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
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
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

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

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

/* Line 1806 of yacc.c  */
#line 116 "qcl.y"
    { (yyval.OBJLIST) = YYNEW(objlist); YYTRY((yyval.OBJLIST)->push_back((yyvsp[(1) - (1)].OBJ))); }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 117 "qcl.y"
    { yyObjList = (yyval.OBJLIST) = YYNEW(objlist); YYACCEPT; }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 118 "qcl.y"
    { YYTRY((yyvsp[(1) - (2)].OBJLIST)->push_back((yyvsp[(2) - (2)].OBJ))); (yyval.OBJLIST)=(yyvsp[(1) - (2)].OBJLIST); }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 119 "qcl.y"
    { yyObjList = (yyval.OBJLIST) = (yyvsp[(1) - (2)].OBJLIST); YYACCEPT; }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 122 "qcl.y"
    { (yyval.OBJ) = 0; }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 123 "qcl.y"
    { (yyval.OBJ) = 0; }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 126 "qcl.y"
    { (yyval.OBJ) = (yyvsp[(1) - (1)].DEF); }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 127 "qcl.y"
    { (yyval.OBJ) = (yyvsp[(1) - (1)].DEF); }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 128 "qcl.y"
    { (yyval.OBJ) = (yyvsp[(1) - (1)].DEF); }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 129 "qcl.y"
    { (yyval.OBJ) = (yyvsp[(1) - (1)].DEF); }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 130 "qcl.y"
    { (yyval.OBJ) = (yyvsp[(1) - (1)].DEF); }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 131 "qcl.y"
    { (yyval.OBJ) = (yyvsp[(1) - (1)].DEF); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 132 "qcl.y"
    { (yyval.OBJ) = (yyvsp[(1) - (1)].STMT); }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 133 "qcl.y"
    { (yyval.OBJ) = (yyvsp[(1) - (1)].STMTLIST); }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 134 "qcl.y"
    { (yyval.OBJ) = YYNEW(sInclude(*(yyvsp[(1) - (2)].STRING))); }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 135 "qcl.y"
    { (yyval.OBJ) = (yyvsp[(2) - (2)].OBJ); }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 138 "qcl.y"
    { 
	  (yyval.DEF) = YYNEW(sFunctDef(tType((yyvsp[(1) - (6)].TYPE)),(yyvsp[(2) - (6)].ID),(yyvsp[(3) - (6)].DEFLIST),(yyvsp[(5) - (6)].DEFLIST),(yyvsp[(6) - (6)].STMTLIST))); }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 140 "qcl.y"
    { 
	  (yyval.DEF) = YYNEW(sFunctDef(tType((yyvsp[(1) - (7)].TYPE),(yyvsp[(2) - (7)].TENSOR)),(yyvsp[(3) - (7)].ID),(yyvsp[(4) - (7)].DEFLIST),(yyvsp[(6) - (7)].DEFLIST),(yyvsp[(7) - (7)].STMTLIST))); }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 144 "qcl.y"
    { 
	  (yyval.DEF) = YYNEW(sQuOpDef((yyvsp[(2) - (6)].ID),(yyvsp[(3) - (6)].DEFLIST),(yyvsp[(5) - (6)].DEFLIST),(yyvsp[(6) - (6)].STMTLIST))); }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 146 "qcl.y"
    {
	  (yyval.DEF) = YYNEW(sQuOpDef((yyvsp[(3) - (6)].ID),(yyvsp[(4) - (6)].DEFLIST),0,0,0,1)); }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 148 "qcl.y"
    { 
	  (yyval.DEF) = YYNEW(sQuOpDef((yyvsp[(3) - (7)].ID),(yyvsp[(4) - (7)].DEFLIST),(yyvsp[(6) - (7)].DEFLIST),(yyvsp[(7) - (7)].STMTLIST),1)); }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 150 "qcl.y"
    {
	  (yyval.DEF) = YYNEW(sQuOpDef((yyvsp[(4) - (7)].ID),(yyvsp[(5) - (7)].DEFLIST),0,0,1,1)); }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 154 "qcl.y"
    { 
	  (yyval.DEF) = YYNEW(sQuFunDef((yyvsp[(2) - (6)].ID),(yyvsp[(3) - (6)].DEFLIST),(yyvsp[(5) - (6)].DEFLIST),(yyvsp[(6) - (6)].STMTLIST))); }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 156 "qcl.y"
    {
	  (yyval.DEF) = YYNEW(sQuFunDef((yyvsp[(3) - (6)].ID),(yyvsp[(4) - (6)].DEFLIST),0,0,0,1)); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 158 "qcl.y"
    { 
	  (yyval.DEF) = YYNEW(sQuFunDef((yyvsp[(3) - (7)].ID),(yyvsp[(4) - (7)].DEFLIST),(yyvsp[(6) - (7)].DEFLIST),(yyvsp[(7) - (7)].STMTLIST),1)); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 160 "qcl.y"
    {
	  (yyval.DEF) = YYNEW(sQuFunDef((yyvsp[(4) - (7)].ID),(yyvsp[(5) - (7)].DEFLIST),0,0,1,1)); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 162 "qcl.y"
    { 
	  (yyval.DEF) = YYNEW(sQuFunDef((yyvsp[(3) - (7)].ID),(yyvsp[(4) - (7)].DEFLIST),(yyvsp[(6) - (7)].DEFLIST),(yyvsp[(7) - (7)].STMTLIST))); 
          YYTRY((yyval.DEF)->setFlag(flagFUNOP)); }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 165 "qcl.y"
    {
	  (yyval.DEF) = YYNEW(sQuFunDef((yyvsp[(4) - (8)].ID),(yyvsp[(5) - (8)].DEFLIST),(yyvsp[(7) - (8)].DEFLIST),(yyvsp[(8) - (8)].STMTLIST),1)); 
          YYTRY((yyval.DEF)->setFlag(flagFUNOP)); }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 170 "qcl.y"
    { 
	  (yyval.DEF) = YYNEW(sProcDef((yyvsp[(2) - (6)].ID),(yyvsp[(3) - (6)].DEFLIST),(yyvsp[(5) - (6)].DEFLIST),(yyvsp[(6) - (6)].STMTLIST))); }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 172 "qcl.y"
    {
	  (yyval.DEF) = YYNEW(sProcDef((yyvsp[(2) - (5)].ID),new sDefList(),(yyvsp[(4) - (5)].DEFLIST),(yyvsp[(5) - (5)].STMTLIST))); }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 176 "qcl.y"
    { (yyval.DEF) = YYNEW(sVarDef(tType((yyvsp[(1) - (3)].TYPE)),(yyvsp[(2) - (3)].ID))); }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 177 "qcl.y"
    { (yyval.DEF) = YYNEW(sVarDef(tType((yyvsp[(1) - (6)].TYPE)),(yyvsp[(2) - (6)].ID),(yyvsp[(4) - (6)].EXPR),0)); }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 178 "qcl.y"
    { (yyval.DEF) = YYNEW(sVarDef(tType((yyvsp[(1) - (7)].TYPE),(yyvsp[(2) - (7)].TENSOR)),(yyvsp[(3) - (7)].ID),(yyvsp[(5) - (7)].EXPR),0)); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 179 "qcl.y"
    { (yyval.DEF) = YYNEW(sVarDef(tType((yyvsp[(1) - (5)].TYPE)),(yyvsp[(2) - (5)].ID),0,(yyvsp[(4) - (5)].EXPR))); }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 180 "qcl.y"
    { (yyval.DEF) = YYNEW(sVarDef(tType((yyvsp[(1) - (6)].TYPE),(yyvsp[(2) - (6)].TENSOR)),(yyvsp[(3) - (6)].ID),0,(yyvsp[(5) - (6)].EXPR))); }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 181 "qcl.y"
    {
          	(yyval.DEF) = YYNEW(sVarDef(tType((yyvsp[(1) - (5)].TYPE)),(yyvsp[(2) - (5)].ID),0,new sVar(new tId(CONDID))));
          	YYTRY((yyval.DEF)->setFlag(flagCONDDEF)); 
          }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 187 "qcl.y"
    { (yyval.DEF) = YYNEW(sConstDef((yyvsp[(2) - (5)].ID),(yyvsp[(4) - (5)].EXPR))); }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 189 "qcl.y"
    { (yyval.STMTLIST) = (yyvsp[(2) - (3)].STMTLIST); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 190 "qcl.y"
    { (yyval.STMTLIST) = YYNEW(sStmtList()); }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 193 "qcl.y"
    { (yyval.DEFLIST) = (yyvsp[(2) - (2)].DEFLIST); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 194 "qcl.y"
    { (yyval.DEFLIST) = YYNEW(sDefList()); }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 197 "qcl.y"
    { (yyval.STMTLIST) = (yyvsp[(1) - (2)].STMTLIST); }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 198 "qcl.y"
    { (yyval.STMTLIST) = YYNEW(sStmtList()); }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 201 "qcl.y"
    { (yyval.DEFLIST) = YYNEW(sDefList()); YYTRY((yyval.DEFLIST)->append((yyvsp[(1) - (1)].DEF))); }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 202 "qcl.y"
    { (yyval.DEFLIST) = YYNEW(sDefList()); YYTRY((yyval.DEFLIST)->append((yyvsp[(1) - (1)].DEF))); }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 203 "qcl.y"
    { YYTRY((yyvsp[(1) - (2)].DEFLIST)->append((yyvsp[(2) - (2)].DEF))); (yyval.DEFLIST)=(yyvsp[(1) - (2)].DEFLIST); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 204 "qcl.y"
    { YYTRY((yyvsp[(1) - (2)].DEFLIST)->append((yyvsp[(2) - (2)].DEF))); (yyval.DEFLIST)=(yyvsp[(1) - (2)].DEFLIST); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 207 "qcl.y"
    { (yyval.DEF) = YYNEW(sArgDef(tType((yyvsp[(1) - (2)].TYPE)),(yyvsp[(2) - (2)].ID))); }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 208 "qcl.y"
    { (yyval.DEF) = YYNEW(sArgDef(tType((yyvsp[(1) - (3)].TYPE),(yyvsp[(2) - (3)].TENSOR)),(yyvsp[(3) - (3)].ID))); }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 211 "qcl.y"
    { (yyval.DEFLIST) = YYNEW(sDefList()); YYTRY((yyval.DEFLIST)->append((yyvsp[(1) - (1)].DEF))); }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 212 "qcl.y"
    { YYTRY((yyvsp[(1) - (3)].DEFLIST)->append((yyvsp[(3) - (3)].DEF))); (yyval.DEFLIST)=(yyvsp[(1) - (3)].DEFLIST); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 215 "qcl.y"
    { (yyval.STMTLIST) = YYNEW(sStmtList()); YYTRY((yyval.STMTLIST)->append((yyvsp[(1) - (1)].STMT))); }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 216 "qcl.y"
    { YYTRY((yyvsp[(1) - (2)].STMTLIST)->append((yyvsp[(2) - (2)].STMT))); (yyval.STMTLIST)=(yyvsp[(1) - (2)].STMTLIST); }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 219 "qcl.y"
    { (yyval.STMT) = YYNEW(sCall((yyvsp[(1) - (4)].ID),(yyvsp[(2) - (4)].EXPRLIST))); }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 220 "qcl.y"
    { (yyval.STMT) = YYNEW(sCall((yyvsp[(1) - (3)].ID),new sExprList())); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 221 "qcl.y"
    { (yyval.STMT) = YYNEW(sCall((yyvsp[(2) - (5)].ID),(yyvsp[(3) - (5)].EXPRLIST),1)); }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 222 "qcl.y"
    { (yyval.STMT) = YYNEW(sAssign(new sVar((yyvsp[(1) - (4)].ID)),(yyvsp[(3) - (4)].EXPR))); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 223 "qcl.y"
    { (yyval.STMT) = YYNEW(sAssign(new sVar((yyvsp[(1) - (7)].ID)),(yyvsp[(6) - (7)].EXPR),(yyvsp[(3) - (7)].EXPRLIST))); }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 224 "qcl.y"
    { (yyval.STMT) = YYNEW(sCall(new tId(SWAPID),new sExprList((yyvsp[(1) - (4)].EXPR),(yyvsp[(3) - (4)].EXPR)))); }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 225 "qcl.y"
    { (yyval.STMT) = YYNEW(sCall(new tId(FANOUTID),new sExprList((yyvsp[(1) - (4)].EXPR),(yyvsp[(3) - (4)].EXPR)))); }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 226 "qcl.y"
    { (yyval.STMT) = YYNEW(sCall(new tId(FANOUTID),new sExprList((yyvsp[(1) - (4)].EXPR),(yyvsp[(3) - (4)].EXPR)),1)); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 227 "qcl.y"
    { (yyval.STMT) = YYNEW(sFor(new sVar((yyvsp[(2) - (7)].ID)),(yyvsp[(4) - (7)].EXPR),(yyvsp[(6) - (7)].EXPR),(yyvsp[(7) - (7)].STMTLIST))); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 228 "qcl.y"
    { (yyval.STMT) = YYNEW(sFor(new sVar((yyvsp[(2) - (9)].ID)),(yyvsp[(4) - (9)].EXPR),(yyvsp[(6) - (9)].EXPR),(yyvsp[(9) - (9)].STMTLIST),(yyvsp[(8) - (9)].EXPR))); }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 229 "qcl.y"
    { (yyval.STMT) = YYNEW(sIf((yyvsp[(2) - (3)].EXPR),(yyvsp[(3) - (3)].STMTLIST))); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 230 "qcl.y"
    { (yyval.STMT) = YYNEW(sIf((yyvsp[(2) - (5)].EXPR),(yyvsp[(3) - (5)].STMTLIST),(yyvsp[(5) - (5)].STMTLIST))); }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 231 "qcl.y"
    { (yyval.STMT) = YYNEW(sWhile((yyvsp[(2) - (3)].EXPR),(yyvsp[(3) - (3)].STMTLIST))); }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 232 "qcl.y"
    { (yyval.STMT) = YYNEW(sUntil((yyvsp[(3) - (4)].EXPR),(yyvsp[(1) - (4)].STMTLIST))); }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 233 "qcl.y"
    { (yyval.STMT) = YYNEW(sBreak()); }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 234 "qcl.y"
    { (yyval.STMT) = YYNEW(sReturn((yyvsp[(2) - (3)].EXPR))); }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 235 "qcl.y"
    { (yyval.STMT) = YYNEW(sInput(new sVar((yyvsp[(2) - (3)].ID)),0)); }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 236 "qcl.y"
    { (yyval.STMT) = YYNEW(sInput(new sVar((yyvsp[(4) - (5)].ID)),(yyvsp[(2) - (5)].EXPR))); }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 237 "qcl.y"
    { (yyval.STMT) = YYNEW(sPrint(new sExprList())); }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 238 "qcl.y"
    { (yyval.STMT) = YYNEW(sPrint((yyvsp[(2) - (3)].EXPRLIST))); }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 239 "qcl.y"
    { (yyval.STMT) = YYNEW(sExit(0)); }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 240 "qcl.y"
    { (yyval.STMT) = YYNEW(sExit((yyvsp[(2) - (3)].EXPR))); }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 241 "qcl.y"
    { (yyval.STMT) = YYNEW(sMeasure((yyvsp[(2) - (3)].EXPR),0)); }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 242 "qcl.y"
    { (yyval.STMT) = YYNEW(sMeasure((yyvsp[(2) - (5)].EXPR),new sVar((yyvsp[(4) - (5)].ID)))); }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 243 "qcl.y"
    { (yyval.STMT) = YYNEW(sReset()); }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 244 "qcl.y"
    { (yyval.STMT) = YYNEW(sDump(0)); }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 245 "qcl.y"
    { (yyval.STMT) = YYNEW(sDump((yyvsp[(2) - (3)].EXPR))); }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 246 "qcl.y"
    { (yyval.STMT) = YYNEW(sPlot()); }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 247 "qcl.y"
    { (yyval.STMT) = YYNEW(sPlot((yyvsp[(2) - (3)].EXPR))); }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 248 "qcl.y"
    { (yyval.STMT) = YYNEW(sPlot((yyvsp[(2) - (5)].EXPR),(yyvsp[(4) - (5)].EXPR))); }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 249 "qcl.y"
    { (yyval.STMT) = YYNEW(sInspect(0)); }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 250 "qcl.y"
    { (yyval.STMT) = YYNEW(sInspect((yyvsp[(2) - (3)].EXPRLIST))); }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 251 "qcl.y"
    { (yyval.STMT) = YYNEW(sLoad(0)); }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 252 "qcl.y"
    { (yyval.STMT) = YYNEW(sLoad((yyvsp[(2) - (3)].EXPR))); }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 253 "qcl.y"
    { (yyval.STMT) = YYNEW(sSave(0)); }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 254 "qcl.y"
    { (yyval.STMT) = YYNEW(sSave((yyvsp[(2) - (3)].EXPR))); }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 255 "qcl.y"
    { (yyval.STMT) = YYNEW(sShell()); }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 256 "qcl.y"
    { (yyval.STMT) = YYNEW(sSet(*(yyvsp[(1) - (2)].STRING),0)); }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 257 "qcl.y"
    { (yyval.STMT) = YYNEW(sSet(*(yyvsp[(1) - (3)].STRING),(yyvsp[(2) - (3)].EXPR))); }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 260 "qcl.y"
    { (yyval.EXPRLIST) = YYNEW(sExprList()); YYTRY((yyval.EXPRLIST)->append((yyvsp[(1) - (1)].EXPR))); }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 261 "qcl.y"
    { YYTRY((yyvsp[(1) - (3)].EXPRLIST)->append((yyvsp[(3) - (3)].EXPR))); (yyval.EXPRLIST)=(yyvsp[(1) - (3)].EXPRLIST); }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 264 "qcl.y"
    { (yyval.EXPR) = (yyvsp[(1) - (1)].CONST); }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 265 "qcl.y"
    { (yyval.EXPR) = YYNEW(sVar((yyvsp[(1) - (1)].ID))); }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 266 "qcl.y"
    { (yyval.EXPR) = YYNEW(sSubscript(new sVar((yyvsp[(1) - (4)].ID)),(yyvsp[(3) - (4)].EXPRLIST))); }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 267 "qcl.y"
    { (yyval.EXPR) = YYNEW(sSubRange(new sVar((yyvsp[(1) - (6)].ID)),(yyvsp[(3) - (6)].EXPR),(yyvsp[(5) - (6)].EXPR),SUBRANGE_LENGTH)); }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 268 "qcl.y"
    { (yyval.EXPR) = YYNEW(sSubRange(new sVar((yyvsp[(1) - (6)].ID)),(yyvsp[(3) - (6)].EXPR),(yyvsp[(5) - (6)].EXPR),SUBRANGE_END)); }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 269 "qcl.y"
    { (yyval.EXPR) = YYNEW(sFunctCall((yyvsp[(1) - (3)].ID),(yyvsp[(2) - (3)].EXPRLIST))); }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 270 "qcl.y"
    { (yyval.EXPR) = YYNEW(sNeg((yyvsp[(2) - (2)].EXPR))); }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 271 "qcl.y"
    { (yyval.EXPR) = YYNEW(sNot((yyvsp[(2) - (2)].EXPR))); }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 272 "qcl.y"
    { (yyval.EXPR) = YYNEW(sLength((yyvsp[(2) - (2)].EXPR))); }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 273 "qcl.y"
    { (yyval.EXPR) = YYNEW(sOr((yyvsp[(1) - (3)].EXPR),(yyvsp[(3) - (3)].EXPR))); }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 274 "qcl.y"
    { (yyval.EXPR) = YYNEW(sXor((yyvsp[(1) - (3)].EXPR),(yyvsp[(3) - (3)].EXPR))); }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 275 "qcl.y"
    { (yyval.EXPR) = YYNEW(sAnd((yyvsp[(1) - (3)].EXPR),(yyvsp[(3) - (3)].EXPR))); }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 276 "qcl.y"
    { (yyval.EXPR) = YYNEW(sEqual((yyvsp[(1) - (3)].EXPR),(yyvsp[(3) - (3)].EXPR))); }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 277 "qcl.y"
    { (yyval.EXPR) = YYNEW(sLeEq((yyvsp[(1) - (3)].EXPR),(yyvsp[(3) - (3)].EXPR))); }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 278 "qcl.y"
    { (yyval.EXPR) = YYNEW(sLeEq((yyvsp[(3) - (3)].EXPR),(yyvsp[(1) - (3)].EXPR))); }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 279 "qcl.y"
    { (yyval.EXPR) = YYNEW(sNotEq((yyvsp[(1) - (3)].EXPR),(yyvsp[(3) - (3)].EXPR))); }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 280 "qcl.y"
    { (yyval.EXPR) = YYNEW(sLess((yyvsp[(1) - (3)].EXPR),(yyvsp[(3) - (3)].EXPR))); }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 281 "qcl.y"
    { (yyval.EXPR) = YYNEW(sLess((yyvsp[(3) - (3)].EXPR),(yyvsp[(1) - (3)].EXPR))); }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 282 "qcl.y"
    { (yyval.EXPR) = YYNEW(sAdd((yyvsp[(1) - (3)].EXPR),(yyvsp[(3) - (3)].EXPR))); }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 283 "qcl.y"
    { (yyval.EXPR) = YYNEW(sSub((yyvsp[(1) - (3)].EXPR),(yyvsp[(3) - (3)].EXPR))); }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 284 "qcl.y"
    { (yyval.EXPR) = YYNEW(sConcat((yyvsp[(1) - (3)].EXPR),(yyvsp[(3) - (3)].EXPR))); }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 285 "qcl.y"
    { (yyval.EXPR) = YYNEW(sMod((yyvsp[(1) - (3)].EXPR),(yyvsp[(3) - (3)].EXPR))); }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 286 "qcl.y"
    { (yyval.EXPR) = YYNEW(sMult((yyvsp[(1) - (3)].EXPR),(yyvsp[(3) - (3)].EXPR))); }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 287 "qcl.y"
    { (yyval.EXPR) = YYNEW(sDiv((yyvsp[(1) - (3)].EXPR),(yyvsp[(3) - (3)].EXPR))); }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 288 "qcl.y"
    { (yyval.EXPR) = YYNEW(sPow((yyvsp[(1) - (3)].EXPR),(yyvsp[(3) - (3)].EXPR))); }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 289 "qcl.y"
    { (yyval.EXPR) = (yyvsp[(2) - (3)].EXPR); }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 290 "qcl.y"
    { (yyval.EXPR) = YYNEW(sBaseFunct((yyvsp[(1) - (3)].OBJTYPE),(yyvsp[(2) - (3)].EXPR))); }
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 291 "qcl.y"
    { (yyval.EXPR) = YYNEW(sListFunct((yyvsp[(1) - (3)].OBJTYPE),(yyvsp[(2) - (3)].EXPRLIST))); }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 292 "qcl.y"
    { (yyval.EXPR) = YYNEW(sListFunct((yyvsp[(1) - (2)].OBJTYPE),new sExprList())); }
    break;



/* Line 1806 of yacc.c  */
#line 2908 "yacc.cc"
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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



