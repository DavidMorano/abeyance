/* ut_connect SUPPORT */
/* lang=C++20 */

/* UNIX® XTI subroutine */
/* version %I% last-modified %G% */

#define	CF_ISCONN	0		/* change meaning of SR_ISCONN? */
#define	CF_BADSOLARIS	0		/* bad Solaris? */

/* revision history:

	= 1989-05-04, David A­D­ Morano
	I needed this subroutine (and the whole 'ut' set of
	subroutines) becauase one cannot connect to a 'ticotsord'
	transport with a UNIX® domain socket.  This may have been
	possible in the past but must have gone away sometime around
	1990 or so, maybe.  It probably went away when some smart
	person working on UNIX® System V Release 4 networking decided
	to make their sockets work more like the ones in BSD!

	= 1992-02-14, David A­D­ Morano
	I updated this subroutine with some stuff from the 'u_connect()'
	subroutine that has to do with a connect attempt after one
	was previously done but in which the previous one was done
	with the file descriptor in non-blocking mode and the latter
	one done with the file descriptor in blocking mode.  Does
	that ever really happen (anymore)?  I guess that it did at
	one time!  With all of the changes to the way sockets work
	now-a-days in different OSes, who can know what happens
	when (really)!

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This subroutine does what the socket counter part 'u_connect()'
	does.  It is pretty much similar but the semantics of the
	call are not entirely clear.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<poll.h>
#include	<xti.h>
#include	<errno.h>
#include	<usystem.h>


/* local defines */

#define	TO_NOMEM	60			/* seconds */
#define	TO_NOSR		(5 * 60)		/* seconds */
#define	TO_CONNECT	(5 * 60)		/* seconds */
#define	POLLTIMEOUT	(1 * 1000)		/* milliseconds */

#ifndef	UTCALL
#define	UTCALL		struct t_call
#endif


/* external subroutines */

extern "C" {
    extern int	snxtierr(char *,int,int) noex ;
}


/* external variables */


/* local structures */

struct connect_flags {
	uint	checkblock:1 ;
	uint	nonblock:1 ;
} ;


/* forward references */

static int checkconnect(struct connect_flags *,int) noex ;
static int lconnect(int,UTCALL *,RCALL *) noex ;
static int	lconnect() ;


/* exported variables */


/* exported subroutines */

int ut_connect(int fd,UTCALL *sndcall,UTCALL *rcvcall) noex {
	struct connect_flags	f = { FALSE, FALSE } ;
	int		rs ;
	int		rs2 ;
	int		to_nosr = TO_NOSR ;

again:
	rs = lconnect(fd,sndcall,rcvcall) ;

	if (rs < 0) {
	    switch (rs) {
	    case SR_NOSR:
	        if (to_nosr-- > 0) goto retry ;
	        break ;
	    case SR_INTR:
	        goto again ;
/* handle the case when it is still outstanding if we can */
	    case SR_ALREADY:
	    case SR_PROTO:
	        rs2 = checkconnect(&f,fd) ;
	        if (rs2 < 0) {
	            rs = rs2 ;
	            goto ret0 ;
	        }
	        if (! f.nonblock) {
	            struct pollfd	fds[2] ;
	            int	nfds ;
	            int	looptimeout = (TO_CONNECT * 1000) ;
	            nfds = 0 ;
	            fds[nfds].fd = fd ;
	            fds[nfds].events = POLLOUT ;
	            fds[nfds].revents = 0 ;
	            nfds += 1 ;
	            while (looptimeout > 0) {
	                rs = u_poll(fds,nfds,POLLTIMEOUT) ;
	                if (rs > 0) {
	                    int	re = fds[0].revents ;
	                    rs = SR_OK ;
	                    if (re & POLLOUT) {
#if	CF_BADSOLARIS
	                        rs = lconnect(fd,sndcall,rcvcall) ;
/* is it connected successfully yet? */
	                        if (rs == SR_ISCONN)
	                            rs = SR_OK ;
#endif /* CF_BADSOLARIS */
	                        if (rs >= 0) break ;
#if	CF_BADSOLARIS
/* is it still in progress? */
	                        if (rs == SR_ALREADY)
	                            rs = SR_OK ;
#endif /* CF_BADSOLARIS */
	                    } else if (re & POLLHUP) {
	                        rs = SR_HANGUP ;
	                    } else if (re & POLLERR) {
	                        rs = SR_POLLERR ;
	                    } else if (re & POLLNVAL)
	                        rs = SR_NOTOPEN ;
	                    if (rs < 0) break ;
	                } /* end if */
	                looptimeout -= POLLTIMEOUT ;
	            } /* end while */
	            if (looptimeout <= 0) {
	                rs = SR_TIMEDOUT ;
		    }
	        } /* end if (waiting for connection to complete) */
	        break ;
#if	CF_ISCONN
	    case SR_ISCONN:
	        rs2 = checkconnect(&f,s) ;
	        if (rs2 < 0) {
	            rs = rs2 ;
	            goto baderr ;
	        }
	        if (! f.nonblock)
	            rs = SR_OK ;
#else
	    case SR_ISCONN:
	        break ;
#endif /* CF_ISCONN */

	    } /* end switch */
	} /* end if (error) */

ret0:
	return rs ;

/* retry operation */
retry:
	msleep(1000) ;
	goto again ;
}
/* end subroutine (ut_connect) */


/* local subroutines */

static int checkconnect(struct connect_flags *fp,int fd) noex {
	int		rs = SR_OK ;

	if (! fp->checkblock) {

	    fp->checkblock = TRUE ;
	    rs = u_fcntl(fd,F_GETFL,0) ;

	    if (rs & O_NONBLOCK) {
	        fp->nonblock = TRUE ;
	    }

	} /* end if (block check) */

	return rs ;
}
/* end subroutine (checkconnect) */

static int lconnect(int fd,UTCALL *sndcall,RCALL *rcvcall) noex {
	int		rs ;

	rs = t_connect(fd,sndcall,rcvcall) ;

	if (rs < 0) {
	    switch (t_errno) {
	    case TACCES:
	        rs = SR_ACCES ;
	        break ;
	    case TBADADDR:
	        rs = SR_DESTADDRREQ ;
	        break ;
	    case TBADDATA:
	        rs = SR_TOOBIG ;
	        break ;
	    case TBADF:
	        rs = SR_NOTSOCK ;
	        break ;
	    case TBADOPT:
	        rs = SR_PROTOTYPE ;
	        break ;
	    case TBUFOVFLW:
	        rs = SR_OVERFLOW ;
	        break ;
	    case TLOOK:
	        rs = SR_LOOK ;
	        break ;
/* this is what is returned when connecting asynchronously */
	    case TNODATA:
	        rs = SR_OK ;
	        break ;
	    case TNOTSUPPORT:
	        rs = SR_OPNOTSUPP ;
	        break ;
	    case TOUTSTATE:
	        rs = SR_NOPROTOOPT ;
	        break ;
	    case TSYSERR:
	        rs = (- errno) ;
	        break ;
	    } /* end switch */
	} /* end if */

	return rs ;
}
/* end subroutine (lconnect) */


