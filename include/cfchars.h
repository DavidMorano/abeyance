/* cfchars HEADER */
/* lang=C20 */

/* convert a digit c-string to its integer value */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	CFCHARS_INCLUDE
#define	CFCHARS_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<stdintx.h>


EXTERNC_begin

extern int cfcharsi(cchar *,int,int *) noex ;
extern int cfcharsl(cchar *,int,long *) noex ;
extern int cfcharsll(cchar *,int,longlong *) noex ;

extern int cfcharsui(cchar *,int,uint *) noex ;
extern int cfcharsul(cchar *,int,ulong *) noex ;
extern int cfcharsull(cchar *,int,ulonglong *) noex ;

EXTERNC_end

#if	__cplusplus

inline int cfchars(cchar *sp,int sl,int *rp) noex {
	return cfcharsi(sp,sl,rp) ;
}
inline int cfchars(cchar *sp,int sl,long *rp) noex {
	return cfcharsl(sp,sl,rp) ;
}
inline int cfchars(cchar *sp,int sl,longlong *rp) noex {
	return cfcharsll(sp,sl,rp) ;
}

inline int cfchars(cchar *sp,int sl,uint *rp) noex {
	return cfcharsui(sp,sl,rp) ;
}
inline int cfchars(cchar *sp,int sl,ulong *rp) noex {
	return cfcharsul(sp,sl,rp) ;
}
inline int cfchars(cchar *sp,int sl,ulonglong *rp) noex {
	return cfcharsull(sp,sl,rp) ;
}

#endif /* __cplusplus */


#endif /* CFCHARS_INCLUDE */


