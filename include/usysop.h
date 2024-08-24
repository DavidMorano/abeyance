/* usysop HEADER (UNIX® system operations) */
/* lang=C20 */

/* translation layer interface for UNIX® equivalents */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services
	(RNS).

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Names:

	Description:
	These subroutines mange the operating system itself.

*******************************************************************************/

#ifndef	USYSOP_INCLUDE
#define	USYSOP_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/types.h>		/* system types */
#include	<sys/time.h>		/* |adjtime(2)| */
#include	<unistd.h>
#include	<time.h>		/* |time(2)| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usupport.h>


EXTERNC_begin

extern int u_adjtime(CTIMEVAL *tvp,TIMEVAL *ovp) noex ;
extern int u_stime(time_t *tp) noex ;
extern int u_time(time_t *rp) noex ;

EXTERNC_end


#endif /* USYSOP_INCLUDE */


