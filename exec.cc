/**********************************************************************

This file is part of the Quantum Computation Language QCL.

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/



#include "syntax.h"
#include "error.h"
#include "quheap.h"
#include "options.h"
#include "debug.h"
#include "dump.h"
#include "plot.h"


#define ERR (-1)
#define RET (-2)
#define BRK (-3)
#define CHECK(v) if((v).isError()) throw tError(errINT,"expression of type tERROR enountered",this)
#define EVAL(v,p) { if(p) { v=(p)->eval(loc,gl,qh); CHECK(v); } }

/***********************************************/
/***************** Definitions *****************/
/***********************************************/

#define TRACE() if (optTrace) qcltrace("DEFINE",this,loc,gl,qh)
// #define ASSERT(c) if(!(c)) throw tError(errINT,"define assertion " #c " failed",this)

void sDef::define(SymTable *loc,SymTable *gl,QuHeap *qh) {
  TRACE();
  throw tError(errINT,"define is not implemented in class sDef",this);
}

void sDefList::define(SymTable *loc,SymTable *gl,QuHeap *qh) {
  sDef *p;
  void *c;
  TRACE();
  for_plist(p,this,c) p->define(loc,gl,qh);
}

void sVarDef::define(SymTable *loc,SymTable *gl,QuHeap *qh) {
  tValue v,l;
  int e;
  TRACE();
  if(pinit) {
    EVAL(v,pinit);
    if(type()!=v.type()) {
      if(basetype()==tQUCOND) 
        v=v.toQuCond();
      else 
        v=v.conv(type());
    }
  } else {
    if(type().isQuExpr()) {
      ASSERT(plen);
      EVAL(l,plen);
      if(l.toInt()<0) 
      throw tError(errRANGE,"quantum register of negative length",this);
      v=qh->qualloc(l.toInt(),basetype());
      if(v.isError()) throw tError(errMEM,"not enough quantum memory",this);
      if(isGlobal()) qh->addReg(v.qustate()->newclone());
    } else if(ord()) {
      ASSERT(plen);
      EVAL(l,plen);
      if(l.toInt()<0) 
        throw tError(errRANGE,"invalid tensor dimension",this);
      v=tValue(type(),l.toInt());
    } else if(type().isQuCond()) {
      v=tValue(QCFALSE(qh->nBits()));
    } else {
      v=tValue(type());
    }
  }
  if(def()) e=loc->put(this,v); else e=gl->put(this,v);
  if(e) throw tError(errINT,"cannot store variable",this);
}

void sConstDef::define(SymTable *loc,SymTable *gl,QuHeap *qh) {
  tValue v;
  int e;
  TRACE();
  EVAL(v,pexpr);
  ASSERT(type()==v.type());
  if(def()) e=loc->put(this,v); else e=gl->put(this,v);
  if(e) throw tError(errINT,"cannot store constant",this);
}

void sRoutDef::define(SymTable *loc,SymTable *gl,QuHeap *qh) {
  TRACE();
  ASSERT(!def());
  if(gl->put(this)) throw tError(errINT,"cannot store routine",this);
}

#undef TRACE
#undef ASSERT


/***********************************************/
/***************** Statements ******************/
/***********************************************/


#define TRACE() if (optTrace) qcltrace("EXEC",this,loc,gl,qh)
#define ASSERT(c) if(!(c)) throw tError(errINT,"exec assertion " #c " failed",this)

void sStmt::exec(SymTable *loc,SymTable *gl,QuHeap *qh) {
  TRACE();
  throw tError(errINT,"exec is not implemented in class sStmt",this);
}

void sStmtList::exec(SymTable *loc,SymTable *gl,QuHeap *qh) {
  sStmt *p;
  void *c;
  TRACE();
  for_plist(p,this,c) {
    try {
      p->exec(loc,gl,qh);
    } catch(tError e) {
      if(optDebug && e.type()!=errIRQ) {
        qclerror(e);
        qclshell(loc,gl,qh,e.object() ? e.object() : p,DB_ERROR);
        throw tError(errIGNORE);
      }
      throw;
    }
  }
}

