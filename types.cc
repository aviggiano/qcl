/**********************************************************************

This file is part of the Quantum Computation Language QCL.

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/


#pragma implementation

#include "types.h"
#include "cond.h"
#include "options.h"
#include "error.h"

#include <math.h>
#include <stdio.h>

#ifdef QCL_DEBUG
int n_object=0;
int n_value=0;
#endif
const char *FALSE_STR="false";
const char *TRUE_STR="true";

const char *BASETYPE_STR[] = {"%UNDEF%", "%ERROR%", "procedure", "operator", 
  "qufunct", "boolean", "int", "real", "complex", "string", "quconst",
  "qureg", "quvoid", "quscratch", "qucond" };

string sdec(long n,const char *format) {
  static char buf[256];
  snprintf(buf,256,format,n);
  return string(buf);
}

int tensordim(int ord, int elem) {
  if(ord==1) return elem;
  int dim;                                   
  if(ord==2) 
    dim=(int)floor(sqrt((double)elem)+0.1);                   
  else                                       
    dim=(int)floor(pow((double)elem,(double)1.0/ord)+0.1);          
  if((int)pow((double)dim,(int)ord)!=elem) return 0;    
  return dim;                                
}

int tensorelem(int ord, int dim) {
  int n=1;
  while(ord--) n*=dim;
  return n;
}

ostream& operator << (ostream& s, const tType& t) {
  s << t.str();
  return s;
}

string tType::str() const {
  string s;
  if(basetype()<=tQUCOND)
    s=BASETYPE_STR[basetype()];
  else
    s="unknown type";
  if(ord()==1) 
    s+=" vector";
  else if(ord()==2)
    s+=" matrix";
  else if(ord()>2)
    s+=" tensor"+sdec(ord());
  return s;  
}

ostream& operator << (ostream& s, const tValue& v) { 
  return s << v.str(); 
}

void tValue::error(const char* m) const {
  SEGFAULT;
  throw tError(errINT,string(m));
}
 
void tValue::delpointer() {
  if(ord()) {
    if(_val.pt->refs>1) {
      _val.pt->refs--;
    } else {
      if(_val.pt->refs==1) {
        switch(basetype()) {
          case tINTEGER:  qcl_delarray(_val.pt->pi); break;
          case tREAL:     qcl_delarray(_val.pt->pr); break;
          case tCOMPLEX:  qcl_delarray(_val.pt->pz); break;
          default: error("invalid tensor type");
        }
      }
      qcl_delete(_val.pt);
    }
  } else {
    switch(basetype()) {
      case tCOMPLEX:	qcl_delete(_val.pz); return;
      case tSTRING:	qcl_delete(_val.ps); return;
      case tQUCONST:
      case tQUREG:
      case tQUVOID:
      case tQUSCR:      if(!_val.pq->isbasestate())
			  qcl_delete(_val.pq); 
                        return;
      case tQUCOND:	qcl_delete(_val.pc); return;
      default: ;
    }
  }
}

void tValue::copytensor() {
  tensor *a=_val.pt;
  tensor *b=new tensor;
  b->dim=a->dim;
  b->len=a->len;
  b->refs=1;
  a->refs--;
  int i;
  switch(basetype()) {
    case tINTEGER:  
      b->pi=new tInt[b->len];
      for(i=0;i<b->len;i++) b->pi[i]=a->pi[i]; 
      break;
    case tREAL:     
      b->pr=new tReal[b->len];
      for(i=0;i<b->len;i++) b->pr[i]=a->pr[i]; 
      break;
    case tCOMPLEX:  
      b->pz=new tComplex[b->len];
      for(i=0;i<b->len;i++) b->pz[i]=a->pz[i]; 
      break;
    default: throw tError(errINT,"invalid tensor type");
  }
  _val.pt=b;
}  

void tValue::inittensor(const tType& t,int d) {
  if(!t.ord()) {
    init(t);
    return;
  }
  _type=t;
  tensor *b=new tensor;
  b->dim=d;
  b->len=tensorelem(ord(),d);
  b->refs=1;
  int i;
  switch(basetype()) {
    case tINTEGER:  
      b->pi=new tInt[b->len];
      for(i=0;i<b->len;i++) b->pi[i]=0; 
      break;
    case tREAL:     
      b->pr=new tReal[b->len];
      for(i=0;i<b->len;i++) b->pr[i]=0; 
      break;
    case tCOMPLEX:  
      b->pz=new tComplex[b->len];
      for(i=0;i<b->len;i++) b->pz[i]=0; 
      break;
    default: error("invalid tensor type");
  }
  _val.pt=b;
}

QuCond tValue::toQuCond() const {                                    
  if(_type==tQUCOND) return *_val.pc;                        
  if(isQuExpr()) return _val.pq;                             
  if(isBoolean())                                            
    return toBool() ? QCTRUE(optBits) : QCFALSE(optBits);    
#ifdef QCL_DEBUG                                             
  cerr << "toQuCond: " << str() << " is not conditional\n";  
#endif                                                       
  return QuCond();                                           
}                                                            

tValue tValue::convert(const tType& t) const {
  if(ord()) {
    tensor *b=new tensor;
    b->dim=dim();
    b->len=elem();
    b->refs=1;
    tValue v;
    v._type=t;
    v._val.pt=b;
    int i;
    switch(v.basetype()) {
      case tINTEGER:  
        b->pi=new tInt[b->len];
        for(i=0;i<b->len;i++) b->pi[i]=(*this)[i].toInt(); 
        break;
      case tREAL:     
        b->pr=new tReal[b->len];
        for(i=0;i<b->len;i++) b->pr[i]=(*this)[i].toReal(); 
        break;
      case tCOMPLEX:  
        b->pz=new tComplex[b->len];
        for(i=0;i<b->len;i++) b->pz[i]=(*this)[i].toComplex(); 
        break;
      default: error("tensor convert failed");
    }
    return v;
  } else {
    switch(t.basetype()) {
      case tINTEGER: return toInt();
      case tREAL:    return toReal();
      case tCOMPLEX: return toComplex();
      case tQUCOND:  return toQuCond();
      default: 
        if(!isQuExpr() || !t.isQuExpr()) 
          error("scalar convert failed");
        tValue v=*this;
        v._type=t;
        return v;
    }
  }
  return tValue();
}

string tValue::str() const {
  if(ord()) {
    int i;
    string ostr="[";
    for(i=0;i<elem();i++) {
      if(i) {
        if(i%dim())
          ostr+=",";
        else
          ostr+=";";
      }
      ostr+=(*this)[i].str();
    }
    return ostr+="]";
  };
  char s[80];
  switch(basetype()) {
    case tBOOLEAN:	return (_val.b ? TRUE_STR : FALSE_STR);
    case tINTEGER:
      sprintf(s,"%ld",_val.i);
      return s;	
    case tREAL:
      if(optTruncZeros) {
        tReal r=_val.r;
        if(abs(r)<pow(0.1,optPrintPrecision+2)) r=0;
        int p=MAX(optPrintPrecision,2+(int)(log10(abs(r))));
        sprintf(s,"%.*g",p,r);
      } else {
        sprintf(s,"%.*f",optPrintPrecision,_val.r);
      }
      return s;	
    case tCOMPLEX:
      if(optTruncZeros) {
        if(abs(_val.pz->imag())<pow(0.1,optPrintPrecision+1))
          return tValue(_val.pz->real()).str();
        else 
          return "("+tValue(_val.pz->real()).str()+","+
                     tValue(_val.pz->imag()).str()+")";
      } else {
        sprintf(s,"(%.*f,%.*f)",optPrintPrecision,_val.pz->real(),
                                optPrintPrecision,_val.pz->imag());
        return s;
      }
    case tSTRING:	return (string)*(_val.ps);
    case tQUCONST:
    case tQUREG:
    case tQUVOID:
    case tQUSCR:
      if(optQuregMask) {
        bitvec b(_val.pq->basebits()),c;
	string ostr="|";
	int i,j;
    	for(i=_val.pq->basebits()-1;i>=0;i--) {
    	  b.setbit(i,1);
    	  c=_val.pq->map(b);
    	  if(zero(c)) {
    	    ostr+=".";
    	  } else {
    	    for(j=0;j<_val.pq->mapbits();j++) {
    	      if(c[j]) { ostr+=(char)(j<10 ? '0'+j : 'a'+j-10); break; }
    	    }
    	  }
    	  b.setbit(i,0);
    	}
        return ostr+">";
      } else {
        if(isEmpty()) return "<>";
        string ostr="<";
	int i;
	for(i=0;;i++) {
	  ostr+=sdec(_val.pq->mapindex(i));
	  if(i>=_val.pq->mapbits()-1) break;
	  ostr+=",";
	}
        return ostr+">";
      }  
      //sprintf(s,"[%d / %d qubits]",_val.pq->mapbits(),_val.pq->basebits());
    case tQUCOND:	return _val.pc->str();
    default:      	return _type.str();
  };
  return "";
}

