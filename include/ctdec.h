/* ctdec HEADER */
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

#ifndef	CTDEC_INCLUDE
#define	CTDEC_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<stdintx.h>
#include	<ctdecp.h>		/* <- extra convenience */


EXTERNC_begin

extern int ctdeci(char *,int,int) noex ;
extern int ctdecl(char *,int,long) noex ;
extern int ctdecll(char *,int,longlong) noex ;

extern int ctdecui(char *,int,uint) noex ;
extern int ctdecul(char *,int,ulong) noex ;
extern int ctdecull(char *,int,ulonglong) noex ;

EXTERNC_end

#ifdef	__cplusplus

inline int ctdec(char *bp,int bl,int v) noex {
	return ctdeci(bp,bl,v) ;
}
inline int ctdec(char *bp,int bl,long v) noex {
	return ctdecl(bp,bl,v) ;
}
inline int ctdec(char *bp,int bl,longlong v) noex {
	return ctdecll(bp,bl,v) ;
}

inline int ctdec(char *bp,int bl,uint v) noex {
	return ctdecui(bp,bl,v) ;
}
inline int ctdec(char *bp,int bl,ulong v) noex {
	return ctdecul(bp,bl,v) ;
}
inline int ctdec(char *bp,int bl,ulonglong v) noex {
	return ctdecull(bp,bl,v) ;
}

#endif /* __cplusplus */


#endif /* CTDEC_INCLUDE */


