/* resolves */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */


#ifndef	RESOLVES_INCLUDE
#define	RESOLVES_INCLUDE	1


#include	<envstandards.h>	/* MUST be first to configure */

#include	<sys/types.h>
#include	<sys/param.h>

#include	<ptm.h>
#include	<lockrw.h>
#include	<paramfile.h>
#include	<finduid.h>
#include	<vechand.h>
#include	<localmisc.h>


#define	RESOLVES		struct resolves_head
#define	RESOLVES_ID		struct resolves_id
#define	RESOLVES_MAPPER		struct resolves_mapper


struct resolves_id {
	cchar	*groupname ;
	cchar	*username ;
	uid_t		uid ;
	gid_t		gid ;
} ;

struct resolves_mapper {
	uint		magic ;
	LOCKRW		rwm ;
	paramfile	dirsfile ;
	vechand		mapdirs ;
	cchar	*fname ;
	time_t		ti_mtime ;
	time_t		ti_check ;
} ;

struct resolves_flags {
	uint		ufind:1 ;
} ;

struct resolves_check {
	PTM		m ;
	time_t		ti_lastcheck ;	/* needs mutex protection */
	int		nmaps ;
} ;

struct resolves_head {
	uint		magic ;
	struct resolves_flags	open ;
	PTM		m ;		/* this is for all of the data */
	RESOLVES_MAPPER	mapper ;
	FINDUID		ufind ;
	cchar	**envv ;
	cchar	*pr ;
	cchar	*fe ;		/* file-ending */
	time_t		ti_lastcheck ;
	int		nmaps ;
	int		nenv ;
} ;


#if	(! defined(RESOLVES_MASTER)) || (RESOLVES_MASTER == 0)

#ifdef	__cplusplus
extern "C" {
#endif

extern int	resolves_open(RESOLVES *,cchar *) ;
extern int	resolves_check(RESOLVES *,time_t) ;
extern int	resolves_process(RESOLVES *,cchar *,
			cchar **,int) ;
extern int	resolves_procid(RESOLVES *,RESOLVES_ID *,
			cchar **,int) ;
extern int	resolves_close(RESOLVES *) ;

extern int	resolvesid_load(RESOLVES_ID *,cchar *,cchar *,
			uid_t,gid_t) ;

#ifdef	__cplusplus
}
#endif

#endif /* RESOLVES_MASTER */


#endif /* RESOLVES_INCLUDE */



