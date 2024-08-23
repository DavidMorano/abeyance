/* usysflag HEADER */
/* lang=C20 */

/* version %I% last-modified %G% */
/* operating system flag */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This file defines preprocessor symbols that express which
	operating syustem is being compiled.


*******************************************************************************/

#ifndef	USYSFLAG_INCLUDE
#define	USYSFLAG_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */

#if defined(OSNAME_SunOS) && (OSNAME_SunOS > 0)
#define	F_SUNOS		1
#else
#define	F_SUNOS		0
#endif
#if defined(OSNAME_Darwin) && (OSNAME_Darwin > 0)
#define	F_DARWIN	1
#else
#define	F_DARWIN	0
#endif
#if defined(OSNAME_Linux) && (OSNAME_Linux > 0)
#define	F_LINUX		1
#else
#define	F_LINUX		0
#endif


#endif /* USYSFLAG_INCLUDE */


