/**********************************************************************

This file is part of the Quantum Computation Library (QCLIB).

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1996-1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/

#pragma implementation

#include "operator.h"

DEBUG( int noperators=0; )

/* opOperator */

opOperator::~opOperator() { DEBUG( noperators--; ) }

/* opElementary */

void opElementary::apply(quState& qs) const {
  int i,n;
  terminfo ti;
  bitvec m;

  if(!qs.mapbits()) return;
  qs.opbegin();
  ti.pqs=&qs;
  m=~qs.mapmask();
  n=qs.baseterms();
  for(i=0;i<n;i++) {
    ti.mapterm=qs.baseterm(i);
    ti.frame=ti.mapterm.vect() & m;
    ti.mapterm.setvect(qs.map(ti.mapterm.vect()));
    addterms(ti);
  };
  qs.opend();
}

/* opMatrix */

opMatrix::opMatrix(int n) : opElementary(n) {
  QC_CHECK(n<=BPW);
  len=1<<n;
  matrix=new term* [len];
}

opMatrix::opMatrix(int n,term **m) : opElementary(n) {
  int i,j,nj;
  QC_CHECK(n<=BPW);

  len=1<<n;
  matrix=new term* [len];
  for(i=0;i<len;i++) {
    nj=0;
    while(m[i][nj++].vect().length());
    matrix[i]=new term[nj];
    for(j=0;j<nj-1;j++) matrix[i][j]=m[i][j];
  };
}
                
opMatrix::~opMatrix() {
  int i;

  for(i=0;i<len;i++) delete[] matrix[i];
  qc_delarray(matrix);
}

void opMatrix::addterms(const terminfo& ti) const {
  word w;
  term *pt;
  complx z;
  
  w=ti.mapterm.vect().getword();
  pt=matrix[w];
  z=ti.mapterm.ampl();
  while(pt->vect().length()) {
    ti.pqs->opadd(ti.frame | ti.pqs->unmap(pt->vect()),z*pt->ampl());
    pt++;
  };
}

opOperator *opMatrix::newclone() const {
  return new opMatrix(bits(),matrix);
}

/* opBit */

opBit::opBit(complx u00,complx u01,complx u10,complx u11,double norm)
: opMatrix(1) {
  matrix[0]=new term[3];
  matrix[1]=new term[3];
  matrix[0][0].set(bitvec(1,0),u00*norm);
  matrix[0][1].set(bitvec(1,1),u10*norm);
  matrix[1][0].set(bitvec(1,0),u01*norm);
  matrix[1][1].set(bitvec(1,1),u11*norm);
}

/* opU2 */

opU2::opU2(double theta,double delta,double sigma,double tau)
: opMatrix(1) {
  complx d,s,t;
  double cs,si;

  matrix[0]=new term[3];
  matrix[1]=new term[3];
  cs=cos(theta/2);
  si=sin(theta/2);
  d=exp(complx(0,delta));
  s=exp(complx(0,sigma));
  t=exp(complx(0,tau));
  matrix[0][0].set(bitvec(1,0),d*s*t*cs);
  matrix[0][1].set(bitvec(1,1),-d*conj(s)*t*si);
  matrix[1][0].set(bitvec(1,0),conj(d)*conj(s)*t*si);
  matrix[1][1].set(bitvec(1,1),d*conj(s)*conj(t)*cs);
}

/* opIdentity */

void opIdentity::apply(quState& qs) const { }

void opIdentity::addterms(const terminfo& ti) const { }

opOperator *opIdentity::newclone() const { 
  return new opIdentity(bits()); 
}

/* opSwap */

void opSwap::addterms(const terminfo& ti) const { 
  bitvec v,w;

  v=ti.mapterm.vect();
  w=v.getbits(offs1,len);
  v.setbits(offs1,v.getbits(offs2,len));
  v.setbits(offs2,w);
  ti.pqs->opadd(ti.frame | ti.pqs->unmap(v),ti.mapterm.ampl());
}

opOperator *opSwap::newclone() const { 
  return new opSwap(bits(),len,offs1,offs2); 
}

/* opPermutation */

opPermutation::opPermutation(int n) : opElementary(n) {
  QC_CHECK(bits()<=BPW);
  len=1<<n;
  perm=new term[len];
}

opPermutation::opPermutation(int n,term *p) : opElementary(n) {
  int i;
  QC_CHECK(n<=BPW);

  len=1<<n;
  perm=new term[len];
  for(i=0;i<len;i++) perm[i]=p[i];
}
                
opPermutation::~opPermutation() {
  qc_delarray(perm);
}

void opPermutation::addterms(const terminfo& ti) const {
  word w;
  complx z;
  
  w=ti.mapterm.vect().getword();
  z=ti.mapterm.ampl();
  ti.pqs->opadd(ti.frame | ti.pqs->unmap(perm[w].vect()),z*perm[w].ampl());
}

opOperator *opPermutation::newclone() const {
  return new opPermutation(bits(),perm);
}

/* opFunction */

