/* logsys SUPPORT */
/* lang=C++20 */

/* send log messages to the system logger device */
/* version %I% last-modified %G% */

#define	CF_LOGIDTAB	0		/* insert a log-id tab */

/* revision history:

	= 1998-02-01, David A­D­ Morano
	This object module was originally written to create a logging
	mechanism for PCS application programs.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	These are the subroutines in this module:

		logsys_open
		logsys_write
		logsys_printf
		logsys_vprintf
		logsys_setid
		logsys_check
		logsys_close

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/param.h>
#include	<sys/stat.h>
#include	<sys/log.h>		/* for LOG_MAXPS */
#include	<sys/strlog.h>		/* interface definitions */
#include	<sys/syslog.h>		/* for all other 'LOG_xxx' */
#include	<unistd.h>
#include	<fcntl.h>
#include	<csignal>
#include	<ctime>
#include	<cstdlib>
#include	<cstdarg>
#include	<cstring>
#include	<usystem.h>
#include	<mallocxx.h>
#include	<ascii.h>
#include	<getnodename.h>
#include	<strw.h>		/* |strwset(3uc)| */
#include	<strwcpy.h>
#include	<strdcpy.h>
#include	<strn.h>
#include	<snx.h>
#include	<mkx.h>			/* |mklogid(3uc)| */
#include	<ncol.h>		/* |charcols(3uc)| */
#include	<ctdec.h>
#include	<mkchar.h>		/* |mkchar(3uc)| */
#include	<ischarx.h>
#include	<localmisc.h>		/* |TIMEBUFLEN| + |NTABCOLS| */

#include	"logsys.h"


/* local defines */

#define	LOGSYS_LOGLEN	LOG_MAXPS
#define	LOGSYS_EXTRA	100
#define	LOGSYS_NMSGS	10

#define	COLSTATE	struct colstate

#ifndef	LOGDEV
#define	LOGDEV		"/dev/conslog"
#endif

#undef	BUFLEN
#define	BUFLEN		100

#undef	OUTBUFLEN
#define	OUTBUFLEN	(LOGSYS_LINELEN + 2 + LOGSYS_EXTRA)

#undef	LOGBUFLEN
#define	LOGBUFLEN	LOGSYS_LOGLEN

#define	TO_OPEN		(60 * 60)
#define	TO_WRITE	30
#define	TO_FLUSH	5
#define	TO_LOCK		4

#ifndef	F_LOCK
#define	F_ULOCK		0
#define	F_LOCK		1
#define	F_TLOCK		2
#define	F_TEST		3
#endif

#ifndef	CF_LOGIDTAB
#define	CF_LOGIDTAB	0
#endif


/* imported namespaces */


/* local typedefs */


/* external subroutines */

extern "C" {
    int		logsys_write(logsys *,int,cchar *,int) noex ;
    int		logsys_vprintf(logsys *,int,cchar *,va_list) noex ;
}

extern "C" {
    extern int	bufvprintf(char *,int,cchar *,va_list) noex ;
}


/* external variables */


/* local structures */

struct colstate {
	int		ncols ;
	int		ncol ;
} ;


/* forward references */

