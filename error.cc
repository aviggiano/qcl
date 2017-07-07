/**********************************************************************

This file is part of the Quantum Computation Language QCL.

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/


#pragma implementation


#ifdef QCL_USE_READLINE
#include <stdlib.h>
#include <stdio.h>
extern "C" {
#include <readline/readline.h>
#include <readline/history.h>
};
#endif

#include "error.h"
#include "syntax.h"
#include "symbols.h"
#include "quheap.h"
#include "options.h"

int isErrorReported=0;

void initialize_readline() {
#ifdef QCL_USE_READLINE
// rl_bind_key ('\t', rl_insert);
rl_unbind_key ('\t');
#endif
}

const char *ERROR_STR[] = {
  "no error","exit","message","internal error","illegal token","parse error",
  "type mismatch","invalid type","parameter mismatch","invalid parameter",
  "unknown symbol","illegal scope","invalid definition","math error",
  "runtime error","general error","syntax error","user error",
  "range error", "external error", "I/O-error", "shell error", 
  "memory error", "option error", "ignored", "user interrupt"
};

void qclerror(string e) {
  cout << format->error_beg << e << format->error_end;
  if(optLogfile) {
    *optLogfile << "! " << e << '\n';
  }
}

void qclerror(const tError& e) {
  if(e.where()!="") qclerror(e.where()+":");
  string s=ERROR_STR[e.type()];
  s+=": "+e.message();
  qclerror(s);
}

void qclabort(string e) { 
  if(e!="") qclerror(e);
  if(optLogfile) {
    *optLogfile << "! QCL terminated\n";
    qcl_delete(optLogfile);
    optLogfile=0;
  }
  cout << format->output_end;
  exit(1);
}

void qclabort(const tError& e) {
  qclerror(e);
  qclabort();
}

string qclinput(string p) {
  static string lastline="";
  string prompt=format->prompt_beg+p+format->prompt_end;
  string t="";
  irqOff();
  if(optTeXmacs) {
    char c;
    cout << prompt << format->output_end  << flush;
    while(cin.get(c) && c!='\n') t+=c;
    if(!cin.eof()) t+='\n';
  } else {
#ifdef QCL_USE_READLINE
    char *l;
    cout << format->output_end << flush;
    l=readline(prompt.c_str());
    if(l) {
      t=l; t+='\n';
      if(*l && t!=lastline) {
        add_history(l);
        lastline=t;
      }
      free(l);
    }
#else
    char c;
    cout << prompt << format->output_end << flush;
    while(cin.get(c) && c!='\n') t+=c;
    if(!cin.eof()) t+='\n';
#endif
  }
  if(optIRQ) irqOn();
  cout << format->output_beg;
  return t;
}
  
void qcloutput(string s) {
  cout << s << flush;
}  

void qclprint(string s) {
  cout << format->print_beg << s << format->print_end << flush;
}  

void qclmessage(string s) {
  cout << format->msg_beg << s << format->msg_end << flush;
}

void qcllog(string s) {
  if(optLogfile) *optLogfile << s << flush;
}

void qcltrace(string s,sObject *obj,SymTable *loc,SymTable *gl,QuHeap *qh) {
  cerr << s;
  if(obj) { 
    cerr << " Object " << obj->objstr();
    if(obj->def())
      cerr << " (" << obj->defstr() << ")";
    if(obj->isExpr()) cerr << " type " << ((sExpr*)obj)->type().str();
    cerr << "\n";
  }
  if(obj) cerr << "  line:  " << obj->prtstr() << "\n";
//if(gl) cerr << "  global:" << gl->prtstr() << "\n";
  if(loc)  cerr << "  local: " << loc->prtstr() << "\n";
  if(qh) cerr << "  quheap:" << qh->prtstr() << "\n";
}

tError::tError(ErrType t,string s,sObject *o) {
  err=t;
  msg=s;
  obj=0;
  if(o) setobj(o);
}

void tError::setobj(sObject *o) {
  obj=o;
  loc="";
  if(!o) return;
  if(o->inRoutDef()) {
    loc+="in "+o->def()->declstr()+" ";
  }
  string s=o->prtstr();
  if(s.length()>40) {
    s.resize(25);
    s+=" ...";
  }
  loc+="at \""+s+'"';
}

