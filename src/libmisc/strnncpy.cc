/* strnncpy SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 */

/* copy a string and fill destination out with NULs */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	strnncpy

	Description:
	Copy a source string to a destination until either the end
	of the source string is reached (by its end-marker) or the
	length of the source string is exhausted.  We always zero
	out to the length of the destination string.  The copy also
	terminates on the exhaustion of the maximum-length destination
	length.  The result is not NUL-terminated.

	Synopsis:
	char *strnncpy(char *d,cchar *s,int slen,int n) noex

	Arguments:
	d	string buffer that receives the copy
	s	the source string that is to be copied
	slen	length of string to copy
	n	the maximum length to be copied

	Returns:
	-	the character pointer to the end of the destination

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>		/* |strncpy(3c)| | |memset(3c)| */
#include	<algorithm>		/* |min(3c++)| + |max(3c++)| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<localmisc.h>


/* local defines */


/* imported namespaces */

using std::min ;			/* subroutine-template */
using std::max ;			/* subroutine-template */


/* local typedefs */


/* external subroutines */

extern "C" {
    extern char *strnncpy(char *,cchar *,int,int) noex ;
}


/* external variables */


/* forward references */

static char *dstcpy(char *dp,cc *sp,int sl = -1) noex {
    	while (sl && *sp) {
	    *dp++ = *sp++ ;
	    sl -= 1 ;
	}
	return dp ;
}

static char *dstncpy(char *dp,int dl,cc *sp,int sl = -1) noex {
    	char	*rp = dstcpy(dp,sp,sl) ;
	if (int fl ; (fl = ((dp + dl) - rp)) > 0) {
	    memset(rp,0,fl) ;
	}
	return rp ;
}


/* local variables */


/* exported variables */


/* exported subroutines */

char *strnncpy(char *dp,cchar *sp,int sl,int sz) noex {
	char		*rp = dp ;
	if (sz >= 0) {
	    if (sl >= 0) {
		if (sl >= sz) {
		    rp = dstcpy(dp,sp,sz) ;
		} else {
		    rp = dstncpy(dp,sz,sp,sl) ;
		}
	    } else {
		rp = dstncpy(dp,sz,sp) ;
	    }
	} else {
	    rp = dstcpy(dp,sp,sl) ;
	}
	return rp ;
}
/* end subroutine (strnncpy) */


