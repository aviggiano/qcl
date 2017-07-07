# Makefile for libqc
#
# This file is part of the Quantum Computation Library (QCLIB).
# 
# (c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1998-2014
# 
# This program comes without any warranty; without even the implied 
# warranty of merchantability or fitness for any particular purpose.
# 
#      This program is free software under the terms of the 
#      GNU General Public Licence (GPL) version 2 or higher

# Comment out if you want to compile for a different target architecture

#ARCHOPT = -m32 -march=i686

# Debugging options

DEBUG = -g -O2 -DQC_DEBUG
#DEBUG = -g -pg -DQC_DEBUG
#DEBUG = -O2

# Comment out if you if you want to use SysV Xrand48() linear congruential 
# PRG instead of the default random() non-linear additive  feedback PRG.

#PRGOPT = -DQC_USE_RAND48

CXXFLAGS = $(ARCHOPT) -c -pedantic -Wall $(DEBUG) $(PRGOPT)

LDFLAGS = $(ARCHOPT) -L. -lm -lqc

FILESCC = bitvec.cc terms.cc qustates.cc operator.cc
FILESH = bitvec.h terms.h qustates.h operator.h qc.h
SOURCE = $(FILESCC) $(FILESH) shor.cc Makefile

all: libqc.a

libqc.a: bitvec.o terms.o qustates.o operator.o
	ar rc libqc.a bitvec.o terms.o qustates.o operator.o && ranlib libqc.a

bitvec.o: bitvec.cc bitvec.h
	$(CXX) bitvec.cc -o bitvec.o $(CXXFLAGS)

terms.o: terms.cc terms.h bitvec.h
	$(CXX) terms.cc -o terms.o $(CXXFLAGS)

qustates.o: qustates.cc qustates.h terms.h bitvec.h
	$(CXX) qustates.cc -o qustates.o $(CXXFLAGS)

operator.o: operator.cc operator.h qustates.h terms.h bitvec.h
	$(CXX) operator.cc -o operator.o $(CXXFLAGS)

shor.o: shor.cc qustates.h terms.h bitvec.h 
	$(CXX) shor.cc -o shor.o $(CXXFLAGS)

shor: shor.o libqc.a 
	$(CXX)  shor.o -o shor $(LNKOPT)

# Other Functions

edit:
	nedit $(SOURCE) &

clean:
	rm -f *.o 

clear: clean
	rm -f libqc.a shor
