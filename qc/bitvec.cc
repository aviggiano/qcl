/**********************************************************************

This file is part of the Quantum Computation Library (QCLIB).

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1996-1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/

#pragma implementation "bitvec.h"

#include "bitvec.h"

using namespace std;

DEBUG( int nbitvecs=0; )

char* qc_check_txt     = "QCLIB: qc_check failed on condition ";
char* qc_check_stdmsg  = 
  "Can't continue. Provoking segfault to simplify backtracking.\n";
char* qc_check_msg  = qc_check_stdmsg;

char* qc_delete_txt    = "QCLIB: qc_delete warning";
char* qc_delarray_txt  = "QCLIB: qc_delarray warning";
char* qc_del_msg =
  "This should not happen (out of memory?). If the warning is reproducable,\n"
  "please send a bugreport to Bernhard Oemer <oemer@tph.tuwien.ac.at>.\n";

/* private members */

void bitvec::l_bitvec(word v) {
  int i,l;
  
  l=WORDS(len);
  pvec=new word[l];
  pvec[0]=v;
  for(i=1;i<l;i++) pvec[i]=0;
}

void bitvec::l_bitvec(const bitvec& v) {
  int i,l;

  l=WORDS(v.len);
  pvec=new word[l];
  for(i=0;i<l;i++) pvec[i]=v.pvec[i];
}

void bitvec::l_append(const bitvec& v) {
  bitvec u(*this);
  setlen(len+v.len);
  *this=u+v;
}

bitvec bitvec::l_getbits(int i,int l) const {
  int k;
  bitvec v(l);

  if(l<=BPW) { v.vec=l_getword(i,l); return v; };
  for(k=0;k<(l>>LDBPW);k++) v.pvec[k]=l_getword(i+(k<<LDBPW),BPW);
  if(l&DBITS) {
    k=l>>LDBPW;
    v.pvec[k]=l_getword(i+(k<<LDBPW),l&DBITS);
  };
  return v;
}

word bitvec::l_getword(int i,int l) const {
  int j,k;
  word w;
  
  j=i&DBITS;
  k=i>>LDBPW;
  w=(pvec[k]>>j)&MASK(l);
  if(l+j>BPW) w|=(pvec[k+1]<<(BPW-j))&MASK(l);
  return w;
}

void bitvec::l_setbits(int i,int l,word v) {
  int j,k;
  
  j=i&DBITS;
  k=i>>LDBPW;
  pvec[k]&=~(MASK(l)<<j);
  pvec[k]|=(MASK(l)&v)<<j;
  if(l+j<=BPW) return;
  pvec[k+1]&=~MASK(l+j-BPW);
  pvec[k+1]|=(MASK(l)&v)>>(BPW-j);
}
            
void bitvec::l_setbits(int i,const bitvec& v) {
  int k;

  for(k=0;k<(v.len>>LDBPW);k++) l_setbits(i+(k<<LDBPW),BPW,v.pvec[k]);
  if(v.len&DBITS) {
    k=v.len>>LDBPW;
    l_setbits(i+(k<<LDBPW),v.len&DBITS,v.pvec[k]);
  };
}

/* public members */

int bitvec::testless(const bitvec& v) const {
  int k;
  QC_CHECK(len==v.len);
  
  if(len<=BPW) return vec<v.vec;
  for(k=(len-1)>>LDBPW;k>=0;k--) {
    if(pvec[k]<v.pvec[k]) return 1;
    if(pvec[k]>v.pvec[k]) return 0;
  };
  return 0;
}

word bitvec::hashfunct() const {
  int k;
  word f=len;

  if(len<=BPW) return vec+(vec>>(BPW/2))+(vec>>(BPW/4))+(vec>>(BPW/8));
  for(k=0;k<WORDS(len);k++) f+=pvec[k]+(pvec[k]>>(BPW/2));
  return f;
}

