/* msgs.h HEADER */


/* Copyright © 2004 David A­D­ Morano.  All rights reserved. */


#ifndef	DEFS_INCLUDE
#define	DEFS_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<limits.h>
#include	<time.h>
#include	<vecstr.h>
#include	<logfile.h>
#include	<dater.h>
#include	<ids.h>
#include	<localmisc.h>


#ifndef	MSGBUFLEN
#define	MSGBUFLEN	2048
#endif

/* service name */
#ifndef	SVCNAMELEN
#define	SVCNAMELEN	32
#endif

/* mail address */
#ifndef	MAILADDRLEN
#define	MAILADDRLEN	(3 * MAXHOSTNAMELEN)
#endif

#ifndef	DEBUGLEVEL
#define	DEBUGLEVEL(n)	(pip->debuglevel >= (n))
#endif

#ifndef	KBUFLEN
#define	KBUFLEN		120
#endif

#ifndef	VBUFLEN
#define	VBUFLEN		(6 * MAXPATHLEN)
#endif

#ifndef	EBUFLEN
#define	EBUFLEN		(6 * MAXPATHLEN)
#endif


struct proginfo_flags {
	uint		progdash:1 ;
	uint		akopts:1 ;
	uint		aparams:1 ;
	uint		quiet:1 ;
	uint		outfile:1 ;
	uint		errfile:1 ;
	uint		configfile:1 ;
	uint		logfile:1 ;
	uint		pidfile:1 ;
	uint		logfname:1 ;
	uint		pidfname:1 ;
	uint		config:1 ;
	uint		daemon:1 ;
	uint		log:1 ;
	uint		logsize:1 ;
	uint		speed:1 ;
	uint		geekout:1 ;
	uint		nodeonly:1 ;
	uint		tmpdate:1 ;
	uint		disable:1 ;
	uint		all:1 ;
	uint		def:1 ;
	uint		list:1 ;
	uint		bufwhole:1 ;
	uint		bufline:1 ;
	uint		bufnone:1 ;
	uint		intrun:1 ;
	uint		intdis:1 ;
	uint		intpoll:1 ;
	uint		intlock:1 ;
	uint		intmark:1 ;
} ;

struct proginfo {
	vecstr		stores ;
	cchar	**envv ;
	cchar	*pwd ;
	cchar	*progename ;		/* execution filename */
	cchar	*progdname ;		/* dirname of arg[0] */
	cchar	*progname ;		/* basename of arg[0] */
	cchar	*pr ;			/* program root */
	cchar	*rootname ;		/* distribution name */
	cchar	*searchname ;
	cchar	*version ;
	cchar	*banner ;
	cchar	*nodename ;
	cchar	*domainname ;
	cchar	*username ;
	cchar	*groupname ;
	cchar	*name ;			/* person name */
	cchar	*logid ;
	cchar	*tmpdname ;
	cchar	*maildname ;
	cchar	*configfname ;
	cchar	*helpfname ;
	cchar	*logfname ;
	cchar	*pidfname ;
	void		*efp ;
	void		*buffer ;		/* general buffer */
	void		*lip ;			/* local information */
	void		*config ;		/* for MSU */
	void		*contextp ;		/* SHELL context */
	struct proginfo_flags	have, f, changed, finval ;
	struct proginfo_flags	open ;
	struct timeb	now ;
	LOGFILE		lh ;
	DATER		tmpdate, mdate ;
	IDS		id ;
	time_t		daytime ;
	pid_t		pid ;
	int		pwdlen ;
	int		progmode ;		/* program mode */
	int		debuglevel ;
	int		verboselevel ;
	int		to ;			/* general time-out */
	int		to_open ;		/* open time-out */
	int		to_read ;		/* read time-out */
	int		n ;
	int		logsize ;		/* max log-file size */
	int		intrun ;		/* run interval */
	int		intdis ;		/* disable interval */
	int		intpoll ;		/* poll interval */
	int		intmark ;		/* mark interval */
	int		intlock ;		/* lock interval */
	int		intspeed ;		/* speed-check interval */
	char		cmd[LOGIDLEN + 1] ;	/* for MSU */
	char		speedname[MAXNAMELEN + 1] ; /* really for MSU */
	char		zname[DATER_ZNAMELEN + 1] ;
} ;

struct pivars {
	cchar	*vpr1 ;
	cchar	*vpr2 ;
	cchar	*vpr3 ;
	cchar	*pr ;
	cchar	*vprname ;
} ;


#ifdef	__cplusplus
}
#endif

extern int proginfo_start(struct proginfo *,cchar **,cchar *,
			cchar *) ;
extern int proginfo_setentry(struct proginfo *,cchar **,cchar *,int) ;
extern int proginfo_setversion(struct proginfo *,cchar *) ;
extern int proginfo_setbanner(struct proginfo *,cchar *) ;
extern int proginfo_setsearchname(struct proginfo *,cchar *,cchar *) ;
extern int proginfo_setprogname(struct proginfo *,cchar *) ;
extern int proginfo_setexecname(struct proginfo *,cchar *) ;
extern int proginfo_setprogroot(struct proginfo *,cchar *,int) ;
extern int proginfo_pwd(struct proginfo *) ;
extern int proginfo_progdname(struct proginfo *) ;
extern int proginfo_progename(struct proginfo *) ;
extern int proginfo_nodename(struct proginfo *) ;
extern int proginfo_getpwd(struct proginfo *,char *,int) ;
extern int proginfo_getename(struct proginfo *,char *,int) ;
extern int proginfo_getenv(struct proginfo *,cchar *,int,cchar **) ;
extern int proginfo_finish(struct proginfo *) ;

#ifdef	__cplusplus
}
#endif

#endif /* DEFS_INCLUDE */


