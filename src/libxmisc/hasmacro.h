/* hasmacro HEADER */
/* lang=C20 */

/* does a counted c-string contain a GTAG macro? */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	HASMACRO_INCLUDE
#define	HASMACRO_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern bool	hasmacro(cchar *,int) noex ;

static inline bool isMacro(cchar *lp,int ll) noex {
	return hasmacro(lp,ll) ;
}

EXTERNC_end


#endif /* HASMACRO_INCLUDE */


