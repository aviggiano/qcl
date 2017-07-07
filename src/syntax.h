/**********************************************************************

This file is part of the Quantum Computation Language QCL.

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/


#ifndef SYNTAX_H
#define SYNTAX_H 1

#pragma interface

#include "types.h"
#include "symbols.h"
#include "extern.h"

#include <stdio.h>

#define for_plist(p,plist,cp) for(p=plist->first(cp);p;p=plist->next(cp))
#define for_pplist(p,plist,cp,q,qlist,cq,cond) for(p=(plist)->first(cp),q=(qlist)->first(cq); \
	(cond);p=(plist)->next(cp),q=(qlist)->next(cq))

#define FANOUTID "Fanout"
#define SWAPID "Swap"
#define CNOTID "CNot"
#define NOTID "Not"
#define CONDID "cond"

#define ASSERT(c) if(QCL_DEBUG && !(c)) 	\
  throw tError(errINT, 				\
  string("assertion " #c " in " __FILE__ ":")+ 	\
  sdec(__LINE__)+string(" failed"),this)

enum ObjFlag {
  flagINV	= 1,
  flagASSIGN	= 2,
  flagBREAK	= 4,
  flagUNTIL	= 8,
  flagRANGE	= 16,
  flagBENNET	= 32,
  flagCOND	= 64,
  flagEXTERN	= 128,
  flagQUIF	= 256,
  flagQUFORK	= 512,
  flagCONDDEF	= 1024,
  flagFUNOP	= 2048
};

class sObject {
  unsigned _flags;
  sObject *_parent;
public:
  sObject(unsigned f=0) { INCOBJ; _flags=f; _parent=0; }
  virtual ~sObject() { DECOBJ; }
  virtual ObjType object() const { return sOBJECT; }
  virtual string prtstr(int ind=NOINDENT) const;
  virtual void typecheck(SymTable *loc,SymTable *gl) { }
  string objstr() const;
  string defstr() const;
  sObject *parent() const { return _parent; }
  void print(ostream& o,int ind=INDENT) { o << prtstr(ind); }

  void setFlag(ObjFlag f,int b=1) { 
    if(b) _flags|=f; else _flags&=~f; 
  }
  void setFlagRec(ObjFlag f,int b=1) { 
    setFlag(f,b); 
    if(parent()) parent()->setFlagRec(f,b);
  }
  void toggleFlag(ObjFlag f) { _flags^=f; }
  void setBennet(int b) { setFlag(flagBENNET,b); }
  void setParent(sObject *p) { _parent=p; }
  int isSet(ObjFlag f) const { return f&_flags; }
  int isSetRec(ObjFlag f) { 
    return isSet(f) || (parent() && parent()->isSetRec(f)); 
  }

  int isDef() const { return object()>=sFUNCTDEF && object()<=sCONSTDEF; }
  int isRoutDef() const { return object()>=sFUNCTDEF && object()<sARGDEF; }
  int isValueDef() const { return object()>=sARGDEF && object()<=sCONSTDEF; }
  int isVarDef() const { return object()==sVARDEF; }
  int isConstDef() const { return object()==sCONSTDEF; }
  int isArgDef() const { return object()==sARGDEF; }
  int isFunctDef() const { return object()==sFUNCTDEF; }
  int isProcDef() const { return object()==sPROCDEF; }
  int isQuOpDef() const { return object()==sQUOPDEF; }
  int isQuFunDef() const { return object()==sQUFUNDEF; }
  int isQuDef() const { return isQuOpDef() || isQuFunDef(); }
  int isExpr() const { return object()>sEXPRLIST && object()<sSTMT; }
  int isBinOp() const { return object()>sBINOP && object()<sBASEFUNCT; }
  int isArithOp() const { return object()>=sADD && object()<sLESS; }
  int isCompOp() const { return object()>=sLESS && object()<sAND; }
  int isLogOp() const { return object()>=sAND && object()<sCONCAT; }
  int isBaseFunct() const { return object()>sBASEFUNCT && object()<sLISTFUNCT; }
  int isTrigFunct() const { return object()>=sSIN && object()<=sCOTH; }
  int isTypecast() const { return object()>=sINT && object()<=sSTRING; }
  int isListFunct() const { return object()>sLISTFUNCT && object()<sSTMT; }
  int isTensor() const { return object()>=sVECTOR && object()<=sTENSOR9; }
  int isStmt() const { return object()>sSTMTLIST && object()<sDEF; }
  int isEof() const { return object()==sEOF; }
  int isInclude() const { return object()==sINCLUDE; }
  int isBennet() const { return isSet(flagBENNET); }
  int isExtern() const { return isSet(flagEXTERN); }
  int isCond() const { return isSet(flagCOND); }
  int isCondDef() const { return isSet(flagCONDDEF); }
  int isDirty() const { return isSet(flagASSIGN) || isSet(flagBREAK); }
  int isFunOp() const { return isSet(flagFUNOP); }
  
  sRoutDef *def() const { 
    if(parent()) {
      if(parent()->isRoutDef())
        return (sRoutDef*)parent();
      else
        return parent()->def();
    } else {
      return 0;
    }
  }
  int inRoutDef() const { sObject *d=(sObject*)def(); return d && d->isRoutDef(); }
  int inProcDef() const { sObject *d=(sObject*)def(); return d && d->isProcDef(); }
  int inFunctDef() const { sObject *d=(sObject*)def(); return d && d->isFunctDef(); }
  int inQuDef() const { sObject *d=(sObject*)def(); return d && d->isQuDef(); }
  int inQuFunDef() const { sObject *d=(sObject*)def(); return d && d->isQuFunDef(); }
  int inQuOpDef() const { sObject *d=(sObject*)def(); return d && d->isQuOpDef(); }
  int inFunOp() const { sObject *d=(sObject*)def(); return d && d->isFunOp(); }
  int isGlobal() const { sObject *d=(sObject*)def(); return !d || d->isProcDef(); }
  int isLocal() const { return !isGlobal(); }
  sStmt *stmt() {
    if(isStmt()) return (sStmt*)this;
    if(parent()) return (sStmt*)parent()->stmt();
    return 0;
  }
};

template<class T>
class sList : public sObject {
  struct node {
    T *p;
    node *n;
  };
  node *_first;
  node *_last;
  int _n;
public:
  sList() : sObject() { _first=_last=0; _n=0; }
  virtual ~sList() {
    node *q;

    while(_first) {
   	  q=_first;
	  _first=q->n;
	  qcl_delete(q->p);
	  qcl_delete(q);
    };
  }
  virtual ObjType object() const { return sLIST; }
  T *first(void* &_cursor) const { _cursor=_first;
                return _cursor ? ((node*)_cursor)->p : 0; }
  T *next(void* &_cursor) const { _cursor= ((node*)_cursor) ? ((node*)_cursor)->n : 0; 
                return _cursor ? ((node*)_cursor)->p : 0; }
  T *last(void* &_cursor) const { _cursor=_last; 
                return _cursor ? ((node*)_cursor)->p : 0; }
  int isEmpty() const { return !_first; }
  int n() const { return _n; }
  void append(T *p) {
    node *q;
    _n++;
    q=new node;
    q->p=p; q->n=0;
    if(!_first) _first=q;
    if(_last) _last->n=q;
    _last=q;
  }
};


/***********************************************/
/***************** Expressions *****************/
/***********************************************/


