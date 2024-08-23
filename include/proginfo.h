/* proginfo HEADER */
/* lang=C++20 */

/* program information */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	PROGINFO_INCLUDE
#define	PROGINFO_INCLUDE
#ifdef	__cplusplus


#include	<envstandards.h>	/* ordered first to configure */
#include	<usystem.h>
#include	<vecstr.h>
#include	<ids.h>
#include	<logfile.h>

#include	<proglog.hh>
#include	<progmsgid.hh>
#include	<proguserlist.hh>


#define	PROGINFO_FL	struct proginfo_flags


enum proginfomems {
	proginfomem_ncpu,
	proginfomem_overlast
} ;

struct proginfo ;

struct proginfo_flags {
	uint		progdash:1 ;	/* leading dash on program-name */
	uint		akopts:1 ;
	uint		aparams:1 ;
	uint		quiet:1 ;
	uint		ignore:1 ;
	uint		errfile:1 ;
	uint		outfile:1 ;
	uint		pcsconf:1 ;
	uint		cfname:1 ;
	uint		lfname:1 ;
	uint		pidfname:1 ;
	uint		logprog:1 ;
	uint		config:1 ;
	uint		watch:1 ;
	uint		background:1 ;
	uint		daemon:1 ;
	uint		logsize:1 ;
	uint		nodeonly:1 ;
	uint		tmpdate:1 ;
	uint		disable:1 ;
	uint		all:1 ;
	uint		def:1 ;
	uint		lister:1 ;
	uint		bufwhole:1 ;
	uint		bufline:1 ;
	uint		bufnone:1 ;
	uint		intrun:1 ;
	uint		intidle:1 ;
	uint		intpoll:1 ;
	uint		intmark:1 ;
	uint		intlock:1 ;
	uint		intdis:1 ;
	uint		reuseaddr:1 ;
	uint		to:1 ;
} ;

struct proginfo_hwser {
	proginfo	*op = nullptr ;
	uint		val ;
	void operator () (proginfo *) noex ;
	operator uint() noex ;
} ;

struct proginfo_co {
	proginfo	*op = nullptr ;
	int		w = -1 ;
	void operator () (proginfo *p,int m) noex {
	    op = p ;
	    w = m ;
	} ;
	int operator () (int = -1) noex ;
	operator int () noex {
	    return operator () () ;
	} ;
} ;

struct proginfo_vals {
	cchar		*argz ;		/* raw ARGZ */
	cchar		*execname ;	/* execution filename */
	cchar		*progname ;	/* program name */
	cchar		*progdname ;	/* dirname of arg[0] */
	cchar		*searchname ;
	cchar		*pr ;		/* program root */
	cchar		*rootname ;	/* distribution name */
	cchar		*version ;
	cchar		*banner ;
	cchar		*umachine ;	/* UNAME machine name */
	cchar		*usysname ;	/* UNAME OS system-name */
	cchar		*urelease ;	/* UNAME OS release */
	cchar		*uversion ;	/* UNAME OS version */
	cchar		*architecture ;	/* UAUX machine architecture */
	cchar		*platform ;	/* UAUX machine platform */
	cchar		*provider ;	/* UAUX machine provider */
	cchar		*nisdomain ;	/* UAUX machine nisdomain */
	cchar		*hz ;		/* OS HZ */
	cchar		*nodename ;	/* USERINFO */
	cchar		*domainname ;	/* USERINFO */
	cchar		*username ;	/* USERINFO */
	cchar		*homedname ;	/* USERINFO */
	cchar		*shell ;	/* USERINFO */
	cchar		*org ;		/* USERINFO */
	cchar		*gecosname ;	/* USERINFO */
	cchar		*realname ;	/* USERINFO */
	cchar		*name ;		/* USERINFO */
	cchar		*fullname ;	/* USERINFO full-name */
	cchar		*mailname ;	/* USERINFO mail-abbreviated-name */
	cchar		*tz ;		/* USERINFO */
	cchar		*maildname ;	/* USERINFO */
	cchar		*logid ;	/* USERINFO ID for logging purposes */
	cchar		*orgcode ;
	cchar		*groupname ;
	cchar		*hostname ;
	cchar		*tmpdname ;
	cchar		*newsdname ;
	cchar		*hfname ;
	cchar		*cfname ;
	cchar		*lfname ;
	cchar		*pidfname ;
	void		*efp ;
	void		*buffer ;	/* general buffer */
	void		*contextp ;	/* SHELL context */
	void		*lip ;		/* local information */
	void		*uip ;		/* USERINFO object */
	void		*userlist ;	/* user-list state */
	void		*config ;	/* configuration */
	void		*watch ;	/* watch */
	void		*pcsconf ;	/* save space when not needed */
	int		progmode ;	/* program mode */
	int		debuglevel ;
	int		verboselevel ;
	int		quietlevel ;
	int		to ;		/* general time-out */
	int		to_open ;	/* open time-out */
	int		to_read ;	/* read time-out */
	int		n ;
	int		logsize ;	/* max log-file size */
	int		intrun ;	/* interval run */
	int		intidle ;	/* interval idle */
	int		intpoll ;	/* interval poll */
	int		intmark ;	/* interval mark */
	int		intlock ;	/* interval lock */
	int		intdis ;	/* interval disable */
	int		pserial ;	/* "pserial" serial number */
	int		serial ;	/* serial number */
	int		ncpus ;		/* internal storage */
	proginfo_vals() noex ;
} ; /* end struct (proginfo_vals) */

struct proginfo : proginfo_vals {
	friend		proginfo_co ;
	proginfo_hwser	hwserial ;
	proginfo_co	ncpu ;
	proginfo_co	finish ;
	proginfo_co	rootdname ;
	proginfo_co	progename ;
	proginfo_co	nodename ;
	vecstr		*sdp ;		/* store-data-pointer */
	ids		*idp ;
	logfile		*lhp ;
	mainv		argv ;
	mainv		envv ;
	PROGINFO_FL	have{} ;
	PROGINFO_FL	pf{} ;
	PROGINFO_FL	changed{} ;
	PROGINFO_FL	open{} ;
	TIMEB		now ;
	time_t		daytime ;
	pid_t		pid ;
	uid_t		uid, euid ;
	gid_t		gid, egid ;
	int		argc ;
	proginfo() noex ;
	void args(int ac,mainv av,mainv ev) noex ;
	int start(mainv,mainv,cchar *) noex ;
	int setprogroot(cchar *,int) noex ;
	int rootexecname(cchar *) noex ;
	int setentry(cchar **,cchar *,int) noex ;
	int setversion(cchar *) noex ;
	int setbanner(cchar *) noex ;
	int setsearchname(cchar *,cchar *) noex ;
	int setprogname(cchar *) noex ;
	int setexecname(cchar *) noex ;
	int getpwd(char *,int) noex ;
	int getename(char *,int) noex ;
	int finish() noex ;
	int expand(char *,int,cchar *,int) noex ;
   private:
	int incpu() noex ;
	int irootdname() noex ;
	int iprogename() noex ;
	int inodename() noex ;
} /* end struct (proginfo) */

typedef	PROGINFO_FL	proginfo_fl ;

EXTERNC_begin

extern int	proginfo_realbegin(proginfo *) noex ;
extern int	proginfo_realend(proginfo *) noex ;

EXTERNC_end


#endif /* __cplusplus */
#endif /* PROGINFO_INCLUDE */


