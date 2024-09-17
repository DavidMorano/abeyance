/* inetconv HEADER */
/* lang=C20 */

/* is a given c-string a valid INET address (either 4 or 6)? */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	INETCONV_INCLUDE
#define	INETCONV_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


EXTERNC_begin

extern int inetnetpton(void *,int,int,cchar *,int) noex ;
extern int inetpton(void *,int,int,cchar *,int) noex ;
extern int inetntop(char *,int,int,cvoid *) noex ;

EXTERNC_end


#endif /* INETCONV_INCLUDE */


