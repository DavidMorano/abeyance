/* ucclustername HEADER */
/* lang=C20 */

/* UNIX® cluster name */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UCCLUSTERNAME_INCLUDE
#define	UCCLUSTERNAME_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>


EXTERNC_begin

extern int ucclustername_init() noex ;
extern int ucclustername_set(cchar *,int,cchar *,int) noex ;
extern int ucclustername_get(char *,int,cchar *) noex ;
extern int ucclustername_fini() noex ;

EXTERNC_end


#endif /* UCCLUSTERNAME_INCLUDE */


