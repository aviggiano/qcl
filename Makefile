# Makefile for QCL
#
# This file is part of the Quantum Computation Language QCL.
# 
# (c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at> 1998-2006
# 
# This program comes without any warranty; without even the implied 
# warranty of merchantability or fitness for any particular purpose.
# 
#      This program is free software under the terms of the 
#      GNU General Public Licence (GPL) version 2 or higher

VERSION=0.6.4

# Directory for Standard .qcl files

QCLDIR = /usr/local/lib/qcl

# Path for qcl binaries

QCLBIN = /usr/local/bin

ARCH = `g++ -dumpmachine || echo bin`

# Comment out if you want to compile for a different target architecture
# To build libqc.a, you will also have to edit qc/Makefile!

#ARCH = i686-linux
#ARCHOPT = -m32 -march=i686

# Debugging and optimization options

#DEBUG = -g -pg -DQCL_DEBUG -DQC_DEBUG
#DEBUG = -g -DQCL_DEBUG -DQC_DEBUG
DEBUG = -O2 -g -DQCL_DEBUG -DQC_DEBUG
#DEBUG = -O2

# Plotting support 
#
# Comment out if you don't have GNU libplotter and X

PLOPT = -DQCL_PLOT
PLLIB = -L/usr/X11/lib -lplotter

# Readline support
#
# Comment out if you don't have GNU readline on your system
# explicit linking against libtermcap or libncurses may be required

RLOPT = -DQCL_USE_READLINE
#RLLIB = -lreadline
RLLIB = -lreadline -lncurses

# Interrupt support
#
# Comment out if your system doesn't support ANSI C signal handling

IRQOPT = -DQCL_IRQ

# Replace with lex and yacc on non-GNU systems (untested)

LEX = flex
YACC = bison 
INSTALL = install

# Character encoding
#
# one of ASCII, LAT1 or UTF8 (currently only affects the degree sign)

#ENCOPT = -DQCL_ASCII
#ENCOPT = -DQCL_LAT1
ENCOPT = -DQCL_UTF8

##### You shouldn't have to edit the stuff below #####

DATE = `date +"%y.%m.%d-%H%M"`

QCDIR = qc
QCLIB = $(QCDIR)/libqc.a
QCLINC = lib

#CXX = g++
#CPP = $(CC) -E
CXXFLAGS = -c $(ARCHOPT) $(DEBUG) $(PLOPT) $(RLOPT) $(IRQOPT) $(ENCOPT) -I$(QCDIR) -DDEF_INCLUDE_PATH="\"$(QCLDIR)\""
LDFLAGS = $(ARCHOPT) -L$(QCDIR) $(DEBUG) $(PLLIB) -lm -lfl -lqc $(RLLIB) 

FILESCC = $(wildcard *.cc)
FILESH = $(wildcard *.h)

SOURCE = $(FILESCC) $(FILESH) qcl.lex qcl.y Makefile

OBJECTS = types.o syntax.o typcheck.o symbols.o error.o \
          lex.o yacc.o print.o quheap.o extern.o eval.o exec.o \
          parse.o options.o debug.o cond.o dump.o plot.o format.o

all: do-it-all

ifeq (.depend,$(wildcard .depend))
include .depend
do-it-all: build
else
do-it-all: dep
	$(MAKE)
endif

#### Rules for depend

dep: lex.cc yacc.cc yacc.h $(QCLIB)
	for i in *.cc; do \
	  $(CPP) -I$(QCDIR) -MM $$i; \
	done > .depend

lex.cc: qcl.lex yacc.h
	$(LEX) -olex.cc qcl.lex

yacc.cc: qcl.y
	$(YACC) -t -d -o yacc.cc qcl.y

yacc.h: yacc.cc
	mv yacc.*?h yacc.h

$(QCLIB):
	cd $(QCDIR) && $(MAKE) libqc.a

#### Rules for build

build: qcl $(QCLINC)/default.qcl

qcl: $(OBJECTS) qcl.o $(QCLIB)
	$(CXX) $(OBJECTS) qcl.o $(LDFLAGS) -o qcl

$(QCLINC)/default.qcl: extern.cc
	grep "^//!" extern.cc | cut -c5- > $(QCLINC)/default.qcl

checkinst:
	[ -f ./qcl -a -f $(QCLINC)/default.qcl ] || $(MAKE) build

install: checkinst
	$(INSTALL) -m 0755 -d $(QCLBIN) $(QCLDIR)
	$(INSTALL) -m 0755 ./qcl $(QCLBIN)
	$(INSTALL) -m 0644 ./$(QCLINC)/*.qcl $(QCLDIR)

uninstall:
	-rm -f $(QCLBIN)/qcl
	-rm -f $(QCLDIR)/*.qcl
	-rmdir $(QCLDIR)

#### Other Functions

edit:
	nedit $(SOURCE) &

clean:
	rm -f *.o lex.* yacc.* 
	cd $(QCDIR) && $(MAKE) clean

clear: clean
	rm -f qcl $(QCLINC)/default.qcl .depend
	cd $(QCDIR) && $(MAKE) clear

dist-src: dep
	mkdir qcl-$(VERSION)
	cp README CHANGES COPYING .depend $(SOURCE) qcl-$(VERSION) 
	mkdir qcl-$(VERSION)/qc
	cp qc/Makefile qc/*.h qc/*.cc qcl-$(VERSION)/qc
	cp -r lib qcl-$(VERSION)
	tar czf qcl-$(VERSION).tgz --owner=0 --group=0 qcl-$(VERSION)
	rm -r qcl-$(VERSION)

dist-bin: build
	mkdir qcl-$(VERSION)-$(ARCH)
	cp Makefile README CHANGES COPYING qcl qcl-$(VERSION)-$(ARCH) 
	cp -r lib qcl-$(VERSION)-$(ARCH)
	tar czf qcl-$(VERSION)-$(ARCH).tgz --owner=0 --group=0 qcl-$(VERSION)-$(ARCH)
	rm -r qcl-$(VERSION)-$(ARCH)

upload: dist-src
	scp qcl-$(VERSION)*.tgz oemer@tph.tuwien.ac.at:html/tgz

scp: dist-src
	scp qcl-$(VERSION).tgz oemer@tph.tuwien.ac.at:bak/qcl-$(DATE).tgz
