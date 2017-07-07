/**********************************************************************

This file is part of the Quantum Computation Language QCL.

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/


#ifndef COND_H
#define COND_H 1

#pragma interface

#include "qc.h"

#include <set>
#include <string>

#define QCFALSE(b) QuCond(b)
#define QCTRUE(b) (~QuCond(b))

class QuCond {
  int _bits;
  set<bitvec> cond;
  typedef set<bitvec>::iterator iter;
  iter cursor;
  void add(const bitvec& v) {
    iter p;
    p=cond.find(v);
    if(p==cond.end()) 
      cond.insert(v);
    else
      cond.erase(v);
  }
public:
  QuCond() { _bits=0; }
  QuCond(int n) { _bits=n; }
  QuCond(const quState *q) { 
    _bits=q->basebits();
    cond.insert(q->unmap(~bitvec(q->mapbits())));
  }
  QuCond(const bitvec& v) {
    _bits=v.length();
    cond.insert(v);
  }
  int bits() const { return _bits; }
  int elem() const { return cond.size(); }
  bitvec clause(int n) const {
    iter i=cond.begin();
    while(i!=cond.end() && n--) i++;
    if(i!=cond.end()) return *i;
    return bitvec(bits());
  }
  int isTrue() const { return elem()==1 && zero(*cond.begin()); }
  int isFalse () const { return elem()==0; }
  QuCond operator ~ () const {
    QuCond r(*this);
    r.add(bitvec(bits()));
    return r;
  }
  QuCond operator ^ (const QuCond& c) const {
    if(isFalse()) return c;
    QuCond r(c);
    iter i;
    for(i=cond.begin();i!=cond.end();i++) r.add(*i);
    return r;
  }
  QuCond operator & (const QuCond& c) const {
    if(isTrue()) return c;
    if(c.isTrue()) return *this;
    QuCond r(bits());
    iter i,j;
    for(i=cond.begin();i!=cond.end();i++)
      for(j=c.cond.begin();j!=c.cond.end();j++)
        r.add(*i | *j);
    return r;
  }
  QuCond operator | (const QuCond& c) const {
    if(isFalse()) return c;
    if(c.isFalse()) return *this;
    return c ^ (*this) ^ (c & (*this));
  }
  bitvec depmask() const {
    iter i;
    bitvec m(bits());
    for(i=cond.begin();i!=cond.end();i++) m|=(*i);
    return m;
  }
  bitvec first() {
    cursor=cond.begin();
    return cursor==cond.end() ? bitvec(0) : *cursor;
  }
  bitvec next() {
    if(cursor!=cond.end()) cursor++;
    return cursor==cond.end() ? bitvec(0) : *cursor;
  }
  string str() const;
};

inline int operator == (const QuCond& a,const QuCond& b) {
  if(a.elem()!=b.elem() || a.bits()!=b.bits()) return 0;
  return (a^b).isFalse();
}

inline int operator != (const QuCond& a,const QuCond& b) {
  if(a.elem()!=b.elem() || a.bits()!=b.bits()) return 1;
  return !(a^b).isFalse();
}

inline int operator < (const QuCond& a,const QuCond& b) {
  if(a.bits()!=b.bits()) return 0;
  if(a.elem()<b.elem()) return 1;
  return a.depmask().nset()<b.depmask().nset();
}

inline int operator > (const QuCond& a,const QuCond& b) {
  if(a.bits()!=b.bits()) return 0;
  if(a.elem()>b.elem()) return 1;
  return a.depmask().nset()>b.depmask().nset();
}

QuCond regcomp(const quState *q,const quState *p);
QuCond regcomp(const quState *q,int n);

#endif
