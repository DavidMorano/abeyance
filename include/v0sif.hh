/* sif HEADER */
/* lang=C++20 */

/* string-interate-find object */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	SIF_INCLUDE
#define	SIF_INCLUDE
#ifdef	__cplusplus


#include	<envstandards.h>	/* ordered first to configure */
#include	<cstring>		/* |strlen(3c)| */
#include	<utypedefs.h>
#include	<clanguage.h>


struct sif {
	cchar		*sp ;
	cchar		*sstr = nullptr ;
	int		sl ;
	int		sch = 0 ;
	sif(cchar *p,int l = -1,int c = 0) noex : sp(p), sl(l), sch(c) { 
	} ;
	sif(cchar *p,int l,cchar *s) noex : sp(p), sl(l) { 
	    sstr = s ;
	} ;
	int next(cchar **) noex ;
	int nextchr(cchar **) noex ;
	int nextbrk(cchar **) noex ;
	int chr(cchar **) noex ;
	int brk(cchar **) noex ;
	int operator () (cchar **rpp) noex ;
} ; /* end struct (sif) */


#endif /* __cplusplus */
#endif /* SIF_INCLUDE */


