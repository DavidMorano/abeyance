/* cfnum HEADER */
/* lang=C20 */

/* convert a decimal digit string to its binary integer value */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	CFNUM_INCLUDE
#define	CFNUM_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<stdintx.h>


EXTERNC_begin

extern int cfnumi(cchar *,int,int *) noex ;
extern int cfnuml(cchar *,int,long *) noex ;
extern int cfnumll(cchar *,int,longlong *) noex ;

extern int cfnumui(cchar *,int,uint *) noex ;
extern int cfnumul(cchar *,int,ulong *) noex ;
extern int cfnumull(cchar *,int,ulonglong *) noex ;

EXTERNC_end

#if	__cplusplus

inline int cfnum(cchar *sp,int sl,int *rp) noex {
	return cfnumi(sp,sl,rp) ;
}
inline int cfnum(cchar *sp,int sl,long *rp) noex {
	return cfnuml(sp,sl,rp) ;
}
inline int cfnum(cchar *sp,int sl,longlong *rp) noex {
	return cfnumll(sp,sl,rp) ;
}

inline int cfnum(cchar *sp,int sl,uint *rp) noex {
	return cfnumui(sp,sl,rp) ;
}
inline int cfnum(cchar *sp,int sl,ulong *rp) noex {
	return cfnumul(sp,sl,rp) ;
}
inline int cfnum(cchar *sp,int sl,ulonglong *rp) noex {
	return cfnumull(sp,sl,rp) ;
}

#endif /* __cplusplus */


#endif /* CFNUM_INCLUDE */


