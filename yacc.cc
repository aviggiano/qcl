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
#line 1 "qcl.y" /* yacc.c:339  */


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


#line 96 "yacc.cc" /* yacc.c:339  */

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
   by #include "yacc.hh".  */
#ifndef YY_YY_YACC_HH_INCLUDED
# define YY_YY_YACC_HH_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
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
    tokTRANS = 903,
    tokINVTRANS = 904,
    tokSWAP = 905,
    tokOR = 906,
    tokXOR = 907,
    tokAND = 908,
    tokNOT = 909,
    tokEQ = 910,
    tokLEEQ = 911,
    tokGREQ = 912,
    tokNOTEQ = 913,
    tokMOD = 914,
    tokNEG = 915
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 32 "qcl.y" /* yacc.c:355  */

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

#line 208 "yacc.cc" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_YACC_HH_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 225 "yacc.cc" /* yacc.c:358  */

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
#define YYFINAL  112
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1560

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  124
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  325

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   915

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    72,     2,    63,     2,     2,    57,     2,
      73,    65,    59,    55,    71,    56,     2,    60,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    64,
      53,    68,    54,     2,     2,     2,     2,     2,     2,     2,
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
      49,    50,    51,    52,    58,    61
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
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

#if YYDEBUG || YYERROR_VERBOSE || 0
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
  "tokEOF", "tokERROR", "tokTRANS", "tokINVTRANS", "tokSWAP", "tokOR",
  "tokXOR", "tokAND", "tokNOT", "tokEQ", "tokLEEQ", "tokGREQ", "tokNOTEQ",
  "'<'", "'>'", "'+'", "'-'", "'&'", "tokMOD", "'*'", "'/'", "tokNEG",
  "'^'", "'#'", "';'", "')'", "'['", "']'", "'='", "'{'", "'}'", "','",
  "'!'", "'('", "$accept", "objlist", "eof", "obj", "functdef", "quopdef",
  "qufundef", "procdef", "vardef", "constdef", "block", "bodydef",
  "bodystm", "deflist", "arg", "arglist", "stmtlist", "stmt", "exprlist",
  "expr", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   902,   400,   401,   402,   403,   404,   405,   406,
     407,   408,   500,   501,   502,   503,   504,   505,   506,   507,
     508,   509,   510,   511,   512,   513,   514,   515,   516,   517,
     518,   519,   520,   521,   601,   602,   603,   604,   605,   606,
     900,   901,   903,   904,   905,   906,   907,   908,   909,   910,
     911,   912,   913,    60,    62,    43,    45,    38,   914,    42,
      47,   915,    94,    35,    59,    41,    91,    93,    61,   123,
     125,    44,    33,    40
};
# endif

#define YYPACT_NINF -225

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-225)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-1)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
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

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
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
       0,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,     0,     0,     0,
       0,     0,     0,     0,    49,     0,     0,    98,     0,     0,
      58,     0,   101,    95,    55,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    42,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    68,    61,    62,    60,     0,
       0,     0,     0,    37,    35,    50,     0,    52,     0,     0,
       0,    98,    38,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    45,    46,    41,    44,    31,     0,     0,     0,
       0,     0,    66,    72,    78,    84,    57,     0,    36,     0,
      33,    18,     0,    99,   100,     0,     0,     0,     0,     0,
      21,    25,    20,     0,    47,    48,    43,    30,    24,     0,
       0,    34,    19,    59,    22,    26,     0,    23,    27,    28,
       0,    63,    29,     0,    64
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -225,  -225,   152,   153,  -225,  -225,  -225,  -225,  -224,  -212,
       0,   -82,   -77,  -225,    55,   -66,   237,    34,    25,    -2
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    39,    40,    41,    42,    43,    44,    45,    46,    47,
     107,   235,   276,   274,   141,   142,   277,   109,    60,    50
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
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

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
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
#line 116 "qcl.y" /* yacc.c:1646  */
    { (yyval.OBJLIST) = YYNEW(objlist); YYTRY((yyval.OBJLIST)->push_back((yyvsp[0].OBJ))); }
#line 1822 "yacc.cc" /* yacc.c:1646  */
    break;

  case 3:
#line 117 "qcl.y" /* yacc.c:1646  */
    { yyObjList = (yyval.OBJLIST) = YYNEW(objlist); YYACCEPT; }
#line 1828 "yacc.cc" /* yacc.c:1646  */
    break;

  case 4:
#line 118 "qcl.y" /* yacc.c:1646  */
    { YYTRY((yyvsp[-1].OBJLIST)->push_back((yyvsp[0].OBJ))); (yyval.OBJLIST)=(yyvsp[-1].OBJLIST); }
