/**********************************************************************

This file is part of the Quantum Computation Language QCL.

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/


#pragma implementation

#include "syntax.h"
#include "error.h"
#include "options.h"

#include <stdlib.h>

#define TRACE() if (optTrace) qcltrace("TYPECHECK",this,loc,gl,0)

#define CHECK(p) if(p) {	\
    p->setParent(this);		\
    p->typecheck(loc,gl);	\
}


/***********************************************/
/***************** Definitions *****************/
/***********************************************/


void sVarDef::typecheck(SymTable *loc,SymTable *gl) {
  TRACE();
  CHECK(plen);
  CHECK(pinit);
  if(def()) {
    if(loc && loc->getDef(id())) 
      throw tError(errSCOPE,"local symbol "+id()+" already defined",this);
  } else {
    if(gl && gl->getDef(id())) {
      if(optAllowRedefines) throw tError(errIGNORE);
      throw tError(errSCOPE,"global symbol "+id()+" already defined",this);
    }  
  };
  if(type().isQuExpr()) {
    if(inFunctDef()) 
      throw tError(errSCOPE,"quantum Variables may non be defined within functions",this);
    if(type()==tQUSCR && !inQuFunDef())
      throw tError(errSCOPE,"scratch Space may only be allocated within quantum functions",this);
    if(type()==tQUVOID)
      throw tError(errSCOPE,"void Registers have to be arguments",this);
    if(plen && pinit) 
      throw tError(errDEF,"quantum variable can either be allocated or defined as reference, not both",this);
    if(plen && !plen->type().isInt()) 
      throw tError(errDEF,"invalid length",this);
    if(pinit && !pinit->type().isQuExpr()) 
      throw tError(errTYPMIS,"invalid initialiser for quantum register reference",this);
    if(!plen && !pinit) 
      throw tError(errDEF,"quantum variable must be allocated or initialized",this);
    if(isSet(flagCONDDEF)) {
      if(!inQuDef() || !def()->isCondDef())
        throw tError(errDEF,"explicit enable register outside conditional operator",this);
      def()->setFlag(flagCOND,0);
    }
  } else {
    if(plen && !ord()) throw tError(errDEF,"length specified for scalar type",this);
    if(pinit && !pinit->type().isConv(type())) 
      throw tError(errTYPMIS,"invalid initialisation",this);
  };
  if(def()) if(loc->put(this)) 
    throw tError(errINT,"cannot add symbol to symtab",this);
  if(def() && type()==tQUSCR) ((sQuFunDef*)def())->setBennet(1);
}

void sConstDef::typecheck(SymTable *loc,SymTable *gl) {
  TRACE();
  CHECK(pexpr);

  if(def()) {
    if(loc && loc->getDef(id())) 
      throw tError(errSCOPE,"local symbol "+id()+" already defined",this);
  } else {
    if(gl && gl->getDef(id())) {
      if(optAllowRedefines) throw tError(errIGNORE);
      throw tError(errSCOPE,"global symbol "+id()+" already defined",this);
    }
  };
  if(pexpr->type().isQuExpr()) 
    throw tError(errTYPMIS,"quantum variables cannot be defined as constant",this);
  settype(pexpr->type());
  if(def()) if(loc->put(this)) throw tError(errINT,"cannot add symbol "+id()+" to symtab",this);
}

