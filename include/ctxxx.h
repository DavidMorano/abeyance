/* ctxxx HEADER */
/* lang=C20 */

/* subroutines to convert an integer to a decimal string */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-01, David A­D­ Morano
	This subroutine was written having been adapated (from
	memory) from something I wrote back in the early 1980s (for
	embedded work).  I had to write every ... last  ... thing
	myself back in the old days.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	CTXXX_INCLUDE
#define	CTXXX_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<stdintx.h>


EXTERNC_begin

extern int ctxxxi(char *,int,int,int) noex ;
extern int ctxxxl(char *,int,int,long) noex ;
extern int ctxxxll(char *,int,int,longlong) noex ;

extern int ctxxxui(char *,int,int,uint) noex ;
extern int ctxxxul(char *,int,int,ulong) noex ;
extern int ctxxxull(char *,int,int,ulonglong) noex ;

EXTERNC_end

#ifdef	__cplusplus

inline int ctxxx(char *bp,int bl,int b,int v) noex {
	return ctxxxi(bp,bl,b,v) ;
}
inline int ctxxx(char *bp,int bl,int b,long v) noex {
	return ctxxxl(bp,bl,b,v) ;
}
inline int ctxxx(char *bp,int bl,int b,longlong v) noex {
	return ctxxxll(bp,bl,b,v) ;
}

inline int ctxxx(char *bp,int bl,int b,uint v) noex {
	return ctxxxui(bp,bl,b,v) ;
}
inline int ctxxx(char *bp,int bl,int b,ulong v) noex {
	return ctxxxul(bp,bl,b,v) ;
}
inline int ctxxx(char *bp,int bl,int b,ulonglong v) noex {
	return ctxxxull(bp,bl,b,v) ;
}

#endif /* __cplusplus */


#endif /* CTXXX_INCLUDE */