void sCall::exec(SymTable *loc,SymTable *gl,QuHeap *qh) {
  tValue v;
  SymTab *psym;
  sRoutDef *d;
  sExpr *p;
  sDef *q;
  void *cp,*cq;
  bitvec m(qh->nBits());
  int l=0;
  TRACE();
  d=(sRoutDef*)gl->getDef(id());
  ASSERT(d && (d->isProcDef() || d->isQuDef()));
  psym=new SymTab();
  for_pplist(p,ppar,cp,q,d->args(),cq,p && q) {
    try {
      v=p->eval(loc,gl,qh).conv(q->type());
    } catch(...) {
      qcl_delete(psym);
      throw;
    }
    if(v.isError() || psym->put(q,v)) { 
      qcl_delete(psym); 
      throw tError(errINT,"argument binding failed",this);
    }
    if(v.isQuExpr()) {
      if(zero(m & v.qustate()->mapmask())) {
        m |= v.qustate()->mapmask();
        l+=v.qustate()->mapbits();
      } else {
        qcl_delete(psym);
        throw tError(errRUN,"quantum arguments overlapping",this);
      }
    }
  }
    
  if(d->isCondDef()) {
    if(qh->cond()) {        
      ASSERT(d->isQuDef()); 
      if(!zero(m & qh->cond()->mapmask()) || !zero(m & qh->cmask())) {
        qcl_delete(psym);
        throw tError(errRUN,"arguments overlap with quantum condition",this);
      }
      l+=qh->cond()->mapbits();
    }
  } else {
    ASSERT(!qh->cond() && zero(qh->cmask()));
  }
  if(l==0 && d->isQuDef()) {
    qcl_delete(psym);
    return;
  }
  qh->call(d,psym,gl,isInv());
}

void sAssign::exec(SymTable *loc,SymTable *gl,QuHeap *qh) {
  tValue *pv;
  tValue v;
  TRACE();
  ASSERT((pv=loc->getRef(pvar->id())) || (pv=gl->getRef(pvar->id())));
  EVAL(v,pexpr);
  if(psubs) {
    sExpr *p;
    tValue s;
    void *c;
    tInt i=0;
    for_plist(p,psubs,c) {
      EVAL(s,p);
      if(s.toInt()>=pv->dim())
        throw tError(errRANGE,"subscript out of range",this);
      i=i*pv->dim()+s.toInt();
    }
    pv->set(i,v.conv(pv->basetype()));
  } else {
    *pv=v.conv(pv->type());
  }
}

void sFor::exec(SymTable *loc,SymTable *gl,QuHeap *qh) {
  tValue *p;
  tValue f,t,s;
  tInt i,st;
  TRACE();
  ASSERT((p=loc->getRef(pvar->id())) || (p=gl->getRef(pvar->id())));
  EVAL(f,pfrom);
  EVAL(t,pto);
  if(pstep) EVAL(s,pstep);
  ASSERT(f.isInt() && t.isInt() && (!pstep || s.isInt()));
  if(pstep) {
    st=s.toInt();
  } else {
    st= 1;
  }

  if(!st) throw tError(errRUN,"zero increment in for loop",this); 
  for(i=f.toInt();(i<=t.toInt() && st>=0) || (i>=t.toInt() && st<=0);i+=st) {
    *p=tValue(i);
    try {
      pbody->exec(loc,gl,qh);
    } catch(sBreak *p) {
      return;
    }
  }
}

void sIf::exec(SymTable *loc,SymTable *gl,QuHeap *qh) {
  tValue v;
  QuCond qc;
  TRACE();
  EVAL(v,pcond);
  ASSERT(v.isCond());
  if(!v.isBoolean()) {
    qc=v.toQuCond();
    if(qc.isTrue()) v=tValue(TRUE);
    if(qc.isFalse()) v=tValue(FALSE);
  }
  if(v.isBoolean()) {
    if(v.toBool()==TRUE) {
      pthen->exec(loc,gl,qh);
    } else {
      if(pelse) pelse->exec(loc,gl,qh);
    }
    return;
  }
  if(isSet(flagQUFORK)) {
    if(qh->qif(qc,gl,1))
      pthen->exec(loc,gl,qh);
    else if(qh->qelse(qc,gl))
      if(pelse) pelse->exec(loc,gl,qh);
  } else {
    if(qh->qif(qc,gl,pelse!=0)) pthen->exec(loc,gl,qh);
    if(pelse && qh->qelse(qc,gl)) pelse->exec(loc,gl,qh);
    qh->qendif(gl);
  }
}

void sLoop::exec(SymTable *loc,SymTable *gl,QuHeap *qh) {
  tValue v;
  TRACE();
  while(1) {
    if(!isSet(flagUNTIL)) {
      EVAL(v,pcond);
      ASSERT(v.isBoolean());
      if(v.toBool()==FALSE) return;
    }
    try {
      pbody->exec(loc,gl,qh);
    } catch(sBreak *p) {
      return;
    }
    if(isSet(flagUNTIL)) {
      EVAL(v,pcond);
      ASSERT(v.isBoolean());
      if(v.toBool()==TRUE) return;
    }
  }
}

void sBreak::exec(SymTable *loc,SymTable *gl,QuHeap *qh) {
  TRACE();
  throw this;
}

void sReturn::exec(SymTable *loc,SymTable *gl,QuHeap *qh) {
  tValue v;
  TRACE();
  EVAL(v,pexpr);
  throw v.conv(def()->type());
}

