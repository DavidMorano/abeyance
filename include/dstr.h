/* dstr HEADER */
/* lang=C20 */

/* dynamic (allocated) string object */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	DSTR_INCLUDE
#define	DSTR_INCLUDE


#include	<envstandards.h>	/* first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


#define	DSTR		struct dstr_head


struct dstr_head {
	char		*sbuf ;
	int		slen ;
} ;

typedef DSTR		dstr ;

EXTERNC_begin

extern int dstr_start(dstr *,cchar *,int) noex ;
extern int dstr_assign(dstr *,dstr *) noex ;
extern int dstr_finish(dstr *) noex ;

EXTERNC_end


#endif /* DSTR_INCLUDE */


