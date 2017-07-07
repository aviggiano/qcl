/**********************************************************************

This file is part of the Quantum Computation Language QCL.

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/


#ifndef FORMAT_H
#define FORMAT_H

struct OutputFormat {
  const char *output_beg;
  const char *output_end;
  const char *error_beg;
  const char *error_end;
  const char *msg_beg;
  const char *msg_end;
  const char *print_beg;
  const char *print_end;
  const char *prompt_beg;
  const char *prompt_end;
  const char *ps_beg;
  const char *ps_end;
  const char *latex_beg;
  const char *latex_end;
  const char *math_beg;
  const char *math_end;
  const char *texverb_beg;
  const char *texverb_end;
  const char *ket_beg;
  const char *ket_end;
  const char *exor;
  const char *imag;
  const char *deg;
  const char *ldots;
  const char *mult;
  const char *matrix_beg;
  const char *matrix_cont;
  const char *matrix_end;
  const char *matrix_col;
  const char *matrix_sep;
  const char *matrix_nl;
};

extern const OutputFormat FormatPlain;
extern const OutputFormat FormatXTerm;
extern const OutputFormat FormatDarkXTerm;
extern const OutputFormat FormatTeXmacs;

#endif
