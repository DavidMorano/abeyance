/* errtimer HEADER */
/* lang=C20 */

/* error-timer */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services (RNS).

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Names:
	errtimer

	Description:
	This object actually provides a counter for counting how
	many times it is called (after sleeping on each call).

*******************************************************************************/

#ifndef	ERRTIMER_INCLUDE
#define	ERRTIMER_INCLUDE
#ifdef	__cplusplus


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<clanguage.h>		
#include	<utypedefs.h>		/* |POLL_INTMULT| */
#include	<utypealiases.h>
#include	<usysrets.h>


struct errtimer ;

struct reterr {
	friend		errtimer ;
	int		rs = SR_OK ;
	bool		fexit = true ;
	reterr() = default ;
	reterr(int ars,bool afe) noex : rs(ars), fexit(afe) { } ;
	void operator () (int ars) noex {
	    rs = ars ;
	    fexit = (ars < 0) ;
	} ;
	void operator () (bool f = true) noex {
	    fexit = f ;
	} ;
	operator int () const noex {
	    return rs ;
	} ;
} ; /* end struct (reterr) */

struct errtimer {
	int		mto = 0 ;
	int		rs = SR_TIMEDOUT ;
	errtimer(cint ato = 0) noex {
	    mto = (ato * POLL_INTMULT) ;
	} ;
	void operator = (cint &ato) noex {
	    mto = (ato * POLL_INTMULT) ;
	} ;
	const reterr operator () (int) noex ;
	operator reterr () noex ;
} ; /* end struct (errtimer) */


#endif /* __cplusplus */
#endif /* ERRTIMER_INCLUDE */


