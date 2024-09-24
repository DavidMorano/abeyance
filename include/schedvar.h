/* schedvar HEADER */
/* lang=C20 */

/* creates the substitution varaiables for 'scheduled' type operations */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	SCHEDVAR_INCLUDE
#define	SCHEDVAR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<vecstr.h>


#define	SCHEDVAR	struct schedvar_head
#define	SCHEDVAR_CUR	struct schedvar_cursor
#define	SCHEDVAR_MAGIC	0x89362514


struct schedvar_cursor {
	int		i ;
} ;

struct schedvar_head {
	vecstr		*slp ;
	uint		magic ;
} ;

typedef	SCHEDVAR	schedvar ;
typedef	SCHEDVAR_CUR	schedvar_cur ;

EXTERNC_begin

extern int schedvar_start(schedvar *) noex ;
extern int schedvar_add(schedvar *,cchar *,cchar *,int) noex ;
extern int schedvar_curbegin(schedvar *,schedvar_cur *) noex ;
extern int schedvar_enum(schedvar *,schedvar_cur *,char *,int,char *,int) noex ;
extern int schedvar_curend(schedvar *,schedvar_cur *) noex ;
extern int schedvar_findkey(schedvar *,cchar *,cchar **) noex ;
extern int schedvar_del(schedvar *,cchar *) noex ;
extern int schedvar_expand(schedvar *,char *,int,cchar *,int) noex ;
extern int schedvar_finish(schedvar *) noex ;

EXTERNC_end


#endif /* SCHEDVAR_INCLUDE */


