/* getpassword HEADER */
/* lang=C20 */

/* get a password (c-string) from the controlling terminal */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETPASSWORD_INCLUDE
#define	GETPASSWORD_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


EXTERNC_begin

extern int	getpassword(cchar *,char *,int) noex ;

EXTERNC_end


#endif /* GETPASSWORD_INCLUDE */


