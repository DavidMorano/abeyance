/* getprogpath HEADER */
/* lang=C20 */

/* get a program path (given some information) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETPROGPATH_INCLUDE
#define	GETPROGPATH_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


EXTERNC_begin

extern int getprogpath(ids *,vecstr *,char *,cchar *,int) noex ;

EXTERNC_end


#endif /* GETPROGPATH_INCLUDE */


