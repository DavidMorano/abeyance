/* main SUPPORT (machostid) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* get the various IDs from the system */
/* version %I% last-modified %G% */


/* revision history:

	= 1988-01-10, David A­D­ Morano
	This subroutine was written (originally) as a test of the
	Sun Solaris® UNIX® 'kstat' facility.  But now it just prints
	the machine ID.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/************************************************************************

  	Name:
	main

	Description:
	Get the host-IDs from the system.

***************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<unistd.h>		/* POXIX <- for |gethostid(3c)| */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstring>		/* CSTD */
#include	<iostream>		/* C++STD |cout(3c++)| */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU |eol(3u)| */


/* local defines */


/* imported namespaces */

using std::cout ;			/* variable */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int main(int,mainv,mainv) {
	ulong	id = gethostid() ;
	cout << id << eol ;
}
/* end subroutine (main) */


