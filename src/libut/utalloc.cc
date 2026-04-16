/* utalloc SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* UNIX® XTI subroutine */
/* XTI allocate */
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


/* local namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */

local int	std_talloc(int,int,int,void **) noex ;


/* local variables */


/* exported variables */


/* exported subroutines */

int ut_alloc(int fd,int stype,int fields,void **rpp) noex {
	int		rs = SR_FAULT ;
	if (rpp) {
	    rs = SR_INVALID ;
	    if (fd >= 0) {
		void *p ;
		bool fexit = false ;
		repeat {
		    if ((rs = std_talloc(fd,stype,fields,&p)) < 0) {
	                switch (rs) {
	                case SR_NOMEM:
	                case SR_NOSR:
	                    msleep(1000) ;
		            falldown ;
	                case SR_INTR:
	                case SR_AGAIN:
	                    fexit = true ;
			    break ;
	                } /* end switch */
	            } /* end if */
		} until ((rs >= 0) || fexit) ;
	        *rpp = (rs >= 0) ? p : nullptr ;
	    } /* end if (valid) */
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (ut_alloc) */


/* local subroutines */

local int std_talloc(int fd,int stype,int fields,void **pp) noex {
    	int		rs = SR_OK ;
	void *p ;
	if ((p = xti_alloc(fd,stype,fields)) == nullptr) {
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
	*pp = (rs >= 0) ? p : nullptr ;
	return rs ;
} /* end subroutine (std_talloc) */


