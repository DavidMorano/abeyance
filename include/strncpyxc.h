/* strncpyxc HEADER */
/* lang=C20 */

/* string-copy variant */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	STRNCPYXC_INCLUDE
#define	STRNCPYXC_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>


EXTERNC_begin

extern char	* strncpybc (char *,cchar *,int) noex ;
extern char	* strncpylc (char *,cchar *,int) noex ;
extern char	* strncpyuc (char *,cchar *,int) noex ;
extern char	* strncpyfc (char *,cchar *,int) noex ;

EXTERNC_end


#endif /* STRNCPYXC_INCLUDE */


