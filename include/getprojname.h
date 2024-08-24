/* getprojname HEADER */
/* lang=C20 */

/* get a project name from the system account database */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-07-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETPROJNAME_INCLUDE
#define	GETPROJNAME_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


EXTERNC_begin

extern int	getprojname(char *,int,cchar *) noex ;

EXTERNC_end


#endif /* GETPROJNAME_INCLUDE */


