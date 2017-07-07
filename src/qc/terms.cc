/**********************************************************************

This file is part of the Quantum Computation Library (QCLIB).

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1996-1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/

#pragma implementation "terms.h"

#include "terms.h"

#include <iomanip>

using namespace std;

#define NONE (-1)

DEBUG( int nterms=0; )
DEBUG( int ntermlists=0; )
DEBUG( int nprobtrees=0; )


/* member functions */

// class termlist:

termlist::termlist(int bits,int len) {
  _nbits=bits;
  listlen=len;
  hashlen=1<<duallog(5*len/4);
  hashmask=hashlen-1;
  newlist();
  clear();
  DEBUG( ntermlists++; )
}

termlist::termlist(const termlist& l) {
  int i;
  
  _nbits=l.nbits();
  _nterms=l.nterms();
  listlen=l.listlen;
  hashlen=l.hashlen;
  hashmask=hashlen-1;
  newlist();
  for(i=0;i<listlen;i++) list[i]=l.list[i];
  for(i=0;i<hashlen;i++) hash[i]=l.hash[i];
  DEBUG( ntermlists++; )
}

termlist::~termlist() {
  dellist();
  DEBUG( ntermlists--; )
}

termlist& termlist::operator = (const termlist& l) {
  int i;

  dellist();
  _nbits=l.nbits();
  _nterms=l.nterms();
  listlen=l.listlen;
  hashlen=l.hashlen;
  hashmask=hashlen-1;
  newlist();
  for(i=0;i<listlen;i++) list[i]=l.list[i];
  for(i=0;i<hashlen;i++) hash[i]=l.hash[i];
  return *this;
}

void termlist::add(const bitvec& v,const complx& z) {
  int h,i,n;
  term *pt;

  h=hashfunct1(v);
  while(1) {
    pt=hash[h];
    if(!pt) {
      if(_nterms>=listlen) {
        pt=list;
        n=_nterms;
        listlen*=2;
        hashlen*=2;
        hashmask=hashlen-1;
        qc_delarray(hash);
        newlist();
        clear();
        for(i=0;i<n;i++) add(pt[i]);
        qc_delarray(pt);
        add(v,z);
      } else {
        list[_nterms].setvect(v);
        list[_nterms].setampl(z);
        hash[h]=&list[_nterms];
        _nterms++;
      };
      return;
    };
    if(pt->vect()==v) {
      pt->setampl(pt->ampl()+z);
      return;
    };
    h+=hashfunct2(v);
    h&=hashmask;
  };
}

/* other functions */

int duallog(int k) {
  int i=0;

  for(;k!=0;k>>=1) i++;
  return i;
}

ostream& operator << (ostream& s,const term& t) {
  complx z=t.ampl();
//s.form("%+19.17f\t%+19.17f\t",z.real(),z.imag());
  s << setw(19) << setprecision(17) << z.real() << '\t';
  s << setw(19) << setprecision(17) << z.imag() << '\t';
  s << t.vect();
  return s;
}

istream& operator >> (istream& s,term& t) {
  bitvec v(t.nbits());
  double x=10,y=10;
  
//s.scan("%lf %lf",&x,&y);
  s >> x >> y;
  if(x>1 || x<-1 || y>1 || y<-1) goto error; 
  s >> v;
  t.setvect(v);
  t.setampl(complx(x,y));
  return s;
error:
  t.setvect(bitvec());
  return s;
}