class sExpr : public sObject {
  tType _type;
public:
  sExpr() : sObject() { _type=tUNDEF; }
  sExpr(const tType& t) : sObject() { _type=t; } 
  virtual ObjType object() const { return sEXPR; }
  tType type() { return _type; }
  BaseType basetype() { return _type.basetype(); }
  int ord() { return _type.ord(); }
  void settype(const tType& t) { _type=t; }
  virtual tValue eval(SymTable *loc,SymTable *gl,QuHeap *qh);
};

class sExprList : public sList<sExpr> {
public:
  sExprList() : sList<sExpr>() { };
  sExprList(sExpr *e) : sList<sExpr>() { append(e); }
  sExprList(sExpr *e1,sExpr *e2) : sList<sExpr>() { 
    append(e1); append(e2); }
  virtual ObjType object() const { return sEXPRLIST; }
  virtual string prtstr(int ind=NOINDENT) const;
  virtual void typecheck(SymTable *loc,SymTable *gl);
};

class sConst : public sExpr {
  tValue _val;
public:
  sConst(const tValue& v) : sExpr(v.type()) { _val=v; }
  virtual ObjType object() const { return sCONST; }
  virtual string prtstr(int ind=NOINDENT) const;
  virtual void typecheck(SymTable *loc,SymTable *gl);
  tValue value() { return _val; }
  virtual tValue eval(SymTable *loc,SymTable *gl,QuHeap *qh);
};

