/* strnwcpyxc SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* copy a counted c-string to a sized destination buffer */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	strnwcpyxc

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
	char *strnwcpy{x}c(char *dp,int dl,cchar *sp,int sl) noex

	Arguments:
	{x}		Base, Lower, Upper, Fold
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
#include	<cstring>		/* |memset(3c)| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<toxc.h>
#include	<localmisc.h>

#include	"strnwcpyxc.h"


/* local defines */


/* imported namespaces */


/* local typedefs */

extern "C" {
    typedef int (*toxc_f)(int) noex ;
}


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */

static char *strnwcpyxc(toxc_f toxc,char *dp,int dl,cchar *sp,int sl) noex {
	if (dp && sp) {
    	    while (dl && sl-- && *sp) {
	        *dp++ = toxc(*sp++) ;
		dl -= 1 ;
	    }
	    if (dl > 0) {
	        memset(dp,0,dl) ;
	    }
	} /* end if (non-null) */
	return dp ;
}
/* end subroutine (strnwcpyxc) */


/* local variables */


/* exported variables */


/* exported subroutines */

char *strnwcpybc(char *dp,int dl,cchar *sp,int sl) noex {
    	return strnwcpyxc(tobc,dp,dl,sp,sl) ;
}

char *strnwcpylc(char *dp,int dl,cchar *sp,int sl) noex {
    	return strnwcpyxc(tolc,dp,dl,sp,sl) ;
}

char *strnwcpyuc(char *dp,int dl,cchar *sp,int sl) noex {
    	return strnwcpyxc(touc,dp,dl,sp,sl) ;
}

char *strnwcpyfc(char *dp,int dl,cchar *sp,int sl) noex {
    	return strnwcpyxc(tofc,dp,dl,sp,sl) ;
}


/* local subroutines */