#line 1834 "yacc.cc" /* yacc.c:1646  */
    break;

  case 5:
#line 119 "qcl.y" /* yacc.c:1646  */
    { yyObjList = (yyval.OBJLIST) = (yyvsp[-1].OBJLIST); YYACCEPT; }
#line 1840 "yacc.cc" /* yacc.c:1646  */
    break;

  case 6:
#line 122 "qcl.y" /* yacc.c:1646  */
    { (yyval.OBJ) = 0; }
#line 1846 "yacc.cc" /* yacc.c:1646  */
    break;

  case 7:
#line 123 "qcl.y" /* yacc.c:1646  */
    { (yyval.OBJ) = 0; }
#line 1852 "yacc.cc" /* yacc.c:1646  */
    break;

  case 8:
#line 126 "qcl.y" /* yacc.c:1646  */
    { (yyval.OBJ) = (yyvsp[0].DEF); }
#line 1858 "yacc.cc" /* yacc.c:1646  */
    break;

  case 9:
#line 127 "qcl.y" /* yacc.c:1646  */
    { (yyval.OBJ) = (yyvsp[0].DEF); }
#line 1864 "yacc.cc" /* yacc.c:1646  */
    break;

  case 10:
#line 128 "qcl.y" /* yacc.c:1646  */
    { (yyval.OBJ) = (yyvsp[0].DEF); }
#line 1870 "yacc.cc" /* yacc.c:1646  */
    break;

  case 11:
#line 129 "qcl.y" /* yacc.c:1646  */
    { (yyval.OBJ) = (yyvsp[0].DEF); }
#line 1876 "yacc.cc" /* yacc.c:1646  */
    break;

  case 12:
#line 130 "qcl.y" /* yacc.c:1646  */
    { (yyval.OBJ) = (yyvsp[0].DEF); }
#line 1882 "yacc.cc" /* yacc.c:1646  */
    break;

  case 13:
#line 131 "qcl.y" /* yacc.c:1646  */
    { (yyval.OBJ) = (yyvsp[0].DEF); }
#line 1888 "yacc.cc" /* yacc.c:1646  */
    break;

  case 14:
#line 132 "qcl.y" /* yacc.c:1646  */
    { (yyval.OBJ) = (yyvsp[0].STMT); }
#line 1894 "yacc.cc" /* yacc.c:1646  */
    break;

  case 15:
#line 133 "qcl.y" /* yacc.c:1646  */
    { (yyval.OBJ) = (yyvsp[0].STMTLIST); }
#line 1900 "yacc.cc" /* yacc.c:1646  */
    break;

  case 16:
#line 134 "qcl.y" /* yacc.c:1646  */
    { (yyval.OBJ) = YYNEW(sInclude(*(yyvsp[-1].STRING))); }
#line 1906 "yacc.cc" /* yacc.c:1646  */
    break;

  case 17:
#line 135 "qcl.y" /* yacc.c:1646  */
    { (yyval.OBJ) = (yyvsp[0].OBJ); }
#line 1912 "yacc.cc" /* yacc.c:1646  */
    break;

  case 18:
#line 138 "qcl.y" /* yacc.c:1646  */
    { 
	  (yyval.DEF) = YYNEW(sFunctDef(tType((yyvsp[-5].TYPE)),(yyvsp[-4].ID),(yyvsp[-3].DEFLIST),(yyvsp[-1].DEFLIST),(yyvsp[0].STMTLIST))); }
#line 1919 "yacc.cc" /* yacc.c:1646  */
    break;

  case 19:
#line 140 "qcl.y" /* yacc.c:1646  */
    { 
	  (yyval.DEF) = YYNEW(sFunctDef(tType((yyvsp[-6].TYPE),(yyvsp[-5].TENSOR)),(yyvsp[-4].ID),(yyvsp[-3].DEFLIST),(yyvsp[-1].DEFLIST),(yyvsp[0].STMTLIST))); }
#line 1926 "yacc.cc" /* yacc.c:1646  */
    break;

  case 20:
#line 144 "qcl.y" /* yacc.c:1646  */
    { 
	  (yyval.DEF) = YYNEW(sQuOpDef((yyvsp[-4].ID),(yyvsp[-3].DEFLIST),(yyvsp[-1].DEFLIST),(yyvsp[0].STMTLIST))); }
#line 1933 "yacc.cc" /* yacc.c:1646  */
    break;

  case 21:
