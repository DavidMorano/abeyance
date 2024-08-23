/* usys_resolvepath HEADER */
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

#ifndef	USYSRESOLVEPATH_INCLUDE
#define	USYSRESOLVEPATH_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */

/* RESOLVEPATH begin */
#if	(!defined(SYSHAS_RESOLVEPATH)) || (SYSHAS_RESOLVEPATH == 0)


#include	<stddef.h>		/* |size_t| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


#ifndef	SUBROUTINE_RESOLVEPATH
#define	SUBROUTINE_RESOLVEPATH
EXTERNC_begin

extern unixret_t resolvepath(cchar *,char *,size_t) noex ;

EXTERNC_end
#endif /* SUBROUTINE_RESOLVEPATH */


#endif /* (!defined(SYSHAS_RESOLVEPATH)) || (SYSHAS_RESOLVEPATH == 0) */
/* RESOLVEPATH end */


#endif /* USYSRESOLVEPATH_INCLUDE */


