/* mkfnamesuf HEADER */
/* lang=C20 */

/* make a file name from parts (one base and some suffixes) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MKFNAMESUF_INCLUDE
#define	MKFNAMESUF_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


EXTERNC_begin

extern int mkfnamesufx(char *,int,cc *,...) noex ;

extern int mkfnamesuf1(char *,cc *,cc *) noex ;
extern int mkfnamesuf2(char *,cc *,cc *,cc *) noex ;
extern int mkfnamesuf3(char *,cc *,cc *,cc *,cc *) noex ;
extern int mkfnamesuf4(char *,cc *,cc *,cc *,cc *,cc *) noex ;
extern int mkfnamesuf5(char *,cc *,cc *,cc *,cc *,cc *,cc *) noex ;

EXTERNC_end

#ifdef	__cplusplus

template<typename ... Args>
inline int mkfnamesuf(char *dp,cc *bp,Args ... args) noex {
	cint	na = npack(Args) ;
	return mkfnamesufx(dp,na,bp,args ...) ;
}

#endif /* __cplusplus */


#endif /* MKFNAMESUF_INCLUDE */


