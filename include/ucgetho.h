/* ucgetho HEADER */
/* lang=C20 */

/* UNIX® C-language system database access (UCGET) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This program was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UCGETHO_INCLUDE
#define	UCGETHO_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<ucentho.h>


EXTERNC_begin

extern int	uc_gethobegin(int) noex ;
extern int	uc_gethoent(ucentho *,char *,int) noex ;
extern int	uc_gethonam(ucentho *,char *,int,cchar *) noex ;
extern int	uc_gethoadd(ucentho *,char *,int,int,cvoid *,int) noex ;
extern int	uc_gethoend() noex ;

EXTERNC_end


#endif /* UCGETHO_INCLUDE */


