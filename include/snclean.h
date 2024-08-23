/* snclean HEADER */
/* lang=C20 */

/* clean up a c-string of text */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	SNCLEAN_INCLUDE
#define	SNCLEAN_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern int	snclean(char *,int,cchar *,int) noex ;

EXTERNC_end


#endif /* SNCLEAN_INCLUDE */


