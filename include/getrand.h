/* getrand HEADER */
/* lang=C20 */

/* retrieve a cheap random number */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETRAND_INCLUDE
#define	GETRAND_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<stdintx.h>


EXTERNC_begin

extern int	getrand(void *,int) noex ;
extern int	getrandi(int *) noex ;
extern int	getrandl(long *) noex ;
extern int	getrandll(longlong *) noex ;

EXTERNC_end

#ifdef	__cplusplus

static inline int getrand(uint *p, int n = 1) noex {
	cint	sz = sizeof(uint) ;
	return getrand(p,(sz * n)) ;
}
static inline int getrand(ulong *p,int n = 1) noex {
	cint	sz = sizeof(ulong) ;
	return getrand(p,(sz * n)) ;
}
static inline int getrand(longlong *p,int n = 1) noex {
	cint	sz = sizeof(ulonglong) ;
	return getrand(p,(sz * n)) ;
}

#endif /* __cplusplus */


#endif /* GETRAND_INCLUDE */


