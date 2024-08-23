/* mailbox HEADER */
/* lang=C20 */

/* mailbox handling object */
/* version %I% last-modified %G% */


/* revision history:

	= 2009-01-10, David A­D­ Morano
        This is being written from scratch to finally get an abstracted
        "mailbox" that is fast enough for interactive use.

*/

/* Copyright © 2009 David A­D­ Morano.  All rights reserved. */

#ifndef	MAILBOX_INCLUDE
#define	MAILBOX_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/param.h>
#include	<unistd.h>
#include	<utypedefs.h>
#include	<usysrets.h>
#include	<clanguage.h>
#include	<vecobj.h>
#include	<vecstr.h>
#include	<localmisc.h>


/* object defines */
#define	MAILBOX_MAGIC		0x31415926
#define	MAILBOX			struct mailbox_head
#define	MAILBOX_INFO		struct mailbox_information
#define	MAILBOX_MI		struct mailbox_msginfo
#define	MAILBOX_READ		struct mailbox_reader
#define	MAILBOX_FL		struct mailbox_flags
#define	MAILBOX_MFL		struct mailbox_msgflags

/* options */
#define	MAILBOX_ORDONLY		O_RDONLY	/* open read-only */
#define	MAILBOX_ORDWR		O_RDWR		/* open read-write */
#define	MAILBOX_ONOCLEN		O_NOCTTY	/* !use "content-length" */
#define	MAILBOX_OUSECLINES	O_NDELAY	/* use 'content-clines" */


struct mailbox_information {
	int		nmsgs ;			/* messages total */
	int		nclens ;		/* messages with CLENs */
} ;

struct mailbox_flags {
	uint		readlock:1 ;
	uint		writelock:1 ;
	uint		readonly:1 ;		/* opened read-only */
	uint		useclen:1 ;
	uint		useclines:1 ;
	uint		rewrite:1 ;
} ;

struct mailbox_head {
	vecobj		*mlp ;		/* Message-List-Pointer */
	cchar		*mailfname ;
	time_t		ti_mod ;	/* modification time */
	time_t		ti_check ;	/* check time */
	MAILBOX_FL	f ;
	uint		magic ;
	int		pagesize ;
	int		mfd ;		/* mail file-descriptor */
	int		mblen ;		/* mailbox file length */
	int		msgs_total ;
	int		msgs_clen ;
	int		msgs_del ;
	int		to_lock ;	/* lock timeout */
	int		to_read ;	/* read timeout */
	int		mflags ;	/* open-flags */
} ;

struct mailbox_msgflags {
	uint		env:1 ;		/* had an environment marker */
	uint		senv:1 ;	/* starting environment marker */
	uint		hdradds:1 ;	/* HDRADDS initialized */
	uint		clen:1 ;	/* CLEN header */
	uint		clines:1 ;	/* CLINES header */
	uint		lines:1 ;	/* LINES header */
	uint		xlines:1 ;	/* XLINES header */
	uint		status:1 ;	/* unused: STATUS header */
	uint		sem:1 ;		/* unused: SEM header */
	uint		mlen:1 ;
	uint		blen:1 ;
	uint		msgread:1 ;	/* unused: message has been 'read' */
	uint		msgold:1 ;	/* unused: message is 'old' */
	uint		msgdel:1 ;	/* marked for deletion */
	uint		addany:1 ;	/* anything (something) being added */
} ;

struct mailbox_msginfo {
	vecstr		hdradds ;	/* HDRs to be added */
	MAILBOX_MFL	hdr, hdrval, hdradd, f, cmd ;
	off_t		moff ;		/* offset to start of message */
	off_t		hoff ;		/* offset to top of headers */
	off_t		soff ;		/* offset to semaphore */
	off_t		boff ;		/* offset to message body */
	uint		hash[8] ;	/* ?? */
	int		mlen ;		/* total "message" length */
	int		hlen ;		/* total header-area length */
	int		blen ;		/* total "body" length */
	int		clen ;		/* content-length (HDR) */
	int		clines ;	/* content-lines (HDR) */
	int		lines ;		/* lines (?) */
	int		xlines ;	/* xlines (?) */
	int		msgi ;		/* message index */
} ;

struct mailbox_reader {
	char		*rbuf ;
	char		*rbp ;
	off_t		foff ;		/* file offset */
	off_t		roff ;		/* read offset */
	int		rsize ;
	int		rlen ;
} ;

#ifdef	COMMENT

/* processed values */
struct mailbox_msgvalues {
	cchar	*efrom ;	/* envelope FROM */
	cchar	*edate ;	/* envelope DATE */
	cchar	*eremote ;	/* envelope REMOTE */
	cchar	*received ;	/* headers "received" */
	cchar	*subject ;	/* header "subject" */
	cchar	*ctype ;	/* header "content-type" */
	cchar	*from ;		/* header "from" */
	cchar	*date ;		/* header "date" */
	cchar	*to ;		/* header "to" */
	cchar	*cc ;		/* header "cc" */
	cchar	*status ;	/* header "status" */
	cchar	*mid ;		/* message ID "message-id" */
} ;

#endif /* COMMENT */

#ifdef	COMMENT
struct mailbox_headkey {
	int		dummy ;
} ;
#endif /* COMMENT */

typedef MAILBOX			mailbox ;
typedef MAILBOX_READ		mailbox_read ;
typedef MAILBOX_INFO		mailbox_info ;
typedef MAILBOX_FL		mailbox_fl ;
typedef MAILBOX_MFL		mailbox_mfl ;
typedef MAILBOX_MI		mailbox_mi ;

EXTERNC_begin

extern int mailbox_open(mailbox *,cchar *,int) noex ;
extern int mailbox_getinfo(mailbox *,mailbox_info *) noex ;
extern int mailbox_count(mailbox *) noex ;
extern int mailbox_mbfile(mailbox *,char *,int) noex ;
extern int mailbox_check(mailbox *,time_t) noex ;
extern int mailbox_msgoff(mailbox *,int,off_t *) noex ;
extern int mailbox_msgret(mailbox *,int,mailbox_mi **) noex ;
extern int mailbox_msgdel(mailbox *,int,int) noex ;
extern int mailbox_msghdradd(mailbox *,int,cchar *,cchar *,int) noex ;
extern int mailbox_countdel(mailbox *) noex ;
extern int mailbox_readbegin(mailbox *,mailbox_read *,off_t,int) noex ;
extern int mailbox_readln(mailbox *,mailbox_read *,char *,int) noex ;
extern int mailbox_readend(mailbox *,mailbox_read *) noex ;
extern int mailbox_close(mailbox *) noex ;

#ifdef	COMMENT
extern int mailbox_msgread(mailbox *,int,char *,int) noex ;
extern int mailbox_msgreadln(mailbox *,int,char *,int) noex ;
#endif

EXTERNC_end

#ifdef	__cplusplus

template<typename ... Args>
inline int mailbox_magic(mailbox *op,Args ... args) noex {
	int		rs = SR_FAULT ;
	if (op && (args && ...)) {
	    rs = (op->magic == MAILBOX_MAGIC) ? SR_OK : SR_NOTOPEN ;
	}
	return rs ;
}
/* end subroutine (mailbox_magic) */

#endif /* __cplusplus */


#endif /* MAILBOX_INCLUDE */


