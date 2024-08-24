/* nchr HEADER */
/* lang=C20 */

/* count number of a specified character in a string */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-10-10, David A­D­ Morano
	This subroutine was modeled from an original assembly
	language version.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	NCHR_INCLUDE
#define	NCHR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern int	nchr(cchar *,int,int) noex ;

EXTERNC_end


#endif /* NCHR_INCLUDE */


