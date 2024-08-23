/* usys_gethrtime HEADER */
/* lang=C20 */

/* miscelllaneous (XXX) operating system support */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This file contains the UNIX® system types that the brain-damaged
	MacOS operating system does NOT have.  We are trying in a very
	small way to make up for some of the immense brain-damage within
	the Apple Darwin operating system.

*******************************************************************************/

#ifndef	USYSGETHRTIME_INCLUDE
#define	USYSGETHRTIME_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/time.h>		/* <- |gethrtime(3c)| */
#include	<time.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


/* GETHRTIME begin */
#if	defined(SYSHAS_GETHRTIME) && (SYSHAS_GETHRTIME > 0)

/* » nothing needed « */

#else /* defined(SYSHAS_GETHRTIME) && (SYSHAS_GETHRTIME > 0) */

#ifndef	TYPEDEF_HRTIME
#define	TYPEDEF_HRTIME

typedef unsigned long		hrtime_t ;

#endif /* TYPEDEF_HRTIME */

#ifndef	SUBROUTINE_GETHRTIME
#define	SUBROUTINE_GETHRTIME
EXTERNC_begin

extern hrtime_t gethrtime() noex ;

EXTERNC_end
#endif /* SUBROUTINE_GETHRTIME */

#endif /* defined(SYSHAS_GETHRTIME) && (SYSHAS_GETHRTIME > 0) */
/* GETHRTIME end */


#endif /* USYSGETHRTIME_INCLUDE */


