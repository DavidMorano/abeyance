/* authfile HEADER */
/* lang=C20 */

/* subroutine to read an authorization file */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	AUTHFILE_INCLUDE
#define	AUTHFILE_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


EXTERNC_begin

extern int	authfile(char *,char *,cchar *) noex ;

EXTERNC_end


#endif /* AUTHFILE_INCLUDE */


