/* si{x}sub SUPPORT */
/* lang=C++20 */

/* find the string-index of a sub-stringin the given c-string */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-23, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	si{x}sub

	Description:
	This subroutine determines if the parameter string (argument
	'ss') is or is not in the buffer specified by the first two
	arguments.  This subroutine either returns (-1) or it returns
	the character position in the buffer of where the string
	starts.

	Synopsis:
	int si{x}sub(cchar *sp,int sl,cchar *ss) noex

	Arguments:
	sp	string to be examined
	sl	length of string to be examined
	ss	null terminated substring to search for

	Returns:
	>=0	index of found substring
	<0	substring not found

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>		/* <- for |strlen(3c)| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<ascii.h>
#include	<toxc.h>
#include	<nleadstr.h>
#include	<localmisc.h>

#include	"six.h"


/* local defines */


/* external subroutines */


/* exported variables */


/* exported subroutines */

int sibasesub(cchar *sp,int sl,cchar *ss) noex {
	cint		sslen = strlen(ss) ;
	int		i{} ; /* used-afterwards */
	bool		f = false ;
	if (sl < 0) sl = strlen(sp) ;
	if (sslen <= sl) {
	    int		m ;
	    for (i = 0 ; i <= (sl-sslen) ; i += 1) {
		f = ((sslen == 0) || (sp[i] == ss[0])) ;
		if (f) {
	     	    m = nleadstr((sp+i),ss,sslen) ;
	     	    f = (m == sslen) ;
		}
	        if (f) break ;
	    } /* end for */
	} /* end if (possible) */
	return (f) ? i : -1 ;
}
/* end subroutine (sibasesub) */

int sicasesub(cchar *sp,int sl,cchar *ss) noex {
	cint		sslen = strlen(ss) ;
	int		i = 0 ;
	bool		f = false ;
	if (sl < 0) sl = strlen(sp) ;
	if (sslen <= sl) {
	    cint	sslead = tofc(ss[0]) ;
	    int		m ;
	    for (i = 0 ; i <= (sl-sslen) ; i += 1) {
		f = ((sslen == 0) || (tofc(sp[i]) == sslead)) ;
		if (f) {
	            m = nleadcasestr((sp+i),ss,sslen) ;
	            f = (m == sslen) ;
		}
	        if (f) break ;
	    } /* end for */
	} /* end if (possible) */
	return (f) ? i : -1 ;
}
/* end subroutine (sicasesub) */

int sifoldsub(cchar *sp,int sl,cchar *ss) noex {
	cint		sslen = strlen(ss) ;
	int		i = 0 ;
	bool		f = false ;
	if (sl < 0) sl = strlen(sp) ;
	if (sslen <= sl) {
	    cint	sslead = tofc(ss[0]) ;
	    int		m ;
	    for (i = 0 ; i <= (sl-sslen) ; i += 1) {
		f = ((sslen == 0) || (tofc(sp[i]) == sslead)) ;
		if (f) {
	            m = nleadfoldstr((sp+i),ss,sslen) ;
	            f = (m == sslen) ;
		}
	        if (f) break ;
	    } /* end for */
	} /* end if (possible) */
	return (f) ? i : -1 ;
}
/* end subroutine (sifoldsub) */


