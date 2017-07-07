/**********************************************************************

This file is part of the Quantum Computation Language QCL.

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/


#pragma implementation

#include "extern.h"
#include "syntax.h"
#include "error.h"
#include "operator.h"
#include "quheap.h"
#include "options.h"

#define ROUTINE(n) int n(const sRoutDef *def,const SymTable *loc,int inv)
#define EXTERR(s) throw tError(errEXT,s)
#define GETVAL(s) tValue *value; value=loc->getRef(s); if(!value) EXTERR("parameter "+string(s)+" not found");;
#define PAR_INT(v,s) int v; { GETVAL(s); if(!value->isInt()) EXTERR("integer expected"); v=value->toInt(); }
#define PAR_REAL(v,s) tReal v; { GETVAL(s); if(!value->isReal()) EXTERR("real expected"); v=value->toReal(); }
#define PAR_COMPLEX(v,s) tComplex v; { GETVAL(s); if(!value->isComplex()) EXTERR("complex expected"); v=value->toComplex(); }
#define PAR_QUSTATE(v,s) quState* v; { GETVAL(s); if(!value->isQuExpr()) EXTERR("quantum expression expected"); v=value->qustate(); }
#define PAR_VECTOR(v,s) tValue v; { GETVAL(s); if(value->type()!=tType(tINTEGER,1)) EXTERR("int vector expected"); v=*value; }
#define PAR_MATRIX(v,s) tValue v; { GETVAL(s); if(value->type()!=tType(tCOMPLEX,2)) EXTERR("complex matrix expected"); v=*value; }
#define STOP while(*((int*)0));

//////////////////////////////////////////////////////////////////////
//!
//! /* generic matrix operator: |i> -> sum_j u[i,j] |j> */
//!
//! extern operator Matrix(complex matrix u,qureg q);
//!
//! /* obsolete matrix operators */
//!
//! extern operator Matrix2x2(
//!   complex u00,complex u01,
//!   complex u10,complex u11,
//! qureg q);
//!
//! extern operator Matrix4x4(
//!   complex u00,complex u01,complex u02,complex u03,
//!   complex u10,complex u11,complex u12,complex u13,
//!   complex u20,complex u21,complex u22,complex u23,
//!   complex u30,complex u31,complex u32,complex u33,
//! qureg q);
//!
//! extern operator Matrix8x8(
//!   complex u00,complex u01,complex u02,complex u03,
//!   complex u04,complex u05,complex u06,complex u07,
//!   complex u10,complex u11,complex u12,complex u13,
//!   complex u14,complex u15,complex u16,complex u17,
//!   complex u20,complex u21,complex u22,complex u23,
//!   complex u24,complex u25,complex u26,complex u27,
//!   complex u30,complex u31,complex u32,complex u33,
//!   complex u34,complex u35,complex u36,complex u37,
//!   complex u40,complex u41,complex u42,complex u43,
//!   complex u44,complex u45,complex u46,complex u47,
//!   complex u50,complex u51,complex u52,complex u53,
//!   complex u54,complex u55,complex u56,complex u57,
//!   complex u60,complex u61,complex u62,complex u63,
//!   complex u64,complex u65,complex u66,complex u67,
//!   complex u70,complex u71,complex u72,complex u73,
//!   complex u74,complex u75,complex u76,complex u77,
//! qureg q);

ROUTINE(ext_matrix) {
  int i,j,k,n,dim;
  PAR_QUSTATE(q,"q");
  tValue v;
  
  n=q->mapbits();
  dim=(1 << n);
  if(!loc->getRef(sdec(dim-1,"u%ld")+sdec(dim-1)) || loc->getRef(string("u")+sdec(dim)+sdec(dim)))
    EXTERR("illegal register size for matrix operator");
  tComplex u[dim][dim];
  term* t[dim];
  for(i=0;i<dim;i++) for(j=0;j<dim;j++) {
    v=loc->getVal(sdec(j,"u%ld")+sdec(i));
    if(!v.isComplex()) EXTERR("invalid matrix element");
    if(inv) u[j][i]=conj(v.toComplex()); else u[i][j]=v.toComplex();
  }
  for(i=0;i<dim;i++) for(j=0;j<dim;j++) {
    tComplex z=0;
    for(k=0;k<dim;k++) z+=u[i][k]*conj(u[j][k]);
    if(i==j) z-=1;
    if(abs(z)>EPSILON_MATRIX)
      EXTERR("matrix operator is not unitary");
  }  
  for(i=0;i<dim;i++) {
    k=0;
    t[i]=new term[dim+1];
    for(j=0;j<dim;j++) {
      if(u[i][j]==tComplex(0)) continue;
      t[i][k++]=term(bitvec(n,j),u[i][j]);
    }
  }
  opMatrix(n,&t[0]).apply(*q);
  for(i=0;i<dim;i++) qcl_delarray(t[i]);
  return 0;
}

