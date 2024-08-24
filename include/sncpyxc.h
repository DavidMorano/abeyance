/* sncpyxc HEADER */
/* lang=C20 */

/* copy a c-string to a given case */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	SNCPYXC_INCLUDE
#define	SNCPYXC_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>


EXTERNC_begin

extern int sncpybc(char *,int,cchar *) noex ;
extern int sncpylc(char *,int,cchar *) noex ;
extern int sncpyuc(char *,int,cchar *) noex ;
extern int sncpyfc(char *,int,cchar *) noex ;

EXTERNC_end


#endif /* SNCPYXC_INCLUDE */


