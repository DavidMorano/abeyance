/* getsystypenum HEADER */
/* lang=C20 */

/* get the system type and OS number (if we can) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETSYSTYPENUM_INCLUDE
#define	GETSYSTYPENUM_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


EXTERNC_begin

extern int	getsystypenum(char *,char *,cc *,cc *) noex ;

EXTERNC_end


#endif /* GETSYSTYPENUM_INCLUDE */