ROUTINE(ext_genmatrix) {
  int i,j,k,n,dim;
  PAR_QUSTATE(q,"q");
  PAR_MATRIX(v,"u");
  tComplex z;
  n=q->mapbits();
  dim=(1 << n);
  if(dim!=v.dim())
    EXTERR("illegal register size for matrix operator");
  for(i=0;i<dim;i++) for(j=0;j<dim;j++) {
    z=0;
    for(k=0;k<dim;k++) 
      z+=v[i*dim+k].toComplex()*conj(v[j*dim+k].toComplex());
    if(i==j) z-=1;
    if(abs(z)>EPSILON_MATRIX)
      EXTERR("matrix operator is not unitary");
  }  
  term* t[dim];
  for(i=0;i<dim;i++) {
    k=0;
    t[i]=new term[dim+1];
    for(j=0;j<dim;j++) {
      z = inv ? conj(v[i*dim+j].toComplex()) : v[j*dim+i].toComplex();
      if(z==tComplex(0)) continue;
      t[i][k++]=term(bitvec(n,j),z);
    }
  }
  opMatrix(n,&t[0]).apply(*q);
  for(i=0;i<dim;i++) qcl_delarray(t[i]);
  return 0;
}

//////////////////////////////////////////////////////////////////////
//!
//! /* generic permutation operator: |i> -> |p[i]> */
//!
//! extern qufunct Perm(int vector p,qureg q);
//!
//! /* obsolete permutation operators */
//!
//! extern qufunct Perm2(int p0 ,int p1 ,qureg q);
//!
//! extern qufunct Perm4(int p0 ,int p1 ,int p2 ,int p3 ,qureg q);
//!
//! extern qufunct Perm8(
//!   int p0 ,int p1 ,int p2 ,int p3 ,int p4 ,int p5 ,int p6 ,int p7 ,
//! qureg q);
//!
//! extern qufunct Perm16(
//!   int p0 ,int p1 ,int p2 ,int p3 ,int p4 ,int p5 ,int p6 ,int p7 ,
//!   int p8 ,int p9 ,int p10,int p11,int p12,int p13,int p14,int p15,
//! qureg q);
//!
//! extern qufunct Perm32(
//!   int p0 ,int p1 ,int p2 ,int p3 ,int p4 ,int p5 ,int p6 ,int p7 ,
//!   int p8 ,int p9 ,int p10,int p11,int p12,int p13,int p14,int p15,
//!   int p16,int p17,int p18,int p19,int p20,int p21,int p22,int p23,
//!   int p24,int p25,int p26,int p27,int p28,int p29,int p30,int p31,
//! qureg q);
//!
//! extern qufunct Perm64(
//!   int p0 ,int p1 ,int p2 ,int p3 ,int p4 ,int p5 ,int p6 ,int p7 ,
//!   int p8 ,int p9 ,int p10,int p11,int p12,int p13,int p14,int p15,
//!   int p16,int p17,int p18,int p19,int p20,int p21,int p22,int p23,
//!   int p24,int p25,int p26,int p27,int p28,int p29,int p30,int p31,
//!   int p32,int p33,int p34,int p35,int p36,int p37,int p38,int p39,
//!   int p40,int p41,int p42,int p43,int p44,int p45,int p46,int p47,
//!   int p48,int p49,int p50,int p51,int p52,int p53,int p54,int p55,
//!   int p56,int p57,int p58,int p59,int p60,int p61,int p62,int p63,
//! qureg q);

