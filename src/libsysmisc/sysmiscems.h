/* sysmiscems SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */


/* Copyright © 2008 David A­D­ Morano.  All rights reserved. */

#ifndef	SYSMISCEMS_INCLUDE
#define	SYSMISCEMS_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<cstddef>
#include	<cstdlib>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<localmisc.h>


#define	SYSMISCEMS	struct sysmiscems_head

#define	SYSMISCEMS_OBJ	struct sysmiscems_obj
#define	SYSMISCEMS_DATA	struct sysmiscems_d


struct sysmiscems_obj {
	cchar	*name ;
	uint		objsize ;
} ;

struct sysmiscems_d {
	uint		intstale ;		/* "stale" interval */
	uint		utime ;
	uint		btime ;
	uint		ncpu ;
	uint		nproc ;
	uint		la[3] ;
} ;

struct sysmiscems_flags {
	uint		shm:1 ;			/* initialized */
} ;

struct sysmiscems_head {
	uint		magic ;
	cchar	*pr ;
	cchar	*prbuf ;
	cchar	*shmname ;
	char		*mapdata ;
	uint		*shmtable ;
	struct sysmiscems_flags	f ;
	time_t		daytime ;
	time_t		ti_shm ;		/* DB file modification */
	time_t		ti_map ;		/* DB map */
	time_t		ti_lastcheck ;		/* last check of file */
	size_t		mapsize ;
	int		nodenamelen ;
	int		pagesize ;
	int		shmsize ;
} ;


#if	(! defined(SYSMISCEMS_MASTER)) || (SYSMISCEMS_MASTER == 0)

#ifdef	__cplusplus
extern "C" {
#endif

extern int	sysmiscems_open(SYSMISCEMS *,cchar *) ;
extern int	sysmiscems_get(SYSMISCEMS *,time_t,int,SYSMISCEMS_DATA *) ;
extern int	sysmiscems_close(SYSMISCEMS *) ;

#ifdef	__cplusplus
}
#endif

#endif /* SYSMISCEMS_MASTER */

#endif /* SYSMISCEMS_INCLUDE */


