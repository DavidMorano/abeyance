/* rmx HEADER */
/* lang=C20 */

/* remove EOL (End-Of-Line) characters from the given string */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	RMX_INCLUDE
#define	RMX_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern int	rmeol(cchar *,int) noex ;
extern int	rmochr(cchar *,int,int) noex ;
extern int	rmrchr(cchar *,int,int) noex ;
extern int	rmtrailchr(cchar *,int,int) noex ;
extern int	rmext(cchar *,int) noex ;
extern int	rmcomment(cchar *,int) noex ;

static inline int rmchr(cchar *sp,int sl,int sch) noex {
	return rmochr(sp,sl,sch) ;
}

EXTERNC_end


#endif /* RMX_INCLUDE */


