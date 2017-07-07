/**********************************************************************

This file is part of the Quantum Computation Library (QCLIB).

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1996-1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/

#ifndef _QUSTATES_H
#define _QUSTATES_H 1

#pragma interface

#include <stdlib.h>
#include <iostream>
#include <map>

#include "bitvec.h"
#include "terms.h"

#define EPSILON (1E-10)

long qc_lrand();
double qc_drand();
void qc_srand(long seed);


DEBUG( extern int nstates; )

typedef map<bitvec,complx> state_map;
typedef map<bitvec,double> spectrum_map;
typedef state_map::const_iterator state_iter;
typedef spectrum_map::const_iterator spectrum_iter;
typedef state_map::const_reverse_iterator state_riter;
typedef spectrum_map::const_reverse_iterator spectrum_riter;

class quBaseState;

typedef const quBaseState* baseid;

class quState {
  int _mapbits;
public:
  quState(int bits);
  virtual ~quState();
  
  int mapbits() const;
  virtual bitvec mapmask() const;
  bitvec measure();
  void opterm(const term& t);
  void printvect(ostream& s,const bitvec& v) const;
  quState* newclone();

  bitvec select() const;
  void reduce(const bitvec& v);
  void normalize(double epsilon=EPSILON);

  virtual void reset(const bitvec& v=bitvec(0))=0;
  virtual baseid base() const=0;
  virtual int basebits() const=0;
  virtual quState* newsubstring(int bits,int offs)=0;
  virtual int isbasestate() const=0;
  virtual double prob(const bitvec& v) const=0;
  virtual int baseterms() const=0;
  virtual const term& baseterm(int i) const=0;
  virtual void opbegin()=0;
  virtual void opadd(const bitvec& v,const complx& z)=0;
  void opadd(const term& t) { opadd(t.vect(),t.ampl()); };
  virtual void opend()=0;
  virtual bitvec map(const bitvec& v) const=0;
  virtual bitvec unmap(const bitvec& v) const=0;
  virtual int mapindex(int i) const=0;
  int operator [] (int i) const { return mapindex(i); };
  virtual void _printvect(ostream& s,const bitvec& v) const;
  state_map *new_state_map(double epsilon=EPSILON) const;
  spectrum_map *new_spectrum_map(double epsilon=EPSILON) const;

  friend class quVar;
};

class quBaseState : public quState {
  termlist *pterms;
  termlist *ptermbuf;
public:
  quBaseState(int bits,int buflen=256);
  virtual ~quBaseState();
  
  virtual void reset(const bitvec& v=bitvec(0));
  virtual baseid base() const;
  virtual int basebits() const;
  virtual quState* newsubstring(int bits,int offs);
  virtual int isbasestate() const;
  virtual bitvec mapmask() const;
  virtual double prob(const bitvec& v) const;
  virtual int baseterms() const;
  virtual const term& baseterm(int i) const;
  virtual void opbegin();
  virtual void opadd(const bitvec& v,const complx& z);
  virtual void opend();
  virtual bitvec map(const bitvec& v) const;
  virtual bitvec unmap(const bitvec& v) const;
  virtual int mapindex(int i) const;
};

class quSubState : public quState {
protected:
  quState *pbase;
public:
  quSubState(int bits);
  virtual ~quSubState();
  
  virtual void reset(const bitvec& v=bitvec(0));
  virtual baseid base() const;
  virtual int basebits() const;
  virtual int isbasestate() const;
  virtual double prob(const bitvec& v) const;
  virtual int baseterms() const;
  virtual const term& baseterm(int i) const;
  virtual void opbegin();
  virtual void opadd(const bitvec& v,const complx& z);
  virtual void opend();
};

class quEmpty : public quSubState {
public:
  quEmpty(quState& qs);
  virtual double prob(const bitvec& v) const;
  virtual void opbegin();
  virtual void opadd(const bitvec& v,const complx& z);
  virtual void opend();
  virtual quState* newsubstring(int bits,int offs);
  virtual bitvec mapmask() const;
  virtual bitvec map(const bitvec& v) const;
  virtual bitvec unmap(const bitvec& v) const;
  virtual int mapindex(int i) const;
};

class quVar : public quSubState {
public:
  quVar();
  quVar(quVar& qs);
  quVar(quState& qs);
  quVar(quState* qs);
  quVar& operator = (quVar& qs);
  quState& operator = (quState& qs);

  virtual quState* newsubstring(int bits,int offs);
  virtual bitvec mapmask() const;
  virtual bitvec map(const bitvec& v) const;
  virtual bitvec unmap(const bitvec& v) const;
  virtual int mapindex(int i) const;
};

class quMask : public quSubState {
  bitvec _mask;
public:
  quMask(quState& qs,bitvec m);

  virtual quState* newsubstring(int bits,int offs);
  virtual bitvec mapmask() const;
  virtual bitvec map(const bitvec& v) const;
  virtual bitvec unmap(const bitvec& v) const;
  virtual int mapindex(int i) const;
};

class quSwap : public quSubState {
public:
  quSwap(quState& qs);
  quSwap(quState* qs);

  virtual quState* newsubstring(int bits,int offs);
  virtual bitvec mapmask() const;
  virtual bitvec map(const bitvec& v) const;
  virtual bitvec unmap(const bitvec& v) const;
  virtual int mapindex(int i) const;
};

class quCombState : public quSubState {
  quState *ptail;
  quCombState(int bits);
  int delflag;
public:
  quCombState(quState& head,quState& tail);
  quCombState(quState* head,quState* tail,int d=0); 
  virtual ~quCombState();

  virtual quState* newsubstring(int bits,int offs);
  virtual bitvec mapmask() const;
  virtual bitvec map(const bitvec& v) const;
  virtual bitvec unmap(const bitvec& v) const;
  virtual int mapindex(int i) const;
  virtual void _printvect(ostream& s,const bitvec& v) const;
};

class quSubString : public quSubState {
  int _mapoffs;
public:
  quSubString(int bits,int offs,quState& base);

  int mapoffs() const;

  virtual quState* newsubstring(int bits,int offs);
  virtual bitvec map(const bitvec& v) const;
  virtual bitvec unmap(const bitvec& v) const;
  virtual int mapindex(int i) const;
};

class quBit : public quSubString {
public:
  quBit(int offs,quState& base);
  void set(int v);
  int get();
};

class quWord : public quSubString {
public:
  quWord(int bits,int offs,quState& base);
  void set(word v);
  word get();
  
  virtual quState* newsubstring(int bits,int offs);
  virtual void _printvect(ostream& s,const bitvec& v) const;
};

/* inline members */

