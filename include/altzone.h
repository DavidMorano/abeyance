/* altzone HEADER */
/* lang=C20 */

/* deal with bad declaration of the |altzone| global variable */
/* version %I% last-modified %G% */


/* revision history:

	- 2008-10-01, David A­D­ Morano
	This object module was originally written.

*/

/* Copyright © 2008 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Finally, note that SlowLaris has a 'define' bug in that it
	does not declare the 'altzone' variable unless some other
	defines are made (see the code). It is not clear if and
	when this will be or has been fixed.  This subroutine does
	not currently use the 'altzone' variable anyway.

*******************************************************************************/

#ifndef	ALTZONE_INCLUDE
#define	ALTZONE_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<time.h>


#if	(defined(OSNAME_SunOS) && (OSNAME_SunOS > 0))

#define	A	(__STDC__ != 0) 
#define	B	defined(_POSIX_C_SOURCE) 
#define	C	defined(_XOPEN_SOURCE)
#if	(A != 0) || (B != 0) || (C != 0)
extern long	altzone ;
#endif

#elif	(defined(OSNAME_Darwin) && (OSNAME_Darwin > 0))

extern long	altzone ;		/* reminder: does not actually exist */

#endif /* (defined(OSNAME_SunOS) && (OSNAME_SunOS > 0)) */


#endif /* ALTZONE_INCLUDE */


