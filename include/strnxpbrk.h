/* strnxchr HEADER */
/* lang=C20 */

/* find a character in a counted c-string */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	STRNXPBRK_INCLUDE
#define	STRNXPBRK_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>


EXTERNC_begin

extern char *strnopbrk(cchar *,int,cchar *) noex ;
extern char *strnrpbrk(cchar *,int,cchar *) noex ;

static inline char *strnpbrk(cchar *sp,int sl,cchar *ss) noex {
	return strnopbrk(sp,sl,ss) ;
}

EXTERNC_end


#endif /* STRNXPBRK_INCLUDE */


