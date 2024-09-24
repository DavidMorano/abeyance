/* gncache HEADER */
/* lang=C20 */

/* group-name cache */
/* version %I% last-modified %G% */


/* revision history:

	= 2004-01-10, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 2004 David A­D­ Morano.  All rights reserved. */

#ifndef	GNCACHE_INCLUDE
#define	GNCACHE_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>		/* system-types */
#include	<time.h>		/* |time_t| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<vechand.h>
#include	<cq.h>
#include	<localmisc.h>		/* |GROUPNAMELEN| */


#define	GNCACHE			struct gncache_head
#define	GNCACHE_ST		struct gncache_stats

#define	GNCACHE_MAGIC		0x98643162
#define	GNCACHE_DEFENT		10
#define	GNCACHE_DEFMAX		20	/* default maximum entries */
#define	GNCACHE_DEFTTL		600	/* default time-to-live */
#define	GNCACHE_MAXFREE		4


struct gncache_stats {
	uint		nentries ;
	uint		total ;			/* access */
	uint		refreshes ;
	uint		phits, pmisses ;	/* positive */
	uint		nhits, nmisses ;	/* negative */
} ;

struct gncache_head {
	cq		*flp ;
	vechand		*rlp ;
	time_t		ti_check ;
	GNCACHE_ST	s ;
	uint		magic ;
	int		ttl ;		/* time-to-live in seconds */
	int		nmax ;		/* maximum entries */
} ;

typedef	GNCACHE		gncache ;
typedef	GNCACHE_ST	gncache_st ;

EXTERNC_begin

extern int gncache_start(gncache *,int,int) noex ;
extern int gncache_add(gncache *,gid_t,char *) noex ;
extern int gncache_lookgid(gncache *,char *,int,gid_t) noex ;
extern int gncache_check(gncache *,time_t) noex ;
extern int gncache_stats(gncache *,gncache_st *) noex ;
extern int gncache_finish(gncache *) noex ;

EXTERNC_end


#endif /* GNCACHE_INCLUDE */


