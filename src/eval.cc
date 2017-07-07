/**********************************************************************

This file is part of the Quantum Computation Language QCL.

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/



#include "syntax.h"
#include "error.h"
#include "debug.h"
#include "options.h"

#include <stdlib.h>
#include <math.h>

#define TRACE() if (optTrace) qcltrace("EVAL",this,loc,gl,qh)

#define CHECK(v) if((v).isError()) throw tError(errINT,"expression of type tERROR enountered",this)
#define EVAL(v,p) { v=(p)->eval(loc,gl,qh); CHECK(v); }
// #define ASSERT(c) if(!(c)) throw tError(errINT,"eval type inconsistency",this)

tValue sExpr::eval(SymTable *loc,SymTable *gl,QuHeap *qh) {
  TRACE();
  throw tError(errINT,"eval is not implemented in class sExpr",this);
}

tValue sConst::eval(SymTable *loc,SymTable *gl,QuHeap *qh) {
  TRACE();
  return _val;
}

tValue sVar::eval(SymTable *loc,SymTable *gl,QuHeap *qh) {
  tValue v;
  ObjType o;
  TRACE();
  v=loc->getVal(id(),&o);
  if(!v.isExpr()) v=gl->getVal(id(),&o);
  ASSERT(v.type()==type() || (v.isQuExpr() && type().isQuExpr()));
  return v;
}

tValue sSubscript::eval(SymTable *loc,SymTable *gl,QuHeap *qh) {
  tValue v,s;
  tInt i;
  TRACE();
  EVAL(v,pvar);
  if(v.isQuExpr()) {
    EVAL(s,psub);
    ASSERT(s.type()==tINTEGER);
    quState *q;
    i=s.toInt();
    q=v.qustate();
    if(v.isEmpty())
      throw tError(errRANGE,"register is of lenght zero",this);
    if(i<0 || i>=q->mapbits())
      throw tError(errRANGE,"invalid qubit subscript",this);
    return tValue(q->newsubstring(1,i),basetype());
  }
  if(v.isQuCond()) {
    EVAL(s,psub);
    ASSERT(s.type()==tINTEGER);
    i=s.toInt();
    if(i<0 || i>=v.qucond()->elem())
      throw tError(errRANGE,"invalid qucond subscript",this);
    bitvec m=v.qucond()->clause(i);
    if(zero(m)) 
      return tValue(new quEmpty(*qh->state()),basetype());
    else
      return tValue(new quMask(*qh->state(),m),basetype());
  }
  ASSERT(v.ord()==nargs());
  sExpr *p;
  void *c;
  i=0;
  for_plist(p,psubs,c) {
    EVAL(s,p);
    if(s.toInt()>=v.dim())
      throw tError(errRANGE,"subscript out of range",this);
    i=i*v.dim()+s.toInt();
  }
  return v[i];
}

tValue sSubRange::eval(SymTable *loc,SymTable *gl,QuHeap *qh) {
  tValue v,e1,e2;
  tInt i,j,m,o,l;
  int s;
  quState *q;
  TRACE();
  EVAL(v,pvar);
  EVAL(e1,pexpr1);
  EVAL(e2,pexpr2);
  ASSERT(v.isQuExpr() && e1.isInt() && e2.isInt());
  i=e1.toInt();
  j=e2.toInt();
  if(isSet(flagRANGE)) {	// [e1..e2]
    if(i<=j) { 
      s=0; o=i; l=j-i+1;
    } else {
      s=1; o=j; l=i-j+1;
    }
  } else {			// [e1::e2]
    s=0; o=i; l=abs((int)j);
    if(j<-1) s=1;
  }
  q=v.qustate();
  m=q->mapbits();
  if(l==0 && o>=0 && o<=m)
    return tValue(new quEmpty(*qh->state()),basetype()); 
  if(m==0)
    throw tError(errRANGE,"register is of lenght zero",this);
  if(o<0 || l<1 || o+l>m)
    throw tError(errRANGE,"invalid quantum subregister",this);
if(s) ASSERT(0);
  if(s)
    return tValue(new quSwap(q->newsubstring(l,o)),basetype());
  else 
    return tValue(q->newsubstring(l,o),basetype());
} 

tValue sNeg::eval(SymTable *loc,SymTable *gl,QuHeap *qh) {
  tValue v;
  TRACE();
  EVAL(v,pexpr);
  if(ord()) {
    int i;
    for(i=0;i<v.elem();i++) {
      switch(v.basetype()) {
        case tINTEGER:      v.set(i,-v[i].toInt()); break;
        case tREAL:         v.set(i,-v[i].toReal()); break;
        case tCOMPLEX:      v.set(i,-v[i].toComplex()); break;
        default:            ASSERT(0);
      }
    }
    return v;
  }
  switch(v.basetype()) {
    case tINTEGER: 	return tValue(-v.toInt());
    case tREAL: 	return tValue(-v.toReal());
    case tCOMPLEX: 	return tValue(-v.toComplex());
    default: 		ASSERT(0);
  }
}

tValue sNot::eval(SymTable *loc,SymTable *gl,QuHeap *qh) {
  tValue v;
  TRACE();
  EVAL(v,pexpr);
  if(v.type().isBoolean())
    return v.toBool()==TRUE ? tValue(FALSE) : tValue(TRUE);
  if(v.type().isQuCond())
    return tValue(~v.toQuCond());
  ASSERT(0);
}

tValue sLength::eval(SymTable *loc,SymTable *gl,QuHeap *qh) {
  tValue v;
  TRACE();
  EVAL(v,pexpr);
  if(v.isQuExpr()) return tValue((tInt)v.qustate()->mapbits());
  if(v.isQuCond()) return tValue((tInt)v.qucond()->elem());
  return tValue((tInt)v.dim());
}

tValue sBinOp::eval(SymTable *loc,SymTable *gl,QuHeap *qh) {
  tValue e1,e2;
  TRACE();
  EVAL(e1,pexpr1);
  EVAL(e2,pexpr2);

  if(e1.ord()) {
    int i;
    if(e2.ord() && (e1.dim()!=e2.dim() || !e1.dim()))
      throw tError(errMATH,"unmatching dimensions",this);
    tValue v(type(),e1.dim());
    if(e2.ord() && object()==sMULT) {
      if(type().ord()) {
        int j,k;
        int d=e1.dim();
        int d1=e1.elem()/d;
        int d2=e2.elem()/d;
        for(i=0;i<d1;i++) 
          for(j=0;j<d2;j++)
            for(k=0;k<d;k++) {
              int ij=i*d2+j;
              v.set(ij,v[ij]+e1[i*d+k]*e2[k*d2+j]);
            }
      } else {
        for(i=0;i<e1.elem();i++) v=v+e1[i]*e2[i];
      }
      return v;
    }
    ASSERT(ord());
    if(object()==sDIV && e2.isZero())
      throw tError(errMATH,"division by zero",this);
    switch(object()) {
      case sADD:  for(i=0;i<v.elem();i++) v.set(i,e1[i]+e2[i]); break;
      case sSUB:  for(i=0;i<v.elem();i++) v.set(i,e1[i]-e2[i]); break;
      case sMULT: for(i=0;i<v.elem();i++) v.set(i,e1[i]*e2); break;
      case sDIV:  for(i=0;i<v.elem();i++) v.set(i,e1[i]/e2); break;
      default:	ASSERT(0);
    }
    return v;
  }

  #define RET(t,o) return tValue(e1.t() o e2.t())
  if(isArithOp()) {
    ASSERT(e1.isNumber() && e2.isNumber());
    ASSERT(object()!=sMOD || (e1.isInt() && e2.isInt()));
    if((object()==sMOD || object()==sDIV) && e2.isZero())
      throw tError(errMATH,"division by zero",this); 
    if(object()==sPOW) {
      if(e1.isZero() && e2.isZero()) throw tError(errMATH,"0^0 is undefined",this);
      if(type().isInt() && (e2.toInt())<0) throw tError(errMATH,"negative exponent in integer power",this);
      if(type().isReal() && (e1.toReal())<0 && !e2.isInt())
        throw tError(errMATH,"negative real base to non integer power",this);
    }
    if(type()==tINTEGER) 
      switch(object()) {
        case sADD:	RET(toInt,+);
        case sSUB:	RET(toInt,-);
        case sMULT:	RET(toInt,*);
        case sDIV:	RET(toInt,/);
        case sMOD:	RET(toInt,%);
        case sPOW:	
          if(e1.toInt()==2) 
            return tValue((tInt)1<<e2.toInt());
          else if(e1.toInt()==-1)
            return tValue((tInt)(e2.toInt()&1 ? -1 : 1));
          else 
            return tValue((tInt)pow((double)e1.toReal(),(int)e2.toInt()));
        default:	;
    };
    if(type()==tREAL) 
      switch(object()) {
        case sADD:	RET(toReal,+);
        case sSUB:	RET(toReal,-);
        case sMULT:	RET(toReal,*);
        case sDIV:	RET(toReal,/);
        case sPOW:	return tValue((tReal)pow(e1.toReal(),e2.toReal()));
        default:	;
    };
    if(type()==tCOMPLEX) 
      switch(object()) {
        case sADD:	RET(toComplex,+);
        case sSUB:	RET(toComplex,-);
        case sMULT:	RET(toComplex,*);
        case sDIV:	RET(toComplex,/);
        case sPOW:	return tValue((tComplex)pow(e1.toComplex(),e2.toComplex()));
        default:	;
    };
    ASSERT(0);
  };
  #undef RET
  
  #define RET(t,o) return e1.t() o e2.t() ? tValue(TRUE) : tValue(FALSE)
  if(isCompOp()) {
    if(object()==sLEEQ || object()==sLESS) {
      ASSERT(e1.isOrdered() && e2.isOrdered()); 
      if(e1.isInt() && e2.isInt()) { 
        if(object()==sLEEQ) RET(toInt,<=); else RET(toInt,<);
      } else {  
        if(object()==sLEEQ) RET(toReal,<=); else RET(toReal,<);
      }
    } else {
      if(e1.isQuExpr() || e2.isQuExpr()) {
        if(e1.isQuExpr() && e2.isQuExpr()) {
          if(!zero(e1.qustate()->mapmask() & e2.qustate()->mapmask()))
            throw tError(errRUN,"overlapping registers",this);
          if(e1.qustate()->mapbits()!=e2.qustate()->mapbits())
            throw tError(errRUN,"registers of different size",this);
          return regcomp(e1.qustate(),e2.qustate());
        } else {
          if(e1.isInt()) return regcomp(e2.qustate(),e1.toInt());
          if(e2.isInt()) return regcomp(e1.qustate(),e2.toInt());
          ASSERT(0);
        }
      }
      if(e1.isNumber() && e2.isNumber()) {
        if(e1.isInt() && e2.isInt()) { 
          if(object()==sEQUAL) RET(toInt,==); else RET(toInt,!=);
        };
        if(e1.isComplex() || e2.isComplex()) {
          if(object()==sEQUAL) RET(toComplex,==); else RET(toComplex,!=);
        };
        if(object()==sEQUAL) RET(toReal,==); else RET(toReal,!=);
      } else {
        ASSERT(e1.type()==e2.type());
        if(e1.isString()) {
          if(object()==sEQUAL) 
            RET(toString,==); 
          else 
            return e1.toString()==e2.toString() ? tValue(FALSE) : tValue(TRUE);
        }
      }
    }
    ASSERT(0);
  }
  #undef RET
  
  #define RET(t,o) return e1.t() o e2.t() ? tValue(TRUE) : tValue(FALSE)
  if(isLogOp() && type().isBoolean()) {
    ASSERT(e1.isBoolean() && e2.isBoolean());
    switch(object()) {
      case sAND: 	RET(toBool,&&);
      case sOR:		RET(toBool,||);
      case sXOR:	RET(toBool,!=);
      default:		;
    }
  }
  #undef RET

  if(isLogOp() && type().isQuCond()) {
    ASSERT(e1.isCond() && e2.isCond());
    switch(object()) {
      case sAND: 	return tValue(e1.toQuCond() & e2.toQuCond());
      case sOR:		return tValue(e1.toQuCond() | e2.toQuCond());
      case sXOR:	return tValue(e1.toQuCond() ^ e2.toQuCond());
      default:		;
    }
  }

  if(object()==sCONCAT) { 
    if(e1.isString() && e2.isString()) 
      return tValue(e1.toString()+e2.toString());
    if(e1.isQuExpr() && e2.isQuExpr()) {
      if(e1.isEmpty() && e2.isEmpty()) 
        return tValue(new quEmpty(*qh->state()),basetype());
      if(e1.isEmpty()) return tValue(e2.qustate()->newclone(),basetype());
      if(e2.isEmpty()) return tValue(e1.qustate()->newclone(),basetype());
      bitvec v1=e1.qustate()->mapmask();
      bitvec v2=e2.qustate()->mapmask();
      if(!zero(v1&v2)) throw tError(errRANGE,"quantum registers overlap",this);
      quState *pq=new quCombState(e1.qustate()->newclone(),e2.qustate()->newclone(),1);
      return tValue(pq,basetype());
    }
  }
  ASSERT(0);
}

tValue sFunctCall::eval(SymTable *loc,SymTable *gl,QuHeap *qh) {
  tValue v;
  SymTab sym;
  sRoutDef *d;
  sExpr *p;
  sDef *q;
  void *cp,*cq;
  
  TRACE();
  d=(sRoutDef*)gl->getDef(id());
  ASSERT(d && d->isFunctDef());
  for_pplist(p,ppar,cp,q,d->args(),cq,p && q) {
    EVAL(v,p);
    if(sym.put(q,v.conv(q->type()))) throw tError(errINT,"argument binding failed",this);
  }
  try {
    d->invoke(&sym,gl,qh);
    throw tError(errGEN,"function didn't return a value",this);
  } catch(tValue r) {
    if(!r.isExpr()) throw tError(errINT,"invalid return value",this);
    return r;
  }
}



tValue sBaseFunct::eval(SymTable *loc,SymTable *gl,QuHeap *qh) {
  tValue v;
  tInt n=0;
  tReal r=0.0;
  tComplex z;
  TRACE();
  EVAL(v,pexpr);
  if(isTypecast()) {
    switch(object()) {
      case sSTRING:
        return tValue(v.str());
      case sCOMPLEX:
        return tValue(v.toComplex());
      case sREAL:
        return tValue(v.toReal());
      case sINT:
        return tValue(v.toInt());
      default:
        ASSERT(0);
    }
  }
  if(v.isInt()) {
    n=v.toInt();
    r=v.toReal();
    z=v.toComplex();
  } else if(v.isReal()) {
    r=v.toReal();
    z=v.toComplex();
  } else if(v.isComplex()) {
    z=v.toComplex();
  }
  if(type().isInt()) {
    ASSERT(v.isNumber());
    switch(object()) {
      case sFLOOR  :  return tValue((tInt)floor(r));
      case sCEIL   :  return tValue((tInt)ceil(r));
      case sABS    :  return tValue((tInt) n>=0 ? n : -n);
      case sINOT   :  return tValue((tInt) ~n);
      default      :  ;

    }
  };
  if(type().isReal()) {
    ASSERT(v.isNumber());
    switch(object()) {
      case sEXP    :  return tValue((tReal)exp(r));
      case sSIN    :  return tValue((tReal)sin(r));
      case sCOS    :  return tValue((tReal)cos(r));
      case sTAN    :  return tValue((tReal)tan(r));
      case sCOT    :  return tValue((tReal)1./tan(r));
      case sSINH   :  return tValue((tReal)sinh(r));
      case sCOSH   :  return tValue((tReal)cosh(r));
      case sTANH   :  return tValue((tReal)tanh(r));
      case sCOTH   :  return tValue((tReal)1./tanh(r));
      case sABS    :  return tValue((tReal)abs(z));
      case sRE     :  return tValue((tReal)z.real());
      case sIM     :  return tValue((tReal)z.imag());
      case sCONJ   :  return v;
      case sSQRT   :
        if(r<0) throw tError(errMATH,"real square root of negative number",this);  
        return tValue((tReal)sqrt(r));
      default      :  ;
    }
  };
  if(type().isComplex()) {
    ASSERT(v.isNumber());
    switch(object()) {
      case sEXP    :  return tValue((tComplex)exp(z));
      case sSIN    :  return tValue((tComplex)sin(z));
      case sCOS    :  return tValue((tComplex)cos(z));
      case sTAN    :  return tValue((tComplex)sin(z)/cos(z));
      case sCOT    :  return tValue((tComplex)cos(z)/sin(z));
      case sSINH   :  return tValue((tComplex)sinh(z));
      case sCOSH   :  return tValue((tComplex)cosh(z));
      case sTANH   :  return tValue((tComplex)sinh(z)/cosh(z));
      case sCOTH   :  return tValue((tComplex)cosh(z)/sinh(z));
      case sCONJ   :  return tValue((tComplex)conj(z));
      case sSQRT   :  return tValue((tComplex)sqrt(z));
      default      :  ;
    }
  };
  ASSERT(0);
}

#ifndef _builtin_h
  unsigned long gcd(unsigned long a,unsigned long b) {
    unsigned long m=a%b;
    if(m) return gcd(b,m);
    return b;
  }
  unsigned long lcm(unsigned long a,unsigned long b) {
    return a/gcd(a,b)*b;
  }
#endif

  
tValue sListFunct::eval(SymTable *loc,SymTable *gl,QuHeap *qh) {
  sExpr *p;
  void *c;
  int i;
  int argc=pexpr->n();
  tValue v[argc];
  tInt n[argc];
  tReal r[argc];
  tComplex z[argc];
  tInt rn;
  tReal rr;
  TRACE();
  i=0;
  for_plist(p,pexpr,c) {
    EVAL(v[i],p);
    if(v[i].isInt()) {
      n[i]=v[i].toInt();
      r[i]=v[i].toReal();
      z[i]=v[i].toComplex();
    }
    if(v[i].isReal()) {
      r[i]=v[i].toReal();
      z[i]=v[i].toComplex();
    }
    if(v[i].isComplex()) {
      z[i]=v[i].toComplex();
    }
    i++;
  }
  switch(object()) {
    case sLOG:
      ASSERT(v[0].isNumber() && (!pexpr2 || v[1].isNumber()));
      if(type().isComplex()) {
        if(pexpr2)
          return tValue((tComplex)log(z[0])/log(z[1]));
        else
          return tValue((tComplex)log(z[0]));
      } else {
        if(r[0]<=0 || (pexpr2 && r[1]<=0))
	  throw tError(errMATH,"real logarithm of non positive number",this);
        if(pexpr2)
          return tValue((tReal)log(r[0])/log(r[1]));
        else
          return tValue((tReal)log(r[0]));
      }
      break;
    case sRANDOM:
      ASSERT(argc==0 && isGlobal());
      return qc_drand();
    case sMIN:
    case sMAX:
      ASSERT(argc>0);
      if(type().isInt()) {
        rn=n[0];
        for(i=1;i<argc;i++) {
          if(object()==sMIN && rn>n[i]) rn=n[i];
          if(object()==sMAX && rn<n[i]) rn=n[i];
        }
        return tValue((tInt)rn);
      } else {
        rr=r[0];
        for(i=1;i<argc;i++) {
          if(object()==sMIN && rr>r[i]) rr=r[i];
          if(object()==sMAX && rr<r[i]) rr=r[i];
        }
        return tValue((tReal)rr);
      }
      break;
    case sIAND:
    case sIOR:
    case sIXOR:
    case sGCD:
    case sLCM:
      ASSERT(argc>0);
      rn=n[0];
      for(i=1;i<argc;i++) {
        if(object()==sIAND) rn&=n[i];
        if(object()==sIOR) rn|=n[i];
        if(object()==sIXOR) rn^=n[i];
        if(object()==sGCD) rn=gcd(n[i],rn);
        if(object()==sLCM) rn=lcm(n[i],rn);
      }
      return tValue((tInt)rn);
    case sBIT:
      ASSERT(argc==2);
      if((n[0]>>n[1])&1)
        return tValue(TRUE);
      else
        return tValue(FALSE);
    default: ;
      ASSERT(isTensor());
      int order=object()-sSCALAR;
      int dim=tensordim(order,argc);
      ASSERT(dim);
      tValue t(type(),dim);
      for(i=0;i<t.elem();i++) t.set(i,v[i]);
      return t;
  }
  ASSERT(0); 
  return tValue(); 
}
