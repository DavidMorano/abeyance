/* getrand HEADER */
/* lang=C20 */

/* get a network service port given a protocl-name and serive-name */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETSERV_INCLUDE
#define	GETSERV_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


EXTERNC_begin

extern int	getserv_name(cchar *,cchar *) noex ;

EXTERNC_end


#endif /* GETSERV_INCLUDE */


