/* usys_stime HEADER */
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

#ifndef	USYSSTIME_INCLUDE
#define	USYSSTIME_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/time.h>		/* for all others |gettimeofday(3c)| */
#include	<unistd.h>		/* for Solaris® */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>

/* GETRANDOM begin */
#if	defined(SYSHAS_GETRANDOM) && (SYSHAS_GETRANDOM > 0)

/* SunOS (Solaris®) already has the |stime(2)| system call */

#else /* defined(SYSHAS_GETRANDOM) && (SYSHAS_GETRANDOM > 0) */

#ifndef	SUBROUTINE_STIME
#define	SUBROUTINE_STIME
EXTERNC_begin

extern unixret_t stime(const time_t *) noex ;

EXTERNC_end
#endif /* SUBROUTINE_STIME */


#endif /* defined(SYSHAS_GETRANDOM) && (SYSHAS_GETRANDOM > 0) */
/* GETRANDOM end */


#endif /* USYSSTIME_INCLUDE */


