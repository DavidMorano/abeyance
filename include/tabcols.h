/* tabcols HEADER */
/* lang=C20 */

/* calculate column values */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	TABCOLS_INCLUDE
#define	TABCOLS_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>


#define	TABCOLS_DEF	8		/* eight columns per TAB character */


EXTERNC_begin

extern int tabcols(int,int) noex ;

EXTERNC_end


#endif /* TABCOLS_INCLUDE */


