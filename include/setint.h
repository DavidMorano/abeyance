/* setint HEADER */
/* lang=C++11 */

/* unordered set of integers */
/* version %I% last-modified %G% */


/* Copyright © 2013 David A­D­ Morano.  All rights reserved. */

#ifndef	SETINT_INCLUDE
#define	SETINT_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


#define	SETINT		struct setint_head
#define	SETINT_CUR	struct setint_cursor


struct setint_cursor {
	void		*interp ;
} ;

struct setint_head {
	void		*setp ;
} ;

typedef SETINT		setint ;
typedef SETINT_CUR	setint_cur ;

EXTERNC_begin

extern int setint_start(setint *) noex ;
extern int setint_finish(setint *) noex ;
extern int setint_addval(setint *,int) noex ;
extern int setint_delval(setint *,int) noex ;
extern int setint_count(setint *) noex ;
extern int setint_mkvec(setint *,int *) noex ;
extern int setint_extent(setint *) noex ;
extern int setint_curbegin(setint *,setint_cur *) noex ;
extern int setint_enum(setint *,setint_cur *,int *) noex ;
extern int setint_curend(setint *,setint_cur *) noex ;
extern int setint_find(setint *,int) noex ;

EXTERNC_end


#endif /* SETINT_INCLUDE */


