/**********************************************************************

This file is part of the Quantum Computation Language QCL.

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/


#ifndef OPTIONS_H
#define OPTIONS_H 1

#include <unistd.h>
#include <getopt.h>
#include <fstream>
#include <stack>
#include <string.h>

#include "types.h"
#include "format.h"

#define VERSION    "QCL version 0.6.4"
#define COPYRIGHT  "(c) by Bernhard Oemer, 1998-2014"
#define DISCLAIMER "This program is free software under the terms of the GPL"

#define QUOTE(x) #x

#ifndef DEF_INCLUDE_PATH
#define DEF_INCLUDE_PATH "/usr/local/lib/qcl"
#endif

#define ENV_INCLUDE_PATH "QCLDIR"
#define ENV_USER_PATH "QCLUSERDIR"

#ifndef DEF_STD_INCLUDE
#define DEF_STD_INCLUDE "default.qcl"
#endif

#ifndef DEF_LOAD_FILE
#define DEF_LOAD_FILE "qclstate"
#endif

#ifndef DEF_SAVE_FILE
#define DEF_SAVE_FILE DEF_LOAD_FILE
#endif

#ifndef DEF_DATAFILE_EXT
#define DEF_DATAFILE_EXT ".qst"
#endif

#ifndef EPSILON_MATRIX
#define EPSILON_MATRIX 0.000001
#endif

#ifndef EPSILON_CHECK
#define EPSILON_CHECK 0.000001
#endif

#ifndef AUTODUMP_STATES
#define AUTODUMP_STATES 8
#endif


extern const OutputFormat *format;
extern ofstream *file;

extern char *optarg;
extern int optind;

void printusage(char *name);
void evalopt(int c,const char *optarg);
void parseopt(int argc,char **argv);

extern struct option qcl_options[];

extern int optInteractive;
extern int optQuiet;
extern string optExec;
extern const OutputFormat *optInterface;
extern int optTeXmacs;
extern int optColor;
extern int optNoDefaultInclude;
extern ofstream *optLogfile;
extern int optBits;
extern string optIncludePath;
extern string optUserPath;
extern int optSeed;
extern char optDumpFormat;
extern int optDumpPolar;
extern int optShowRegs;
extern int optQuregMask;
extern int optDebug;
extern int optAutoDump;
extern int optDumpPrecision;
extern tReal optDumpEpsilon;
extern int optTrucStates;
extern int optPrintPrecision;
extern int optTruncZeros;
extern string optPlotPaper;
extern int optPlotSize;
extern string optDumpFilename;
extern string optPlotFilename;
extern int optLog;
extern int optLogState;
extern int optCheck;
extern int optTrace;
extern int optSyntax;
extern int optEcho;
extern int optTest;
extern int optShellEscape;
extern int optAllowRedefines;
extern int optIRQ;

#define IRQ_NONE  0
#define IRQ_SHELL 1
#define IRQ_EXIT  2

void irqOn();
void irqOff();
extern volatile int irqFlag;

#endif
