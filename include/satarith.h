/* satarith HEADER */
/* lang=C20 */

/* Integer Saturation Addition */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#ifndef	SATARITH_INCLUDE
#define	SATARITH_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<stdintx.h>


EXTERNC_begin

extern int		iaddsat(int,int) noex ;
extern long		laddsat(long,long) noex ;
extern longlong		lladdsat(longlong,longlong) noex ;

extern uint		uiaddsat(uint,uint) noex ;
extern ulong		uladdsat(ulong,ulong) noex ;
extern ulonglong	ulladdsat(ulonglong,ulonglong) noex ;

EXTERNC_end

#ifdef	__cplusplus

extern int		addsat(int v1,int v2) noex {
	return iaddsat(v1,v2) ;
}
extern long		addsat(long v1,long v2) noex {
	return laddsat(v1,v2) ;
}
extern longlong		addsat(longlong v1,longlong v2) noex {
	return lladdsat(v1,v2) ;
}

extern uint		addsat(uint v1,uint v2) noex {
	return uiaddsat(v1,v2) ;
}
extern ulong		addsat(ulong v1,ulong v2) noex {
	return uladdsat(v1,v2) ;
}
extern ulonglong	addsat(ulonglong v1,ulonglong v2) noex {
	return ulladdsat(v1,v2) ;
}

#endif /* __cplusplus */


#endif /* SATARITH_INCLUDE */


