/* cfdigx HEADER */
/* lang=C++20 */

/* convert a digit c-string to its integer value */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-10-01, David A­D­ Morano
	This subroutine was written by being adapted from one of
	my previous versions of the same (from the early 1980s;
	embedded work at AT&T), which itself was adapted from an
	original asembly-language version (in Digital Euipment Corp
	VAX assembly).

	= 2013-04-30, David A­D­ Morano
	I took the plunge and rewrote this set of subroutine using
	the LIBC subroutines |strtoXX(3c)|, being much simplified
	now.  It is no longer stand-alone, like in the old days,
	but we have been mostly on UNIX®i for some time now (decades)
	and use in non-UNIX®i environments is now quite rare.  I
	hope that this is not a problem.  We will see.

	= 2023-10,10, David A-D- Morano
	I took the liberty to rewite these subroutines in terms of
	a subroutine-template. This did nothing to make the code
	faster in any way. After template expansion the code is the
	same as before.  All type-versions of the former subroutines
	are now in a single subroutine-template. I guess that I had
	too much idle time on my hands.

*/

/* Copyright © 1998,2013,2023 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Subroutines to convert digit strings to binary integers.

*******************************************************************************/

#ifndef	CFDIGX_INCLUDE
#define	CFDIGX_INCLUDE
#ifdef	__cplusplus /* everything is C++ only */


#include	<envstandards.h>	/* MUST be first to configure */
#include	<climits>
#include	<cstdlib>
#include	<cstring>
#include	<bit>
#include	<usystem.h>
#include	<stdintx.h>
#include	<char.h>
#include	<sfx.h>
#include	<uvariables.hh>
#include	<checkbase.h>
#include	<localmisc.h>


inline bool iszero(int ch) noex {
	ch &= 0xFF ;
	return (ch == '0') ;
}

inline int rmleadzero(cchar *sp,int sl) noex {
	int	nsl = sl ;
	for (int i = 0 ; (i < (sl-1)) && iszero(sp[0]) ; i += 1) {
	    nsl -= 1 ;
	} /* end for */
	return nsl ;
}

template<typename T>
int cfdigux(cc *sp,int sl,int b,T *rp) noex {
	int		rs = SR_FAULT ;
	if (sp) {
	    cchar	*nsp ;
	    int		nsl = sfshrink(sp,sl,&nsp) ;
	    rs = SR_INVALID ;
	    if (nsl > 0) {
	        if (nsl > 1) {
		    cint	r = rmleadzero(nsp,nsl) ;
		    nsp += (nsl-r) ;
		    nsl = r ;
		} /* end if */
	    	if ((rs = checkbase(nsp,nsl,b)) >= 0) {
		    rs = cvtfx(nsp,nsl,b,rp) ;
		} /* end if (checkbase) */
	    } /* end if (non-zero c-string) */
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine-template (cfdigx) */


#endif	/* __cplusplus */
#endif /* CFDIGX_INCLUDE */


