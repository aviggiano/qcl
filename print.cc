/**********************************************************************

This file is part of the Quantum Computation Language QCL.

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/


#pragma implementation

#include <stdlib.h>
#include <stdio.h>

#include "syntax.h"

#define IND() if(ind!=NOINDENT) \
  { int i; for(i=0;i<ind;i++) ostr+= "  "; }
#define NL() (ind==NOINDENT ? string(" ") : string("\n"))
#define INC() (ind!=NOINDENT ? ind+1 : ind)

string sObject::prtstr(int ind) const {
  return "<undef prtstr>";
}

string sObject::defstr() const {
  string s;
  sDef *d=def();
  if(!d && isRoutDef()) d=(sDef*)this;
  if(d->isRoutDef()) {
    switch(d->object()) {
      case sFUNCTDEF: s += "in function ";  break;
      case sPROCDEF:  s += "in procedure "; break;
      case sQUOPDEF:  s += "in operator ";  break;
      case sQUFUNDEF: s += "in qufunct ";  break;
      default: ;
    }
    s+=d->id();
  }
  return s;
}

string sDef::declstr() const {
  string s=prtstr();
  int l=s.length();
  if(l<2) return s;
  if(s[l-2]==';' && s[l-1]==' ')
    s.resize(s.length()-2);
  return s;
}

string sRoutDef::declstr() const {
  string ostr;
  if(isExtern()) ostr+="extern ";
  if(isCondDef()) ostr+="cond ";
  if(isFunctDef()) ostr+=type().str() + " ";
  if(isProcDef()) ostr+= "procedure ";
  if(isQuFunDef()) ostr+= "qufunct ";
  if(isQuOpDef() || isFunOp()) ostr+= "operator ";

  ostr+= id()+"("+pargs->prtstr()+")";
  return ostr;
}


/***********************************************/
/***************** Expressions *****************/
/***********************************************/


string sExprList::prtstr(int ind) const {
  string ostr;
  sExpr *e;
  void *c;
  if(isEmpty()) return "";
  ostr+=first(c)->prtstr(ind);
  while((e=next(c))) {
    ostr+= ","+e->prtstr(ind);
  };
  return ostr;
}

string sConst::prtstr(int ind) const {
  string ostr;
  if(_val.isString()) 
    ostr+= string("\"") + _val.str() + string("\""); 
  else 
    ostr+= _val.str();
  return ostr;
}

string sVar::prtstr(int ind) const {
  return id();
}

string sSubscript::prtstr(int ind) const {
  return pvar->prtstr(ind)+"["+psub->prtstr(ind)+"]";
}



string sSubRange::prtstr(int ind) const {
  string ostr;
  ostr=pvar->prtstr(ind);
  ostr+= "["+pexpr1->prtstr(ind);
  if(isSet(flagRANGE)) ostr+= ".."; else ostr+= "::";
  ostr+=pexpr2->prtstr(ind)+"]";
  return ostr;
}

string sUnOp::prtstr(int ind) const {
  string ostr;
  switch(object()) {
    case sNEG: ostr+= "-"; break;
    case sNOT: ostr+= "not "; break;
    case sLENGTH: ostr+= "#"; break;
    default: ostr+= "%UnOp% ";
  };
  ostr+=pexpr->prtstr(ind);
  return ostr;
}

string sBinOp::binop_prtstr(int ind,const sBinOp *o) const {
  string ostr;
  int par;
  if(o) {
    par=1;
    if(isCompOp() && o->isLogOp()) par=0;
    if(isArithOp() && o->isCompOp()) par=0;
    if((object()==sMULT || object()==sDIV || object()==sMOD) &&
       (o->object()==sADD || o->object()==sSUB)) par=0;
    if(object()==sPOW && o->isArithOp() && o->object()!=sPOW) par=0;
  } else {
    par=0;
  }
  if(par) ostr+= "(";
  if(pexpr1->isBinOp())
    ostr+=((sBinOp*)pexpr1)->binop_prtstr(ind,this);
  else
    ostr+=pexpr1->prtstr(ind);
  switch(object()) {
    case sADD: ostr+= "+"; break;
    case sSUB: ostr+= "-"; break;
    case sMULT: ostr+= "*"; break;
    case sDIV: ostr+= "/"; break;
    case sMOD: ostr+= " mod "; break;
    case sPOW: ostr+= "^"; break;
    case sLESS: ostr+= "<"; break;
    case sEQUAL: ostr+= "=="; break;
    case sLEEQ: ostr+= "<="; break;
    case sNOTEQ: ostr+= "!="; break;
    case sAND: ostr+= " and "; break;
    case sOR: ostr+= " or "; break;
    case sXOR: ostr+= " xor "; break;
    case sCONCAT: ostr+= "&"; break;
    default: ostr+= " %BinOp% ";
  };
  if(pexpr2->isBinOp())
    ostr+=((sBinOp*)pexpr2)->binop_prtstr(ind,this);
  else
    ostr+=pexpr2->prtstr(ind);
  if(par) ostr+=")";
  return ostr;
}

