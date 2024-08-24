/* cfdect HEADER */
/* lang=C20 */

/* Convert-From-Decimal-Time */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	CFDECT_INCLUDE
#define	CFDECT_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<stdintx.h>


EXTERNC_begin

extern int cfdecti(cchar *,int,int *) noex ;

EXTERNC_end

#ifdef	__cplusplus

static inline int cfdect(cchar *sp,int sl,int *rp = nullptr) noex {
	return cfdect(sp,sl,rp) ;
}

#else 

static inline int cfdect(cchar *sp,int sl,int *rp) noex {
	return cfdect(sp,sl,rp) ;
}

#endif /* __cplusplus */


#endif /* CFDECT_INCLUDE */


