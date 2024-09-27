/* getaddr HEADER */
/* lang=C20 */

/* get an address-family (or AF length) by name */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETADDR_INCLUDE
#define	GETADDR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


EXTERNC_begin

extern int getaddrfamily(cchar *) noex ;
extern int getaddrlen(int) noex ;

EXTERNC_end


#endif /* GETADDR_INCLUDE */


