/* cthex HEADER */
/* lang=C20 */

/* subroutines to convert an integer to a HEX string */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	CTHEX_INCLUDE
#define	CTHEX_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<stdintx.h>


EXTERNC_begin

extern int cthexc(char *,int,int) noex ;
extern int cthexs(char *,int,int) noex ;
extern int cthexi(char *,int,int) noex ;
extern int cthexl(char *,int,long) noex ;
extern int cthexll(char *,int,longlong) noex ;

extern int cthexuc(char *,int,uint) noex ;
extern int cthexus(char *,int,uint) noex ;
extern int cthexui(char *,int,uint) noex ;
extern int cthexul(char *,int,ulong) noex ;
extern int cthexull(char *,int,ulonglong) noex ;

EXTERNC_end

#ifdef	__cplusplus

inline int cthex(char *bp,int bl,int v) noex {
	return cthexi(bp,bl,v) ;
}
inline int cthex(char *bp,int bl,long v) noex {
	return cthexl(bp,bl,v) ;
}
inline int cthex(char *bp,int bl,longlong v) noex {
	return cthexll(bp,bl,v) ;
}

inline int cthex(char *bp,int bl,uint v) noex {
	return cthexui(bp,bl,v) ;
}
inline int cthex(char *bp,int bl,ulong v) noex {
	return cthexul(bp,bl,v) ;
}
inline int cthex(char *bp,int bl,ulonglong v) noex {
	return cthexull(bp,bl,v) ;
}

#endif /* __cplusplus */


#endif /* CTHEX_INCLUDE */


