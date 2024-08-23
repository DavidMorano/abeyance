/* strlinelen HEADER */
/* lang=C20 */

/* calculate the number of characters in a c-string up to a given maximum */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	STRLINELEN_INCLUDE
#define	STRLINELEN_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern int	strlinelen(cchar *,int,int) noex ;

EXTERNC_end


#endif /* STRLINELEN_INCLUDE */


