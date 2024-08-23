/* ucgetloadavg HEADER */
/* lang=C20 */

/* version %I% last-modified %G% */
/* auxillary operating system support */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

	= 2017-08-01, David A­D­ Morano
	Updated for lack of interfaces in MacOS Darwin

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This file contains the UNIX system types that the brain-damaged
	MacOS operating system does NOT have.  We are trying in a
	very small way to make up for some of the immense brain-damage
	within the Apple Darwin operating system.

*******************************************************************************/

#ifndef	UCGETLOADAVG_INCLUDE
#define	UCGETLOADAVG_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>


EXTERNC_begin

extern int	uc_getloadavg(double *,int) noex ;

EXTERNC_end


#endif /* UCGETLOADAVG_INCLUDE */


