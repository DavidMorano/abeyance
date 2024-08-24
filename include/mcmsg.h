/* mcmsg HEADER */
/* lang=C20 */

/* create and parse mail-cluster IPC messages */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MCMSG_INCLUDE
#define	MCMSG_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/param.h>
#include	<usystem.h>
#include	<localmisc.h>


#ifndef	LOGNAMELEN
#define	LOGNAMELEN	32
#endif

#ifndef	NODENAMELEN
#define	NODENAMELEN	257		/* System V */
#endif

#ifndef	MAILADDRLEN
#define	MAILADDRLEN	(3 * MAXHOSTNAMELEN)
#endif

#define	MCMSG_REQ		struct mcmsg_request
#define	MCMSG_REP		struct mcmsg_report
#define	MCMSG_ACK		struct mcmsg_acknowledge
#define	MCMSG_LMAILUSER		LOGNAMELEN
#define	MCMSG_LCLUSTER		NODENAMELEN
#define	MCMSG_LMSGID		MAILADDRLEN
#define	MCMSG_LFROM		MAILADDRLEN


/* client request message */
struct mcmsg_request {
	uint	msglen ;
	uint	tag ;
	uint	timestamp ;
	char	cluster[MCMSG_LCLUSTER + 1] ;
	char	mailuser[MCMSG_LMAILUSER + 1] ;
	uchar	msgtype ;
	uchar	seq ;
} ;

/* server report */
struct mcmsg_report {
	uint	msglen ;
	uint	tag ;
	uint	timestamp ;
	uint	mlen ;
	char	cluster[MCMSG_LCLUSTER + 1] ;
	char	mailuser[MCMSG_LMAILUSER + 1] ;
	char	msgid[MCMSG_LMSGID + 1] ;
	char	from[MCMSG_LFROM + 1] ;
	uchar	flags ;
	uchar	msgtype ;
	uchar	seq ;
	uchar	rc ;
} ;

/* general acknowledgement */
struct mcmsg_acknowledge {
	uint	msglen ;
	uint	tag ;
	uchar	msgtype ;
	uchar	seq ;
	uchar	rc ;
} ;

/* request types */
enum mcmsgtypes {
	mcmsgtype_request,
	mcmsgtype_report,
	mcmsgtype_ack,
	mcmsgtype_overlast
} ;

/* response codes */
enum mcmsgrcs {
	mcmsgrc_ok,
	mcmsgrc_invalid,
	mcmsgrc_notavail,
	mcmsgrc_goingdown,
	mcmsgrc_overlast
} ;

typedef MCMSG_REQ	mcmsg_req ;
typedef	MCMSG_REP	mcmsg_rep ;
typedef	MCMSG_ACK	mcmsg_ack ;

EXTERNC_begin

extern int	mcmsg_request(mcmsg_req *,int,char *,int) noex ;
extern int	mcmsg_report(mcmsg_rep *,int,char *,int) noex ;
extern int	mcmsg_acknowlege(mcmsg_ack *,int,char *,int) noex ;

EXTERNC_end


#endif /* MCMSG_INCLUDE */


