/**********************************************************************

This file is part of the Quantum Computation Language QCL.

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/


#ifndef DUMP_H
#define DUMP_H 1

#pragma interface

#include "types.h"

/*
bitvec trimvect(const bitvec& v);
string vect2bin(const bitvec& v);
string vect2dec(const bitvec& v);
string vect2hex(const bitvec& v);
*/

int report_state(QuHeap *qh);
int dump_state(QuHeap *qh,ostream *o=0);
int dump_spectrum(quState *qs,ostream *o=0);

#endif