/* quState */

inline quState::quState(int bits) {
  _mapbits=bits;
  DEBUG( nstates++; )
}

inline int quState::mapbits() const { return _mapbits; }

inline bitvec quState::measure() {
  bitvec v;

  v=select();
  reduce(v);
  return v;
}

inline void quState::opterm(const term& t) { opadd(t.vect(),t.ampl()); }

inline void quState::printvect(ostream& s,const bitvec& v) const {
  s << '|';
  _printvect(s,v);
  s << '>';
}

inline quState *quState::newclone() {
  return newsubstring(mapbits(),0);
}

/* quBaseState */

inline quBaseState::quBaseState(int bits,int buflen)
  : quState(bits) {
  pterms=new termlist(bits,buflen);
  ptermbuf=new termlist(bits,buflen);
  reset();
}

/* quSubState */

inline quSubState::quSubState(int bits)
  : quState(bits) {
  pbase=0;
}

/* quEmpty */

inline quEmpty::quEmpty(quState& qs) : quSubState(0) {
  pbase=(quState*)qs.base();
}

/* quMask */

inline quMask::quMask(quState& qs,bitvec m) : quSubState(m.nset()) {
  QC_CHECK(m.length()==qs.mapbits());
  _mask=m;
  pbase=qs.newclone();
}

/* quSwap */

inline quSwap::quSwap(quState& qs) : quSubState(qs.mapbits()) {
  pbase=qs.newclone();
}

inline quSwap::quSwap(quState* qs) : quSubState(qs->mapbits()) {
  pbase=qs;
}

/* quVar */

inline quVar::quVar() : quSubState(0) {
  pbase=0;
}

inline quVar::quVar(quVar& qs) : quSubState(qs.mapbits()) {
  pbase=qs.newclone();
}

inline quVar::quVar(quState& qs) : quSubState(qs.mapbits()) {
  pbase=qs.newclone();
}

inline quVar::quVar(quState* qs) : quSubState(qs->mapbits()) {
  pbase=qs;
}


inline quVar& quVar::operator = (quVar& qs) {
  if(pbase && !pbase->isbasestate()) qc_delete(pbase);
  pbase=qs.newclone();
  _mapbits=qs.mapbits();
  return qs;
}

inline quState& quVar::operator = (quState& qs) {
  if(pbase && !pbase->isbasestate()) qc_delete(pbase);
  pbase=qs.newclone();
  _mapbits=qs.mapbits();
  return qs;
}

/* quCombState */

inline quCombState::quCombState(quState& head,quState& tail) 
  : quSubState(head.mapbits()+tail.mapbits()) {
  QC_CHECK(head.base()==tail.base());
  QC_CHECK(zero(head.mapmask() & tail.mapmask()));

  delflag=1;
  pbase=head.newclone();
  ptail=tail.newclone();
}

inline quCombState::quCombState(quState* head,quState* tail,int d) 
  : quSubState(head->mapbits()+tail->mapbits()) {
  QC_CHECK(head->base()==tail->base());
  QC_CHECK(zero(head->mapmask() & tail->mapmask()));

  delflag=d;
  pbase=head;
  ptail=tail;
}

inline quCombState::quCombState(int bits) 
  : quSubState(bits) {
  ptail=0;
}

/* quSubString */

inline quSubString::quSubString(int bits,int offs,quState& base)
  : quSubState(bits) {
  _mapoffs=offs;
  pbase=base.newclone();
}

inline int quSubString::mapoffs() const { return _mapoffs; }

/* quBit */

inline quBit::quBit(int offs,quState& base)
  : quSubString(1,offs,base) {}

inline void quBit::set(int v) {
  reduce(bitvec(1,v!=0));
}

inline int quBit::get() {
  return !measure().testzero();
}

/* quWord */

inline quWord::quWord(int bits,int offs,quState& base)
  : quSubString(bits,offs,base) {
  QC_CHECK(bits<=BPW);
}

inline void quWord::set(word v) {
  reduce(bitvec(mapbits(),v));
}

/* other functions */

inline quCombState operator / (quState& head,quState& tail) {
  return quCombState(head,tail);
}


inline word quWord::get() {
  return measure().getword(0,mapbits());
}

#endif

