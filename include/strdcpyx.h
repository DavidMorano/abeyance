/* strdcpyx HEADER */
/* lang=C20 */

/* string-copy variant */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	STRDCPYX_INCLUDE
#define	STRDCPYX_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<strdcpyxw.h>


EXTERNC_begin

extern char *strdcpyx(char *,int,int,...) noex ;

extern char *strdcpy1(char *,int,cc *) noex ;
extern char *strdcpy2(char *,int,cc *,cc *) noex ;
extern char *strdcpy3(char *,int,cc *,cc *,cc *) noex ;
extern char *strdcpy4(char *,int,cc *,cc *,cc *,cc *) noex ;
extern char *strdcpy5(char *,int,cc *,cc *,cc *,cc *,cc *) noex ;
extern char *strdcpy6(char *,int,cc *,cc *,cc *,cc *,cc *,cc *) noex ;

EXTERNC_end

#ifdef	__cplusplus

template<typename ... Args>
inline char *strdcpy(char *dp,int dl,Args ... args) noex {
	cint	na = npack(Args) ;
	return strdcpyx(dp,dl,na,args ...) ;
}

#endif /* __cplusplus */


#endif /* STRDCPYX_INCLUDE */