template<typename ... Args>
static int logsys_ctor(logsys *op,Args ... args) noex {
	int		rs = SR_FAULT ;
	if (op && (args && ...)) {
	    rs = SR_OK ;
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (logsys_ctor) */

static int logsys_dtor(logsys *op) noex {
	int		rs = SR_FAULT ;
	if (op) {
	    rs = SR_OK ;
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (logsys_dtor) */

template<typename ... Args>
static inline int logsys_magic(logsys *op,Args ... args) noex {
	int		rs = SR_FAULT ;
	if (op && (args && ...)) {
	    rs = (op->magic == LOGSYS_MAGIC) ? SR_OK : SR_NOTOPEN ;
	}
	return rs ;
}
/* end subroutine (logsys_magic) */

static int	logsys_mklogid(logsys *) noex ;
static int	logsys_fixlogid(logsys *,int) noex ;
static int	logsys_fileopen(logsys *) noex ;
static int	logsys_fileclose(logsys *) noex ;
static int	logsys_iflush(logsys *) noex ;
static int	logsys_logdevice(logsys *,int,cchar *,int) noex ;

static int	colstate_load(colstate *,int,int) noex ;
static int	colstate_linecols(colstate *,cchar *,int) noex ;

static int	loadlogid(char *,int,cchar *) noex ;
static int	mkclean(char *,int,cchar *,int) noex ;

static bool	hasourbad(cchar *,int) noex ;
static bool	isourbad(int) noex ;
static bool	isLogFac(int) noex ;


/* local variables */

static constexpr int	logfacs[] = {
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
} ;

constexpr int		logidlen = LOGSYS_LOGIDLEN ;

constexpr bool		f_logidtab = CF_LOGIDTAB ;


/* exported variables */


/* exported subroutines */

int logsys_open(logsys *op,int logfac,cc *logtag,cc *logid,int opts) noex {
	int		rs ;
	if ((rs = logsys_ctor(op,logtag)) >= 0) {
	    rs = SR_INVALID ;
	    if (logtag[0] && isLogFac(logfac)) {
	        int		cl ;
	        cchar		*cp ;
	        rs = memclear(op) ; /* dangerous */
	        op->n = LOGSYS_NMSGS ;
	        op->logfac = logfac ;
	        op->opts = opts ;
	        op->lfd = -1 ;
	        if ((rs = uc_mallocstrw(logtag,-1,&cp)) >= 0) {
	            op->logtag = cp ;
	            if ((logid == nullptr) || (logid[0] == '\0')) {
	                cl = logsys_mklogid(op) ;
	            } else {
	                cl = loadlogid(op->logid,logidlen,logid) ;
	            }
	            logsys_fixlogid(op,cl) ;
	            op->magic = LOGSYS_MAGIC ;
	        } else {
	            op->lfd = rs ; /* error */
	        } /* end if (m-a) */
	    } /* end if (valid) */
	    if (rs < 0) {
		logsys_dtor(op) ;
	    }
	} /* end if (logsys_ctor) */
	return rs ;
}
/* end subroutine (logsys_open) */

int logsys_close(logsys *op) noex {
	int		rs ;
	int		rs1 ;
	if ((rs = logsys_magic(op)) >= 0) {
	    {
	        rs1 = logsys_fileclose(op) ;
	        if (rs >= 0) rs = rs1 ;
	    }
	    if (op->logtag) {
	        rs1 = uc_free(op->logtag) ;
	        if (rs >= 0) rs = rs1 ;
	        op->logtag = nullptr ;
	    }
	    {
	        rs1 = logsys_dtor(op) ;
	        if (rs >= 0) rs = rs1 ;
	    }
	    op->magic = 0 ;
	} /* end if (magic) */
	return rs ;
}
/* end subroutine (logsys_close) */

int logsys_printf(logsys *op,int logpri,cchar *fmt,...) noex {
	int		rs ;
	{
	    va_list	ap ;
	    va_begin(ap,fmt) ;
	    rs = logsys_vprintf(op,logpri,fmt,ap) ;
	    va_end(ap) ;
	} /* end block */
	return rs ;
}
/* end subroutine (logsys_printf) */

int logsys_vprintf(logsys *op,int logpri,cchar *fmt,va_list ap) noex {
	int		rs ;
	int		len = 0 ;
	if ((rs = logsys_magic(op,fmt,ap)) >= 0) {
	    cint	olen = OUTBUFLEN ;
	    char	obuf[OUTBUFLEN + 1] ;
	    if ((rs = bufvprintf(obuf,olen,fmt,ap)) >= 0) {
	        cchar	*sp = obuf ;
	        cchar	*tp ;
	        int	sl = rs ;
	        while ((tp = strnchr(sp,sl,'\n')) != nullptr) {
	            rs = logsys_write(op,logpri,sp,(tp - sp)) ;
	            len += rs ;
	            if (rs < 0) break ;
	            sl -= ((tp + 1) - sp) ;
	            sp = (tp + 1) ;
	        } /* end while */
	        if ((rs >= 0) && (sl > 0)) {
	            rs = logsys_write(op,logpri,sp,sl) ;
	            len += rs ;
	        }
	    } /* end if (bufvprintf) */
	} /* end if (magic) */
	return (rs >= 0) ? len : rs ;
}
/* end subroutine (logsys_vprintf) */

/* set (or reset) the log ID */
int logsys_setid(logsys *op,cchar *logid) noex {
	int		rs ;
	if ((rs = logsys_magic(op)) >= 0) {
	    if (logid == nullptr) logid = "*null*" ;
	    if ((rs = loadlogid(op->logid,logidlen,logid)) >= 0) {
	        rs = logsys_fixlogid(op,rs) ;
    	    }
	} /* end if (magic) */
	return rs ;
}
/* end subroutine (logsys_setid) */

int logsys_check(logsys *op,time_t dt) noex {
	int		rs ;
	int		f = false ;
	if ((rs = logsys_magic(op)) >= 0) {
	    if (op->lfd >= 0) {
	        f = f || ((dt - op->ti_write) >= TO_WRITE) ;
	        f = f || ((dt - op->ti_open) >= TO_OPEN) ;
	        if (f) {
	            rs = logsys_fileclose(op) ;
	        } else {
	            if ((dt - op->ti_write) >= TO_FLUSH) {
	                if (op->c > 0) {
		            rs = logsys_iflush(op) ;
		        }
	            }
	        }
	    } /* end if (valid) */
	} /* end if (magic) */
	return (rs >= 0) ? f : rs ;
}
/* end subroutine (logsys_check) */

int logsys_flush(logsys *op) noex {
	int		rs ;
	if ((rs = logsys_magic(op)) >= 0) {
	    if (op->c > 0) rs = logsys_iflush(op) ;
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (logsys_flush) */

int logsys_write(logsys *op,int logpri,cchar *wbuf,int wlen) noex {
	int		rs ;
	int		outlen = 0 ;
	if ((rs = logsys_magic(op,vbuf)) >= 0) {
	    colstate	cs ;
	    int		blen ;
	    if (wlen < 0) wlen = strlen(wbuf) ;
	    if (wbuf[wlen-1] == '\n') {
	        wlen -= 1 ;
	    }
	    colstate_load(&cs,LOGSYS_LINELEN,(logidlen + 1)) ;
	    blen = colstate_linecols(&cs,wbuf,wlen) ;
	    outlen = (op->logidlen + blen + 1) ;
    /* do we need a flush? */
	    if (op->c > 0) {
	        rs = logsys_iflush(op) ;
	    }
	    if (rs >= 0) {
	        int	bl = wlen ;
	        cchar	*bp = wbuf ;
	        char	tmpbuf[LOGSYS_USERLEN + 1] ;
	        if (hasourbad(wbuf,blen)) {
	            bp = tmpbuf ;
	            bl = mkclean(tmpbuf,LOGSYS_USERLEN,wbuf,wlen) ;
	        }
	        if ((rs = logsys_logdevice(op,logpri,bp,bl)) >= 0) {
	            op->c += 1 ;
	        }
	    } /* end if (ok) */
	} /* end if (magic) */
	return (rs >= 0) ? outlen : rs ;
}
/* end subroutine (logsys_write) */


/* private subroutines */

static int logsys_mklogid(logsys *op) noex {
	int		rs ;
	int		rs1 ;
	int		ll = 0 ;
	char		*nbuf{} ;
	if ((rs = malloc_nn(&nbuf)) >= 0) {
	    cint	nlen = rs ;
	    if ((rs = getnodename(nbuf,nlen)) >= 0) {
	        cint	pid = getpid() ;
		if ((rs = mklogid(op->logid,logidlen,nbuf,rs,pid)) >= 0) {
		    ll = rs ;
		} /* end if (mklogid) */
	    } /* end if (getnodename) */
	    rs1 = uc_free(nbuf) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (m-a-f) */
	return (rs >= 0) ? cl : rs ;
}
/* end subroutine (logsys_mklogid) */

static int logsys_fixlogid(logsys *op,int cl) noex {
	if_constexpr (f_logidtab) {
	    if (cl < NTABCOLS) {
	        strwset((op->logid + cl),' ',(NTABCOLS - cl)) ;
	        cl = NTABCOLS ;
	    }
	    op->logid[cl++] = '\t' ;
	} /* end if_constexpr (f_logidtab) */
	op->logid[cl] = '\0' ;
	op->logidlen = cl ;
	return cl ;
}
/* end subroutine (logsys_fixlogid) */

static int logsys_fileopen(logsys *op) noex {
	int		rs = SR_OK ;
	if (op->lfd < 0) {
	    cint	of = O_WRONLY ;
	    cmode	om = 0666 ;
	    cchar	*logdev = LOGDEV ;
	    if ((rs = u_open(logdev,of,om)) >= 0) {
		op->lfd = rs ;
		rs = uc_closeonexec(op->lfd,true) ;
		op->ti_open = time(nullptr) ;
		if (rs < 0) {
		    u_close(op->lfd) ;
		    op->lfd = -1 ;
		}
	    } /* end if (open) */
	} /* end if (need an open) */
	return rs ;
}
/* end subroutine (logsys_fileopen) */

static int logsys_fileclose(logsys *op) noex {
	int		rs = SR_OK ;
	int		rs1 ;
	int		len = 0 ;
	if (op->c > 0) {
	    len = logsys_iflush(op) ;
	    if (rs >= 0) rs = len ;
	}
	if (op->lfd >= 0) {
	    rs1 = uc_close(op->lfd) ;
	    if (rs >= 0) rs = rs1 ;
	    op->lfd = -1 ;
	}
	return (rs >= 0) ? len : rs ;
}
/* end subroutine (logsys_fileclose) */

/* this is a nuller now w/ the system log device */
static int logsys_iflush(logsys *op) noex {
	if (op->c >= op->n) op->c = 0 ;
	return SR_OK ;
}
/* end subroutine (logsys_iflush) */

static int logsys_logdevice(logsys *op,int logpri,cchar *wp,int wl) noex {
	STRBUF		cmsg{} ;
	STRBUF		dmsg{} ;
	struct log_ctl	lc{} ;
	cint		llen = LOGBUFLEN ;
	int		rs = SR_OK ;
	int		ll ;
	char		logbuf[LOGBUFLEN+1], *lp = logbuf ;
	if (op->lfd < 0) {
	    rs = logsys_fileopen(op) ;
	}
	if (rs >= 0) {
	    logpri &= LOG_PRIMASK ;		/* truncate any garbage */
/* formulate the string to write */
	    {
	        cchar	*lt = op->logtag ;
	        cchar	*li = op->logid ;
	        ll = strdcpy5w(lp,llen,lt,"-",li,": ",wp,wl) - lp ;
	    }
/* write it to the LOG device */
	    lc.flags = SL_CONSOLE ;
	    lc.level = 0 ;
	    lc.pri = (op->logfac | logpri) ;
	    /* set up the strbufs */
	    cmsg.maxlen = sizeof(struct log_ctl) ;
	    cmsg.len = sizeof(struct log_ctl) ;
	    cmsg.buf = (caddr_t) &lc ;
	    dmsg.maxlen = (ll+1) ;
	    dmsg.len = ll ;
	    dmsg.buf = logbuf ;
	    /* output the message to the local logger */
	    rs = u_putmsg(op->lfd,&cmsg,&dmsg,0) ;
	} /* end if (ok) */
	return rs ;
}
/* end subroutine (logsys_logdevice) */

static int colstate_load(colstate *csp,int ncols,int ncol) noex {
	csp->ncols = ncols ;
	csp->ncol = ncol ;
	return SR_OK ;
}
/* end subroutine (colstate_load) */

/* return the number of characters that will fill the current column limit */
static int colstate_linecols(colstate *csp,cchar *lbuf,int llen) noex {
	int		i ; /* used afterwards */
	int		rcols = (csp->ncols - csp->ncol) ;
	int		cols ;
	for (i = 0 ; (rcols > 0) && (i < llen) ; i += 1) {
	    cols = charcols(NTABCOLS,csp->ncol,lbuf[i]) ;
	    if (cols > rcols) break ;
	    csp->ncol += cols ;
	    rcols -= cols ;
	} /* end for */
	return i ;
}
/* end subroutine (colstate_linecols) */

static int loadlogid(char *outbuf,int outlen,cchar *logstr) noex {
	int		len = 0 ;
	for (int i = 0 ; (i < outlen) && logstr[i] ; i += 1) {
	    cint	ch = mkchar(logstr[i]) ;
	    if (isprintlatin(ch)) {
		outbuf[len++] = ch ;
	    }
	} /* end for */
	return len ;
}
/* end subroutine (loadlogid) */

static int mkclean(char *outbuf,int outlen,cchar *sbuf,int slen) noex {
	int		i ; /* used afterwards */
	for (i = 0 ; (i < outlen) && (i < slen) ; i += 1) {
	    outbuf[i] = sbuf[i] ;
	    if (isourbad(sbuf[i] & 0xff)) outbuf[i] = '­' ;
	} /* end for */
	return i ;
}
/* end subroutine (mkclean) */

static int hasourbad(cchar *sp,int sl) noex {
	int		f = false ;
	while (sl && (sp[0] != '\0')) {
	    cint	ch = (sp[0] & 0xff) ;
	    f = isourbad(ch) ;
	    if (f) break ;
	    sp += 1 ;
	    sl -= 1 ;
	} /* end if */
	return f ;
}
/* end subroutine (hasourbad) */

static bool isourbad(int ch) noex {
	bool		f = true ;
	switch (ch) {
	case CH_SO:
	case CH_SI:
	case CH_SS2:
	case CH_SS3:
	case '\t':
	    f = false ;
	    break ;
	default:
	    f = (! isprintlatin(ch)) ;
	    break ;
	} /* end switch */
	return f ;
}
/* end subroutine (isourbad) */

static int isLogFac(int fac) noex {
	bool		f = false ;
	for (int i = 0 ; logfacs[i] >= 0 ; i += 1) {
	    f = (fac == logfacs[i]) ;
	    if (f) break ;
	} /* end if */
	return f ;
}
/* end subroutine (isLogFac) */


