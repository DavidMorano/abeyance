/* opensockaddr HEADER */
/* lang=C20 */

/* open a connection to a socket by a SOCKADDR */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	OPENSOCKADDR_INCLUDE
#define	OPENSOCKADDR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>


EXTERNC_begin

extern int opensockaddr(int,int,int,SOCKADDR *,int) noex ;

EXTERNC_end


#endif /* OPENSOCKADDR_INCLUDE */


