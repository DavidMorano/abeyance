/* ucpwcache HEADER */
/* lang=C20 */

/* UNIX® password entry fetching */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UCPWCACHE_INCLUDE
#define	UCPWCACHE_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<pwd.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<localmisc.h>


#define	UCPWCACHE_ST		struct ucpwcache_stats

#define	UCPWCACHE_MAX		120	/* max cache entries */
#define	UCPWCACHE_TTL		(20*60)	/* entry time-out in seconds */
#define	UCPWCACHE_TOLOCK	5


struct ucpwcache_stats {
	uint		nmax ;		/* maximum number of entries */
	uint		ttl ;		/* time-to-live */
	uint		nent ;
	uint		acc ;
	uint		phit, nhit ;
	uint		pmis, nmis ;
} ;

typedef UCPWCACHE_ST	ucpwcache_st ;

EXTERNC_begin

extern int ucpwcache_init() noex ;
extern int ucpwcache_name(PASSWD *,char *,int,cchar *) noex ;
extern int ucpwcache_uid(PASSWD *,char *,int,uid_t) noex ;
extern int ucpwcache_stats(ucpwcache_st *) noex ;
extern int ucpwcache_setparam(int,int) noex ;
extern int ucpwcache_fini() noex ;

EXTERNC_end


#endif /* UCPWCACHE_INCLUDE */