#line 146 "qcl.y" /* yacc.c:1646  */
    {
	  (yyval.DEF) = YYNEW(sQuOpDef((yyvsp[-3].ID),(yyvsp[-2].DEFLIST),0,0,0,1)); }
#line 1940 "yacc.cc" /* yacc.c:1646  */
    break;

  case 22:
#line 148 "qcl.y" /* yacc.c:1646  */
    { 
	  (yyval.DEF) = YYNEW(sQuOpDef((yyvsp[-4].ID),(yyvsp[-3].DEFLIST),(yyvsp[-1].DEFLIST),(yyvsp[0].STMTLIST),1)); }
#line 1947 "yacc.cc" /* yacc.c:1646  */
    break;

  case 23:
#line 150 "qcl.y" /* yacc.c:1646  */
    {
	  (yyval.DEF) = YYNEW(sQuOpDef((yyvsp[-3].ID),(yyvsp[-2].DEFLIST),0,0,1,1)); }
#line 1954 "yacc.cc" /* yacc.c:1646  */
    break;

  case 24:
#line 154 "qcl.y" /* yacc.c:1646  */
    { 
	  (yyval.DEF) = YYNEW(sQuFunDef((yyvsp[-4].ID),(yyvsp[-3].DEFLIST),(yyvsp[-1].DEFLIST),(yyvsp[0].STMTLIST))); }
#line 1961 "yacc.cc" /* yacc.c:1646  */
    break;

  case 25:
#line 156 "qcl.y" /* yacc.c:1646  */
    {
	  (yyval.DEF) = YYNEW(sQuFunDef((yyvsp[-3].ID),(yyvsp[-2].DEFLIST),0,0,0,1)); }
#line 1968 "yacc.cc" /* yacc.c:1646  */
    break;

  case 26:
#line 158 "qcl.y" /* yacc.c:1646  */
    { 
	  (yyval.DEF) = YYNEW(sQuFunDef((yyvsp[-4].ID),(yyvsp[-3].DEFLIST),(yyvsp[-1].DEFLIST),(yyvsp[0].STMTLIST),1)); }
#line 1975 "yacc.cc" /* yacc.c:1646  */
    break;

  case 27:
#line 160 "qcl.y" /* yacc.c:1646  */
    {
	  (yyval.DEF) = YYNEW(sQuFunDef((yyvsp[-3].ID),(yyvsp[-2].DEFLIST),0,0,1,1)); }
#line 1982 "yacc.cc" /* yacc.c:1646  */
    break;

  case 28:
#line 162 "qcl.y" /* yacc.c:1646  */
    { 
	  (yyval.DEF) = YYNEW(sQuFunDef((yyvsp[-4].ID),(yyvsp[-3].DEFLIST),(yyvsp[-1].DEFLIST),(yyvsp[0].STMTLIST))); 
          YYTRY((yyval.DEF)->setFlag(flagFUNOP)); }
#line 1990 "yacc.cc" /* yacc.c:1646  */
    break;

  case 29:
#line 165 "qcl.y" /* yacc.c:1646  */
    {
	  (yyval.DEF) = YYNEW(sQuFunDef((yyvsp[-4].ID),(yyvsp[-3].DEFLIST),(yyvsp[-1].DEFLIST),(yyvsp[0].STMTLIST),1)); 
          YYTRY((yyval.DEF)->setFlag(flagFUNOP)); }
#line 1998 "yacc.cc" /* yacc.c:1646  */
    break;

  case 30:
#line 170 "qcl.y" /* yacc.c:1646  */
    { 
	  (yyval.DEF) = YYNEW(sProcDef((yyvsp[-4].ID),(yyvsp[-3].DEFLIST),(yyvsp[-1].DEFLIST),(yyvsp[0].STMTLIST))); }
#line 2005 "yacc.cc" /* yacc.c:1646  */
    break;

  case 31:
#line 172 "qcl.y" /* yacc.c:1646  */
    {
	  (yyval.DEF) = YYNEW(sProcDef((yyvsp[-3].ID),new sDefList(),(yyvsp[-1].DEFLIST),(yyvsp[0].STMTLIST))); }
#line 2012 "yacc.cc" /* yacc.c:1646  */
    break;

  case 32:
#line 176 "qcl.y" /* yacc.c:1646  */
    { (yyval.DEF) = YYNEW(sVarDef(tType((yyvsp[-2].TYPE)),(yyvsp[-1].ID))); }
#line 2018 "yacc.cc" /* yacc.c:1646  */
    break;

  case 33:
#line 177 "qcl.y" /* yacc.c:1646  */
    { (yyval.DEF) = YYNEW(sVarDef(tType((yyvsp[-5].TYPE)),(yyvsp[-4].ID),(yyvsp[-2].EXPR),0)); }
