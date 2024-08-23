/* usys_getrandom HEADER */
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

#ifndef	USYSGETRANDOM_INCLUDE
#define	USYSGETRANDOM_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */

/* GETRANDOM begin */
#if	(!defined(SYSHAS_GETRANDOM)) || (SYSHAS_GETRANDOM == 0)


#include	<sys/random.h>		/* |getentropy(2)| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


#define GRND_NONBLOCK		0x01	/* do not block open */
#define GRND_RANDOM		0x02	/* use '/dev/random' */
#define GRND_INSECURE		0x04	/* quality can be compromised */


#ifndef	SUBROUTINE_GETRANDOM
#define	SUBROUTINE_GETRANDOM
EXTERNC_begin

extern unixret_t	getrandom(void *,size_t,uint) noex ;

EXTERNC_end
#endif /* SUBROUTINE_GETRANDOM */


#endif /* (!defined(SYSHAS_GETRANDOM)) || (SYSHAS_GETRANDOM == 0) */
/* GETRANDOM end */


#endif /* USYSGETRANDOM_INCLUDE */


