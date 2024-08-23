/* sview HEADER */
/* lang=C20 */

/* string-view */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	SVIEW_INCLUDE
#define	SVIEW_INCLUDE
#ifdef	__cplusplus


#include	<envstandards.h>	/* MUST be first to configure */
#include	<cstring>		/* |strlen(3c)| */
#include	<utypedefs.h>
#include	<clanguage.h>


struct sview {
	cchar		*sp ;
	int		sl ;
	constexpr sview() noex : sp(nullptr), sl(0) { } ;
	constexpr sview(cchar *p,int l) noex : sp(p), sl(l) { 
	   if (l < 0) sl = strlen(p) ;
	} ;
	constexpr sview(const sview &o) noex {
	    sp = o.sp ;
	    sl = o.sl ;
	} ;
	constexpr sview(const sview *op) noex {
	    sp = op->sp ;
	    sl = op->sl ;
	} ;
	constexpr const sview &operator = (const sview &o) noex {
	    sp = o.sp ;
	    sl = o.sl ;
	    return *this ;
	} ;
	constexpr const sview &operator = (cchar *op) noex {
	    sp = op  ;
	    sl = strlen(op) ;
	    return *this ;
	} ;
} ; /* end struct (sview) */


#endif /* __cplusplus */
#endif /* SVIEW_UNCLUDE */


