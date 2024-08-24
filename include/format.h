/* format HEADER */
/* lang=C20 */

/* header file for the FORMAT subroutine */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-07-01, David A­D­ Morano
	This file was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	FORMAT_INCLUDE
#define	FORMAT_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<stdarg.h>
#include	<utypedefs.h>
#include	<clanguage.h>


#define	FORMAT_OCLEAN	(1<<0)		/* clean data */
#define	FORMAT_ONOOVERR	(1<<1)		/* do *not* return error on overflow */

EXTERNC_begin

extern int	format(char *,int,int,cchar *,va_list) noex ;

EXTERNC_end


#endif /* FORMAT_INCLUDE */