bitvec& bitvec::qnot() {
  int k,l;

  if(len<=BPW) {
    vec=(~vec) & MASK(len);
  } else {
    l=WORDS(len);
    for(k=0;k<l;k++) pvec[k]=~pvec[k];
    if(len & DBITS) pvec[l-1]&=MASK(len & DBITS);
  };
  return *this;
}

const unsigned char qc_swaptab[256] = {
  0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0,
  0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0,
  0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8,
  0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8,
  0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4,
  0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4,
  0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec,
  0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc,
  0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2,
  0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2,
  0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea,
  0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa,
  0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6,
  0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6,
  0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee,
  0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe,
  0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1,
  0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1,
  0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9,
  0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9,
  0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5,
  0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5,
  0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed,
  0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd,
  0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3,
  0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3,
  0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb,
  0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb,
  0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7,
  0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
  0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef,
  0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff
};

bitvec& bitvec::swap() {
  int i,j;
  word a,b;
  for(i=0,j=len-8;i<len/2-7;i+=8,j-=8) {
    a=getword(i,8);
    b=getword(j,8);
    a=qc_swaptab[a];
    b=qc_swaptab[b];
    setbits(i,8,b);
    setbits(j,8,a);
  }
  for(i=(len/2)&~7,j=len-i-1;i<j;i++,j--) {
    a=(*this)[i];
    b=(*this)[j];
    if(a^b) {
      setbit(i,b);
      setbit(j,a);
    }
  }
  return *this;
}

/* other functions */

int bitvec_format=(BITVEC_FORMAT_HEX|BITVEC_FORMAT_KET);
const char *bitvec_ket_prefix 	= "|";
const char *bitvec_ket_postfix 	= ">";
const char *bitvec_hex_prefix	= "0x";
const char *bitvec_hex_postfix	= "";

ostream& operator << (ostream& s,const bitvec& v) {
  int i,c;

  if(bitvec_format&BITVEC_FORMAT_KET) {
    s << bitvec_ket_prefix;
  }
  if(bitvec_format&BITVEC_FORMAT_HEX) {
    s << bitvec_hex_prefix;
    for(i=((v.length()-1) & ~3);i>=0;i-=4) {
      c=v.getword(i,(i+4<=v.length()) ? 4 : (v.length()-i));
      if(c<=9) s << (char)('0'+c); else s << (char)('a'+c-10);
    }
    s << bitvec_hex_postfix;
  } else {
    for(i=v.length()-1;i>=0;i--) {
      s << (v[i] ? '1' : '0');
    }
  }
  if(bitvec_format&BITVEC_FORMAT_KET) {
    s << bitvec_ket_postfix;
  }
  return s;
}

istream& operator >> (istream& s,bitvec& v) {
  int j=0,i=0,h=0,k=0;
  char *b;
  char c;

  if(!(b=new char[v.length()+3])) goto error;  
  do {
    s >> c;
    if(!s) goto error;
    if(c=='|') k=1;
  } while(c==' ' || c=='\t' || c=='|');
  while(1) {
    b[i++]=c;
    if(!(h && i<=(v.length()-1)/4) && !(!h && i<v.length())) break;
    s >> c;
    if(!s) goto error;
    if(c=='x' && b[i-1]=='0') {
      h=1; s >> c; i=0;
      continue;
    }
    if(c>='A' && c<='F') c+='a'-'A';
    if((h && (c<'0' || c>'9') && (c<'a' || c>'f')) ||
       (!h && c!='0' && c!='1')) goto error;
  }
  b[i--]=0;
  if(k) {
    s >> c;
    if(c!='>') goto error;
  }
  v=0;
  if(h) {
    for(j=0;i>=0 && j<v.length();i--,j+=4)
      v.setbits(j,j+4<=v.length() ? 4 : v.length()-j,(word)
                (b[i]>='0' && b[i]<='9' ? b[i]-'0' : b[i]-'a'+10));
  } else {
    for(j=0;i>=0 && j<v.length();i--,j++)
      v.setbit(j,b[i]=='1');
  }
  return s;
  
error:

  v.setlen(0);
  if(b) qc_delarray(b);
  return s;
}
