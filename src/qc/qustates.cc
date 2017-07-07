/**********************************************************************

This file is part of the Quantum Computation Library.

Copyright by Bernhard Oemer 1996, all rights reserved

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

The use and distribution in any electronic or non-electronic way
of this or any other file of this package is forbidden without 
prior written or PGP-signed permission from the author.

E-mail: oemer@tph.tuwien.ac.at

PGP fingerprint:     51 BB 4A CE CB 15 32 DE  A7 64 BC F4 05 F1 35 A8
PGP public key:      http://tph.tuwien.ac.at/~oemer/pubkey.txt

************************************************************************/

#pragma implementation "qustates.h"

#include "qustates.h"

DEBUG( int nstates=0; )

#ifdef QC_USE_RAND48
long qc_lrand() { return lrand48(); }
double qc_drand() { return drand48(); }
void qc_srand(long seed) { srand48(seed); }
#else
#include <limits.h>
long qc_lrand() { return random(); }
double qc_drand() { return random()/(1.0+(double)INT_MAX); }
void qc_srand(long seed) { srandom(seed); }
#endif

/* quState */

quState::~quState() { 
  DEBUG( nstates--; ) 
}

bitvec quState::select() const {
  int i,n;
  double p,q;

  n=baseterms();
  i=qc_lrand()%n;
  p=qc_drand();
  q=0.0;

  while(q<p) {
    i++; if(i>=n) i=0;
    q+=norm(baseterm(i).ampl());
  };
  return map(baseterm(i).vect());
}

void quState::reduce(const bitvec& v) {
  int i;

  opbegin();
  for(i=0;i<baseterms();i++) 
    if(v==map(baseterm(i).vect())) opterm(baseterm(i));
  opend();
  normalize();
}

void quState::normalize(double epsilon) {
  term t;
  int i,n;
  double p,q;

  p=0.0;
  opbegin();
  n=baseterms();
  for(i=0;i<n;i++) {
    q=norm(baseterm(i).ampl());
    if(q>=epsilon) { 
      opterm(baseterm(i));
      p+=q;
    };
  };
  opend();
  QC_CHECK(p>0);
  p=1/sqrt(p);
  opbegin();
  n=baseterms();
  for(i=0;i<n;i++) {
    t=baseterm(i);
    t.setampl(t.ampl()*p);
    opterm(t);
  };
  opend();
}

bitvec quState::mapmask() const {
  bitvec v(mapbits());
  return unmap(~v);
}


void quState::_printvect(ostream& s,const bitvec& v) const {
  QC_CHECK(v.length()==mapbits());
  s << v;
}

state_map *quState::new_state_map(double epsilon) const {
  state_map *pm=new state_map();
  term t;
  int i;
  double p;
  for(i=0;i<baseterms();i++) {
    t=baseterm(i);
    p=norm(t.ampl());
    if(p>=epsilon) (*pm)[t.vect()]=t.ampl();
  }
  return pm;
}

spectrum_map *quState::new_spectrum_map(double epsilon) const {
  spectrum_map *pm=new spectrum_map();
  term t;
  int i;
  double p;
  for(i=0;i<baseterms();i++) {
    t=baseterm(i);
    p=norm(t.ampl());
    bitvec v=map(t.vect());
    if(pm->find(v)==pm->end()) 
      (*pm)[v]=p;
    else
      (*pm)[v]+=p;
  }
  if(epsilon) {
    for(spectrum_map::iterator it=pm->begin();it!=pm->end();) {
      spectrum_map::iterator it0=it++;
      if(it0->second<epsilon) pm->erase(it0);
    }
  }
  return pm;
}

/* quBaseState */

quBaseState::~quBaseState() {
  qc_delete(pterms);
  qc_delete(ptermbuf);
}

void quBaseState::reset(const bitvec& v) {
  opbegin();
  if(v.length()) opadd(v,1.0); else opadd(bitvec(basebits()),1.0);
  opend();
}

baseid quBaseState::base() const {
  return (baseid) this;
}

int quBaseState::basebits() const {
  return mapbits();
}

quState* quBaseState::newsubstring(int bits,int offs) {
  if(mapbits()==bits && offs==0) return this;
  QC_CHECK(bits+offs<=mapbits());
  return new quSubString(bits,offs,*this);
}

