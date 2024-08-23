/* strnxchr HEADER */
/* lang=C20 */

/* find a character in a counted c-string */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	STRNXCHR_INCLUDE
#define	STRNXCHR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>


EXTERNC_begin

extern char *strnochr(cchar *,int,int) noex ;
extern char *strnrchr(cchar *,int,int) noex ;

static inline char *strnchr(cchar *sp,int sl,int sch) noex {
	return strnochr(sp,sl,sch) ;
}

EXTERNC_end


#endif /* STRNXCHR_INCLUDE */


