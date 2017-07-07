/**********************************************************************

This file is part of the Quantum Computation Library (QCLIB).

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1996-1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/

#ifndef _BITVEC_H
#define _BITVEC_H 1

#pragma interface

#include <iostream>

using namespace std;

#define WORDTYPE unsigned long
#define BPW     ((int)(8*sizeof(WORDTYPE)))
#define LDBPW   (BPW==16 ? 4 : (BPW==32 ? 5 : (BPW==64 ? 6 : 7)))
#define UBITS   (~(BPW-1))
#define DBITS   (BPW-1)

#define MASK(l) ((l)>=BPW ? (~0) : ((1<<(l))-1))
#define WORDS(l) (((l)+BPW-1)>>LDBPW)

extern char* qc_check_txt;
extern char* qc_check_msg;
extern char* qc_delete_txt;
extern char* qc_delarray_txt;
extern char* qc_del_msg;

#define SEGFAULT while(*((int*)0))

#ifdef QC_DEBUG
  #define QC_WHERE " in " __FILE__ ":" << __LINE__ << "\n"
  #define QC_CHECK(cond) if(!(cond)) { \
    std::cerr << qc_check_txt << #cond QC_WHERE << qc_check_msg; \
    SEGFAULT; \
  }
  #define DEBUG(d) d
  #define qc_delete(p) { \
    if(!p) { \
      std::cerr << qc_delete_txt << QC_WHERE << qc_del_msg; \
    } else { delete p; p=0; } \
  }
  #define qc_delarray(p) { \
    if(!p) { \
      std::cerr << qc_delarray_txt << QC_WHERE << qc_del_msg; \
    } else { delete[] p; p=0; } \
  }
#else
  #define QC_CHECK(cond)
  #define DEBUG(d)
  #define qc_delete(p) { if(p) { delete p; p=0; } }
  #define qc_delarray(p) { if(p) { delete[] p; p=0; } }
#endif

typedef WORDTYPE word;

DEBUG( extern int nbitvecs; )

class bitvec {
  int len;
  union {
    word *pvec;
    word vec;
  };
  void l_bitvec(word v=0);
  void l_bitvec(const bitvec& v);
  void l_append(const bitvec& v);
  bitvec l_getbits(int i,int l) const;
  word l_getword(int i,int l) const;
  void l_setbits(int i,int l,word v);
  void l_setbits(int i,const bitvec& v);
public:
  bitvec(int l=0, word v=0);
  bitvec(const bitvec& v);
  ~bitvec();
  void setlen(int l);
  bitvec& operator = (word v);
  bitvec& operator = (const bitvec& v);
  bitvec& operator += (const bitvec& v);
  int operator [] (int i) const;
  int length() const;
  bitvec getbits(int i,int l) const;
  word getword(int i,int l) const;
  word getword() const;
  void setbit(int i,int b=1);
  void setbits(int i,int l,word v=~0);
  void setbits(int i,const bitvec& v);
//  bitvec operator + (const bitvec& v) const;
  int testeq(const bitvec& v) const;
  int testzero() const;
  bitvec& operator &= (const bitvec& v);
  bitvec& operator |= (const bitvec& v);
  bitvec& operator ^= (const bitvec& v);

  word hashfunct() const;
  int testless(const bitvec& v) const;
  bitvec& qnot();
  void push(int b);
  int pop();
  int top() const;
  int nset() const;
  bitvec& swap();
};

/* inline members */

inline bitvec::bitvec(int l, word v) {
  len=l;
  if(l<=BPW) vec=v&MASK(l); else l_bitvec(v);
  DEBUG( nbitvecs++; )
}

inline bitvec::bitvec(const bitvec& v) {
  len=v.len;
  if(len<=BPW) vec=v.vec; else l_bitvec(v);
  DEBUG( nbitvecs++; )
}

inline bitvec::~bitvec() { 
  if(len>BPW) qc_delarray(pvec);
  DEBUG( nbitvecs--; ) 
}

inline void bitvec::setlen(int l) {
  QC_CHECK(l>=0);
    if(WORDS(l)!=WORDS(len)) { 
    if(len>BPW) qc_delarray(pvec);
    if(l>BPW) pvec=new word[WORDS(l)];
  };
  len=l;
}

inline bitvec& bitvec::operator = (word v) {
  int i;

  if(len<=BPW) { 
    vec=v;
  } else {
    pvec[0]=v;
    for(i=1;i<WORDS(len);i++) pvec[i]=0;
  };
  return *this;
}

inline bitvec& bitvec::operator = (const bitvec& v) {
  int i;

  setlen(v.len);
  if(len<=BPW) 
    vec=v.vec; 
  else 
    for(i=0;i<WORDS(len);i++) pvec[i]=v.pvec[i];
  return *this;
}

inline bitvec& bitvec::operator += (const bitvec& v) {
if(len+v.len<=BPW) {
    vec|=v.vec<<len;
    len+=v.len;
    return *this;
  } else {
    l_append(v);
  };
  return *this;
}

inline int bitvec::operator [] (int i) const {
  QC_CHECK(i<len);
  return len<=BPW ? (vec>>i)&1 : (pvec[i>>LDBPW]>>(i&DBITS))&1;
}

inline int bitvec::length() const { return len; }

inline bitvec bitvec::getbits(int i,int l) const {
  QC_CHECK(i+l<=len);
  return len<=BPW ? bitvec(l,vec>>i) : l_getbits(i,l);
}

inline word bitvec::getword(int i,int l) const {
  QC_CHECK(i+l<=len);
  QC_CHECK(l<=BPW);
  return len<=BPW ? (vec>>i)&MASK(l) : l_getword(i,l);
}

