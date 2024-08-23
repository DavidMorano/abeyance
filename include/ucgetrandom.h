/* ucgetrnadom HEADER */
/* lang=C20 */

/* LIBUC get some pseudo-randomo data from the operaring system */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UCGETRANDOM_INCLUDE
#define	UCGETRANDOM_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>


EXTERNC_begin

extern int uc_getrandom(void *,int,uint) noex ;
extern int uc_getentropy(void *,int) noex ;

EXTERNC_end


#endif /* UCGETRANDOM_INCLUDE */


