/* mapshmtmp HEADER */
/* lang=C20 */

/* map shared-mmemory temporary segment */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MAPSHMTMP_INCLUDE
#define	MAPSHMTMP_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>


EXTERNC_begin

extern int mapshmtmp(char *,int,mode_t,int,char **) noex ;

EXTERNC_end


#endif /* MAPSHMTMP_INCLUDE */