void sRoutDef::typecheck(SymTable *loc,SymTable *gl) {
  sDef *p;
  SymTab l,g;
  SymTabComb *psym;
  void *c;
  int i;
  int f=0;
  TRACE();
  
  if(gl && gl->getDef(id())) {
    if(optAllowRedefines) throw tError(errIGNORE);
    throw tError(errSCOPE,"global symbol "+id()+" already defined",this);
  }  
  if(def()) 
    throw tError(errSCOPE,"subroutines may only be defined in global scope",this);
  if(pdefs) pdefs->setParent(this);
  if(pbody) pbody->setParent(this);
  CHECK(pargs);
  for_plist(p,pargs,c) {
    if(l.getRef(p->id())) throw tError(errINVPAR,"duplicate parameter",this);
    if(isFunctDef() && (p->type().isQuExpr() && !p->type().isQuConst())) 
      throw tError(errINVPAR,"functions may only depend on quconst registers",this);
    if(p->type().isQuReg()) f=1;  
    l.put(p);
  };
  if(isExtern()) {
    pext=0;
    for(i=0;ExtRoutTable[i].rout;i++) {
      if(id()==string(ExtRoutTable[i].id)) {
        pext=ExtRoutTable[i].rout;
        break;
      }
    }
    if(!pext) throw tError(errEXT,"external routine "+id()+" not found",this);
  } else {
//    if(isFunctDef()) g.put(this);
    if(isRoutDef()) g.put(this);
    if(isCondDef()) l.put(&CONDDEF);
    psym=new SymTabComb(&g,gl);
    try {
      pdefs->typecheck(&l,psym);
    } catch(...) {
      qcl_delete(psym);
      throw;
    }
    if(isQuFunDef() && f && isBennet()) {
      qcl_delete(psym);
      throw tError(errINVTYP,"local scratch registers can't be used with qureg arguments",this);  
    }
    try {
      pbody->typecheck(&l,psym);
    } catch(...) {
      qcl_delete(psym); 
      throw; 
    }
    qcl_delete(psym);
  }
}

void sDefList::typecheck(SymTable *loc,SymTable *gl) {
  sDef *p;
  void *c;
  TRACE();
  for_plist(p,this,c) {
    CHECK(p);
  }
}


/***********************************************/
/***************** Statements ******************/
/***********************************************/


void sStmtList::typecheck(SymTable *loc,SymTable *gl) {
  sStmt *p;
  void *c;
  TRACE();
  for_plist(p,this,c) {
    CHECK(p);
  }
}

void sCall::typecheck(SymTable *loc,SymTable *gl) {
  sRoutDef *d;
  sExpr *p;
  sDef *q;
  string s;
  void *cp,*cq;
  tType pt,qt;
  TRACE();
  d=(sRoutDef*)gl->getDef(id());
  if(!d || !d->isRoutDef() || d->isFunctDef()) 
    throw tError(errSYMBOL,"undefined procedure or operator "+id(),this);
  if(inFunctDef()) 
    throw tError(errSCOPE,"calls not allowed within functions",this);
  if(inQuDef()) {
    if(d->isProcDef())
      throw tError(errSCOPE,"procedure call within operator",this);
  }
  if(!d->isCondDef() && isSetRec(flagCOND))
    throw tError(errSCOPE,"only conditional operators allowed in this scope",this);
  if(inQuFunDef() && d->isQuOpDef() && !inFunOp())
     throw tError(errSCOPE,"operator called within qufunct",this);
  for_pplist(p,ppar,cp,q,d->args(),cq,p || q) {
    if(!p || !q) throw tError(errPARMIS,"unmatching argument number",this);
    CHECK(p);
    pt=p->type(); qt=q->type();
    if(!pt.isConv(qt))
      throw tError(errPARMIS,"unmatching argument types",this);
    if(pt.isQuConst() && !qt.isQuConst())
      throw tError(errPARMIS,"quconst used as non-const argument to "+id(),this); 
    if(pt.isQuExpr()) p->settype(q->type());
  };
}

void sAssign::typecheck(SymTable *loc,SymTable *gl) {
  sDef *d;
  void *c;
  sExpr *p;
  TRACE();
  setFlagRec(flagASSIGN);
  CHECK(pvar);
  CHECK(pexpr);
  CHECK(psubs);
  d=loc->getDef(pvar->id());
  if(!d && isLocal()) 
    throw tError(errSYMBOL,"unknown local variable "+pvar->id(),this);
  if(!d) d=gl->getDef(pvar->id());
  if(!d || d->object()!=sVARDEF) 
    throw tError(errSYMBOL,"unknown variable "+pvar->id(),this);
  if(d->type().isQuExpr()) 
    throw tError(errINVTYP,"assignment to quantum variable",this);
  if(inProcDef() && d->type().isQuCond())
    throw tError(errSCOPE,"local assignment to global qucond variable",this);
  if(psubs) {
    if(!d->type().ord())
      throw tError(errINVTYP,pvar->id()+" is not a tensor variable",this);
    if(d->type().ord()!=psubs->n())
      throw tError(errINVTYP,"invalid number of indices",this);    
    for_plist(p,psubs,c)
      if(!p->type().isInt())
        throw tError(errTYPMIS,"index must be integer",this);
    if(!pexpr->type().isConv(d->type().basetype()))
      throw tError(errTYPMIS,"invalid assignment",this);
  } else {
    if(!pexpr->type().isConv(d->type()))
      throw tError(errTYPMIS,"invalid assignment",this);
  }
}

