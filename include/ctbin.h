/* ctbin HEADER */
/* lang=C20 */

/* subroutines to convert an integer to a binary-digit string */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	CTBIN_INCLUDE
#define	CTBIN_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<stdintx.h>


EXTERNC_begin

extern int ctbini(char *,int,int) noex ;
extern int ctbinl(char *,int,long) noex ;
extern int ctbinll(char *,int,longlong) noex ;

extern int ctbinui(char *,int,uint) noex ;
extern int ctbinul(char *,int,ulong) noex ;
extern int ctbinull(char *,int,ulonglong) noex ;

EXTERNC_end

#ifdef	__cplusplus

inline int ctbin(char *bp,int bl,int v) noex {
	return ctbini(bp,bl,v) ;
}
inline int ctbin(char *bp,int bl,long v) noex {
	return ctbinl(bp,bl,v) ;
}
inline int ctbin(char *bp,int bl,longlong v) noex {
	return ctbinll(bp,bl,v) ;
}

inline int ctbin(char *bp,int bl,uint v) noex {
	return ctbinui(bp,bl,v) ;
}
inline int ctbin(char *bp,int bl,ulong v) noex {
	return ctbinul(bp,bl,v) ;
}
inline int ctbin(char *bp,int bl,ulonglong v) noex {
	return ctbinull(bp,bl,v) ;
}

#endif /* __cplusplus */


#endif /* CTBIN_INCLUDE */


