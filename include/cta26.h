/* cta26 HEADER */
/* lang=C20 */

/* subroutines to convert an integer to a base-26 string */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	CTA26_INCLUDE
#define	CTA26_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<stdintx.h>


EXTERNC_begin

extern int cta26i(char *,int,int,int,int) noex ;
extern int cta26l(char *,int,int,int,long) noex ;
extern int cta26ll(char *,int,int,int,longlong) noex ;

extern int cta26ui(char *,int,int,int,uint) noex ;
extern int cta26ul(char *,int,int,int,ulong) noex ;
extern int cta26ull(char *,int,int,int,ulonglong) noex ;

EXTERNC_end

#ifdef	__cplusplus

inline int cta26(char *bp,int bl,int t,int p,int v) noex {
	return cta26i(bp,bl,t,p,v) ;
}
inline int cta26(char *bp,int bl,int t,int p,long v) noex {
	return cta26l(bp,bl,t,p,v) ;
}
inline int cta26(char *bp,int bl,int t,int p,longlong v) noex {
	return cta26ll(bp,bl,t,p,v) ;
}

inline int cta26(char *bp,int bl,int t,int p,uint uv) noex {
	return cta26ui(bp,bl,t,p,uv) ;
}
inline int cta26(char *bp,int bl,int t,int p,ulong uv) noex {
	return cta26ul(bp,bl,t,p,uv) ;
}
inline int cta26(char *bp,int bl,int t,int p,ulonglong uv) noex {
	return cta26ull(bp,bl,t,p,uv) ;
}

#endif /* __cplusplus */


#endif /* CTA26_INCLUDE */


