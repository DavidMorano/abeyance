/* ctroman HEADER */
/* lang=C11 */

/* convert to Roman-Numerals */
/* version %I% last-modified %G% */


/* revision history:

	= 2017-08-15, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 2017 David A­D­ Morano.  All rights reserved. */

#ifndef	CTROMAN_INCLUDE
#define	CTROMAN_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<stdintx.h>


EXTERNC_begin

extern int ctromani(char *,int,int) noex ;
extern int ctromanl(char *,int,long) noex ;
extern int ctromanll(char *,int,longlong) noex ;

extern int ctromanui(char *,int,uint) noex ;
extern int ctromanul(char *,int,ulong) noex ;
extern int ctromanull(char *,int,ulonglong) noex ;

EXTERNC_end

#ifdef	__cplusplus

template<typename T>
inline int ctroman(char *,int,T) noex {
	return SR_NOSYS ;
}

template<>
inline int ctroman(char *dp,int dl,int v) noex {
	return ctromani(dp,dl,v) ;
}

template<>
inline int ctroman(char *dp,int dl,long v) noex {
	return ctromanl(dp,dl,v) ;
}

template<>
inline int ctroman(char *dp,int dl,longlong v) noex {
	return ctromanll(dp,dl,v) ;
}

template<>
inline int ctroman(char *dp,int dl,uint v) noex {
	return ctromanui(dp,dl,v) ;
}

template<>
inline int ctroman(char *dp,int dl,ulong v) noex {
	return ctromanul(dp,dl,v) ;
}

template<>
inline int ctroman(char *dp,int dl,ulonglong v) noex {
	return ctromanull(dp,dl,v) ;
}

#endif /* __cplusplus */


#endif /* CTROMAN_INCLUDE */