void sInput::exec(SymTable *loc,SymTable *gl,QuHeap *qh) {
  int n,e;
  tReal x,y;
  tValue v;
  tValue *p;
  string m,s;
  TRACE();
  ASSERT( (p=loc->getRef(pvar->id())) || (p=gl->getRef(pvar->id())) );
  if(pprompt) {
    EVAL(v,pprompt);
    m=v.toString();
  } else {
    m+=pvar->type().str()+" "+pvar->id()+" ";
    if(pvar->type().isComplex()) m+="[(Re,Im)] ";
    if(pvar->type().isBoolean()) m+="[t(rue)/f(alse)] ";
    m+="?";
  }
  m+=" ";
  while(1) {
    e=0;
    s=qclinput("? "+m)+"\n";
    switch(pvar->basetype()) {
      case tINTEGER:
        if(sscanf(s.c_str(),"%d",&n)==1) v=tValue((tInt)n);
        break;
      case tREAL:
        if(sscanf(s.c_str(),"%lf",&x)==1) v=tValue((tReal)x);
        break;
      case tCOMPLEX:
        if(sscanf(s.c_str(),"(%lf,%lf)",&x,&y)==2) v=tValue(tComplex(x,y));
        break;
      case tSTRING:
        v=tValue(s);
        break;
      case tBOOLEAN:
        if(s[0]=='t' || s[0]=='T')  v=tValue((boolean)TRUE);
        if(s[0]=='f' || s[0]=='F')  v=tValue((boolean)FALSE);
        break;
      default: ASSERT(0);
    };
    if(v.isDefined()) break;
  }
  *p=v;
  qcllog("? "+m+s);
}

void sPrint::exec(SymTable *loc,SymTable *gl,QuHeap *qh) {
  sExpr *p;
  void *c;
  string ostr;
  tValue v;
  TRACE();
  for_plist(p,plist,c) {
    EVAL(v,p);
    ostr+=v.str()+" ";
  }
  qclprint(ostr);
  qcllog(": "+ostr+"\n");
}

void sExit::exec(SymTable *loc,SymTable *gl,QuHeap *qh) {
  tValue v;
  TRACE();
  if(pmsg) {
    EVAL(v,pmsg);
    throw tError(errUSR,v.toString(),this);
  } else {
    throw tError(errEXIT);
  }
}

void sMeasure::exec(SymTable *loc,SymTable *gl,QuHeap *qh) {
  tValue s,m;
  tValue *p=0;
  ostream *log=&cout;
  TRACE();
  EVAL(s,pstate);
  ASSERT(s.isQuExpr());
  if(pvar) ASSERT(((p=loc->getRef(pvar->id())) || (p=gl->getRef(pvar->id()))) && p->isInt());
  if(s.isEmpty()) {
    if(pvar) *p=0;
    return;
  }
  if(optLog) {
    if(optLogfile) log=optLogfile;
    *log << "@ MEASURE " << s << "\n";
  };
  m=qh->measure(s);
  isStateModified=1;
  if(m.isUndef()) throw tError(errMATH,"measured integer is too long",this);
  if(!m.isInt()) throw tError(errINT,"measurement failed",this);
  if(pvar) *p=m;
}

void sInclude::exec(SymTable *loc,SymTable *gl,QuHeap *qh) {
  TRACE();
  throw tError(errINT,"uncaught include",this);
}


  
void sReset::exec(SymTable *loc,SymTable *gl,QuHeap *qh) {
  TRACE();
  if(optLog) {
    if(optLogfile) *optLogfile << "@ RESET\n"; else cout << "@ RESET\n";
  };
  qh->reset();
  isStateModified=1;
}


/***********************************************/
/****************** Commands *******************/
/***********************************************/


void sDump::exec(SymTable *loc,SymTable *gl,QuHeap *qh) {
  char t[80];
  tValue v;
  quState *q=0;
  bitvec b(qh->nBits()),c;
  ostream *f=0;
  TRACE();


  if(pexpr) {
    EVAL(v,pexpr);
    ASSERT(v.isQuExpr());
    q=v.qustate();
    ASSERT(q);
    if(v.isEmpty())
      throw tError(errINVPAR,"cannot dump register of lenght zero",this);
    qclprint("SPECTRUM "+ pexpr->prtstr()+": "+v.str());
  } else {
    sprintf(t,"STATE: %d / %d qubits allocated, %d / %d qubits free",
      qh->nBits()-qh->nFree(),qh->nBits(),qh->nFree(),qh->nBits());
    qclprint(t);
  }
  if(optDumpFilename!="") {
    f=new ofstream(optDumpFilename.c_str(),ios::out|ios::app);
    if(!f || !*f) {
      if(f) delete f;
      throw tError(errIO,"cannot open "+optDumpFilename,this);
    }
  }
  if(pexpr)
    dump_spectrum(q,f);
  else
    dump_state(qh,f);
  if(f) delete f;
}

