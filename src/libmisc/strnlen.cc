/* strnlen SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 */

/* calculate the length of a c-string */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-17, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	strnlen

	Description:
	This subroutine computes the length of a supplied string
	but will not examine the string for more than a specified
	length.

	Synopsis:
	int strnlen(cchar *s,int n) noex

	Arguments:
	s	string to be examined
	n	maximum length of string to be examined

	Returns:
	len	mimimum of length of string or 'n' above

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>		/* |strlen(3c)| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<localmisc.h>


/* local defines */


/* exported variables */


/* exported subroutines */

int strnlen(cchar *s,int n) noex {
	int	i = 0 ;
	if (s) {
	    if (n >= 0) {
	        for (i = 0 ; (i < n) && *s ; i += 1) {
	            s += 1 ;
	        }
	    } else {
	        i = strlen(s) ;
	    }
	} /* end if (non-null) */
	return i ;
}
/* end subroutine (strnlen) */


