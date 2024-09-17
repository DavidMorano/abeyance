/* dirlist HEADER */
/* lang=C20 */

/* directory list manager */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-09-10, David A­D­ Morano
	I created this modeled after something similar that was
	used for some of my PCS programs ('bbnews' I think).

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#ifndef	DIRLIST_INCLUDE
#define	DIRLIST_INCLUDE 


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>
#include	<vecobj.h>


#define	DIRLIST		struct dirlist_head
#define	DIRLIST_CUR	struct dirlist_cursor
#define	DIRLIST_MAGIC	0x09854123


struct dirlist_cursor {
	int		i ;
} ;

struct dirlist_head {
	vecobj		*dbp ;
	uint		magic ;
	int		tlen ;
} ;

typedef DIRLIST		dirlist ;
typedef DIRLIST_CUR	dirlist_cur ;

EXTERNC_begin

extern int dirlist_start(dirlist *) noex ;
extern int dirlist_semi(dirlist *) noex ;
extern int dirlist_adds(dirlist *,cchar *,int) noex ;
extern int dirlist_add(dirlist *,cchar *,int) noex ;
extern int dirlist_strsize(dirlist *) noex ;
extern int dirlist_curbegin(dirlist *,dirlist_cur *) noex ;
extern int dirlist_curend(dirlist *,dirlist_cur *) noex ;
extern int dirlist_curenum(dirlist *,dirlist_cur *,char *,int) noex ;
extern int dirlist_curget(dirlist *,dirlist_cur *,cchar **) noex ;
extern int dirlist_join(dirlist *) noex ;
extern int dirlist_joinsize(dirlist *) noex ;
extern int dirlist_joinmk(dirlist *,char *,int) noex ;
extern int dirlist_finish(dirlist *) noex ;

EXTERNC_end


#endif /* DIRLIST_INCLUDE */