void sFor::typecheck(SymTable *loc,SymTable *gl) {
  sDef *p;
  sConstDef *pv;
  SymTab sym;
  SymTabComb *psym;
  TRACE();
  CHECK(pvar);
  if(pbody) pbody->setParent(this);
  p=loc->getDef(pvar->id());
  if(!p && isLocal()) 
    throw tError(errSYMBOL,"unknown local variable "+pvar->id(),this);
  if(!p) p=gl->getDef(pvar->id());
  if(!p || p->object()!=sVARDEF) 
    throw tError(errSYMBOL,"invalid Symbol type",this);
  CHECK(pfrom);
  CHECK(pto);
  if(pstep) CHECK(pstep);
  if(!pfrom->type().isInt() || !pto->type().isInt() ||
    (pstep && !pstep->type().isInt())) 
    throw tError(errINVTYP,"for loop parameters must be integer",this);
  pv=new sConstDef(new tId(p->id()),(sExpr*)new sConst(tValue(0)));
  if(!pv) throw tError(errINT,"alloc failed",this);
  pv->settype(tType(tINTEGER));
  sym.put(pv);
  psym=new SymTabComb(&sym,loc);
  try {
    pbody->typecheck(psym,gl);
  } catch(...) {
    qcl_delete(psym);
    qcl_delete(pv);
    throw;
  }
  qcl_delete(psym);
  qcl_delete(pv);
}

void sIf::typecheck(SymTable *loc,SymTable *gl) {
  TRACE();
  CHECK(pcond);
  tType t=pcond->type();
  if(!t.isBoolean() && !t.isQuCond()) 
    throw tError(errTYPMIS,"invalid if-condition",this);
  if(t.isQuCond()) setFlag(flagCOND);
  CHECK(pthen);
  CHECK(pelse);
  if(t.isQuCond()) {
    if(isDirty()) {
      if(!inQuDef())
        throw tError(errSCOPE,"forking quantum condition outside operator definition",this);
      setFlag(flagQUFORK);
    } else {
      setFlag(flagQUIF);
    }
  }
}

void sLoop::typecheck(SymTable *loc,SymTable *gl) {
  TRACE();
  CHECK(pcond);
  if(!pcond->type().isBoolean()) 
    throw tError(errTYPMIS,"not boolean loop condition",this);
  CHECK(pbody);
}

void sBreak::typecheck(SymTable *loc,SymTable *gl) {
  TRACE();
  if(!def()) throw tError(errSCOPE,"break statement outside routine",this);
  setFlagRec(flagBREAK);
}

void sReturn::typecheck(SymTable *loc,SymTable *gl) {
  TRACE();
  CHECK(pexpr);
  if(!inFunctDef()) 
    throw tError(errSCOPE,"return statement outside function",this);
  if(!pexpr->type().isConv(def()->type()))
    throw tError(errTYPMIS,"return expression doesn't match function type",this);
}

void sInput::typecheck(SymTable *loc,SymTable *gl) {
  sDef *p;
  TRACE();
  CHECK(pprompt);
  CHECK(pvar);
  if(isLocal()) 
    throw tError(errSCOPE,"input not allowed in this scope",this);
  if(pprompt && !pprompt->type().isString())
    throw tError(errINVTYP,"input prompt is no string",this);

  p=loc->getDef(pvar->id());
  if(!p && isLocal()) 
    throw tError(errSYMBOL,"unknown local variable "+pvar->id(),this);
  if(!p) p=gl->getDef(pvar->id());
  if(!p || p->object()!=sVARDEF) 
    throw tError(errSYMBOL,"unknown variable "+pvar->id(),this);
  if(pvar->type().isQuExpr())
    throw tError(errINVTYP,"cannot input quantum variables",this);
}

