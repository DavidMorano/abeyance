/* sysmiscs HEADER */
/* lang=C20 */

/* return SYSMISC information from the system */
/* version %I% last-modified %G% */


/* Copyright © 2008 David A­D­ Morano.  All rights reserved. */

#ifndef	SYSMISCS_INCLUDE
#define	SYSMISCS_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<msfile.h>
#include	<localmisc.h>


#define	SYSMISCS	struct sysmiscs_head
#define	SYSMISCS_D	struct sysmiscs_data
#define	SYSMISCS_FL	struct sysmiscs_flags

#define	SYSMISCS_MAGIC	0x66342125
#define	SYSMISCS_PROG	"msu"


struct sysmiscs_data {
	uint		utime ;
	uint		btime ;
	uint		ncpu ;
	uint		nproc ;
} ;

struct sysmiscs_flags {
	uint		msinit:1 ;		/* MS is initialized */
	uint		msopen:1 ;
	uint		msold:1 ;
} ;

struct sysmiscs_head {
	cchar		*pr ;
	cchar		*nodename ;
	cchar 		*dbname ;		/* DB-name */
	cchar 		*dbfname ;		/* DB file-name */
	msfile		ms ;
	time_t		ti_db ;			/* DB file modification */
	time_t		ti_map ;		/* DB map */
	time_t		ti_lastcheck ;		/* last check of file */
	SYSMISCS_FL	f ;
	uint		magic ;
	int		nodenamelen ;
} ;

typedef	SYSMISCS	sysmiscs ;
typedef	SYSMISCS_D	sysmiscs_d ;
typedef	SYSMISCS_FL	sysmiscs_fl ;

EXTERNC_begin

extern int	sysmiscs_open(sysmiscs *,cchar *) noex ;
extern int	sysmiscs_get(sysmiscs *,time_t,sysmiscs_d *) noex ;
extern int	sysmiscs_close(sysmiscs *) noex ;

EXTERNC_end


#endif /* SYSMISCS_INCLUDE */


