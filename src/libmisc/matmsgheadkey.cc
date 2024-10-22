/* matmsg SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 */

/* match on a header-key name */
/* version %I% last-modified %G% */

#define	CF_SHORTENV	0		/* early return? */
#define	CF_SPACETAB	1		/* header whitespace is space-tab */

/* revision history:

	= 1998-11-01, David A­D­ Morano
	This file is a collection of some subroutines that were
	individually written in the past.  I think that I added the
	|matmsgstart()| subroutine for more general completeness.
	Existing applications figure out whether it is a message-start
	on their own right now.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/******************************************************************************

	Synopsis:
	int matmsgheadkey(cchar *sp,int sl,int *olp) noex

	Arguments:
	sp		string to test for header
	sl		length of input string
	olp		optional pointer to hold over-last index

	Returns:
	>=0		got a match
	<0		did not get a match

****************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<char.h>
#include	<vechand.h>
#include	<localmisc.h>


/* local defines */

#define	MAXHEADERLEN	1025
#define	SPACETAB(c)	(((c) == ' ') || ((c) == '\t'))

#if	CF_SPACETAB
#define	HEADERWHITE(c)	SPACETAB(c)
#else
#define	HEADERWHITE(c)	CHAR_ISWHITE(c)
#endif


/* external subroutines */

extern int	matcasestr(const char **,const char *,int) ;


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int matmsgheadkey(cchar *s,int slen,int *olp) noex {
	int		klen ;
	cchar		*sp = s ;

	if (slen < 0)
	    slen = strlen(s) ;

	if (slen < 2)
	    return -1 ;

	while ((slen > 0) && (! HEADERWHITE(*sp)) && (*sp != ':')) {
	    sp += 1 ;
	    slen -= 1 ;
	} /* end while */

	klen = (sp - s) ;
	while ((slen > 0) && HEADERWHITE(*sp)) {
	    sp += 1 ;
	    slen -= 1 ;
	}

	if (slen <= 0)
	    return -1 ;

	if (olp) {
	    *olp = (sp - s) + 1 ;
	}

	return (*sp == ':') ? klen : -1 ;
}
/* end subroutine (matmsgheadkey) */


