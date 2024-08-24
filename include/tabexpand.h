/* tabexpand HEADER */
/* lang=C20 */

/* expand the TAB characters into spaces */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	TABEXPAND_INCLUDE
#define	TABEXPAND_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>


EXTERNC_begin

extern int	tabexpand(char *,int,int,cchar *,int) noex ;

EXTERNC_end


#endif /* TABEXPAND_INCLUDE */


