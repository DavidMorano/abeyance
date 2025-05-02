/* xxtostr HEADER */
/* encoding=ISO8859-1 */
/* lang=C20,C++20 */

/* subroutines to convert an integer to a c-string */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

	= 2024-01-15, David A.D. Morano
	Added a comment below.

*/

/* Copyright (c) 1998,2024 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Group:
	{x}tostr

	Description:
	These subroutines convert integers (either signed or unsigned
	of various sized types) into their c-string digit
	representations.

	The following subroutines are provoided for base-20 conversions
	of the various types:

	name		signed	size
	itostr		yes	32-bit
	ltostr		yes	64-bit
	lltostr		yes	128-bit
	uitostr		no	32-bit
	ultostr		no	64-bit
	ulltostr	no	128-bit

	The two subroutine-templates (below) can convert for any
	number base.  The subroutine-templates are:

	name		signed	size	base
	sxxtostr	yes	any	any up to base-64
	uxxtostr	no	any	any up to base-64

	Rnjoy.

	Notes:
	As you may know, aside from the more recent standardization
	of the "convert-to-string" numeric conversion subroutine-templates
	in C++, there has never been a standardized implementation
	of these kinds of conversion functions.
		-- 2024-01-15, David A.D. Morano

*******************************************************************************/

#ifndef	XXTOSTR_INCLUDE
#define	XXTOSTR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<limits.h>		/* |LONG_MAX| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<libutil.hh>		/* |cstrlen(3u)| */
#include	<syswords.hh>
#include	<stdintx.h>


#ifdef	__cplusplus

inline cint		xxtostr_maxbase = cstrlen(sysword.w_digtab) ;

template<typename UT>
inline int uxxtostr(char *endp,int b,UT v) noex {
	uint		ub = uint(b) ;
	int		rs = SR_FAULT ;
	char		*rp = endp ;
	if (endp) {
	    rs = SR_NOTSUP ;
	    *rp = '\0' ;
	    if ((b >= 2) && (b <= xxtostr_maxbase)) {
	        if (v != 0) {
                    int		di ;
	            if_constexpr (szof(UT) > szof(ulong)) {
	                const UT	vmask(~ LONG_MAX) ;
		        UT		utnv ;
	                while ((v & vmask) != 0L) {
	                    utnv = v / ub ;
                            di = int(v - (utnv * ub)) ;
                            *--rp = sysword.w_digtab[di] ;
	                    v = utnv ;
	                } /* end while (slower) */
	                {
		            ulong	lv = ulong(v) ;
		            ulong	nv ;
		            while (lv != 0) {
	                        nv = lv / ub ;
                                di = int(lv - (nv * ub)) ;
                                *--rp = sysword.w_digtab[di] ;
	                        lv = nv ;
		            } /* end while */
		            v = lv ;
	                } /* end block (faster) */
	            } else {
		        UT		nv ;
	                while (v != 0) {
	                    nv = v / ub ;
                            di = int(v - (nv * ub)) ;
                            *--rp = sysword.w_digtab[di] ;
	                    v = nv ;
	                } /* end while (regular) */
		    } /* end if-constexpr (size-of-operand) */
	            rs = SR_OK ;
	        } else {
	            rs = SR_OK ;
	            *--rp = '0' ;
	        } /* end if */
	    } /* end if (base supported) */
	} /* end if (non-null) */
	return (rs >= 0) ? int(endp - rp) : rs ;
}
/* end subroutine-template (uxxtostr) */

template<typename UT,typename ST>
inline constexpr int sxxtostr(char *endp,int b,ST v) noex {
	UT		ulv = (UT) v ;
	int		rs = SR_FAULT ;
	char		*rp = nullptr ;
	if (v < 0) ulv = (- ulv) ;
	if (endp) {
	    if ((rs  = uxxtostr(endp,b,ulv)) >= 0) {
		cint	len = rs ;
		rp = (endp - len) ;
	        if (v < 0) *--rp = '-' ;
	    }
	}
	return (rs >= 0) ? int(endp - rp) : rs ;
}
/* end subroutine (sxxtostr) */

#endif /* __cplusplus */

EXTERNC_begin

char *itostr(int,char *) noex ;
char *ltostr(long,char *) noex ;
char *lltostr(longlong,char *) noex ;

char *uitostr(uint,char *) noex ;
char *ultostr(ulong,char *) noex ;
char *ulltostr(ulonglong,char *) noex ;

EXTERNC_end


#endif /* XXTOSTR_INCLUDE */


