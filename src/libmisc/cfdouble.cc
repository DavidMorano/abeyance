/* cfdouble SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* convert a floating point digit string to its double value */
/* version %I% last-modified %G% */


/* revision history:

	= 2007-01-88, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 2007 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Name:
	cfdouble

	Description:
	This subroutine also ignores white space at the front or
	back of the digit string and handles a minus sign.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<cerrno>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<usystem.h>
#include	<snwcpy.h>
#include	<localmisc.h>

#include	"cfdouble.h"


/* local defines */

#define	LOCBUFLEN	100


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */

constexpr int		loclen = LOCBUFLEN ;


/* exported variables */


/* exported subroutines */

int cfdouble(cchar *sbuf,int slen,double *rp) noex {
	int		rs = SR_FAULT ;
	if (sbuf && rp) {
	    cchar	*sp = sbuf ;
	    char	locbuf[loclen + 1] ;
	    rs = SR_OK ;
	    if (slen >= 0) { /* because we need string to be NUL terminated */
	        sp = locbuf ;
	        rs = snwcpy(locbuf,loclen,sbuf,slen) ;
	        if (rs == SR_OVERFLOW) rs = SR_INVALID ;
	    }
	    if (rs >= 0) {
	        errno = 0 ;
	        char *bp ;
		*rp = strtod(sp,&bp) ;
	        if (errno != 0) {
		    rs = (- errno) ;
		}
	    }
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (cfdouble) */


