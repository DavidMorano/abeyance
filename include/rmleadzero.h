/* rmleadzero HEADER */
/* lang=C20 */

/* remove leading white-space and zero characters */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	RMLEADZERO_INCLUDE
#define	RMLEADZERO_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>


EXTERNC_begin

extern int	rmleadzero(cchar *,int) noex ;

EXTERNC_end


#endif /* RMLEADZERO_INCLUDE */


