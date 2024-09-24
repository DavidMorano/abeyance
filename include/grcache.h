/* grcache HEADER */
/* lang=C20 */

/* GROUP cache */
/* version %I% last-modified %G% */


/* Copyright © 2004 David A­D­ Morano.  All rights reserved. */

#ifndef	GRCACHE_INCLUDE
#define	GRCACHE_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>		/* system types */
#include	<time.h>		/* |time_t| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<vechand.h>
#include	<cq.h>


#define	GRCACHE			struct grcache_head
#define	GRCACHE_ST		struct grcache_stats

#define	GRCACHE_MAGIC		0x98643162
#define	GRCACHE_DEFENTS		10
#define	GRCACHE_DEFMAX		20	/* default maximum entries */
#define	GRCACHE_DEFTTL		600	/* default time-to-live */
#define	GRCACHE_MAXFREE		4


struct grcache_stats {
	uint		nentries ;		/* number of current entries */
	uint		total ;			/* accesses */
	uint		refreshes ;		/* refreshes */
	uint		phits, pmisses ;	/* positive */
	uint		nhits, nmisses ;	/* negative */
} ;

struct grcache_head {
	cq		*flp ;		/* free-list-pointer */
	vechand		*rlp ;		/* record-list-pointer */
	time_t		ti_check ;
	GRCACHE_ST	s ;
	uint		magic ;
	uint		wcount ;
	int		ttl ;		/* time-to-live */
	int		nmax ;		/* maximum entries */
} ;

typedef	GRCACHE		grcache ;
typedef	GRCACHE_ST	grcache_st ;

EXTERNC_begin

extern int grcache_start(grcache *,int,int) noex ;
extern int grcache_lookname(grcache *,ucentgr *,char *,int,cchar *) noex ;
extern int grcache_lookgid(grcache *,ucentgr *,char *,int,gid_t) noex ;
extern int grcache_check(grcache *,time_t) noex ;
extern int grcache_stats(grcache *,grcache_st *) noex ;
extern int grcache_finish(grcache *) noex ;

EXTERNC_end


#endif /* GRCACHE_INCLUDE */


