/* geeaddrinfo HEADER */
/* lang=C20 */

/* get "effective" address information */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETEADDRINFO_INCLUDE
#define	GETEADDRINFO_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


EXTERNC_begin

extern int geteaddrinfo(cc *,cc *,ADDRINFO *hintp,char *,ADDRINFO **rpp) noex ;

EXTERNC_end


#endif /* GETEADDRINFO_INCLUDE */


