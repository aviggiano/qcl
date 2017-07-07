/**********************************************************************

This file is part of the Quantum Computation Language QCL.

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/


#pragma implementation

#include "dump.h"
#include "quheap.h"
#include "options.h"
#include "error.h"

/*

bitvec trimvect(const bitvec& v) {}
string vect2bin(const bitvec& v) {}
string vect2dec(const bitvec& v) {}


string vect2hex(const bitvec& v) {
  string s="0x";
  int i,c;
  for(i=((v.length()-1) & ~3);i>=0;i-=4) {                        
    c=v.getword(i,(i+4<=v.length()) ? 4 : (v.length()-i));        
    if(c<=9) s+=(char)('0'+c); else s+=(char)('a'+c-10);  
  }
  return format->ket_beg+string(s)+format->ket_end;
}

*/

string regstr(const bitvec& v,int width=0) {
  int i,c,z=0;
  char s[v.length()+3];
  char *p=s;

  if((optDumpFormat=='a'||optDumpFormat=='d') && v.length()>BPW || optDumpFormat=='x') {
    *(p++)='0'; *(p++)='x';
    for(i=((v.length()-1) & ~3);i>=0;i-=4) {
      c=v.getword(i,(i+4<=v.length()) ? 4 : (v.length()-i));
      z|=c;
      if(width && !z && i>=width) continue;
      if(c<=9) *(p++)=(char)('0'+c); else *(p++)=(char)('a'+c-10);
    }
    *(p++)=0;
  } else if(optDumpFormat=='d') {
    sprintf(s,"%lu",v.getword());
  } else {
    for(i=v.length()-1;i>=0;i--) {
      z|=v[i];
      if(width && !z && i>=width) continue;
      *(p++)=(v[i] ? '1' : '0');
    }
    *(p++)=0;
  }
  return string(s);
}

string vectstr(const bitvec& v,int width=0,const QuHeap *qh=0) {
  if(optShowRegs && qh && qh->Regs()) {
    int i;
    bitvec m=bitvec(v.length());
    string s=format->ket_beg;
    for(i=0;i<qh->Regs();i++) {
      const quState *q=qh->Reg(i);
      s+=regstr(q->map(v),0);
      m|=q->mapmask();
      if(i+1<qh->Regs()) s+=',';
    }
    if(!zero(~m&v)) {
      quMask qm(*(qh->state()),~m);
      s+=';';
      s+=regstr(qm.map(v),0);
    }
    s+=format->ket_end;
    return s;
  } else {
    return format->ket_beg+regstr(v,width)+format->ket_end;
  }
}

string probstr(tReal r) {
  char s[2*optDumpPrecision+80];
  sprintf(s,"%.*g",optDumpPrecision,r);
  return s;
}

string amplstr(const tComplex &z,int cont=0) {
  const char *sg = "";
  tReal r=z.real();
  tReal i=z.imag();
  int p=optDumpPrecision;
  char s[2*optDumpPrecision+80];
  if(abs(r)<optDumpEpsilon) r=0;
  if(abs(i)<optDumpEpsilon) i=0;
  if(abs(r-1)<optDumpEpsilon) r=1;
  if(abs(i-1)<optDumpEpsilon) i=1;
  if(abs(r+1)<optDumpEpsilon) r=-1;
  if(abs(i+1)<optDumpEpsilon) i=-1;
  
  if(r!=0 && i!=0) {
    if(cont) sg=" + ";
    if(optDumpPolar) 
      sprintf(s,"%s(%.*g;%.*g%s)",sg,p,sqrt(r*r+i*i),p,180.0/PI*atan2(i,r),format->deg);
    else
      sprintf(s,"%s(%.*g%+.*g%s)",sg,p,r,p,i,format->imag);
    return s;
  }
  if(cont) sg=" + ";
  if(cont && r<0) { r=-r; sg=" - "; }
  if(cont && i<0) { i=-i; sg=" - "; }
  if(i==1 && r==0) {
    sprintf(s,"%s%s",sg,format->imag);
  } else if(i==-1 && r==0) {
    sprintf(s,"%s-%s",sg,format->imag);
  } else if(i!=0) {
    sprintf(s,"%s%.*g%s",sg,p,i,format->imag);
  } else {
    sprintf(s,"%s%.*g",sg,p,r);
  }
  return s;
}    

string termstr(const tComplex &z,const bitvec& v,int cont=0,int width=0,const QuHeap *qh=0) {
  return amplstr(z,cont)+format->mult+vectstr(v,width,qh);
}

int report_state(QuHeap *qh) {
  int width= optTrucStates ? MAX(qh->nBits()-qh->nFree(),1) : 0;
  state_map *pm=qh->state()->new_state_map(optDumpEpsilon);
  state_iter i;
  
  cout << format->latex_beg;
  
  cout << "[" << qh->nBits()-qh->nFree() << "/" << qh->nBits() << "] ";
  if(optAutoDump && (int)pm->size()<=optAutoDump) {
    cout << format->math_beg;
    for(i=pm->begin();i!=pm->end();i++)
      cout << termstr((*i).second,(*i).first,i!=pm->begin(),width,qh);
    cout << format->math_end;
  } else if(pm->size()>4) {
    cout << format->math_beg;
    i=pm->begin();
    cout << termstr((*i).second,(*i).first,0,width,qh);
//    i++;  
//    cout << termstr((*i).second,(*i).first,1,width,qh);
    if(optTeXmacs) 
      cout << " + \\ldots";
    else
      cout << " + ...";
    cout << termstr((*(pm->rbegin())).second,(*(pm->rbegin())).first,1,width,qh);
    cout << format->math_end;
    cout << " (" << pm->size() << " terms)";
  } else {
    cout << " " << pm->size() << " terms";
  }
  cout << "\n";
  delete pm;
  cout << format->latex_end;
  return 0;
}

int dump_state(QuHeap *qh,ostream *o) {
  int width= optTrucStates ? MAX(qh->nBits()-qh->nFree(),1) : 0;
  state_iter i;
  ostream *f= o ? o : &cout;
    const OutputFormat *oldformat=format;

  if(o) format=&FormatPlain;
  (*f) << format->latex_beg;
  (*f) << format->math_beg;
  state_map *pm=qh->state()->new_state_map(optDumpEpsilon);
  for(i=pm->begin();i!=pm->end();i++)
    (*f) << termstr((*i).second,(*i).first,i!=pm->begin(),width);
  delete pm;
  (*f) << format->math_end;
  (*f) << "\n";
  (*f) << format->latex_end;
  format=oldformat;
  return 0;
}
  
int dump_spectrum(quState *qs,ostream *o) {
  spectrum_iter i;
  ostream *f= o ? o : &cout;
  const OutputFormat *oldformat=format;

  if(o) format=&FormatPlain;
  (*f) << format->latex_beg;
  (*f) << format->math_beg;
  spectrum_map *pm=qs->new_spectrum_map(optDumpEpsilon);
  for(i=pm->begin();i!=pm->end();i++) {
    if(i!=pm->begin()) (*f) << ", ";
    (*f) << probstr((*i).second);
    (*f) << format->mult;
    (*f) << vectstr((*i).first);
  }
  delete pm;
  (*f) << format->math_end;
  (*f) << "\n";
  (*f) << format->latex_end;
  format=oldformat;
  return 0;
}
    
