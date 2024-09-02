/* getutmpterm HEADER */
/* lang=C20 */

/* get a terminal (device file-path) from the UTMP database */
/* version %I% last-modified %G% */


/* revision history:

	= 2003-03-04, David A.D. Morano
	This was written from scratch.

*/

/* Copyright © 2003 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This subroutine retrieve a terminal (device file-path) from
	the UTMP database, given a session ID.

*******************************************************************************/

#ifndef	GETUTMPTERM_INCLUDE
#define	GETUTMPTERM_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


EXTERNC_begin

extern int	getutmpterm(char *,int,pid_t) noex ;

EXTERNC_end


#endif /* GETUTMPTERM_INCLUDE */


