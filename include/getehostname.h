/* gethehostname HEADER */
/* lang=C20 */

/* get a HOSTENT for a given INET name */
/* version %I% last-modified %G% */


/* Copyright © 2008 David A­D­ Morano.  All rights reserved. */

#ifndef	GETEHOSTNAME_INCLUDE
#define	GETEHOSTNAME_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<usystem.h>

EXTERNC_begin

extern int	getehostname(char *,cchar *) noex ;

EXTERNC_end


#endif /* GETEHOSTNAME_INCLUDE */


