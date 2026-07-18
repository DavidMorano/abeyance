/* conslog SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* send log messages to the system logger device */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This object module was originally written to create a logging
	mechanism for PCS application programs.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Object:
	conslog

	Description:
	These are the subroutines in this module:
		conslog_open
		conslog_write
		conslog_printf
		conslog_vprintf
		conslog_check
		conslog_close

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/syslog.h>		/* for all other 'LOG_xxx' */
#include	<unistd.h>		/* POSIX */
#include	<fcntl.h>		/* POSIX */
#include	<ctime>			/* CSTD */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdarg>		/* CSTD */
#include	<cstring>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<ascii.h>		/* LIBU */
#include	<ucmem.h>		/* LIBUC */
#include	<snwx.h>		/* LIBUC */
#include	<strn.h>		/* LIBUC */
#include	<strdcpy.h>		/* LIBUC */
#include	<char.h>		/* LIBUC */
#include	<ischarx.h>		/* LIBUC */
#include	<localmisc.h>		/* LIBU */

#include	"conslog.h"

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |memclear(3u)| */

/* local defines */

#define	CONSLOG_LOGLEN	LOG_MAXPS
#define	CONSLOG_EXTRA	100
#define	CONSLOG_NMSGS	10

#ifndef	LOGDEV
#define	LOGDEV		"/dev/conslog"
#endif

#undef	OUTBUFLEN
#define	OUTBUFLEN	(CONSLOG_LINELEN +2)

#define	TO_OPEN		(60 * 60)
#define	TO_WRITE	30
#define	TO_LOCK		4

#ifndef	SL_CONSOLE
#define	SL_CONSOLE	0
#endif


/* imported namespaces */

using libuc::mem ;			/* variable */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */

struct colstate {
	int		ncols ;
	int		ncol ;
} ; /* end struct */


/* forward references */

template<typename ... Args>
local int conslog_ctor(conslog *op,Args ... args) noex {
    	CONSLOG		*hop = op ;
	int		rs = SR_FAULT ;
	if (op && (args && ...)) ylikely {
	    rs = memclear(hop) ;
	} /* end if (non-null) */
	return rs ;
} /* end subroutine (conslog_ctor) */

local int conslog_dtor(conslog *op) noex {
	int		rs = SR_FAULT ;
	if (op) ylikely {
	    rs = SR_OK ;
	} /* end if (non-null) */
	return rs ;
} /* end subroutine (conslog_dtor) */

template<typename ... Args>
local inline int conslog_magic(conslog *op,Args ... args) noex {
	int		rs = SR_FAULT ;
	if (op && (args && ...)) ylikely {
	    rs = (op->magval == CONSLOG_MAGIC) ? SR_OK : SR_NOTOPEN ;
	}
	return rs ;
} /* end subroutine (conslog_magic) */

local int	conslog_fileready(conslog *) noex ;
local int	conslog_fileopen(conslog *) noex ;
local int	conslog_fileclose(conslog *) noex ;
local int	conslog_logdevice(conslog *,int,cchar *,int) noex ;

local bool	isLogFac(int) noex ;


/* local variables */

constexpr int	logfacs[] = {
	LOG_KERN,
	LOG_USER,
	LOG_MAIL,
	LOG_DAEMON,
	LOG_AUTH,
	LOG_SYSLOG,
	LOG_LPR,
	LOG_NEWS,
	LOG_UUCP,
	LOG_CRON,
	LOG_LOCAL0,
	LOG_LOCAL1,
	LOG_LOCAL2,
	LOG_LOCAL3,
	LOG_LOCAL4,
	LOG_LOCAL5,
	LOG_LOCAL6,
	LOG_LOCAL7,
	-1
} ; /* end array (logfacs) */


/* exported variables */


/* exported subroutines */

int conslog_open(conslog *op,int logfac) noex {
	int		rs ;
	if ((rs = conslog_ctor(op)) >= 0) {
	    rs = SR_INVALID ;
	    memclear(op) ;
	    if (isLogFac(logfac)) {
	        op->lfd = -1 ;
	        op->magval = CONSLOG_MAGIC ;
	    } /* end if (valid) */
	    if (rs < 0) {
		conslog_dtor(op) ;
	    } /* end if (error) */
	} /* end if (conslog_ctor) */
	return rs ;
} /* end subroutine (conslog_open) */

int conslog_close(conslog *op) noex {
	int		rs ;
	int		rs1 ;
	if ((rs = conslog_magic(op)) >= 0) {
	    {
	        rs1 = conslog_fileclose(op) ;
	        if (rs >= 0) rs = rs1 ;
	    }
	    {
	        rs1 = conslog_dtor(op) ;
	        if (rs >= 0) rs = rs1 ;
	    }
	    op->magval = 0 ;
	} /* end if (magic) */
	return rs ;
} /* end subroutine (conslog_close) */

int conslog_printf(conslog *op,int logpri,cchar *fmt,...) noex {
	va_list		ap ;
	int		rs ;
	if ((rs = conslog_magic(op,fmt)) >= 0) {
	    va_begin(ap,fmt) ;
	    rs = conslog_vprintf(op,logpri,fmt,ap) ;
	    va_end(ap) ;
	} /* end if (magic) */
	return rs ;
} /* end subroutine (conslog_printf) */