class sVar : public sExpr {
  tId *pid;
public:
  sVar(tId *id) : sExpr() { pid=id; }
  virtual ~sVar() { qcl_delete(pid); }
  tId id() const { return *pid; }
  virtual ObjType object() const { return sVAR; }
  virtual string prtstr(int ind=NOINDENT) const;
  virtual void typecheck(SymTable *loc,SymTable *gl);
  virtual tValue eval(SymTable *loc,SymTable *gl,QuHeap *qh);
};

class sSubscript : public sExpr {
  sVar *pvar;
  sExprList *psubs;
  sExpr *psub;
public:
  sSubscript(sVar *v,sExpr *s) : sExpr() { 
    pvar=v;
    psub=s;
    psubs=new sExprList;
    psubs->append(s);
  }
  sSubscript(sVar *v,sExprList *e) : sExpr() {
    void *c;
    pvar=v;
    psubs=e;
    psub=e->first(c);
  }
  virtual ~sSubscript() { qcl_delete(pvar); qcl_delete(psubs); }
  int nargs() const { return psubs->n(); }
  virtual ObjType object() const { return sSUBSCRIPT; }
  virtual string prtstr(int ind=NOINDENT) const; 
  virtual void typecheck(SymTable *loc,SymTable *gl);
  virtual tValue eval(SymTable *loc,SymTable *gl,QuHeap *qh);
};

#define SUBRANGE_LENGTH 0   // [o :: l]
#define SUBRANGE_END 1      // [b .. e]



// flagRANGE 0: [a \ b]   or [a :: b]  =  <a,a+1,...,a+b-1>
// flagRANGE 1: [a : b]   or [a .. b]  =  <a,a+1,...,b>

class sSubRange : public sExpr {
  sVar *pvar;
  sExpr *pexpr1,*pexpr2;
public:
  sSubRange(sVar *v,sExpr *e1,sExpr *e2,int f=0) : sExpr() { 
    pvar=v; pexpr1=e1; pexpr2=e2; setFlag(flagRANGE,f); }
  virtual ~sSubRange() { qcl_delete(pvar); qcl_delete(pexpr1); qcl_delete(pexpr2); }
  virtual ObjType object() const { return sSUBRANGE; }
  virtual string prtstr(int ind=NOINDENT) const;
  virtual void typecheck(SymTable *loc,SymTable *gl);
  virtual tValue eval(SymTable *loc,SymTable *gl,QuHeap *qh);
};

class sUnOp : public sExpr {
protected:
  sExpr *pexpr;
public:
  sUnOp(sExpr *e) : sExpr() { pexpr=e; }
  virtual ~sUnOp() { qcl_delete(pexpr); }
  virtual ObjType object() const { return sUNOP; }
  virtual string prtstr(int ind=NOINDENT) const;
  virtual void typecheck(SymTable *loc,SymTable *gl);
};

class sNeg : public sUnOp {
public:
  sNeg(sExpr *e) : sUnOp(e) { }
  virtual ObjType object() const { return sNEG; }
  virtual tValue eval(SymTable *loc,SymTable *gl,QuHeap *qh);
};

class sNot : public sUnOp {
public:
  sNot(sExpr *e) : sUnOp(e) { }
  virtual ObjType object() const { return sNOT; }
  virtual tValue eval(SymTable *loc,SymTable *gl,QuHeap *qh);
};

class sLength : public sUnOp {
public:
  sLength(sExpr *e) : sUnOp(e) { }
  virtual ObjType object() const { return sLENGTH; }
  virtual tValue eval(SymTable *loc,SymTable *gl,QuHeap *qh);
};

class sBinOp : public sExpr {
protected:
  sExpr *pexpr1;
  sExpr *pexpr2;
  string binop_prtstr(int ind,const sBinOp *o) const;
public:
  sBinOp(sExpr *e1,sExpr *e2) : sExpr() { pexpr1=e1; pexpr2=e2; }
  virtual ~sBinOp() { qcl_delete(pexpr1); qcl_delete(pexpr2); }
  virtual ObjType object() const { return sBINOP; }
  virtual string prtstr(int ind=NOINDENT) const;
  virtual void typecheck(SymTable *loc,SymTable *gl);
  virtual tValue eval(SymTable *loc,SymTable *gl,QuHeap *qh);
};

