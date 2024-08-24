/* constdiv HEADER */
/* lang=C++20 */

/* perform division of a 32-bit value by a constant w/o using division */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This is a common algorithn for performing division by a
	constant (what I am callig "constant division").  I forget
	the name of the person who invented this.  If you know
	or remember who he was, please let me know so that I
	can credit him right here.
		-- David A.D. Morano

	Update, found it (the reference). This algorithm is from
	"Hacker's Delight," second edition, ch 10, 
	"Integer division by constant"

	Rules:
	Unisigned integer division of 32-bit numbers (|uint|).

	How-to-use:
	{
	    uint	n = «x1» ;
	    uint	d = «x2» ;
	    uint	q ;
	    constdiv	diver(d) ;
	    q = diver(n) ;
	    cout << q << eol ;
	}

*******************************************************************************/

#ifndef	CONSTDIV_INCLUDE
#define	CONSTDIV_INCLUDE
#ifdef	__cplusplus /* everything is C++ only */


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<stdintx.h>
#include	<localmisc.h>


struct constdiv {
	uint		m = 0 ;
	uint		s = 0 ;
	constexpr constdiv() = delete ;
	constexpr constdiv(const constdiv &) = delete ;
	constexpr constdiv(uint d) noex {
	    const uint	two31 = 0x80000000 ;
	    if (d > 0) {
		uint	ad = d, anc, delta, q1, r1, q2, r2, t ;
		int	p = 31 ;
		t = two31 + (d >> 31) ;
		anc = t - 1 - t % ad ;
		q1 = two31 / anc ;
		r1 = two31 - q1 * anc ;
		q2 = two31 / ad ;
		r2 = two31 - q2 * ad ;
		repeat {
		    p += 1 ;
		    q1 = 2 * q1 ;
		    r1 = 2 * r1 ;
		    if (r1 >= anc) {
			q1 += 1 ;
			r1 -= anc ;
		    }
		    q2 = 2 * q2 ;
		    r2 = 2 * r2 ;
		    if (r2 >= ad) {
			q2 += 1 ;
			r2 -= ad ;
		    }
		    delta = ad - r2 ;
		} until (!((q1 < delta) || (q1 == delta && r1 == 0))) ;
		m = q2 + 1 ;
		s = p - 32 ;
	    } /* end if (valid divisor) */
	} ; /* end constructor */
	constexpr uint operator () (uint n) noex {
	    ulong	hi = ulong((ulong(m) * ulong(n)) >> 32) ;
	    uint	q ;
	    q = uint(hi) ;
	    if (s >= 0) {
		q >>= s ;
		q += (q >> 31) ;
	    }
	    return q ;
	} ;
} ; /* end subroutine (constdiv) */


#endif	/* __cplusplus */
#endif /* CONSTDIV_INCLUDE */


