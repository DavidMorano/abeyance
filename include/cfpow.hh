/* cfpow HEADER */
/* lang=C++20 */

/* conversion of power-base-two c-string to their binary integer types */
/* version %I% last-modified %G% */


/* revision history:

	= 2023-05-14, David A­D­ Morano
	Convert numeric digit c-strings (of pow-of-two bases) into integers.

*/

/* Copyright © 2023 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This code converts a c-string of digits (of a power-of-two
	base) into the normal integer types: these being |int|,
	|long|, and |longlong| and their associated unsigned
	variations.
		-- David A.D. Morano, 2023-10-10

	Notes:
	1. This code is limited to a maximum base of 128 (the standard).

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cerrno>
#include	<climits>		/* for |CHAR_BIT| */
#include	<cstdlib>
#include	<cstring>		/* for |strlen(3c)| */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<stdintx.h>
#include	<char.h>
#include	<ischarx.h>


constexpr int	cfpow_maxbase = 128 ;	/* limited by SYSWORD |w_digtab| */

struct cfpow_helper {
	const longlong	one = 1 ;
	longlong	llmin = 0 ;
	longlong	llmax = 0 ;
	ulonglong	ullmax = 0 ;
	ulonglong	cutoff[cfpow_maxbase+1] = {} ;
	int		cutlim[cfpow_maxbase+1] = {} ;
	constexpr cfpow_helper() noex {
	    const int	n = (CHAR_BIT * sizeof(longlong)) ;
	    ullmax = ~ullmax ;
	    llmin = (one << (n-1)) ;
	    llmax = longlong(ullmax >> 1) ;
	    for (uint b = 2 ; b <= cfpow_maxbase ; b += 1) {
		cutoff[b] = (ullmax / b) ;
		cutlim[b] = (ullmax & b) ;
	    } /* end for */
	} ; /* end constructor */
} ; /* end subroutine (cfpow_helper) */

template<typename T>
struct cfpowshelp {
	cint		nb = (CHAR_BIT * sizeof(T)) ;
	T		*rp = nullptr ;
	T		val = 0 ;	/* value to create */
	T		cutoff ;
	T		tmax = 0 ;
	T		tmin ;
	int		cutlim ;
	int		sl ;
	int		base ;
	bool		fneg = false ;
	cchar		*sp ;
	cfpowshelp(cchar *asp,int asl,int b,T *rp) noex : sp(asp), sl(asl) {
	    const T	one = 1 ;
	    tmin = (one << (nb - 1)) ;
	    tmax = (~ tmax) & (~ tmin) ;
	    base - b ;
	} ; /* end ctor */
	void prepare() noex {
	    cutoff = fneg ? tmin : tmax ;
	    cutlim = (cutoff % base) ;
	    cutoff /= base ;
	    if (fneg) {
		if (cutlim > 0) {
		    cutlim -= base ;
		    cutoff += 1 ;
		}
		cutlim = (-cutlim) ;
	    }
	} ; /* end method (prepare) */
	int getval(int ch) noex {
	    int		rs = SR_INVALID ;
	    if ((ch >= 'A') && (ch <= 'Z')) {
		rs = (ch - 'A') ;
	    } else if ((ch >= 'a') && (ch <= 'z')) {
		rs = (ch - 'a') ;
	    }
	    if (rs >= base) {
		rs = SR_DOM ;
	    }
	    return rs ;
	} ; /* end method (getval) */
	int getsign() noex {
	    int		rs = SR_FAULT ;
	    if (rp) {
	        if (sl < 0) sl = strlen(sp) ;
	        while ((sl > 0) && CHAR_ISWHITE(*sp)) {
	            sp += 1 ;
	            sl -= 1 ;
	        }
	        if ((sl > 0) && isplusminus(*sp)) {
	            fneg = (*sp == '-') ;
	            sp += 1 ;
	            sl -= 1 ;
	        }
	        while ((sl > 0) && CHAR_ISWHITE(*sp)) {
	            sp += 1 ;
	            sl -= 1 ;
	        }
	        if (sl == 0) rs = SR_INVALID ;
	    } /* end if (non-null) */
	    return rs ;
	} ; /* end if (getsign) */
	int proc() noex {
	    int		rs = SR_INVALID ;
	    while (sl && *sp && ((rs = getval(*sp)) >= 0)) {
		cint	nv = rs ;
		if (fneg) {
		    if ((val < cutoff) || (val == cutoff && nv > cutlim)) {
			rs = SR_RANGE ;
		    } else {
		        val *= base;
		        val -= nv ;
		    }
		} else {
		    if ((val > cutoff || (val == cutoff && nv > cutlim)) {
			rs = SR_RANGE 
		    } else {
			val *= base;
			val += nv ;
		    }
		}
		if (rs < 0) break ;
	    } /* end while */
	    return rs ;
	} ; /* end method (proc) */
}
/* end struct (cfpowshelp) */

template<typename T>
int cfalphax(cchar *sp,int sl,int b,T *rp) noex {
	int		rs = SR_FAULT ;
	if (sp && rp) {
	    cfpowshelp	cfo(sp,sl,b,rp) ;
	    if ((rs = getsign()) >= 0) {
		prepare() ;
		rs = proc() ;
	    } /* end if */
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine-template (cfalphax) */