#define BINOP_CLASS(T,S) 				\
  class T : public sBinOp { 				\
    public:						\
    T (sExpr *e1,sExpr *e2) : sBinOp(e1,e2) { }		\
    virtual ObjType object() const { return S; }	\
  }

BINOP_CLASS(sAdd,sADD);
BINOP_CLASS(sSub,sSUB);
BINOP_CLASS(sMult,sMULT);
BINOP_CLASS(sDiv,sDIV);
BINOP_CLASS(sMod,sMOD);
BINOP_CLASS(sPow,sPOW);

BINOP_CLASS(sLess,sLESS);
BINOP_CLASS(sEqual,sEQUAL);
BINOP_CLASS(sLeEq,sLEEQ);
BINOP_CLASS(sNotEq,sNOTEQ);

BINOP_CLASS(sAnd,sAND);
BINOP_CLASS(sOr,sOR);
BINOP_CLASS(sXor,sXOR);

BINOP_CLASS(sConcat,sCONCAT);

#undef BINOP_CLASS

class sFunctCall : public sExpr {
  tId *pid;
  sExprList *ppar;
public:
  sFunctCall(tId *id,sExprList *par) : sExpr() { pid=id; ppar=par; }
  virtual ~sFunctCall() { qcl_delete(pid); qcl_delete(ppar); }
  tId id() const { return *pid; }
  virtual ObjType object() const { return sFUNCTCALL; }
  virtual string prtstr(int ind=NOINDENT) const;
  virtual void typecheck(SymTable *loc,SymTable *gl);
  virtual tValue eval(SymTable *loc,SymTable *gl,QuHeap *qh);
};

class sBaseFunct : public sExpr {
  ObjType _objtype;
  sExpr *pexpr;
public:
  sBaseFunct(ObjType o,sExpr *e) : sExpr() { _objtype=o; pexpr=e; }
  virtual ~sBaseFunct() { qcl_delete(pexpr); }
  sExpr *expr();
  virtual ObjType object() const { return _objtype; }
  virtual string prtstr(int ind=NOINDENT) const;
  virtual void typecheck(SymTable *loc,SymTable *gl);
  virtual tValue eval(SymTable *loc,SymTable *gl,QuHeap *qh);
};

class sListFunct : public sExpr {
  ObjType _objtype;
  sExprList *pexpr;
  sExpr *pexpr1;
  sExpr *pexpr2;
public:
  sListFunct(ObjType o,sExprList *e) : sExpr() { 
    void *c;
    _objtype=o; pexpr=e; pexpr1=e->first(c); pexpr2=e->next(c); }
  virtual ~sListFunct() { qcl_delete(pexpr); }
  sExpr *expr();
  virtual ObjType object() const { return _objtype; }
  virtual string prtstr(int ind=NOINDENT) const;
  virtual void typecheck(SymTable *loc,SymTable *gl);
  virtual tValue eval(SymTable *loc,SymTable *gl,QuHeap *qh);
};


/***********************************************/
/***************** Statements ******************/
/***********************************************/


class sStmt : public sObject {
public:
  sStmt(int inv=0) : sObject() { setFlag(flagINV,inv); }
  virtual ObjType object() const { return sSTMT; }
  virtual void exec(SymTable *loc,SymTable *gl,QuHeap *qh);
  int isInv() const { return isSet(flagINV); }
};

class sStmtList : public sList<sStmt> {
public:
  sStmtList() : sList<sStmt>() { }
  virtual ObjType object() const { return sSTMTLIST; }
  virtual string prtstr(int ind=NOINDENT) const;
  virtual void typecheck(SymTable *loc,SymTable *gl);
  virtual void exec(SymTable *loc,SymTable *gl,QuHeap *qh);
};

class sCall : public sStmt {
  tId *pid;
  sExprList *ppar;
public:
  sCall(tId *id,sExprList *par,int inv=0) : sStmt(inv) { 
    pid=id; ppar=par; }
  virtual ~sCall() { qcl_delete(pid); qcl_delete(ppar); }
  virtual ObjType object() const { return sCALL; }
  virtual string prtstr(int ind=NOINDENT) const;
  tId id() const { return *pid; };
  virtual void typecheck(SymTable *loc,SymTable *gl);
  virtual void exec(SymTable *loc,SymTable *gl,QuHeap *qh);
};

