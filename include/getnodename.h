/* getnodename HEADER */
/* lang=C20 */

/* get program root directory */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETNODENAME_INCLUDE
#define	GETNODENAME_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


EXTERNC_begin

extern int	getnodedomain(char *,char *) noex ;

extern int	getnodename(char *,int) noex ;
extern int	getuserdomain(char *,int) noex ;
extern int	getsysdomain(char *,int) noex ;

static inline int getinetdomain(char *rbuf,int rlen) noex {
	return getsysdomain(rbuf,rlen) ;
}

static inline int getdomainnamex(char *rp,int rl) noex {
	return getsysdomain(rp,rl) ;
}

EXTERNC_end


#endif /* GETNODENAME_INCLUDE */


