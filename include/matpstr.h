/* matpstr HEADER */
/* lang=C20 */

/* Match a String */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright (c) 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MATPSTR_INCLUDE
#define	MATPSTR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<localmisc.h>


EXTERNC_begin

extern int matpbasestr(mainv,int,cchar *,int) noex ;
extern int matpcasestr(mainv,int,cchar *,int) noex ;
extern int matpfoldstr(mainv,int,cchar *,int) noex ;

EXTERNC_end

#ifdef	__cplusplus
inline int matpstr(mainv bs,int n,cchar *sp,int sl = -1) noex {
	return matpbasestr(bs,n,sp,sl) ;
}
#else
static inline int matpstr(mainv bs,int n,cchar *sp,int sl) noex {
	return matpbasestr(bs,n,sp,sl) ;
}
#endif /* __cplusplus */


#endif /* MATPSTR_INCLUDE */


