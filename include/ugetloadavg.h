/* ugetloadavg HEADER */
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

#ifndef	UGETLOADAVG_INCLUDE
#define	UGETLOADAVG_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


#ifndef	LOADAVG_NSTATS
#define LOADAVG_NSTATS		3	/* maximum load-averages available */
#endif


#ifdef	__cplusplus
namespace libu {
    extern int	dloadavg(double *,int) noex ;
}
#endif /* __cplusplus */

EXTERNC_begin
extern int	u_getloadavg(uint *,int) noex ;
EXTERNC_end


#endif /* UGETLOADAVG_INCLUDE */