int quBaseState::isbasestate() const {
  return 1;
}

bitvec quBaseState::mapmask() const {
  return ~ bitvec(mapbits());
}

double quBaseState::prob(const bitvec& v) const {
  return norm(pterms->ampl(v));
}

int quBaseState::baseterms() const {
  return pterms->nterms();
}

const term& quBaseState::baseterm(int i) const {
  return (*pterms)[i];
}

void quBaseState::opbegin() {
  ptermbuf->clear();
}

void quBaseState::opadd(const bitvec& v,const complx& z) {
  ptermbuf->add(v,z);
}

void quBaseState::opend() {
  termlist *pl;
  pl=pterms; pterms=ptermbuf; ptermbuf=pl;
}

bitvec quBaseState::map(const bitvec& v) const {
  return v;
}

bitvec quBaseState::unmap(const bitvec& v) const {
  return v;
}

int quBaseState::mapindex(int i) const {
  return i;
}

/* quSubState */

quSubState::~quSubState() {
  if(pbase && !pbase->isbasestate()) qc_delete(pbase);
}

void quSubState::reset(const bitvec& v) {
  term t;
  int i,n;
  bitvec w,v0,v1;
  
  if(v.length()) w=v; else w=bitvec(basebits());
  v0=~mapmask();
  v1=unmap(w);
  opbegin();
  n=baseterms();
  for(i=0;i<n;i++) {
    t=baseterm(i);
    opadd((t.vect() & v0) | v1,t.ampl());
  };
  opend();
}

baseid quSubState::base() const {
  return pbase->base();
} 

int quSubState::basebits() const {
  return pbase->basebits();
}

int quSubState::isbasestate() const {
  return 0;
}

double quSubState::prob(const bitvec& v) const {
  int i;
  double p=0.0;
  term t;

  for(i=0;i<baseterms();i++) {
    t=pbase->baseterm(i);
    if(map(t.vect())==v) p+=norm(t.ampl());
  };
  return p;
}

int quSubState::baseterms() const {
  return pbase->baseterms();
}

const term& quSubState::baseterm(int i) const {
  return pbase->baseterm(i);
}

void quSubState::opbegin() {
  pbase->opbegin();
}

void quSubState::opadd(const bitvec& v,const complx& z) {
  pbase->opadd(v,z);
}

void quSubState::opend() {
  pbase->opend();
}

/* quEmpty */

double quEmpty::prob(const bitvec& v) const { return 0; }
void quEmpty::opbegin() { }
void quEmpty::opadd(const bitvec& v,const complx& z) { }
void quEmpty::opend() { }

quState* quEmpty::newsubstring(int bits,int offs) {
  QC_CHECK(pbase && bits==0 && offs==0);
  return new quEmpty(*pbase);
}

bitvec quEmpty::mapmask() const {
  return bitvec(basebits());
}

bitvec quEmpty::map(const bitvec& v) const {
  return bitvec(0);
}

bitvec quEmpty::unmap(const bitvec& v) const {
  return bitvec(basebits());
}

int quEmpty::mapindex(int i) const {
  QC_CHECK(0);
  return -1;
}

/* quMask */

quState* quMask::newsubstring(int bits,int offs) {
  QC_CHECK(bits+offs<=mapbits());
  int o,i=-1;                               
  if(bits==mapbits() && offs==0)
    return new quMask(*pbase,_mask);
  for(o=0;o<offs;o++) while(!_mask[++i]);  
  if(bits==1) {
    while(!_mask[++i]);
    return pbase->newsubstring(1,i);
  } else {
    bitvec m(pbase->mapbits());
    for(o=0;o<bits;o++) {
      while(!_mask[++i]);
      m.setbit(i);
    }
    return new quMask(*pbase,m);
  }
}

bitvec quMask::mapmask() const {
  return pbase->unmap(_mask);
}

bitvec quMask::map(const bitvec& v) const {
  bitvec m(mapbits());
  bitvec u=pbase->map(v);
  int i,j=-1;
  for(i=0;i<mapbits();i++) {
    while(!_mask[++j]);
    if(u[j]) m.setbit(i);
  }
  return m;
}

