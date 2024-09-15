/* ucgetua HEADER */
/* lang=C20 */

/* UNIX® C-language system database access (UCGET) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-23, David A­D­ Morano
	This module was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UCGETUA_INCLUDE
#define	UCGETUA_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<ucentua.h>


EXTERNC_begin

extern int	uc_getuabegin() noex ;
extern int	uc_getuaent(ucentua *,char *,int) noex ;
extern int	uc_getuanam(ucentua *,char *,int,cchar *) noex ;
extern int	uc_getuauid(ucentua *,char *,int,uid_t) noex ;
extern int	uc_getuaend() noex ;

EXTERNC_end


#endif /* UCGETUA_INCLUDE */


