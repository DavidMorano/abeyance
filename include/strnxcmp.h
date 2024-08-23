/* strnxcmp HEADER */
/* lang=C20 */

/* find a character in a counted c-string */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	STRNXCMP_INCLUDE
#define	STRNXCMP_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<string.h>		/* |strncmp(3c)| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern int strnfoldcmp(cchar *,cchar *,int) noex ;
extern int strnkeycmp(cchar *,cchar *,int) noex ;
extern int strnleadcmp(cchar *,cchar *,int) noex ;
extern int strnncmp(cchar *,int,cchar *,int) noex ;
extern int strnndictcmp(cchar *,int,cchar *,int) noex ;

static inline int strnbasecmp(cchar *s1,cchar *s2,int slen) noex {
	return strncmp(s1,s2,slen) ;
}

EXTERNC_end


#endif /* STRNXCMP_INCLUDE */


