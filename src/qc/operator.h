/**********************************************************************

This file is part of the Quantum Computation Library (QCLIB).

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1996-1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/

#ifndef _OPERATOR_H
#define _OPERATOR_H 1

#pragma interface

#include "qustates.h"

struct terminfo {
  quState *pqs;		// the quatum register operated on
  bitvec frame;		// vector of not affacted qubits
  term mapterm;		// register term
};

#ifndef PI
#define PI M_PI
#endif

DEBUG( extern int noperators; )

class opOperator {
  int _bits;
public:
  opOperator(int n) { _bits=n; DEBUG( noperators++; ) };
  virtual ~opOperator();
  int bits() const { return _bits; };
  quState& operator () (quState& qs) const {
    QC_CHECK(_bits==qs.mapbits());
    apply(qs);
    return qs;
  };
  virtual void apply(quState& qs) const=0;
  virtual opOperator *newclone() const=0;
  
  friend class opVar;
};

class opElementary : public opOperator {
public:
  opElementary(int n) : opOperator(n) { };
  virtual void apply(quState& qs) const;
  virtual void addterms(const terminfo& ti) const=0;
};

class opMatrix : public opElementary {
  int len;
protected:
  term **matrix;
  opMatrix(int bits);
public:
  opMatrix(int n,term **m);
  virtual ~opMatrix();
  virtual opOperator *newclone() const;
  virtual void addterms(const terminfo& ti) const;
};

class opBit : public opMatrix {
public:
  opBit(complx u00,complx u01,complx u10,complx u11,double norm=1.0);
};

class opU2 : public opMatrix {
public:
  opU2(double theta,double delta=0,double sigma=0,double tau=0);
};

class opIdentity : public opElementary {
public:
  opIdentity(int n) : opElementary(n) { };
  virtual opOperator *newclone() const;
  virtual void apply(quState& qs) const;
  virtual void addterms(const terminfo& ti) const;
};

class opSwap : public opElementary {
  int offs1,offs2;
  int len;
public:
  opSwap(int n,int m,int o1,int o2) : opElementary(n) {
    QC_CHECK(o1+m<=n && o2+m<=n);
    QC_CHECK(o1+m<=o2 || o2+m<=o1);
    len=m; offs1=o1; offs2=o2;
  };
  virtual opOperator *newclone() const;
  virtual void addterms(const terminfo& ti) const;
};

class opPermutation : public opElementary {
  int len;
protected:
  term *perm;
  opPermutation(int bits);
public:
  opPermutation(int n,term *p);
  virtual ~opPermutation();
  virtual opOperator *newclone() const;
  virtual void addterms(const terminfo& ti) const;
};

class opFunction : public opElementary {
  int _arg;
  int _fct;
public:
  opFunction(int arg,int fct) : opElementary(arg+fct) {
    _arg=arg; _fct=fct;
  };
  int arg() const { return _arg; };
  int fct() const { return _fct; };
  virtual void addterms(const terminfo& ti) const;
  virtual term funct(const bitvec& v) const=0;
};

class opEXPN : public opFunction {
  word _x;
  word _num;
public:
  opEXPN(int arg,int fct,word x,word num) : opFunction(arg,fct) {
    QC_CHECK(arg<=BPW && (num<(1ul<<(BPW/2))) && x<num);
    _x=x; _num=num;
  };
  virtual term funct(const bitvec& v) const;
  virtual opOperator *newclone() const;
};

class opGate : public opElementary {
public:
  opGate(int n) : opElementary(n) { };
  virtual void addterms(const terminfo& ti) const;
  virtual term funct(const bitvec& v) const=0;
};

class opCNot : public opOperator {
  int out;
  int enable;
public:
  opCNot(int o,int e) : opOperator(o+e) { out=o; enable=e; }
  virtual void apply(quState& qs) const;
  virtual opOperator *newclone() const;
};

class opCPhase : public opOperator {
  complx phase;
  opCPhase(int n,complx p) : opOperator(n) { phase=p; }
public:
  opCPhase(int n,double phi,int i=0) : opOperator(n) { 
    phase=exp(complx(0,i?-phi:phi)); }
  virtual void apply(quState& qs) const;
  virtual opOperator *newclone() const;
};

class opCk : public opGate {
  int out;
  int _k;
protected:
  int *in;
  opCk(int n,int k,int o);
public:
  opCk(int n,int k,int o,int *i);
  virtual ~opCk();
  virtual term funct(const bitvec& v) const;
  virtual opOperator *newclone() const;
};

class opC0 : public opCk {
public:
  opC0(int n,int o) : opCk(n,0,o,0) { };
};

class opNot : public opC0 {
public:
  opNot() : opC0(1,0) { };
};

class opC1 : public opCk {
public:
  opC1(int n,int o,int i) : opCk(n,1,o,&i) { };
};

class opXor : public opC1 {
public:
  opXor() : opC1(2,0,1) { };
};

class opC2 : public opCk {
public:
  opC2(int n,int o,int i1,int i2) : opCk(n,2,o) {
    in[0]=i1; in[1]=i2;
  };
};

class opToffoli : public opC2 {
public:
  opToffoli() : opC2(3,0,1,2) { };
};

class opCondPhase : public opGate {
  double _phi;
  int _k;
protected:
  int *in;
public:
  opCondPhase(int n,int k,double phi);
  opCondPhase(int n,int k,int *i,double phi);
  virtual ~opCondPhase();
  virtual term funct(const bitvec& v) const;
  virtual opOperator *newclone() const;
};

class opX : public opCondPhase {
public:
  opX(int n,int i1,int i2,int pow) 
  : opCondPhase(n,2,2*PI/(double)(1<<pow)) {
    in[0]=i1; in[1]=i2;
  };
};

class opComposition : public opOperator {
  opOperator *inner,*outer;
public:
  opComposition(const opOperator& in,const opOperator& out) 
  : opOperator(in.bits()) {
    QC_CHECK(in.bits()==out.bits());
    inner=in.newclone();
    outer=out.newclone();
  };
  opComposition(opOperator *in,opOperator *out) 
  : opOperator(in->bits()) {
    QC_CHECK(in->bits()==out->bits());
    inner=in;
    outer=out;
  };
  virtual ~opComposition();
  virtual void apply(quState& qs) const;
  virtual opOperator *newclone() const;
};
  
class opEmbedded : public opOperator {
  int _offs;
  opOperator *_op;
public:
  opEmbedded(int n,int offs,const opOperator& op)
  : opOperator(n) {
    QC_CHECK(op.bits()+offs<=n);
    _offs=offs;
    _op=op.newclone();
  };
  opEmbedded(int n,int offs,opOperator *op)
  : opOperator(n) {
    QC_CHECK(op->bits()+offs<=n);
    _offs=offs;
    _op=op;
  };
  virtual ~opEmbedded();
  virtual void apply(quState& qs) const;
  virtual opOperator *newclone() const;
};

class opVar : public opOperator {
  opOperator *_op;
public:
  opVar() : opOperator(0) {
    _op=0;
  };
  opVar(const opVar& op) : opOperator(op.bits()) {
    _op=op.newclone();
  };
  opVar(const opOperator& op) : opOperator(op.bits()) {
    _op=op.newclone();
  };
  const opVar& operator = (const opVar& op) {
    if(_op) delete _op;
    _op=op.newclone();
    _bits=op.bits();
    return op;
  };
  const opOperator& operator = (const opOperator& op) {
    if(_op) delete _op;
    _op=op.newclone();
    _bits=op.bits();
    return op;
  };
  const opOperator& operator *= (const opOperator& op) {
    if(_op) {
      QC_CHECK(bits()==op.bits());
      _op=new opComposition(_op,op.newclone());
    } else {
      _op=op.newclone();
      _bits=op.bits();
    };
    return *_op;
  };
  virtual ~opVar();
  virtual void apply(quState& qs) const;
  virtual opOperator *newclone() const;
};

/* functions */

inline opComposition operator * (const opOperator& out,const opOperator& in) {
  return opComposition(in,out);
}

inline opComposition operator / (const opOperator& low,const opOperator& high) {
  int n=low.bits()+high.bits();
  return opComposition(new opEmbedded(n,0,low),
                       new opEmbedded(n,low.bits(),high));
}

#endif

