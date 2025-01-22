/* stpcpyxc SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 */

/* copy a c-string to destination buffer w/ a case conversion */
/* version %I% last-modified %G% */

#define	CF_STPCPY	1		/* use |stpcpy(3c)| */

/* revision history:

	= 1998-11-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Names:
	stpcpybc
	stpcpylc
	stpcpyuc
	stpcpyfc

	Description:
	These subroutines copy a source c-string to a (uncounted)
	destination while converting the case of the characters
	(according to which subroutine is called).

	Synopsis:
	rp = *stpcpy{x}c(char *dst,cchar *src) noex

	Arguments:
	dst	destination result buffer (pointer)
	src	source c-string pointer
	rp	result pointer (pointing to resulting NUL character in 'dst'

	Returns:
	-	a pointer to the NUL character in the destination buffer

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<cstring>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<toxc.h>
#include	<localmisc.h>

#include	"stpcpyxc.h"


/* local defines */

#ifndef	CF_STPCPY
#define	CF_STPCPY	1		/* use |stpcpy(3c)| */
#endif


/* imported namespaces */


/* local typedefs */

extern "C" {
    typedef int (*toxc_f)(int) noex ;
}


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */

static char *stpcpyxc(toxc_f toxc,char *dp,cchar *sp) noex {
	while (*sp) {
	    *dp++ = toxc(*sp++) ;
	} /* end while */
	*dp = '\0' ;
	return dp ;
}
/* end subroutine (stpcpyxc) */


/* local variables */

constexpr bool		f_stpcpy = CF_STPCPY ;


/* exported variables */


/* exported subroutines */

char *stpcpybc(char *dp,cchar *sp) noex {
	char		*rp ;
	if_constexpr (f_stpcpy) {
	    rp = stpcpy(dp,sp) ;
	} else {
	    rp = stpcpyxc(tobc,dp,sp) ;
	}
	return rp ;
}

char *stpcpylc(char *dp,cchar *sp) noex {
	return stpcpyxc(tolc,dp,sp) ;
}

char *stpcpyuc(char *dp,cchar *sp) noex {
	return stpcpyxc(touc,dp,sp) ;
}

char *stpcpyfc(char *dp,cchar *sp) noex {
	return stpcpyxc(tofc,dp,sp) ;
}


