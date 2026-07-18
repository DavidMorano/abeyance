/* checkonc HEADER (Check-ONC) */
/* charset=ISO8859-1 */
/* lang=C20 */

/* Check-ONC */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-24, David A­D­ Morano
	This subroutine was written as an enhancement for adding
	back-matter (end pages) to the output document.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	CHECKONC_INCLUDE
#define	CHECKONC_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


EXTERNC_begin

extern int	checkonc(cc *,cc *,cc *,cc *) noex ;

EXTERNC_end


#endif /* CHECKONC_INCLUDE */


