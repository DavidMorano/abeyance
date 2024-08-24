/* mkfname HEADER */
/* lang=C20 */

/* make a file name from several parts */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MKFNAME_INCLUDE
#define	MKFNAME_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>

#include	<mkfnamesuf.h>


EXTERNC_begin

extern int mkfnamex(char *,int,...) noex ;

extern int mkfname1(char *,cc *) noex ;
extern int mkfname2(char *,cc *,cc *) noex ;
extern int mkfname3(char *,cc *,cc *,cc *) noex ;
extern int mkfname4(char *,cc *,cc *,cc *,cc *) noex ;
extern int mkfname5(char *,cc *,cc *,cc *,cc *,cc *) noex ;
extern int mkfname6(char *,cc *,cc *,cc *,cc *,cc *,cc *) noex ;

EXTERNC_end

#ifdef	__cplusplus

template<typename ... Args>
inline int mkfname(char *dp,Args ... args) noex {
	cint	na = npack(Args) ;
	return mkfnamex(dp,na,args ...) ;
}

#endif /* __cplusplus */


#endif /* MKFNAME_INCLUDE */


