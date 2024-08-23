/* sncpyx HEADER */
/* lang=C20 */

/* copy a c-string to a given case */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	SNCPYX_INCLUDE
#define	SNCPYX_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<sncpyxw.h>


EXTERNC_begin

extern int sncpyx(char *,int,int,...) noex ;

extern int sncpy1(char *,int,cc *) noex ;
extern int sncpy2(char *,int,cc *,cc *) noex ;
extern int sncpy3(char *,int,cc *,cc *,cc *) noex ;
extern int sncpy4(char *,int,cc *,cc *,cc *,cc *) noex ;
extern int sncpy5(char *,int,cc *,cc *,cc *,cc *,cc *) noex ;
extern int sncpy6(char *,int,cc *,cc *,cc *,cc *,cc *,cc *) noex ;

EXTERNC_end

#ifdef	__cplusplus

template<typename ... Args>
inline int sncpy(char *dp,int dl,Args ... args) noex {
	cint		na = npack(Args) ;
	return sncpyx(dp,dl,na,args ...) ;
}

#endif /* __cplusplus */


#endif /* SNCPYX_INCLUDE */