#line 2024 "yacc.cc" /* yacc.c:1646  */
    break;

  case 34:
#line 178 "qcl.y" /* yacc.c:1646  */
    { (yyval.DEF) = YYNEW(sVarDef(tType((yyvsp[-6].TYPE),(yyvsp[-5].TENSOR)),(yyvsp[-4].ID),(yyvsp[-2].EXPR),0)); }
#line 2030 "yacc.cc" /* yacc.c:1646  */
    break;

  case 35:
#line 179 "qcl.y" /* yacc.c:1646  */
    { (yyval.DEF) = YYNEW(sVarDef(tType((yyvsp[-4].TYPE)),(yyvsp[-3].ID),0,(yyvsp[-1].EXPR))); }
#line 2036 "yacc.cc" /* yacc.c:1646  */
    break;

  case 36:
#line 180 "qcl.y" /* yacc.c:1646  */
    { (yyval.DEF) = YYNEW(sVarDef(tType((yyvsp[-5].TYPE),(yyvsp[-4].TENSOR)),(yyvsp[-3].ID),0,(yyvsp[-1].EXPR))); }
#line 2042 "yacc.cc" /* yacc.c:1646  */
    break;

  case 37:
#line 181 "qcl.y" /* yacc.c:1646  */
    {
          	(yyval.DEF) = YYNEW(sVarDef(tType((yyvsp[-4].TYPE)),(yyvsp[-3].ID),0,new sVar(new tId(CONDID))));
          	YYTRY((yyval.DEF)->setFlag(flagCONDDEF)); 
          }
#line 2051 "yacc.cc" /* yacc.c:1646  */
    break;

  case 38:
#line 187 "qcl.y" /* yacc.c:1646  */
    { (yyval.DEF) = YYNEW(sConstDef((yyvsp[-3].ID),(yyvsp[-1].EXPR))); }
#line 2057 "yacc.cc" /* yacc.c:1646  */
    break;

  case 39:
#line 189 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMTLIST) = (yyvsp[-1].STMTLIST); }
#line 2063 "yacc.cc" /* yacc.c:1646  */
    break;

  case 40:
#line 190 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMTLIST) = YYNEW(sStmtList()); }
#line 2069 "yacc.cc" /* yacc.c:1646  */
    break;

  case 41:
#line 193 "qcl.y" /* yacc.c:1646  */
    { (yyval.DEFLIST) = (yyvsp[0].DEFLIST); }
#line 2075 "yacc.cc" /* yacc.c:1646  */
    break;

  case 42:
#line 194 "qcl.y" /* yacc.c:1646  */
    { (yyval.DEFLIST) = YYNEW(sDefList()); }
#line 2081 "yacc.cc" /* yacc.c:1646  */
    break;

  case 43:
#line 197 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMTLIST) = (yyvsp[-1].STMTLIST); }
#line 2087 "yacc.cc" /* yacc.c:1646  */
    break;

  case 44:
#line 198 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMTLIST) = YYNEW(sStmtList()); }
#line 2093 "yacc.cc" /* yacc.c:1646  */
    break;

  case 45:
#line 201 "qcl.y" /* yacc.c:1646  */
    { (yyval.DEFLIST) = YYNEW(sDefList()); YYTRY((yyval.DEFLIST)->append((yyvsp[0].DEF))); }
#line 2099 "yacc.cc" /* yacc.c:1646  */
    break;

  case 46:
#line 202 "qcl.y" /* yacc.c:1646  */
    { (yyval.DEFLIST) = YYNEW(sDefList()); YYTRY((yyval.DEFLIST)->append((yyvsp[0].DEF))); }
#line 2105 "yacc.cc" /* yacc.c:1646  */
    break;

  case 47:
#line 203 "qcl.y" /* yacc.c:1646  */
    { YYTRY((yyvsp[-1].DEFLIST)->append((yyvsp[0].DEF))); (yyval.DEFLIST)=(yyvsp[-1].DEFLIST); }
#line 2111 "yacc.cc" /* yacc.c:1646  */
    break;

  case 48:
#line 204 "qcl.y" /* yacc.c:1646  */
    { YYTRY((yyvsp[-1].DEFLIST)->append((yyvsp[0].DEF))); (yyval.DEFLIST)=(yyvsp[-1].DEFLIST); }
#line 2117 "yacc.cc" /* yacc.c:1646  */
    break;

  case 49:
