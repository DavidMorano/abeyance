/* maintqotd HEADER */
/* lang=C20 */

/* maintenance of the QOTD facility */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MAINTQOTD_INCLUDE
#define	MAINTQOTD_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<ids.h>
#include	<vecstr.h>
#include	<vecpstr.h>
#include	<localmisc.h>		/* extra types */


#define	MAINTQOTD_SEARCHNAME	"maintqotd"
#define	MAINTQOTD_PRNAME	"LOCAL"
#define	MAINTQOTD_PROGEXEC	"qotd"
#define	MAINTQOTD_PROGMKQOTD	"helloworld"
#define	MAINTQOTD_CONFMAGIC	0x8932170
#define	MAINTQOTD		struct maintqotd_head
#define	MAINTQOTD_FL		struct maintqotd_flags


struct maintqotd_flags {
	uint		stores:1 ;
	uint		id:1 ;
	uint		hosts:1 ;
	uint		sources:1 ;
	uint		logsub:1 ;
	uint		logsize:1 ;
	uint		spooldir:1 ;
	uint		lfname:1 ;
	uint		to:1 ;
} ;

struct maintqotd_head {
	vecstr		stores ;
	vecpstr		hosts ;
	vecpstr		sources ;
	MAINTQOTD_FL	f, have, changed, final ;
	MAINTQOTD_FL	open ;
	ids		id ;
	cchar		*pr ;
	cchar		*pn ;		/* program-name */
	cchar		*sn ;		/* search-name */
	cchar		*nn ;		/* node-name */
	cchar		*dn ;		/* domain-name */
	cchar		*un ;		/* user-name */
	cchar		*logid ;	/* log-ID */
	cchar		*lfname ;	/* log file-name */
	cchar		*hostname ;
	cchar		*spooldname ;	/* spool directory */
	cchar		*qdname ;	/* particular quote directory */
	void		*config ;	/* configuration state */
	void		*logsub ;	/* log-file state */
	uid_t		euid ;
	uid_t		uid_pr ;
	gid_t		gid_pr ;
	time_t		dt ;
	int		of ;
	int		to ;
	int		mjd ;
	int		logsize ;
	mode_t		om ;
} ;

EXTERNC_begin

extern int maintqotd(cchar *,int,int,int) noex ;

EXTERNC_end


#endif /* MAINTQOTD_INCLUDE */


