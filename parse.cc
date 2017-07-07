/**********************************************************************

This file is part of the Quantum Computation Language QCL.

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/


#include "syntax.h"
#include "symbols.h"
#include "error.h"
#include "parse.h"
#include "options.h"

objlist *yyObjList;
int yyTest;
FILE* yyToplevelFile;
int yyStringBufferActive;
string yyFilenames[YYMAXINCLUDE];
FILE* yyFilePointers[YYMAXINCLUDE];
int yyLineNos[YYMAXINCLUDE];
int yyIncludeStackPt = 0;
string yyFilename="<input>";

extern char *yytext;
extern int yylineno;

string safestring(const char *s) {
  string t;
  while(*s) {
    if(isprint(*s))
      t+=*s;
    else
      t+=sdec(*s,"\\0%lo");
    s++;
  }
  return t;
}

int yyerror(const char* s) {
  string t;
  if(!yyStringBufferActive) {
    t+="in "+yyFilename+", line "+sdec(yylineno)+", ";
  };
  t+="near \""+safestring(yytext)+"\"";
  qclerror(t);
  qclerror(s);
  return 1;
}

FILE* openqclfile(string fname) {
  string s;
  FILE *f;
  s=fname;
  if(( f=fopen(s.c_str(),"r") )) { yyFilename=s; return f; };
  s=fname+".qcl";
  if(( f=fopen(s.c_str(),"r") )) { yyFilename=s; return f; };
  if(optUserPath!="") {
    s=optUserPath+"/"+fname;
    if(( f=fopen(s.c_str(),"r") )) { yyFilename=s; return f; };
    s=optUserPath+"/"+fname+".qcl";
    if(( f=fopen(s.c_str(),"r") )) { yyFilename=s; return f; };
  }
  if(optIncludePath!="") {
    s=optIncludePath+"/"+fname;
    if(( f=fopen(s.c_str(),"r") )) { yyFilename=s; return f; };
    s=optIncludePath+"/"+fname+".qcl";
    if(( f=fopen(s.c_str(),"r") )) { yyFilename=s; return f; };
  }
  s="lib/"+fname;
  if(( f=fopen(s.c_str(),"r") )) { yyFilename=s; return f; };
  s="lib/"+fname+".qcl";
  if(( f=fopen(s.c_str(),"r") )) { yyFilename=s; return f; };
  return 0;
}

int chksyntax(string s) {
  int r;
  yyTest=1;
  yyObjList=0;
  yyScanString(s);
  r=yyparse();
  yyCleanUp();
  yyTest=0;
  return r;
}

int chksyntax(FILE* f) {
  int r;
  yyTest=1;
  yyObjList=0;
  yyScanFile(f);
  r=yyparse();
  yyCleanUp();
  yyTest=0;
  return r;
}

objlist* parseobj() {
  yyTest=0;
  yyObjList=0;
  int r;
  r=yyparse();
  if(r || !yyObjList) qclabort("parsing failed");
  return yyObjList;
}
