/* findxfile HEADER */
/* lang=C20 */

/* find an eXecutable file given a name */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	FINDXFILE_INCLUDE
#define	FINDXFILE_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>
#include	<ids.h>


EXTERNC_begin

extern int	findxfile(ids *,char *,cchar *) noex ;

EXTERNC_end


#endif /* FINDXFILE_INCLUDE */