#line 207 "qcl.y" /* yacc.c:1646  */
    { (yyval.DEF) = YYNEW(sArgDef(tType((yyvsp[-1].TYPE)),(yyvsp[0].ID))); }
#line 2123 "yacc.cc" /* yacc.c:1646  */
    break;

  case 50:
#line 208 "qcl.y" /* yacc.c:1646  */
    { (yyval.DEF) = YYNEW(sArgDef(tType((yyvsp[-2].TYPE),(yyvsp[-1].TENSOR)),(yyvsp[0].ID))); }
#line 2129 "yacc.cc" /* yacc.c:1646  */
    break;

  case 51:
#line 211 "qcl.y" /* yacc.c:1646  */
    { (yyval.DEFLIST) = YYNEW(sDefList()); YYTRY((yyval.DEFLIST)->append((yyvsp[0].DEF))); }
#line 2135 "yacc.cc" /* yacc.c:1646  */
    break;

  case 52:
#line 212 "qcl.y" /* yacc.c:1646  */
    { YYTRY((yyvsp[-2].DEFLIST)->append((yyvsp[0].DEF))); (yyval.DEFLIST)=(yyvsp[-2].DEFLIST); }
#line 2141 "yacc.cc" /* yacc.c:1646  */
    break;

  case 53:
#line 215 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMTLIST) = YYNEW(sStmtList()); YYTRY((yyval.STMTLIST)->append((yyvsp[0].STMT))); }
#line 2147 "yacc.cc" /* yacc.c:1646  */
    break;

  case 54:
#line 216 "qcl.y" /* yacc.c:1646  */
    { YYTRY((yyvsp[-1].STMTLIST)->append((yyvsp[0].STMT))); (yyval.STMTLIST)=(yyvsp[-1].STMTLIST); }
#line 2153 "yacc.cc" /* yacc.c:1646  */
    break;

  case 55:
#line 219 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sCall((yyvsp[-3].ID),(yyvsp[-2].EXPRLIST))); }
#line 2159 "yacc.cc" /* yacc.c:1646  */
    break;

  case 56:
#line 220 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sCall((yyvsp[-2].ID),new sExprList())); }
#line 2165 "yacc.cc" /* yacc.c:1646  */
    break;

  case 57:
#line 221 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sCall((yyvsp[-3].ID),(yyvsp[-2].EXPRLIST),1)); }
#line 2171 "yacc.cc" /* yacc.c:1646  */
    break;

  case 58:
#line 222 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sAssign(new sVar((yyvsp[-3].ID)),(yyvsp[-1].EXPR))); }
#line 2177 "yacc.cc" /* yacc.c:1646  */
    break;

  case 59:
#line 223 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sAssign(new sVar((yyvsp[-6].ID)),(yyvsp[-1].EXPR),(yyvsp[-4].EXPRLIST))); }
#line 2183 "yacc.cc" /* yacc.c:1646  */
    break;

  case 60:
#line 224 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sCall(new tId(SWAPID),new sExprList((yyvsp[-3].EXPR),(yyvsp[-1].EXPR)))); }
#line 2189 "yacc.cc" /* yacc.c:1646  */
    break;

  case 61:
#line 225 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sCall(new tId(FANOUTID),new sExprList((yyvsp[-3].EXPR),(yyvsp[-1].EXPR)))); }
#line 2195 "yacc.cc" /* yacc.c:1646  */
    break;

  case 62:
#line 226 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sCall(new tId(FANOUTID),new sExprList((yyvsp[-3].EXPR),(yyvsp[-1].EXPR)),1)); }
#line 2201 "yacc.cc" /* yacc.c:1646  */
    break;

  case 63:
#line 227 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sFor(new sVar((yyvsp[-5].ID)),(yyvsp[-3].EXPR),(yyvsp[-1].EXPR),(yyvsp[0].STMTLIST))); }
#line 2207 "yacc.cc" /* yacc.c:1646  */
    break;

  case 64:
#line 228 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sFor(new sVar((yyvsp[-7].ID)),(yyvsp[-5].EXPR),(yyvsp[-3].EXPR),(yyvsp[0].STMTLIST),(yyvsp[-1].EXPR))); }
#line 2213 "yacc.cc" /* yacc.c:1646  */
    break;

  case 65:
#line 229 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sIf((yyvsp[-1].EXPR),(yyvsp[0].STMTLIST))); }
#line 2219 "yacc.cc" /* yacc.c:1646  */
    break;

  case 66:
#line 230 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sIf((yyvsp[-3].EXPR),(yyvsp[-2].STMTLIST),(yyvsp[0].STMTLIST))); }
#line 2225 "yacc.cc" /* yacc.c:1646  */
    break;

  case 67:
