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
#include "error.h"
#include "quheap.h"
#include "debug.h"
#include "options.h"
#include "dump.h"

#define ERR (-1)
#define RET (-2)
#define BRK (-3)

#define EXERR(e,s) { 		\
  err->report(e,this);			\
  err->remark(s);			\
  err->line(prtstr(),0);		\
  if(optDebug) qclshell(loc,gl,qh,this,err,DB_ERROR); \
  return ERR;				\
}

sVarDef CONDDEF(tQUCONST,new string(CONDID));

void sRoutDef::invoke(SymTable *loc,SymTable *gl,QuHeap *qh,int inv) {
  int i;
  void *c;
  sDef *p;
  tValue *pv,*qv;
  tValue v;
  int f;
  ostream *log=&cout;
  
  if(optCheck) {
    for_plist(p,args(),c) {
      if(!inv && p->type().isQuVoid() || p->type().isQuScr()) {
        pv=loc->getRef(p->id());
	if(!pv || !pv->isQuExpr()) 
	  throw tError(errINT,"invalid quantum parameter",this);
	i=pv->qustate()->mapbits();
	if(pv->qustate()->prob(bitvec(i))<(1.0-EPSILON_CHECK))
	  throw tError(errMEM,"void or scratch register not empty",this);
      }
    }
  }

  if(irqFlag==IRQ_SHELL) qclshell(loc,gl,qh,this,DB_IRQ);
  if(irqFlag==IRQ_EXIT) throw tError(errIRQ,"execution aborted");

  if(isExtern()) {
    if(optLog) {
      if(optLogfile) log=optLogfile;
      *log << "@ ";
      if(inv) *log << "!";
      *log << id() << "(";
      f=0;
      for_plist(p,args(),c) {
        if(f) *log << ","; else f=1;
        *log << p->prtstr() << "=";
	if((pv=loc->getRef(p->id()))) {
	  *log << pv->str();
	} else {
	  *log << "undefined";
	}
      }
      if(isCondDef() && (pv=loc->getRef(CONDID))) 
        *log << ";" CONDID "=" << pv->str();
      *log << ")\n";
    };
    if(!optTest) {
      isStateModified=1;
      (pext)(this,loc,inv);
      if(optLogState) dump_state(qh,optLogfile);
    }
    return;
  }
  
  SymTab l;
  SymTabComb lcomb((SymTable*)&l,loc);
  QuHeap lqh(qh,isQuDef());

  if(isBennet()) {
    for_plist(p,args(),c) {
      if(p->type().isQuVoid()) {
        pv=loc->getRef(p->id());
        if(!pv || !pv->isQuExpr()) 
	  throw tError(errINT,"invalid quantum parameter",this);
        v=lqh.qualloc(pv->qustate()->mapbits());
	if(v.isError())
	  throw tError(errMEM,"can't allocate internal scratch space",this);
	l.put(p,v);
      }
    }
  }

  if(isCondDef() && isCond()) {
    pv=loc->getRef(CONDID);
    if(!pv || !pv->isQuConst())
      throw tError(errINT,"undefined quantum condition");
    lqh.qcond(pv->qustate(),gl);
  }

  QuHeap *pqh=&lqh;
  int forks=0;

  do {
    SymTab ll;
    SymTabComb llcomb((SymTable*)&ll,&lcomb);
    forks++;
    if(forks>1) pqh=new QuHeap(&lqh);
    try {
      defs()->define(&llcomb,gl,pqh);
      body()->exec(&llcomb,gl,&lqh);
    } catch(sBreak *p) {
    }
    if(forks>1) delete pqh;
  } while(lqh.qendfork(gl));

  if(isBennet()) {                                           
    lqh.apply(gl,0); 
    for_plist(p,args(),c) {                                  
      if(p->type().isQuVoid()) {                             
        pv=loc->getRef(p->id());                             
        if(!pv || !pv->isQuExpr())                           
          throw tError(errINT,"parameter "+p->id()+" not found",this);
        qv=l.getRef(p->id());                                
        if(!qv || !qv->isQuExpr())                           
          throw tError(errINT,"temporary register not found",this);
        lqh.call(FANOUTID,gl,!inv,0,*qv,*pv);
      }                                                      
    }                                                        
    lqh.apply(gl,1);
  } else {                                                   
    lqh.apply(gl,inv);
  }                                                          
  
  if(optCheck) {
    term t;
    for_plist(p,args(),c) {
      if(inv && p->type().isQuVoid() || p->type().isQuScr()) {
        pv=loc->getRef(p->id());
	if(!pv || !pv->isQuExpr())
          throw tError(errINT,"temporary register not found",this);
	i=pv->qustate()->mapbits();
	if(pv->qustate()->prob(bitvec(i))<(1.0-EPSILON_CHECK))
	  throw tError(errMEM,"void or scratch register not empty",this);
      }
    }
    for(i=0;i<qh->state()->baseterms();i++) {
      t=qh->state()->baseterm(i);
      if(!zero(t.vect()&qh->mFree()) && norm(t.ampl())>EPSILON_CHECK)
        throw tError(errMEM,"quantum heap is corrupted",this);
    }
  }
}

void sFunctDef::invoke(SymTable *loc,SymTable *gl,QuHeap *qh,int inv) {
  SymTab l;
  SymTabComb lcomb((SymTable*)&l,loc);
  pdefs->define(&lcomb,gl,qh);
  body()->exec(&lcomb,gl,qh);
}


#define ENTRY(s,n) case n: return s;

