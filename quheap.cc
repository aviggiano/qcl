/**********************************************************************

This file is part of the Quantum Computation Language QCL.

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/


#pragma implementation

#include "quheap.h"
#include "error.h"

#include <sstream>

#include <stdio.h>

int isStateModified=1;

term string2term(const string& s,int l) {
  term t(l);

  istringstream buf(s.c_str());
  buf >> t;
  return t;
}  
      
string term2string(const term& t,int binary) {
  ostringstream buf;
  buf << t;
  return string(buf.str());
}


class opFANOUT : public opGate {
  int inv;
public:
  opFANOUT(int n,int i) : opGate(2*n) { inv=i; }
  virtual term funct(const bitvec& v) const { 
    bitvec a(v.getbits(0,bits()/2));
    bitvec b(v.getbits(bits()/2,bits()/2));
    b^=a;
    a+=b;
    return term(a,1.0);
  };
  virtual opOperator *newclone() const { return new opFANOUT(bits()/2,inv); }
};


QuHeap::QuHeap(int n,int d) {
  bs=new quBaseState(n);
  delbs=1;
  nbits=n;
  mbits=bitvec(n).qnot();
  nfree=n;
  mfree=bitvec(n).qnot();
  ndirty=0;
  mdirty=bitvec(n);
  parent=0;
  delayed=d;
  init();
}

QuHeap::QuHeap(quState *s,int d) {
  int n;
  bs=s;
  delbs=0;
  n=s->mapbits();
  nbits=n;
  mbits=bitvec(n).qnot();
  nfree=n;
  mfree=bitvec(n).qnot();
  ndirty=0;
  mdirty=bitvec(n);
  parent=0;
  delayed=d;
  init();
}
 
QuHeap::QuHeap(QuHeap *h,int d) {
  bs=h->bs;
  delbs=0;
  nbits=h->nbits;
  mbits=h->mbits;
  nfree=h->nfree;
  mfree=h->mfree;
  ndirty=h->ndirty;
  mdirty=h->mdirty;
  parent=h;
  delayed=d;
  regs=h->regs;
  init();
}

void QuHeap::init() {
  ignore=0;
  qconds=0;
}

QuHeap::~QuHeap() {
  while(!ql.empty()) {
    if(ql.back().s) delete ql.back().s;
    ql.pop_back();
  }
  while(!cd.empty()) {
    centry c=cd.back();
    if(c.ev) delete c.ev;
    if(c.reg) delete c.reg;
    if(c.reg0) delete c.reg0;
    cd.pop_back();
  }
  while(!regs.empty()) {
    regs.pop_back();
  }
  if(bs && delbs) qcl_delete(bs);
}

tValue QuHeap::qualloc(int n,BaseType t) {
  int i,o=0,l,ll; 
  quState *ss;

  if(n==0) return tValue(new quEmpty(*bs),t);
  if(n>nfree) throw tError(errMEM,"out of quantum memory");
  
  while(o+n<=nbits) {
    for(i=o;i<o+n;i++) {
      if(!mfree[i]) {
    	o=i+1;
    	break;
      };
    };
    if(i>=o) break;
  };
  if(o+n<=nbits) {
    ss=bs->newsubstring(n,o);
    nfree-=n;
    mfree&=~ ss->mapmask();
    return tValue(ss);
  };
  o=l=0;
  ss=0;
  while(o<nbits && l<n) {
    if(!mfree[o]) { o++; continue; }
    for(i=o+1;i<n || !mfree[i];i++);
    ll=i-o;
    if(l+ll>n) ll=n-l;
    if(ss) {
      ss=new quCombState(ss,bs->newsubstring(l,o),1);
    } else {
      ss=bs->newsubstring(l,o);
    };
    l+=ll;
  }
  if(!ss || l!=n || ss->mapbits()!=n) {
    if(ss) qcl_delete(ss);
    throw tError(errMEM,"register allocation failed");
  }
  nfree-=n;
  mfree&=~ ss->mapmask();
  return tValue(ss,t);    
}

void QuHeap::qufree(tValue var) {
  int n;
  bitvec m;
  quState *ss;
  if(!var.isQuExpr()) throw tError(errINVTYP);
  ss=var.qustate();
  n=ss->mapbits();
  m=ss->mapmask();
  if(n>nbits-nfree-ndirty || !zero(m & mdirty) || !zero(m & mfree))
    throw tError(errMEM,"qufree: overlapping registers");
  nfree+=n;
  mfree|=m; 
}

tValue QuHeap::measure(tValue var) {
  bitvec m;
  if(!var.isQuExpr()) throw tError(errINVTYP);
  if(var.qustate()->mapbits()>8*(int)sizeof(tInt)) 
    throw tError(errRANGE,"register loo long to measure");
  m=var.qustate()->measure();
  return(tValue((tInt)m.getword()));
}

void QuHeap::reset() {
  bs->reset();
}

void QuHeap::qcond(quState *s,SymTable *gl) {
  QuCond qc=s;
  qconds++;
  qif(qc,gl);
}

int QuHeap::qif(QuCond qc,SymTable *gl,int has_else) {
  centry c;
  if(ignore) {
    int i=ncond();
    fmask.push(0);
    if(fmask.length()==oldfmask.length() && oldfmask==fmask) {
      if((int)cd.size()!=ncond())
        throw tError(errINT,"qucond stack mismatch");
      return 0;
    }
    if(ncond()<oldfmask.length() && oldfmask[i]) return 0;
    return 1;
  }
  c.qc=qc;
  c.ev=0;
  if(ncond()) {
    c.qc0=cd.back().qc0 & qc;
    c.dep=c.qc0.depmask();
    c.inv=cd.back().inv;
  } else {
    c.qc0=qc;
    c.dep=qc.depmask();
    c.inv=bitvec(nbits);
  }
  if(!zero(qc.depmask()&cmask()))
    throw tError(errRUN,"overlapping quantum conditions");
  bitvec v;
  if(qc.elem()==1 && zero(qc.first()&cmask()) && (!has_else || qc.first().nset()==1)) {
    v=qc.first();
  } else {
    c.tmp=qualloc(1);
    try {
      c.ev=new vector<quentry>;
      for(v=qc.first();v.length();v=qc.next()) {
        quentry q;
        q=makeentry(CNOTID,gl,0,0,c.tmp,tValue(new quMask(*bs,v),tQUCONST));
        callentry(q,gl);
        q=makeentry(CNOTID,gl,1,0,c.tmp,tValue(new quMask(*bs,v),tQUCONST));
        c.ev->push_back(q);
      }
    } catch(...) {
      qufree(c.tmp);
      throw;
    }
    v=c.tmp.qustate()->mapmask();
  }

  c.reg=new quMask(*bs,v);
  if(ncond()) v|=cd.back().reg0->mapmask();    
  c.reg0=new quMask(*bs,v);                     
  fmask.push(0);
  cd.push_back(c);
  return !c.qc0.isFalse();
}

int QuHeap::qelse(QuCond qc,SymTable *gl) {
  if(ncond()==0 || fmask.top()!=0)
    throw tError(errINT,"unexpected else-statement");
  if(fmask.length()==oldfmask.length() && oldfmask==fmask) {
    if((int)cd.size()!=ncond())
      throw tError(errINT,"qucond stack mismatch");
    ignore=0;
  }
  fmask.pop();
  if(ignore) {
    fmask.push(1);
    return 1;
  }
  centry c=cd.back();
  cd.pop_back();
  if(qc!=c.qc)
    throw tError(errINT,"if- and else-conditions don't match");
  c.qc=~qc;
  if(ncond()) {
    c.qc0=cd.back().qc0 & qc;
  } else {
    c.qc0=qc;
  }
  if(c.reg) {
    if(!c.ev) c.ev=new vector<quentry>;
    callentry(makeentry(NOTID,gl,0,0,*c.reg),gl);
    c.ev->push_back(makeentry(NOTID,gl,1,0,*c.reg));
  }
  c.inv^=c.reg->mapmask();
  fmask.push(1);
  cd.push_back(c);
  return !c.qc0.isFalse();
}

void QuHeap::qendif(SymTable *gl) {
  if(fmask.length()==0)
    throw tError(errINT,"unexpected endif");
  fmask.pop();
  centry c=cd.back();
  cd.pop_back();
  while(c.ev && !c.ev->empty()) {
    callentry(c.ev->back(),gl);
    c.ev->pop_back();
  }
  if(c.tmp.isQuExpr()) qufree(c.tmp);
  if(c.ev) delete c.ev;
  if(c.reg) delete c.reg;
  if(c.reg0) delete c.reg0;
}

int QuHeap::qendfork(SymTable *gl) {
  while(ncond() && fmask.top()) {
    qendif(gl);
  }
  oldfmask=fmask;
  ignore=(ncond()>qconds);
  if(ignore) 
    fmask=bitvec(qconds);
  else
    while(ncond()) qendif(gl);
  return ignore;
}


void QuHeap::add(sRoutDef *d,SymTable *s,int inv) {
  quentry q;
  if(ignore) return;
  q.d=d; q.s=s; q.i=inv;
  ql.push_back(q);
}

void QuHeap::apply(SymTable *gl,int inv) {
  int i;
  if(inv) {
    for(i=ql.size()-1;i>=0;i--) {
      ql[i].d->invoke(ql[i].s,gl,this,!ql[i].i);
    }
  } else {
    for(i=0;i<(int)ql.size();i++) {
      ql[i].d->invoke(ql[i].s,gl,this,ql[i].i);  
    }
  }
}      

void QuHeap::call(tId op,SymTable *gl,int inv,int cnd,tValue a,tValue b,tValue c) {
  callentry(makeentry(op,gl,inv,cnd,a,b,c),gl);
}

void QuHeap::call(sRoutDef *d,SymTable *loc,SymTable *gl,int inv,int cnd) {
  quentry q;
  q.d=d; q.s=loc; q.i=inv;
  if(q.d->isCondDef()) {
    if(cond() && cnd) 
      q.s->put(&CONDDEF,tValue(*cond(),tQUCONST));
    else 
      q.s->put(&CONDDEF,tValue(new quEmpty(*state()),tQUCONST));
  }
  callentry(q,gl);
}

void QuHeap::callentry(const quentry& q,SymTable *gl) {
  if(ignore) return;
  if(delayed) {
    ql.push_back(q);
  } else {
    try {
      q.d->invoke(q.s,gl,this,q.i);
    } catch (...) {
      delete q.s;
      throw;
    }
    delete q.s;
  }
}

QuHeap::quentry QuHeap::makeentry(tId op,SymTable *gl,int inv,int cnd,
                  tValue a,tValue b,tValue c) {
  quentry q;
  void *cc=0;
  sDef *dd;
  q.d=(sRoutDef*)gl->getDef(op);
  if(!q.d || !q.d->isQuDef())
    throw tError(errSYMBOL,"cannot find operator "+op);
  if(cond() && !q.d->isCondDef())
    throw tError(errSYMBOL,"operator "+op+" is not conditional");
  q.s=new SymTab();
  if(a.isDefined() && (dd=q.d->args()->first(cc))) q.s->put(dd,a);
  if(b.isDefined() && (dd=q.d->args()->next(cc))) q.s->put(dd,b);
  if(c.isDefined() && (dd=q.d->args()->next(cc))) q.s->put(dd,c);
  if(q.d->isCondDef()) {
    if(cond() && cnd) 
      q.s->put(&CONDDEF,tValue(*cond(),tQUCONST));
    else 
      q.s->put(&CONDDEF,tValue(new quEmpty(*state()),tQUCONST));
  }
  q.i=inv;
  return q;
}

string QuHeap::prtstr() {
  string ostr;
  int i;
  if(parent) ostr+=parent->prtstr();
  ostr+="{ ";
  for(i=0;i<(int)ql.size();i++) {
    if(ql[i].i) ostr+="!";
    ostr+=ql[i].d->id();
    ostr+=ql[i].s->prtstr();
    ostr+=" ";
  }
  ostr+="}";
  return ostr;
}

int QuHeap::load(ifstream& f) {
  int l=-1;
  term t;
  string s;
  char buf[1024];

//f.scan("QCL begin state %d qubits\n",&l);
  f.getline(buf,1024);
  sscanf(buf,"QCL begin state %d qubits\n",&l);
  if(l!=nbits) return 2;
  bs->opbegin();
  while(!f.eof()) {
    f.getline(buf,1024);
    s=buf;
    if(s=="QCL end state") break;
    t=string2term(s,l);
    if(t.nbits()==0) {
      return 1;
    }
    bs->opadd(t);
  }
  bs->opend();
  return 0;
}

int QuHeap::save(ofstream& f) {
  int i;
  string s;
  
  f << "QCL begin state " << bs->basebits() << " qubits\n";
  if(!f) return 1;
  bs->normalize();
  for(i=0;i<bs->baseterms();i++) {
    f << bs->baseterm(i) << "\n";
    if(!f) return 1;
  }
  f << "QCL end state\n";
  if(!f) return 1;
  return 0;
}
