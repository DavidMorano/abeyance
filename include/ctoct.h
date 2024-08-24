/* ctoct HEADER */
/* lang=C++20 */

/* subroutines to convert an integer to a OCTAL string */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	CTOCT_INCLUDE
#define	CTOCT_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<stdintx.h>


EXTERNC_begin

extern int ctocti(char *,int,int) noex ;
extern int ctoctl(char *,int,long) noex ;
extern int ctoctll(char *,int,longlong) noex ;

extern int ctoctui(char *,int,uint) noex ;
extern int ctoctul(char *,int,ulong) noex ;
extern int ctoctull(char *,int,ulonglong) noex ;

EXTERNC_end

#ifdef	__cplusplus

inline int ctoct(char *bp,int bl,int v) noex {
	return ctocti(bp,bl,v) ;
}
inline int ctoct(char *bp,int bl,long v) noex {
	return ctoctl(bp,bl,v) ;
}
inline int ctoct(char *bp,int bl,longlong v) noex {
	return ctoctll(bp,bl,v) ;
}

inline int ctoct(char *bp,int bl,uint v) noex {
	return ctoctui(bp,bl,v) ;
}
inline int ctoct(char *bp,int bl,ulong v) noex {
	return ctoctul(bp,bl,v) ;
}
inline int ctoct(char *bp,int bl,ulonglong v) noex {
	return ctoctull(bp,bl,v) ;
}

#endif /* __cplusplus */


#endif /* CTOCT_INCLUDE */


