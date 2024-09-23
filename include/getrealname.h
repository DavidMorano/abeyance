/* getrealname HEADER */
/* lang=C20 */

/* subroutines to access the 'passwd' and 'group' databases */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETREALNAME_INCLUDE
#define	GETREALNAME_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


EXTERNC_begin

extern int	getrealname(char *,int,cchar *) noex ;

EXTERNC_end


#endif /* GETREALNAME_INCLUDE */


