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
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


enum sifmems {
	sifmem_iswhitechr,
	sifmem_iswhitestr,
	sifmem_isspanchr,
	sifmem_isspanstr,
	sifmem_overlast
} ;
struct sif ;
struct sif_co {
	sif		*op = nullptr ;
	int		w = -1 ;
	void operator () (sif *p,int m) noex {
	    op = p ;
	    w = m ;
	} ;
	operator bool () noex ;
} ;
struct sif {
	cchar		*sp ;
	cchar		*sstr = nullptr ;
	int		sl ;
	int		sch = 0 ;
	sif_co		iswhitechr ;
	sif_co		iswhitestr ;
	sif_co		isspanchr ;
	sif_co		isspanstr ;
	void sif_init() noex {
	    iswhitechr(this,sifmem_iswhitechr) ;
	    iswhitestr(this,sifmem_iswhitestr) ;
	    isspanchr(this,sifmem_isspanchr) ;
	    isspanstr(this,sifmem_isspanstr) ;
	} ;
	sif(cchar *p,int l = -1,int c = 0) noex : sp(p), sl(l), sch(c) { 
	    sif_init() ;
	} ;
	sif(cchar *p,int l,cchar *s) noex : sp(p), sl(l) { 
	    sif_init() ;
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


