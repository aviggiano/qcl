/**********************************************************************

This file is part of the Quantum Computation Language QCL.

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/


#ifndef EXTERN_H
#define EXTERN_H 1

#pragma interface

#include "types.h"

/*
class QuBaseState : public quBaseState {
public:
  QuBaseState(int n) : quBaseState(n) { }
};
*/

struct RoutTableEntry {
  tExtRout *rout;
  const char *id;
};

extern RoutTableEntry ExtRoutTable[];

#endif