void sPrint::typecheck(SymTable *loc,SymTable *gl) {
  TRACE();
  CHECK(plist);
}

void sExit::typecheck(SymTable *loc,SymTable *gl) {
  TRACE();
  CHECK(pmsg);
  if(pmsg && !pmsg->type().isString()) 
    throw tError(errSCOPE,"error message is not a string",this);
}

void sMeasure::typecheck(SymTable *loc,SymTable *gl) {
  sDef *p;
  TRACE();
  CHECK(pstate);
  CHECK(pvar);
  if(isLocal()) 
    throw tError(errSCOPE,"measurement is not allowed in this scope",this);
  if(!pstate || !pstate->type().isQuExpr())
    throw tError(errINVTYP,"quantum state required",this);

  if(pvar) {
    p=loc->getDef(pvar->id());
    if(!p && isLocal()) 
      throw tError(errSYMBOL,"unknown local variable "+pvar->id(),this);
    if(!p) p=gl->getDef(pvar->id());
    if(!p || p->object()!=sVARDEF) 
      throw tError(errSYMBOL,"unknown variable "+pvar->id(),this);
    if(!pvar->type().isInt())
      throw tError(errINVTYP,"quantum eigenstates are integers",this);
  }
}

void sInclude::typecheck(SymTable *loc,SymTable *gl) {
  TRACE();
  throw tError(errINT,"uncaught include",this);
}


void sReset::typecheck(SymTable *loc,SymTable *gl) {
  TRACE();
  if(isLocal()) 
    throw tError(errSCOPE,"reset of quantum state is not allowed in this  scope",this);
}

/***********************************************/
/****************** Commands *******************/
/***********************************************/


void sDump::typecheck(SymTable *loc,SymTable *gl) {
  TRACE();
  CHECK(pexpr);
  if(pexpr && !pexpr->type().isQuExpr())
    throw tError(errINVTYP,"quantum expression required",this);
}

void sPlot::typecheck(SymTable *loc,SymTable *gl) {
  TRACE();
  CHECK(pexpr1);
  CHECK(pexpr2);
  if(pexpr1 && !pexpr1->type().isQuExpr() || pexpr2 && !pexpr2->type().isQuExpr())
    throw tError(errINVTYP,"quantum expression required",this);
}

void sInspect::typecheck(SymTable *loc,SymTable *gl) {
  sExpr *p;
  void *c;
  TRACE();
  if(plist) {
    for_plist(p,plist,c) {
      if(!p || p->object()!=sVAR)
  	throw tError(errINVTYP,"can only list symbols",this);
    };
  };
}

void sLoad::typecheck(SymTable *loc,SymTable *gl) {
  TRACE();
  CHECK(pexpr);
  if(pexpr && !pexpr->type().isString())
    throw tError(errINVTYP,"filename must be a string",this);
}

void sSave::typecheck(SymTable *loc,SymTable *gl) {
  TRACE();
  CHECK(pexpr);
  if(pexpr && !pexpr->type().isString())
    throw tError(errINVTYP,"filename must be a string",this);
}

void sSet::typecheck(SymTable *loc,SymTable *gl) {
  int i;
  tValue v;
  string s;
  TRACE();
  CHECK(pexpr);
  if(pexpr && pexpr->type().isQuExpr())
    throw tError(errINVTYP,"quantum expression as option argument",this); 
  for(i=0;qcl_options[i].val;i++) {
    if(opt==string(qcl_options[i].name)) goto cont;
  }
  throw tError(errOPT,"illegal option "+opt,this);
cont:
  if(qcl_options[i].has_arg && !pexpr)
    throw tError(errOPT,"missing argument for option "+opt,this);
  if(!qcl_options[i].has_arg && pexpr)
    throw tError(errOPT,"option "+opt+" takes no argument",this);
}

/***********************************************/
/***************** Expressions *****************/
/***********************************************/


void sExprList::typecheck(SymTable *loc,SymTable *gl) {
  sExpr *p;
  void *c;
  TRACE();
  for_plist(p,this,c) {
    CHECK(p);
  };
}

