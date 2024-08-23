/* strxcmp HEADER */
/* lang=C20 */

/* c-string comparisons */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	STRXCMP_INCLUDE
#define	STRXCMP_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<strnxcmp.h>


EXTERNC_begin

extern int	stremacmp(cchar *,cchar *) noex ;
extern int	strpcmp(cchar *,cchar *) noex ;
extern int	strleadcmp(cchar *,cchar *) noex ;

static inline int strdictcmp(cchar *s1,cchar *s2) noex {
	return strnndictcmp(s1,-1,s2,-1) ;
}

EXTERNC_end


#endif /* STRXCMP_INCLUDE */


