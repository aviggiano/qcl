/**********************************************************************

This file is part of the Quantum Computation Language QCL.

(c) Copyright by Bernhard Oemer <oemer@tph.tuwien.ac.at>, 1998

This program comes without any warranty; without even the implied 
warranty of merchantability or fitness for any particular purpose.

     This program is free software under the terms of the 
     GNU General Public Licence (GPL) version 2 or higher

************************************************************************/

#include "format.h"

#define DATA_BEGIN	"\2"
#define DATA_END	"\5"
#define DATA_ESCAPE	"\033"

#define XTERMCOLOR(x) "\033[0;3" #x "m"

#define XTERM_BLACK 	XTERMCOLOR(0)
#define XTERM_RED 	XTERMCOLOR(1)
#define XTERM_GREEN 	XTERMCOLOR(2)
#define XTERM_YELLOW 	XTERMCOLOR(3)
#define XTERM_BLUE 	XTERMCOLOR(4)
#define XTERM_MAGENTA 	XTERMCOLOR(5)
#define XTERM_CYAN 	XTERMCOLOR(6)
#define XTERM_WHITE 	XTERMCOLOR(7)

const OutputFormat FormatPlain = {
  "",			// output_beg
  "",			// output_end
  "! ",			// error_beg
  "\n",			// error_end
  "! ",			// msg_beg
  "\n",			// msg_end
  ": ",			// print_beg
  "\n",			// print_end
  "",			// prompt_beg
  "",			// prompt_end
  "",			// ps_beg
  "",			// ps_end
  "",			// latex_beg
  "",			// latex_end
  "",			// math_beg
  "",			// math_end
  "",			// texverb_beg
  "",			// texverb_end
  "|",			// ket_beg
  ">",			// ket_end
  ";",			// xor
  "i",			// imag
#ifdef QCL_UTF8
  "\xc2\xb0",		// deg
#elif defined QCL_LAT1
  "\xb0",		// deg
#else
  "deg",		// deg
#endif
  "...",		// ldots
  " ",			// mult
  "",			// matrix_beg
  "",			// matrix_cont
  "",			// matrix_end
  "",			// matrix_col
  "",			// matrix_sep
  ""			// matrix_nl
};

const OutputFormat FormatXTerm = {
  XTERM_BLACK,		// output_beg
  XTERM_BLACK,		// output_end
  XTERM_RED "! ",	// error_beg
  XTERM_BLACK "\n",	// error_end
  XTERM_RED "! ",	// msg_beg
  XTERM_BLACK "\n",	// msg_end
  XTERM_BLUE ": ",	// print_beg
  XTERM_BLACK "\n",	// print_end
  "",			// prompt_beg
  "",			// prompt_end
  "",			// ps_beg
  "",			// ps_end
  "",			// latex_beg
  "",			// latex_end
  "",			// math_beg
  "",			// math_end
  "",			// texverb_beg
  "",			// texverb_end
  XTERM_MAGENTA "|",	// ket_beg
  ">" XTERM_BLACK,	// ket_end
  ";",			// xor
  "i",			// imag
#ifdef QCL_UTF8
  "\xc2\xb0",		// deg
#elif defined QCL_LAT1
  "\xb0",		// deg
#else
  "deg",		// deg
#endif
  "...",		// ldots
  " ",			// mult
  "",			// matrix_beg
  "",			// matrix_cont
  "",			// matrix_end
  "",			// matrix_col
  "",			// matrix_sep
  ""			// matrix_nl
};

const OutputFormat FormatDarkXTerm = {
  XTERM_WHITE,		// output_beg
  XTERM_WHITE,		// output_end
  XTERM_RED "! ",	// error_beg
  XTERM_WHITE "\n",	// error_end
  XTERM_RED "! ",	// msg_beg
  XTERM_WHITE "\n",	// msg_end
  XTERM_BLUE ": ",	// print_beg
  XTERM_WHITE "\n",	// print_end
  "",			// prompt_beg
  "",			// prompt_end
  "",			// ps_beg
  "",			// ps_end
  "",			// latex_beg
  "",			// latex_end
  "",			// math_beg
  "",			// math_end
  "",			// texverb_beg
  "",			// texverb_end
  XTERM_MAGENTA "|",	// ket_beg
  ">" XTERM_WHITE,	// ket_end
  ";",			// xor
  "i",			// imag
#ifdef QCL_UTF8
  "\xc2\xb0",		// deg
#elif defined QCL_LAT1
  "\xb0",		// deg
#else
  "deg",		// deg
#endif
  "...",		// ldots
  " ",			// mult
  "",			// matrix_beg
  "",			// matrix_cont
  "",			// matrix_end
  "",			// matrix_col
  "",			// matrix_sep
  ""			// matrix_nl
};

const OutputFormat FormatTeXmacs = {
  DATA_BEGIN "verbatim:",			// output_beg
  DATA_END,					// output_end
  DATA_BEGIN "latex:\\red\\verb~",		// error_beg
  "~" DATA_END,					// error_end
  DATA_BEGIN "latex:\\red\\verb~",		// msg_beg
  "~" DATA_END,					// msg_end
  DATA_BEGIN "latex:\\blue\\verb~",		// print_beg
  "~" DATA_END,					// print_end
						// prompt_beg
  DATA_BEGIN "channel:prompt" DATA_END DATA_BEGIN "latex:\\red\\verb~",
  "~" DATA_END,					// prompt_end
  DATA_BEGIN "ps:",				// ps_beg
  DATA_END,					// ps_end
  DATA_BEGIN "latex:",				// latex_beg
  DATA_END,					// latex_end
  "$",						// math_beg
  "$",						// math_end
  "\\verb~",					// texverb_beg
  "~",						// texverb_end
  "{\\magenta|\\mathrm{",			// ket_beg
  "}\\rangle}",					// ket_end
  "\\oplus",					// xor
  "i",						// imag
  "^{\\circ}",					// deg
  "\\ldots",					// ldots
  "\\,",					// mult
  "",			// matrix_beg
  "",			// matrix_cont
  "",			// matrix_end
  "",			// matrix_col
  "",			// matrix_sep
  ""			// matrix_nl
};
