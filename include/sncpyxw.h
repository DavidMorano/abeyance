/* sncpyxw HEADER */
/* lang=C20 */

/* copy a c-string to a given case */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	SNCPYXW_INCLUDE
#define	SNCPYXW_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern int sncpyxw(char *,int,int,...) noex ;

extern int sncpy1w(char *,int,ccp,int) noex ;
extern int sncpy2w(char *,int,ccp,ccp,int) noex ;
extern int sncpy3w(char *,int,ccp,ccp,ccp,int) noex ;
extern int sncpy4w(char *,int,ccp,ccp,ccp,ccp,int) noex ;
extern int sncpy5w(char *,int,ccp,ccp,ccp,ccp,ccp,int) noex ;
extern int sncpy6w(char *,int,ccp,ccp,ccp,ccp,ccp,ccp,int) noex ;

EXTERNC_end

#ifdef	__cplusplus

inline int sncpyw(char *dp,int dl,cc *s1,int sl) noex {
	return sncpyxw(dp,dl,1,s1,sl) ;
}
inline int sncpyw(char *dp,int dl,cc *s1,cc *s2,int sl) noex {
	return sncpyxw(dp,dl,2,s1,s2,sl) ;
}
inline int sncpyw(char *dp,int dl,cc *s1,cc *s2,cc *s3,int sl) noex {
	return sncpyxw(dp,dl,3,s1,s2,s3,sl) ;
}
inline int sncpyw(char *dp,int dl,cc *s1,cc *s2,cc *s3,cc *s4,int sl) noex {
	return sncpyxw(dp,dl,4,s1,s2,s3,s4,sl) ;
}
inline int sncpyw(char *dp,int dl,cc *s1,cc *s2,cc *s3,cc *s4,
		cc *s5,int sl) noex {
	return sncpyxw(dp,dl,5,s1,s2,s3,s4,s5,sl) ;
}
inline int sncpyw(char *dp,int dl,cc *s1,cc *s2,cc *s3,cc *s4,
		cc *s5,cc *s6,int sl) noex {
	return sncpyxw(dp,dl,6,s1,s2,s3,s4,s5,s6,sl) ;
}

#endif /* __cplusplus */


#endif /* SNCPYXW_INCLUDE */


