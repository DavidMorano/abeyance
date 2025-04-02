/* ut_look SUPPORT */
/* lang=C++20 */

/* UNIX® XTI subroutine */
/* XTI look */


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
#include	<xti.h>
#include	<errno.h>
#include	<usystem.h>


/* local defines */

#ifndef	UTCALL
#define	UTCALL		struct t_call
#endif


/* external subroutines */


/* exported variables */


/* exported subroutines */

int ut_look(int fd) noex {
	int		rs ;

again:
	rs = t_look(fd) ;

	if (rs < 0) {
	    switch (t_errno) {
	    case TBADF:
	        rs = SR_NOTSOCK ;
		break ;
	    case TPROTO:
	        rs = SR_PROTO;
		break ;
	    case TSYSERR:
	        rs = (- errno) ;
		break ;
	    default:
		rs = SR_NOANODE ;
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
/* end subroutine (ut_look) */


