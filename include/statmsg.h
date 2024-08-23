/* statmsg HEADER */
/* lang=C20 */

/* object to help (manage) STATMSG messages */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	STATMSG_INCLUDE
#define	STATMSG_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>		/* |uid_t| + |gid_t| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<ptm.h>
#include	<lockrw.h>
#include	<paramfile.h>
#include	<vechand.h>
#include	<localmisc.h>


#define	STATMSG_MAGIC	0x75648942
#define	STATMSG		struct statmsg_head
#define	STATMSG_ID	struct statmsg_ident
#define	STATMSG_MAP	struct statmsg_mapper
#define	STATMSG_FL	struct statmsg_flags
#define	STATMSG_CK	struct statmsg_check


struct statmsg_ident {
	cchar		*groupname ;
	cchar		*username ;
	uid_t		uid ;
	gid_t		gid ;
} ;

struct statmsg_mapper {
	lockrw		rwm ;
	paramfile	dirsfile ;
	vechand		mapdirs ;
	cchar		*username ;
	cchar		*userhome ;
	cchar		*fname ;
	time_t		ti_mtime ;
	time_t		ti_check ;
	uint		magic ;
} ;

struct statmsg_flags {
	uint		sorted:1 ;
} ;

struct statmsg_check {
	ptm		m ;
	time_t		ti_lastcheck ;	/* needs mutex protection */
	int		nmaps ;
} ;

struct statmsg_head {
	STATMSG_MAP	mapper ;
	ptm		m ;		/* this is for all of the data */
	cchar		**envv ;
	cchar		*useralloc ;
	cchar		*username ;
	cchar		*userhome ;
	cchar		*fe ;		/* file-ending */
	time_t		ti_lastcheck ;
	STATMSG_FL	f ;
	uint		magic ;
	int		nmaps ;
	int		nenv ;
} ;

typedef	STATMSG		statmsg ;
typedef	STATMSG_FL	statmsg_fl ;
typedef	STATMSG_ID	statmsg_id ;
typedef	STATMSG_MAP	statmsg_map ;
typedef	STATMSG_CK	statmsg_ch ;

EXTERNC_begin

extern int statmsg_open(statmsg *,cchar *) noex ;
extern int statmsg_check(statmsg *,time_t) noex ;
extern int statmsg_process(statmsg *,cchar *,cchar **,cchar *,int) noex ;
extern int statmsg_processid(statmsg *,statmsg_id *,cchar **,cchar *,int) noex ;
extern int statmsg_close(statmsg *) noex ;

extern int statmsgid_load(statmsg_id *,cchar *,cchar *,uid_t,gid_t) noex ;

EXTERNC_end


#endif /* STATMSG_INCLUDE */


