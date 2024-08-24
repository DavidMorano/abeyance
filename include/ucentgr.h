/* ucentgr HEADER */
/* lang=C++20 */

/* UCENTGR object management */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-23, David A­D­ Morano
	This subroutine was originally written.

*/


/* revision history:

	= 1998-02-12, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UCENTGR_INCLUDE
#define	UCENTGR_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<ucsysgr.h>		/* <- the money shot! */


#ifdef	__cplusplus

struct ucentgr : group {
	int parse(char *,int,cchar *,int) noex ;
	int load(char *,int,const ucentgr *) noex ;
	int format(char *,int) noex ;
	int size() noex ;
	operator int () noex {
	    return size() ;
	} ;
} ; /* end struct (ucentgr) */

#else /* __cplusplus */

typedef GROUP		ucentgr ;

#endif /* __cplusplus */


#endif /* UCENTGR_INCLUDE */


