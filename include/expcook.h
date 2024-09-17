/* expcook HEADER */
/* lang=C20 */

/* Expand-Cookie - creates the substitution variables for cookie escapes */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-09-01, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	EXPCOOK_INCLUDE
#define	EXPCOOK_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<hdbstr.h>
#include	<buffer.h>


#define	EXPCOOK		struct expcook_head
#define	EXPCOOK_CUR	struct expcook_cursor
#define	EXPCOOK_MAGIC	0x75837393


struct expcook_cursor {
	hdbstr_cur	*clp ;
} ;

struct expcook_head {
	hdbstr		*hlp ;
	uint		magic ;
} ;

typedef EXPCOOK		expcook ;
typedef EXPCOOK_CUR	expcook_cur ;

EXTERNC_begin

extern int expcook_start(expcook *) noex ;
extern int expcook_add(expcook *,cchar *,cchar *,int) noex ;
extern int expcook_curbegin(expcook *,expcook_cur *) noex ;
extern int expcook_curend(expcook *,expcook_cur *) noex ;
extern int expcook_enum(expcook *,expcook_cur *,char *,int) noex ;
extern int expcook_findkey(expcook *,cchar *,int,cchar **) noex ;
extern int expcook_delkey(expcook *,cchar *) noex ;
extern int expcook_exp(expcook *,int,char *,int,cchar *,int) noex ;
extern int expcook_expbuf(expcook *,int,buffer *,cchar *,int) noex ;
extern int expcook_finish(expcook *) noex ;

EXTERNC_end


#endif /* EXPCOOK_INCLUDE */


