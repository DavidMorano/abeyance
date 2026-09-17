/* matcasesubstr SUPPORT */
/* lang=C++20 */

/* match a string case-insensitively */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-12-01, David A­D­ Morano
	Module was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	matcasesubstr

	Description:
	Check is the given substring is amoung the array of strings
	given (case insensitively).

	Synopsis:
	int matcasesubstr(mainv a,cchar *sp,int sl) noex

	Arguments:
	a		array of string to match against
	sp		string to test against array
	sl		length of test string

	Returns:
	>=0		index of match in array
	<0		no match found (not further distinguished)

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<six.h>
#include	<localmisc.h>

#include	"matxstr.h"


/* local defines */


/* external subroutines */


/* external variables */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int matcasesubstr(mainv a,cchar *sp,int sl) noex {
	int		i = 0 ;
	for (i = 0 ; a[i] ; i += 1) {
	    if (sicasesub(sp,sl,a[i]) >= 0) break ;
	} /* end for */
	return (a[i] != nullptr) ? i : -1 ;
}
/* end subroutine (matcasesubstr) */


