/* ucproguser HEADER */
/* lang=C20 */

/* UNIX® username and possibly user-home-directory */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UCPROGUSER_INCLUDE
#define	UCPROGUSER_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>


EXTERNC_begin

extern int ucproguser_init() noex ;
extern int ucproguser_nameset(cchar *,int,uid_t,int) noex ;
extern int ucproguser_nameget(char *,int,uid_t) noex ;
extern int ucproguser_fini() noex ;

EXTERNC_end


#endif /* UCPROGUSER_INCLUDE */


