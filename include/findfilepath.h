/* findfilepath HEADER */
/* lang=C20 */

/* find a file path (given some information) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	FINDFILEPATH_INCLUDE
#define	FINDFILEPATH_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


EXTERNC_begin

extern int findfilepath(char *,cchar *,cchar *,int) noex ;

EXTERNC_end


#endif /* FINDFILEPATH_INCLUDE */


