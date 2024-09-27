/* getuserorg HEADER */
/* lang=C20 */

/* get the best approximation of the username of the current user */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETUSERORG_INCLUDE
#define	GETUSERORG_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


EXTERNC_begin

extern int	getuserorg(char *,int,cchar *) noex ;
extern int	gethomeorg(char *,int,cchar *) noex ;

EXTERNC_end


#endif /* GETUSERORG_INCLUDE */


