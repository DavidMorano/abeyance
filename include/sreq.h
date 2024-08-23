/* sreq HEADER */
/* lang=C++20 */

/* Service-Request */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	SREQ_INCLUDE
#define	SREQ_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/param.h>		/* for MAXPATHLEN */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<sockaddress.h>
#include	<osetstr.h>
#include	<localmisc.h>		/* |MAXPATHLEN| */

#include	"mfslocinfo.h"
#include	"mfserve.h"
#include	"svcentsub.h"


#define	SREQ		struct sreq
#define	SREQ_FL		struct sreq_flags
#define	SREQ_SNCUR	struct sreq_sncursor
#define	SREQ_MAGIC	0x65918233
#define	SREQ_JOBIDLEN	15		/* same as LOGIDLEN? */
#define	SREQ_SVCBUFLEN	(5*MAXPATHLEN)	/* max service-buffer length */


enum sreqstates {
	sreqstate_acquire,		/* acquire service string */
	sreqstate_svc,			/* have service string */
	sreqstate_program,		/* spawned program (process) */
	sreqstate_thread,		/* spawned thread */
	sreqstate_done,			/* job finished */
	sreqstate_overlast
} ;

struct sreq_sncursor {
	osetstr_cur	cur ;
} ;

struct sreq_flags {
	uint		longopt:1 ;		/* the "long" switch */
	uint		process:1 ;
	uint		thread:1 ;
	uint		shlib:1 ;
	uint		ss:1 ;
	uint		builtout:1 ;
	uint		builtdone:1 ;
	uint		namesvcs:1 ;		/* service names (for 'help') */
} ;

struct sreq_head {
	sockaddress	sa ;			/* peername socket address */
	SVCENTSUB	ss ;
	osetstr		namesvcs ;		/* service names (for 'help') */
	MFSERVE_INFO	binfo ;			/* buuilt-info info */
	void		*sop ;			/* shared-object handle */
	void		*objp ;			/* object pointer */
	cchar		**av ;			/* argument vector */
	cchar		*argstab ;		/* argument strings */
	cchar		*peername ;
	cchar		*netuser ;
	cchar		*netpass ;
	cchar		*netident ;
	cchar		*svcbuf ;		/* service-buffer */
	cchar		*svc ;			/* allocated */
	cchar		*subsvc ;
	char		*efname ;		/* Error-File-Name */
	time_t		stime ;			/* time-start */
	time_t		etime ;			/* time-end */
	pid_t		pid ;			/* child PID */
	pthread_t	tid ;			/* child thread ID */
	SREQ_FL		open, f ;
	uint		magic ;
	volatile int	f_exiting ;
	int		ji ;			/* job number in DB */
	int		jsn ;			/* job serial number */
	int		nav ;			/* number arguments */
	int		salen ;			/* peername socket length */
	int		nnames ;		/* number of names */
	int		ifd ;			/* file-descriptor input */
	int		ofd ;			/* output */
	int		efd ;			/* error */
	int		jtype ;			/* job-type */
	int		stype ;			/* sub-type */
	int		state ;			/* job state (see above) */
	int		svclen ;		/* service-length */
	int		trs ;			/* thread return-status */
	char		logid[SREQ_JOBIDLEN+1] ;
} ;

typedef	SREQ		sreq ;
typedef	SREQ_FL		sreq_fl ;
typedef	SREQ_SNCUR	sreq_sncur ;

EXTERNC_begin

extern int sreq_start(sreq *,cchar *,cchar *,int,int) noex ;
extern int sreq_typeset(sreq *,int,int) noex ;
extern int sreq_getfd(sreq *) noex ;
extern int sreq_havefd(sreq *,int) noex ;
extern int sreq_svcaccum(sreq *,cchar *,int) noex ;
extern int sreq_svcmunge(sreq *) noex ;
extern int sreq_svcparse(sreq *,int) noex ;
extern int sreq_setlong(sreq *,int) noex ;
extern int sreq_setstate(sreq *,int) noex ;
extern int sreq_getjsn(sreq *) noex ;
extern int sreq_getsvc(sreq *,cchar **) noex ;
extern int sreq_getsubsvc(sreq *,cchar **) noex ;
extern int sreq_getav(sreq *,cchar ***) noex ;
extern int sreq_getstate(sreq *) noex ;
extern int sreq_getstdin(sreq *) noex ;
extern int sreq_getstdout(sreq *) noex ;
extern int sreq_ofd(sreq *) noex ;
extern int sreq_closestdin(sreq *) noex ;
extern int sreq_closestdout(sreq *) noex ;
extern int sreq_closefds(sreq *) noex ;
extern int sreq_svcentbegin(sreq *,LOCINFO *,SVCENT *) noex ;
extern int sreq_svcentend(sreq *) noex ;
extern int sreq_exiting(sreq *) noex ;
extern int sreq_thrdone(sreq *) noex ;
extern int sreq_sncreate(sreq *) noex ;
extern int sreq_snadd(sreq *,cchar *,int) noex ;
extern int sreq_snbegin(sreq *,SREQ_SNCUR *) noex ;
extern int sreq_snenum(sreq *,SREQ_SNCUR *,cchar **) noex ;
extern int sreq_snend(sreq *,SREQ_SNCUR *) noex ;
extern int sreq_sndestroy(sreq *) noex ;
extern int sreq_builtload(sreq *,MFSERVE_INFO *) noex ;
extern int sreq_builtrelease(sreq *) noex ;
extern int sreq_objstart(sreq *,cchar *,cchar **) noex ;
extern int sreq_objcheck(sreq *) noex ;
extern int sreq_objabort(sreq *) noex ;
extern int sreq_objfinish(sreq *) noex ;
extern int sreq_stderrbegin(sreq *,cchar *) noex ;
extern int sreq_stderrclose(sreq *) noex ;
extern int sreq_stderrend(sreq *) noex ;
extern int sreq_finish(sreq *) noex ;

EXTERNC_end


#endif /* SREQ_INCLUDE */


