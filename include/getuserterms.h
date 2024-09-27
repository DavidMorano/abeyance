/* getuserterms HEADER */
/* lang=C20 */

/* get a list (returned as vector of c-strings) of the logged in user terms */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETUSERTERMS_INCLUDE
#define	GETUSERTERMS_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


EXTERNC_begin

extern int	getuserterms(vecstr *,cchar *) noex ;

EXTERNC_end


#endif /* GETUSERTERMS_INCLUDE */


