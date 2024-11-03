/* logtwo SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 */

/* calculate the log-base-2 of a number */
/* version %I% last-modified %G% */


/* revision history:

	= 2003-03-04, David A.D. Morano
	This was written from scratch.

*/

/* Copyright © 2003 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Name:
	log2

	Description:
	Find the log-base-2 of a number (v).

	Synopsis:
	double logtwo(double v) noex

	Arguments:
	v		number to take the log-base-2 of

	Returns:
	-		result

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<math.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<localmisc.h>

#include	"logtwo.h"


/* local defines */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

double logtwo(double v) noex {
	const double	n = log(v) ;
	const double	d = log(2.0) ;
	return (n/d) ;
}
/* end subroutine (logtwo) */


