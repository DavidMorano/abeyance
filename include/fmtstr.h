/* fmtstr HEADER */
/* lang=C20 */

/* header file for the FMTSTR subroutine */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-07-01, David A­D­ Morano
	This file was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	FMTSTR_INCLUDE
#define	FMTSTR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<stdarg.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>

#include	<fmtopts.h>


EXTERNC_begin

extern int	fmtstr(char *,int,int,cchar *,va_list) noex ;

EXTERNC_end


#endif /* FMTSTR_INCLUDE */


