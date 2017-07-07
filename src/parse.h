/**********************************************************************

This file is part of the Quantum Computation Language QCL.

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/


#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include <list>
extern char *yytext;
#define YYNEW(o) (yyTest ? 0 : new o)
#define YYTRY(o) { if(!yyTest) { o; } }
#define YYMAXINCLUDE 10
#define YY_USER_INIT { yyToplevelFile=0; yyStringBufferActive=0; yyIncludeStackPt=0; }

extern void yyrestart(FILE*);
extern int yyparse();
extern int yydebug;

extern void yyScanString(string s);
extern void yyScanFile(FILE *f);
extern void yyCleanUp();

class objlist : public list<sObject*> {
public:
  ~objlist() { 
    while(size()) {
      if(front()) delete front();
      pop_front();
    }
  }
};


//extern sObject *yyObject;
extern objlist *yyObjList;

extern int yyTest;
extern FILE* yyToplevelFile;
extern int yyStringBufferActive;
extern string yyFilenames[YYMAXINCLUDE];
extern FILE* yyFilePointers[YYMAXINCLUDE];
extern int yyLineNos[YYMAXINCLUDE];
extern int yyIncludeStackPt;
extern string yyFilename;
extern int yyLineNo;
extern int yyStmtBeg;


FILE* openqclfile(string fname);

int chksyntax(string s);
int chksyntax(FILE* f);
objlist* parseobj();
string safestring(const char *s);

#endif
