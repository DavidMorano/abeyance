/* osetint HEADER */
/* lang=C20 */

/* ordered set of integers */
/* version %I% last-modified %G% */


/* Copyright © 1999 David A­D­ Morano.  All rights reserved. */

#ifndef	OSETINT_INCLUDE
#define	OSETINT_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


#define	OSETINT		struct osetint_head
#define	OSETINT_CUR	struct osetint_cursor


struct osetint_cursor {
	void		*interp ;
} ;

struct osetint_head {
	void		*setp ;
} ;

typedef OSETINT		osetint ;
typedef OSETINT_CUR	osetint_cur ;

EXTERNC_begin

extern int osetint_start(osetint *) noex ;
extern int osetint_finish(osetint *) noex ;
extern int osetint_addval(osetint *,int) noex ;
extern int osetint_delval(osetint *,int) noex ;
extern int osetint_count(osetint *) noex ;
extern int osetint_mkvec(osetint *,int *) noex ;
extern int osetint_extent(osetint *) noex ;
extern int osetint_curbegin(osetint *,osetint_cur *) noex ;
extern int osetint_enum(osetint *,osetint_cur *,int *) noex ;
extern int osetint_curend(osetint *,osetint_cur *) noex ;
extern int osetint_find(osetint *,int) noex ;

EXTERNC_end


#endif /* OSETINT_INCLUDE */


