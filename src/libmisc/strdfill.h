/* strdfill HEADER */
/* lang=C20 */

/* c-string comparisons */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	STRDFILL_INCLUDE
#define	STRDFILL_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern char *strdfillx(char *,int,int,...) noex ;

extern char *strdfill1(char *,int,cc *) noex ;
extern char *strdfill2(char *,int,cc *,cc *) noex ;
extern char *strdfill3(char *,int,cc *,cc *,cc *) noex ;
extern char *strdfill4(char *,int,cc *,cc *,cc *,cc *) noex ;
extern char *strdfill5(char *,int,cc *,cc *,cc *,cc *,cc *) noex ;

EXTERNC_end

#ifdef	__cplusplus

template<typename ... Args>
inline char *srtdfill(char *dp,int dl,Args ... args) noex {
	cint		na = npack(Args) ;
	return strdfillx(dp,dl,na,args ...) ;
}

#endif /* __cplusplus */


#endif /* STRDFILL_INCLUDE */