class sAssign : public sStmt {
  sVar *pvar;
  sExpr *pexpr;
  sExprList *psubs;
public:
  sAssign(sVar *v,sExpr *e,sExprList *s=0) : sStmt(0) { 
    pvar=v; pexpr=e; psubs=s; 
    setFlag(flagASSIGN); 
  }
  virtual ~sAssign() { 
    qcl_delete(pvar); qcl_delete(pexpr); 
    if(psubs) qcl_delete(psubs);
  } 
  virtual ObjType object() const { return sASSIGN; }
  virtual string prtstr(int ind=NOINDENT) const;
  virtual void typecheck(SymTable *loc,SymTable *gl);
  virtual void exec(SymTable *loc,SymTable *gl,QuHeap *qh);
};

class sFor : public sStmt {
  sVar *pvar;
  sExpr *pfrom;
  sExpr *pto;
  sExpr *pstep;
  sStmtList *pbody;
public:
  sFor(sVar *v,sExpr *f,sExpr *t,sStmtList *b,sExpr *s=0) : sStmt(0) {
    pvar=v; pfrom=f; pto=t; pstep=s; pbody=b; }
  virtual ~sFor() { 
    qcl_delete(pvar); 
    qcl_delete(pfrom); 
    qcl_delete(pto); 
    if(pstep) qcl_delete(pstep); 
    if(pbody) qcl_delete(pbody); 
  } 
  virtual ObjType object() const { return sFOR; }
  virtual string prtstr(int ind=NOINDENT) const;
  virtual void typecheck(SymTable *loc,SymTable *gl);
  virtual void exec(SymTable *loc,SymTable *gl,QuHeap *qh);
};

class sIf : public sStmt {
  sExpr *pcond;
  sStmtList *pthen;
  sStmtList *pelse;
public:
  sIf(sExpr *c,sStmtList *t,sStmtList *e=0) : sStmt(0) {
    pcond=c; pthen=t; pelse=e; }
  virtual ~sIf() { 
    qcl_delete(pcond); 
    qcl_delete(pthen); 
    if(pelse) qcl_delete(pelse); 
  }
  virtual ObjType object() const { return sIF; }
  virtual string prtstr(int ind=NOINDENT) const;
  virtual void typecheck(SymTable *loc,SymTable *gl);
  virtual void exec(SymTable *loc,SymTable *gl,QuHeap *qh);
};

class sLoop : public sStmt {
  sExpr *pcond;
  sStmtList *pbody;
public:
  sLoop(sExpr *c,sStmtList *b,int until) : sStmt(0) { 
    pcond=c; pbody=b; setFlag(flagUNTIL,until); }
  virtual ~sLoop() { qcl_delete(pcond); qcl_delete(pbody); }
  virtual ObjType object() const { return sLOOP; }
  sExpr *cond() const { return pcond; }
  sStmtList *body() const { return pbody; }
  virtual void typecheck(SymTable *loc,SymTable *gl);
  virtual void exec(SymTable *loc,SymTable *gl,QuHeap *qh);
};

class sWhile : public sLoop {
public:
  sWhile(sExpr *c,sStmtList *b) : sLoop(c,b,0) { }
  virtual ObjType object() const { return sWHILE; }
  virtual string prtstr(int ind=NOINDENT) const;
};

class sUntil : public sLoop {
public:
  sUntil(sExpr *c,sStmtList *b) : sLoop(c,b,1) { }
  virtual ObjType object() const { return sUNTIL; }
  virtual string prtstr(int ind=NOINDENT) const;
};

class sBreak : public sStmt {
public:
  sBreak() : sStmt(0) { setFlag(flagBREAK); }
  virtual ObjType object() const { return sBREAK; }
  virtual string prtstr(int ind=NOINDENT) const;
  virtual void typecheck(SymTable *loc,SymTable *gl);
  virtual void exec(SymTable *loc,SymTable *gl,QuHeap *qh);
};

