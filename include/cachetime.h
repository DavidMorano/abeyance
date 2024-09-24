/* cachetime HEADER */
/* lang=C20 */

/* cache-time manager */
/* version %I% last-modified %G% */


/* revision history:

	= 2004-09-10, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2004 David A­D­ Morano.  All rights reserved. */

#ifndef	CACHETIME_INCLUDE
#define	CACHETIME_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<hdb.h>
#include	<ptm.h>


#define	CACHETIME_MAGIC		0x79854123
#define	CACHETIME_NENTS		400
#define	CACHETIME		struct cachetime_head
#define	CACHETIME_CUR		struct cachetime_cursor
#define	CACHETIME_ENT		struct cachetime_entry
#define	CACHETIME_ST		struct cachetime_statistics


struct cachetime_statistics {
	uint		req ;
	uint		hit ;
	uint		miss ;
} ;

struct cachetime_cursor {
	hdb_cur		*hcp ;
} ;

struct cachetime_entry {
	cchar		*name ;
	time_t		mtime ;
} ;

struct cachetime_head {
	hdb		*dbp ;
	ptm		*mxp ;
	uint		magic ;
	uint		c_req ;
	uint		c_hit ;
	uint		c_miss ;
} ;

typedef CACHETIME		cachetime ;
typedef CACHETIME_CUR		cachetime_cur ;
typedef CACHETIME_ENT		cachetime_ent ;
typedef CACHETIME_ST		cachetime_st ;

EXTERNC_begin

extern int cachetime_start(cachetime *) noex ;
extern int cachetime_lookup(cachetime *,cchar *,int,time_t *) noex ;
extern int cachetime_curbegin(cachetime *,cachetime_cur *) noex ;
extern int cachetime_curend(cachetime *,cachetime_cur *) noex ;
extern int cachetime_enum(cachetime *,cachetime_cur *,char *,int,
		time_t *) noex ;
extern int cachetime_stats(cachetime *,cachetime_st *) noex ;
extern int cachetime_finish(cachetime *) noex ;

EXTERNC_end


#endif /* CACHETIME_INCLUDE */


