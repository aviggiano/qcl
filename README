
QCL version 0.6.4 by Bernhard Oemer <oemer@tph.tuwien.ac.at>
============================================================


Despite many common concepts with classical computer science, quantum
computing is still widely considered as a special discipline within the
broad field of theoretical physics.  One reason for the slow adoption of
QC by the computer science community is the confusing variety of
formalisms (Dirac notation, matrices, gates, operators, etc.), none of
which has any similarity with classical programming languages, as well
as the rather ``physical'' terminology in most of the available
literature.

QCL (Quantum Computation Language) tries to fill this gap: QCL is a
hight level, architecture independent programming language for quantum
computers, with a syntax derived from classical procedural languages
like C or Pascal.  This allows for the complete implementation and
simulation of quantum algorithms (including classical components) in one
consistent formalism.


Features:
---------

 -  a classical control language with functions, flow-control,
    interactive i/o and various classical data types (int, real,
    complex, boolean, string)

 -  2 quantum operator types: general unitarian (operator) and
    reversible pseudo-classic gates (qufunct) 

 -  inverse execution, allowing for on-the-fly determination of the
    inverse operator though caching of operator calls

 -  various quantum data types (qubit registers) for compile time
    information on access modes (qureg, quconst, quvoid, quscratch)

 -  convenient functions to manipulate quantum registers (q[n] -
    qubit, q[n:m] - substring, q&p - combined register)

 -  Quantum memory management (quheap) allowing for local quantum
    variables

 -  Transparent integration of Bennet-style scratch space management

 -  Easy adaption to individual sets of elementary operators

 -  graphical output for (X11 and Postscript) (v0.5)

 -  conditional operators and quantum if-statements (v0.5, experimental)


Availability:
-------------

QCL has been developed under Linux; version 0.5.1 is tested to compile
with the GNU C++ compiler 2.95.3 under SuSE 7.3. It should - however -
compile under any Unix system with minor modifications (see the Makefile
for details).

The current version of QCL (sources and i386 Linux binaries) is available from
my homepage:

  http://tph.tuwien.ac.at/~oemer/qcl/


Documentation:
--------------

The reference documentation for QCL is my master thesis in technical
physics "A Procedural Formalism for Quantum Computing". It gives a
complete reference to QCL with many examples and also features a brief
introduction into Quantum Computing. Some knowledge about Quantum
Physics and familiarity with the braket-formalism is required. 

A more basic introduction esp. for computing scientists to quantum
computing, quantum algorithms and QCL is included in my CS master thesis
"Quantum Programming in QCL" which also features an introductory chapter
to quantum physics in general.

Both documents are available online in Postscript or HTML format:

  http://tph.tuwien.ac.at/~oemer/qcl.html#doc


Installation:
-------------

Besides the usual C++ development tools, you will need to have flex,
bison and (optionally) GNU readline installed on your system.

Untar the source package, then cd to the QCL directory, edit the Makefile
for your needs and type

  make
  make install

This will, by default, install the binary qcl to /usr/local/bin and the QCL
include files to /usr/local/lib/qcl.

For plotting support, libplotter (the C++ bindings of of GNU libplot) is
required. GNU libplot is part of the the GNU plotutils; see

  http://www.gnu.org/software/plotutils/

Since version 0.4.3, QCL also includes support for the TeXmacs mathematical
text editor. Recent TeXmacs distributions (1.0.0.6 or newer) already provide
the necessary interfaces, so no additional installation is required. You can
get the latest TeXmacs sources from

  http://www.texmacs.org/


Credits:
--------

Andrey G. Grozin <A.G.Grozin@inp.nsk.su>
  - initial TeXmacs support
  - color XTerm support
  
Muhammad Hussain Yusuf <myusuf@btconnect.com> 
  - maintainer of the debian QCL package
  - testing of QCL on many hardware plattforms


Feedback:
---------

If you encounter any bugs or miss any particular feature or just like
QCL, please let me know. My email address is

  Bernhard Oemer <oemer@tph.tuwien.ac.at>

The QCL interpreter is Open Source(tm) software, so please feel free to write
your own ports and extentions. If you send me patches, I will most probably
include them in future versions of QCL and maintain them to the best of my
abilities. ;-) Since English isn't my native language, I also appreciate
any orthographic and grammatical corrections.



Bernhard Oemer

