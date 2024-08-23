/* sysval HEADER */
/* lang=C++20 */

/* retrieve operating-system values */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Recommended usage within source code:
		#include	<sysval.hh>
		sysval	pagesize(sysval_ps) ;
		if ((rs = pagesize) >= 0) {
			* do something w/ value in 'rs' *
		}

	Notes:
	1. thread-safe
	2. process-wide
	3. values cached
	4. relatively volatile values have cache time-outs

*******************************************************************************/

#ifndef	SYSVAL_INCLUDE
#define	SYSVAL_INCLUDE
#ifdef	__cplusplus /* everything is C++ only */


#include	<envstandards.h>	/* ordered first to configure */
#include	<usystem.h>


enum sysvals {
	sysval_ps,		/* PageSize */
	sysval_mc,		/* MaxChild */
	sysval_mi,		/* MaxIovec */
	sysval_mg,		/* MaxGroups */
	sysval_mo,		/* MaxOpen */
	sysval_mp,		/* MaxPages (physical pages) */
	sysval_ct,		/* ClkTck */
	sysval_pc,		/* ProcessorsConfigured */
	sysval_po,		/* ProcessorsOnline */
	sysval_overlast
} ;

struct sysval {
	cint		name = -1 ;
	constexpr sysval(int n) noex : name(n) { } ; 
	sysval() = delete ;
	sysval &operator = (const sysval &) = delete ;
	operator int () noex ;
} ; /* end class (sysval) */


#endif	/* __cplusplus */
#endif /* SYSVAL_INCLUDE */


