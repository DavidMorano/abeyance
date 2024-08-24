/* xfile HEADER */
/* lang=C20 */

/* check if a given file is eXecutable */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	XFILE_INCLUDE
#define	XFILE_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>
#include	<ids.h>


EXTERNC_begin

extern int	xfile(ids *,cchar *) noex ;

EXTERNC_end


#endif /* XFILE_INCLUDE */


