/* fmtopts HEADER */
/* lang=C20 */

/* header file for the FMTOPTS subroutine */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-07-01, David A­D­ Morano
	This file was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	FMTOPTS_INCLUDE
#define	FMTOPTS_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<stdarg.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


enum fmtsopts {
	fmtopt_clean,			/* clean up the string-data */
	fmtopt_nooverr,			/* no-overflow-error */
	fmtopt_overlast
} ;


#define	FMTOPTS_OCLEAN		(1 << fmtopt_clean)
#define	FMTOPTS_ONOOVERR	(1 << fmtopt_nooverr)


#endif /* FMTOPTS_INCLUDE */


