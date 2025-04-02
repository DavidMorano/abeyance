/* ut_alloc SUPPORT */
/* lang=C++20 */

/* UNIX® XTI subroutine */
/* XTI allocate */


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

int ut_alloc(int fd,int stype,int fields,void **rpp) noex {
	int		rs = SR_OK ;
	void		*p ;

	if (rpp == NULL) return SR_FAULT ;

again:
	p = t_alloc(fd,stype,fields) ;

	if (p == NULL) {
	    switch (t_errno) {
	    case TBADF:
	        rs = SR_NOTSOCK ;
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
		fallthrough ;
		/* FALLTHROUGH */
	    case SR_INTR:
	    case SR_AGAIN:
	        goto again ;
	    } /* end switch */
	} /* end if */

	*rpp = (rs >= 0) ? p : NULL ;

	return rs ;
}
/* end subroutine (ut_alloc) */


