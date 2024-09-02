/* ucentpr HEADER */
/* lang=C++20 */

/* UCENTPR object management */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-23, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UCENTPR_INCLUDE
#define	UCENTPR_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<netdb.h>		/* <- is that the money shot? */


#ifdef	__cplusplus

struct ucentpr : protoent {
	int parse(char *,int,cchar *,int) noex ;
	int load(char *,int,const ucentpr *) noex ;
	int format(char *,int) noex ;
	int size() noex ;
	operator int () noex {
	    return size() ;
	} ;
} ; /* end struct (ucentpr) */

#else /* __cplusplus */

typedef PROTOENT	ucentpr ;

#endif /* __cplusplus */


#endif /* UCENTPR_INCLUDE */


