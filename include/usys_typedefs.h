/* usys_typedefs HEADER */
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

	This file contains the UNIX® system types that the brain-damaged
	MacOS operating system does NOT have.  We are trying in a very
	small way to make up for some of the immense brain-damage within
	the Apple Darwin operating system.

*******************************************************************************/

#ifndef	USYSTYPEDEFS_INCLUDE
#define	USYSTYPEDEFS_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<dirent.h>

#if	(!defined(SYSHAS_TYPEDIRENT)) || (SYSHAS_TYPEDIRENT == 0)

#ifndef	TYPEDEF_DIRENT
#define	TYPEDEF_DIRENT
typedef struct dirent		dirent_t ;
#endif

#endif /* SYSHAS_TYPEDIRENT */


#endif /* USYSTYPEDEFS_INCLUDE */