ROUTINE(ext_perm) {
  int i,n,dim;
  PAR_QUSTATE(q,"q");
  tValue v;
  
  n=q->mapbits();
  dim=(1 << n);
  if(!loc->getRef(sdec(dim-1,"p%ld")) || loc->getRef(sdec(dim,"p%ld")))
    EXTERR("illegal register size for permutation operator");
  int p[dim];
  int pp[dim];
  term t[dim];
  for(i=0;i<dim;i++) {
    v=loc->getVal(sdec(i,"p%ld"));
    if(!v.isInt() || v.toInt() < 0 || v.toInt() >= dim) 
      EXTERR("invalid permutation element");
    p[i]=v.toInt();
  }
  for(i=0;i<dim;i++) pp[i]=-1;
  for(i=0;i<dim;i++) pp[p[i]]=i;
  for(i=0;i<dim;i++) {
    if(pp[i]==-1) EXTERR("no permutation"); 
    if(inv) { 
      t[i]=term(bitvec(n,pp[i]),1); 
    } else {
      t[i]=term(bitvec(n,p[i]),1);
    }
  }
  opPermutation(n,t).apply(*q);
  return 0;
}

ROUTINE(ext_genperm) {
  int i,n,dim;
  PAR_QUSTATE(q,"q");
  PAR_VECTOR(v,"p");
  
  n=q->mapbits();
  dim=(1 << n);
  if(dim!=v.dim())
    EXTERR("illegal register size for permutation operator");
  int p[dim];
  term t[dim];
  for(i=0;i<dim;i++) p[i]=-1;
  for(i=0;i<dim;i++) p[v[i].toInt()]=i;
  for(i=0;i<dim;i++) {
    if(p[i]==-1) EXTERR("no permutation"); 
    if(inv) { 
      t[i]=term(bitvec(n,p[i]),1); 
    } else {
      t[i]=term(bitvec(n,v[i].toInt()),1);
    }
  }
  opPermutation(n,t).apply(*q);
  return 0;
}

//////////////////////////////////////////////////////////////////////
//!
//! /* standard unconditional single-qubit gates */
//!
//! extern operator H(qureg q);
//! extern qufunct  NOT(qureg q);
//! extern qufunct  X(qureg q);
//! extern operator Y(qureg q);
//! extern operator Z(quconst q);
//! extern operator S(quconst q);
//! extern operator T(quconst q);
//!
//! operator Pauli(int i,qureg q) {   // Pauli Matrices
//!   if i==1 { X(q); }
//!   if i==2 { Y(q); }
//!   if i==3 { Z(q); }
//!   if i<0 or i>3 { exit "Unknown Pauli Gate"; }
//! }
//!
//! /* The Mix-operator can be any operator which transforms */ 
//! /* the state |0> into an even superposition of all base- */
//! /* vector with phase 0, i.e. |0> -> 1/sqrt(N) sum |i>    */
//!
//! operator Mix(qureg q) {           // Generic Mix-Operator
//!   H(q);                           // using the Hadamard 
//! }                                 // transform

ROUTINE(ext_bit) {
  int i;
  quState *qbit;
  PAR_QUSTATE(q,"q");
  opBit *op;
  tComplex I(0,1);
  tComplex sg= inv ? -1 : 1;
  char c=(def->id())[0];
  if(def->id().length()!=1) c='?';
  switch(c) {
    case 'H': op=new opBit(1,1,1,-1,sqrt(0.5)); break;
    case 'X': op=new opBit(0,1,1,0); 		break;
    case 'Y': op=new opBit(0,-I,I,0); 		break;
    case 'Z': op=new opBit(1,0,0,-1); 		break;
    case 'S': op=new opBit(1,0,0,sg*I);		break;
    case 'T': op=new opBit(1,0,0,sqrt(0.5)+sg*sqrt(0.5)*I); break;
    case '?':
    default: EXTERR("unknown single qubit operator "+def->id());
  } 
  for(i=0;i<q->mapbits();i++) {
    qbit=q->newsubstring(1,i);
    op->apply(*qbit);
    qcl_delete(qbit);
  };
  qcl_delete(op);
  return 0;
}

ROUTINE(ext_x) {
  PAR_QUSTATE(q,"q");
  opCNot(q->mapbits(),0).apply(*q);
  return 0;
}

