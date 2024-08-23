/* ucpts HEADER */
/* lang=C20 */

/* auxillary operating system support */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

	= 2017-08-01, David A­D­ Morano
	Updated for lack of interfaces in MacOS Darwin

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This file contains the UNIX® system subroutines for
	pseudo-terminal slave management.  These subroutines
	first appeared in UNIX® System V Release 3 (SVR3).

*******************************************************************************/

#ifndef	UCPTS_INCLUDE
#define	UCPTS_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>


EXTERNC_begin

extern int uc_ptsname(int,char *,int) noex ;
extern int uc_ptsgrant(int) noex ;
extern int uc_ptsunlock(int) noex ;

EXTERNC_end


#endif /* UCPTS_INCLUDE */


