/* compactstr HEADER */
/* lang=C20 */

/* compact (remove white-space) a c-string inplace */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	COMPACTSTR_INCLUDE
#define	COMPACTSTR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>


EXTERNC_begin

extern int compactstr(char *,int) noex ;

EXTERNC_end


#endif /* COMPACTSTR_INCLUDE */


