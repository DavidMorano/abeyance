/* strn HEADER */
/* lang=C20 */

/* find a character in a counted c-string */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	STRN_INCLUDE
#define	STRN_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>

#include	<strnxcmp.h>
#include	<strnxchr.h>
#include	<strnxpbrk.h>
#include	<strncpyxc.h>


EXTERNC_begin

/* calculate string length */
extern int strnnlen(cchar *,int,int) noex ;
/* find */
extern char *strnsub(cchar *,int,cchar *) noex ;
extern char *strncasesub(cchar *,int,cchar *) noex ;
/* copy */
extern char *strnncpy(char *,cchar *,int,int) noex ;
extern char *strnwcpy(char *,int,cchar *,int) noex ;
/* set */
extern char *strnset(char *,int,int) noex ;
extern char *strnset(char *,int,int) noex ;

static inline char *strnsetblanks(char *dp,int dl) noex {
	return strnset(dp,dl,' ') ;
}

EXTERNC_end


#endif /* STRN_INCLUDE */