/////////////////////////////////////////////////////////////////////////
//!
//! /* unconditional controlled-not gate */
//!
//! extern qufunct CNOT(qureg q,quconst c);

ROUTINE(ext_cnot) {
  PAR_QUSTATE(q,"q");
  PAR_QUSTATE(c,"c");
  quCombState cb(q,c);
  opCNot(q->mapbits(),c->mapbits()).apply(cb);
  return 0;
}

///////////////////////////////////////////////////////////////////
//!
//! /* The conditional versions of Not and CNot can either  */
//! /* use the built-in conditional Not-gate or the generic */
//! /* unconditional NOT and CNOT gates                     */   
//!
//! // extern cond qufunct Not(qureg q);        // conditional Not
//! cond qufunct Not(qureg q) {                 // generic NOT/CNOT
//!   quconst e = cond;
//!   if #e>0 { CNOT(q,e); } else { NOT(q); }
//! }
//! 
//! cond qufunct CNot(qureg q,quconst c) {
//!   quconst e = cond;
//!   // if c and e { Not(q); };                // conditional Not
//!   CNOT(q,c & e);                            // generic CNOT
//! };

ROUTINE(ext_not) {
  PAR_QUSTATE(q,"q");
  PAR_QUSTATE(c,CONDID);
  quCombState cb(q,c);
  opCNot(q->mapbits(),c->mapbits()).apply(cb);
  return 0;
}

//////////////////////////////////////////////////////////////////////
//!
//! /* unconditional V-gate (controlled phase rotation)     */
//!
//! extern operator V(real phi,quconst q);

ROUTINE(ext_cphase) {
  PAR_REAL(phi,"phi");
  PAR_QUSTATE(q,"q");
  if(inv) phi=-phi;
  opCPhase(q->mapbits(),phi).apply(*q);
  return 0;
}

//////////////////////////////////////////////////////////////////////
//!
//! /* The conditional versions of Phase and CPhase can     */
//! /* either use the built-in conditional Phase-gate or    */
//! /* or the unconditional V-gate                          */
//!
//! // extern cond operator Phase(real phi);    // conditional Phase
//! cond operator Phase(real phi) {             // V-gate
//!   quconst c = cond;
//!   if #c>0 { V(phi,c); }
//! }
//!
//! cond operator CPhase(real phi,quconst q) {
//!   quconst e = cond;
//!   // if q and e { Phase(phi); }             // conditional Phase
//!   V(phi,q & e);                             // V-gate
//! }

ROUTINE(ext_phase) {
  PAR_REAL(phi,"phi");
  PAR_QUSTATE(q,CONDID);
  if(inv) phi=-phi;
  opCPhase(q->mapbits(),phi).apply(*q);
  return 0;
}


//////////////////////////////////////////////////////////////////////
//!
//! /* obsolete single qubit rotation (period 4*pi) */
//!
//! extern operator Rot(real theta,qureg q);

ROUTINE(ext_rot) {
  PAR_REAL(theta,"theta");
  PAR_QUSTATE(q,"q");
  if(q->mapbits()!=1) EXTERR("Only single qubits can be rotated");
  if(inv) theta=-theta;
  opU2(theta).apply(*q);
  return 0;
}


//////////////////////////////////////////////////////////////////////
//!
//! /* Square root of Not */
//!
//! extern operator SqrtNot(qureg q);

ROUTINE(ext_sqrtnot) {
  int i;
  quState *qbit;
  PAR_QUSTATE(q,"q");
  int sg= inv ? -1 : 1;
  tComplex a(sqrt(0.5),sqrt(0.5)*sg);
  tComplex b(sqrt(0.5),-sqrt(0.5)*sg);
  opBit op(a,b,b,a);
  for(i=0;i<q->mapbits();i++) {
    qbit=q->newsubstring(1,i);
    op.apply(*qbit);
    qcl_delete(qbit);
  };
  return 0;
}


//////////////////////////////////////////////////////////////////////
//!
//! /* Single qubit rotation about X-axis */
//!
//! extern operator RotX(real theta,qureg q);

