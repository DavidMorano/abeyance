/* usys_linux HEADER */
/* lang=C20 */

/* Apple Darwin operating system support */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

	= 2017-08-01, David A­D­ Morano
	Updated for lack of interfaces in MacOS Darwin

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This file contains the UNIX® system types and preprocessor symbols
	that may not be provided.

*******************************************************************************/

#ifndef	USYSLINUX_INCLUDE
#define	USYSLINUX_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<sys/wait.h>		/* <- type |idtype_t| is there */
#include	<sys/time.h>		/* <- |TIMESPEC| is there */
#include	<signal.h>
#include	<pthread.h>
#include	<time.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


/* USYSLINUX start */
#if	defined(OSNAME_Linux) && (OSNAME_Linux > 0)


/*----------------------------------------------------------------------------*/
/* UCTIMEOUT begin */

#ifndef	SIGTIMEOUT
#define	SIGTIMEOUT	SIGRTMAX	/* hack for now */
#endif

/* UCTIMEOUT end */
/*----------------------------------------------------------------------------*/


#endif /* defined(OSNAME_Linux) && (OSNAME_Linux > 0)*/
/* USYSLINUX finish */


#endif /* USYSLINUX_INCLUDE */


