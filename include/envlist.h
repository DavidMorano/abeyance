/* envlist HEADER */
/* lang=C20 */

/* environment container */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	ENVLIST_INCLUDE
#define	ENVLIST_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>
#include	<hdb.h>


#define	ENVLIST			struct envlist_head
#define	ENVLIST_CHUNKSIZE	256


struct envlist_head {
	hdb		*elp ;
	void		*store ;	/* <- this is a STRPACK object */
} ;

typedef ENVLIST		envlist ;

EXTERNC_begin

extern int envlist_start(envlist *,int) noex ;
extern int envlist_addkeyval(envlist *,cchar *,cchar *,int) noex ;
extern int envlist_add(envlist *,cchar *,int) noex ;
extern int envlist_present(envlist *,cchar *,int,cchar **) noex ;
extern int envlist_count(envlist *) noex ;
extern int envlist_finish(envlist *) noex ;

EXTERNC_end


#endif /* ENVLIST_INCLUDE */


