/* mbcache HEADER */
/* lang=C20 */

/* mailbox cache */
/* version %I% last-modified %G% */


/* Copyright © 2009 David A­D­ Morano.  All rights reserved. */

#ifndef	MBCACHE_INCLUDE
#define	MBCACHE_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<vecint.h>
#include	<strpack.h>
#include	<dater.h>
#include	<date.h>
#include	<localmisc.h>

#include	"mailbox.h"


#define	MBCACHE_MAGIC		0x31415927
#define	MBCACHE			struct mbcache_head
#define	MBCACHE_FL		struct mbcache_flags
#define	MBCACHE_INFO		struct mbcache_information
#define	MBCACHE_SCAN		struct mbcache_scanner
#define	MBCACHE_SFLAGS		struct mbcache_sflags

/* open options */
#define	MBCACHE_ORDWR		MAILBOX_ORDWR

#define	MBCACHE_MFVREAD		0		/* MSG has been read */
#define	MBCACHE_MFVDEL		1		/* MSG marked for deletion */
#define	MBCACHE_MFVSPAM		2		/* MSG marked as spam */
#define	MBCACHE_MFVTRASH	3		/* MSG marked as trash */

#define	MBCACHE_MFMREAD		(1<<MBCACHE_MFVREAD)
#define	MBCACHE_MFMDEL		(1<<MBCACHE_MFVDEL)
#define	MBCACHE_MFMSPAM		(1<<MBCACHE_MFVSPAM)
#define	MBCACHE_MFMTRASH	(1<<MBCACHE_MFVTRASH)


enum mbcachemfs {
	mbcachemf_envaddr,
	mbcachemf_envdate,
	mbcachemf_envremote,
	mbcachemf_hdrmid,
	mbcachemf_hdrfrom,
	mbcachemf_hdrdate,
	mbcachemf_hdrsubject,
	mbcachemf_hdrstatus,
	mbcachemf_scanfrom,
	mbcachemf_scansubject,
	mbcachemf_scandate,
	mbcachemf_scanline,
	mbcachemf_overlast
} ;

struct mbcache_information {
	int		nmsgs ;		/* mailbox messages total */
	int		nmsgdels ;	/* mailbox messages deleted */
} ;

struct mbcache_sflags {
	uint		info:1 ;	/* msg-info loaded */
	uint		vs:1 ;		/* values (extended) initialized */
	uint		lineoffs:1 ;	/* 'lineoffs' initialized */
	uint		edate:1 ;	/* date-envelope initialized */
	uint		hdate:1 ;	/* date-header initialized */
	uint		clen:1 ;
	uint		clines:1 ;
	uint		lines:1 ;
	uint		xlines:1 ;
	uint		status:1 ;	/* have STATUS header */
	uint		msgid:1 ;	/* have MSGID header */
	uint		sem:1 ;		/* have SEM header */
	uint		read:1 ;	/* MSG has been read */
	uint		del:1 ;		/* MSG marked for deletion */
	uint		spam:1 ;	/* MSG marked as spam */
	uint		trash:1 ;	/* MSG marked as trash (trashed) */
	uint		scanfrom:1 ;
	uint		scansubject:1 ;
	uint		scandate:1 ;
} ;

struct mbcache_scanner {
	cchar		*vs[mbcachemf_overlast] ;
	cchar		*fname ;	/* processed content file */
	vecint		lineoffs ;
	DATE		edate ;		/* date-envelope */
	DATE		hdate ;		/* date-header */
	off_t		moff ;		/* offset message start (envelope) */
	off_t		hoff ;		/* offset message headers */
	off_t		boff ;		/* offset message body */
	time_t		etime ;		/* time-envelope */
	time_t		htime ;		/* time-header */
	MBCACHE_SFLAGS	hdr, hdrval, proc, f ;
	int		vl[mbcachemf_overlast] ;
	int		mlen ;		/* length message whole */
	int		hlen ;		/* length message headers */
	int		blen ;		/* length message body */
	int		filesize ;	/* processed content file */
	int		nlines ;	/* message lines-native */
	int		vlines ; 	/* message lines-view */
	int		msgi ;		/* message index */
} ;

struct mbcache_flags {
	uint		readonly:1 ;
} ;

struct mbcache_head {
	mailbox		*mbp ;
	cchar		*mbfname ;
	MBCACHE_SCAN	**msgs ;
	mailbox_info	mbi ;
	strpack		strs ;
	dater		dm ;		/* dater-manager */
	MBCACHE_FL	f ;
	uint		magic ;
	int		mflags ;	/* mailbox open-flags */
} ;

typedef	MBCACHE		mbcache ;
typedef	MBCACHE_FL	mbcache_fl ;
typedef	MBCACHE_SCAN	mbcache_scan ;
typedef	MBCACHE_INFO	mbcache_info ;

EXTERNC_begin

extern int mbcache_start(mbcache *,cchar *,int,mailbox *) noex ;
extern int mbcache_mbfile(mbcache *,char *,int) noex ;
extern int mbcache_mbinfo(mbcache *,mbcache_info *) noex ;
extern int mbcache_count(mbcache *) noex ;
extern int mbcache_countdel(mbcache *) noex ;
extern int mbcache_sort(mbcache *) noex ;
extern int mbcache_msgoff(mbcache *,int,off_t *) noex ;
extern int mbcache_msglines(mbcache *,int,int *) noex ;
extern int mbcache_msginfo(mbcache *,int,mbcache_scan **) noex ;
extern int mbcache_msgscan(mbcache *,int,mbcache_scan **) noex ;
extern int mbcache_msghdrtime(mbcache *,int,time_t *) noex ;
extern int mbcache_msgenvtime(mbcache *,int,time_t *) noex ;
extern int mbcache_msgtimes(mbcache *,int,time_t *) noex ;
extern int mbcache_msgflags(mbcache *,int) noex ;
extern int mbcache_msgsetflag(mbcache *,int,int,int) noex ;
extern int mbcache_msgsetlines(mbcache *,int,int) noex ;
extern int mbcache_msgdel(mbcache *,int,int) noex ;
extern int mbcache_msgdeldup(mbcache *) noex ;
extern int mbcache_finish(mbcache *) noex ;

EXTERNC_end


#endif /* MBCACHE_INCLUDE */


