%{

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

%}


%union {
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
}

%type <OBJLIST>		objlist
%type <OBJ>		obj eof
%type <EXPR> 		expr
%type <EXPRLIST>	exprlist
%type <STMT> 		stmt
%type <STMTLIST> 	stmtlist block bodystm
%type <DEF>		arg constdef vardef functdef quopdef procdef qufundef 
%type <DEFLIST>		deflist arglist bodydef

%token <TYPE>	tokTYPE		400
%token <TENSOR> tokTENSOR	401
%token <ID>	tokID		402
%token <CONST>	tokCONS		403
%token <OBJTYPE> tokBASEFUNCT	404
%token <OBJTYPE> tokLISTFUNCT	405
%token <STRING>	tokINCLUDE	406
%token <STRING>	tokSET		407
%token <ID>	tokIDCALL	408

%token tokCONST         500
%token tokCOND          501
%token tokEXTERN        502
%token tokOP            503
%token tokPROC          504
%token tokQUFUN         505
%token tokFOR           506
%token tokTO            507
%token tokWHILE         508
%token tokUNTIL         509
%token tokBREAK         510
%token tokRETURN        511
%token tokIF            512
%token tokELSE          513
%token tokRANGE_LENGTH  514
%token tokRANGE_END     515
%token tokSTEP          516
%token tokINPUT         517
%token tokPRINT         518
%token tokEXIT          519
%token tokMEASURE       520
%token tokRESET         521

%token tokDUMP		601
%token tokINSPECT	602
%token tokLOAD		603
%token tokSAVE		604
%token tokPLOT		605
%token tokSHELL		606

%token tokEOF		900
%token tokERROR		901


%nonassoc 	tokTRANS tokINVTRANS tokSWAP
%left 		tokOR tokXOR
%left 		tokAND
%left 		tokNOT
%nonassoc 	tokEQ tokLEEQ tokGREQ tokNOTEQ '<' '>'
%left 		'+' '-' '&'
%left 		tokMOD
%left 		'*' '/'
%left 		tokNEG
%left		'^'
%left		'#'

%%

objlist:  obj		{ $$ = YYNEW(objlist); YYTRY($$->push_back($1)); }
	| eof		{ yyObjList = $$ = YYNEW(objlist); YYACCEPT; }
	| objlist obj 	{ YYTRY($1->push_back($2)); $$=$1; }
        | objlist eof 	{ yyObjList = $$ = $1; YYACCEPT; }
;

eof:	  tokEOF	{ $$ = 0; }
	| ';' eof	{ $$ = 0; }
;

obj:	  functdef 	{ $$ = $1; }
	| quopdef 	{ $$ = $1; }
	| qufundef 	{ $$ = $1; }
	| procdef 	{ $$ = $1; }
	| vardef 	{ $$ = $1; }
	| constdef 	{ $$ = $1; }
	| stmt 	 	{ $$ = $1; }
	| block 	{ $$ = $1; }
	| tokINCLUDE ';'{ $$ = YYNEW(sInclude(*$1)); }
	| ';' obj	{ $$ = $2; }
;

functdef:  tokTYPE tokIDCALL arglist ')' bodydef bodystm  { 
	  $$ = YYNEW(sFunctDef(tType($1),$2,$3,$5,$6)); }
	| tokTYPE tokTENSOR tokIDCALL arglist ')' bodydef bodystm  { 
	  $$ = YYNEW(sFunctDef(tType($1,$2),$3,$4,$6,$7)); }
;

quopdef:  tokOP tokIDCALL arglist ')' bodydef bodystm  { 
	  $$ = YYNEW(sQuOpDef($2,$3,$5,$6)); }
	| tokEXTERN tokOP tokIDCALL arglist ')' ';' {
	  $$ = YYNEW(sQuOpDef($3,$4,0,0,0,1)); }
	| tokCOND tokOP tokIDCALL arglist ')' bodydef bodystm  { 
	  $$ = YYNEW(sQuOpDef($3,$4,$6,$7,1)); }
	| tokEXTERN tokCOND tokOP tokIDCALL arglist ')' ';' {
	  $$ = YYNEW(sQuOpDef($4,$5,0,0,1,1)); }
;

qufundef:  tokQUFUN tokIDCALL arglist ')' bodydef bodystm  { 
	  $$ = YYNEW(sQuFunDef($2,$3,$5,$6)); }
	| tokEXTERN tokQUFUN tokIDCALL arglist ')' ';' {
	  $$ = YYNEW(sQuFunDef($3,$4,0,0,0,1)); }
	| tokCOND tokQUFUN tokIDCALL arglist ')' bodydef bodystm  { 
	  $$ = YYNEW(sQuFunDef($3,$4,$6,$7,1)); }
	| tokEXTERN tokCOND tokQUFUN tokIDCALL arglist ')' ';' {
	  $$ = YYNEW(sQuFunDef($4,$5,0,0,1,1)); }
	| tokQUFUN tokOP tokIDCALL arglist ')' bodydef bodystm  { 
	  $$ = YYNEW(sQuFunDef($3,$4,$6,$7)); 
          YYTRY($$->setFlag(flagFUNOP)); }
	| tokCOND tokQUFUN tokOP tokIDCALL arglist ')' bodydef bodystm {
	  $$ = YYNEW(sQuFunDef($4,$5,$7,$8,1)); 
          YYTRY($$->setFlag(flagFUNOP)); }
