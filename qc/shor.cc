/**********************************************************************

This file is part of the Quantum Computation Library (QCLIB).

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1996-1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/

#include <math.h>
#include <time.h>
#include <unistd.h>

#include "operator.h"

extern char *optarg;
extern int optind;

// global variables

int seed=time(0);	// random seed value
int quiet=0;		// quiet mode
int verbose=0;		// verbose mode
int show=0;		// show state spectrums
int dump=0;		// dump quantum state
int maxtries=3;		// max. number of selections
int maxgates=-1;	// max. number of cond. phase gates per bit in FFT
int iter=0;		// total number of tries


// returns 0 and sets *a and *b if n = (*a) * (*b)
// returns 1 if n is a prime number 

int factorize(word n,word *a,word *b) {
  word i,m;

  m=(word)ceil(sqrt((double)n));
  for(i=2;i<=m;i++) {
    if(n%i==0) {
      *a=i;
      *b=n/i;
      return 0;
    };
  };
  return 1;
}

// returns 1 if p is a power of b and 0 otherwise

int testpower(word p,word b) {
  if(p<b) return testpower(b,p);
  if(p==b) return 1;
  if(p%b) return 0;
  return testpower(p/b,b);
}

// returns x^a mod n

word powmod(word x,word a,word n) {
  word u,y;
  int i;
  y=1; u=x;
  for(i=0;i<BPW-1;i++) {
    if(a & (1<<i)) { y*=u; y%=n; };
    u*=u; u%=n;
  };
  return y;
}

// returns the greatest common divisor of a and b

int gcd(int a,int b) {
  if(b>a) return gcd(b,a);
  return a%b ? gcd(a,a%b) : b;
}

// returns a random number 1 < r < (n-1) coprime to n

int randcoprime(int n) {
  int x;

  while(1) {
    x=qc_lrand()%(n-3)+2;
    if(gcd(x,n)==1) return x;
  }
}

// finds the best rational approximation (*p)/(*q) to x with 
// denominator < qmax and sets *p and *q accordingly. 

void approx(double x,word qmax,word *p,word *q) {
  word p0,p1,p2;
  word q0,q1,q2;
  word a;
  double y,z,e;

  e=1.0/(2.0*(double)qmax*(double)qmax);
  y=x; a=(int)floor(y);
  p0=1; p1=a;
  q0=0; q1=1;

  while(1) {
    z=y-floor(y);
    if(z<e) break;
    y=1/z;
    a=(int)floor(y);
    p2=a*p1+p0;
    q2=a*q1+q0;
    if(q2>qmax) break;
    p0=p1; p1=p2;
    q0=q1; q1=q2;
  };
  *p=p1; *q=q1;
}

// performs a fast fourier transformation on qs using
// Coppersmith's algorithm
 
opVar opFFT(int n) {
  int i,j,m;
  opVar op;

  for(i=0;i<n;i++) {
    if(maxgates>0) { m=i-maxgates; if(m<0) m=0; } else m=0;
    for(j=m;j<i;j++) op *= opX(n,n-i-1,n-j-1,i-j+1);
    op *= opEmbedded(n,n-i-1,new opU2(PI/2,PI/2,PI/2,PI));
  };
  for(i=0;i<(n/2);i++) op *= opSwap(n,1,i,n-i-1);
  return op;
}

// prints usage message

void usage() {
  cerr << "USAGE: shor [options] number\n";
  cerr << "Options: -s<seed> set random seed value\n";
  cerr << "         -t<maxtries> set max. no. of selections from same state.\n";
  cerr << "         -g<gates> set max. no. of cond. phase gates per bit in FFT.\n";
  cerr << "         -q operate quietly, -v verbose output\n";
}

// main program

int main(int argc,char **argv) {

  word number;		// number to be factored
  word factor;		// found factor
  int width;		// length of N in bits
  int starttime;	// starttime

  { // reading command line parameters
  
    int c;

    while(1) {
      c=getopt(argc,argv,"s:t:g:qvld"); 
      if(c<0) break;
      switch(c) {
        case 's': seed=atoi(optarg); break;
        case 't': maxtries=atoi(optarg); break;
        case 'g': maxgates=atoi(optarg); break;
        case 'q': quiet=1; verbose=0; break;
        case 'v': verbose=1; quiet=0; break;
        case 'l': show=1; break;
        case 'd': dump=1; break;
        default: usage(); exit(1);
      };
    };
    if(optind!=argc-1 || (number=atoi(argv[optind]))<1 ) { usage(); exit(1); };
    qc_srand(seed);
  };

  { // testing number

    word a,b;
  
    if(number%2==0) {
      cerr << "number must be odd !\n";
      exit(1);
    };
    if(factorize(number,&a,&b)) {
      cerr << number << " is a prime number !\n";
      exit(1);
    };
    if(testpower(b,a)) {
      cerr << number << " is a prime power of " << a << " !\n";
      exit(1);
    };
  };

  if(!quiet) {
    cout << "factoring " << number << ": random seed = " << seed;
    cout << ", tries = " << maxtries;
    if(maxgates>=0) cout << ", maxgates = " << maxgates;
    cout << ".\n";
  };
  
  cout.setf(ios::fixed,ios::floatfield);
  cout.precision(4);

  starttime=time(0);
  width=duallog(number);
  if(verbose) cout << "allocating " << (3*width) << " quBits with " <<
                      (1<<(2*width)) << " terms.\n";

  { // Shors's algorithm

    int nreg1=2*width,nreg2=width;
    quBaseState qubase(nreg1+nreg2,1<<nreg1);
    quWord reg1(nreg1,0,qubase);
    quWord reg2(nreg2,nreg1,qubase);
    opVar op;

    word x;		// base value
    word mreg1,mreg2;	// mesaurements of 1st and 2nd register
    word pow;		// pow^2==1 mod number
    word a,b;		// possible factors
    word p,q;		// fraction p/q for rational approximation
    double qmax;	// period and maximal period
    int tries;		// number of selections

    while(1) {
      if(!quiet) cout << "\nRESET:   reseting state to |0,0>\n";
      
      qubase.reset();			// reseting state
      
      if(!quiet) cout << "FFT:     performing 1st fourier transformation.\n";
      
      opFFT(nreg1)(reg1);		// 1st fourier transformaion
      
      x=randcoprime(number);		// selecting random x
      
      if(!quiet) cout << "EXPN:    trying x = " << x << ". |a,0> --> |a," << 
                         x << "^a mod " << number << ">\n";
      
      opEXPN(nreg1,nreg2,x,number)(qubase);	// modular exponentiation
      
      mreg2=reg2.measure().getword();	// measure 2nd register

      if(!quiet) cout << "MEASURE: 2nd register: |*," << mreg2 << ">\n";
      if(!quiet) cout << "FFT:     performing 2nd fourier transformation.\n";
      
      opFFT(nreg1)(reg1);		// 2nd fourier transformation

      qmax=1<<width;
      tries=0; 
      
    reselect:
    
      mreg1=reg1.select().getword();	// measure 1st register
      
      if(!quiet) cout << "MEASURE: 1st register: |" << 
                         mreg1 << "," << mreg2 << ">\n";
      tries++;
      iter++;
      if(mreg1==0) {
        if(!quiet) cout << "<failed> " << "measured zero in 1st register. ";
	if(tries<maxtries) {
	  if(!quiet) cout << "reselecting ...\n"; 
	  goto reselect; 
	} else {
	  if(!quiet) cout << "trying again ...\n"; 
	  continue; 
	};
      };

      // finding rational approximation for mreg1/rmax^2
      approx((double) mreg1/(qmax*qmax),(int) qmax,&p,&q);

      if(verbose) cout << "rational approximation for " <<
                          mreg1 << "/2^" << nreg1 << " is " << 
                          p << "/" << q << ", possible period: " << q << "\n";
      if(q&1) {
        if(!2*q<qmax) cout << "<failed> ";
        if(!quiet) cout << "odd period " << q << ". ";
        if(2*q<qmax) { 
          q*=2; 
          if(!quiet) cout << "trying period " << q << "\n";
        } else { 
	  if(tries<maxtries) {
	    if(!quiet) cout << "reselecting ...\n"; 
	    goto reselect;
	  } else {
	    if(!quiet) cout << "trying again ...\n"; 
	    continue; 
	  };
        };
      };

      pow=powmod(x,q/2,number);	// pow = x^(q/2) mod number
      a=(pow+1)%number;		// candidates with possible
      b=(pow+number-1)%number;	// common factors with number

      if(verbose) cout << x << "^" << q/2 << " mod " << number << " = " <<
                          pow << ". possible common factors of " <<
                          number << " with " << a << " and " << b << ".\n";
      
      // testing for common factors with number                    
      if(a>1 && (factor=gcd(number,a))>1) break; 
      if(b>1 && (factor=gcd(number,b))>1) break;
      
      if(!quiet) cout << "<failed> " << a << " and " << b << 
                         " have no common factors with " << number << ". ";

      if(tries<maxtries) {
        if(!quiet) cout << "reselecting ...\n"; 
        goto reselect;
      } else {
        if(!quiet) cout << "trying again ...\n"; 
        continue; 
      };
    };
    
    cout << number << " = " << factor << " * " << number/factor << ".\n";
    if(verbose) cout << "program succeded after " << time(0)-starttime <<
                        " s and " << iter << " iterations.\n";
  };    

  return 0;
}


