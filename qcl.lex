%{

/**********************************************************************

This file is part of the Quantum Computation Language QCL.

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/

#include "types.h"
#include "syntax.h"
#include "parse.h"
#include "yacc.h"

YY_BUFFER_STATE include_stack[YYMAXINCLUDE];
YY_BUFFER_STATE string_buffer;
FILE* toplevel_file;

double cnum_real,cnum_imag;

%}

%option noyywrap
%option yylineno

%x STR
%x REM
%x COM
%x INC
%x SET

%x SCINC

ALPHA		[a-zA-Z]
DIGIT 		[0-9]
ALPHANUM	{ALPHA}|{DIGIT}
SPECIAL		[^a-zA-Z0-9]
UNSIGNED        {DIGIT}+
REAL            {DIGIT}+"."{DIGIT}*
CNUM            [ \t]*[+\-]?{DIGIT}+("."{DIGIT}*)?[ \t]*
COMPLEX		"("{CNUM}","{CNUM}")"
ID		{ALPHA}{ALPHANUM}*
%%

"const"		yylval.OBJ=0; return tokCONST;
"cond"		yylval.OBJ=0; return tokCOND; 
"extern"	yylval.OBJ=0; return tokEXTERN;
"operator"	yylval.OBJ=0; return tokOP;
"procedure"	yylval.OBJ=0; return tokPROC;
"qufunct"	yylval.OBJ=0; return tokQUFUN;
"for"		yylval.OBJ=0; return tokFOR;
"to"		yylval.OBJ=0; return tokTO;
"while"		yylval.OBJ=0; return tokWHILE;
"until"		yylval.OBJ=0; return tokUNTIL;
"break"		yylval.OBJ=0; return tokBREAK; 
"return"	yylval.OBJ=0; return tokRETURN;
"if"		yylval.OBJ=0; return tokIF;
"else"		yylval.OBJ=0; return tokELSE;
"and"		yylval.OBJ=0; return tokAND;
"or"		yylval.OBJ=0; return tokOR;
"xor"		yylval.OBJ=0; return tokXOR;
"not"		yylval.OBJ=0; return tokNOT;
"mod"		yylval.OBJ=0; return tokMOD;
"step"		yylval.OBJ=0; return tokSTEP;
"input"		yylval.OBJ=0; return tokINPUT;
"print"		yylval.OBJ=0; return tokPRINT;
"exit"		yylval.OBJ=0; return tokEXIT;
"measure"	yylval.OBJ=0; return tokMEASURE;
"reset"		yylval.OBJ=0; return tokRESET;
"dump"		yylval.OBJ=0; return tokDUMP;
"plot"		yylval.OBJ=0; return tokPLOT; 
"list"		yylval.OBJ=0; return tokINSPECT;
"load"		yylval.OBJ=0; return tokLOAD;
"save"		yylval.OBJ=0; return tokSAVE;
"shell"		yylval.OBJ=0; return tokSHELL;

"<->"			yylval.OBJ=0; return tokSWAP;
"->"			yylval.OBJ=0; return tokTRANS;
"<-"			yylval.OBJ=0; return tokINVTRANS;
"=="			yylval.OBJ=0; return tokEQ;
"<="			yylval.OBJ=0; return tokLEEQ;
">="			yylval.OBJ=0; return tokGREQ;
"!="			yylval.OBJ=0; return tokNOTEQ;
"\\"			yylval.OBJ=0; return tokRANGE_LENGTH;
"::"			yylval.OBJ=0; return tokRANGE_LENGTH;
":"			yylval.OBJ=0; return tokRANGE_END; 
".."			yylval.OBJ=0; return tokRANGE_END; 

"("|")"|"["|"]" 	yylval.OBJ=0; return *yytext;
"+"|"-"|"*"|"/"|"^" 	yylval.OBJ=0; return *yytext;
"<"|">"|"="|"#"		yylval.OBJ=0; return *yytext;
"!"|"&"|","		yylval.OBJ=0; return *yytext;

"{"[ \t\n\r;]*		yylval.OBJ=0; return '{';
"}"[ \t\n\r;]*		yylval.OBJ=0; return '}';
";"[ \t\n\r;]*		yylval.OBJ=0; return ';';

"boolean"	yylval.TYPE=tBOOLEAN; return tokTYPE;
"int"		yylval.TYPE=tINTEGER; return tokTYPE;
"real"		yylval.TYPE=tREAL; return tokTYPE;
"complex"	yylval.TYPE=tCOMPLEX; return tokTYPE;
"string"	yylval.TYPE=tSTRING; return tokTYPE;
"qureg"		yylval.TYPE=tQUREG; return tokTYPE;
"quconst"	yylval.TYPE=tQUCONST; return tokTYPE;
"quvoid"	yylval.TYPE=tQUVOID; return tokTYPE;
"quscratch"	yylval.TYPE=tQUSCR; return tokTYPE;
"qucond"	yylval.TYPE=tQUCOND; return tokTYPE;

"vector"	yylval.TENSOR=1; return tokTENSOR;
"matrix"	yylval.TENSOR=2; return tokTENSOR;
"tensor"[3-9]	yylval.TENSOR=yytext[6]-'0'; return tokTENSOR;

"exp("	 	yylval.OBJTYPE=sEXP; return tokBASEFUNCT;
"sin("	 	yylval.OBJTYPE=sSIN; return tokBASEFUNCT;
"cos("	 	yylval.OBJTYPE=sCOS; return tokBASEFUNCT;
"tan("	 	yylval.OBJTYPE=sTAN; return tokBASEFUNCT;
"cot("	 	yylval.OBJTYPE=sCOT; return tokBASEFUNCT;
"sinh("	 	yylval.OBJTYPE=sSINH; return tokBASEFUNCT;
"cosh("	 	yylval.OBJTYPE=sCOSH; return tokBASEFUNCT;
"tanh("	 	yylval.OBJTYPE=sTANH; return tokBASEFUNCT;
"coth("	 	yylval.OBJTYPE=sCOTH; return tokBASEFUNCT;
"abs("	 	yylval.OBJTYPE=sABS; return tokBASEFUNCT;
"Re("	 	yylval.OBJTYPE=sRE; return tokBASEFUNCT;
"Im("	 	yylval.OBJTYPE=sIM; return tokBASEFUNCT;
"conj("	 	yylval.OBJTYPE=sCONJ; return tokBASEFUNCT;
"floor("	yylval.OBJTYPE=sFLOOR; return tokBASEFUNCT;
"ceil("	 	yylval.OBJTYPE=sCEIL; return tokBASEFUNCT;
"sqrt("	 	yylval.OBJTYPE=sSQRT; return tokBASEFUNCT;
"not("	 	yylval.OBJTYPE=sINOT; return tokBASEFUNCT;
"int("		yylval.OBJTYPE=sINT; return tokBASEFUNCT;
"real("		yylval.OBJTYPE=sREAL; return tokBASEFUNCT;
"complex("	yylval.OBJTYPE=sCOMPLEX; return tokBASEFUNCT;
"string("	yylval.OBJTYPE=sSTRING; return tokBASEFUNCT;

"log("	 	yylval.OBJTYPE=sLOG; return tokLISTFUNCT;
"random("	yylval.OBJTYPE=sRANDOM; return tokLISTFUNCT;
"min("	 	yylval.OBJTYPE=sMIN; return tokLISTFUNCT;
"max("	 	yylval.OBJTYPE=sMAX; return tokLISTFUNCT;
"gcd("	 	yylval.OBJTYPE=sGCD; return tokLISTFUNCT;
"lcm("	 	yylval.OBJTYPE=sLCM; return tokLISTFUNCT;
"bit("	 	yylval.OBJTYPE=sBIT; return tokLISTFUNCT;
"and("	 	yylval.OBJTYPE=sIAND; return tokLISTFUNCT;
"or("	 	yylval.OBJTYPE=sIOR; return tokLISTFUNCT;
"xor("	 	yylval.OBJTYPE=sIXOR; return tokLISTFUNCT;

"vector("	yylval.OBJTYPE=sVECTOR; return tokLISTFUNCT;
"matrix("	yylval.OBJTYPE=sMATRIX; return tokLISTFUNCT;
"tensor"[3-9]"(" {
	yylval.OBJTYPE=(ObjType)(sSCALAR+(yytext[6]-'0'));
        return tokLISTFUNCT;
      }

 yylval.OBJTYPE=sMATRIX; return tokLISTFUNCT;

"set"[ \t]+		BEGIN(SET);
<SET>[a-zA-Z\-]+ {
	BEGIN(0);
	yylval.STRING=YYNEW(string(yytext)); 
	return tokSET;
      }	

"include"[ \t]+\"	BEGIN(INC);
<INC>[^\"\n\t]+ {
	yylval.STRING=YYNEW(string(yytext));
	return tokINCLUDE;
      }	
<INC>\"			BEGIN(0);


"true" {
	yylval.OBJ=YYNEW(sConst(tValue(TRUE)));
	return tokCONS;
      }

"false" {
	yylval.OBJ=YYNEW(sConst(tValue(FALSE)));
	return tokCONS;
      }

{UNSIGNED} {
	yylval.OBJ=YYNEW(sConst(tValue((tInt)atol(yytext))));
	return tokCONS;
      }

{UNSIGNED}".." {
	yylval.OBJ=YYNEW(sConst(tValue((tInt)atol(yytext))));
        unput('.'); unput('.');
	return tokCONS;
      }

{REAL} { 
	yylval.OBJ=YYNEW(sConst(tValue((tReal)atof(yytext))));
	return tokCONS;
      }

{COMPLEX} {
	sscanf(yytext,"(%lf,%lf)",&cnum_real,&cnum_imag);
	yylval.OBJ=YYNEW(sConst(tValue(tComplex(cnum_real,cnum_imag))));
	return tokCONS;
      }

{ID}"("	yylval.ID=YYNEW(tId(yytext,strlen(yytext)-1)); return tokIDCALL;
{ID}	yylval.ID=YYNEW(tId(yytext)); return tokID;

\"\"	yylval.OBJ=YYNEW(sConst(tValue(string("")))); return tokCONS;

\"			BEGIN(STR);
<STR>[^\"\n\t]*	{
	yylval.OBJ=YYNEW(sConst(tValue((char*)yytext)));
	return tokCONS;
      }

<STR>\"			BEGIN(0);

"/*"         	    BEGIN(REM);
<REM>[^*\n]*        ;
<REM>"*"+[^*/\n]*   ;
<REM>\n             ;
<REM>"*"+"/"        BEGIN(0);

