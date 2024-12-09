/* mtime SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 */

/* Millisecond Time */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Name:
	umtime

	Description:
	Sort of like |time(2)| but returns milliseconds rather than
	seconds.  Unlike |time(2)|, this subroutine takes no
	arguments.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>

#include	"mtime.h"


/* local defines */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported varaibles */

usys_mtime	getmtime ;
usys_mtime	mtime ;


/* exported subroutines */

mtime_t umtime(void) noex {
	mtime_t		t ;
	mtime_t		m = 0 ;
	if (TIMEVAL tv ; gettimeofday(&tv,nullptr) >= 0) {
	    t = tv.tv_sec ;
	    m += (t*1000) ;
	    m += (tv.tv_usec / 1000) ;
	} else {
	    const time_t	ut = time(nullptr) ; /* good until 2038! */
	    t = mtime_t(ut) ;
	    m += (t * 1000) ;
	}
	return m ;
}
/* end subroutine (umtime) */


