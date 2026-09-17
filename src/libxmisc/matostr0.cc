/* matostr SUPPORT */
/* lang=C++20 */

/* Match-Option-String */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-12-01, David A­D­ Morano
	Module was originally written.

*/

/* Copyright (c) 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	mato{x}str

	Description:
	Check that the given string matches a MINIMUM number of
	leading characters for some string in the given array of
	strings.  If we get a match, we return the array index.  If
	we do not match, we return "less-than-zero".

	Synopsis:
	int mato{x}str(cchar *const *a,int n,cchar *sp,int sl) noex

	Arguments:
	a		array of string to match against
	n		minimum number of characters that must match
	sp		string to test against array
	sl		length of test string

	Returns:
	>=0		index of match in array
	<0		no match found (not further distinguished)


	Name:
	matocasestr

	Description:
	Check that the given string case-insensitively matches a
	MINIMUM number of leading characters for some string in the
	given array of strings.  If we get a match, we return the
	array index.  If we do not match, we return "less-than-zero".

	Synopsis:
	int matocasestr(cchar **a,int n,cchar *sp,int sl) noex

	Arguments:
	a		array of string to match against
	n		minimum number of characters that must match
	sp		string to test against array
	sl		length of test string

	Returns:
	>=0		index of match in array
	<0		no match found (not further distinguished)


	Notes:
	1. Rationale for using templates rather than passing a 
	function-pointer:
	The thinking is that I want the template instantiation to
	"see" any inlined subroutine and optimize it all out rather
	than being forced to actually call a subroutine (if only a
	pointer was supplied). Anywat, that was the thinking, even
	if misguided. Also note that this goes against one of the
	major coding standard rules which is: to optimize for space
	rather than time (without the compiler doing that operation
	itself).

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstring>		/* |strlen(3c)| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<toxc.h>
#include	<nleadstr.h>
#include	<localmisc.h>

#include	"matostr.h"


/* local defines */


/* imported namespaces */


/* local typedefs */

typedef int (*toxc_f)(int) noex ;
typedef int (*nleadxstr_f)(cchar *,cchar *,int) noex ;


/* external subroutines */


/* external variables */


/* forward references */


/* local variables */


/* subroutine-templates */

template<toxc_f toxc,nleadxstr_f nleadxstr>
int matoxstr(mainv a,int n,cchar *sp,int sl) noex {
	cint		lch = toxc(sp[0]) ;
	int		i ;
	int		m ;
	if (sl < 0) sl = strlen(sp) ;
	for (i = 0 ; a[i] ; i += 1) {
	    cchar	*ap = a[i] ;
	    if ((m = (lch == toxc(ap[0]))) > 0) {
	        m = nleadxstr(ap,sp,sl) ;
	    }
	    if ((m == sl) && ((m >= n) || (ap[m] == '\0'))) {
		break ; 
	    }
	} /* end for */
	return (a[i]) ? i : -1 ;
}
/* end subroutine-template (matoxstr) */


/* exported variables */


/* exported subroutines */

int matobasestr(mainv a,int n,cchar *sp,int sl) noex {
	return matoxstr<tobc,nleadbasestr>(a,n,sp,sl) ;
}
/* end subroutine (matobasestr) */

int matocasestr(mainv a,int n,cchar *sp,int sl) noex {
	return matoxstr<tolc,nleadcasestr>(a,n,sp,sl) ;
}
/* end subroutine (matocasestr) */

int matofoldstr(mainv a,int n,cchar *sp,int sl) noex {
	return matoxstr<tofc,nleadfoldstr>(a,n,sp,sl) ;
}
/* end subroutine (matofoldstr) */