string sBinOp::prtstr(int ind) const {
  return binop_prtstr(ind,0);
}

string sFunctCall::prtstr(int ind) const {
  return id()+"("+ppar->prtstr(ind)+")";
}

string sBaseFunct::prtstr(int ind) const {
  string ostr;
  switch(object()) {
    case sEXP	 : ostr+= "exp" 	; break;
    case sSIN	 : ostr+= "sin" 	; break;
    case sCOS	 : ostr+= "cos" 	; break;
    case sTAN	 : ostr+= "tan" 	; break;
    case sCOT	 : ostr+= "cot" 	; break;
    case sSINH   : ostr+= "sinh"	; break;
    case sCOSH   : ostr+= "cosh"	; break;
    case sTANH   : ostr+= "tanh"	; break;
    case sCOTH   : ostr+= "coth"	; break;
    case sABS	 : ostr+= "abs" 	; break;
    case sRE	 : ostr+= "Re" 	  	; break;
    case sIM	 : ostr+= "Im" 	  	; break;
    case sCONJ   : ostr+= "conj"	; break;
    case sFLOOR  : ostr+= "floor"	; break;
    case sCEIL   : ostr+= "ceil"	; break;
    case sSQRT   : ostr+= "sqrt"	; break;
    case sINOT   : ostr+= "not"		; break;
    case sINT    : ostr+= "int"		; break;
    case sREAL   : ostr+= "real"	; break;
    case sCOMPLEX: ostr+= "complex"	; break;
    case sSTRING : ostr+= "string"	; break;
    default: ostr+= " %BaseFunct% ";
  };
  ostr+="("+pexpr->prtstr(ind)+")";
  return ostr;
}

string sListFunct::prtstr(int ind) const {
  string ostr;
  switch(object()) {
    case sLOG	 : ostr+= "log" 	  ; break;
    case sRANDOM : ostr+= "random" 	  ; break;
    case sMIN	 : ostr+= "min" 	  ; break;
    case sMAX	 : ostr+= "max" 	  ; break;
    case sGCD	 : ostr+= "gcd" 	  ; break;
    case sLCM	 : ostr+= "lcm" 	  ; break;
    case sBIT	 : ostr+= "bit" 	  ; break;
    case sIAND	 : ostr+= "and" 	  ; break;
    case sIOR	 : ostr+= "or" 	  	  ; break;
    case sIXOR	 : ostr+= "xor" 	  ; break;
    case sVECTOR : ostr+= "vector" 	  ; break;
    case sMATRIX : ostr+= "matrix" 	  ; break;
    case sTENSOR3:
    case sTENSOR4:
    case sTENSOR5:
    case sTENSOR6:
    case sTENSOR7:
    case sTENSOR8:
    case sTENSOR9: 
      ostr+= "tensor";
      ostr+= '0'+(object()-sSCALAR);
      break;
    default: ostr+= " %ListFunct% ";
  };
  ostr+="("+pexpr->prtstr(ind)+")";
  return ostr;
}


/***********************************************/
/***************** Statements ******************/
/***********************************************/


string sStmtList::prtstr(int ind) const {
  string ostr;
  sStmt *s;
  void *c;
  if(isEmpty()) return "";
  ostr+=first(c)->prtstr(ind);
  while((s=next(c))) ostr+=s->prtstr(ind);
  return ostr;
}

string sCall::prtstr(int ind) const {
  string ostr;
  IND();
  if(isInv()) ostr+="!";
  ostr+= id() + "("+ppar->prtstr(ind)+");"+NL();
  return ostr;
}

string sAssign::prtstr(int ind) const {
  string ostr;
  IND();
  ostr+=pvar->prtstr(ind);
  if(psubs) ostr+="["+psubs->prtstr(ind)+"]";
  ostr+=" = "+pexpr->prtstr(ind)+ ";"+NL();
  return ostr;
}

string sFor::prtstr(int ind) const {
  string ostr;
  IND();
  ostr+= "for "+pvar->prtstr(ind)+ " = ";
  ostr+=pfrom->prtstr(ind)+ " to ";
  ostr+=pto->prtstr(ind);
  if(pstep) { ostr+= " step "; ostr+=pstep->prtstr(ind); };
  ostr+= " {"+NL();
  ostr+=pbody->prtstr(INC());
  IND();
  ostr+="}"+NL();
  return ostr;
}

string sIf::prtstr(int ind) const {
  string ostr;
  IND();
  ostr+= "if "+pcond->prtstr(ind); ostr+= " {";
  if(isSet(flagQUFORK)) ostr+="  // forking";
  ostr+=NL();
  ostr+=pthen->prtstr(INC());
  if(pelse) { 
    IND();
    ostr+= "} else {"+NL()+pelse->prtstr(INC());
  };
  IND();
  ostr+="}"+NL();
  return ostr;
}

