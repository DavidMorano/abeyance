/* usysauxinforeq_linux HEADER */
/* lang=C20 */

/* version %I% last-modified %G% */
/* Apple Darwin operating system support */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

	= 2017-08-01, David A­D­ Morano
	Updated for lack of interfaces in MacOS Darwin

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This file contains the UNIX system types and preprocessor symbols
	that may not be provided.


*******************************************************************************/

#ifndef	USYSAUXINFO_LINUX_INCLUDE
#define	USYSAUXINFO_LINUX_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */

/* USYSAUXINFO_LINUX start */
#if	defined(OSNAME_Linux) && (OSNAME_Linux > 0)

#include	<sys/types.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>

#include	<sysauxinfo.h>


#endif /* defined(OSNAME_Linux) && (OSNAME_Linux > 0)*/
/* USYSAUXINFO_LINUX finish */


#endif /* USYSAUXINFO_LINUX_INCLUDE */


