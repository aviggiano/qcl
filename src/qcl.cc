/**********************************************************************

This file is part of the Quantum Computation Language QCL.

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/


#include "syntax.h"
#include "symbols.h"
#include "error.h"
#include "quheap.h"
#include "parse.h"
#include "options.h"
#include "debug.h"

#include <stdio.h>
#include <unistd.h>
#include <getopt.h>

extern char *optarg;
extern int optind;
extern struct msgstruct *message;

int main(int argc,char **argv) {
  string s;
  int i;

  initialize_readline();
  parseopt(argc,argv);
  QuHeap qh(optBits);
  SymTab gl(1);
  SymTab loc;

  cout << format->output_beg;
  if(!optQuiet) {
    cout << "QCL Quantum Computation Language ("
         << optBits << " qubits, seed " << optSeed << ")\n";
  }
  if(!optNoDefaultInclude) qclfile(DEF_STD_INCLUDE,&loc,&gl,&qh);
  for(i=optind;i<argc;i++) qclfile(argv[i],&loc,&gl,&qh,0,QL_ERRORABORT);
  if(optExec!="") qclstring(optExec,&loc,&gl,&qh);
  if(optInteractive) qclshell(&loc,&gl,&qh);
  if(optLogfile) qcl_delete(optLogfile);
  cout << format->output_end;
  return 0;
}

