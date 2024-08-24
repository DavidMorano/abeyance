/* strdcpyxw HEADER */
/* lang=C20 */

/* string-copy variant */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	STRDCPYXW_INCLUDE
#define	STRDCPYXW_INCLUDE


#include	<envstandards.h>	/* first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern char *strdcpyxw(char *,int,int,...) noex ;

extern char *strdcpy1w(char *,int,cc *,int) noex ;
extern char *strdcpy2w(char *,int,cc *,cc *,int) noex ;
extern char *strdcpy3w(char *,int,cc *,cc *,cc *,int) noex ;
extern char *strdcpy4w(char *,int,cc *,cc *,cc *,cc *,int) noex ;
extern char *strdcpy5w(char *,int,cc *,cc *,cc *,cc *,cc *,int) noex ;
extern char *strdcpy6w(char *,int,cc *,cc *,cc *,cc *,cc *,cc *,int) noex ;

EXTERNC_end

#ifdef	__cplusplus

inline char *strdcpyw(char *dp,int dl,cc *s1,int sl) noex {
	return strdcpyxw(dp,dl,1,s1,sl) ;
}
inline char *strdcpyw(char *dp,int dl,cc *s1,cc *s2,int sl) noex {
	return strdcpyxw(dp,dl,2,s1,s2,sl) ;
}
inline char *strdcpyw(char *dp,int dl,cc *s1,cc *s2,cc *s3,int sl) noex {
	return strdcpyxw(dp,dl,3,s1,s2,s3,sl) ;
}
inline char *strdcpyw(char *dp,int dl,cc *s1,cc *s2,cc *s3,cc *s4,int sl) noex {
	return strdcpyxw(dp,dl,4,s1,s2,s3,s4,sl) ;
}
inline char *strdcpyw(char *dp,int dl,cc *s1,cc *s2,cc *s3,cc *s4,
		cc *s5,int sl) noex {
	return strdcpyxw(dp,dl,5,s1,s2,s3,s4,s5,sl) ;
}
inline char *strdcpyw(char *dp,int dl,cc *s1,cc *s2,cc *s3,cc *s4,
		cc *s5,cc *s6,int sl) noex {
	return strdcpyxw(dp,dl,6,s1,s2,s3,s4,s5,s6,sl) ;
}

#endif /* __cplusplus */


#endif /* STRDCPYXW_INCLUDE */