inline word bitvec::getword() const {
  QC_CHECK(len<=BPW);

  return vec;
}

inline void bitvec::setbit(int i,int b) {
  QC_CHECK(i<len);
  if(len<=BPW) {
    if(b) vec|=(1<<i); else vec&=~(1<<i);
  } else {
    if(b) 
      pvec[i>>LDBPW] |= (1<<(i&DBITS)); 
    else
      pvec[i>>LDBPW] &= ~(1<<(i&DBITS));
  };
}

inline void bitvec::setbits(int i,int l,word v) {
  QC_CHECK(i+l<=len);
  QC_CHECK(l<=BPW);
  if(len<=BPW) {
    vec&=~(MASK(l)<<i);
    vec|=(MASK(l)&v)<<i;
  } else {
    l_setbits(i,l,v);
  };
}

inline void bitvec::setbits(int i,const bitvec& v) {
  QC_CHECK(i+v.len<=len);
  if(v.len<=BPW) setbits(i,v.len,v.vec); else l_setbits(i,v);
}

/*
inline bitvec bitvec::operator + (const bitvec& v) const {
  bitvec u(*this);
  u+=v;
  return u;
}
*/

inline int bitvec::testeq(const bitvec& v) const {
  int k;
  QC_CHECK(len==v.len);

  if(len<=BPW) return vec==v.vec;
  for(k=0;k<WORDS(len);k++) if(pvec[k]!=v.pvec[k]) return 0;
  return 1;
}

inline int bitvec::testzero() const {
  int k;

  if(len<=BPW) return vec==0;
  for(k=0;k<WORDS(len);k++) if(pvec[k]!=0) return 0;
  return 1;
}

inline bitvec& bitvec::operator &= (const bitvec& v) {
  int k;
  QC_CHECK(len==v.len);

  if(len<=BPW) {
    vec&=v.vec;
  } else {
    for(k=0;k<WORDS(len);k++) pvec[k]&=v.pvec[k];
  };
  return *this;
}

inline bitvec& bitvec::operator |= (const bitvec& v) {
  int k;
  QC_CHECK(len==v.len);

  if(len<=BPW) {
    vec|=v.vec;
  } else {
    for(k=0;k<WORDS(len);k++) pvec[k]|=v.pvec[k];
  };
  return *this;
}
 
inline bitvec& bitvec::operator ^= (const bitvec& v) {
  int k;
  QC_CHECK(len==v.len);

  if(len<=BPW) {
    vec^=v.vec;
  } else {
    for(k=0;k<WORDS(len);k++) pvec[k]^=v.pvec[k];
  };
  return *this;
}

inline void bitvec::push(int b) {
  if(WORDS(len)<WORDS(len+1)) {
    if(len==0) {
      vec=0;
    } else {
      word *p=new word[WORDS(len+1)];
      p[WORDS(len)]=0;
      if(WORDS(len)==1) {
        p[0]=vec;
      } else {
        int i;
        for(i=0;i<WORDS(len);i++) p[i]=pvec[i];
        qc_delete(pvec);
      }
      pvec=p;
    }
  }
  len++;
  setbit(len-1,b);
}

inline int bitvec::pop() {
  QC_CHECK(len);
  int b=(*this)[len-1];
  setbit(len-1,0);
  if(WORDS(len-1)<WORDS(len)) {
    if(WORDS(len-1)==1) {
      word w=pvec[0];
      qc_delete(pvec);
      vec=w;
    } else if(WORDS(len-1)>1) {
      int i;
      word *p=new word[WORDS(len-1)];
      for(i=0;i<WORDS(len-1);i++) p[i]=pvec[i];
      qc_delete(pvec);
    }
  }
  len--;
  return b;
}

inline int bitvec::top() const {
  QC_CHECK(len);
  return (*this)[len-1];
}
  
inline int bitvec::nset() const {
  int n=0;
  int i;
  for(i=0;i<len;i++) n+=(*this)[i];
  return n;
}

/* other inline functions */

inline int operator == (const bitvec& a,const bitvec& b) { return a.testeq(b); }

inline int operator != (const bitvec& a,const bitvec& b) { return !a.testeq(b); }

inline int operator <  (const bitvec& a,const bitvec& b) { return a.testless(b); }

inline int operator >  (const bitvec& a,const bitvec& b) { return b.testless(a); }

inline int operator <= (const bitvec& a,const bitvec& b) { return !b.testless(a); }

inline int operator >= (const bitvec& a,const bitvec& b) { return !a.testless(b); }

inline bitvec operator + (const bitvec& a,const bitvec& b) {
  bitvec v(a);
  v+=b;
  return v;
}

inline bitvec operator ~ (const bitvec& a) {
  bitvec v(a);

  v.qnot();
  return v;
}

inline bitvec operator & (const bitvec& a,const bitvec& b) {
  bitvec v(a);

  v&=b;
  return v;
}

inline bitvec operator | (const bitvec& a,const bitvec& b) {
  bitvec v(a);

  v|=b;
  return v;
}

inline bitvec operator ^ (const bitvec& a,const bitvec& b) {
  bitvec v(a);

  v^=b;
  return v;
}

inline int zero(const bitvec& v) {
  return v.testzero();
}

inline bitvec swap(const bitvec& v) {
  bitvec s=v;
  s.swap();
  return s;
}

/* other functions */

#define BITVEC_FORMAT_BIN 0
#define BITVEC_FORMAT_HEX 1
#define BITVEC_FORMAT_PLAIN 0
#define BITVEC_FORMAT_KET 2

extern int bitvec_format;
extern int bitvec_min_width;

ostream& operator << (ostream& s,const bitvec& v);
istream& operator >> (istream& s,bitvec& v);

#endif

