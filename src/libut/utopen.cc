/* utopen SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* UNIX® XTI subroutine */
/* XTI open */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<poll.h>
#include	<uxti.h>
#include	<cerrno>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<usupport.h>
#include	<localmisc.h>


/* local defines */

#ifndef	UTCALL
#define	UTCALL		struct t_call
#endif


/* external subroutines */


/* exported variables */


/* exported subroutines */

int ut_open(cchar *fname,int f,struct t_info *ip) noex {
	int		rs ;

again:
	rs = t_open(fname,f,ip) ;

	if (rs < 0) {
	    switch (t_errno) {
	    case TBADFLAG:
	        rs = SR_INVALID ;
		break ;
	    case TSYSERR:
	        rs = (- errno) ;
		break ;
	    } /* end switch */
	} /* end if */

	if (rs < 0) {
	    switch (rs) {
	    case SR_NOMEM:
	    case SR_NOSR:
	        msleep(1000) ;
/* FALLTHROUGH */
	    case SR_INTR:
	    case SR_AGAIN:
	        goto again ;
	    } /* end switch */
	} /* end if */

	return rs ;
}
/* end subroutine (ut_open) */


