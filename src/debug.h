/**********************************************************************

This file is part of the Quantum Computation Language QCL.

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/


#ifndef DEBUG_H
#define DEBUG_H

#include <list>

#include "symbols.h"
#include "quheap.h"
#include "syntax.h"

#define DB_NORMAL	1
#define DB_ESCAPE	2
#define DB_ERROR	3
#define DB_IRQ		4

#define QL_ERRORREPORT	0	// report errors and continue
#define QL_ERRORABORT	1	// abort on errors
#define QL_ERRORRETURN	2	// return on errors
#define QL_IGNOREEXIT	4	// ignore exit
#define QL_NOERRMSG	8	// don't print errormessages

/*
class objlist : public list<sObject*> {
public:
  objlist();
  ~objlist();
};
*/

extern int shell_depth;

int qcllist(SymTable *loc,SymTable *gl,QuHeap *qh,sObject *obj=0,int flags=QL_ERRORREPORT);
int qclfile(string fname,SymTable *loc,SymTable *gl,QuHeap *qh,sObject *obj=0,int flags=QL_ERRORRETURN);
int qclshell(SymTable *loc,SymTable *gl,QuHeap *qh,sObject *obj=0,int cond=DB_NORMAL);
int qclstring(string s,SymTable *loc,SymTable *gl,QuHeap *qh);

#endif
