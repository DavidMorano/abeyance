/* strnwcpy SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* copy a counted c-string to a sized destination buffer */
/* version %I% last-modified %G% */

#define	CF_STPNCPY	1		/* use |stpncpy(3c)| (POSIX® 2008) */

/* revision history:

	= 1998-11-01, David A­D­ Morano
	This code was originally written.

	= 2025-01-15, David A­D­ Morano
	In the course of reviewing this code (after some years now)
	for conformance with the C++20 standard (I am actually
	compiling now-a-days for C++26), I decided (again after
	all of these years), to change the code to use (optionally
	when a compile-define 'define' is set to '1') the new (as
	of POSIX® 2008) subroutine |stpncpy(3c)|.  Using this new
	subroutine is now the default.  Does it really make this
	faster?  Who knows?  I simply put a compile-time flag (using
	C++11 'constexpr') around the old and new code, in the
	subroutine |dstcpy()| below, to decide which code to use.

*/

/* Copyright © 1998,2025 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	strnwcpy

	Description:
	Ths subroutine is similar to |strncpy(3c)| (in that it
	zero-fills out any remainder of the destiation string buffer
	which is not otherwise filled up by characters from the
	source string) but it takes a counted c-string for the
	source rather than only a NUL-terminated string (the source
	c-string can also be NUL-terminated).  The arguments to
	this are also different than from |strncpy(3c)|.  It also
	returns a pointer to the end of the filled in (non-NUL)
	part of the destination character buffer (written to) rather
	than to the beginning of it.  No NUL character is placed
	at the end (overlast-end) of the destination string, so the
	resuling c-string may not be NUL-terminated.

	Synopsis:
	char *strnwcpy(char *dp,int dl,cchar *sp,int sl) noex

	Arguments:
	dp		destination character buffer pointer
	dl		destination character buffer length
	sp		source c-string pointer
	sl		source c-string length

	Returns:
	-		pointer to the end of the filled in part
			of the created destination string

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>		/* |stpncpy(3c)| + |memset(3c)| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<strwcpy.h>
#include	<localmisc.h>

#include	"strn.h"


/* local defines */

#ifndef	CF_STPNCPY
#define	CF_STPNCPY	1		/* use |stpncpy(3c)| */
#endif


/* imported namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */

static inline char *dstcpy(char *,cc *,int) noex ;

static char *dstncpy(char *dp,int dl,cc *sp,int sl) noex {
    	char	*rp = dstcpy(dp,sp,sl) ;
	if (int fl ; (fl = ((dp + dl) - rp)) > 0) {
	    memset(rp,0,fl) ;
	}
	return rp ;
}


/* local variables */

constexpr bool		f_stpncpy = CF_STPNCPY ;


/* exported variables */


/* exported subroutines */

char *strnwcpy(char *dp,int dl,cchar *sp,int sl) noex {
	char		*rp = dp ;
	if (dp && sp) {
	    if (dl >= 0) {
	        if (sl >= 0) {
		    if (sl >= dl) {
		        rp = dstncpy(dp,dl,sp,dl) ;
		    } else {
		        rp = dstncpy(dp,dl,sp,sl) ;
		    }
	        } else {
		    rp = dstncpy(dp,dl,sp,dl) ;
	        }
	    } else {
	        rp = dstcpy(dp,sp,sl) ;
	    }
	} /* end if (non-null) */
	return rp ;
}
/* end subroutine (strnwcpy) */


/* local subroutines */

static char *dstcpy(char *dp,cc *sp,int sl) noex {
	if_constexpr (f_stpncpy) {
	    dp = stpncpy(dp,sp,sl) ;
	} else {
    	    while (sl-- && *sp) {
	        *dp++ = *sp++ ;
	    }
	} /* end if_constexpr (f_stpncpy) */
    	return dp ;
}


