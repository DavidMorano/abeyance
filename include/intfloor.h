/* intfloor HEADER */
/* lang=C20 */

/* Integer-Flooring */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#ifndef	INTFLOOR_INCLUDE
#define	INTFLOOR_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>		/* |off_t| + |size_t| */
#include	<stdint.h>		/* |intptr_t| + |uintptr_t| */
#include	<utypedefs.h>
#include	<clanguage.h>
#include	<stdintx.h>


EXTERNC_begin

extern int		ifloor(int,int) noex ;
extern long		lfloor(long,int) noex ;
extern longlong		llfloor(longlong,int) noex ;
extern off_t		offloor(off_t,int) noex ;
extern intptr_t		ipfloor(intptr_t,int) noex ;

extern uint		ufloor(uint,int) noex ;
extern ulong		ulfloor(ulong,int) noex ;
extern ulonglong	ullfloor(ulonglong,int) noex ;
extern size_t		szfloor(size_t,int) noex ;
extern uintptr_t	uipfloor(uintptr_t,int) noex ;

EXTERNC_end

#ifdef	__cplusplus

inline int floor(int v,int m) noex {
	return ifloor(v,m) ;
}
inline long floor(long v,int m) noex {
	return lfloor(v,m) ;
}
inline longlong floor(longlong v,int m) noex {
	return llfloor(v,m) ;
}
inline off_t floor(off_t v,int m) noex {
	return offloor(v,m) ;
}

#ifdef	COMMENT
inline intptr_t floor(intptr_t v,int m) noex {
	return ipfloor(v,m) ;
}
#endif /* COMMENT */

inline uint floor(uint v,int m) noex {
	return ufloor(v,m) ;
}
inline ulong floor(ulong v,int m) noex {
	return ulfloor(v,m) ;
}
inline ulonglong floor(ulonglong v,int m) noex {
	return ullfloor(v,m) ;
}

#ifdef	COMMENT
inline size_t floor(size_t v,int m) noex {
	return szfloor(v,m) ;
}
inline uintptr_t floor(uintptr_t v,int m) noex {
	return uipfloor(v,m) ;
}
#endif /* COMMENT */

#endif /* __cplusplus */


#endif /* INTFLOOR_INCLUDE */


