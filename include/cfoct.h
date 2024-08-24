/* cfoct HEADER */
/* lang=C20 */

/* convert a decimal digit string to its binary integer value */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	CFOCT_INCLUDE
#define	CFOCT_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<stdintx.h>


EXTERNC_begin

extern int cfocti(cchar *,int,int *) noex ;
extern int cfoctl(cchar *,int,long *) noex ;
extern int cfoctll(cchar *,int,longlong *) noex ;

extern int cfoctui(cchar *,int,uint *) noex ;
extern int cfoctul(cchar *,int,ulong *) noex ;
extern int cfoctull(cchar *,int,ulonglong *) noex ;

EXTERNC_end

#if	__cplusplus

inline int cfoct(cchar *sp,int sl,int *rp) noex {
	return cfocti(sp,sl,rp) ;
}
inline int cfoct(cchar *sp,int sl,long *rp) noex {
	return cfoctl(sp,sl,rp) ;
}
inline int cfoct(cchar *sp,int sl,longlong *rp) noex {
	return cfoctll(sp,sl,rp) ;
}

inline int cfoct(cchar *sp,int sl,uint *rp) noex {
	return cfoctui(sp,sl,rp) ;
}
inline int cfoct(cchar *sp,int sl,ulong *rp) noex {
	return cfoctul(sp,sl,rp) ;
}
inline int cfoct(cchar *sp,int sl,ulonglong *rp) noex {
	return cfoctull(sp,sl,rp) ;
}

#endif /* __cplusplus */


#endif /* CFOCT_INCLUDE */


