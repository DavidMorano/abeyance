/* usysauxinforeq_sunos HEADER */
/* lang=C20 */

/* version %I% last-modified %G% */
/* Sun-Solaris® (SunOS) operating system support */


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

#ifndef	USYSAUXINFO_SUNOS_INCLUDE
#define	USYSAUXINFO_SUNOS_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */

/* USYSAUXINFO_SUNOS start */
#if	defined(OSNAME_SunOS) && (OSNAME_SunOS > 0)

#include	<sys/types.h>
#include	<sys/systeminfo.h>	/* <- where the stuff we want is */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>

#include	<sysauxinfo.h>


#endif /* defined(OSNAME_SunOS) && (OSNAME_SunOS > 0) */
/* USYSAUXINFO_SUNOS end */


#endif /* USYSAUXINFO_SUNOS_INCLUDE */


