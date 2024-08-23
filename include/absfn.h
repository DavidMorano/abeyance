/* absfn HEADER */
/* lang=C20 */

/* assert a NUL-terminated string */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	ABSFN_INCLUDE
#define	ABSFN_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<localmisc.h>


#define	ABSFN		struct absfn_head
#define	ABSFN_SHORTLEN	128		/* "string length optimization" */


struct absfn_head {
	cchar	*as ;	/* allocated string */
	char	buf[ABSFN_SHORTLEN+1] ;
} ;

#ifdef	__cplusplus
enum absfnmems {
	absfnmem_finish,
	absfnmem_overlast
} ;
struct absfn ;
struct absfn_co {
	absfn		*op = nullptr ;
	int		w = -1 ;
	void operator () (absfn *p,int m) noex {
	    op = p ;
	    w = m ;
	} ;
	operator int () noex ;
	int operator () () noex { 
	    return operator int () ;
	} ;
} ; /* end struct (absfn_co) */
struct absfn : absfn_head {
	absfn_co	finish ;
	absfn() noex {
	    finish(this,absfnmem_finish) ;
	} ;
	absfn(const absfn &) = delete ;
	absfn &operator = (const absfn &) = delete ;
	int start(cchar *sp,int sl,cchar **) noex ;
	~absfn() noex {
	    (void) int(finish) ;
	} ;
} ; /* end struct (absfn) */
#else /* __cplusplus */
typedef ABSFN		absfn ;
#endif /* __cplusplus */

EXTERNC_begin

extern int	absfn_start(absfn *,cchar *,int,cchar **) noex ;
extern int	absfn_finish(absfn *) noex ;

EXTERNC_end


#endif /* ABSFN_INCLUDE */


