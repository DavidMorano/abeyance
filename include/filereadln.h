/* filereadln HEADER */
/* lang=C20 */

/* read a single line from a file */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	FILEREADLN_INCLUDE
#define	FILEREADLN_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>


EXTERNC_begin

extern int	filereadln(cchar *,char *,int) noex ;

EXTERNC_end


#endif /* FILEREADLN_INCLUDE */


