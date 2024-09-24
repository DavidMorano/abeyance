/* pwcache HEADER */
/* lang=C20 */

/* password cache */
/* version %I% last-modified %G% */


/* Copyright © 2004 David A­D­ Morano.  All rights reserved. */

#ifndef	PWCACHE_INCLUDE
#define	PWCACHE_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>		/* |uid_t| */
#include	<usystem.h>
#include	<hdb.h>
#include	<pq.h>


#define	PWCACHE			struct pwcache_head
#define	PWCACHE_ST		struct pwcache_stats

#define	PWCACHE_MAGIC		0x98643168
#define	PWCACHE_DEFENTS		10	/* default entries */
#define	PWCACHE_DEFMAX		20	/* default maximum entries */
#define	PWCACHE_DEFTTL		600	/* default time-to-live */


struct pwcache_stats {
	uint		nentries ;		/* number of current entries */
	uint		total ;			/* accesses */
	uint		refreshes ;		/* refreshes */
	uint		phits, pmisses ;	/* positive */
	uint		nhits, nmisses ;	/* negative */
} ;

struct pwcache_head {
	hdb		*dbp ;
	pq		*lrup ;		/* least-recently-used */
	time_t		ti_check ;
	PWCACHE_ST	s ;
	uint		magic ;
	uint		wcount ;	/* write-count */
	int		ttl ;		/* time-to-live */
	int		nmax ;		/* maximum entries */
} ;

typedef	PWCACHE		pwcache ;
typedef PWCACHE_ST	pwcache_st ;

EXTERNC_begin

extern int pwcache_start(pwcache *,int,int) noex ;
extern int pwcache_lookup(pwcache *,ucentpw *,char *,int,cchar *) noex ;
extern int pwcache_uid(pwcache *,ucentpw *,char *,int,uid_t) noex ;
extern int pwcache_invalidate(pwcache *,cchar *) noex ;
extern int pwcache_check(pwcache *,time_t) noex ;
extern int pwcache_stats(pwcache *,pwcache_st *) noex ;
extern int pwcache_finish(pwcache *) noex ;

EXTERNC_end


#endif /* PWCACHE_INCLUDE */


