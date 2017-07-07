/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
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

/* Line 2068 of yacc.c  */
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



/* Line 2068 of yacc.c  */
#line 123 "yacc.hh"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


