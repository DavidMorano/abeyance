/* udup HEADER */
/* lang=C20 */

/* UNIX® File-Descriptor Dupplication */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This file contains the subroutine declarations for various
	UNIX® system Memory-Management subroutines.

	Names:
	u_mdup
	u_mdup2

	Descrptor:
	I duplication file-descriptors.

*******************************************************************************/

#ifndef	UDUP_INCLUDE
#define	UDUP_INCLUDE


#include	<envstandards.h>
#include	<sys/types.h>
#include	<sys/mman.h>
#include	<unistd.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>

#include	<usys.h>


#ifdef	__cplusplus
extern "C" {
#endif

extern int u_dup(int) noex ;
extern int u_dup2(int,int) noex ;

#ifdef	__cplusplus
}
#endif


#endif /* UDUP_INCLUDE */


