/* lastlogfile HEADER */
/* lang=C++20 */

/* manage reading or writing a LASTLOG file */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	LASTLOGFILE_INCLUDE
#define	LASTLOGFILE_INCLUDE


#undef	LOCAL_DARWIN
#define	LOCAL_DARWIN	\
	(defined(OSNAME_Darwin) && (OSNAME_Darwin > 0))


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utmp.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


/* object defines */
#define	LASTLOGFILE_MAGIC	1092387457
#define	LASTLOGFILE		struct lastlogfile_head
#define	LASTLOGFILE_CUR		struct lastlogfile_cursor
#define	LASTLOGFILE_ENT		struct lastlog

/* other defines */
#define	LASTLOGFILE_FILEPATH	"/var/adm/lastlog"
#define	LASTLOGFILE_LHOST	16
#define	LASTLOGFILE_LLINE	8


struct lastlogfile_cursor {
	int		i ;
} ;

struct lastlogfile_head {
	cchar		*fname ;	/* stored file name */
	size_t		fsize ;		/* file size */
	time_t		otime ;		/* open time (for FD caching) */
	time_t		mtime ;		/* last modification time */
	uint		magic ;
	int		pagesize ;
	int		oflags ;	/* open flags */
	int		fd ;		/* file descriptor */
} ;

typedef	LASTLOGFILE	lastlogfile ;
typedef	LASTLOGFILE_CUR	lastlogfile_cur ;
typedef	LASTLOGFILE_ENT	lastlogfile_ent ;

EXTERNC_begin

extern int lastlogfile_open(lastlogfile *,cchar *,int) noex ;
extern int lastlogfile_readinfo(lastlogfile *,uid_t,time_t *,
		char *,char *) noex ;
extern int lastlogfile_writeinfo(lastlogfile *,uid_t,time_t,
		cchar *,cchar *) noex ;
extern int lastlogfile_readentry(lastlogfile *,uid_t,lastlogfile_ent *) noex ;
extern int lastlogfile_writeentry(lastlogfile *,uid_t,lastlogfile_ent *) noex ;
extern int lastlogfile_check(lastlogfile *,time_t) noex ;
extern int lastlogfile_close(lastlogfile *) noex ;
extern int lastlogfile_curbegin(lastlogfile *,lastlogfile_cur *) noex ;
extern int lastlogfile_curend(lastlogfile *,lastlogfile_cur *) noex ;
extern int lastlogfile_curenum(lastlogfile *,lastlogfile_cur *,
		uid_t *,time_t *,char *,char *) noex ;

EXTERNC_end


#endif /* LASTLOGFILE_INCLUDE */


