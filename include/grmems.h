/* grmems HEADER */
/* lang=C++20 */

/* UNIX® group membership access and cache */
/* version %I% last-modified %G% */


/* revision history:

	= 2004-08-27, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2004 David A­D­ Morano.  All rights reserved. */

#ifndef	GRMEMS_INCLUDE
#define	GRMEMS_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<time.h>		/* |time_t| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<recarr.h>
#include	<pq.h>


#define	GRMEMS_MAGIC		0x98643169
#define	GRMEMS_CURMAGIC		0x9864316a
#define	GRMEMS			struct grmems_head
#define	GRMEMS_ST		struct grmems_statdata
#define	GRMEMS_CUR		struct grmems_cursor


struct grmems_cursor {
	uint		magic ;
	int		ri ;		/* record index */
	int		i ;		/* index through members */
} ;

struct grmems_statdata {
	uint		nentries ;		/* number of current entries */
	uint		total ;			/* accesses */
	uint		refreshes ;		/* refreshes */
	uint		phits, pmisses ;	/* positive */
	uint		nhits, nmisses ;	/* negative */
} ;

struct grmems_head {
	recarr		*recs ;		/* linear array (of recs) */
	pq		*lrup ;		/* least-recently-used */
	void		*usergids ;
	void		*mapdata ;
	size_t		mapsize ;
	time_t		ti_check ;
	time_t		ti_open ;
	time_t		ti_access ;
	time_t		ti_usergids ;
	GRMEMS_ST	s ;
	uint		magic ;
	uint		wcount ;	/* write-count */
	int		pagesize ;
	int		ttl ;		/* time-to-live */
	int		nmax ;		/* maximum entries */
	int		cursors ;	/* cursors outstanding */
	int		fd ;
	int		fsize ;
	int		nusergids ;
} ;

typedef GRMEMS		grmems ;
typedef GRMEMS_CUR	grmems_cur ;
typedef GRMEMS_ST	grmems_st ;

EXTERNC_begin

extern int grmems_start(grmems *,int,int) noex ;
extern int grmems_curbegin(grmems *,grmems_cur *) noex ;
extern int grmems_lookup(grmems *,grmems_cur *,cchar *,int) noex ;
extern int grmems_lookread(grmems *,grmems_cur *,char *,int) noex ;
extern int grmems_curend(grmems *,grmems_cur *) noex ;
extern int grmems_invalidate(grmems *,cchar *,int) noex ;
extern int grmems_check(grmems *,time_t) noex ;
extern int grmems_stats(grmems *,grmems_st *) noex ;
extern int grmems_finish(grmems *) noex ;

EXTERNC_end


#endif /* GRMEMS_INCLUDE */