class sReturn : public sStmt {
  sExpr *pexpr;
public:
  sReturn(sExpr *e) : sStmt(0) { pexpr=e; }
  virtual ~sReturn() { qcl_delete(pexpr); }
  virtual ObjType object() const { return sRETURN; }
  virtual string prtstr(int ind=NOINDENT) const;
  virtual void typecheck(SymTable *loc,SymTable *gl);
  virtual void exec(SymTable *loc,SymTable *gl,QuHeap *qh);
};

class sInput : public sStmt {
  sExpr *pprompt;
  sVar *pvar;
public:
  sInput(sVar *v,sExpr *s) : sStmt(0) { pprompt=s; pvar=v; }
  virtual ~sInput() { if (pprompt) qcl_delete(pprompt); qcl_delete(pvar); }
  virtual ObjType object() const { return sINPUT; }
  virtual string prtstr(int ind=NOINDENT) const;
  virtual void typecheck(SymTable *loc,SymTable *gl);
  virtual void exec(SymTable *loc,SymTable *gl,QuHeap *qh);
};

class sPrint : public sStmt {
  sExprList *plist;
public:
  sPrint(sExprList *l) : sStmt(0) { plist=l; }
  virtual ~sPrint() { qcl_delete(plist); }
  virtual ObjType object() const { return sPRINT; }
  virtual string prtstr(int ind=NOINDENT) const;
  virtual void typecheck(SymTable *loc,SymTable *gl);
  virtual void exec(SymTable *loc,SymTable *gl,QuHeap *qh);
};

class sExit : public sStmt {
  sExpr *pmsg;
public:
  sExit(sExpr *s) : sStmt(0) { pmsg=s; }
  virtual ~sExit() { if(pmsg) qcl_delete(pmsg); }
  virtual ObjType object() const { return sEXIT; }
  virtual string prtstr(int ind=NOINDENT) const;
  virtual void typecheck(SymTable *loc,SymTable *gl);
  virtual void exec(SymTable *loc,SymTable *gl,QuHeap *qh);
};

class sMeasure : public sStmt {
  sExpr *pstate;
  sVar *pvar;
public:
  sMeasure(sExpr *q,sVar *v) : sStmt(0) { pstate=q; pvar=v; }
  virtual ~sMeasure() { if (pvar) qcl_delete(pvar); qcl_delete(pstate); }
  virtual ObjType object() const { return sMEASURE; }
  virtual string prtstr(int ind=NOINDENT) const;
  virtual void typecheck(SymTable *loc,SymTable *gl);
  virtual void exec(SymTable *loc,SymTable *gl,QuHeap *qh);
};

class sInclude : public sStmt {
  string fname;
public:
  sInclude(string s) : sStmt(0) { fname=s; }
  string filename() { return fname; }
  virtual ObjType object() const { return sINCLUDE; }
  virtual string prtstr(int ind=NOINDENT) const;
  virtual void typecheck(SymTable *loc,SymTable *gl);
  virtual void exec(SymTable *loc,SymTable *gl,QuHeap *qh);
};

class sReset : public sStmt {
public:
  sReset() : sStmt(0) { }
  virtual ObjType object() const { return sRESET; }
  virtual string prtstr(int ind=NOINDENT) const;
  virtual void typecheck(SymTable *loc,SymTable *gl);
  virtual void exec(SymTable *loc,SymTable *gl,QuHeap *qh);
};

/***********************************************/
/****************** Commands *******************/
/***********************************************/



class sDump : public sStmt {
  sExpr *pexpr;
public:
  sDump(sExpr *v=0) : sStmt(0) { pexpr=v; }
  virtual ~sDump() { if(pexpr) qcl_delete(pexpr); }
  virtual ObjType object() const { return sDUMP; }
  virtual string prtstr(int ind=NOINDENT) const;
  virtual void typecheck(SymTable *loc,SymTable *gl);
  virtual void exec(SymTable *loc,SymTable *gl,QuHeap *qh);
};

class sPlot : public sStmt {
  sExpr *pexpr1;
  sExpr *pexpr2;
public:
  sPlot(sExpr *e1=0,sExpr *e2=0) : sStmt(0) { pexpr1=e1; pexpr2=e2; }
  virtual ~sPlot() { 
    if(pexpr1) qcl_delete(pexpr1);
    if(pexpr2) qcl_delete(pexpr2);
  }
  virtual ObjType object() const { return sPLOT; }
  virtual string prtstr(int ind=NOINDENT) const;
  virtual void typecheck(SymTable *loc,SymTable *gl);
  virtual void exec(SymTable *loc,SymTable *gl,QuHeap *qh);
};

