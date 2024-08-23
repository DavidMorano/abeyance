/* cvtdig HEADER */
/* lang=C++20 */

/* convert an integer value into a c-string, given a value and base */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-01, David A­D­ Morano
	This subroutine was written having been adapated (from
	memory) from something I wrote back in the early 1980s (for
	embedded work).  I had to write every ... last  ... thing
	myself back in the old days.

	= 2020-04-23, David A-D- Morano
	I updated the |ffbsi| subroutine below to use the new C++20
	find-first-bit-set intrinsic (often a single machine
	instruction).

*/

/* Copyright © 1998,2020 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	cvtdig

	Description:
	This subroutine converts a value (and a base) into its
	string representation. It only works for bases that are a
	power-of-two, and also only for bases up to sixty four (64).

	Synopsis:
	template<typename UT>
	int cvtdig(char *buf,UT &val,int n,int b) noex

	Arguments:
	buf		result buffer
	val		value to convert
	n		number of bytes in given value to convert, generally:
				1, 2, 4, 8, 16, 32, 64, 128
	b		the base to use, generally:
				2=binary
				4=genetic
				8=octal
				16=hexadecimal
				32=
				64=

	Returns:
	-		length of result characters

*******************************************************************************/

#ifndef	CVTDIG_INCLUDE
#define	CVTDIG_INCLUDE
#ifdef	__cplusplus /* everything is C++ only */


#include	<envstandards.h>	/* MUST be first to configure */
#include	<climits>		/* |CHAR_BIT| */
#include	<cstddef>		/* |nullptr_t| */
#include	<bit>			/* <- for |countr_zero(3c++)| */
#include	<uvariables.hh>
#include	<usysrets.h>
#include	<utypedefs.h>
#include	<clanguage.h>
#include	<stdintx.h>


static constexpr int	cvtdig_maxbase = 64 ;	/* largest pow-of-two */

static inline constexpr int cvtdig_ffbsi(int b) noex {
	cuint		ub = uint(b) ;
	return std::countr_zero(ub) ;
}
/* end subroutine (cvtdig_ffbsi) */

template<typename UT>
constexpr int cvtdig(char *rbuf,int rlen,UT val,int n,int b) noex {
	cint		nshift = cvtdig_ffbsi(b) ;
	int		rs = SR_INVALID ;
	int		ndig = 0 ;
	if ((b > 1) && (b <= cvtdig_maxbase)) {
	    ndig = ((n * CHAR_BIT) + nshift - 1) / nshift ;
	    rs = SR_OVERFLOW ;
	    if (ndig <= rlen) {
	        cuint	mask = uint(b-1) ;
	        for (int i = (ndig - 1) ; i >= 0 ; i -= 1) {
	            rbuf[i] = sysword.w_digtab[val & mask] ;
	            val >>= nshift ;
	        } /* end for */
	        rbuf[ndig] = '\0' ;
		rs = SR_OK ;
	    } /* end if (no-overflow) */
	} /* end if (valid base) */
	return (rs >= 0) ? ndig : rs ;
}
/* end subroutine-template (cvtdig) */


#endif	/* __cplusplus */
#endif /* CVTDIG_INCLUDE */


