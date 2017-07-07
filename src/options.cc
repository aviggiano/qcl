/**********************************************************************

This file is part of the Quantum Computation Language QCL.

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/


#include <stdio.h>
#include <time.h>

#include "options.h"
#include "error.h"

#define QCL_SHORTOPTS "hVix:qno:b:s:I:U:d:p:f:P:Z:T:Q:g:a:l:L:c:S:E:t:e:r:"

#define OPT_TEXMACS 	256
#define OPT_COLOR 	257
#define OPT_TRACE 	258
#define OPT_PLOTPAPER	259
#define OPT_PLOTSIZE	260
#define OPT_IRQ		261
#define OPT_LIB		262
#define OPT_LIGHTCOLOR 	263

struct option qcl_options[]={
  {"help",0,0,'h'},
  {"version",0,0,'V'},
  {"interactive",0,0,'i'},
  {"exec",0,0,'x'},
  {"quiet",0,0,'q'},
  {"color",0,0,OPT_COLOR},
  {"light-colors",0,0,OPT_LIGHTCOLOR},
  {"texmacs",0,0,OPT_TEXMACS},
  {"no-default-include",0,0,'n'},
  {"logfile",1,0,'o'},
  {"bits",1,0,'b'},
  {"seed",1,0,'s'},
  {"include-prefix",1,0,'I'},
  {"include-path",1,0,'I'},
  {"qcldir",1,0,'I'},
  {"qcluserdir",1,0,'U'},
  {"dump-file",1,0,'d'},
  {"plot-file",1,0,'p'},
  {"plot-paper",1,0,OPT_PLOTPAPER},
  {"plot-size",1,0,OPT_PLOTSIZE},
  {"dump-format",1,0,'f'},
  {"show-regs",1,0,'r'},
  {"precision",1,0,'P'},
  {"trunc-zeros",1,0,'Z'},
  {"trunc-states",1,0,'T'},
  {"qureg-mask",1,0,'Q'},
  {"debug",1,0,'g'},
  {"auto-dump",1,0,'a'},
  {"log",1,0,'l'},
  {"log-state",1,0,'L'},
  {"check",1,0,'c'},
  {"trace",1,0,OPT_TRACE},
  {"syntax",1,0,'S'},
  {"echo",1,0,'E'},
  {"test",1,0,'t'},
  {"shell-escape",1,0,'e'},
  {"library",1,0,OPT_LIB},
  {"allow-redefines",1,0,OPT_LIB},
  {"irq",1,0,OPT_IRQ},
//  {"",0,0,''},
  {0,0,0,0}
};

const OutputFormat *format=&FormatPlain;

void printusage(char *name) {
  cerr << "USAGE: " << name << " [options] [file] ...\n";
  cerr << "QCL interpeter and quantum computer simulator\n\n";
  cerr << "Startup Options:\n";
  cerr << "-h, --help                      display this message\n";
  cerr << "-V, --version                   display version information\n";
  cerr << "-i, --interactive               force interactive mode\n";
  cerr << "-x, --exec<commands>            execute <commands> on startup\n";
  cerr << "-q, --quiet                     skip startup message\n";
  cerr << "--color                         color xterm interface\n";
  cerr << "--light-color                   color xterm interface for black background\n";
  cerr << "--texmacs                       TeXmacs interface (experimental)\n";
  cerr << "-n, --no-default-include        don't read " << DEF_STD_INCLUDE << " on startup\n";
  cerr << "-o, --logfile                   specify a logfile\n";
  cerr << "-b, --bits=n:                   set number of qubits (" << 8*sizeof(int) <<")\n";
  cerr << "Dynamic Options (can be changed with the set statement):\n";
  cerr << "-s, --seed=<seed-value>         set random seed value (system time)\n";
  cerr << "-I, --qcldir=<path>             QCL system include path (" DEF_INCLUDE_PATH ")\n";
  cerr << "-U, --qcluserdir=<path>         QCL user include path ($HOME/.qcl)\n";
  cerr << "--library=<y|n>                 ignore redefinitions of existing symbols (n)\n";
  cerr << "-d, --dump-file=<file>          send output of dump-command to <file> (none)\n";
  cerr << "-p, --plot-file=<file>          Postscript file created by plot-command (none)\n";
  cerr << "-f, --dump-format=x,d,b,X,D,B   list base vectors as hex, decimal or binary (d)\n";
  cerr << "                                lower case for cartesian, upper for polar values\n";
  cerr << "-r, --show-regs=<y|n>           show global registers in dumped states (y)\n";
  cerr << "-D, --dump-precision=<digits>   shown digits in dumped states (5)\n";
  cerr << "-P, --precision=<digits>        shown digits for real and complex values (6)\n";
  cerr << "-Z, --trunc-zeros=<y|n>         truncate zeros for real and complex values (y)\n";
  cerr << "-T, --truc-states=<y|n>         truncate non-allocated qubits (y)\n";
  cerr << "--plot-paper=<format>           Set paper-format for Postscript output (b5)\n";
  cerr << "--plot-size=<pixel>             Set maximum window size for X11 plots (600)\n";
  cerr << "-Q, --qureg-mask=<y|n>          list registers as masks instead of lists (n)\n";
  cerr << "-g, --debug=<y|n>               open debug-shell on error (n)\n";
  cerr << "-a, --auto-dump=<max>           dump states up to max terms in shell mode (8)\n"; 
  cerr << "-l, --log==<y|n>                log external operator calls (n)\n";
  cerr << "-L, --log-state==<y|n>          log state after each transformation (n)\n";
  cerr << "-c, --check==<y|n>              check consistency of quantum heap (n)\n";
  cerr << "--trace==<y|n>                  trace mode (very verbose) (n)\n";
  cerr << "-S, --syntax=<y|n>              check only the syntax, no interpretation (n)\n";
  cerr << "-E, --echo=<y|n>                echo parsed input (n)\n";
  cerr << "-t, --test=<y|n>                test programm, ignore quantum operations (n)\n";
  cerr << "-e, --shell-escape=<y|n>        honor shell-escapes (y)\n";
  cerr << "--irq=<y|n>                     allow user interrupts if supported (y)\n";
}

int optInteractive=0;
string optExec;
const OutputFormat *optInterface=&FormatPlain;
int optQuiet=0;
int optTeXmacs=0;
int optColor=0;
int optNoDefaultInclude=0;
string optIncludePath=DEF_INCLUDE_PATH;
string optUserPath="";
ofstream *optLogfile=0;
int optBits=BPW;
int optSeed=time(0);
char optDumpFormat='d';
int optDumpPolar=0;
int optShowRegs=1;
int optQuregMask=0;
int optDebug=0;
int optAutoDump=AUTODUMP_STATES;
int optDumpPrecision=5;
tReal optDumpEpsilon=0.00001;
int optTrucStates=1;
int optPrintPrecision=6;
int optTruncZeros=1;
string optPlotPaper="b5";
int optPlotSize=600;
string optDumpFilename="";
string optPlotFilename="";
int optLog=0;
int optLogState=0;
int optCheck=0;
int optTrace=0;
int optSyntax=0;
int optEcho=0;
int optTest=0;
int optShellEscape=1;
int optAllowRedefines=0;
int optIRQ=1;

#define OPTERR(s) throw tError(errOPT,s)

#define LOGVAL(v) { \
  if(!strchr("1yYtT0nNfF",arg[0])) 	\
    OPTERR("Invalid boolean value");	\
  v=(strchr("1yYtT",arg[0])!=0);	\
}

#define INTVAL(v) { \
  char *p;						\
  v=strtol(arg,&p, 10);					\
  if(*p || v<0) OPTERR("Invalid integer value");	\
}

void evalopt(int c,const char *arg) {
  switch(c) {
    case 's': INTVAL(optSeed);
  	      qc_srand(optSeed);
  	      break;
    case 'I': optIncludePath=arg;     		break;
    case 'U': optUserPath=arg;     		break;
    case 'd': optDumpFilename=arg;   		break;
    case 'p': optPlotFilename=arg;   		break;
    case 'f': if(!arg[0] || !strchr("hxdbaHXDBA",arg[0])) OPTERR("Invalid dump format");
  	      optDumpFormat=tolower(arg[0]);
              optDumpPolar=isupper(arg[0]);
  	      if(optDumpFormat=='h') optDumpFormat='x';
  	      break;
    case 'r': LOGVAL(optShowRegs);	   	break;
    case 'D': INTVAL(optDumpPrecision);		
              optDumpEpsilon=pow(0.1,optDumpPrecision);
    	      break;
    case 'P': INTVAL(optPrintPrecision);	break;
    case 'Z': LOGVAL(optTruncZeros);   		break;
    case 'T': LOGVAL(optTrucStates);   		break;
    case OPT_PLOTPAPER:	optPlotPaper=arg;	break;
    case OPT_PLOTSIZE:	INTVAL(optPlotSize);	break;
    case 'Q': LOGVAL(optQuregMask);    		break;
    case 'g': LOGVAL(optDebug);	      		break;
    case 'a': INTVAL(optAutoDump);		break;
    case 'l': LOGVAL(optLog);			break;
    case 'L': LOGVAL(optLogState);		break;
    case 'c': LOGVAL(optCheck);			break;
    case OPT_TRACE: 	LOGVAL(optTrace);	break;
    case 'S': LOGVAL(optSyntax);		break;
    case 'E': LOGVAL(optEcho);			break;
    case 't': LOGVAL(optTest);	      		break;
    case 'e': LOGVAL(optShellEscape);		break;
    case OPT_LIB: LOGVAL(optAllowRedefines);   	break;
    case OPT_IRQ: 	
    	      LOGVAL(optIRQ);   	
              if(optIRQ) irqOn(); else irqOff();
              break;
    case ':': OPTERR("Missing parameter");
    case '?':
    default:  OPTERR("Illegal option");
  };
}

void parseopt(int argc,char **argv) {
  int c=0;
  int ind;
  if(optIRQ) irqOn(); else irqOff();
  char *inc=getenv(ENV_INCLUDE_PATH);
  if(inc) optIncludePath=inc;
  inc=getenv("ENV_USER_PATH");
  if(inc) {
    optUserPath=inc;
  } else {
    inc=getenv("HOME");
    if(inc) optUserPath=string(inc)+"/.qcl";
  }
  try {
    while(1) {
      c=getopt_long(argc,argv,QCL_SHORTOPTS,qcl_options,&ind);
      if(c==-1) break;
      switch(c) {
        case 'h': printusage(argv[0]);
                  exit(0);
        case 'V': cerr << VERSION << ", " << COPYRIGHT << "\n" << DISCLAIMER << "\n";
                  exit(0);
        case 'i': optInteractive=1;       break;
        case 'q': optQuiet=1;       break;
        case 'x': optExec+=optarg;
        	  optExec+=";";
        	  break;
        case OPT_COLOR: 
        	  optInterface=&FormatXTerm;
                  optColor=1;
                  break;
        case OPT_LIGHTCOLOR: 
        	  optInterface=&FormatDarkXTerm;
                  optColor=1;
                  break;
        case OPT_TEXMACS: 
        	  optInterface=&FormatTeXmacs;
                  optTeXmacs=1;
                  break;
        case 'n': optNoDefaultInclude=1;  break;
        case 'o': optLogfile=new ofstream(optarg);
                  if(!optLogfile || !*optLogfile) {
                    optLogfile=0;
                    OPTERR(string("can't create logfile ")+optarg);
                  };
                  break;
        case 'b': {
                    char *p;
                    optBits=strtol(optarg,&p, 10);        
                    if(*p || optBits<2) OPTERR("Illegal number of qubits");
                    break;
                  }
        default:  evalopt(c,optarg);
      }
    }
  } catch(tError e) {
    cout << format->output_beg;
    qclabort(e);
  }
  if(argc==optind && optExec=="") optInteractive=1;
  if(optSyntax) optTest=1;
  qc_srand(optSeed);
  if(optIRQ) irqOn(); else irqOff();
  format=optInterface;
}

volatile int irqFlag=IRQ_NONE;

#ifdef QCL_IRQ

#include<signal.h>

static void irqHandler(int sig) {
  if(sig==SIGINT) irqFlag=IRQ_EXIT;
  if(sig==SIGTSTP) irqFlag=IRQ_SHELL;
  signal(SIGINT,SIG_DFL);
  signal(SIGTSTP,SIG_DFL);
}

void irqOn() {
  if(optIRQ) {
    signal(SIGINT,&irqHandler);
    signal(SIGTSTP,&irqHandler);
  }
}

void irqOff() { 
  irqFlag=IRQ_NONE;
  signal(SIGINT,SIG_DFL);
  signal(SIGTSTP,SIG_DFL);
}

#else

void irqOn() { } 
void irqOff() { }

#endif

#undef OPTERR
