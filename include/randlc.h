/* randlc HEADER */
/* lang=C20 */

/* implement Linear-Congruential random-number generator (RNG) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	RANDLC_INCLUDE
#define	RANDLC_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern int	randlc(int) noex ;

EXTERNC_end


#endif /* RANDLC_INCLUDE */


