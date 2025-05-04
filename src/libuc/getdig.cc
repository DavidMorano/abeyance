/* getdig SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 */

/* create a digit from a value */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-14, David A­D­ Morano
	This little object module was first written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	getdig

	Description:
	Given a value we return a character digit (anything from
	base-2 up to base-64) corresponding to that value.

	Synopsis:
	int getdig(int v) noex 

	Argument:
	v		value that we want the corresponding digit for

	Returns:
	-		the value of the digit requested
	-1		error (argument is out-of-domain)

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>		/* <- |strlen(3c)| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<libutil.hh>		/* |xstrlen(3u)| */
#include	<localmisc.h>

#include	"getdig.h"


import uvariables ;

/* local defines */


/* imported namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */

static cint	maxbase = xstrlen(sysword.w_digtab) ;


/* exported variables */


/* exported subroutines */

int getdig(int v) noex {
	int		dig = -1 ;
	if ((v >= 0) && (v < maxbase)) {
	    dig = sysword.w_digtab[v] ;
	}
	return dig ;
}
/* end subroutine (getdig) */


