/* xxtostr SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 */

/* subroutines to convert an integer to a c-string */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Group:
	{xx}tostr

	Name:
	uxxtostr

	Description:
	These subroutines convert an integer (signed or unsigned
	of various sized types) into a c-string representation that
	is placed into the caller supplied buffer (of specified
	length).

	Synopsis:
	template<typename UT,typename ST>
	char *uxxtostr(char **epp,int b,ST v) noex

	Arguments:
	endp		pointer to one past the end of the supplied buffer
	base		number base
	v		integer value to be converted
	epp		pointer to passed endp

	Returns:
	>=0		length of buffer used by the conversion
	<0		error in the conversion

	Notes:
	As it stands now, these subroutines do not perform any funny
	business in trying to make this process faster!  These
	subroutines are, therefore, probably the slowest such
	conversions routinely available.  To really move (execute)
	quickly through the division-related aspects of the require
	algorithm, one would have to use assembly language where
	both the quotient and the reminder of a division are produced
	simultaneously (since each are needed to continue).  This,
	of course, assumes that the underlying machine architecture
	has such instructions.  But short of assembly (and and the
	required machine instructions) this present implemtnation
	is adequate.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<cerrno>		/* <- for |errno| */
#include	<climits>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<stdintx.h>
#include	<localmisc.h>		/* ?? not-needed ?? */

#include	"xxtostr.h"


/* local defines */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */

constexpr int		b = 10 ;


/* exported variables */


/* exported subroutines */

char *itostr(int v,char *endp) noex {
	int		rs ;
	char		*rp = nullptr ;
	if ((rs = sxxtostr<uint>(endp,b,v)) >= 0) {
	    rp = (endp - rs) ;
	} else {
	    errno = (-rs) ;
	}
	return (rs >= 0) ? rp : nullptr ;
}

char *ltostr(long v,char *endp) noex {
	int		rs ;
	char		*rp = nullptr ;
	if ((rs = sxxtostr<ulong>(endp,b,v)) >= 0) {
	    rp = (endp - rs) ;
	} else {
	    errno = (-rs) ;
	}
	return (rs >= 0) ? rp : nullptr ;
}

char *lltostr(longlong v,char *endp) noex {
	int		rs ;
	char		*rp = nullptr ;
	if ((rs = sxxtostr<ulonglong>(endp,b,v)) >= 0) {
	    rp = (endp - rs) ;
	} else {
	    errno = (-rs) ;
	}
	return (rs >= 0) ? rp : nullptr ;
}

char *uitostr(uint uv,char *endp) noex {
	char		*rp = nullptr ;
	int		rs ;
	if ((rs = uxxtostr(endp,b,uv)) >= 0) {
	    rp = (endp - rs) ;
	} else {
	    errno = (-rs) ;
	}
	return (rs >= 0) ? rp : nullptr ;
}

char *ultostr(ulong uv,char *endp) noex {
	char		*rp = nullptr ;
	int		rs ;
	if ((rs = uxxtostr(endp,b,uv)) >= 0) {
	    rp = (endp - rs) ;
	} else {
	    errno = (-rs) ;
	}
	return (rs >= 0) ? rp : nullptr ;
}

char *ulltostr(ulonglong uv,char *endp) noex {
	char		*rp = nullptr ;
	int		rs ;
	if ((rs = uxxtostr(endp,b,uv)) >= 0) {
	    rp = (endp - rs) ;
	} else {
	    errno = (-rs) ;
	}
	return (rs >= 0) ? rp : nullptr ;
}


