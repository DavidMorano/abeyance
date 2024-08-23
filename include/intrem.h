/* intrem HEADER */
/* lang=C20 */

/* Integer-Remaider */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#ifndef	INTREM_INCLUDE
#define	INTREM_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern int		irem(int,int) noex ;
extern long		lrem(long,int) noex ;
extern longlong		llrem(longlong,int) noex ;
extern uint		uirem(uint,int) noex ;
extern ulong		ulrem(ulong,int) noex ;
extern ulonglong	ullrem(ulonglong,int) noex ;

EXTERNC_end

#ifdef	__cplusplus

static inline int rem(int v,int d) noex {
	return irem(v,d) ;
}
static inline long rem(long v,int d) noex {
	return lrem(v,d) ;
}
static inline longlong rem(longlong v,int d) noex {
	return llrem(v,d) ;
}

static inline uint rem(uint v,int d) noex {
	return uirem(v,d) ;
}
static inline ulong rem(ulong v,int d) noex {
	return ulrem(v,d) ;
}
static inline ulonglong rem(ulonglong v,int d) noex {
	return ullrem(v,d) ;
}

#endif /* __cplusplus */


#endif /* INTREM_INCLUDE */