;

procdef:  tokPROC tokIDCALL arglist ')' bodydef bodystm  { 
	  $$ = YYNEW(sProcDef($2,$3,$5,$6)); }
	| tokPROC tokIDCALL ')' bodydef bodystm  {
	  $$ = YYNEW(sProcDef($2,new sDefList(),$4,$5)); }
;

vardef:	  tokTYPE tokID ';' { $$ = YYNEW(sVarDef(tType($1),$2)); }
	| tokTYPE tokID '[' expr ']' ';' { $$ = YYNEW(sVarDef(tType($1),$2,$4,0)); }
	| tokTYPE tokTENSOR tokID '[' expr ']' ';' { $$ = YYNEW(sVarDef(tType($1,$2),$3,$5,0)); }
	| tokTYPE tokID '=' expr ';' { $$ = YYNEW(sVarDef(tType($1),$2,0,$4)); }
	| tokTYPE tokTENSOR tokID '=' expr ';' { $$ = YYNEW(sVarDef(tType($1,$2),$3,0,$5)); }
        | tokTYPE tokID '=' tokCOND ';' {
          	$$ = YYNEW(sVarDef(tType($1),$2,0,new sVar(new tId(CONDID))));
          	YYTRY($$->setFlag(flagCONDDEF)); 
          }
;

constdef: tokCONST tokID '=' expr ';' { $$ = YYNEW(sConstDef($2,$4)); };

block:    '{' stmtlist '}' { $$ = $2; }
	| '{' '}' { $$ = YYNEW(sStmtList()); }
;

bodydef:  '{' deflist { $$ = $2; }
	| '{' { $$ = YYNEW(sDefList()); }
;

bodystm:  stmtlist '}' { $$ = $1; }
	| '}' { $$ = YYNEW(sStmtList()); }
;

deflist:  vardef	{ $$ = YYNEW(sDefList()); YYTRY($$->append($1)); }
	| constdef	{ $$ = YYNEW(sDefList()); YYTRY($$->append($1)); }
	| deflist vardef { YYTRY($1->append($2)); $$=$1; }
	| deflist constdef { YYTRY($1->append($2)); $$=$1; }
;

arg: 	  tokTYPE tokID { $$ = YYNEW(sArgDef(tType($1),$2)); }
	| tokTYPE tokTENSOR tokID { $$ = YYNEW(sArgDef(tType($1,$2),$3)); }
;

arglist:  arg      { $$ = YYNEW(sDefList()); YYTRY($$->append($1)); }
	| arglist ',' arg { YYTRY($1->append($3)); $$=$1; }
;
	 
stmtlist: stmt		{ $$ = YYNEW(sStmtList()); YYTRY($$->append($1)); }
	| stmtlist stmt { YYTRY($1->append($2)); $$=$1; }
;

