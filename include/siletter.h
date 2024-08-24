/* siletter HEADER */
/* lang=C20 */

/* perform some kind of processsing */
/* version %I% last-modified %G% */


/* revision history:

	= 2009-04-01, David A­D­ Morano
	This subroutine was written as an enhancement for adding
	back-matter (end pages) to the output document.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	SILETTER_INCLUDE
#define	SILETTER_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


#define	SILETTER_RES	struct siletter_result 


struct siletter_result {
	cchar		*lp ;
	int		ll ;
} ;

typedef SILETTER_RES	siletter_res ;

EXTERNC_begin

extern int	siletter(siletter_res *,cchar *,int) noex ;

EXTERNC_end


#endif /* SILETTER_INCLUDE */


