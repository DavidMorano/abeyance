/* ucentpw HEADER */
/* lang=C++20 */

/* UCENTPW object management */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-23, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UCENTPW_INCLUDE
#define	UCENTPW_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<ucsyspw.h>		/* <- the money shot */


#ifdef	__cplusplus

struct ucentpw : passwd {
	int parse(char *,int,cchar *,int) noex ;
	int load(char *,int,const ucentpw *) noex ;
	int format(char *,int) noex ;
	int size() noex ;
	operator int () noex {
	    return size() ;
	} ;
} ; /* end struct (ucentpw) */

#else /* __cplusplus */

typedef PASSWD		ucentpw ;

#endif /* __cplusplus */


#endif /* UCENTPW_INCLUDE */