string sWhile::prtstr(int ind) const {
  string ostr;
  IND();
  ostr+= "while "+cond()->prtstr(ind)+" {"+NL();
  ostr+=body()->prtstr(INC());
  IND();
  ostr+="}"+NL();
  return ostr;
}

string sUntil::prtstr(int ind) const {
  string ostr;
  IND();
  ostr+= "{"+NL();
  ostr+=body()->prtstr(INC());
  IND();
  ostr+="} until "+cond()->prtstr(ind)+";"+NL();
  return ostr;
}

string sBreak::prtstr(int ind) const {
  string ostr;
  IND();
  ostr+= "break;"+NL();
  return ostr;
}

string sReturn::prtstr(int ind) const {
  string ostr;
  IND();
  ostr+= "return "+pexpr->prtstr(ind); ostr+= ";"+NL();
  return ostr;
}

string sInput::prtstr(int ind) const {
  string ostr;
  IND();
  ostr+= "input ";
  if(pprompt) ostr+=pprompt->prtstr()+",";
  ostr+= pvar->prtstr()+";"+NL();
  return ostr;
}

string sPrint::prtstr(int ind) const {
  string ostr;
  IND();
  ostr+="print "+plist->prtstr()+";"+NL();
  return ostr;
}

string sExit::prtstr(int ind) const {
  string ostr;
  IND();
  ostr+="exit";
  if(pmsg) ostr+=" "+pmsg->prtstr();
  ostr+=";"+NL();
  return ostr;
}

string sMeasure::prtstr(int ind) const {
  string ostr;
  IND();
  ostr+= "measure ";
  ostr+= pstate->prtstr();
  if(pvar) ostr+=","+pvar->prtstr();
  ostr+=";"+NL();
  return ostr;
}

string sInclude::prtstr(int ind) const {
  string ostr;
  IND();
  ostr+="include \""+fname+"\";"+NL();
  return ostr;
}

string sReset::prtstr(int ind) const {
  string ostr;
  IND();
  ostr+="reset;"+NL();
  return ostr;
}


/***********************************************/
/****************** Commands *******************/
/***********************************************/


string sDump::prtstr(int ind) const {
  string ostr;
  IND();
  ostr+="dump";
  if(pexpr) ostr+=" "+pexpr->prtstr();
  ostr+=";"+NL();
  return ostr;
}

string sPlot::prtstr(int ind) const {
  string ostr;
  IND();
  return ostr+"shell;"+NL();
}

string sInspect::prtstr(int ind) const {
  string ostr;
  IND();
  ostr+="list";
  if(plist) ostr+=" "+plist->prtstr();
  ostr+=";"+NL();
  return ostr;
}

string sLoad::prtstr(int ind) const {
  string ostr;
  IND();
  ostr+="load";
  if(pexpr) ostr+=" "+pexpr->prtstr();
  ostr+=";"+NL();
  return ostr;
}

string sSave::prtstr(int ind) const {
  string ostr;
  IND();
  ostr+="save";
  if(pexpr) ostr+=" "+pexpr->prtstr();
  ostr+=";"+NL();
  return ostr;
}

string sSet::prtstr(int ind) const {
  string ostr;
  IND();
  ostr+="set "+opt;
  if(pexpr) ostr+=" "+pexpr->prtstr();
  ostr+=";"+NL();
  return ostr;
}

string sShell::prtstr(int ind) const {
  string ostr;
  IND();
  return ostr+"shell;"+NL();
}

/***********************************************/
/***************** Definitions *****************/
/***********************************************/


string sDefList::prtstr(int ind) const {
  string ostr;
  sDef *d;
  void *c;
  if(isEmpty()) return "";
  ostr+=first(c)->prtstr(ind);
  while((d=next(c))) {
    if(d->object()==sARGDEF) ostr+= ",";    
    ostr+=d->prtstr(ind);
  }
  return ostr;
}

string sArgDef::prtstr(int ind) const {
  string ostr;
  ostr+= type().str() + " " + id();
  return ostr;
}

string sVarDef::prtstr(int ind) const {
  string ostr;
  IND();
  ostr+= type().str() + " " + id();
  if(plen) { ostr+= "["+plen->prtstr(ind)+ "]"; }
  if(pinit) { ostr+= " = "+pinit->prtstr(ind); }
  ostr+= ";"+NL();
  return ostr;
}

string sConstDef::prtstr(int ind) const {
  string ostr;
  IND();
  ostr+= "const " + id() + " = ";
  ostr+=pexpr->prtstr(ind); ostr+= ";"+NL(); 
  return ostr;
}

string sRoutDef::prtstr(int ind) const {
  string ostr;
  IND();
  ostr+=declstr();
  if(isExtern()) { 
    ostr+= ";"+NL();
  } else {
    ostr+=" {"+NL()+pdefs->prtstr(INC())+pbody->prtstr(INC());
    IND();
    ostr+="}"+NL();
  }
  return ostr;
}

string sEof::prtstr(int ind) const {
  return "";
}

string sMsg::prtstr(int ind) const {
  return "";
}

#undef IND
#undef NL
#undef INC
