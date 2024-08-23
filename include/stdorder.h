/* stdorder HEADER */
/* lang=C20 */

/* standard byte-order serializations */
/* version %I% last-modified %G% */


/* revision history:

	= 2001-03-24, David A­D­ Morano
	This code is newly written but modeled after some code that
	was originally written to get some standardized variable
	serialization for the Ethernet-Controller (ETHCON) development
	work.

*/

/* Copyright © 2001 David A­D­ Morano.  All rights reserved. */

#ifndef	STDORDER_INCLUDE
#define	STDORDER_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<stdintx.h>


EXTERNC_begin

extern int stdorder_rc(cchar *,char *) noex ;
extern int stdorder_rs(cchar *,short *) noex ;
extern int stdorder_ri(cchar *,int *) noex ;
extern int stdorder_rl(cchar *,long *) noex ;
extern int stdorder_rll(cchar *,longlong *) noex ;

extern int stdorder_ruc(cchar *,uchar *) noex ;
extern int stdorder_rus(cchar *,ushort *) noex ;
extern int stdorder_rui(cchar *,uint *) noex ;
extern int stdorder_rul(cchar *,ulong *) noex ;
extern int stdorder_rull(cchar *,ulonglong *) noex ;

extern int stdorder_wc(char *,char) noex ;
extern int stdorder_ws(char *,short) noex ;
extern int stdorder_wi(char *,int) noex ;
extern int stdorder_wl(char *,long) noex ;
extern int stdorder_wll(char *,longlong) noex ;

extern int stdorder_wuc(char *,uchar) noex ;
extern int stdorder_wus(char *,ushort) noex ;
extern int stdorder_wui(char *,uint) noex ;
extern int stdorder_wul(char *,ulong) noex ;
extern int stdorder_wull(char *,ulonglong) noex ;

EXTERNC_end

#ifdef	__cplusplus

inline int stdorder_r(cchar *sp,char *rp) noex {
	return stdorder_rc(sp,rp) ;
}
inline int stdorder_r(cchar *sp,short *rp) noex {
	return stdorder_rs(sp,rp) ;
}
inline int stdorder_r(cchar *sp,int *rp) noex {
	return stdorder_ri(sp,rp) ;
}
inline int stdorder_r(cchar *sp,long *rp) noex {
	return stdorder_rl(sp,rp) ;
}
inline int stdorder_r(cchar *sp,longlong *rp) noex {
	return stdorder_rll(sp,rp) ;
}

inline int stdorder_r(cchar *sp,uchar *rp) noex {
	return stdorder_ruc(sp,rp) ;
}
inline int stdorder_r(cchar *sp,ushort *rp) noex {
	return stdorder_rus(sp,rp) ;
}
inline int stdorder_r(cchar *sp,uint *rp) noex {
	return stdorder_rui(sp,rp) ;
}
inline int stdorder_r(cchar *sp,ulong *rp) noex {
	return stdorder_rul(sp,rp) ;
}
inline int stdorder_r(cchar *sp,ulonglong *rp) noex {
	return stdorder_rull(sp,rp) ;
}

inline int stdorder_w(char *bp,char v) noex {
	return stdorder_wc(bp,v) ;
}
inline int stdorder_w(char *bp,short v) noex {
	return stdorder_ws(bp,v) ;
}
inline int stdorder_w(char *bp,int v) noex {
	return stdorder_wi(bp,v) ;
}
inline int stdorder_w(char *bp,long v) noex {
	return stdorder_wl(bp,v) ;
}
inline int stdorder_w(char *bp,longlong v) noex {
	return stdorder_wll(bp,v) ;
}

inline int stdorder_w(char *bp,uchar uv) noex {
	return stdorder_wuc(bp,uv) ;
}
inline int stdorder_w(char *bp,ushort uv) noex {
	return stdorder_wus(bp,uv) ;
}
inline int stdorder_w(char *bp,uint uv) noex {
	return stdorder_wui(bp,uv) ;
}
inline int stdorder_w(char *bp,ulong uv) noex {
	return stdorder_wul(bp,uv) ;
}
inline int stdorder_w(char *bp,ulonglong uv) noex {
	return stdorder_wull(bp,uv) ;
}

#endif /* __cplusplus */


#endif /* STDORDER_INCLUDE */