void sPlot::exec(SymTable *loc,SymTable *gl,QuHeap *qh) {
  tValue v1,v2;
  quState *q1=0,*q2=0;
  string l1,l2;
  TRACE();
  if(pexpr1) {
    EVAL(v1,pexpr1);
    ASSERT(v1.isQuExpr());
    q1=v1.qustate();
    l1=pexpr1->prtstr()+sdec(q1->mapbits()," (%ld qubits)");
    v1.str();
  }
  if(pexpr2) {
    EVAL(v2,pexpr2);
    ASSERT(v2.isQuExpr());
    q2=v2.qustate();
    l2=pexpr2->prtstr()+sdec(q2->mapbits()," (%ld qubits)");
  }
  if(q1 && v1.isEmpty() || q2 && v2.isEmpty())
    throw tError(errINVPAR,"cannot plot register of lenght zero",this);
  if(q2) {
    plot_spectrum2(q1,q2,l1,l2);
  } else if(q1) {
    plot_spectrum(q1,l1);
  } else {
    plot_state(qh);
  }
}

void sInspect::exec(SymTable *loc,SymTable *gl,QuHeap *qh) {
  sExpr *p;
  sVar *q;
  void *c;
  sDef *d;
  string ostr;
  tValue *pv=0;
  TRACE();
  if(plist) {
    for_plist(p,plist,c) {
      ostr="";
      ASSERT(p->object()==sVAR);
      q=(sVar*)p;
      if(( d=loc->getDef(q->id()) )) {
  	ostr="local ";
	pv=loc->getRef(q->id());
      } else if(( d=gl->getDef(q->id()) )) {
  	ostr="global ";
	pv=gl->getRef(q->id());
      }
      ostr+=q->id();
      if(pv) ostr+=" = "+pv->str();
      if(!pv && !d) ostr+=" is undefined";
      qclprint(ostr);
      if(d) {
        ostr=d->prtstr(0);
        if(d->isArgDef()) ostr+=" (parameter)\n";
        qcloutput(ostr);
      }
    };
  } else {
    qclprint("global symbols:");
    qcloutput(gl->prtstr(0));
    qclprint("local symbols:");
    qcloutput(loc->prtstr(0));
  };
}

void sLoad::exec(SymTable *loc,SymTable *gl,QuHeap *qh) {
  ifstream f;
  tValue v;
  string fn;
  TRACE();
  if(pexpr) {
    EVAL(v,pexpr);
    ASSERT(v.isString());
    fn=v.toString();
  } else {
    fn=DEF_LOAD_FILE DEF_DATAFILE_EXT;
  };
  f.open(fn.c_str(),ios::in);
  if(!f) throw tError(errIO,"cannot open "+fn+" for reading",this);
  if(qh->load(f)) throw tError(errIO,"error while reading "+fn,this);
  isStateModified=1;
  f.close();
}

void sSave::exec(SymTable *loc,SymTable *gl,QuHeap *qh) {
  ofstream f;
  tValue v;
  string fn;
  TRACE();
  if(pexpr) {
    EVAL(v,pexpr);
    ASSERT(v.isString());
    fn=v.toString();
  } else {
    fn=DEF_SAVE_FILE DEF_DATAFILE_EXT;
  };
  f.open(fn.c_str(),ios::out);
  if(!f) throw tError(errIO,"cannot open "+fn+" for writing",this);
  if(qh->save(f)) throw tError(errIO,"error writing "+fn,this);
  f.close();
  if(!f) throw tError(errIO,"cannot close "+fn,this);
}

void sSet::exec(SymTable *loc,SymTable *gl,QuHeap *qh) {
  int i;
  tValue v;
  string s;
  TRACE();
  EVAL(v,pexpr);
  for(i=0;qcl_options[i].val;i++) {
    if(opt==string(qcl_options[i].name)) goto cont;
  }
  throw tError(errOPT,"illegal option "+opt,this);
cont:
  if(qcl_options[i].has_arg && !pexpr)
    throw tError(errOPT,"missing argument for option "+opt,this);
  if(!qcl_options[i].has_arg && pexpr)
    throw tError(errOPT,"option "+opt+" takes no argument",this);
  if(pexpr) s=v.str();
  evalopt(qcl_options[i].val,s.c_str());
}

void sShell::exec(SymTable *loc,SymTable *gl,QuHeap *qh) {
  string ostr;
  TRACE();
  if(!optShellEscape) return;
  qclshell(loc,gl,qh,def(),DB_ESCAPE);
}
 
