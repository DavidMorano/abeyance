/* isinetaddr HEADER */
/* lang=C20 */

/* is a given c-string a valid INET address (either 4 or 6)? */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	ISINETADDR_INCLUDE
#define	ISINETADDR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern bool	isinetaddr(cchar *) noex ;

EXTERNC_end


#endif /* ISINETADDR_INCLUDE */


