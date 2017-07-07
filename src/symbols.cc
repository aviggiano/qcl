/**********************************************************************

This file is part of the Quantum Computation Language QCL.

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/


#pragma implementation

#include "symbols.h"
#include "syntax.h"

#define IND() if(ind!=NOINDENT) \
  { int i; for(i=0;i<ind;i++) ostr+= "  "; }
#define NL() (ind==NOINDENT ? string(" ") : string("\n"))
#define INC() (ind!=NOINDENT ? ind+1 : ind)


void SymTab::deltree(entry *t) {
  if(t->pred) deltree(t->pred);
  if(t->succ) deltree(t->succ);
  if(t->pval) qcl_delete(t->pval);
  if(global && t->pdef) qcl_delete(t->pdef);
  qcl_delete(t);
}

int SymTab::putentry(entry *t,entry *e) {
  if(e->pdef->id()<t->pdef->id()) {
    if(t->pred) return putentry(t->pred,e); 
	t->pred=e;
	return 0;
  };
  if(e->pdef->id()>t->pdef->id()) {
  if(t->succ) return putentry(t->succ,e);
    t->succ=e;
    return 0;
  };
  return 1;
}

SymTab::entry * SymTab::getentry(entry *t,const tId& id) const {
  if(id==t->pdef->id()) return t;
  if(t->pred && id<t->pdef->id()) return getentry(t->pred,id);
  if(t->succ && id>t->pdef->id()) return getentry(t->succ,id);
  return 0;
}

int SymTab::put(sDef *d,const tValue& v) {
  entry *e;

  if(!d->isDef()) return 1;
  e=new entry;
  e->pdef=d;
  e->pval= d->isValueDef() ? new tValue(v) : 0;
  e->pred=e->succ=0;
  if(root) return putentry(root,e);
  root=e;
  return 0;
}

tValue SymTab::getVal(const tId& id,ObjType *o) const {
  entry *e;

  if(!root) return tValue();
  e=getentry(root,id);
  if(!e) return tValue();
  if(!e->pdef->isValueDef()) return tValue();
  if(o) *o=e->pdef->object();
  return *(e->pval);
}

sDef *SymTab::getDef(const tId& id) const {
  entry *e;

  if(!root) return 0;
  e=getentry(root,id);
  if(!e) return 0;
  return e->pdef;
}

tValue *SymTab::getRef(const tId& id,ObjType *o) const {
  entry *e;

  if(!root) return 0;
  e=getentry(root,id);
  if(!e) return 0;
  if(!e->pdef->isValueDef()) return 0;
  if(o) *o=e->pdef->object();
  return e->pval;
}

string SymTab::recstr(entry *e,int ind) {
  string ostr;
  if (!e) return "";
  if(e->pred) ostr+=recstr(e->pred,ind);
  IND();
  ostr+=e->pdef->declstr()+";";
  if(ind!=NOINDENT || e->succ) ostr+=NL();
  if(e->succ) ostr+=recstr(e->succ,ind);
  return ostr;
}

string SymTab::prtstr(int ind) {
  string ostr;
  
  if(ind==NOINDENT) {
    return "{"+recstr(root,ind)+"}";
  } else {
    return recstr(root,ind);
  }
}

int SymTabComb::put(sDef *d,const tValue& v) {
  return tab1->put(d,v);
}

tValue SymTabComb::getVal(const tId& id,ObjType *o) const {
  tValue v;

  v=tab1->getVal(id,o);
  if(v.isDefined()) return v;
  return tab2->getVal(id,o);
}

sDef *SymTabComb::getDef(const tId& id) const {
  sDef *d;

  d=tab1->getDef(id);
  if(d) return d;
  return tab2->getDef(id);
}

tValue *SymTabComb::getRef(const tId& id,ObjType *o) const {
  tValue *v;

  v=tab1->getRef(id,o);
  if(v) return v;
  return tab2->getRef(id,o);
}
 
string SymTabComb::prtstr(int ind) {
  string ostr;

  if(ind==NOINDENT) {
    ostr="{";
    if(tab1) ostr+=tab1->prtstr(ind);
    ostr+=",";
    if(tab2) ostr+=tab2->prtstr(ind);
    ostr+="}";
  } else {
    if(tab2) ostr+=tab2->prtstr(ind);
    if(tab1) ostr+=tab1->prtstr(ind);
  };
  return ostr;
}

SymTable *glsym; 	// global SymTable




