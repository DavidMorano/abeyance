/* mailmsgfile HEADER */
/* lang=C20 */

/* create and cache message content files */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#ifndef	MAILMSGFILE_INCLUDE
#define	MAILMSGFILE_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>
#include	<hdb.h>
#include	<localmisc.h>


#define	MAILMSGFILE_MAGIC	0x24182132
#define	MAILMSGFILE		struct mailmsgfile_head
#define	MAILMSGFILE_FL		struct mailmsgfile_flags
#define	MAILMSGFILE_MI		struct mailmsgfile_minfo

#define	MAILMSGFILE_STRLEN	100
#define	MAILMSGFILE_TZNAMELEN	10

#define	MAILMSGFILE_TTEMP	0
#define	MAILMSGFILE_TPERM	1


struct mailmsgfile_minfo {
	cchar		*a ;		/* memory allocation */
	cchar		*mid ;
	cchar		*mfname ;
	uint		nsize ;
	uint		vsize ;
	uint		nlines ;
	uint		vlines ;
} ;

struct mailmsgfile_flags {
	uint		mailnew:1 ;	/* new mail arrived */
	uint		files:1 ;	/* container initialized */
	uint		checkout:1 ;	/* thread is running */
} ;

struct mailmsgfile_head {
	hdb		*flp ;		/* File-List-Pointer */
	cchar		*tmpdname ;
	pthread_t	tid ;
	MAILMSGFILE_FL	f ;
	uint		magic ;
	int		pagesize ;
	int		cols ;
	int		ind ;
	int		to ;
	volatile int	f_checkdone ;	/* thread has completed */
} ;

typedef MAILMSGFILE	mailmsgfile ;
typedef MAILMSGFILE_FL	mailmsgfile_fl ;
typedef MAILMSGFILE_MI	mailmsgfile_mi ;

EXTERNC_begin

extern int mailmsgfile_start(mailmsgfile *,cchar *,int,int) noex ;
extern int mailmsgfile_new(mailmsgfile *,int,cchar *,int,off_t,int) noex ;
extern int mailmsgfile_get(mailmsgfile *,cchar *,cchar **) noex ;
extern int mailmsgfile_msginfo(mailmsgfile *,mailmsgfile_mi **,cchar *) noex ;
extern int mailmsgfile_finish(mailmsgfile *) noex ;

EXTERNC_end


#endif /* MAILMSGFILE_INCLUDE */


