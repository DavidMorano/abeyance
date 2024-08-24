/* usys_streams HEADER */
/* lang=C20 */

/* miscelllaneous (XXX) operating system support */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	General:
	This file contains the UNIX® system types that the brain-damaged
	MacOS operating system does NOT have.  We are trying in a very
	small way to make up for some of the immense brain-damage within
	the Apple Darwin operating system.  This particular file provides
	link-time symbols for emulating a broken UNIZ® STREAMS®
	interface.

	Name:
	strmsgget
	strmsggetp
	strmsgput
	strmsgputp

	Description:
	This module manages UNIX® STREAMS®.  These are the STREAMS®
	invented by Dennis Ritchie (of AT&T Bell Laboratories fame).
	The STREAMS® framework first appeared in UNIX® System V
	Release 3 (and in my opinion was a huge success there; I
	used it myself back in the day).  The STREAMS® framework
	was ported to UNIX® System V Release 4 by others.  For
	completeness, the people who ported STREAMS® to UNIX® System
	V Release 4 were: Robert Israel, Gil McGrath, Dave Olander,
	Her-Daw Che, and Maury Bach.

	Synopsis:
	unixret_t strmsgget(int fd,SB *cmp,SB *dmp,int *fp) noex
	unixret_t strmsggetp(int fd,SB *cmp,SB *dmp,int *bp,int *fp) noex
	unixret_t strmsgput(int fd,SB *cmp,SB *dmp,int flags) noex
	unixret_t strmsgputp(int fd,SB *cmp,SB *dmp,int band,int flags) noex

	Arguments:
	fd		file-descriptor
	cmp		control-message-pointer
	dmp		data-message-pointer
	fp		pointer to flags (an integer)
	bp		pointer to priority-band (an integer)
	flag		flags

	Returns:
	>=0		OK
	<0		error code (system-return)

*******************************************************************************/

#ifndef	USYSSTREAMS_INCLUDE
#define	USYSSTREAMS_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


#ifndef	STRBUF
#define	STRBUF		struct strbuf
#endif

#ifndef	STRPEEK
#define	STRPEEK		struct strpeek
#endif

#ifndef	STRRECVFD
#define	STRRECVFD	struct strrecvfd
#endif

#ifndef	STRIOCTL	
#define	STRIOCTL	struct strioctl
#endif


/* STREAMS begin */
#if	defined(SYSHAS_STREAMS) && (SYSHAS_STREAMS > 0)

/* system has STREAMS® */
#include	<stropts.h>

#else /* defined(SYSHAS_STREAMS) && (SYSHAS_STREAMS > 0) */

#ifndef	I_STREAMBASE
#define	I_STREAMBASE	('S'+100)
#endif

#ifndef	I_STR
#define	I_STR		(I_STREAMBASE+0)
#endif

#ifndef	I_PUSH
#define	I_PUSH		(I_STREAMBASE+1)
#endif

#ifndef	I_PEEK
#define	I_PEEK		(I_STREAMBASE+2)
#endif

#ifndef	I_SENDFD
#define	I_SENDFD	(I_STREAMBASE+3)
#endif

#ifndef	I_RECVFD
#define	I_RECVFD	(I_STREAMBASE+4)
#endif

#ifndef	I_SRDOPT
#define	I_SRDOPT	(I_STREAMBASE+5)
#endif

#ifndef	ISPTM		/* ask if FD is a pseudo-terminal */
#define	ISPTM		(I_STREAMBASE+6)
#endif

#ifndef	RMSGD
#define	RMSGD		(I_STREAMBASE+7)
#endif


struct strbuf {
	char		*buf ;
	int		len ;
	int		maxlen ;
} ;

struct strpeek {
	STRBUF		ctlbuf ;
	STRBUF		databuf ;
	uint		flags ;
} ;

struct strrecvfd {      
        int		fd ;
        uid_t		uid ;
        gid_t		gid ;
        char		fill[8] ;
} ;

struct strioctl {
	char		*ic_dp ;	/* data pointer */
	int		ic_len ;	/* data length */
	int		ic_cmd ;	/* command */
	int		ic_timout ;	/* timeout */
} ;

EXTERNC_begin

extern unixret_t isastream(int) noex ;
extern unixret_t fattach(int,cchar *) noex ;
extern unixret_t fdetach(cchar *) noex ;

extern unixret_t getmsg(int,STRBUF *,STRBUF *,int *) noex ;
extern unixret_t getpmsg(int,STRBUF *,STRBUF *,int *,int *) noex ;
extern unixret_t putmsg(int,STRBUF *,STRBUF *,int) noex ;
extern unixret_t putpmsg(int,STRBUF *,STRBUF *,int,int) noex ;

EXTERNC_end

#endif /* defined(SYSHAS_STREAMS) && (SYSHAS_STREAMS > 0) */
/* STREAMS end */


#endif /* USYSSTREAMS_INCLUDE */


