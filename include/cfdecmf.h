/* cfdecmf HEADER */
/* lang=C20 */

/* Convert-From-Decimal-Multiply-Factor */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	CFDECMF_INCLUDE
#define	CFDECMF_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<stdintx.h>


EXTERNC_begin

extern int cfdecmfi(cchar *,int,int *) noex ;
extern int cfdecmfl(cchar *,int,long *) noex ;
extern int cfdecmfll(cchar *,int,longlong *) noex ;

extern int cfdecmfui(cchar *,int,uint *) noex ;
extern int cfdecmful(cchar *,int,ulong *) noex ;
extern int cfdecmfull(cchar *,int,ulonglong *) noex ;

EXTERNC_end

#if	__cplusplus

inline int cfdecmf(cchar *sp,int sl,int *rp) noex {
	return cfdecmfi(sp,sl,rp) ;
}
inline int cfdecmf(cchar *sp,int sl,long *rp) noex {
	return cfdecmfl(sp,sl,rp) ;
}
inline int cfdecmf(cchar *sp,int sl,longlong *rp) noex {
	return cfdecmfll(sp,sl,rp) ;
}

inline int cfdecmf(cchar *sp,int sl,uint *rp) noex {
	return cfdecmfui(sp,sl,rp) ;
}
inline int cfdecmf(cchar *sp,int sl,ulong *rp) noex {
	return cfdecmful(sp,sl,rp) ;
}
inline int cfdecmf(cchar *sp,int sl,ulonglong *rp) noex {
	return cfdecmfull(sp,sl,rp) ;
}

#endif /* __cplusplus */


#endif /* CFDECMF_INCLUDE */


