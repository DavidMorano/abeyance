/* uclustername HEADER */
/* lang=C20 */

/* UNIX® cluster name */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UCLUSTERNAME_INCLUDE
#define	UCLUSTERNAME_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<usystem.h>
#include	<localmisc.h>


EXTERNC_begin

extern int uclustername_init() noex ;
extern int uclustername_set(cchar *,int,cchar *,int) noex ;
extern int uclustername_get(char *,int,cchar *) noex ;
extern int uclustername_fini() noex ;

EXTERNC_end


#endif /* UCLUSTERNAME_INCLUDE */


