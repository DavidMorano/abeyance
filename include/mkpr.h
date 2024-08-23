/* mkpr HEADER */
/* lang=C20 */

/* make a program-root file-path */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MKPR_INCLUDE
#define	MKPR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>


EXTERNC_begin

extern int mkpr(char *,int,cchar *,cchar *) noex ;
extern int getrootdname(char *,int,cchar *,cchar *) noex ;

EXTERNC_end


#endif /* MKPR_INCLUDE */


