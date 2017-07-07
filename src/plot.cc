/**********************************************************************

This file is part of the Quantum Computation Language QCL.

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/


#pragma implementation

#include "plot.h"
#include "error.h"
#include "quheap.h"
#include "options.h"

#ifdef QCL_PLOT

#include <plotter.h>

#define MARK_REAL 16	// filled circle
#define MARK_IMAG 5	// cross

ostream *plotfile;
Plotter *plotter;

inline long pow(int a,int b) { return (long)pow((double)a,b); }

double vec2double(bitvec v) {
  if(v.length()<=BPW)
    return v.getword();
  else
    return v.getword(v.length()-BPW,BPW)*pow(2,v.length()-BPW);
}  

void open_plot() {
  plotfile=0;
  Plotter::parampl("PAGESIZE",(void*)optPlotPaper.c_str());
  Plotter::parampl("BITMAPSIZE",(void*)"600x600");
  if(optPlotFilename!="") {
    plotfile=new ofstream(optPlotFilename.c_str(),ios::out);
    if(!plotfile || !*plotfile) {
      if(plotfile) delete plotfile;
      throw tError(errIO,"cannot open plot-file "+optDumpFilename);
    }
    plotter=new PSPlotter(cin,*plotfile,cerr);
  } else if(optTeXmacs) {
    plotter=new PSPlotter(cin,cout,cerr);
    cout << format->ps_beg;
  } else {
    plotter=new XPlotter(cin,cout,cerr);
  }
  if(!plotter || plotter->openpl()<0) {
    if(plotter) delete plotter;
    if(plotfile) delete plotfile;
    throw tError(errINT,"cannot open plotter object");
  }
  if(optPlotFilename=="" && optTeXmacs) 
    plotter->fspace(-0.28,-0.58,1.28,1.58);
  else
    plotter->fspace(-0.08,-0.08,1.08,1.08);
  plotter->ffontsize(0.04);
}

void close_plot() {
  int r=-1;
  if(plotter) {
    r=plotter->closepl();
    delete plotter;
  }
  if(plotfile) delete plotfile;
  if(optTeXmacs && optPlotFilename=="") cout << format->ps_end;
  if(r<0) throw tError(errINT,"cannot close plotter object");
}

void plot_state(QuHeap *qh) {
  qclprint("PLOT STATE");
  open_plot();
  char buf[80];
  int used=qh->nBits()-qh->nFree();
  tComplex z;
  bitvec v;
  state_iter i;
  double x;
  double maxx = pow(2,MAX(used,1))-1;
  double maxy = 1/sqrt(maxx+1);
  double msize = 0.75/(maxx+1);

  if(msize<0.012) msize=0.012;
  if(msize>0.05) msize=0.05;

  state_map *pm=qh->state()->new_state_map();
  for(i=pm->begin();i!=pm->end();i++) {
    x=vec2double((*i).first);
    if(x>maxx) maxx=x;
    z=(*i).second;
    if(abs(z.real())>maxy) maxy=abs(z.real());
    if(abs(z.imag())>maxy) maxy=abs(z.imag());
  }

  if(maxx>pow(2,used))
    sprintf(buf,"basevectors |0> ... |%.0f>",maxx);
  else
    sprintf(buf,"%d used qubit%s, %d basevector%s",
      used,used==1?"":"s",(int)pow(2,used),used==0?"":"s");
  plotter->fmove(0.5,-0.04);
  plotter->alabel('c','c',buf);

  plotter->color(0x4000,0x4000,0x4000);
  plotter->flinewidth(0.003);

  plotter->fmove(0,0.5);
  plotter->fcont(1,0.5);
  
  plotter->color(0,0,0);
  plotter->flinewidth(0.001);

  for(i=pm->begin();i!=pm->end();i++) {
    x=vec2double((*i).first)/maxx;
    z=(*i).second;
    plotter->fmove(x,0.5+abs(z)/(2*maxy));
    plotter->fcont(x,0.5-abs(z)/(2*maxy));
    plotter->fmarker(x,0.5+z.real()/(2*maxy),MARK_REAL,msize);
    plotter->fmarker(x,0.5+z.imag()/(2*maxy),MARK_IMAG,1.2*msize);
  }
  delete pm;
  close_plot();
}

void plot_spectrum(quState *q,string lab) {
  qclprint("PLOT SPECTRUM "+lab);
  open_plot();
  bitvec v;
  spectrum_iter i;
  double x,y;
  double maxx = pow(2,q->mapbits())-1;
  double maxy = 1/(maxx+1);
  spectrum_map *pm=q->new_spectrum_map();
  for(i=pm->begin();i!=pm->end();i++) {
    y=(*i).second;
    if(y>maxy) maxy=y;
  }

  plotter->fmove(0.5,-0.04);
  plotter->alabel('c','c',lab.c_str());

  plotter->color(0x4000,0x4000,0x4000);
  plotter->flinewidth(0.003);

  plotter->fmove(0,0);
  plotter->fcont(1,0);
  
  plotter->color(0,0,0);
  plotter->flinewidth(0.001);

  for(i=pm->begin();i!=pm->end();i++) {
    x=vec2double((*i).first)/maxx;
    y=(*i).second;
    plotter->fmove(x,0.0);
    plotter->fcont(x,y/maxy);
    plotter->fmarker(x,y/maxy,MARK_REAL,0.012);
  }
  delete pm;
  close_plot();
}

void plot_spectrum2(quState *qx,quState *qy,string labx,string laby) {
  qclprint("PLOT XY-SPECTRUM "+labx+" / "+laby);
  open_plot();
  
  bitvec v,vx,vy;
  spectrum_iter i;
  double x,y,z;
  int nx=qx->mapbits();
  int ny=qy->mapbits();
  double maxx = pow(2,nx);
  double maxy = pow(2,ny);
  double maxz = 1/(maxx*maxy);
  double dx=1/maxx;
  double dy=1/maxy;
  quCombState q(qx,qy);

  spectrum_map *pm=q.new_spectrum_map();
  for(i=pm->begin();i!=pm->end();i++) {
    z=(*i).second;
    if(z>maxz) maxz=z;
  }
  maxz*=1.2;
  
  plotter->fmove(0.5,-0.04);
  plotter->alabel('c','c',labx.c_str());
  plotter->textangle(90);
  plotter->fmove(-0.04,0.5);
  plotter->alabel('c','c',laby.c_str());
  plotter->textangle(0);

  plotter->color(0x4000,0x4000,0x4000);
  plotter->flinewidth(0.003);

  plotter->fmove(-0.01,1);
  plotter->fcont(-0.01,-0.01);
  plotter->fcont(1,-0.01);
  
  plotter->color(0,0,0);
  plotter->flinewidth(0.001);
  plotter->filltype(0x8000);

  for(i=pm->begin();i!=pm->end();i++) {
    v=(*i).first;
    x=vec2double(v.getbits(0,nx))/maxx+dx/2;
    y=vec2double(v.getbits(nx,ny))/maxy+dy/2;
    z=sqrt((*i).second/maxz)/2;
    plotter->fellipse(x,y,z*dx,z*dy,0);
//  plotter->fbox(x-z*dx,y-z*dy,x+z*dx,y+z*dy);
  }
  delete pm;
  close_plot();
}

#else

void plot_state(QuHeap *qh) {
  qclmessage("this QCL binary doesn't contain plotting support.");
}

void plot_spectrum(quState *q,string lab) {
  qclmessage("this QCL binary doesn't contain plotting support.");
}

void plot_spectrum2(quState *qx,quState *qy,string labx,string laby) {
  qclmessage("this QCL binary doesn't contain plotting support.");
}

#endif