void sConst::typecheck(SymTable *loc,SymTable *gl) {
  TRACE();
  if(!_val.type().isDefined()) throw tError(errINT,"undefined constant",this);
  settype(_val.type());
}

void sVar::typecheck(SymTable *loc,SymTable *gl) {
  sDef *p,*q=0;
  TRACE();
  p=loc->getDef(id());
  if(!p) q=gl->getDef(id());
  if(!p && q && (q->isConstDef() || isGlobal())) p=q;
  if(!p && isLocal()) 
    throw tError(errSYMBOL,"unknown local variable "+id(),this);
  if(!p) p=q;
  if(!p || !p->isValueDef()) 
    throw tError(errSYMBOL,"unknown variable or constant "+id(),this);
  settype(p->type());
}

void sSubscript::typecheck(SymTable *loc,SymTable *gl) {
  TRACE();
  CHECK(pvar);
  CHECK(psubs);
  void *c;
  sExpr *p;
  tType t=pvar->type();
  if(!t.isQuExpr() && !t.ord() && !t.isQuCond()) 
    throw tError(errINVTYP,"subscript on integral type",this);
  if(t.ord() && nargs()!=t.ord() || !t.ord() && nargs()!=1)
    throw tError(errINVTYP,"invalid number of indices",this);    
  for_plist(p,psubs,c) {                                        
    if(!p->type().isInt())                                      
      throw tError(errTYPMIS,"index must be integer",this);          
  }
  if(t.isQuCond() && !t.isQuExpr())
    settype(tQUCONST);
  else
    settype(pvar->basetype());
}

void sSubRange::typecheck(SymTable *loc,SymTable *gl) {
  TRACE();
  CHECK(pvar);
  CHECK(pexpr1);
  CHECK(pexpr2);
  if(!pvar->type().isQuExpr()) 
    throw tError(errINVTYP,"bit selection on quantum variable",this);
  if(!pexpr1->type().isInt() || !pexpr2->type().isInt()) 
    throw tError(errINVTYP,"subrange parameters not integer",this);
  settype(pvar->type());
}

void sUnOp::typecheck(SymTable *loc,SymTable *gl) {
  TRACE();
  CHECK(pexpr);
  tType t=pexpr->type();
  switch(object()) {
    case sNEG:
      if(!t.isNumber() && !t.ord()) 
        throw tError(errINVTYP,"unary Minus: argument is not numeric",this);
      settype(pexpr->type());
      break;
    case sNOT:
      if(t.isBoolean()) {
        settype(pexpr->type());
        break;
      }
      if(t.isQuCond()) {
        settype(tType(tQUCOND));
        break;
      }
      throw tError(errINVTYP,"negation: invalid argument",this);
      break;
    case sLENGTH:
      if(!t.isQuExpr() && !t.ord() && !t.isQuCond()) 
        throw tError(errINVTYP,"length operator used on scalar type",this);
      settype(tType(tINTEGER));
      break;
    default:
      throw tError(errINT,"invalid unary operator",this);
  }
}

