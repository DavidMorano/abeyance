/* tmpx HEADER */
/* lang=C20 */

/* object to facilitate UTMPX management */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#ifndef	TMPX_INCLUDE
#define	TMPX_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>		/* |pid_t| */
#include	<utmpx.h>
#include	<time.h>		/* |time_t| */
#include	<usystem.h>
#include	<vecstr.h>


/* UTMPX file */
#if	(defined(OSNAME_SunOS) && (OSNAME_SunOS > 0))
#define	UTMPX_DEFUTMP	"/var/adm/utmpx"
#elif	defined(OSNAME_Darwin) && (OSNAME_Darwin > 0)
#define	UTMPX_DEFUTMP	"/var/run/utmpx"
#elif	defined(OSNAME_Linux) && (OSNAME_Linux > 0)
#define	UTMPX_DEFUTMP	"/var/run/utmpx"
#else
#define	UTMPX_DEFUTMP	"/var/run/utmpx"
#endif

/* UTMPX stuff */
#ifndef	UTMPX_TEMPTY
#define	UTMPX_TEMPTY		0	/* entry is unused */
#define	UTMPX_TRUNLEVEL		1
#define	UTMPX_TBOOTTIME		2
#define	UTMPX_TOLDTIME		3
#define	UTMPX_TNEWTIME		4
#define	UTMPX_TPROCINIT		5	/* process spawned by "init" */
#define	UTMPX_TPROCLOGIN	6	/* a "getty" waiting for login */
#define	UTMPX_TPROCUSER		7	/* a regular user process */
#define	UTMPX_TPROCDEAD		8	/* used in WTMPX only? */
#define	UTMPX_TACCOUNT		9	/* used in WTMPX only? */
#define	UTMPX_TSIGNATURE	10	/* used in WTMPX only? */
#endif /* UTMPX_TEMPTY */

#ifndef	UTMPX_LID
#define	UTMPX_LID		4
#define	UTMPX_LUSER		32
#define	UTMPX_LLINE		32
#define	UTMPX_LHOST		256
#endif

/* object defines */
#define	TMPX		struct tmpx_head
#define	TMPX_FL		struct tmpx_flags
#define	TMPX_CUR	struct tmpx_cursor
#define	TMPX_ENT	struct utmpx
#define	TMPX_MAGIC	1092387456
#define	TMPX_ENTSIZE	sizeof(TMPX_ENT)
#define	TMPX_DEFUTMP	UTMPX_DEFUTMP

/* entry-type values */
#define	TMPX_TEMPTY	UTMPX_TEMPTY
#define	TMPX_TRUNLEVEL	UTMPX_TRUNLEVEL
#define	TMPX_TBOOTTIME	UTMPX_TBOOTTIME
#define	TMPX_TOLDTIME	UTMPX_TOLDTIME
#define	TMPX_TNEWTIME	UTMPX_TNEWTIME
#define	TMPX_TPROCINIT	UTMPX_TPROCINIT
#define	TMPX_TPROCLOGIN	UTMPX_TPROCLOGIN
#define	TMPX_TPROCUSER	UTMPX_TPROCUSER
#define	TMPX_TPROCDEAD	UTMPX_TPROCDEAD
#define	TMPX_TACCOUNT	UTMPX_TACCOUNT
#define	TMPX_TSIGNATURE	UTMPX_TSIGNATURE

/* entry-legnth values */
#define	TMPX_LID	UTMPX_LID
#define	TMPX_LUSER	UTMPX_LUSER
#define	TMPX_LLINE	UTMPX_LLINE
#define	TMPX_LHOST	UTMPX_LHOST


struct tmpx_cursor {
	int		i ;
} ;

struct tmpx_flags {
	uint		writable:1 ;
} ;

struct tmpx_head {
	cchar		*fname ;	/* stored file name */
	caddr_t		mapdata ;	/* file mapping buffer */
	time_t		ti_open ;	/* open time (for FD caching) */
	time_t		ti_mod ;	/* last modification time */
	time_t		ti_check ;	/* last check time */
	size_t		mapsize ;
	size_t		fsize ;		/* file total size */
	TMPX_FL		f ;
	uint		mapoff ;	/* file mapping starting offset */
	uint		magic ;
	int		pagesize ;
	int		oflags ;	/* open flags */
	int		operms ;	/* open permissions */
	int		fd ;		/* file descriptor */
	int		ncursors ;
	int		mapei ;		/* index of top mapped entry */
	int		mapen ;		/* number of mapped entries */
} ;

typedef TMPX		tmpx ;
typedef TMPX_FL		tmpx_fl ;
typedef TMPX_CUR	tmpx_cur ;
typedef TMPX_ENT	tmpx_ent ;

EXTERNC_begin

extern int tmpx_open(tmpx *,cchar *,int) noex ;
extern int tmpx_read(tmpx *,int,tmpx_ent *) noex ;
extern int tmpx_write(tmpx *,int,tmpx_ent *) noex ;
extern int tmpx_check(tmpx *,time_t) noex ;
extern int tmpx_curbegin(tmpx *,tmpx_cur *) noex ;
extern int tmpx_curend(tmpx *,tmpx_cur *) noex ;
extern int tmpx_enum(tmpx *,tmpx_cur *,tmpx_ent *) noex ;
extern int tmpx_fetchuser(tmpx *,tmpx_cur *,tmpx_ent *,cchar *) noex ;
extern int tmpx_fetchpid(tmpx *,tmpx_ent *,pid_t) noex ;
extern int tmpx_nusers(tmpx *) noex ;
extern int tmpx_close(tmpx *) noex ;

extern int tmpx_getboottime(tmpx *,time_t *) noex ;
extern int tmpx_getrunlevel(tmpx *) noex ;
extern int tmpx_getuserlines(tmpx *,vecstr *,cchar *) noex ;
extern int tmpx_getuserterms(tmpx *,vecstr *,cchar *) noex ;

EXTERNC_end


#endif /* TMPX_INCLUDE */


