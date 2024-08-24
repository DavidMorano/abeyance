/* pathclean HEADER */
/* lang=C20 */

/* add a c-string to the end of an existing path c-string */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	PATHCLEAN_INCLUDE
#define	PATHCLEAN_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


EXTERNC_begin

extern int pathclean(char *,cchar *,int) noex ;

EXTERNC_end


#endif /* PATHCLEAN_INCLUDE */


