/* cfxxx HEADER */
/* lang=C20 */

/* convert a decimal digit string to its binary integer value */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	CFXXX_INCLUDE
#define	CFXXX_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<stdintx.h>


EXTERNC_begin

extern int cfxxxi(cchar *,int,int *) noex ;
extern int cfxxxl(cchar *,int,long *) noex ;
extern int cfxxxll(cchar *,int,longlong *) noex ;

extern int cfxxxui(cchar *,int,uint *) noex ;
extern int cfxxxul(cchar *,int,ulong *) noex ;
extern int cfxxxull(cchar *,int,ulonglong *) noex ;

EXTERNC_end

#if	__cplusplus

inline int cfxxx(cchar *sp,int sl,int *rp) noex {
	return cfxxxi(sp,sl,rp) ;
}
inline int cfxxx(cchar *sp,int sl,long *rp) noex {
	return cfxxxl(sp,sl,rp) ;
}
inline int cfxxx(cchar *sp,int sl,longlong *rp) noex {
	return cfxxxll(sp,sl,rp) ;
}

inline int cfxxx(cchar *sp,int sl,uint *rp) noex {
	return cfxxxui(sp,sl,rp) ;
}
inline int cfxxx(cchar *sp,int sl,ulong *rp) noex {
	return cfxxxul(sp,sl,rp) ;
}
inline int cfxxx(cchar *sp,int sl,ulonglong *rp) noex {
	return cfxxxull(sp,sl,rp) ;
}

#endif /* __cplusplus */


#endif /* CFXXX_INCLUDE */


