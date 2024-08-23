/* intceil HEADER */
/* lang=C20 */

/* Integer-Ceiling */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	INTCEIL_INCLUDE
#define	INTCEIL_INCLUDE 


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>		/* |off_t| + |size_t| */
#include	<stdint.h>		/* |intptr_t| + |uintptr_t| */
#include	<utypedefs.h>
#include	<clanguage.h>
#include	<stdintx.h>


EXTERNC_begin

extern int		iceil(int,int) noex ;
extern long		lceil(long,int) noex ;
extern longlong		llceil(longlong,int) noex ;
extern off_t		ofceil(off_t,int) noex ;
extern intptr_t		ipceil(intptr_t,int) noex ;

extern uint		uceil(uint,int) noex ;
extern ulong		ulceil(ulong,int) noex ;
extern ulonglong	ullceil(ulonglong,int) noex ;
extern size_t		szceil(size_t,int) noex ;
extern uintptr_t	uipceil(uintptr_t,int) noex ;

EXTERNC_end

#ifdef	__cplusplus

inline int ceil(int v,int m) noex {
	return iceil(v,m) ;
}
inline long ceil(long v,int m) noex {
	return lceil(v,m) ;
}
inline longlong ceil(longlong v,int m) noex {
	return llceil(v,m) ;
}
inline off_t ceil(off_t v,int m) noex {
	return ofceil(v,m) ;
}

#ifdef	COMMENT
inline intptr_t ceil(intptr_t v,int m) noex {
	return ipceil(v,m) ;
}
#endif /* COMMENT */

inline uint ceil(uint v,int m) noex {
	return uceil(v,m) ;
}
inline ulong ceil(ulong v,int m) noex {
	return ulceil(v,m) ;
}
inline ulonglong ceil(ulonglong v,int m) noex {
	return ullceil(v,m) ;
}

#ifdef	COMMENT
inline size_t ceil(size_t v,int m) noex {
	return szceil(v,m) ;
}
inline uintptr_t ceil(uintptr_t v,int m) noex {
	return uipceil(v,m) ;
}
#endif /* COMMENT */

#endif /* __cplusplus */


#endif /* INTCEIL_INCLUDE */