#line 231 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sWhile((yyvsp[-1].EXPR),(yyvsp[0].STMTLIST))); }
#line 2231 "yacc.cc" /* yacc.c:1646  */
    break;

  case 68:
#line 232 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sUntil((yyvsp[-1].EXPR),(yyvsp[-3].STMTLIST))); }
#line 2237 "yacc.cc" /* yacc.c:1646  */
    break;

  case 69:
#line 233 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sBreak()); }
#line 2243 "yacc.cc" /* yacc.c:1646  */
    break;

  case 70:
#line 234 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sReturn((yyvsp[-1].EXPR))); }
#line 2249 "yacc.cc" /* yacc.c:1646  */
    break;

  case 71:
#line 235 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sInput(new sVar((yyvsp[-1].ID)),0)); }
#line 2255 "yacc.cc" /* yacc.c:1646  */
    break;

  case 72:
#line 236 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sInput(new sVar((yyvsp[-1].ID)),(yyvsp[-3].EXPR))); }
#line 2261 "yacc.cc" /* yacc.c:1646  */
    break;

  case 73:
#line 237 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sPrint(new sExprList())); }
#line 2267 "yacc.cc" /* yacc.c:1646  */
    break;

  case 74:
#line 238 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sPrint((yyvsp[-1].EXPRLIST))); }
#line 2273 "yacc.cc" /* yacc.c:1646  */
    break;

  case 75:
#line 239 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sExit(0)); }
#line 2279 "yacc.cc" /* yacc.c:1646  */
    break;

  case 76:
#line 240 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sExit((yyvsp[-1].EXPR))); }
#line 2285 "yacc.cc" /* yacc.c:1646  */
    break;

  case 77:
#line 241 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sMeasure((yyvsp[-1].EXPR),0)); }
#line 2291 "yacc.cc" /* yacc.c:1646  */
    break;

  case 78:
#line 242 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sMeasure((yyvsp[-3].EXPR),new sVar((yyvsp[-1].ID)))); }
#line 2297 "yacc.cc" /* yacc.c:1646  */
    break;

  case 79:
#line 243 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sReset()); }
#line 2303 "yacc.cc" /* yacc.c:1646  */
    break;

  case 80:
#line 244 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sDump(0)); }
#line 2309 "yacc.cc" /* yacc.c:1646  */
    break;

  case 81:
#line 245 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sDump((yyvsp[-1].EXPR))); }
#line 2315 "yacc.cc" /* yacc.c:1646  */
    break;

  case 82:
#line 246 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sPlot()); }
#line 2321 "yacc.cc" /* yacc.c:1646  */
    break;

  case 83:
#line 247 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sPlot((yyvsp[-1].EXPR))); }
#line 2327 "yacc.cc" /* yacc.c:1646  */
    break;

  case 84:
#line 248 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sPlot((yyvsp[-3].EXPR),(yyvsp[-1].EXPR))); }
#line 2333 "yacc.cc" /* yacc.c:1646  */
    break;

  case 85:
#line 249 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sInspect(0)); }
#line 2339 "yacc.cc" /* yacc.c:1646  */
    break;

  case 86:
#line 250 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sInspect((yyvsp[-1].EXPRLIST))); }
#line 2345 "yacc.cc" /* yacc.c:1646  */
    break;

  case 87:
#line 251 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sLoad(0)); }
#line 2351 "yacc.cc" /* yacc.c:1646  */
    break;

  case 88:
#line 252 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sLoad((yyvsp[-1].EXPR))); }
#line 2357 "yacc.cc" /* yacc.c:1646  */
    break;

  case 89:
#line 253 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sSave(0)); }
#line 2363 "yacc.cc" /* yacc.c:1646  */
    break;

  case 90:
#line 254 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sSave((yyvsp[-1].EXPR))); }
#line 2369 "yacc.cc" /* yacc.c:1646  */
    break;

  case 91:
#line 255 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sShell()); }
#line 2375 "yacc.cc" /* yacc.c:1646  */
    break;

  case 92:
#line 256 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sSet(*(yyvsp[-1].STRING),0)); }
#line 2381 "yacc.cc" /* yacc.c:1646  */
    break;

  case 93:
#line 257 "qcl.y" /* yacc.c:1646  */
    { (yyval.STMT) = YYNEW(sSet(*(yyvsp[-2].STRING),(yyvsp[-1].EXPR))); }
#line 2387 "yacc.cc" /* yacc.c:1646  */
    break;

  case 94:
