/* uc_gettimeofday */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* interface component for UNIX® library-3c */
/* get the current time of day */


/* revision history:

	= 1998-04-13, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Name:
	uc_gettimeofday

	Description:
	This routine calls the system's (library) 'gettimeofday'
	subroutine.

	Synopsis:
	int uc_gettimeofday(struct timeval *tvp,void *np) noex
	
	Arguments:
	tvp		pointer to TIMEVAL object to hold result
	np		NULL pointer (currently required)

	Returns:
	>=0		success
	<0		failure and this is the error code

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/time.h>
#include	<cerrno>
#include	<unistd.h>
#include	<usystem.h>
#include	<localmisc.h>


/* external subroutines */


/* exported subroutines */

int uc_gettimeofday(struct timeval *tvp,void *dp) noex {
	int		rs = SR_FAULT ;
	if (tvp) {
	    rs = SR_OK ;
	    if (gettimeofday(tvp,dp) == -1) rs = (- errno) ;
	}
	return rs ;
}
/* end subroutine (uc_gettimeofday) */