void opFunction::addterms(const terminfo& ti) const {
  term t;
  bitvec v,w;
//QC_CHECK(zero(ti.mapterm.vect().getbits(_arg,_fct)));

  v=ti.mapterm.vect().getbits(0,_arg);
  w=ti.mapterm.vect().getbits(_arg,_fct);
  t=funct(v); 
  w^=t.vect();
  ti.pqs->opadd(ti.frame|ti.pqs->unmap(v+w),ti.mapterm.ampl()*t.ampl());
}

/* opEXPN */

term opEXPN::funct(const bitvec& v) const {
  word a,y,u;
  int i;

  a=v.getword(); y=1; u=_x;
  for(i=0;i<bits();i++) {
    if(a & (1<<i)) { y*=u; y%=_num; };
    u*=u; u%=_num;
  };
  return term(bitvec(fct(),y),1.0);
}

opOperator *opEXPN::newclone() const {
  return new opEXPN(arg(),fct(),_x,_num);
}


/* opGate */

void opGate::addterms(const terminfo& ti) const {
  term t;

  t=funct(ti.mapterm.vect());
  ti.pqs->opadd(ti.frame|ti.pqs->unmap(t.vect()),ti.mapterm.ampl()*t.ampl());
}

/* opCNot */

void opCNot::apply(quState& qs) const {
  int i,n;
  bitvec m,me,mo;
  term t;

  if(!qs.mapbits()) return;
  qs.opbegin();
  m=bitvec(bits());
  for(i=0;i<out;i++) m.setbit(i);
  me=qs.unmap(~m);
  mo=qs.unmap(m);
  n=qs.baseterms();
  for(i=0;i<n;i++) {
    t=qs.baseterm(i);
    if((t.vect()&me)==me) t.setvect(t.vect()^mo);
    qs.opadd(t.vect(),t.ampl());
  }
  qs.opend();
}

opOperator *opCNot::newclone() const {
  return new opCNot(out,enable);
}

/* opCPhase */

void opCPhase::apply(quState& qs) const {
  int i,n;
  bitvec m=qs.unmap(~bitvec(bits()));
  term t;

  if(!qs.mapbits()) return;
  qs.opbegin();
  n=qs.baseterms();
  for(i=0;i<n;i++) {
    t=qs.baseterm(i);
    if((t.vect()&m)==m) t.setampl(t.ampl()*phase);
    qs.opadd(t.vect(),t.ampl());
  }
  qs.opend();
}

opOperator *opCPhase::newclone() const {
  return new opCPhase(bits(),phase);
}


/* opCk */

opCk::opCk(int n,int k,int o) : opGate(n) {
  _k=k;
  out=o;
  in=new int[k];
}

opCk::opCk(int n,int k,int o,int *i) : opGate(n) {
  int j;
  
  _k=k;
  out=o;
  in=new int[k];
  for(j=0;j<k;j++) in[j]=i[j];
}
  
opCk::~opCk() {
  qc_delete(in);
}

term opCk::funct(const bitvec& v) const {
  bitvec w=v;
  int f=1;
  int i;
  QC_CHECK(v.length()==bits());

  for(i=0;i<_k;i++) f &= v[in[i]];
  if(f) w.setbit(out,!w[out]);
  return term(w,1.0);
}

opOperator *opCk::newclone() const {
  return new opCk(bits(),_k,out,in);
}

/* opCondPhase */

opCondPhase::opCondPhase(int n,int k,double phi) : opGate(n) {
  int j;
  _k=k;
  in=new int[k];
  for(j=0;j<k;j++) in[j]=j;
  _phi=phi;
}

opCondPhase::opCondPhase(int n,int k,int *i,double phi) : opGate(n) {
  int j;
  
  _k=k;
  in=new int[k];
  for(j=0;j<k;j++) in[j]=i[j];
  _phi=phi;
}
  
opCondPhase::~opCondPhase() {
  qc_delete(in);
}

term opCondPhase::funct(const bitvec& v) const {
  int f=1;
  int i;

  for(i=0;i<_k;i++) f &= v[in[i]];
  if(f) 
    return term(v,exp(complx(0,_phi)));
  else
    return term(v,1.0);
}

opOperator *opCondPhase::newclone() const {
  return new opCondPhase(bits(),_k,in,_phi);
}

/* opComposition */

void opComposition::apply(quState& qs) const {
  inner->apply(qs);
  outer->apply(qs);
}

opOperator *opComposition::newclone() const {
  return new opComposition(*inner,*outer);
}

opComposition::~opComposition() {
  if(inner) qc_delete(inner);
  if(outer) qc_delete(outer);
}

/* opEmbedded */

void opEmbedded::apply(quState& qs) const {
  quState *pqs;

  if(!qs.mapbits()) return;
  pqs=qs.newsubstring(_op->bits(),_offs);
  _op->apply(*pqs);
  if(!pqs->isbasestate()) qc_delete(pqs);
}

opOperator *opEmbedded::newclone() const {
  return new opEmbedded(bits(),_offs,*_op);
}

opEmbedded::~opEmbedded() {
  if(_op) delete _op;
}

/* opVar */

void opVar::apply(quState& qs) const {
  if(_op) _op->apply(qs);
}

opOperator *opVar::newclone() const {
  if(_op) return _op->newclone(); else return new opVar();
}

opVar::~opVar() {
  if(_op) delete _op;
}

