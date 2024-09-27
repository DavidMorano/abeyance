/* getuid HEADER */
/* lang=C20 */

/* get the UID for a given user-name */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-08-20, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright (c) 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETUID_INCLUDE
#define	GETUID_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


EXTERNC_begin

extern int	getuid_name(cchar *,int) noex ;
extern int	getuid_user(cchar *,int) noex ;

EXTERNC_end


#endif /* GETUID_INCLUDE */