int conslog_vprintf(conslog *op,int logpri,cchar *fmt,va_list ap) noex {
    	cnullptr	np{} ;
	int		rs ;
	int		rs1 ;
	int		len = 0 ; /* return-value */
	if ((rs = conslog_magic(op,fmt,ap)) >= 0) {
	    if (char *lbuf ; (rs = mem.ml(&lbuf)) >= 0) {
		cint	llen = rs ;
		if ((rs = snwvprintf(lbuf,llen,fmt,ap)) >= 0) {
		    int		sl = rs ;
		    cchar	*sp = lbuf ;
	            for (cchar *tp ; (tp = strnchr(sp,sl,'\n')) != np ; ) {
	                {
		            cint tl = intconv(tp - sp) ;
	                    rs = conslog_write(op,logpri,sp,tl) ;
	                    len += rs ;
	                }
	                sl -= intconv((tp + 1) - sp) ;
	                sp = (tp + 1) ;
	                if (rs < 0) break ;
		    } /* end while */
		    if ((rs >= 0) && (sl > 0)) {
	    	        rs = conslog_write(op,logpri,sp,sl) ;
	    	        len += rs ;
		    } /* end if */
		} /* end if (snwvprintf) */
		rs1 = mem.free(lbuf) ;
		if (rs >= 0) rs = rs1 ;
	    } /* end if (m-a-f) */
	} /* end if (magic) */
	return (rs >= 0) ? len : rs ;
} /* end subroutine (conslog_vprintf) */

int conslog_check(conslog *op,time_t dt) noex {
	int		rs ;
	if ((rs = conslog_magic(op)) >= 0) {
	    if (op->lfd >= 0) {
	        bool	f = false ;
	        f = f || ((dt - op->ti_write) >= TO_WRITE) ;
	        f = f || ((dt - op->ti_open) >= TO_OPEN) ;
	        if (f) {
	            rs = conslog_fileclose(op) ;
	        }
	    } /* end if (open) */
	} /* end if (magic) */
	return rs ;
} /* end subroutine (conslog_check) */

int conslog_write(conslog *op,int logpri,cchar *wbuf,int wlen) noex {
	int		rs ;
	int		len = 0 ; /* return-value */
	if ((rs = conslog_magic(op,wbuf)) >= 0) {
	    if (wlen < 0) wlen = lenstr(wbuf) ;
	    while (wlen && iseol(wbuf[wlen-1])) {
	        wlen -= 1 ;
	    } /* end while */
	    while (wlen && CHAR_ISWHITE(wbuf[wlen-1])) {
	        wlen -= 1 ;
	    } /* end while */
	    if (wlen > 0) {
		if ((rs = conslog_logdevice(op,logpri,wbuf,wlen)) >= 0) {
		    len = rs ;
		    op->c += 1 ;
		}
	    } /* end if (non-zero positive) */
	} /* end if (magic) */
	return (rs >= 0) ? len : rs ;
} /* end subroutine (conslog_write) */

int conslog_count(conslog *op) noex {
	int		rs ;
	if ((rs = conslog_magic(op)) >= 0) {
	    rs = op->c ;
	} /* end if (magic) */
	return rs ;
} /* end subroutine (conslog_count) */


/* private subroutines */

local int conslog_fileready(conslog *op) noex {
    	int		rs = SR_OK ;
	if (op->lfd < 0) {
	    rs = conslog_fileopen(op) ;
	}
	return rs ;
} /* end subroutine */

local int conslog_fileopen(conslog *op) noex {
	int		rs = SR_OK ;
	if (op->lfd < 0) {
	    cint	of = O_WRONLY ;
	    cmode	om = 0666 ;
	    cchar	*logdev = LOGDEV ;
	    if ((rs = u_open(logdev,of,om)) >= 0) {
	        op->lfd = rs ;
	        rs = u_closeonexec(op->lfd,true) ;
	        op->ti_open = time(nullptr) ;
	        if (rs < 0) {
	            u_close(op->lfd) ;
	            op->lfd = -1 ;
	        } /* end if (error) */
	    } /* end if (open) */
	} /* end if (need an open) */
	return rs ;
} /* end subroutine (conslog_fileopen) */

local int conslog_fileclose(conslog *op) noex {
	int		rs = SR_OK ;
	int		rs1 ;
	if (op->lfd >= 0) {
	    rs1 = u_close(op->lfd) ;
	    if (rs >= 0) rs = rs1 ;
	    op->lfd = -1 ;
	} /* end if (was open) */
	return rs ;
} /* end subroutine (conslog_fileclose) */

local int conslog_logdevice(conslog *op,int logpri,cchar *bp,int bl) noex {
	log_ctl		lc{} ;
	STRBUF		cmsg ;
	STRBUF		dmsg ;
	int		rs ;
	if ((rs = conslog_fileready(op)) >= 0) {
	    logpri &= LOG_PRIMASK ;		/* truncate any garbage */
	    /* write it to the LOG device */
	    lc.flags = SL_CONSOLE ;
	    lc.level = 0 ;
	    lc.pri = (op->logfac | logpri) ;
	    /* set up the strbufs */
	    cmsg.maxlen = szof(log_ctl) ;
	    cmsg.len = szof(log_ctl) ;
	    cmsg.buf = (caddr_t) &lc ;
	    dmsg.maxlen = (bl+1) ;
	    dmsg.len = bl ;
	    dmsg.buf = (char *) bp ;
	    /* output the message to the local logger */
	    rs = u_putmsg(op->lfd,&cmsg,&dmsg,0) ;
	} /* end if (ok) */
	return rs ;
} /* end subroutine (conslog_logdevice) */

local bool isLogFac(int fac) noex {
	bool		f = false ;
	for (int i = 0 ; logfacs[i] >= 0 ; i += 1) {
	    f = (fac == logfacs[i]) ;
	    if (f) break ;
	} /* end if */
	return f ;
} /* end subroutine (isLogFac) */


