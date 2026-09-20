/* strnkeycmp SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* string key comparison */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-09-10, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	strnkeycmp

	Description:
	This subroutine makes a comparison of the key of a string
	that looks like a SHELL variable assignment.  For example,
	consider the following compound string:
		A=the_dog_house
	The 'A' would be the key, and the part 'the_dog_house' is
	the value.

	Synopsis:
	int strnkeycmp(cchar *e1p,cchar *e2p,int n) noex

	Arguments:
	e1p		first string
	e2p		second string
	n		maximum number of characters to compare

	Returns:
	>0		the second key is greater than the first
	0		the keys of the strings are equal
	<0		the first key is less than the second

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<algorithm>		/* |min(3c++)| + |max(3c++)| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<mkchar.h>
#include	<localmisc.h>

#include	"strnxcmp.h"

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |lenstr(3u)| */

/* local defines */


/* imported namespaces */

using std::min ;			/* subroutine */
using std::max ;			/* subroutine */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

local inline bool isend(int ch) noex {
    	return (ch == '=') || (ch == '\0') ;
}

int strnkeycmp(cchar *e1p,cchar *e2p,int n) noex {
	int		rc = 0 ;
	if (e1p && e2p) {
	    if (n < 0) {
	        cint n1 = lenstr(e1p) ;
	        cint n2 = lenstr(e2p) ;
		n = min(n1,n2) ;
	    } /* end if */
	    {
	        for (int i = 0 ; (i < n) && *e1p && *e2p ; i += 1) {
	            if ((*e1p == '=') || (*e2p == '=')) break ;
	            if (*e1p != *e2p) break ;
	            e1p += 1 ;
	            e2p += 1 ;
	        } /* end for */
	        if ((*e1p != *e2p) && n) {
		    cint ch1 = mkchar(*e1p) ;
		    cint ch2 = mkchar(*e2p) ;
	            if (isend(ch1)) {
		        rc = isend(ch2) ? 0 : (- ch2) ;
	            } else if (isend(ch2)) {
		        rc = (+ ch1) ;
	            } else {
		        rc = ch1 - ch2 ;
		    }
	        } /* end if (resolution) */
	    } /* end block */
	} /* end if (non-null) */
	return rc ;
}
/* end subroutine (strnkeycmp) */

#ifdef	OBSOLETE

local inline int chdiff(cchar *c1p,cchar *c2p) noex {
    	cint ch1 = mkchar(*c1p) ;
    	cint ch2 = mkchar(*c2p) ;
	return (ch1 - ch2) ;
} /* end subroutine (chdiff) */

int strnkeycmp(cchar *e1p,cchar *e2p,int n) noex {
	int		rc = 0 ;
	if (e1p && e2p) {
            if (n >= 0) {
                while (*e1p && *e2p && (n > 0)) {
                    if ((*e1p == '=') || (*e2p == '=')) break ;
                    rc = chdiff(e1p,e2p) ;
                    if (rc != 0) break ;
                    e1p += 1 ;
                    e2p += 1 ;
                    n -= 1 ;
                } /* end while */
            } else {
                while (*e1p && *e2p) {
                    if ((*e1p == '=') || (*e2p == '=')) break ;
                    rc = chdiff(e1p,e2p) ;
                    if (rc != 0) break ;
                    e1p += 1 ;
                    e2p += 1 ;
                } /* end while */
            } /* end if */
            if ((rc == 0) && (n != 0)) {
                if (*e1p != *e2p) {
                    if ((rc == 0) && (*e1p == '=')) {
                        rc = (*e2p == '\0') ? 0 : -1 ;
                    }
                    if ((rc == 0) && (*e2p == '=')) {
                        rc = (*e1p == '\0') ? 0 : 1 ;
                    }
                    if (rc == 0) {
                        rc = chdiff(e1p,e2p) ;
                    }
                } /* end if */
            } /* end if (still non-zero) */
 	} /* end if (at least one non-null) */
	return rc ;
}
/* end subroutine (strnkeycmp) */

#endif /* OBSOLETE */


