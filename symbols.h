/**********************************************************************

This file is part of the Quantum Computation Language QCL.

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/


#ifndef SYMBOLS_H
#define SYMBOLS_H 1

#pragma interface

#include "types.h"


class SymTable {
public:
  struct entry {
    sDef *pdef;
    tValue *pval;
    entry *pred;
    entry *succ;
  };
  SymTable() { }
  virtual ~SymTable() { }
  virtual int put(sDef *d,const tValue& v=tValue()) = 0;
  virtual tValue getVal(const tId& id,ObjType *o=0) const = 0;
  virtual sDef *getDef(const tId& id) const = 0;
  virtual tValue *getRef(const tId& id,ObjType *o=0) const = 0;
  virtual string prtstr(int ind=NOINDENT) = 0;
  void print(ostream& o) { o << prtstr(); }
};

class SymTab : public SymTable {
  entry *root;
  void deltree(entry *t);
  int putentry(entry *t,entry *e);
  entry *getentry(entry *t,const tId& id) const;
  string recstr(entry *e,int ind=NOINDENT);
  int global;
public:
  SymTab(int g=0) : SymTable() { root=0; global=g; }
  virtual ~SymTab() { if(root) deltree(root); }
  virtual int put(sDef *d,const tValue& v=tValue());
  virtual tValue getVal(const tId& id,ObjType *o=0) const;
  virtual sDef *getDef(const tId& id) const;
  virtual tValue *getRef(const tId& id,ObjType *o=0) const;
  virtual string prtstr(int ind=NOINDENT);
};

class SymTabComb : public SymTable {
  SymTable *tab1;
  SymTable *tab2;
public:
  SymTabComb(SymTable *t1,SymTable *t2) : SymTable() {
    tab1=t1; tab2=t2; }
  virtual ~SymTabComb() { };
  virtual int put(sDef *d,const tValue& v=tValue());
  virtual tValue getVal(const tId& id,ObjType *o=0) const;
  virtual sDef *getDef(const tId& id) const;
  virtual tValue *getRef(const tId& id,ObjType *o=0) const;
  virtual string prtstr(int ind=NOINDENT);
};

#endif