stmt: 	  tokIDCALL exprlist ')' ';' { $$ = YYNEW(sCall($1,$2)); }
	| tokIDCALL ')' ';' { $$ = YYNEW(sCall($1,new sExprList())); }
	| '!' tokIDCALL exprlist ')' ';' { $$ = YYNEW(sCall($2,$3,1)); }
	| tokID '=' expr ';' { $$ = YYNEW(sAssign(new sVar($1),$3)); }
	| tokID '[' exprlist ']' '=' expr ';' { $$ = YYNEW(sAssign(new sVar($1),$6,$3)); }
	| expr tokSWAP expr ';' { $$ = YYNEW(sCall(new tId(SWAPID),new sExprList($1,$3))); }
	| expr tokTRANS expr ';' { $$ = YYNEW(sCall(new tId(FANOUTID),new sExprList($1,$3))); }
	| expr tokINVTRANS expr ';' { $$ = YYNEW(sCall(new tId(FANOUTID),new sExprList($1,$3),1)); }
	| tokFOR tokID '=' expr tokTO expr block { $$ = YYNEW(sFor(new sVar($2),$4,$6,$7)); }
	| tokFOR tokID '=' expr tokTO expr tokSTEP expr block { $$ = YYNEW(sFor(new sVar($2),$4,$6,$9,$8)); }
	| tokIF expr block { $$ = YYNEW(sIf($2,$3)); }
	| tokIF expr block tokELSE block { $$ = YYNEW(sIf($2,$3,$5)); }
	| tokWHILE expr block { $$ = YYNEW(sWhile($2,$3)); }
	| block tokUNTIL expr ';' { $$ = YYNEW(sUntil($3,$1)); }
	| tokBREAK ';' { $$ = YYNEW(sBreak()); }
	| tokRETURN expr ';' { $$ = YYNEW(sReturn($2)); }
        | tokINPUT tokID ';' { $$ = YYNEW(sInput(new sVar($2),0)); }
        | tokINPUT expr ',' tokID ';' { $$ = YYNEW(sInput(new sVar($4),$2)); }
	| tokPRINT ';' { $$ = YYNEW(sPrint(new sExprList())); }
	| tokPRINT exprlist ';' { $$ = YYNEW(sPrint($2)); }
	| tokEXIT ';' { $$ = YYNEW(sExit(0)); }
	| tokEXIT expr ';' { $$ = YYNEW(sExit($2)); }
        | tokMEASURE expr ';' { $$ = YYNEW(sMeasure($2,0)); }
        | tokMEASURE expr ',' tokID ';' { $$ = YYNEW(sMeasure($2,new sVar($4))); }
	| tokRESET ';' { $$ = YYNEW(sReset()); }
	| tokDUMP ';' { $$ = YYNEW(sDump(0)); }
	| tokDUMP expr ';' { $$ = YYNEW(sDump($2)); }
        | tokPLOT ';' { $$ = YYNEW(sPlot()); }
        | tokPLOT expr ';' { $$ = YYNEW(sPlot($2)); }
        | tokPLOT expr ',' expr ';' { $$ = YYNEW(sPlot($2,$4)); }
	| tokINSPECT ';' { $$ = YYNEW(sInspect(0)); }
	| tokINSPECT exprlist ';' { $$ = YYNEW(sInspect($2)); }
	| tokLOAD ';' { $$ = YYNEW(sLoad(0)); }
	| tokLOAD expr ';' { $$ = YYNEW(sLoad($2)); }
	| tokSAVE ';' { $$ = YYNEW(sSave(0)); }
	| tokSAVE expr ';' { $$ = YYNEW(sSave($2)); }	
	| tokSHELL ';' { $$ = YYNEW(sShell()); }
	| tokSET ';' { $$ = YYNEW(sSet(*$1,0)); }
	| tokSET expr ';' { $$ = YYNEW(sSet(*$1,$2)); }
;

exprlist: expr      { $$ = YYNEW(sExprList()); YYTRY($$->append($1)); }
	| exprlist ',' expr { YYTRY($1->append($3)); $$=$1; }
;

expr: 	  tokCONS { $$ = $1; }
	| tokID { $$ = YYNEW(sVar($1)); }
	| tokID '[' exprlist ']' { $$ = YYNEW(sSubscript(new sVar($1),$3)); }
	| tokID '[' expr tokRANGE_LENGTH expr ']' { $$ = YYNEW(sSubRange(new sVar($1),$3,$5,SUBRANGE_LENGTH)); }
	| tokID '[' expr tokRANGE_END expr ']' { $$ = YYNEW(sSubRange(new sVar($1),$3,$5,SUBRANGE_END)); }
	| tokIDCALL exprlist ')' { $$ = YYNEW(sFunctCall($1,$2)); }
	| '-' expr %prec tokNEG { $$ = YYNEW(sNeg($2)); }
	| tokNOT expr { $$ = YYNEW(sNot($2)); }
	| '#' expr { $$ = YYNEW(sLength($2)); }
	| expr tokOR expr { $$ = YYNEW(sOr($1,$3)); }
	| expr tokXOR expr { $$ = YYNEW(sXor($1,$3)); }
	| expr tokAND expr { $$ = YYNEW(sAnd($1,$3)); }
	| expr tokEQ expr { $$ = YYNEW(sEqual($1,$3)); }
	| expr tokLEEQ expr { $$ = YYNEW(sLeEq($1,$3)); }
	| expr tokGREQ expr { $$ = YYNEW(sLeEq($3,$1)); }
	| expr tokNOTEQ expr { $$ = YYNEW(sNotEq($1,$3)); }
	| expr '<' expr { $$ = YYNEW(sLess($1,$3)); }
	| expr '>' expr { $$ = YYNEW(sLess($3,$1)); }
	| expr '+' expr { $$ = YYNEW(sAdd($1,$3)); }
	| expr '-' expr { $$ = YYNEW(sSub($1,$3)); }
	| expr '&' expr { $$ = YYNEW(sConcat($1,$3)); }
	| expr tokMOD expr { $$ = YYNEW(sMod($1,$3)); }
	| expr '*' expr { $$ = YYNEW(sMult($1,$3)); }
	| expr '/' expr { $$ = YYNEW(sDiv($1,$3)); }
	| expr '^' expr { $$ = YYNEW(sPow($1,$3)); }
	| '(' expr ')' { $$ = $2; }
	| tokBASEFUNCT expr ')' { $$ = YYNEW(sBaseFunct($1,$2)); }
	| tokLISTFUNCT exprlist ')' { $$ = YYNEW(sListFunct($1,$2)); }
	| tokLISTFUNCT ')' { $$ = YYNEW(sListFunct($1,new sExprList())); }
;

