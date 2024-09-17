/* finduid HEADER */
/* lang=C20 */

/* find a username given a UID by various means */
/* version %I% last-modified %G% */


/* Copyright © 2004 David A­D­ Morano.  All rights reserved. */

#ifndef	FINDUID_INCLUDE
#define	FINDUID_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<time.h>		/* |time_t| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<ptm.h>
#include	<pwcache.h>
#include	<tmpx.h>


#define	FINDUID		struct finduid_head
#define	FINDUID_FL	struct finduid_flags
#define	FINDUID_ST	struct finduid_stats

#define	FINDUID_MAGIC	0x98643169
#define	FINDUID_DEFMAX	20	/* default maximum entries */
#define	FINDUID_DEFTTL	600	/* default time-to-live */


struct finduid_stats {
	uint		total ;		/* accesses */
	uint		refreshes ;	/* refreshes */
	uint		phits ;		/* positive hit */
	uint		nhits ;		/* negative hit */
} ;

struct finduid_flags {
	uint		ut:1 ;
} ;

struct finduid_head {
	ptm		*mxp ;
	tmpx		*utp ;
	pwcache		*ucp ;
	time_t		ti_utopen ;	/* open-time */
	time_t		ti_utcheck ;	/* check-time */
	FINDUID_ST	s ;
	FINDUID_FL	open ;
	uint		magic ;
	int		ttl ;		/* time-to-live */
	int		nmax ;		/* maximum entries */
} ;

typedef	FINDUID		finduid ;
typedef	FINDUID_FL	finduid_fl ;
typedef	FINDUID_ST	finduid_st ;

EXTERNC_begin

extern int finduid_start(finduid *,int,int) noex ;
extern int finduid_lookup(finduid *,char *,int,uid_t) noex ;
extern int finduid_invalidate(finduid *,cchar *) noex ;
extern int finduid_check(finduid *,time_t) noex ;
extern int finduid_stats(finduid *,finduid_st *) noex ;
extern int finduid_finish(finduid *) noex ;

EXTERNC_end


#endif /* FINDUID_INCLUDE */


