/* ctdecp HEADER */
/* lang=C20 */

/* subroutines to convert an integer to a decimal string /w precision */
/* version %I% last-modified %G% */


/* revision history:

	= 2004-03-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 2004 David A­D­ Morano.  All rights reserved. */

#ifndef	CTDECP_INCLUDE
#define	CTDECP_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<stdintx.h>


EXTERNC_begin

extern int	ctdecpi(char *,int,int,int) noex ;
extern int	ctdecpl(char *,int,int,long) noex ;
extern int	ctdecpll(char *,int,int,longlong) noex ;

extern int	ctdecpui(char *,int,int,uint) noex ;
extern int	ctdecpul(char *,int,int,ulong) noex ;
extern int	ctdecpull(char *,int,int,ulonglong) noex ;

EXTERNC_end

#ifdef	__cplusplus

template<typename T>
inline int ctdecp(char *,int,int,T) noex {
	return 0 ;
}

template<>
inline int ctdecp(char *dp,int dl,int p,int v) noex {
	return ctdecpi(dp,dl,p,v) ;
}

template<>
inline int ctdecp(char *dp,int dl,int p,long v) noex {
	return ctdecpl(dp,dl,p,v) ;
}

template<>
inline int ctdecp(char *dp,int dl,int p,longlong v) noex {
	return ctdecpll(dp,dl,p,v) ;
}

template<>
inline int ctdecp(char *dp,int dl,int p,uint v) noex {
	return ctdecpui(dp,dl,p,v) ;
}

template<>
inline int ctdecp(char *dp,int dl,int p,ulong v) noex {
	return ctdecpul(dp,dl,p,v) ;
}

template<>
inline int ctdecp(char *dp,int dl,int p,ulonglong v) noex {
	return ctdecpull(dp,dl,p,v) ;
}

#endif /* __cplusplus */


#endif /* CTDECP_INCLUDE */


