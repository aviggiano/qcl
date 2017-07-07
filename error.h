/**********************************************************************

This file is part of the Quantum Computation Language QCL.

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/


#ifndef ERROR_H
#define ERROR_H 1

#pragma interface

#include "types.h"

class tError;

int yyerror(const char*);

enum ErrType { errNONE, errEXIT, errMSG, errINT, errLEXICAL, errPARSE, 
               errTYPMIS, errINVTYP, errPARMIS, errINVPAR, errSYMBOL, 
	       errSCOPE, errDEF, errMATH,errRUN, errGEN, errSYNTAX,
	       errUSR, errRANGE, errEXT, errIO, errSHELL, errMEM,
	       errOPT, errIGNORE, errIRQ };



void initialize_readline();

void qclerror(string e);
void qclerror(const tError& e);

void qclabort(string e="");
void qclabort(const tError& e);


string qclinput(string p="?");

void qcloutput(string s);
void qclprint(string s);
void qcllog(string s);
void qclmessage(string s);

void qcltrace(string s,sObject *obj,SymTable *loc,SymTable *gl,QuHeap *qh=0);

extern int isErrorReported;


class tError {
  ErrType err;
  string msg;
  string loc;
  sObject *obj;
public:
  tError(ErrType t,string s="",sObject *o=0);
  void setobj(sObject *o);
  void setmsg(string s) { msg=s; }
  int hasobj() const { return loc!=""; }
  int hasmsg() const { return msg!=""; }
  string message() const { return msg; }
  string where() const { return loc; }
  ErrType type() const { return err; }
  sObject *object() const { return obj; }
};

#endif
