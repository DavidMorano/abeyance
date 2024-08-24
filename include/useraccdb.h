/* useraccdb HEADER */
/* lang=C20 */

/* user-access (user-access-logging) data-base management */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	USERACCDB_INCLUDE
#define	USERACCDB_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>		/* for 'ino_t' */
#include	<filer.h>
#include	<dater.h>
#include	<localmisc.h>


#define	USERACCDB	struct useraccdb_head
#define	USERACCDB_FL	struct useraccdb_flags
#define	USERACCDB_CUR	struct useraccdb_cursor
#define	USERACCDB_ENT	struct useraccdb_entry


struct useraccdb_entry {
	cchar		*user ;
	cchar		*name ;
	time_t		atime ;
	uint		count ;
} ;

struct useraccdb_cursor {
	filer		b ;
	off_t		eo ;		/* enumeration offset */
} ;

struct useraccdb_flags {
	uint		locked:1 ;
	uint		dater:1 ;
} ;

struct useraccdb_head {
	dater		*dmp ;		/* dater-manager-pointer */
	cchar		*fname ;
	off_t		eo ;
	time_t		ti_check ;
	time_t		ti_mod ;
	ino_t		ino ;
	dev_t		dev ;
	USERACCDB_FL	f ;
	uint		magic ;
	int		fd ;
} ;

typedef	USERACCDB	useraccdb ;
typedef	USERACCDB_FL	useraccdb_fl ;
typedef	USERACCDB_CUR	useraccdb_cur ;
typedef	USERACCDB_ENT	useraccdb_ent ;

EXTERNC_begin

extern int useraccdb_open(useraccdb *,cchar *,cchar *) noex ;
extern int useraccdb_find(useraccdb *,useraccdb_ent *,char *,int,cchar *) noex ;
extern int useraccdb_update(useraccdb *,cchar *,cchar *) noex ;
extern int useraccdb_curbegin(useraccdb *,useraccdb_cur *) noex ;
extern int useraccdb_curend(useraccdb *,useraccdb_cur *) noex ;
extern int useraccdb_enum(useraccdb *,useraccdb_cur *,
		useraccdb_ent *,char *,int) noex ;
extern int useraccdb_check(useraccdb *,time_t) noex ;
extern int useraccdb_close(useraccdb *) noex ;

EXTERNC_end


#endif /* USERACCDB_INCLUDE */