bitvec quMask::unmap(const bitvec& v) const {
  bitvec m(pbase->mapbits());
  int i,j=-1;
  for(i=0;i<mapbits();i++) {
    while(!_mask[++j]); 
    if(v[i]) m.setbit(j);
  }
  return pbase->unmap(m);
}

int quMask::mapindex(int i) const {
  int j=-1;                               
  while(i-->=0) while(!_mask[++j]);
  return j;
}

/* quSwap */

quState* quSwap::newsubstring(int bits,int offs) {
  QC_CHECK(bits+offs<=mapbits());
  return new quSwap(pbase->newsubstring(bits,mapbits()-bits-offs));
}

bitvec quSwap::mapmask() const {
  return pbase->mapmask();
}

bitvec quSwap::map(const bitvec& v) const {
  return pbase->map(swap(v));
}

bitvec quSwap::unmap(const bitvec& v) const {
  return pbase->unmap(swap(v));
}

int quSwap::mapindex(int i) const {
  return pbase->mapindex(mapbits()-i-1);
}

/* quVar */

quState* quVar::newsubstring(int bits,int offs) {
  if(pbase) return pbase->newsubstring(bits,offs); else return new quVar();
}

bitvec quVar::mapmask() const {
  QC_CHECK(pbase);
  return pbase->mapmask();
}

bitvec quVar::map(const bitvec& v) const {
  QC_CHECK(pbase);
  return pbase->map(v);
}

bitvec quVar::unmap(const bitvec& v) const {
  QC_CHECK(pbase);
  return pbase->unmap(v);
}

int quVar::mapindex(int i) const {
  QC_CHECK(pbase);
  return pbase->mapindex(i);
}

/* quCombState */

quCombState::~quCombState() {
  if(delflag) {
    if(!ptail->isbasestate()) qc_delete(ptail);
  } else {
    pbase=0;
  };
}

quState* quCombState::newsubstring(int bits,int offs) {
  int l=pbase->mapbits();
  quCombState *c;
  QC_CHECK(bits+offs<=mapbits());

  if(bits+offs<=l) 
    return pbase->newsubstring(bits,offs);
  if(offs>=l)
    return ptail->newsubstring(bits,offs-l);
  c=new quCombState(bits);
  c->pbase=pbase->newsubstring(l-offs,offs);
  c->ptail=ptail->newsubstring(bits-l+offs,0);
  c->delflag=1;
  return c;
}

bitvec quCombState::mapmask() const {
  return pbase->mapmask() | ptail->mapmask();
}

bitvec quCombState::map(const bitvec& v) const {
  return pbase->map(v)+ptail->map(v);
}

bitvec quCombState::unmap(const bitvec& v) const {
  int l=pbase->mapbits();
  
  return pbase->unmap(v.getbits(0,l))|ptail->unmap(v.getbits(l,v.length()-l));
}

int quCombState::mapindex(int i) const {
  int l=pbase->mapbits();
  if(i<l)
    return pbase->mapindex(i);
  else
    return ptail->mapindex(i-l);
} 

void quCombState::_printvect(ostream& s,const bitvec& v) const {
  QC_CHECK(v.length()==mapbits());
  pbase->_printvect(s,v.getbits(0,pbase->mapbits()));
  s << ',';
  ptail->_printvect(s,v.getbits(pbase->mapbits(),ptail->mapbits()));
}

/* quSubString */

quState* quSubString::newsubstring(int bits,int offs) {
  return pbase->newsubstring(bits,_mapoffs+offs);
}

bitvec quSubString::map(const bitvec& v) const {
  return pbase->map(v).getbits(mapoffs(),mapbits());
}

bitvec quSubString::unmap(const bitvec& v) const {
  bitvec m(pbase->mapbits());

  m.setbits(mapoffs(),v);
  return pbase->unmap(m);
}

int quSubString::mapindex(int i) const {
  return mapoffs()+pbase->mapindex(i);
}

/* quWord */

quState* quWord::newsubstring(int bits,int offs) {
  quState *p;
  quWord *w;
  p=pbase->newsubstring(bits,mapoffs()+offs);
  w=new quWord(bits,0,*p);
  qc_delete(p);
  return w;
}

void quWord::_printvect(ostream& s,const bitvec& v) const {
  QC_CHECK(v.length()==mapbits());
  s << v.getword(0,v.length());
}

