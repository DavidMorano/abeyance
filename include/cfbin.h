/* cfbin HEADER */
/* lang=C20 */

/* convert a digit c-string to its integer value */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	CFBIN_INCLUDE
#define	CFBIN_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<stdintx.h>


EXTERNC_begin

extern int cfbini(cchar *,int,int *) noex ;
extern int cfbinl(cchar *,int,long *) noex ;
extern int cfbinll(cchar *,int,longlong *) noex ;

extern int cfbinui(cchar *,int,uint *) noex ;
extern int cfbinul(cchar *,int,ulong *) noex ;
extern int cfbinull(cchar *,int,ulonglong *) noex ;

EXTERNC_end

#if	__cplusplus

inline int cfbin(cchar *sp,int sl,int *rp) noex {
	return cfbini(sp,sl,rp) ;
}
inline int cfbin(cchar *sp,int sl,long *rp) noex {
	return cfbinl(sp,sl,rp) ;
}
inline int cfbin(cchar *sp,int sl,longlong *rp) noex {
	return cfbinll(sp,sl,rp) ;
}

inline int cfbin(cchar *sp,int sl,uint *rp) noex {
	return cfbinui(sp,sl,rp) ;
}
inline int cfbin(cchar *sp,int sl,ulong *rp) noex {
	return cfbinul(sp,sl,rp) ;
}
inline int cfbin(cchar *sp,int sl,ulonglong *rp) noex {
	return cfbinull(sp,sl,rp) ;
}

#endif /* __cplusplus */


#endif /* CFBIN_INCLUDE */