ROUTINE(ext_rotx) {
  PAR_REAL(theta,"theta");
  PAR_QUSTATE(q,"q");
  if(q->mapbits()!=1) EXTERR("Only single qubits can be rotated");
  if(inv) theta=-theta;
  double cs=cos(theta/2);
  double si=sin(theta/2);
  opBit(cs,complx(0,-si),complx(0,-si),cs).apply(*q);
  return 0;
}


//////////////////////////////////////////////////////////////////////
//!
//! /* Single qubit rotation about Y-axis */
//!
//! extern operator RotY(real theta,qureg q);

ROUTINE(ext_roty) {
  PAR_REAL(theta,"theta");
  PAR_QUSTATE(q,"q");
  if(q->mapbits()!=1) EXTERR("Only single qubits can be rotated");
  if(inv) theta=-theta;
  double cs=cos(theta/2);
  double si=sin(theta/2);
  opBit(cs,-si,si,cs).apply(*q);
  return 0;
}


//////////////////////////////////////////////////////////////////////
//!
//! /* Single qubit rotation about Z-axis */
//!
//! extern operator RotZ(real theta,qureg q);

ROUTINE(ext_rotz) {
  PAR_REAL(theta,"theta");
  PAR_QUSTATE(q,"q");
  if(q->mapbits()!=1) EXTERR("Only single qubits can be rotated");
  if(inv) theta=-theta;
  complx d=exp(complx(0,-0.5*theta));
  opBit(d,0,0,conj(d)).apply(*q);
  return 0;
}




//////////////////////////////////////////////////////////////////////
//!
//! extern qufunct ModExp(int n,int x,quconst a,quvoid b);

ROUTINE(ext_modexp) {
  PAR_INT(n,"n");
  PAR_INT(x,"x");
  PAR_QUSTATE(a,"a");
  PAR_QUSTATE(b,"b");
  quCombState cb(a,b); 
  opEXPN(a->mapbits(),b->mapbits(),x,n).apply(cb);
  return 0;
}

//////////////////////////////////////////////////////////////////////
//!
//! /* The Fanout operator is used internally for scratch  */
//! /* space management. If you provide your own version,  */
//! /* make sure it doesn't use local quscratch registers. */
//!
//! /* generic Fanout operator                             */
//!
//! extern cond qufunct Fanout(quconst a,quvoid b);
//! 
//! /* alternative implementation; comment out if you want */
//! /* an explicit decomposition using CNot gates          */
//! /*
//! cond qufunct Fanout(quconst a,quvoid b) {
//!   int i;
//!   if #a!=#b { exit "fanout arguments must be of equal size"; }
//!   for i=0 to #a-1 { CNot(b[i],a[i]); }
//! }
//! */
//!

class opFANOUT : public opGate {
  int inv;
  int enable;
public:
  opFANOUT(int n,int e,int i) : opGate(2*n+e) { inv=i; enable=e; }
  virtual term funct(const bitvec& v) const { 
    int n=(bits()-enable)/2;
    bitvec a(v.getbits(0,n));
    bitvec b(v.getbits(n,n));
    if(enable) {
      bitvec e(v.getbits(2*n,enable));
      if(zero(~e)) b^=a;
      a+=b; a+=e;
    } else {
      b^=a;
      a+=b;
    }
    return term(a,1.0);
  };
  virtual opOperator *newclone() const { 
    return new opFANOUT((bits()-enable)/2,enable,inv); 
  }
};

ROUTINE(ext_fanout) {
  PAR_QUSTATE(a,"a");
  PAR_QUSTATE(b,"b");
  PAR_QUSTATE(c,CONDID);
  int na,nb,nc;
  bitvec ma,mb,mc;
  na=a->mapbits();
  ma=a->mapmask();
  nb=b->mapbits();
  mb=b->mapmask();
  nc=c->mapbits();
  mc=c->mapmask();
  if(na!=nb || !zero(ma & mb)) 
    EXTERR("fanout arguments must be of equal size");
  if(!zero((ma|mb)&mc)) 
    EXTERR("fanout overlapping quantum condition");
  quCombState cb(a,b);
  if(nc) {
    quCombState cb2(&cb,c);
    opFANOUT(na,nc,inv).apply(cb2);
  } else { 
    opFANOUT(na,0,inv).apply(cb);
  }
  return 0;
}
  