string sObject::objstr() const {
  switch(object()) {
    ENTRY("sVOID",sVOID);

    ENTRY("sOBJECT",sOBJECT);
    ENTRY("sLIST",sLIST);

    ENTRY("sEXPR",sEXPR);
    ENTRY("sEXPRLIST",sEXPRLIST);
    ENTRY("sCONST",sCONST);
    ENTRY("sVAR",sVAR);
    ENTRY("sSUBSCRIPT",sSUBSCRIPT);
    ENTRY("sSUBRANGE",sSUBRANGE);
    ENTRY("sFUNCTCALL",sFUNCTCALL);
    ENTRY("sUNOP",sUNOP);
    ENTRY("sNEG",sNEG);
    ENTRY("sNOT",sNOT);
    ENTRY("sLENGTH",sLENGTH);
    ENTRY("sBINOP",sBINOP);
    ENTRY("sADD",sADD);
    ENTRY("sSUB",sSUB);
    ENTRY("sMULT",sMULT);
    ENTRY("sDIV",sDIV);
    ENTRY("sMOD",sMOD);
    ENTRY("sPOW",sPOW);
    ENTRY("sLESS",sLESS);
    ENTRY("sEQUAL",sEQUAL);
    ENTRY("sLEEQ",sLEEQ);
    ENTRY("sNOTEQ",sNOTEQ);
    ENTRY("sAND",sAND);
    ENTRY("sOR",sOR);
    ENTRY("sXOR",sXOR);
    ENTRY("sCONCAT",sCONCAT);
    ENTRY("sBASEFUNCT",sBASEFUNCT);
    ENTRY("sEXP",sEXP);
    ENTRY("sSIN",sSIN);
    ENTRY("sCOS",sCOS);
    ENTRY("sTAN",sTAN);
    ENTRY("sCOT",sCOT);
    ENTRY("sSINH",sSINH);
    ENTRY("sCOSH",sCOSH);
    ENTRY("sTANH",sTANH);
    ENTRY("sCOTH",sCOTH);
    ENTRY("sABS",sABS);
    ENTRY("sRE",sRE);
    ENTRY("sIM",sIM);
    ENTRY("sCONJ",sCONJ);
    ENTRY("sFLOOR",sFLOOR);
    ENTRY("sCEIL",sCEIL);
    ENTRY("sSQRT",sSQRT);
    ENTRY("sINOT",sINOT);
    ENTRY("sINT",sINT);
    ENTRY("sREAL",sREAL);
    ENTRY("sCOMPLEX",sCOMPLEX);
    ENTRY("sSTRING",sSTRING);
    
    ENTRY("sLISTFUNCT",sLISTFUNCT);
    ENTRY("sLOG",sLOG);
    ENTRY("sRANDOM",sRANDOM);
    ENTRY("sMIN",sMIN);
    ENTRY("sMAX",sMAX);
    ENTRY("sGCD",sGCD);
    ENTRY("sLCM",sLCM);
    ENTRY("sBIT",sBIT);
    ENTRY("sIAND",sIAND);
    ENTRY("sIOR",sIOR);
    ENTRY("sIXOR",sIXOR);
    ENTRY("sSCALAR",sSCALAR);
    ENTRY("sVECTOR",sVECTOR);
    ENTRY("sMATRIX",sMATRIX);
    ENTRY("sTENSOR3",sTENSOR3);
    ENTRY("sTENSOR4",sTENSOR4);
    ENTRY("sTENSOR5",sTENSOR5);
    ENTRY("sTENSOR6",sTENSOR6);
    ENTRY("sTENSOR7",sTENSOR7);
    ENTRY("sTENSOR8",sTENSOR8);
    ENTRY("sTENSOR9",sTENSOR9);

    ENTRY("sSTMT",sSTMT);
    ENTRY("sSTMTLIST",sSTMTLIST);
    ENTRY("sCALL",sCALL);
    ENTRY("sASSIGN",sASSIGN);
    ENTRY("sFOR",sFOR);
    ENTRY("sIF",sIF);
    ENTRY("sLOOP",sLOOP);
    ENTRY("sWHILE",sWHILE);
    ENTRY("sUNTIL",sUNTIL);
    ENTRY("sBREAK",sBREAK);
    ENTRY("sRETURN",sRETURN);
    ENTRY("sINPUT",sINPUT);
    ENTRY("sPRINT",sPRINT);
    ENTRY("sEXIT",sEXIT);
    ENTRY("sMEASURE",sMEASURE);
    ENTRY("sINCLUDE",sINCLUDE);
    ENTRY("sRESET",sRESET);
    ENTRY("sDUMP",sDUMP);
    ENTRY("sPLOT",sPLOT);
    ENTRY("sINSPECT",sINSPECT);
    ENTRY("sLOAD",sLOAD);
    ENTRY("sSAVE",sSAVE);
    ENTRY("sSET",sSET);
    ENTRY("sSHELL",sSHELL);

    ENTRY("sDEF",sDEF);
    ENTRY("sDEFLIST",sDEFLIST);
    ENTRY("sROUTDEF",sROUTDEF);
    ENTRY("sFUNCTDEF",sFUNCTDEF);
    ENTRY("sPROCDEF",sPROCDEF);
    ENTRY("sQUOPDEF",sQUOPDEF);
    ENTRY("sQUFUNDEF",sQUFUNDEF);
    ENTRY("sARGDEF",sARGDEF);
    ENTRY("sVARDEF",sVARDEF);
    ENTRY("sCONSTDEF",sCONSTDEF);

    ENTRY("sEOF",sEOF);
    ENTRY("sMSG",sMSG);
    default: ;
  }
  return "UNKNOWN_OBJECT"; 
}

#undef ENTRY
