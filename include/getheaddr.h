/* getheaddr HEADER */
/* lang=C20 */

/* get a HOSTENT for a given INET address */
/* version %I% last-modified %G% */


/* Copyright © 2008 David A­D­ Morano.  All rights reserved. */

#ifndef	GETHEADDR_INCLUDE
#define	GETHEADDR_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<usystem.h>

EXTERNC_begin

extern int	getheaddr(ucentho *,char *,int,cchar *) noex ;

EXTERNC_end


#endif /* GETHEADDR_INCLUDE */