class sInspect : public sStmt {
  sExprList *plist;
public:
  sInspect(sExprList *l=0) : sStmt(0) { plist=l; }
  virtual ~sInspect() { if(plist) qcl_delete(plist); }
  virtual ObjType object() const { return sINSPECT; }
  virtual string prtstr(int ind=NOINDENT) const;
  virtual void typecheck(SymTable *loc,SymTable *gl);
  virtual void exec(SymTable *loc,SymTable *gl,QuHeap *qh);
};


class sLoad : public sStmt {
  sExpr *pexpr;
public:
  sLoad(sExpr *v=0) : sStmt(0) { pexpr=v; }
  virtual ~sLoad() { if(pexpr) qcl_delete(pexpr); }
  virtual ObjType object() const { return sLOAD; }
  virtual string prtstr(int ind=NOINDENT) const;
  virtual void typecheck(SymTable *loc,SymTable *gl);
  virtual void exec(SymTable *loc,SymTable *gl,QuHeap *qh);
};


class sSave : public sStmt {
  sExpr *pexpr;
public:
  sSave(sExpr *v=0) : sStmt(0) { pexpr=v; }
  virtual ~sSave() { if(pexpr) qcl_delete(pexpr); }
  virtual ObjType object() const { return sSAVE; }
  virtual string prtstr(int ind=NOINDENT) const;
  virtual void typecheck(SymTable *loc,SymTable *gl);
  virtual void exec(SymTable *loc,SymTable *gl,QuHeap *qh);
};


class sSet : public sStmt {
  string opt;
  sExpr *pexpr;
public:
  sSet(string s,sExpr *arg=0) : sStmt(0) { opt=s; pexpr=arg; }
  virtual ~sSet() { if(pexpr) qcl_delete(pexpr); }
  string option() { return opt; }
  virtual ObjType object() const { return sSET; }
  virtual string prtstr(int ind=NOINDENT) const;
  virtual void typecheck(SymTable *loc,SymTable *gl);
  virtual void exec(SymTable *loc,SymTable *gl,QuHeap *qh);
};


class sShell : public sStmt {
public:
  sShell() : sStmt(0) { }
  virtual ~sShell() { }
  virtual ObjType object() const { return sSHELL; }
  virtual string prtstr(int ind=NOINDENT) const;
  virtual void exec(SymTable *loc,SymTable *gl,QuHeap *qh);
};



/***********************************************/
/***************** Definitions *****************/
/***********************************************/


class sDef : public sObject {
  tType _type;
  tId *pid;
public:
  sDef(const tType& t,tId *i) : sObject() { _type=t; pid=i; }
  virtual ~sDef() { if(pid) qcl_delete(pid); }
  virtual ObjType object() const { return sDEF; }
  tType type() const { return _type; }
  void settype(const tType& t) { _type=t; }
  BaseType basetype() { return _type.basetype(); }
  int ord() { return _type.ord(); }
  tId id() const { return *pid; };
  virtual string declstr() const;
  virtual void define(SymTable *loc,SymTable *gl,QuHeap *qh);
};

class sDefList : public sList<sDef> {
public:
  sDefList() : sList<sDef>() { };
  virtual ObjType object() const { return sDEFLIST; }
  virtual string prtstr(int ind=NOINDENT) const;
  virtual void typecheck(SymTable *loc,SymTable *gl);
  virtual void define(SymTable *loc,SymTable *gl,QuHeap *qh);
};

class sArgDef : public sDef {
public:
  sArgDef(const tType& t,tId *i) : 
	sDef(t,i) { }
  virtual ObjType object() const { return sARGDEF; };
  virtual string prtstr(int ind=NOINDENT) const;
};

class sVarDef : public sDef {
  sExpr *plen;
  sExpr *pinit;
public:
  sVarDef(const tType& t,tId *i,sExpr *l=0,sExpr *ini=0) : 
	sDef(t,i) { plen=l; pinit=ini; }
  ~sVarDef() { if(plen) qcl_delete(plen); if(pinit) qcl_delete(pinit); }
  virtual ObjType object() const { return sVARDEF; };
  virtual string prtstr(int ind=NOINDENT) const;
  virtual void typecheck(SymTable *loc,SymTable *gl);
  virtual void define(SymTable *loc,SymTable *gl,QuHeap *qh);
};