void sBinOp::typecheck(SymTable *loc,SymTable *gl) {
  tType t1,t2;
  TRACE();
  CHECK(pexpr1);
  CHECK(pexpr2);
  t1=pexpr1->type();
  t2=pexpr2->type();
  
  if(t1.ord() || t2.ord()) {
    BaseType bt=(BaseType)MAX(t1.basetype(),t2.basetype());
    if(object()==sADD || object()==sSUB) {
      if(t1.ord()!=t2.ord()) 
        throw tError(errTYPMIS,"tensors are of different order",this);
      settype(tType(bt,t1.ord()));
      return;
    } 
    if(object()==sMULT || object()==sDIV) {
      if(t1.ord() && t2.ord()) {
        settype(tType(bt,t1.ord()+t2.ord()-2));
        return;
      }
      if(!t1.isNumber() && !t2.isNumber())
        throw tError(errTYPMIS,"invalid tensor operation",this);
      if(object()==sDIV && t2.ord())
        throw tError(errTYPMIS,"divisor must be scalar",this);
      settype(tType(bt,MAX(t1.ord(),t2.ord())));  
      if(t1.isNumber()) {
        sExpr *p=pexpr1;
        pexpr1=pexpr2;
        pexpr2=p;
      }
      return;
    }
    throw tError(errINVTYP,"invalid tensor operation",this);
  }

  switch(object()) {
    case sMOD:
      if(t1!=tINTEGER || t2!=tINTEGER) 
        throw tError(errINVTYP,"modulus arguments must be integer",this);    
    case sADD:
    case sSUB:
    case sMULT:
    case sDIV:
    case sPOW:    
      if(!t1.isNumber() || !t2.isNumber()) 
        throw tError(errINVTYP,"non numeric argument to binary arithmetic operator",this);
      if(t1==tINTEGER && t2==tINTEGER) { 
        settype(tType(tINTEGER));
        break;
      }
      if(t1==tCOMPLEX || t2==tCOMPLEX) {
        settype(tType(tCOMPLEX));
        break;
      }
      settype(tType(tREAL));
      break;
      
    case sLEEQ:
    case sLESS:
      if(!t1.isOrdered() || !t2.isOrdered())
        throw tError(errINVTYP,"comparison operator with unordered type",this);
      if(t1.isQuExpr() || t2.isQuExpr()) 
        throw tError(errINVTYP,"cannot compare quantum expressions",this);
    case sNOTEQ:
    case sEQUAL:
      if(t1.isQuExpr() || t2.isQuExpr()) {
        if(!t1.isQuExpr() && !t1.isInt() ||
           !t2.isQuExpr() && !t2.isInt()) 
          throw tError(errINVTYP,"invalid quantum condition",this); 
        settype(tType(tQUCOND));
        break;
      }
      if(t1.isCond() || t2.isCond())
        throw tError(errINVTYP,"cannot compare boolean values",this); 
      if((!t1.isNumber() || !t2.isNumber()) && t1!=t2)
        throw tError(errINVTYP,"comparison type mismatch",this);
      settype(tType(tBOOLEAN));
      break;  
    
    case sAND:
    case sOR:
    case sXOR:
      if(t1.isBoolean() && t2.isBoolean()) { 
        settype(tType(tBOOLEAN));
        break;
      }
      if(t1.isCond() && t2.isCond()) { 
        settype(tType(tQUCOND));
        break;
      }
      throw tError(errINVTYP,"logical operator type mismatch",this);
      break;  

    case sCONCAT:
      if(t1.isQuExpr() && t2.isQuExpr()) {
        if(t1==t2) { settype(t1); break; };
        if(t1.isQuConst() || t2.isQuConst()) { settype(tType(tQUCONST)); break; }
        settype(tType(tQUREG));
        break;
      }
      if(t1.isString() && t2.isString()) {
        settype(tType(tSTRING));
        break;
      }
      throw tError(errINVTYP,"concatenation of invalid types",this);

    default:
      throw tError(errINT,"invalid binary operator",this);
  }
}

void sFunctCall::typecheck(SymTable *loc,SymTable *gl) {
  sRoutDef *d;
  sExpr *p;
  sDef *q;
  string s;
  void *cp,*cq;
  TRACE();
  d=(sRoutDef*)gl->getDef(id());
  if(!d || !d->isFunctDef()) 
    throw tError(errSYMBOL,"undefined function "+id(),this);
  for_pplist(p,ppar,cp,q,d->args(),cq,p || q) {
    if(!p || !q) throw tError(errPARMIS,"unmatching argument number",this);
    CHECK(p);
    if(!p->type().isConv(q->type()))
      throw tError(errPARMIS,"unmatching argument types",this);
  };
  settype(d->type());
}

