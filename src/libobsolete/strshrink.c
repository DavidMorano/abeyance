/* strshrink SUPPORT */
/* lang=C++20 */

/* remove leading and trailing white space */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	strshrink

	Description:
	This subroutine ehrink returns a string that is the same
	as the originally specified one except with any leading and
	trailing white-space removed.  Note that this subroutine
	modifies the given (passed) string.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstring>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<char.h>
#include	<localmisc.h>


/* local defines */


/* local variables */


/* exported variables */


/* exported subroutines */

char *strshrink(char *s) noex {
	int		l ;
	while (CHAR_ISWHITE(*s)) {
	    s += 1 ;
	}
	l = strlen(s) ;
	while ((l > 0) && CHAR_ISWHITE(s[l-1])) {
	    l -= 1 ;
	}
	s[l] = '\0' ;
	return s ;
}
/* end subroutine (strshrink) */


