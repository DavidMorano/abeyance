/* linehist HEADER */
/* lang=C20 */

/* line history */
/* version %I% last-modified %G% */


/* revision history:

	= 2016-06-29, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	LINEHIST_INCLUDE
#define	LINEHIST_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<langstate.h>


#define	LINEHIST_MAGIC		0x13f3c203
#define	LINEHIST		struct linehist_head
#define	LINEHIST_LINE		struct linehist_line


struct linehist_head {
	langstate	ls ;
	void		*lvp ;		/* line history */
	uint		magic ;
	char		ss[2] ;		/* search-characters */
} ;

typedef LINEHIST	linehist ;

EXTERNC_begin

extern int linehist_start(linehist *,cchar *) noex ;
extern int linehist_proc(linehist *,int,cchar *,int) noex ;
extern int linehist_count(linehist *) noex ;
extern int linehist_get(linehist *,int,int *) noex ;
extern int linehist_finish(linehist *) noex ;

EXTERNC_end


#endif /* LINEHIST_INCLUDE */


