/* GNU gettext - internationalization aids
   Copyright (C) 1995-1998, 2000-2002 Free Software Foundation, Inc.

   This file was written by Peter Miller <millerp@canb.auug.org.au>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */

#ifndef _PO_LEX_H
#define _PO_LEX_H

#include <sys/types.h>
#include <stdio.h>
#include <stdbool.h>
#include "error.h"
#include "progname.h"
#include "pos.h"
#include "xerror.h"

/* Lexical analyzer for reading PO files.  */


/* Global variables from po-lex.c.  */

/* Current position within the PO file.  */
extern lex_pos_ty gram_pos;
extern int gram_pos_column;

/* Number of parse errors within a PO file that cause the program to
   terminate.  Cf. error_message_count, declared in <error.h>.  */
extern unsigned int gram_max_allowed_errors;

/* True if obsolete entries shall be considered as valid.  */
extern bool pass_obsolete_entries;


/* Prepare lexical analysis.  */
extern void lex_start PARAMS ((FILE *fp, const char *real_filename,
			       const char *logical_filename));

/* Terminate lexical analysis.  */
extern FILE *lex_end PARAMS ((void));

/* Open the PO file FNAME and prepare its lexical analysis.  */
extern void lex_open PARAMS ((const char *fname));

/* Terminate lexical analysis and close the current PO file.  */
extern void lex_close PARAMS ((void));

/* Return the next token in the PO file.  The return codes are defined
   in "po-gram-gen2.h".  Associated data is put in 'po_gram_lval.  */
extern int po_gram_lex PARAMS ((void));

/* po_gram_lex() can return comments as COMMENT.  Switch this on or off.  */
extern void po_lex_pass_comments PARAMS ((bool flag));

/* po_gram_lex() can return obsolete entries as if they were normal entries.
   Switch this on or off.  */
extern void po_lex_pass_obsolete_entries PARAMS ((bool flag));


/* ISO C 99 is smart enough to allow optimizations like this.  */
#if __STDC__ && (defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L)

/* CAUTION: If you change this macro, you must also make identical
   changes to the function of the same name in src/po-lex.c  */

# define po_gram_error(fmt, ...)					    \
  do {									    \
    char *totalfmt = xasprintf ("%s%s", "%s:%lu:%d: ", fmt);		    \
    error_with_progname = false;					    \
    error (0, 0, totalfmt, gram_pos.file_name,				    \
	   (unsigned long) gram_pos.line_number, gram_pos_column + 1,	    \
	   __VA_ARGS__ + 0);						    \
    error_with_progname = true;						    \
    free (totalfmt);							    \
    if (*fmt == '.')							    \
      --error_message_count;						    \
    else if (error_message_count >= gram_max_allowed_errors)		    \
      error (1, 0, _("too many errors, aborting"));			    \
  } while (0)

/* CAUTION: If you change this macro, you must also make identical
   changes to the function of the same name in src/po-lex.c  */

# define po_gram_error_at_line(pos, fmt, ...)				    \
  do {									    \
    error_with_progname = false;					    \
    error_at_line (0, 0, (pos)->file_name, (pos)->line_number,		    \
		   fmt, __VA_ARGS__ + 0);					    \
    error_with_progname = true;						    \
    if (*fmt == '.')							    \
      --error_message_count;						    \
    else if (error_message_count >= gram_max_allowed_errors)		    \
      error (1, 0, _("too many errors, aborting"));			    \
  } while (0)

/* GCC is also smart enough to allow optimizations like this.  */
#elif __STDC__ && defined __GNUC__ && __GNUC__ >= 2 && !defined __APPLE_CC__

/* CAUTION: If you change this macro, you must also make identical
   changes to the function of the same name in src/po-lex.c  */

# define po_gram_error(fmt, args...)					    \
  do {									    \
    char *totalfmt = xasprintf ("%s%s", "%s:%d:%d: ", fmt);		    \
    error_with_progname = false;					    \
    error (0, 0, totalfmt, gram_pos.file_name, gram_pos.line_number,	    \
	   gram_pos_column + 1 , ## args);				    \
    error_with_progname = true;						    \
    free (totalfmt);							    \
    if (*fmt == '.')							    \
      --error_message_count;						    \
    else if (error_message_count >= gram_max_allowed_errors)		    \
      error (1, 0, _("too many errors, aborting"));			    \
  } while (0)

/* CAUTION: If you change this macro, you must also make identical
   changes to the function of the same name in src/po-lex.c  */

# define po_gram_error_at_line(pos, fmt, args...)			    \
  do {									    \
    error_with_progname = false;					    \
    error_at_line (0, 0, (pos)->file_name, (pos)->line_number,		    \
		    fmt , ## args);					    \
    error_with_progname = true;						    \
    if (*fmt == '.')							    \
      --error_message_count;						    \
    else if (error_message_count >= gram_max_allowed_errors)		    \
      error (1, 0, _("too many errors, aborting"));			    \
  } while (0)

#else
extern void po_gram_error PARAMS ((const char *fmt, ...));
extern void po_gram_error_at_line PARAMS ((const lex_pos_ty *pos,
					   const char *fmt, ...));
#endif


/* Contains information about the definition of one translation.  */
struct msgstr_def
{
  char *msgstr;
  size_t msgstr_len;
};

#endif
