/* getprogroot HEADER */
/* lang=C20 */

/* get program root directory */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETPROGROOT_INCLUDE
#define	GETPROGROOT_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern int getprogroot(cc *,mainv,int *,char *,cc *) noex ;

EXTERNC_end


#endif /* GETPROGROOT_INCLUDE */


