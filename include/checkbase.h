/* checkbase HEADER */
/* lang=C20 */

/* test whether a string is composed of all characters of a given base */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	CHECKBASE_INCLUDE
#define	CHECKBASE_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern int checkbase(cchar *,int,int) noex ;

EXTERNC_end


#endif /* CHECKBASE_INCLUDE */


