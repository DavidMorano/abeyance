/* syshasutmp HEADER */
/* lang=C20 */

/* System-Has-UTMPX */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	SYSHASUTMP_INCLUDE
#define	SYSHASUTMP_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */


#if	defined(OSNAME_SunOS) && (ISNAME_SunOS > 0)
#define	SYSHASUTMP_SESSION	1
#define	SYSHASUTMP_SYSLEN	1
#define	SYSHASUTMP_EXIT		1
#elif	defined(OSNAME_Darwin) && (OSNAME_Darwin > 0) 
#define	SYSHASUTMP_SESSION	0
#define	SYSHASUTMP_SYSLEN	0
#define	SYSHASUTMP_EXIT		0
#elif	defined(OSNAME_Linux) && (OSNAME_Linux > 0) 
#define	SYSHASUTMP_SESSION	1
#define	SYSHASUTMP_SYSLEN	1
#define	SYSHASUTMP_EXIT		1
#else
#define	SYSHASUTMP_SESSION	0
#define	SYSHASUTMP_SYSLEN	0
#define	SYSHASUTMP_EXIT		0
#endif /* which OS */


#endif /* SYSHASUTMP_INCLUDE */


