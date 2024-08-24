/* usys_libstr HEADER */
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

#ifndef	USYSLIBSTR_INCLUDE
#define	USYSLIBSTR_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<stddef.h>
#include	<string.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


/* STRNLEN begin */
#if	(!defined(SYSHAS_STRNLEN)) || (SYSHAS_STRNLEN == 0)

#ifndef	SUBROUTINE_STRNLEN
#define	SUBROUTINE_STRNLEN
EXTERNC_begin
extern int	strnlen(cchar *,size_t) noex ;
EXTERNC_end
#endif /* SUBROUTINE_STRNLEN */

#endif /* (!defined(SYSHAS_STRNLEN)) || (SYSHAS_STRNLEN == 0) */
/* STRNLEN end */

/* STRLCPY begin */
#if	(!defined(SYSHAS_STRLCPY)) || (SYSHAS_STRLCPY == 0)

#ifndef	SUBROUTINE_STRLCPY
#define	SUBROUTINE_STRLCPY
EXTERNC_begin
extern int	strlcpy(char *,cchar *,size_t) noex ;
EXTERNC_end
#endif /* SUBROUTINE_STRLCPY */

#endif /* (!defined(SYSHAS_STRLCPY)) || (SYSHAS_STRLCPY == 0) */
/* STRLCPY end */


#endif /* USYSLIBSTR_INCLUDE */


