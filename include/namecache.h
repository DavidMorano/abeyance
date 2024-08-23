/* namecache HEADER */
/* lang=C20 */

/* real-name cache (from UNIX® System PASSWD database) */
/* version %I% last-modified %G% */


/* revision history:

	= 2004-06-23, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2004 David A­D­ Morano.  All rights reserved. */

#ifndef	NAMECACHE_INCLUDE
#define	NAMECACHE_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<hdb.h>
#include	<localmisc.h>


#define	NAMECACHE		struct namecache_head
#define	NAMECACHE_ST		struct namecache_statistics

#define	NAMECACHE_MAGIC		0x98643167
#define	NAMECACHE_DEFENTS	20
#define	NAMECACHE_DEFMAX	21
#define	NAMECACHE_DEFTO		(5 * 60)


struct namecache_statistics {
	uint		nentries ;
	uint		total ;			/* access */
	uint		refreshes ;
	uint		phits, pmisses ;	/* positive */
	uint		nhits, nmisses ;	/* negative */
} ;

struct namecache_head {
	hdb		*dbp ;
	cchar		*varname ;
	NAMECACHE_ST	s ;
	uint		magic ;
	int		nmax ;		/* maximum number of entries */
	int		ttl ;		/* time-to-live (in seconds) */
} ;

typedef	NAMECACHE		namecache ;
typedef	NAMECACHE_ST		namecache_st ;

EXTERNC_begin

extern int namecache_start(namecache *,cchar *,int,int) noex ;
extern int namecache_add(namecache *,cchar *,cchar *,int) noex ;
extern int namecache_lookup(namecache *,cchar *,cchar **) noex ;
extern int namecache_stats(namecache *,namecache_st *) noex ;
extern int namecache_finish(namecache *) noex ;

EXTERNC_end


#endif /* NAMECACHE_INCLUDE */


