/**********************************************************************

This file is part of the Quantum Computation Language QCL.

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/


#ifndef TYPES_H
#define TYPES_H 1

#pragma interface

#include "qc.h"
#include "cond.h"

#include <string>

string sdec(long n,const char *format="%ld");

#ifdef QCL_DEBUG
  #define qcl_delete(p) { \
    if(!p) { \
      cerr << "qcl_delete warning in " << __FILE__ << ":" << __LINE__<<  "\n"; \
    } else { delete p; p=0; } \
  }
  #define qcl_delarray(p) { \
    if(!p) { \
      cerr << "qcl_delarray warning in " << __FILE__ << ":" << __LINE__ << "\n"; \
    } else { delete[] p; p=0; } \
  }
  extern int n_object;
  extern int n_value;
  #define INCOBJ // n_object++
  #define DECOBJ // n_object--
  #define INCVAL // n_value++
  #define DECVAL // n_value--
#else
  #define qcl_delete(p) { if(p) { delete p; p=0; } }
  #define qcl_delarray(p) { if(p) { delete[] p; p=0; } }
  #define INCOBJ
  #define DECOBJ
  #define INCVAL
  #define DECVAL
#endif

typedef long   tInt;
typedef double tReal;
typedef complx tComplex;

#define NOINDENT (-1)
#define INDENT 0

extern const char *FALSE_STR;
extern const char *TRUE_STR;
extern const char *BASETYPE_STR[];

typedef string tId;

enum boolean { FALSE = 0, TRUE = 1 };

enum BaseType { tUNDEF, tERROR, tVOID, tQUOP, tQUFUN,
		tBOOLEAN, tINTEGER, tREAL, tCOMPLEX, tSTRING,
                tQUCONST, tQUREG, tQUVOID, tQUSCR, tQUCOND };

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MAX3(a,b,c) MAX(a,MAX(b,c))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MIN3(a,b,c) MIN(a,MIN(b,c))
                
// Class Hierarchy

enum ObjType { 
sVOID			= 0,

sOBJECT			= 1000, 
  sLIST			= 1010, 
  sOBJLIST		= 1020,

  sEXPR			= 2000, 
  sEXPRLIST		= 2010,
    sCONST		= 2020, 
    sVAR		= 2030, 
    sSUBSCRIPT		= 2040, 
    sSUBRANGE		= 2050, 
    sFUNCTCALL		= 2060, 
    sUNOP		= 2100, 
      sNEG		= 2110,
      sNOT		= 2120, 
      sLENGTH		= 2130, 
    sBINOP		= 2200, 
      sADD		= 2210,	// Arithmetic OPs
      sSUB		= 2211,
      sMULT		= 2212,
      sDIV		= 2213,
      sMOD		= 2214,
      sPOW		= 2215, 
      sLESS		= 2220,	// Comparators
      sEQUAL		= 2221,
      sLEEQ		= 2222,
      sNOTEQ		= 2223,
      sAND		= 2230,	// Logical OPs
      sOR		= 2231, 
      sXOR		= 2232, 
      sCONCAT		= 2240,	// Others
    sBASEFUNCT		= 2300,
      sEXP		= 2301, 
      sSIN		= 2302, // Trigonometric Functions
      sCOS		= 2303,
      sTAN		= 2304,
      sCOT		= 2305,
      sSINH		= 2306,
      sCOSH		= 2307,
      sTANH		= 2308,
      sCOTH		= 2309, 
      sABS		= 2320, // Complex -> Real
      sRE		= 2321,
      sIM		= 2322,
      sCONJ		= 2330, // Others
      sFLOOR		= 2331,
      sCEIL		= 2332,
      sSQRT		= 2333,
      sINOT		= 2340, // Bitwise NOT
      sINT		= 2350, // explicit typecasts
      sREAL		= 2351,
      sCOMPLEX		= 2352,
      sSTRING		= 2353,
      
    sLISTFUNCT		= 2400,
      sLOG		= 2401,
      sRANDOM		= 2402,
      sMIN		= 2403,
      sMAX		= 2404,
      sGCD		= 2405,
      sLCM		= 2406,
      sBIT		= 2407,
      sIAND		= 2410, // Bitwise OPs
      sIOR		= 2411,
      sIXOR		= 2412,
      sSCALAR		= 2500, // Tensors
      sVECTOR		= 2501,
      sMATRIX		= 2502,
      sTENSOR3		= 2503,
      sTENSOR4		= 2504,
      sTENSOR5		= 2505,
      sTENSOR6		= 2506,
      sTENSOR7		= 2507,
      sTENSOR8		= 2508,
      sTENSOR9		= 2509,

  sSTMT			= 3000,
  sSTMTLIST		= 3010,
    sCALL		= 3020,
    sASSIGN		= 3040,
    sFOR		= 3060,
    sIF			= 3070,
    sLOOP		= 3080,
      sWHILE		= 3081,
      sUNTIL		= 3082,
    sBREAK		= 3090,
    sRETURN		= 3100,
    sINPUT		= 3110,
    sPRINT		= 3120,
    sEXIT		= 3130,
    sMEASURE		= 3140,
    sRESET		= 3150,
    
    sINCLUDE		= 3500,
    sDUMP		= 3510, 
    sPLOT		= 3520, 
    sINSPECT		= 3530,
    sLOAD		= 3540,
    sSAVE		= 3550,
    sSET		= 3560,
    sSHELL		= 3570,
    
  sDEF			= 4000,
  sDEFLIST		= 4010,
    sROUTDEF		= 4100, 
      sFUNCTDEF		= 4110, 
      sPROCDEF		= 4120,
      sQUOPDEF		= 4130,
      sQUFUNDEF		= 4140,
    sARGDEF		= 4200, 
    sVARDEF		= 4210, 
    sCONSTDEF		= 4220,

  sEOF			= 5000,
  sMSG			= 5010
};

// classes in syntax.h

class sObject;
class sExpr;
class sStmt;
class sDef;
class sExprList;
class sStmtList;
class sDefList;
class sRoutDef;

// classes in symbols.h

class SymTable;

// classes in quheap.h

class QuHeap;

// classes in error.h

class tError;

// classes in extern.h

//class QuBaseState;
struct RoutTableEntry;

typedef int tExtRout(const sRoutDef *,const SymTable *,int);


#define BASETYPE_MASK 0xffff
#define ORDER_SHIFT   16

int tensordim(int ord, int elem);
int tensorelem(int ord, int dim);

class tType {
  int _type;
public:
  tType(BaseType t=tUNDEF) { _type=t; }
  tType(BaseType t,int o) { _type=(t | (o << ORDER_SHIFT)); }
  tType(const tType& t) { _type=t._type; }
  BaseType basetype() const { return (BaseType)(_type & BASETYPE_MASK); }
  int ord() const { return _type >> ORDER_SHIFT; }
  int isBaseType() const { return _type>=tBOOLEAN && _type<=tQUSCR; }
  int isExpr() const { return _type>=tBOOLEAN; }
  int isDefined() const { return _type>=tVOID; }
  int isNumber() const { return _type>=tINTEGER && _type<=tCOMPLEX; }
  int isInt() const { return _type==tINTEGER; }
  int isBoolean() const { return _type==tBOOLEAN; }
  int isReal() const { return _type==tREAL; }
  int isOrdered() const { return isInt() || isReal(); }
  int isComplex() const { return _type==tCOMPLEX; }
  int isQuExpr() const { return _type>=tQUCONST && _type<=tQUSCR; }
  int isQuConst() const { return _type==tQUCONST; }
  int isQuReg() const { return _type==tQUREG; }
  int isQuVoid() const { return _type==tQUVOID; }
  int isQuScr() const { return _type==tQUSCR; }
  int isQuVar() const { return isQuExpr() && !isQuConst(); }
  int isQuCond() const { return isQuExpr() || _type==tQUCOND; }
  int isCond() const { return isQuCond() || isBoolean(); }
  int isString() const { return _type==tSTRING; }
  int isError() const { return _type==tERROR; }
  int isUndef() const { return _type==tUNDEF; }
  int isConv(const tType& t) const {
    if(_type==t._type || isQuExpr() && t.isQuExpr()) return 1;
    if(isBoolean() && t.isQuCond()) return 1;
    if(ord()!=t.ord()) return 0;
    return basetype()>=tINTEGER && basetype()<t.basetype() &&
           t.basetype()<=tCOMPLEX;
  }
  void operator=(const tType& t) { _type=t._type; }
  void operator=(BaseType t) { _type=t; }
  int operator==(const tType& t) const { return _type==t._type; }
  int operator==(BaseType t) const { return _type==t; }
  int operator!=(const tType& t) const { return _type!=t._type; }
  int operator!=(BaseType t) const { return _type!=t; }
  string str() const;
};

ostream& operator << (ostream& s, const tType& t);

class tValue {
  tType _type;
  void error(const char*) const;
  struct tensor {
    int dim;
    int len;
    int refs;
    union {
      tInt *pi;
      tReal *pr;
      tComplex *pz;
    };
  };
  union {
    boolean b;
    long i;
    tReal r;
    tComplex *pz;
    string *ps;
    quState *pq;
    QuCond *pc;
    tensor *pt;
  } _val;
  void delpointer();
  void assign(const tValue& v) {
    _type=v._type;
    if(_type.ord()) {
      _val.pt=v._val.pt;
      _val.pt->refs++;
      return;
    }
    switch(_type.basetype()) {
      case tBOOLEAN:  	_val.b=v._val.b; break;
      case tINTEGER:  	_val.i=v._val.i; break;
      case tREAL:	_val.r=v._val.r; break;
      case tCOMPLEX:	_val.pz=new tComplex(*v._val.pz); break;
      case tSTRING:	_val.ps=new string(*v._val.ps); break;
      case tQUCONST:
      case tQUREG:
      case tQUVOID:
      case tQUSCR:
			_val.pq=v._val.pq->newclone();  break;
      case tQUCOND:	_val.pc=new QuCond(*v._val.pc); break;
      default:		;
    }
  }
  void init(const tType& t) {
    _type=t;
    switch(t.basetype()) {
      case tBOOLEAN:  	_val.b=FALSE; break;
      case tINTEGER:  	_val.i=0; break;
      case tREAL:	_val.r=0.0; break;
      case tCOMPLEX:	_val.pz=new tComplex(); break;
      case tSTRING:	_val.ps=new string(); break;
      case tQUCONST:
      case tQUREG:
      case tQUVOID:
      case tQUSCR:
      			_val.pq=new quVar(); break;
      case tQUCOND:	_val.pc=new QuCond(); break;
      default:		;
    }
  }
  void inittensor(const tType& t,int d);
  void copytensor();
  tValue convert(const tType& t) const;
public:
  tValue() { INCVAL; _type=tUNDEF; }
  tValue(BaseType t) { 
    INCVAL;
    init(tType(t));
  }
  tValue(const tType& t) {
    INCVAL;
    init(t);
  }
  tValue(const tType& t,int d) {
    INCVAL;
    inittensor(t,d);
  }
  tValue(const tValue& v) { INCVAL; assign(v); }
  tValue(boolean b) { INCVAL; _type=tBOOLEAN; _val.b=b; }
  tValue(int i) { INCVAL; _type=tINTEGER; _val.i=i; }
  tValue(tInt i) { INCVAL; _type=tINTEGER; _val.i=i; }
  tValue(tReal r) { INCVAL; _type=tREAL; _val.r=r; }
  tValue(const tComplex& z) { INCVAL; _type=tCOMPLEX; _val.pz=new tComplex(z); }
  tValue(const char* s) { INCVAL; _type=tSTRING; _val.ps=new string(s); }
  tValue(string s) { INCVAL; _type=tSTRING; _val.ps=new string(s); }
  tValue(quState& q,BaseType t=tQUREG) { INCVAL; _type=t; _val.pq=q.newclone(); }
  tValue(quState *q,BaseType t=tQUREG) { INCVAL; _type=t; _val.pq=q; }
  tValue(const QuCond& c) { INCVAL; _type=tQUCOND; _val.pc=new QuCond(c); }
  ~tValue() { DECVAL; delpointer(); }
  tType type() const { return _type; }
  BaseType basetype() const { return _type.basetype(); }
  int ord() const { return _type.ord(); }
  int elem() const { return ord() ? _val.pt->len : 0; }
  int dim() const { return ord() ? _val.pt->dim : 0; }
  int isBaseType() const { return _type.isBaseType(); }
  int isExpr() const { return _type.isExpr(); }
  int isDefined() const { return _type.isDefined(); }
  int isNumber() const { return _type.isNumber(); }
  int isBoolean() const { return _type.isBoolean(); }
  int isInt() const { return _type.isInt(); }
  int isReal() const { return _type.isReal(); }
  int isOrdered() const { return isInt() || isReal(); }
  int isComplex() const { return _type.isComplex(); }
  int isQuExpr() const { return _type.isQuExpr(); }
  int isQuConst() const { return _type.isQuConst(); }
  int isQuReg() const { return _type.isQuReg(); }
  int isQuVoid() const { return _type.isQuVoid(); }
  int isQuScr() const { return _type.isQuScr(); }
  int isQuVar() const { return isQuExpr() && !isQuConst(); }
  int isEmpty() const { return !isQuExpr() || !_val.pq->mapbits(); }
  int isQuCond() const { return _type.isQuCond(); }
  int isCond() const { return _type.isCond(); }
  int isString() const { return _type.isString(); }
  int isError() const { return _type.isError(); }
  int isUndef() const { return _type.isUndef(); }
  int isConv(const tType& t) const { return _type.isConv(t); }
  int isZero() const { return (isInt() && _val.i==0) || (_type==tREAL && 
    _val.r==0.00) || (_type==tCOMPLEX && *_val.pz==tComplex(0,0)); }

  tValue conv(const tType& t) const {
    if(_type==t) return tValue(*this);
    if(!isConv(t)) error("not convertible");
    return convert(t);
  }
    
  void setQuType(BaseType t) { 
    if(!isQuExpr()) error("setQuType: no quantum type");
    _type=t; 
  }
  
  boolean toBool() const { return _val.b ? TRUE : FALSE; }
  tInt toInt() const { 
    if(isInt()) return _val.i;
    if(isReal()) return (tInt) _val.r;
    return (tInt) toBool();
  }
  tReal toReal() const { return isReal() ? _val.r : (tReal) toInt(); }
  tComplex toComplex() const { return isComplex() ? *_val.pz : (tComplex) toReal(); }
  string toString() const { return *_val.ps; }
  QuCond toQuCond() const;
  quState* qustate() const { return isQuExpr() ? _val.pq : 0; }
  QuCond* qucond() const { return _type==tQUCOND ? _val.pc : 0; }
  tValue& operator = (const tValue& v) { 
    if(this!=&v) {
      delpointer(); 
      assign(v); 
    }
    return *this; 
  }
  tValue operator [] (int i) const { 
    if(elem()<=i) error("index out of range");
    switch(basetype()) {
      case tINTEGER:  return tValue(_val.pt->pi[i]);
      case tREAL:     return tValue(_val.pt->pr[i]);
      case tCOMPLEX:  return tValue(_val.pt->pz[i]);
      default:        error("invalid tensor type");
    }
    return tValue(tERROR);
  }
  void set(int i,tValue v) {
    if(elem()<=i) error("index out of range");
    if(_val.pt->refs>1) copytensor();
    switch(basetype()) {
      case tINTEGER:  _val.pt->pi[i]=v.toInt();     return;
      case tREAL:     _val.pt->pr[i]=v.toReal();    return;
      case tCOMPLEX:  _val.pt->pz[i]=v.toComplex(); return;
      default:        error("invalid tensor type");
    }
  }
  string str() const;
};


#define VALOP(o) \
inline tValue operator o (const tValue& a,const tValue& b) { 	\
  switch(MAX(a.basetype(),b.basetype())) {			\
    case tINTEGER:  return a.toInt() o b.toInt();		\
    case tREAL:     return a.toReal() o b.toReal();		\
    case tCOMPLEX:  return a.toComplex() o b.toComplex();	\
    default:        ;						\
  }								\
  return tValue();						\
}

VALOP(+)
VALOP(-)    
VALOP(*)    
VALOP(/)    

#undef VALOP

ostream& operator << (ostream& s, const tValue& v);

#endif
