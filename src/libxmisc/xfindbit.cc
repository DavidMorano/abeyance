/* xfindbit SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* find bits (meeting certain criteria) */
/* version %I% last-modified %G% */


/* revision history:

	= 1999-03-09, David A­D­ Morano
	This group of subroutines was originally written here in C
	language but were inspired by single instructions on the
	VAX (Digital Equipment 1979) that did essentially the same
	functions.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/******************************************************************************

  	Group:
	zfindbit

	Description:
	Find bits that meet a certain criteria in an integer.

	xffbs[il]	find first bit set
	xffbc[il]	find first bit clear
	xflbs[il]	find last bit set
	xflbc[il]	find last bit clear

******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<climits>		/* CSTD */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */


/* local defines */


/* local namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int xffbsi(uint v) noex {
	cint	n = (szof(uint) * CHAR_BIT) ;
	int	i ;
	for (i = 0 ; i < n ; i += 1) {
	    if (v & 1) break ;
	    v = v >> 1 ;
	} /* end for */
	return (i < n) ? i : -1 ;
} /* end subroutine (xffbsi) */

int xffbci(uint v) noex {
	cint	n = (szof(uint) * CHAR_BIT) ;
	int	i ;
	for (i = 0 ; i < n ; i += 1) {
	    if (! (v & 1)) break ;
	    v = v >> 1 ;
	} /* end for */
	return (i < n) ? i : -1 ;
} /* end subroutine (xffbci) */

int xffbsl(ulong v) noex {
	cint	n = (szof(ulong) * CHAR_BIT) ;
	int	i ;
	for (i = 0 ; i < n ; i += 1) {
	    if (v & 1) break ;
	    v = v >> 1 ;
	} /* end for */
	return (i < n) ? i : -1 ;
} /* end subroutine (xffbsl) */

/* find first bit clear in LONG */
int xffbcl(ulong v) noex {
	cint	n = (szof(ulong) * CHAR_BIT) ;
	int	i ;
	for (i = 0 ; i < n ; i += 1) {
	    if (! (v & 1)) break ;
	    v = v >> 1 ;
	} /* end for */
	return (i < n) ? i : -1 ;
} /* end subroutine (xffbcl) */

/* find last bit set in integer */
int xflbsi(uint v) noex {
	cint	n = (szof(uint) * CHAR_BIT) ;
	int	i ;
	for (i = (n-1) ; i >= 0 ; i -= 1) {
	    if ((v >> i) & 1) break ;
	} /* end for */
	return (i >= 0) ? i : -1 ;
} /* end subroutine (xflbsi) */

/* find last bit clear in integer */
int xflbci(uint v) noex {
	cint	n = (szof(uint) * CHAR_BIT) ;
	int	i ;
	for (i = (n-1) ; i >= 0 ; i -= 1) {
	    if (! ((v >> i) & 1)) break ;
	} /* end for */
	return (i >= 0) ? i : -1 ;
} /* end subroutine (xflbci) */

/* find last bit set in LONG */
int xflbsl(ulong v) noex {
	cint	n = (szof(ulong) * CHAR_BIT) ;
	int	i ;
	for (i = (n-1) ; i >= 0 ; i -= 1) {
	    if ((v >> i) & 1) break ;
	} /* end for */
	return (i >= 0) ? i : -1 ;
}
/* end subroutine (xflbsl) */

/* find last bit clear in LONG */
int xflbcl(ulong v) noex {
	cint	n = (szof(ulong) * CHAR_BIT) ;
	int	i ;
	for (i = (n - 1) ; i >= 0 ; i -= 1) {
	    if (! ((v >> i) & 1)) break ;
	} /* end for */
	return (i >= 0) ? i : -1 ;
} /* end subroutine (xflbcl) */

/* find the number of set bits in an *integer* */
int xfbscounti(uint v) noex {
	cint	n = (szof(uint) * CHAR_BIT) ;
	int	c = 0 ;
	for (int i = 0 ; i < n ; i += 1) {
	    if (v & 1) c += 1 ;
	    v = v >> 1 ;
	} /* end for */
	return c ;
} /* end subroutine (xfbscounti) */

/* find the number of set bits in an *LONG* (64 bits) */
int xfbscountl(ulong v) noex {
	cint	n = (szof(ulong) * CHAR_BIT) ;
	int	c = 0 ;
	for (int i = 0 ; i < n ; i += 1) {
	    if (v & 1) c += 1 ;
	    v = v >> 1 ;
	} /* end for */
	return c ;
} /* end subroutine (xfbscountl) */


