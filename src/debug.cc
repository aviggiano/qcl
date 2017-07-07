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
#include "debug.h"
#include "dump.h"

/*

objlist::objlist() : list<sObject*>() {
  sObject *p;
  while((p=parseobj())) push_back(p);
  yyCleanUp();
}

objlist::~objlist() {
  while(size()) {
    delete front();
    pop_front();
  }
}

*/

int shell_depth=-1;

int qcllist(SymTable *loc,SymTable *gl,QuHeap *qh,sObject *obj,int flags) {
  objlist *o;
  sObject *p;

  o=parseobj();
  while(o->size()) {
    p=o->front();
    if(optEcho) qcloutput(p->prtstr(INDENT));
    if(p->isInclude()) {
      if(qclfile(((sInclude*)p)->filename(),loc,gl,qh,0,flags|QL_ERRORRETURN)) {
        delete o;
        return 1;
      }
      o->pop_front();
      delete p;
      continue;      
    }
    try {
      p->typecheck(loc,gl);
      if(p->isDef()) {
        ((sDef*)p)->define(loc,gl,qh);
      } else if(p->isStmt()) {
        ((sStmt*)p)->exec(loc,gl,qh);
        delete p;
      } else {
        throw tError(errINT,"input is neither definition nor statement");
      }
    } catch(tError e) {
      if(e.type()==errEXIT) { delete o; return 2; }
      if(e.type()==errIGNORE) {
      } else {
        if(flags&QL_ERRORABORT) qclabort(e);
        if(!(flags&QL_NOERRMSG)) qclerror(e);
        if(flags&QL_ERRORRETURN) { delete o; return 1; }
      }
      delete p;
    }
    o->pop_front();
  }
  return 0;
}  

int qclfile(string fname,SymTable *loc,SymTable *gl,QuHeap *qh,sObject *obj,int flags) { 
  FILE *f;
  string s;

  f=openqclfile(fname);  
  if(!f) { qclerror("Can't open "+fname); return 1; }
  if(chksyntax(f)) return 1; 
  f=openqclfile(fname);
  if(!f) { 
    qclerror("Can't reopen "+fname);
    return 1;
  }
  yyScanFile(f);
  return qcllist(loc,gl,qh,0,flags | QL_ERRORRETURN);
}  

int qclshell(SymTable *loc,SymTable *gl,QuHeap *qh,sObject *obj,int cond) { 
  string s,prompt;
  
  SymTab l,g(1);
  SymTabComb lcomb((SymTable*)&l,loc),gcomb((SymTable*)&g,gl);
  QuHeap lqh(qh);

  irqOff();
  shell_depth++;
  if(cond==DB_ESCAPE) qclmessage("shell escape");
  if(cond==DB_ERROR) {
    qclmessage("debug shell");
    qcloutput(loc->prtstr(1));
  }
  if(cond==DB_IRQ && obj) {
    qclmessage("user interrupt in "+obj->defstr());
    qcloutput(loc->prtstr(1));
  }
  prompt="qcl";
  if(shell_depth>=1) prompt+=(char)('0'+shell_depth);
  prompt+=cond==DB_ERROR ? "$ " : "> ";
    
  while(1) {
    if(isStateModified) lqh.state()->normalize();
    if(optAutoDump && isStateModified) report_state(&lqh);
    isStateModified=0;
    s=qclinput(prompt);
    if(s.substr(0,prompt.length())==prompt)
      s=s.erase(0,prompt.length());
    if(s=="\n") continue;
    if(s=="") { cout << "\n"; break; }
    s+=";";
    if(chksyntax(s)) continue;
    yyScanString(s);
    if(qcllist(&lcomb,&gcomb,&lqh,0,QL_ERRORRETURN)==2) break;
  };
  shell_depth--;
  return 0;
}

int qclstring(string s,SymTable *loc,SymTable *gl,QuHeap *qh) { 
  if(chksyntax(s)) return 1;
  yyScanString(s);
  return qcllist(loc,gl,qh,0,QL_ERRORRETURN);
}

  
