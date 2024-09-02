/* nulstr HEADER */
/* lang=C20 */

/* assert a NUL-terminated string */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	NULSTR_INCLUDE
#define	NULSTR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<localmisc.h>


#define	NULSTR		struct nulstr_head
#define	NULSTR_SHORTLEN	128		/* "string length optimization" */


struct nulstr_head {
	cchar	*as ;	/* allocated string */
	char	buf[NULSTR_SHORTLEN+1] ;
} ;

#ifdef	__cplusplus
enum nulstrmems {
	nulstrmem_finish,
	nulstrmem_overlast
} ;
struct nulstr ;
struct nulstr_co {
	nulstr		*op = nullptr ;
	int		w = -1 ;
	void operator () (nulstr *p,int m) noex {
	    op = p ;
	    w = m ;
	} ;
	operator int () noex ;
	int operator () () noex { 
	    return operator int () ;
	} ;
} ; /* end struct (nulstr_co) */
struct nulstr : nulstr_head {
	nulstr_co	finish ;
	nulstr() noex {
	    finish(this,nulstrmem_finish) ;
	} ;
	nulstr(const nulstr &) = delete ;
	nulstr &operator = (const nulstr &) = delete ;
	int start(cchar *sp,int sl,cchar **) noex ;
	~nulstr() noex {
	    (void) int(finish) ;
	} ;
} ; /* end struct (nulstr) */
#else /* __cplusplus */
typedef NULSTR		nulstr ;
#endif /* __cplusplus */

EXTERNC_begin

extern int	nulstr_start(nulstr *,cchar *,int,cchar **) noex ;
extern int	nulstr_finish(nulstr *) noex ;

EXTERNC_end


#endif /* NULSTR_INCLUDE */


