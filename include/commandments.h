/* commandments HEADER */
/* lang=C++20 */

/* COMMANDMENTS object implementation */
/* version %I% last-modified %G% */


/* revision history:

	= 2008-03-01, David A­D­ Morano
	This module was originally written.

*/

/* Copyright © 2008 David A­D­ Morano.  All rights reserved. */

#ifndef	COMMANDMENTS_INCLUDE
#define	COMMANDMENTS_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<localmisc.h>

#include	"cmi.h"


#define	COMMANDMENTS_MAGIC	0x99447248
#define	COMMANDMENTS		struct commandments_head
#define	COMMANDMENTS_INFO	struct commandments_information
#define	COMMANDMENTS_CUR	struct commandments_cursor
#define	COMMANDMENTS_C		struct commandments_cursor
#define	COMMANDMENTS_ENT	struct commandments_entry
#define	COMMANDMENTS_E		struct commandments_entry
#define	COMMANDMENTS_FL		struct commandments_flags
#define	COMMANDMENTS_OBJ	struct commandments_object
#define	COMMANDMENTS_DBNAME	"ten"


struct commandments_object {
	cchar		*name ;
	uint		objsize ;
	uint		cursize ;
} ;

struct commandments_information {
	time_t		dbtime ;		/* db-time */
	time_t		citime ;		/* idx-time */
	uint		maxent ;
	uint		count ;
} ;

struct commandments_entry {
	uint		cn ;			/* commandment number */
} ;

struct commandments_cursor {
	CMI_CUR		vicur ;
} ;

struct commandments_flags {
	uint		user:1 ;		/* user or system? */
	uint		idx:1 ;
	uint		ids:1 ;
} ;

struct commandments_head {
	uint		magic ;
	COMMANDMENTS_FL	f ;
	CMI		idx ;
	void		*a ;
	cchar		*pr ;
	cchar		*dbname ;
	cchar		*uhome ;		/* user home dir */
	cchar 		*fname ;
	cchar		*data_db ;
	size_t		size_db ;		/* srouce DB size */
	time_t		ti_db ;			/* source DB m-time */
	time_t		ti_idx ;		/* index modification */
	time_t		ti_map ;		/* map */
	time_t		ti_lastcheck ;		/* last check of file */
	uid_t		uid ;
	uid_t		uid_pr ;
	gid_t		gid_pr ;
	int		ncursors ;
	int		nents ;
	int		maxent ;
} ;

typedef	COMMANDMENTS		commandments ;
typedef	COMMANDMENTS_INFO	commandments_info ;
typedef	COMMANDMENTS_CUR	commandments_cur ;
typedef	COMMANDMENTS_ENT	commandments_ent ;
typedef	COMMANDMENTS_FL		commandments_fl ;
typedef	COMMANDMENTS_OBJ	commandments_obj ;

EXTERNC_begin

extern int	commandments_open(commandments *,cchar *,cchar *) ;
extern int	commandments_audit(commandments *) ;
extern int	commandments_count(commandments *) ;
extern int	commandments_max(commandments *) ;
extern int	commandments_read(commandments *,char *,int,int) ;
extern int	commandments_get(commandments *,int,char *,int) ;
extern int	commandments_curbegin(commandments *,commandments_cur *) ;
extern int	commandments_enum(commandments *,commandments_cur *,
			commandments_ent *,char *,int) ;
extern int	commandments_curend(commandments *,commandments_cur *) ;
extern int	commandments_close(commandments *) ;

EXTERNC_end


#endif /* COMMANDMENTS_INCLUDE */


