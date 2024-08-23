/* timecount HEADER */
/* lang=C++20 */

/* count-down timer */
/* version %I% last-modified %G% */


/* revision history:

	= 2001-04-11, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

	= 2011-02-23, David A­D­ Morano
	I updated this to be able to accept lambdas (w/ C++11)

*/

/* Copyright © 2001,2011 David D-A- Morano.  All rights reserved. */

/*******************************************************************************

	This object provides a glorified count-down timer.

*******************************************************************************/

#ifndef	TIMECOUNT_INCLUDE
#define	TIMECOUNT_INCLUDE
#ifdef	__cplusplus


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


#ifndef	POLL_INTMULT
#define	POLL_INTMULT	1000
#endif


class timecount {
	int		to ;		/* milliseconds */
public:
	timecount(int a) : to(a * POLL_INTMULT) { } ;
	timecount(const timecount &) = delete ;
	timecount &operator = (const timecount &) = delete ;
	operator int () noex ;
} ; /* end class (timecount) */


#endif /* __cplusplus */
#endif /* TIMECOUNT_INCLUDE */


