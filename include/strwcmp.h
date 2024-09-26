/* strwcmp HEADER */
/* lang=C20 */

/* string-comparison variant */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	STRWCMP_INCLUDE
#define	STRWCMP_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>


EXTERNC_begin

extern int strwbasecmp(cchar *,cchar *,int) noex ;
extern int strwcasecmp(cchar *,cchar *,int) noex ;
extern int strwfoldcmp(cchar *,cchar *,int) noex ;

static inline int strwcmp(cchar *bs,cchar *sp,int sl) noex {
	return strwbasecmp(bs,sp,sl) ;
}

static inline int strwbasecmpo(cchar *s1,cchar *s2,int len) noex {
	return strwbasecmp(s1,s2,len) ;
}
static inline int strwbasecmpr(cchar *s1,cchar *s2,int len) noex {
	return strwbasecmp(s2,s1,len) ;
}

static inline int strwcasecmpo(cchar *s1,cchar *s2,int len) noex {
	return strwcasecmp(s1,s2,len) ;
}
static inline int strwcasecmpr(cchar *s1,cchar *s2,int len) noex {
	return strwcasecmp(s2,s1,len) ;
}

static inline int strwfoldcmpo(cchar *s1,cchar *s2,int len) noex {
	return strwfoldcmp(s1,s2,len) ;
}
static inline int strwfoldcmpr(cchar *s1,cchar *s2,int len) noex {
	return strwfoldcmp(s2,s1,len) ;
}

EXTERNC_end

#ifdef	__cplusplus

inline int strwcmpo(cchar *s1,cchar *s2,int len) noex {
	return strwbasecmp(s1,s2,len) ;
}
inline int strwcmpr(cchar *s1,cchar *s2,int len) noex {
	return strwbasecmp(s2,s1,len) ;
}

#else /* __cplusplus */

static inline int strwcmpo(cchar *s1,cchar *s2,int len) noex {
	return strwbasecmp(s1,s2,len) ;
}
static inline int strwcmpr(cchar *s1,cchar *s2,int len) noex {
	return strwbasecmp(s2,s1,len) ;
}

#endif /* __cplusplus */


#endif /* STRWCMP_INCLUDE */


