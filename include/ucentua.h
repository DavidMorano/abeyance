/* ucentua HEADER */
/* lang=C++20 */

/* subroutines for simple USERATTR object (from UNIX® library-3c) management */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-23, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UCENTUA_INCLUDE
#define	UCENTUA_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<userattr.h>		/* <- the money shot! */


#ifdef	__cplusplus

struct ucentua : userattr {
	int parse(char *,int,cchar *,int) noex ;
	int load(char *,int,const ucentua *) noex ;
	int format(char *,int) noex ;
	int size() noex ;
	operator int () noex {
	    return size() ;
	} ;
} ; /* end struct (ucentua) */

#else /* __cplusplus */

typedef USERATTR	ucentua ;

#endif /* __cplusplus */


#endif /* UCENTUA_INCLUDE */


