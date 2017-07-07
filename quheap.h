/**********************************************************************

This file is part of the Quantum Computation Language QCL.

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/


#ifndef QUHEAP_H
#define QUHEAP_H

#pragma interface

#include "operator.h"
#include "types.h"
#include "syntax.h"

#include <vector>
#include <stack>
#include <fstream>

extern int isStateModified;

term string2term(const string& s,int l);
string term2string(const term& t,int binary=0);

class QuHeap {
  struct quentry {
    sRoutDef *d;
    SymTable *s;
    int i;
  };
  struct centry {
    QuCond qc;
    QuCond qc0;
    tValue tmp;
    quState *reg;
    quState *reg0;
    bitvec dep;
    bitvec inv;
    vector<quentry> *ev;
  };
  int nbits;
  bitvec mbits;
  int nfree;
  bitvec mfree;
  int ndirty;
  bitvec mdirty;
  quState *bs;
  QuHeap *parent;
  int delbs;
  int delayed;
  
  int ignore;
  bitvec fmask;
  bitvec oldfmask;
  int qconds;
  vector<centry> cd;
  vector<quentry> ql;
  vector<tValue> regs;
  void init();
  quentry makeentry(tId op,SymTable *gl,int inv=0,int cnd=1,
            tValue a=tUNDEF,tValue b=tUNDEF,tValue c=tUNDEF);
  void callentry(const quentry& q,SymTable *gl);
public:
  int ncond() const { return fmask.length(); }
  quState *cond() const { 
    return ncond() ? cd.back().reg0 : 0; 
  }
  bitvec cmask() const { 
    return fmask.length() ? cd.back().dep : bitvec(nbits); 
  }
  bitvec imask() const { 
    return fmask.length() ? cd.back().inv : bitvec(nbits); 
  }
  
  QuHeap(int n,int d=0);
  QuHeap(quState *s,int d=0);
  QuHeap(QuHeap *h,int d=0);
  ~QuHeap();
  tValue qualloc(int n,BaseType t=tQUREG); 
  void qufree(tValue var);
  tValue measure(tValue);
  void reset();
  
  void addReg(quState *r) { regs.push_back(tValue(*r)); };
  int Regs() const { return regs.size(); }
  const quState* Reg(int i) const { return regs[i].qustate(); };

  void qcond(quState *s,SymTable *gl);
  int qif(QuCond qc,SymTable *gl,int has_else=0);
  int qelse(QuCond qc,SymTable *gl);
  void qendif(SymTable *gl);
  int qendfork(SymTable *gl);
  
  void add(sRoutDef *d,SymTable *s,int inv);
  void apply(SymTable *gl,int inv);
  
  void call(tId op,SymTable *gl,int inv=0,int cnd=1,
            tValue a=tUNDEF,tValue b=tUNDEF,tValue c=tUNDEF);
  void call(sRoutDef *d,SymTable *loc,SymTable *gl,int inv=0,int cnd=1);
  string prtstr();
  quState *state() const { return bs; }
  int nBits() const { return nbits; }
  bitvec mBits() const { return mbits; }
  int nFree() const { return nfree; }
  bitvec mFree() const { return mfree; }
  int nDirty() const { return ndirty; }
  bitvec mDirty() const { return mdirty; }
  int nTerms() const { return bs ? bs->baseterms() : 0; }
  
  int load(ifstream& f);
  int save(ofstream& f);

  // workaround for broken template lib.
  // QuHeap& operator=(QuHeap const &) { assert(0); return *this; };
};

#endif
