/**********************************************************************

This file is part of the Quantum Computation Library (QCLIB).

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1996-1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/

#ifndef _TERMS_H
#define _TERMS_H 1

#pragma interface

#include <iostream>
#include <complex>

using namespace std;

#include "bitvec.h"

typedef class complex<double> complx;

#define NONE (-1)
#define EPSILON_PRINT (1E-5)

DEBUG( extern int nterms; )
DEBUG( extern int ntermlists; )
DEBUG( extern int nprobtrees; )

class term {
  bitvec _vect;
  complx _ampl;
public:
  term();
  term(int n);
  term(const bitvec& v,const complx& z=0);
  term(const term& t);
  ~term();
  term& operator = (const term& t);
  void set(const bitvec& v,const complx& z);
  void setvect(const bitvec& v);
  void setampl(const complx& z);
  inline const bitvec& vect() const;
  inline const complx& ampl() const;
  int nbits() const;
};

class termlist {
  int _nterms;
  int _nbits;
  int listlen;
  int hashlen;
  term *list;
  term **hash;
  int hashmask;

  void newlist();
  void dellist();
  int hashfunct1(const bitvec& v) const;
  int hashfunct2(const bitvec& v) const;
  term *search(const bitvec& v) const;
public:
  termlist(int bits,int len=256);
  termlist(const termlist& l);
  ~termlist();
  termlist& operator = (const termlist& l);
  void add(const bitvec& v,const complx& z);
  
  void add(const term& t);
  void clear();
  int nterms() const;
  int nbits() const;
  const term& operator [] (int i) const;
  complx ampl(int i) const;
  complx ampl(const bitvec& v) const;
};


/* inline members */

// class term

inline void term::setvect(const bitvec& v) { _vect=v; }

inline void term::setampl(const complx& z) { _ampl=z; }

inline const bitvec& term::vect() const { return _vect; }

inline int term::nbits() const { return _vect.length(); }

inline const complx& term::ampl() const { return _ampl; }

inline term::term() { DEBUG( nterms++; ) }

inline term::term(int n) {
  _vect.setlen(n);
  DEBUG( nterms++; )
}

inline term::term(const bitvec& v,const complx& z) {
  _vect=v;
  _ampl=z;
  DEBUG( nterms++; )
}

inline term::term(const term& t) {
  _vect=t.vect();
  _ampl=t.ampl();
  DEBUG( nterms++; )
}

inline term::~term() { DEBUG( nterms--; ) }

inline term& term::operator = (const term& t) {
  _vect=t.vect();
  _ampl=t.ampl();
  return *this;
}

inline void term::set(const bitvec& v,const complx& z) {
  _vect=v;
  _ampl=z;
}

// class termlist: private members

inline void termlist::newlist() {
  list=new term[listlen];
  hash=new term*[hashlen];
}

inline void termlist::dellist() {
  qc_delarray(list); list=0;
  qc_delarray(hash); hash=0;
}

inline int termlist::hashfunct1(const bitvec& v) const {
  return v.hashfunct() & hashmask;
}

inline int termlist::hashfunct2(const bitvec& v) const {
  int f;

  f=v.hashfunct(); f+=(f>>3);
  return (f & hashmask) | 1;
}

inline term *termlist::search(const bitvec& v) const {
  int h;
  term *pt;

  h=hashfunct1(v);
  while(1) {
    pt=hash[h];
    if(!pt || pt->vect()==v) return pt;
    h+=hashfunct2(v);
  };
}

// class termlist: public members

inline void termlist::add(const term& t) {
  add(t.vect(),t.ampl());
}

inline void termlist::clear() {
  int i;

  _nterms=0;
  for(i=0;i<hashlen;i++) hash[i]=0;
}

inline int termlist::nterms() const { return _nterms; }

inline int termlist::nbits() const { return _nbits; }

inline const term& termlist::operator [] (int i) const {
  QC_CHECK(i<_nterms);
  return list[i];
}

inline complx termlist::ampl(int i) const {
  QC_CHECK(i<_nterms);
  return list[i].ampl();
}

inline complx termlist::ampl(const bitvec& v) const {
  term *pt;

  pt=search(v);
  return pt ? pt->ampl() : complx(0);
}

/* other functions */

int duallog(int k);

ostream& operator << (ostream& s,const term& t);
istream& operator >> (istream& s,term& t);

#endif

