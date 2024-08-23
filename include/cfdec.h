/* cfdec HEADER */
/* lang=C20 */

/* convert a decimal digit string to its binary integer value */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	CFDEC_INCLUDE
#define	CFDEC_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<stdintx.h>

#include	<cfdect.h>
#include	<cfdecmf.h>
#include	<cfdecf.h>


EXTERNC_begin

extern int cfdeci(cchar *,int,int *) noex ;
extern int cfdecl(cchar *,int,long *) noex ;
extern int cfdecll(cchar *,int,longlong *) noex ;

extern int cfdecui(cchar *,int,uint *) noex ;
extern int cfdecul(cchar *,int,ulong *) noex ;
extern int cfdecull(cchar *,int,ulonglong *) noex ;

EXTERNC_end

#if	__cplusplus

inline int cfdec(cchar *sp,int sl,int *rp) noex {
	return cfdeci(sp,sl,rp) ;
}
inline int cfdec(cchar *sp,int sl,long *rp) noex {
	return cfdecl(sp,sl,rp) ;
}
inline int cfdec(cchar *sp,int sl,longlong *rp) noex {
	return cfdecll(sp,sl,rp) ;
}

inline int cfdec(cchar *sp,int sl,uint *rp) noex {
	return cfdecui(sp,sl,rp) ;
}
inline int cfdec(cchar *sp,int sl,ulong *rp) noex {
	return cfdecul(sp,sl,rp) ;
}
inline int cfdec(cchar *sp,int sl,ulonglong *rp) noex {
	return cfdecull(sp,sl,rp) ;
}

#endif /* __cplusplus */


#endif /* CFDEC_INCLUDE */


