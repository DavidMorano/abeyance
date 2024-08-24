/* ucstrtox HEADER */
/* lang=C20 */

/* interface component for UNIX® library-3c */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UCSTRTOX_INCLUDE
#define	UCSTRTOX_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<stdintx.h>


EXTERNC_begin

extern int uc_strtoi(cchar *,cchar **,int,int *) noex ;
extern int uc_strtol(cchar *,cchar **,int,long *) noex ;
extern int uc_strtoll(cchar *,cchar **,int,longlong *) noex ;
extern int uc_strtoui(cchar *,cchar **,int,uint *) noex ;
extern int uc_strtoul(cchar *,cchar **,int,ulong *) noex ;
extern int uc_strtoull(cchar *,cchar **,int,ulonglong *) noex ;

EXTERNC_end

#ifdef	__cplusplus

inline int uc_strto(cchar *sp,cchar **endpp,int b,int *rp) noex {
	return uc_strtoi(sp,endpp,b,rp) ;
}
inline int uc_strto(cchar *sp,cchar **endpp,int b,long *rp) noex {
	return uc_strtol(sp,endpp,b,rp) ;
}
inline int uc_strto(cchar *sp,cchar **endpp,int b,longlong *rp) noex {
	return uc_strtoll(sp,endpp,b,rp) ;
}
inline int uc_strto(cchar *sp,cchar **endpp,int b,uint *rp) noex {
	return uc_strtoui(sp,endpp,b,rp) ;
}
inline int uc_strto(cchar *sp,cchar **endpp,int b,ulong *rp) noex {
	return uc_strtoul(sp,endpp,b,rp) ;
}
inline int uc_strto(cchar *sp,cchar **endpp,int b,ulonglong *rp) noex {
	return uc_strtoull(sp,endpp,b,rp) ;
}

#endif /* __cplusplus */


#endif /* UCSTRTOX_INCLUDE */


