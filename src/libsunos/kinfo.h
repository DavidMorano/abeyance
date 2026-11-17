/* kinfo HEADER */
/* charset=ISO8859-1 */
/* lang=C20 */

/* kernel information access (for Sun Solaris®) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-12-01, David A­D­ Morano
	Module was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	KINFO_INCLUDE
#define	KINFO_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>		/* POSIX® */
#include	<kstat.h>		/* Solaris® */


#define	KINFO		struct kinfo_head
#define	KINFO_FL	struct kinfo_flags
#define	KINFO_DA	struct kinfo_data


struct kinfo_data {
	uint		boottime ;
	uint		ncpu ;
	uint		nproc ;
	uint		la[3] ;
} ; /* end struct */

struct kinfo_flags {
	uint		kopen:1 ;
} ; /* end struct */

struct kinfo_head {
	kstat_ctl_t	*kcp ;
	time_t		ti_access ;		/* last access */
	time_t		ti_sysmisc ;		/* last SYSMISC update */
	time_t		ti_loadave ;		/* last LOADAVE update */
	time_t		ti_update ;		/* last KSTAT chain update */
	KINFO_DATA	d ;
	KINFO_FL	f ;
	uint		magic ;
	int		nactive ;		/* number of active requests */
	int		tosysmisc ;
	int		toloadave ;
} ; /* end struct */

typedef	KINFO		kinfo ;
typedef	KINFO_FL	kinfo_fl ;
typedef	KINFO_DA	kinfo_da ;

EXTERNC_begin

extern int kinfo_open(kinfo *,time_t) noex ;
extern int kinfo_boottime(kinfo *,time_t,kinfo_da *) noex ;
extern int kinfo_loadave(kinfo *,time_t,kinfo_da *) noex ;
extern int kinfo_sysmisc(kinfo *,time_t,kinfo_da *) noex ;
extern int kinfo_check(kinfo *,time_t) noex ;
extern int kinfo_close(kinfo *) noex ;

EXTERNC_end


#endif /* KINFO_INCLUDE */


