/* lgcd SUPPORT */
/* lang=C++20 */

/* (long) integer Greastest Common Divisor (GCD) */
/* version %I% last-modified %G% */


/* revision history:

	= 2004-03-01, David A­D­ Morano
	This subroutine was originally written.  

*/

/* Copyright © 2004 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	igcd

	Description:
	This subroutine calculates the Greastest Common Divisor
	(GCD) of two integer numbers.

	Synopsis:
	long igcd(int a,int b) noex

	Arguments:
	a	number
	b	number

	Returns:
	-	GCD(a,b)

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<localmisc.h>


/* local defines */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported subroutines */

long lgcd(long a,long b) noex {
	long		r ;
	while ((r = (a % b)) > 0) {
	    a = b ;
	    b = r ;
	} /* end while */
	return b ;
}
/* end subroutine (lgcd) */


