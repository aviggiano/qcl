/**********************************************************************

This file is part of the Quantum Computation Language QCL.

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/


#ifndef PLOT_H
#define PLOT_H 1

#pragma interface

#include "types.h"

void plot_state(QuHeap *qh);
void plot_spectrum(quState *q,string lab="");
void plot_spectrum2(quState *qx,quState *qy,string labx="",string laby="");

#endif