#line 260 "qcl.y" /* yacc.c:1646  */
    { (yyval.EXPRLIST) = YYNEW(sExprList()); YYTRY((yyval.EXPRLIST)->append((yyvsp[0].EXPR))); }
#line 2393 "yacc.cc" /* yacc.c:1646  */
    break;

  case 95:
#line 261 "qcl.y" /* yacc.c:1646  */
    { YYTRY((yyvsp[-2].EXPRLIST)->append((yyvsp[0].EXPR))); (yyval.EXPRLIST)=(yyvsp[-2].EXPRLIST); }
#line 2399 "yacc.cc" /* yacc.c:1646  */
    break;

  case 96:
#line 264 "qcl.y" /* yacc.c:1646  */
    { (yyval.EXPR) = (yyvsp[0].CONST); }
#line 2405 "yacc.cc" /* yacc.c:1646  */
    break;

  case 97:
#line 265 "qcl.y" /* yacc.c:1646  */
    { (yyval.EXPR) = YYNEW(sVar((yyvsp[0].ID))); }
#line 2411 "yacc.cc" /* yacc.c:1646  */
    break;

  case 98:
#line 266 "qcl.y" /* yacc.c:1646  */
    { (yyval.EXPR) = YYNEW(sSubscript(new sVar((yyvsp[-3].ID)),(yyvsp[-1].EXPRLIST))); }
#line 2417 "yacc.cc" /* yacc.c:1646  */
    break;

  case 99:
#line 267 "qcl.y" /* yacc.c:1646  */
    { (yyval.EXPR) = YYNEW(sSubRange(new sVar((yyvsp[-5].ID)),(yyvsp[-3].EXPR),(yyvsp[-1].EXPR),SUBRANGE_LENGTH)); }
#line 2423 "yacc.cc" /* yacc.c:1646  */
    break;

  case 100:
#line 268 "qcl.y" /* yacc.c:1646  */
    { (yyval.EXPR) = YYNEW(sSubRange(new sVar((yyvsp[-5].ID)),(yyvsp[-3].EXPR),(yyvsp[-1].EXPR),SUBRANGE_END)); }
#line 2429 "yacc.cc" /* yacc.c:1646  */
    break;

  case 101:
#line 269 "qcl.y" /* yacc.c:1646  */
    { (yyval.EXPR) = YYNEW(sFunctCall((yyvsp[-2].ID),(yyvsp[-1].EXPRLIST))); }
#line 2435 "yacc.cc" /* yacc.c:1646  */
    break;

  case 102:
#line 270 "qcl.y" /* yacc.c:1646  */
    { (yyval.EXPR) = YYNEW(sNeg((yyvsp[0].EXPR))); }
#line 2441 "yacc.cc" /* yacc.c:1646  */
    break;

  case 103:
#line 271 "qcl.y" /* yacc.c:1646  */
    { (yyval.EXPR) = YYNEW(sNot((yyvsp[0].EXPR))); }
#line 2447 "yacc.cc" /* yacc.c:1646  */
    break;

  case 104:
#line 272 "qcl.y" /* yacc.c:1646  */
    { (yyval.EXPR) = YYNEW(sLength((yyvsp[0].EXPR))); }
#line 2453 "yacc.cc" /* yacc.c:1646  */
    break;

  case 105:
#line 273 "qcl.y" /* yacc.c:1646  */
    { (yyval.EXPR) = YYNEW(sOr((yyvsp[-2].EXPR),(yyvsp[0].EXPR))); }
#line 2459 "yacc.cc" /* yacc.c:1646  */
    break;

  case 106:
#line 274 "qcl.y" /* yacc.c:1646  */
    { (yyval.EXPR) = YYNEW(sXor((yyvsp[-2].EXPR),(yyvsp[0].EXPR))); }
#line 2465 "yacc.cc" /* yacc.c:1646  */
    break;

  case 107:
#line 275 "qcl.y" /* yacc.c:1646  */
    { (yyval.EXPR) = YYNEW(sAnd((yyvsp[-2].EXPR),(yyvsp[0].EXPR))); }
#line 2471 "yacc.cc" /* yacc.c:1646  */
    break;

  case 108:
#line 276 "qcl.y" /* yacc.c:1646  */
    { (yyval.EXPR) = YYNEW(sEqual((yyvsp[-2].EXPR),(yyvsp[0].EXPR))); }
#line 2477 "yacc.cc" /* yacc.c:1646  */
    break;

  case 109:
#line 277 "qcl.y" /* yacc.c:1646  */
    { (yyval.EXPR) = YYNEW(sLeEq((yyvsp[-2].EXPR),(yyvsp[0].EXPR))); }
