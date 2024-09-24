/* getfstype HEADER */
/* lang=C20 */

/* get the type of the filesystem for an FD */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETFSTYPE_INCLUDE
#define	GETFSTYPE_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


EXTERNC_begin

extern int	getfstype(char *,int,int) noex ;

EXTERNC_end


#endif /* GETFSTYPE_INCLUDE */


