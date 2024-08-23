/* cfhex HEADER */
/* lang=C20 */

/* convert a decimal digit string to its binary integer value */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	CFHEX_INCLUDE
#define	CFHEX_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<stdintx.h>


EXTERNC_begin

extern int cfhexi(cchar *,int,int *) noex ;
extern int cfhexl(cchar *,int,long *) noex ;
extern int cfhexll(cchar *,int,longlong *) noex ;

extern int cfhexui(cchar *,int,uint *) noex ;
extern int cfhexul(cchar *,int,ulong *) noex ;
extern int cfhexull(cchar *,int,ulonglong *) noex ;

EXTERNC_end

#if	__cplusplus

inline int cfhex(cchar *sp,int sl,int *rp) noex {
	return cfhexi(sp,sl,rp) ;
}
inline int cfhex(cchar *sp,int sl,long *rp) noex {
	return cfhexl(sp,sl,rp) ;
}
inline int cfhex(cchar *sp,int sl,longlong *rp) noex {
	return cfhexll(sp,sl,rp) ;
}

inline int cfhex(cchar *sp,int sl,uint *rp) noex {
	return cfhexui(sp,sl,rp) ;
}
inline int cfhex(cchar *sp,int sl,ulong *rp) noex {
	return cfhexul(sp,sl,rp) ;
}
inline int cfhex(cchar *sp,int sl,ulonglong *rp) noex {
	return cfhexull(sp,sl,rp) ;
}

#endif /* __cplusplus */


#endif /* CFHEX_INCLUDE */


