/* userports HEADER */
/* lang=C20 */

/* query the USERPOTS database for entries */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	USERPORTS_INCLUDE
#define	USERPORTS_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<usystem.h>		/* for |ino_t| */
#include	<vecobj.h>
#include	<vecpstr.h>
#include	<localmisc.h>


#define	USERPORTS	struct userports_head
#define	USERPORTS_FL	struct userports_flags
#define	USERPORTS_CUR	struct userports_cursor
#define	USERPORTS_ENT	struct userports_entry
#define	USERPORTS_FI	struct userports_file
#define	USERPORTS_MAGIC	0x87437174
#define	USERPORTS_FNAME	"/etc/userports"


struct userports_entry {
	cchar		*protocol ;
	cchar		*portname ;
	uid_t		uid ;
} ;

struct userports_cursor {
	int		i ;
} ;

struct userports_flags {
	uint		feof:1 ;
	uint		sorted:1 ;
} ;

struct userports_file {
	ino_t		ino ;
	dev_t		dev ;
	time_t		mtime ;
} ;

struct userports_head {
	vecobj		*elp ;		/* entry-list-pointer */
	vecpstr		*plp ;		/* protocol-list-pointer */
	vecpstr		*olp ;		/* port-list-pinter */
	cchar		*fname ;
	USERPORTS_FL	f ;
	USERPORTS_FI	fi ;
	uint		magic ;
} ;

typedef	USERPORTS	userports ;
typedef	USERPORTS_FL	userports_fl ;
typedef	USERPORTS_CUR	userports_cur ;
typedef	USERPORTS_ENT	userports_ent ;
typedef	USERPORTS_FI	userports_fi ;

EXTERNC_begin

extern int userports_open(userports *,cchar *) noex ;
extern int userports_query(userports *,uid_t,cchar *,int) noex ;
extern int userports_curbegin(userports *,userports_cur *) noex ;
extern int userports_enum(userports *,userports_cur *,userports_ent *) noex ;
extern int userports_fetch(userports *,userports_cur *,uid_t,
		userports_ent *) noex ;
extern int userports_curend(userports *,userports_cur *) noex ;
extern int userports_close(userports *) noex ;

EXTERNC_end


#endif /* USERPORTS_INCLUDE */


