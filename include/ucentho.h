/* ucentho HEADER */
/* lang=C++20 */

/* UCENTHO object management */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-23, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UCENTHO_INCLUDE
#define	UCENTHO_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<netdb.h>		/* <- is that the money shot? */


#ifdef	__cplusplus

struct ucentho : hostent {
	int parse(char *,int,cchar *,int) noex ;
	int load(char *,int,const ucentho *) noex ;
	int format(char *,int) noex ;
	int size() noex ;
	operator int () noex {
	    return size() ;
	} ;
} ; /* end struct (ucentho) */

#else /* __cplusplus */

typedef HOSTENT		ucentho ;

#endif /* __cplusplus */


#endif /* UCENTHO_INCLUDE */


