/* strfieldcmp SUPPORT */
/* lang=C++20 */

/* string field comparisons */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-12-12, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	strfieldcmp

	Description:
	These subroutines are used to compare fields of a string
	(like an environment variables type of string 'HOME=/here').
	Fields that can be compared are:

		key
		value

	Synopses:
	int strnkeycmp(cchar *s,cchar *kp,int kl) noex
	int strnvaluecmp(cchar *sp,cchar *vp,int vl) noex

*******************************************************************************/

#include	<envstandards.h>
#include	<sys/types.h>
#include	<sys/param.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<localmisc.h>

#include	"strfieldcmp.h"


/* local defines */


/* external subroutines */


/* external variables */


/* exported subroutines */

int strnkeycmp(cchar *s,cchar *kp,int kl) noex {
	int		rc = -1 ;
	if (kl < 0) kl = strlen(kp) ;
	if ((strncmp(s,kp,kl) == 0) && (s[kl] == '=')) {
	    rc = 0 ;
	}
	return rc ;
}
/* end subroutine (strnkeycmp) */

int strnvaluecmp(cchar *sp,cchar *vp,int vl) noex {
	int		rc = -1 ;
	if (vl < 0) vl = strlen(vp) ;
	if (cchar *tp ; (tp = strchr(sp,'=')) != NULL) {
	    sp = (tp+1) ;
	    while (*sp) {
	        if ((strncmp(sp,vp,vl) == 0) &&
	            ((sp[vl] == '\0') || (sp[vl] == ':'))) {
		    rc = 0 ;
		}
	        if ((tp = strchr(sp,':')) == NULL) break ;
	        sp = (tp+1) ;
		if (rc == 0) break ;
	    } /* end while */
	} /* end if */
	return rc ;
}
/* end subroutine (strnvaluecmp) */


