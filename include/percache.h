/* percache HEADER */
/* lang=C20 */

/* persistent cache */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-01-22, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	PERCACHE_INCLUDE
#define	PERCACHE_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


#define	PERCACHE	struct percache_head
#define	PERCACHE_ITEM	struct percache_dataitem


enum pertypes {
	pertype_hostid,
	pertype_nprocs,
	pertype_btime,
	pertype_runlevel,
	pertype_nusers,
	pertype_sysdomain,
	pertype_netload,
	pertype_systat,
	pertype_overlast
} ;

struct percache_dataitem {
	uint		t ;
	uint		v ;
} ;

struct percache_head {
	volatile uint	f_init ;
	volatile uint	f_initdone ;
	volatile uint	f_finireg ;
	PERCACHE_ITEM	items[pertype_overlast] ;
	cchar		*sysdomain ;
	cchar		*netload ;
	cchar		*systat ;
} ;

typedef PERCACHE	percache ;
typedef	PERCACHE_ITEM	percache_item ;

EXTERNC_begin

extern int	percache_init(percache *) noex ;
extern int	percache_finireg(percache *) noex ;
extern int	percache_invalidate(percache *) noex ;
extern int	percache_gethostid(percache *,time_t,uint *) noex ;
extern int	percache_getnprocs(percache *,time_t) noex ;
extern int	percache_getbtime(percache *,time_t,time_t *) noex ;
extern int	percache_getrunlevel(percache *,time_t) noex ;
extern int	percache_getnusers(percache *,time_t) noex ;
extern int	percache_getsysdomain(percache *,time_t,cchar **) noex ;
extern int	percache_getnetload(percache *,time_t,cchar *,cchar **) noex ;
extern int	percache_getsystat(percache *,time_t,cchar *,cchar **) noex ;
extern int	percache_fini(percache *) noex ;

EXTERNC_end


#endif /* PERCACHE_INCLUDE */