//////////////////////////////////////////////////////////////////////
//!
//! /* generic Swap operator                               */
//!
//! extern cond qufunct Swap(qureg a,qureg b);
//!
//! /* alternative implementation; comment out if you want */
//! /* an explicit decomposition using CNot gates          */
//! /*
//! cond qufunct Swap(qureg a,qureg b) {
//!   int i;
//!   if #a!=#b { exit "swap arguments must be of equal size"; }
//!   for i=0 to #a-1 {
//!     CNot(b[i],a[i]);
//!     CNot(a[i],b[i]);
//!     CNot(b[i],a[i]);
//!   }
//! }
//! */

class opSWAP : public opGate {
  int inv;
  int enable;
public:
  opSWAP(int n,int e,int i) : opGate(2*n+e) { inv=i; enable=e; }
  virtual term funct(const bitvec& v) const { 
    int n=(bits()-enable)/2;
    bitvec a(v.getbits(0,n));
    bitvec b(v.getbits(n,n));
    if(enable) {
      bitvec e(v.getbits(2*n,enable));
      if(!zero(~e)) return term(v,1.0);
      return term(b+a+e,1.0);
    }
    return term(b+a,1.0);
  };
  virtual opOperator *newclone() const { 
    return new opSWAP((bits()-enable)/2,enable,inv); 
  }
};

ROUTINE(ext_swap) {
  PAR_QUSTATE(sa,"a");
  PAR_QUSTATE(sb,"b");
  PAR_QUSTATE(c,CONDID);
  int na,nb,nc;
  bitvec ma,mb,mc;
  na=sa->mapbits();
  ma=sa->mapmask();
  nb=sb->mapbits();
  mb=sb->mapmask();
  nc=c->mapbits();
  mc=c->mapmask();
  if(na!=nb || !zero(ma & mb)) 
    EXTERR("swap arguments must be of equal size");
  quCombState cb(sa,sb); 
  if(nc) {
    quCombState cb2(&cb,c);
    opSWAP(na,nc,0).apply(cb2);
  } else {
    opSWAP(na,0,0).apply(cb);
  }
  return 0;
}


RoutTableEntry ExtRoutTable[] = {
 { &ext_fanout,FANOUTID },
 { &ext_swap,SWAPID },
 { &ext_matrix,"Matrix2x2" },
 { &ext_matrix,"Matrix4x4" },
 { &ext_matrix,"Matrix8x8" },
 { &ext_genmatrix,"Matrix" },
 { &ext_perm,"Perm2" },
 { &ext_perm,"Perm4" },
 { &ext_perm,"Perm8" },
 { &ext_perm,"Perm16" },
 { &ext_perm,"Perm32" },
 { &ext_perm,"Perm64" },
 { &ext_genperm,"Perm" },
 { &ext_not,"Not" },
 { &ext_cnot,"CNOT" },
 { &ext_phase,"Phase" },
 { &ext_cphase,"V" },
 { &ext_bit,"H" },
 { &ext_x,"NOT" },
 { &ext_x,"X" },
 { &ext_bit,"Y" },
 { &ext_bit,"Z" },
 { &ext_bit,"S" },
 { &ext_bit,"T" },
 { &ext_rot,"Rot" },
 { &ext_rotx,"RotX" },
 { &ext_roty,"RotY" },
 { &ext_rotz,"RotZ" },
 { &ext_sqrtnot,"SqrtNot" },
 { &ext_modexp,"ModExp" },
 { 0, "" }
};

//////////////////////////////////////////////////////////////////////
//!
//! /* Mathematical constants */
//!
//! const pi = 3.141592653589793238462643383279502884197;
//! const E  = 2.718281828459045235360287471352662497757;
//! const I  = (0,1);
//!
//! /* Auxillary functions */
//! 
//! qufunct set(int n,qureg q) {
//!   int i;
//!   for i=0 to #q-1 {
//!     if bit(n,i) { Not(q[i]); }
//!   }
//! }
//!
//! /* Randomize register (apply random single qubit rotations) */
//!
//! procedure randomize(qureg q) {
//!   int i;
//!   for i=0 to #q-1 {
//!     RotZ(4*pi*random(),q[i]);
//!     RotY(4*pi*random(),q[i]);
//!     RotZ(4*pi*random(),q[i]);
//!   }
//! }