#line 2483 "yacc.cc" /* yacc.c:1646  */
    break;

  case 110:
#line 278 "qcl.y" /* yacc.c:1646  */
    { (yyval.EXPR) = YYNEW(sLeEq((yyvsp[0].EXPR),(yyvsp[-2].EXPR))); }
#line 2489 "yacc.cc" /* yacc.c:1646  */
    break;

  case 111:
#line 279 "qcl.y" /* yacc.c:1646  */
    { (yyval.EXPR) = YYNEW(sNotEq((yyvsp[-2].EXPR),(yyvsp[0].EXPR))); }
#line 2495 "yacc.cc" /* yacc.c:1646  */
    break;

  case 112:
#line 280 "qcl.y" /* yacc.c:1646  */
    { (yyval.EXPR) = YYNEW(sLess((yyvsp[-2].EXPR),(yyvsp[0].EXPR))); }
#line 2501 "yacc.cc" /* yacc.c:1646  */
    break;

  case 113:
#line 281 "qcl.y" /* yacc.c:1646  */
    { (yyval.EXPR) = YYNEW(sLess((yyvsp[0].EXPR),(yyvsp[-2].EXPR))); }
#line 2507 "yacc.cc" /* yacc.c:1646  */
    break;

  case 114:
#line 282 "qcl.y" /* yacc.c:1646  */
    { (yyval.EXPR) = YYNEW(sAdd((yyvsp[-2].EXPR),(yyvsp[0].EXPR))); }
#line 2513 "yacc.cc" /* yacc.c:1646  */
    break;

  case 115:
#line 283 "qcl.y" /* yacc.c:1646  */
    { (yyval.EXPR) = YYNEW(sSub((yyvsp[-2].EXPR),(yyvsp[0].EXPR))); }
#line 2519 "yacc.cc" /* yacc.c:1646  */
    break;

  case 116:
#line 284 "qcl.y" /* yacc.c:1646  */
    { (yyval.EXPR) = YYNEW(sConcat((yyvsp[-2].EXPR),(yyvsp[0].EXPR))); }
#line 2525 "yacc.cc" /* yacc.c:1646  */
    break;

  case 117:
#line 285 "qcl.y" /* yacc.c:1646  */
    { (yyval.EXPR) = YYNEW(sMod((yyvsp[-2].EXPR),(yyvsp[0].EXPR))); }
#line 2531 "yacc.cc" /* yacc.c:1646  */
    break;

  case 118:
#line 286 "qcl.y" /* yacc.c:1646  */
    { (yyval.EXPR) = YYNEW(sMult((yyvsp[-2].EXPR),(yyvsp[0].EXPR))); }
#line 2537 "yacc.cc" /* yacc.c:1646  */
    break;

  case 119:
#line 287 "qcl.y" /* yacc.c:1646  */
    { (yyval.EXPR) = YYNEW(sDiv((yyvsp[-2].EXPR),(yyvsp[0].EXPR))); }
#line 2543 "yacc.cc" /* yacc.c:1646  */
    break;

  case 120:
#line 288 "qcl.y" /* yacc.c:1646  */
    { (yyval.EXPR) = YYNEW(sPow((yyvsp[-2].EXPR),(yyvsp[0].EXPR))); }
#line 2549 "yacc.cc" /* yacc.c:1646  */
    break;

  case 121:
#line 289 "qcl.y" /* yacc.c:1646  */
    { (yyval.EXPR) = (yyvsp[-1].EXPR); }
#line 2555 "yacc.cc" /* yacc.c:1646  */
    break;

  case 122:
#line 290 "qcl.y" /* yacc.c:1646  */
    { (yyval.EXPR) = YYNEW(sBaseFunct((yyvsp[-2].OBJTYPE),(yyvsp[-1].EXPR))); }
#line 2561 "yacc.cc" /* yacc.c:1646  */
    break;

  case 123:
#line 291 "qcl.y" /* yacc.c:1646  */
    { (yyval.EXPR) = YYNEW(sListFunct((yyvsp[-2].OBJTYPE),(yyvsp[-1].EXPRLIST))); }
#line 2567 "yacc.cc" /* yacc.c:1646  */
    break;

  case 124:
#line 292 "qcl.y" /* yacc.c:1646  */
    { (yyval.EXPR) = YYNEW(sListFunct((yyvsp[-1].OBJTYPE),new sExprList())); }
#line 2573 "yacc.cc" /* yacc.c:1646  */
    break;


#line 2577 "yacc.cc" /* yacc.c:1646  */
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
