/**********************************************************************

This file is part of the Quantum Computation Language QCL.

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/


#pragma implementation

#include "cond.h"
#include "types.h"

string QuCond::str() const {
  string ostr="";
  bitvec v;
  iter i;
  int j;
  if(elem()==0) return "<>";
  for(i=cond.begin();i!=cond.end();i++) {
    ostr+=" ";
    v=*i;
    if(zero(v)) {
      ostr+="*;";
    } else {
      for(j=0;j<bits();j++) {
        if(v[j]) { ostr+=sdec(j,"%d,"); }
      }
    }
    ostr[ostr.length()-1]=';';
  }
  ostr[0]='<';
  ostr[ostr.length()-1]='>';
  return ostr;
}

inline QuCond regbit(const quState *q,int i) {
  bitvec m(q->basebits());
  m.setbit(q->mapindex(i));
  return QuCond(m);
}

QuCond regcomp(const quState *q,const quState *p) {
  QuCond c=QCTRUE(q->basebits());
  int i;
  int n=q->mapbits();
  if(n!=p->mapbits()) return QCFALSE(q->basebits());
  for(i=0;i<n;i++) 
    c=c & ~(regbit(q,i) ^ regbit(p,i)); 
  return c;
}

QuCond regcomp(const quState *q,int n) {
  QuCond c=QCTRUE(q->basebits());
  int i;
  for(i=0;i<q->mapbits();i++) {
    if(n&1)
      c=c & regbit(q,i);
    else
      c=c & ~regbit(q,i);
    n>>=1;
  } 
  if(n) return QCFALSE(q->basebits());
  return c;
}

