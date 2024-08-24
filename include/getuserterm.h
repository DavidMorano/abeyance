/* getuserterm HEADER */
/* lang=C20 */

/* get the name of the most recently accessed controlling terminal */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETUSERTERM_INCLUDE
#define	GETUSERTERM_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


EXTERNC_begin

extern int	getuserterm(char *rbuf,int rlen,cchar *username) noex ;

EXTERNC_end


#endif /* GETUSERTERM_INCLUDE */


