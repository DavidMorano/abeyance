/* ndigit HEADER */
/* lang=C20 */

/* calculate the number of digits in a given integer given a number-base */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	NDIGIT_INCLUDE
#define	NDIGIT_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<stdintx.h>


EXTERNC_begin


extern int ndigiti(int,int) noex ;
extern int ndigitl(long,int) noex ;
extern int ndigitll(longlong,int) noex ;

extern int ndigitui(uint,int) noex ;
extern int ndigitul(ulong,int) noex ;
extern int ndigitull(ulonglong,int) noex ;

static inline int ndigits(int v,int b) noex {
	return ndigiti(v,b) ;
}

EXTERNC_end

#ifdef	__cplusplus

template<typename T>
constexpr int ndigit(T v,int b) noex {
	int		n = 0 ;
	if (v >= 0) {
	    uint	ub = uint(b) ;	/* faster? */
	    if (b >= 2) {
	        if (v == 0) {
	            n = 1 ;
	        } else {
	            while (v != 0) {
	                n += 1 ;
	                v = (v / ub) ;
	            }
		} /* end if (non-zero positive) */
	    } /* end if (valid base) */
	} /* end if (valid) */
	return n ;
}
/* end subroutine-template (ndigit) */

#endif /* __cplusplus */


#endif /* NDIGIT_INCLUDE */