"//"			BEGIN(COM);
<COM>[^\n]*		;
<COM>"\n"		BEGIN(0);

^"<<"[ \t]*		BEGIN(SCINC);

<SCINC>[^\"\n \t;]+ {
	BEGIN(0);
	yylval.STRING=YYNEW(string(yytext));
	return tokINCLUDE;
      }	

^"?"		yylval.OBJ=0; return tokPRINT;


[ \t\n\r]	;

<<EOF>>		yylval.OBJ=0; return tokEOF;

.		yylval.OBJ=0; return tokERROR; 

%%

void yyScanString(string s) { 
  YY_FLUSH_BUFFER;
  if(yyStringBufferActive) yy_delete_buffer(string_buffer);

  string_buffer=yy_scan_string(s.c_str());
  yyIncludeStackPt=0;
  yyStringBufferActive=1;
  yyToplevelFile=0;
  yylineno=1;
}

void yyScanFile(FILE *f) {
  YY_FLUSH_BUFFER;
  if(yyStringBufferActive) yy_delete_buffer(string_buffer);
  yyrestart(f);
  yyIncludeStackPt=0;
  yyStringBufferActive=0;
  yyToplevelFile=f;
  yylineno=1;
}

void yyCleanUp() {
  int i;
  YY_FLUSH_BUFFER;
  yyrestart(stdin);
  if(yyToplevelFile) fclose (yyToplevelFile);
  if(yyStringBufferActive) yy_delete_buffer(string_buffer);
  yyToplevelFile=0;
  yyStringBufferActive=0;
  for(i=0;i<yyIncludeStackPt;i++) {
    if(i) yy_delete_buffer(include_stack[i]);
    if(yyFilePointers[i]) {
      fclose(yyFilePointers[i]);
      yyFilePointers[i]=0;
    }
  }
  yyIncludeStackPt=0;
}

