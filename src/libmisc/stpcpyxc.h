/* stpcpyxc HEADER */
/* encoding=ISO8859-1 */
/* lang=C20 */

/* copy a c-string to destination buffer w/ a case conversion */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	STPCPYXC_INCLUDE
#define	STPCPYXC_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>


EXTERNC_begin

extern char	* stpcpybc (char *,cchar *) noex ;
extern char	* stpcpylc (char *,cchar *) noex ;
extern char	* stpcpyuc (char *,cchar *) noex ;
extern char	* stpcpyfc (char *,cchar *) noex ;

EXTERNC_end


#endif /* STPCPYXC_INCLUDE */


