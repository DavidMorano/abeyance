/* vstrcmpx HEADER */
/* lang=C20 */

/* convert a character string to a given case */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	VSTRCMPX_INCLUDE
#define	VSTRCMPX_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>

#include	<vstrkeycmpx.h>


EXTERNC_begin

extern int vstrcmpo(cchar **,cchar **) noex ;
extern int vstrcmpr(cchar **,cchar **) noex ;

static inline int vstrcmp(cchar **s1pp,cchar **s2pp) noex {
	return vstrcmpo(s1pp,s2pp) ;
}

EXTERNC_end


#endif /* VSTRCMPX_INCLUDE */


