/* logzones HEADER */
/* lang=C20 */

/* log timezone names */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	LOGZONES_INCLUDE
#define	LOGZONES_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


#define	LOGZONES		struct logzones_head
#define	LOGZONES_ENT		struct logzones_entry
#define	LOGZONES_CUR		struct logzones_cursor
#define	LOGZONES_FL		struct logzones_flags

#define	LOGZONES_MAGIC		91824563
#define	LOGZONES_ENTLEN		48
#define	LOGZONES_NENTS		100
#define	LOGZONES_ZNAMESIZE	8
#define	LOGZONES_STAMPSIZE	23
#define	LOGZONES_NOZONEOFFSET	(13 * 60)


struct logzones_entry {
	uint		count ;
	short		off ;
	short		znl ;
	char		znb[LOGZONES_ZNAMESIZE + 1] ;
	char		st[LOGZONES_STAMPSIZE + 1] ;
} ;

struct logzones_flags {
	uint		writable:1 ;
	uint		lockedread:1 ;
	uint		lockedwrite:1 ;
	uint		cursor:1 ;		/* cursor-locked ? */
	uint		cursorlockbroken:1 ;	/* cursor lock broken */
	uint		cursoracc:1 ;		/* accessed while cursored ? */
	uint		remote:1 ;		/* remote mounted file */
} ;

struct logzones_head {
	cchar		*fname ;
	char		*buf ;
	time_t		opentime ;		/* file open time */
	time_t		accesstime ;		/* file access time */
	time_t		mtime ;			/* file modification time */
	LOGZONES_FL	f ;
	uint		magic ;
	int		oflags ;
	int		pagesize ;
	int		filesize ;
	int		bufsize ;
	int		fd ;
	mode_t		operms ;
} ;

struct logzones_cursor {
	int		i ;
} ;

typedef LOGZONES	logzones ;
typedef	LOGZONES_ENT	logzones_ent ;
typedef	LOGZONES_CUR	logzones_cur ;
typedef	LOGZONES_FL	logzones_fl ;

EXTERNC_begin

extern int logzones_open(logzones *,cchar *,int,mode_t) noex ;
extern int logzones_curbegin(logzones *,logzones_cur *) noex ;
extern int logzones_curend(logzones *,logzones_cur *) noex ;
extern int logzones_curenum(logzones *,logzones_cur *,logzones_ent *) noex ;
extern int logzones_match(logzones *,cchar *,int,int,logzones_ent *) noex ;
extern int logzones_update(logzones *,cchar *,int,int,cchar *) noex ;
extern int logzones_check(logzones *,time_t) noex ;
extern int logzones_close(logzones *) noex ;

EXTERNC_end


#endif /* LOGZONES_INCLUDE */