void sBaseFunct::typecheck(SymTable *loc,SymTable *gl) {
  tValue v;
  tType t;
  TRACE();
  CHECK(pexpr);
  t=pexpr->type();
  if(isTrigFunct() || object()==sEXP || object()==sSQRT) {
    if(!t.isNumber()) 
      throw tError(errTYPMIS,"argument is not a number",this);
    if(pexpr->type().isComplex()) 
      settype(tType(tCOMPLEX));
    else
      settype(tType(tREAL));    
  } else if(isTypecast()) {
    switch(object()) {
      case sSTRING:
        settype(tType(tSTRING));
        return;
      case sCOMPLEX:
        if(!t.isNumber() && !t.isBoolean()) break;
        settype(tType(tCOMPLEX));
        return;
      case sREAL:
        if(!t.isReal() && !t.isInt() && !t.isBoolean()) break;
        settype(tType(tREAL));
        return;
      case sINT:
        if(!t.isInt() && !t.isBoolean()) break;
        settype(tType(tINTEGER));
        return;
      default: ;
    }
    throw tError(errTYPMIS,"invalid typecast",this);
  } else {
    if(!t.isNumber()) 
      throw tError(errTYPMIS,"argument is not a number",this);
    switch(object()) {
      case sABS:
        if(t.isInt()) 
          settype(tType(tINTEGER));
        else
          settype(tType(tREAL)); 
        break;   
      case sRE: 
      case sIM:
        settype(tType(tREAL));
        break;
      case sCONJ: 
        settype(tType(tCOMPLEX));
        break;
      case sFLOOR: 
      case sCEIL: 
        if(t.isComplex())
          throw tError(errTYPMIS,"ordered type required",this);
        settype(tType(tINTEGER));
        break;
      case sINOT:
        if(!t.isInt())
          throw tError(errTYPMIS,"integer required",this);
        settype(tType(tINTEGER));
        break;  
      default:
        throw tError(errINT,"unknown base function",this);
    }
  }
}

void sListFunct::typecheck(SymTable *loc,SymTable *gl) {
  tValue v;
  tType t;
  int argc;
  void *c;
  sExpr *p;
  TRACE();
  CHECK(pexpr);
  if(pexpr1) t=pexpr1->type();
  argc=pexpr->n();
  switch(object()) {
    case sLOG:
      if(!pexpr1 || argc>2)
    	throw tError(errSYNTAX,"invalid number of arguments to log",this);
      if(!pexpr1->type().isNumber() || (pexpr2 && !pexpr2->type().isOrdered()))
    	throw tError(errTYPMIS,"invalid log argument",this);
      if(t.isComplex())
    	settype(tType(tCOMPLEX));
      else
    	settype(tType(tREAL));
      return;
    case sRANDOM:
      if(isLocal())
        throw tError(errSCOPE,"function random is not allowed in this scope",this); 
      if(argc) throw tError(errSYNTAX,"function random takes no arguments",this);
      settype(tType(tREAL));
      return;
    case sMIN:
    case sMAX:
      if(!argc) throw tError(errSYNTAX,"missing argument",this);
      settype(tType(tINTEGER));
      for_plist(p,pexpr,c) {
        if(!p->type().isOrdered()) 
          throw tError(errTYPMIS,"argument of unordered type",this);
        if(p->type().isReal()) settype(tType(tREAL));
      }
      return;
    case sGCD:
    case sLCM:
    case sIAND:
    case sIOR:
    case sIXOR:
      if(!argc) throw tError(errSYNTAX,"missing argument",this);
      for_plist(p,pexpr,c) {
        if(!p->type().isInt()) 
          throw tError(errTYPMIS,"integer required",this);
      }
      settype(tType(tINTEGER));
      return;
    case sBIT:
      if(argc!=2) throw tError(errSYNTAX,"bit expects two arguments",this);
      if(!pexpr1->type().isInt() || !pexpr2->type().isInt())
        throw tError(errTYPMIS,"integer required",this);
      settype(tType(tBOOLEAN));
      return;
    default: 
      if(!isTensor()) break;
      int order=object()-sSCALAR;
      if(!tensordim(order,argc))
        throw tError(errTYPMIS,"invalid number of tensor elements",this);
      BaseType t=tINTEGER;
      for_plist(p,pexpr,c) {
        if(!p->type().isNumber()) 
          throw tError(errTYPMIS,"tensor element is not a number",this);
        if(p->type().isReal()) t=tREAL;
        if(p->type().isComplex()) { t=tCOMPLEX; break; }
      }
      settype(tType(t,order));
      return;
  }
  throw tError(errINT,"unknown list function",this);
}    
