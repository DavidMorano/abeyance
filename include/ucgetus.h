/* ucgetus HEADER */
/* lang=C20 */

/* UNIX® C-language system database access (UCGET) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-23, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UCGETUS_INCLUDE
#define	UCGETUS_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern int	uc_getusbegin() noex ;
extern int	uc_getusent(char *,int) noex ;
extern int	uc_getusend() noex ;

EXTERNC_end


#endif /* UCGETUS_INCLUDE */


