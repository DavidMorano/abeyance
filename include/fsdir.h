/* fsdir HEADER */
/* lang=C20 */

/* File-System-Direcroy (FSDIR) */
/* version %I% last-modified %G% */


/* revision history:

	= 1999-07-28, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1999 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This object facilitates reading directory entries.

*******************************************************************************/


#include	<envstandards.h>	/* ordered first to configure */


#if	defined(SYSHAS_GETDENTS) && (SYSHAS_GETDENTS > 0)

#include	<sunos_fsdir.h>

#else /* defined(SYSHAS_GETDENTS) && (SYSHAS_GETDENTS > 0) */

#include	<darwin_fsdir.h>

#endif /* defined(SYSHAS_GETDENTS) && (SYSHAS_GETDENTS > 0) */