class sConstDef : public sDef {
  sExpr *pexpr;
public:
  sConstDef(tId *i,sExpr *v) : sDef(tType(tUNDEF),i) { pexpr=v; }
  virtual ~sConstDef() { qcl_delete(pexpr); }
  virtual ObjType object() const { return sCONSTDEF; };
  virtual string prtstr(int ind=NOINDENT) const;
  virtual void typecheck(SymTable *loc,SymTable *gl);
  virtual void define(SymTable *loc,SymTable *gl,QuHeap *qh);
};

class sRoutDef : public sDef {
protected:
  sDefList *pargs;
  sDefList *pdefs;
  union { 
    sStmtList *pbody;
    tExtRout *pext;
  };
  string filename;
  int linebeg;
  int lineend;
public:
  sRoutDef(const tType& t,tId *i,sDefList *a,sDefList *d,sStmtList *b,int c=0,int ext=0) : sDef(t,i) { 
    pargs=a; pdefs=d; pbody=b;
    setFlag(flagBENNET,0);
    setFlag(flagCONDDEF,c);
    setFlag(flagCOND,c);
    setFlag(flagEXTERN,ext);
  };  
  virtual ~sRoutDef() { 
    qcl_delete(pargs); 
    if(!isExtern()) { qcl_delete(pdefs); qcl_delete(pbody); } 
  }
  virtual ObjType object() const { return sROUTDEF; }
  sDefList *args() { return pargs; }
  sDefList *defs() { return pdefs; }
  sStmtList *body() { return pbody; }
  tExtRout *ext() { return pext; }
  void setsource(string f,int b,int e) { 
    filename=f; linebeg=b; lineend=e; 
    if(linebeg>lineend) linebeg=1;
  }
  string& sourcefile() { return filename; }
  int sourcebeg() { return linebeg; }
  int sourceend() { return lineend; }
  virtual string prtstr(int ind=NOINDENT) const;
  virtual string declstr() const;
  virtual void invoke(SymTable *loc,SymTable *gl,QuHeap *qh,int inv=0);
  virtual void typecheck(SymTable *loc,SymTable *gl);
  virtual void define(SymTable *loc,SymTable *gl,QuHeap *qh);
};

class sFunctDef : public sRoutDef {
public:
  sFunctDef(const tType& t,tId *i,sDefList *a,sDefList *d,sStmtList *b,int ext=0) : 
	sRoutDef(t,i,a,d,b,ext) { } 
  virtual ObjType object() const { return sFUNCTDEF; };
  virtual void invoke(SymTable *loc,SymTable *gl,QuHeap *qh,int inv=0);
};

class sProcDef : public sRoutDef {
public:
  sProcDef(tId *i,sDefList *a,sDefList *d,sStmtList *b,int ext=0) : 
	sRoutDef(tType(tVOID),i,a,d,b,ext) { }  
  virtual ObjType object() const { return sPROCDEF; }
};

class sQuOpDef : public sRoutDef {
public:
  sQuOpDef(tId *i,sDefList *a,sDefList *d,sStmtList *b,int c=0,int ext=0) : 
	sRoutDef(tType(tQUOP),i,a,d,b,c,ext) { }  
  virtual ObjType object() const { return sQUOPDEF; }
};

class sQuFunDef : public sRoutDef {
public:
  sQuFunDef(tId *i,sDefList *a,sDefList *d,sStmtList *b,int c=0,int ext=0) : 
	sRoutDef(tType(tQUOP),i,a,d,b,c,ext) { }  
  virtual ObjType object() const { return sQUFUNDEF; }
};

class sEof : public sObject {
public:
  sEof() : sObject() { }
  virtual ObjType object() const { return sEOF; }
  virtual string prtstr(int ind=NOINDENT) const;
};

class sMsg : public sObject {
  string m;
public:
  sMsg(string s) : sObject() { m=s; }
  sMsg(const char *s) : sObject() { m=s; }
  virtual ObjType object() const { return sMSG; }
  virtual string prtstr(int ind=NOINDENT) const;
  string msg() { return m; }
};

extern sVarDef CONDDEF;
  
#endif

