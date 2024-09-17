/* uterm SUPPORT */
/* lang=C++20 */

/* "UNIX Terminal" helper routines */
/* version %I% last-modified %G% */

#define	CF_FIRSTREAD	0	/* perform an initial |read()|? */
#define	CF_SUBUNIX	1	/* allow UNIX® to handle Control-Z */

/* revision history:

	= 1998-02-01, David A­D­ Morano
	This module was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	uterm

	Description:
	These routines provide a stand-alone terminal environment.

	History:
	This code is very old.  Although the code below is "officially"
	dated from 1998, in reality the code dates from 1984.  This
	code was taken from the driver code for the
	Multi-Function-Peripherial (MFP) used in the various computers
	architected and designed dating from 1984.  This code is
	essentially a UNIX® adapted version of the C-language version
	of MFP driver code written for the eXecutive-Debugging-Tool
	(XDT) ROM Debug-Monitor.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<termios.h>
#include	<unistd.h>
#include	<poll.h>
#include	<ctime>
#include	<climits>		/* |CHAR_UMAX| + |CHAR_BIT| */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstdarg>
#include	<cstring>
#include	<usystem.h>
#include	<ascii.h>
#include	<baops.h>
#include	<charq.h>
#include	<vecobj.h>
#include	<buffer.h>
#include	<sbuf.h>
#include	<sigign.h>
#include	<strn.h>
#include	<mkchar.h>
#include	<ischarx.h>
#include	<localmisc.h>

#include	"uterm.h"


/* local defines */

#define	UTERM_MAGIC	0x33442281

#define	TTY_MINCHARS	0	/* minimum characters to get */
#define	TTY_MINTIME	5	/* minimum time (x100 milliseconds) */

#define	TTY_READCHARS	20

#define	WBUFLEN		40	/* maximum output write buffer */

#define	TO_HANGUP	3	/* the error monitoring interval */
#define	MAXLOOPS	300	/* maximum loops in monitor interval */

#define	TA_SIZE		256
#define	EC_SIZE		256

/* output priorities */

#define	OPM_WRITE	0x01
#define	OPM_READ	0x02
#define	OPM_ECHO	0x04
#define	OPM_ANY		0x07

#define	OPV_WRITE	0
#define	OPV_READ	1
#define	OPV_ECHO	2

#undef	CH_FILTER
#define	CH_FILTER	0x100

#define	FILTER(c)	((c) | CH_FILTER)

#ifndef	HEXBUFLEN
#define	HEXBUFLEN	100
#endif

#ifndef	CF_SUBUNIX
#define	CF_SUBUNIX	1	/* allow UNIX® to handle Control-Z */
#endif


/* externals subroutines */

extern "C" {
    extern int	tcsetmesg(int,int) noex ;
    extern int	tcsetbiff(int,int) noex ;
    extern int	tcgetlines(int) noex ;
    extern int	tcsetlines(int,int) noex ;
}


/* external variables */


/* local structures */


/* forward references */

template<typename ... Args>
static inline int uterm_magic(uterm *op,Args ... args) noex {
	int		rs = SR_FAULT ;
	if (op && (args && ...)) {
	    rs = (op->magic == UTERM_MAGIC) ? SR_OK : SR_NOTOPEN ;
	}
	return rs ;
}
/* end subroutine (uterm_magic) */

static int	uterm_loadterms(uterm *,cchar *) noex ;
static int	uterm_attrbegin(uterm *) noex ;
static int	uterm_attrend(uterm *) noex ;
static int	uterm_qbegin(uterm *) noex ;
static int	uterm_qend(uterm *) noex ;
static int	uterm_controlmode(uterm *) noex ;
static int	uterm_writeproc(uterm *,cchar *,int) noex ;

static int	tty_wait(uterm *,int) noex ;
static int	tty_echo(uterm *,cchar *,int) noex ;
static int	tty_risr(uterm *,cchar *,int) noex ;
static int	tty_wps(uterm *,cchar *,int) noex ;
static int	tty_loadchar(uterm *,cchar *,int) noex ;

static int	sinotprint(cchar *,int) noex ;


/* local variables */

constexpr int		fieldterm_tabsize = ((UCHAR_MAX + 1) / CHAR_BIT) ;

constexpr uid_t		uidend(-1) ;

constexpr char	uterms[] = {
	0xEF, 0xFC, 0xC0, 0xFE,
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
} ;

static constexpr int	sigouts[] = {
	SIGTTOU,
	0
} ;

constexpr bool		f_subunix = CF_SUBUNIX ;


/* exported variables */


/* exported subroutines */

int uterm_start(uterm *op,int fd) noex {
	int		rs = SR_FAULT ;
	if (op) {
	    rs = SR_INVALID ;
	    if (fd >= 0) {
	        op->ti_start = getustime ;
	        op->fd = fd ;
	        op->uid = -1 ;
	        if ((rs = uc_tcgetpgrp(fd)) == SR_NOTTY) {
	            op->f.noctty = true ;
	            rs = SR_OK ;
	        }
	        if (rs >= 0) {
		    if ((rs = uterm_loadterms(op,uterms)) >= 0) {
	                if ((rs = uterm_attrbegin(op)) >= 0) {
		            if ((rs = uterm_qbegin(op)) >= 0) {
		                op->magic = UTERM_MAGIC ;
		            }
	 	            if (rs < 0) {
		                uterm_attrend(op) ;
		            }
	                }
		    } /* end if (uterm_loadterms) */
	        } /* end if (ok) */
	    } /* end if (valid) */
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (uterm_start) */

int uterm_finish(uterm *op) noex {
	int		rs ;
	int		rs1 ;
	if ((rs = uterm_magic(op)) >= 0) {
	    {
		rs1 = uterm_qend(op) ;
		if (rs >= 0) rs = rs1 ;
	    }
	    {
		rs1 = uterm_attrend(op) ;
		if (rs >= 0) rs = rs1 ;
	    }
	    op->magic = 0 ;
	} /* end if (magic) */
	return rs ;
}
/* end subroutine (uterm_finish) */

int uterm_suspend(uterm *op) noex {
	return uterm_restore(op) ;
}
/* end subroutine (uterm_suspend) */

int uterm_resume(uterm *op) noex {
	return uterm_ensure(op) ;
}
/* end subroutine (uterm_resume) */

int uterm_restore(uterm *op) noex {
	int		rs ;
	if ((rs = uterm_magic(op)) >= 0) {
	    TERMIOS	*attrp = &op->ts_old ;
	    if ((rs = uc_tcattrset(op->fd,TCSADRAIN,attrp)) >= 0) {
	        rs = op->fd ;
	    }
	} /* end if (magic) */
	return rs ;
}
/* end subroutine (uterm_restore) */

int uterm_ensure(uterm *op) noex {
	int		rs ;
	if ((rs = uterm_magic(op)) >= 0) {
	    TERMIOS	*attrp = &op->ts_new ;
	    cint	cmd = TCSADRAIN ;
	    rs = uc_tcattrset(op->fd,cmd,attrp) ;
	} /* end if (magic) */
	return rs ;
}
/* end subroutine (uterm_ensure) */

int uterm_control(uterm *op,int cmd,...) noex {
	va_list		ap ;
	int		rs ;
	if ((rs = uterm_magic(op)) >= 0) {
	    cint	fc = (cmd & FM_CMDMASK) ;
	    int		iw, *iwp ;
	    va_begin(ap,cmd) ;
	    switch (fc) {
	    case utermcmd_noop:
		break ;
	    case utermcmd_getuid:
		if (op->uid == uidend) {
	            if ((rs = uc_fuid(op->fd)) >= 0) {
			op->uid = rs ;
		    }
		} else {
		    rs = op->uid ;
		}
	        break ;
	    case utermcmd_getsid:
	        rs = uc_tcgetsid(op->fd) ;
	        break ;
	    case utermcmd_getmode:
	        iwp = (int *) va_arg(ap,int *) ;
	        if (iwp != nullptr) *iwp = op->mode ;
	        break ;
	    case utermcmd_setmode:
	        iw = (int) va_arg(ap,int) ;
	        op->mode = iw ;
		rs = uterm_controlmode(op) ;
	        break ;
	    case utermcmd_setrterms:
		{
	            const uchar	*rp = (uchar *) va_arg(ap,uchar *) ;
		    memcpy(op->rterms,rp,32) ;
		}
		break ;
	    case utermcmd_reestablish:
		{
		    TERMIOS	*attrp = &op->ts_new ;
	            cint	cmd = TCSADRAIN ;
	            rs = uc_tcattrset(op->fd,cmd,attrp) ;
		}
	        break ;
	    case utermcmd_getmesg:
		rs = uterm_getmesg(op) ;
		break ;
	    case utermcmd_setmesg:
		{
		    cint	f = (int) va_arg(ap,int) ;
	            rs = tcsetmesg(op->fd,f) ;
		}
		break ;
	    case utermcmd_getbiff:
		rs = uterm_getbiff(op) ;
		break ;
	    case utermcmd_setbiff:
		{
		    cint	f = (int) va_arg(ap,int) ;
	            rs = tcsetbiff(op->fd,f) ;
		}
		break ;
	    case utermcmd_getpgrp:
	        rs = uc_tcgetpgrp(op->fd) ;
	        break ;
	    case utermcmd_setpgrp:
		{
		    SIGIGN	si ;
		    if ((rs = sigign_start(&si,sigouts)) >= 0) {
		        const pid_t	pgrp = (pid_t) va_arg(ap,pid_t) ;
	                rs = uc_tcsetpgrp(op->fd,pgrp) ;
		        sigign_finish(&si) ;
		    } /* end if (sigign) */
		}
	        break ;
	    case utermcmd_getpop:
		rs = uterm_getpop(op) ;
		break ;
	    case utermcmd_setpop:
		{
		    cint	v = (int) va_arg(ap,int) ;
	            rs = uterm_setpop(op,v) ;
		}
		break ;
	    default:
	        rs = SR_INVALID ;
	        break ;
	    } /* end switch */
	    va_end(ap) ;
	} /* end if (magic) */
	return rs ;
}
/* end subroutine (uterm_control) */

int uterm_status(uterm *op,int cmd,...) noex {
	int		rs ;
	if ((rs = uterm_magic(op)) >= 0) {
	    va_list	ap ;
	    va_begin(ap,cmd) ;
	    switch (cmd) {
	    case utermcmd_noop:
	        break ;
	    case utermcmd_setmesg:
	        {
	            cint	v = (int) va_arg(ap,int) ;
	            rs = tcsetmesg(op->fd,v) ;
	        }
	        break ;
	    case utermcmd_getlines:
	        rs = tcgetlines(op->fd) ;
	        break ;
	    case utermcmd_setlines:
	        {
	            cint	v = (int) va_arg(ap,int) ;
	            rs = tcsetlines(op->fd,v) ;
	        }
	        break ;
	    case utermcmd_getsid:
	        rs = uc_tcgetsid(op->fd) ;
	        break ;
	    case utermcmd_getpgrp:
	        rs = uc_tcgetpgrp(op->fd) ;
	        break ;
	    case utermcmd_setpgrp:
	        {
	            const pid_t	pgrp = (pid_t) va_arg(ap,pid_t) ;
	            rs = uc_tcsetpgrp(op->fd,pgrp) ;
	        }
	        break ;
	    default:
	        rs = SR_INVALID ;
	        break ;
	    } /* end switch */
	    va_end(ap) ;
	} /* end if (magic) */
	return rs ;
}
/* end subroutine (uterm_status) */

int uterm_reade(uterm *op,char *rbuf,int rlen,int timeout,int fc,
		uterm_pr *lpp,uterm_ld *llp) noex {
	int		rs ;
	int		count = 0 ;
	if ((rs = uterm_magic(op,rbuf)) >= 0) {
	int		ch = -1 ;
	cchar		*terms = op->rterms ;
	char		qbuf[2] ;
	fc |= op->mode ;
	if (fc & fm_rawin) fc |= fm_nofilter ;
	if (fc & fm_noecho) fc |= fm_notecho ;

	op->f.cntl_c = false ;
	op->f.cntl_o = false ;		/* cancel ^O effect */
	op->f.read = true ;		/* read is in progress */

/* top of further access */
/* top */
	if ((rs >= 0) && (lpp != nullptr) && (lpp->plen > 0)) {
	    rs = tty_wps(op,lpp->pbuf,lpp->plen) ;
	}

	if ((rs >= 0) && (llp != nullptr) && (llp->llen > 0)) {
	    rs = tty_loadchar(op,llp->lbuf,llp->llen) ;
	}

	count = 0 ;

/* check TA buffer first */
/* next */
	while ((rs >= 0) && (count < rlen)) {
	    bool	f_eot = false ;

	    while ((rs = charq_rem(&op->taq,qbuf)) == SR_EMPTY) {
	 	{
	            rs = tty_wait(op,timeout) ;
		}
	        if ((timeout >= 0) && (op->timeout <= 0)) break ;
	        if (rs < 0) break ;
	    } /* end while */

	    if (rs < 0) break ;

	    if ((timeout >= 0) && (op->timeout <= 0)) break ;

	    if (op->f.cntl_c) break ;

	    ch = mkchar(qbuf[0]) ;
	    rbuf[count] = ch ;

/* check for terminator */

	    if (BATST(terms,ch))
	        break ;

/* check for a filter character */

	    if (! (fc & fm_nofilter)) {
	        switch (ch) {
	        case CH_EOT:
	            if (count == 0)
	                f_eot = true ;
	            ch = -1 ;
	            break ;
	        case CH_NAK:
	            if (! (fc & fm_noecho)) {
	                rs = tty_echo(op," ^U\r\n",5) ;
		    }
	            ch = -1 ;
	            break ;
	        case CH_DEL:
	        case CH_BS:
	            if (count > 0) {
	                count -= 1 ;
	                if (! (fc & fm_noecho)) {
	                    rs = tty_echo(op,"\b \b",3) ;
			}
	            }
	            ch = -1 ;
	            break ;
	        case CH_DC2:
	            if (! (fc & fm_noecho)) {
	                rs = tty_echo(op," ^R\r\n",5) ;
	                if ((rs >= 0) && (lpp != nullptr) && 
	                    (lpp->pbuf != nullptr) && (lpp->plen > 0)) {
	                    rs = tty_wps(op,lpp->pbuf,lpp->plen) ;
			}
	                if ((rs >= 0) && (count > 0)) {
	                    rs = tty_echo(op,rbuf,count) ;
			}
	            }
	            ch = -1 ;
	            break ;
	        case CH_CAN:
	            if (! (fc & fm_noecho)) {
	                rs = tty_echo(op," ^X\r\n",5) ;
		    }
	            ch = -1 ;
	            break ;
	        } /* end switch */
	    } /* end if (filtering) */

	    if ((rs >= 0) && (ch >= 0)) {
	        if ((! (fc & fm_noecho)) && isprintlatin(ch)) {
		    char	ebuf[2] ;
		    ebuf[0] = ch ;
	            rs = tty_echo(op,ebuf,1) ;
	        }
	        count += 1 ;
	    } /* end if (normal character) */

	    if (f_eot) break ;
	} /* end while */

/* exit processing */

	if ((rs >= 0) && (ch >= 0) && BATST(terms,ch)) {
	    switch (ch) {
	    case CH_CR:
	    case CH_LF:
	        if (! ((fc & fm_notecho) || (fc & fm_noecho))) {
	            rs = tty_echo(op,"\r\n",2) ;
		}
	        if (! (fc & fm_nofilter)) {
	            rbuf[count] = CH_LF ;
		}
	        break ;
	    case CH_ESC:
	    case CH_CSI:
	        if (! ((fc & fm_notecho) || (fc & fm_noecho))) {
	            rs = tty_echo(op,"$",1) ;
		}
	        break ;
	    } /* end switch */
	    count += 1 ;
	} /* end if (terminator processing) */

	op->f.read = false ;
	} /* end if (magic) */
	return (rs >= 0) ? count : rs ;
}
/* end subroutine (uterm_reade) */

int uterm_read(uterm *op,char *rbuf,int rlen) noex {
	return uterm_reade(op,rbuf,rlen,-1,0,nullptr,nullptr) ;
}
/* end subroutine (uterm_read) */

int uterm_write(uterm *op,cchar *wbuf,int wlen) noex {
	int		rs ;
	int		tlen = 0 ;
	if ((rs = uterm_magic(op)) >= 0) {
	    if (! op->f.cntl_o) {
	        if (wlen < 0) wlen = strlen(wbuf) ;
	        if (op->mode & fm_rawout) {
	            rs = u_write(op->fd,wbuf,wlen) ;
		    tlen = rs ;
	        } else {
	            rs = uterm_writeproc(op,wbuf,wlen) ;
	            tlen = rs ;
	        }
	    } /* end if (not-in-cancel) */
	} /* end if (magic) */
	return (rs >= 0) ? tlen : rs ;
}
/* end subroutine (uterm_write) */

int uterm_cancel(uterm *op,int fc,int cparam) noex {
	int		rs ;
	(void) fc ;
	if ((rs = uterm_magic(op)) >= 0) {
	    rs = cparam ;
	} /* end if (magic) */
	return rs ;
}
/* end subroutine (uterm_cancel) */

int uterm_poll(uterm *op) noex {
	int		rs ;
	if ((rs = uterm_magic(op)) >= 0) {
	    if ((rs = tty_wait(op,0)) >= 0) {
	        if (op->f.cntl_c) rs = SR_CANCELED ;
	    }
	} /* end if (magic) */
	return rs ;
}
/* end subroutine (uterm_poll) */

int uterm_getmesg(uterm *op) noex {
	int		rs ;
	if ((rs = uterm_magic(op)) >= 0) {
	    USTAT	sb ;
	    if ((rs = u_fstat(op->fd,&sb)) >= 0) {
	        rs = bool(sb.st_mode & S_IWGRP) ;
	    }
	} /* end if (magic) */
	return rs ;
}
/* end subroutine (uterm_getmesg) */

int uterm_getbiff(uterm *op) noex {
	int		rs ;
	if ((rs = uterm_magic(op)) >= 0) {
	    USTAT	sb ;
	    if ((rs = u_fstat(op->fd,&sb)) >= 0) {
	        rs = bool(sb.st_mode & S_IXUSR) ;
	    }
	} /* end if (magic) */
	return rs ;
}
/* end subroutine (uterm_getbiff) */

int uterm_getpop(uterm *op) noex {
	int		rs ;
	if ((rs = uterm_magic(op)) >= 0) {
	    USTAT	sb ;
	    if ((rs = u_fstat(op->fd,&sb)) >= 0) {
	        int		v = 0 ;
	        if (sb.st_mode & S_IXUSR) v |= 0x01 ;
	        if (sb.st_mode & S_IWGRP) v |= 0x02 ;
	        rs = v ;
	    }
	} /* end if (magic) */
	return rs ;
}
/* end subroutine (uterm_getpop) */

int uterm_setpop(uterm *op,int v) noex {
	int		rs ;
	int		rv = 0 ;
	if ((rs = uterm_magic(op)) >= 0) {
	    USTAT	sb ;
	    if ((rs = u_fstat(op->fd,&sb)) >= 0) {
	        mode_t	fm = sb.st_mode ;
	        if (sb.st_mode & S_IXUSR) rv |= 0x01 ;
	        if (sb.st_mode & S_IWGRP) rv |= 0x02 ;
	        if (v != rv) {
		    fm &= S_IXUSR ;
		    if (v & 0x01) fm |= S_IXUSR ;
		    fm &= S_IWGRP ;
		    if (v & 0x02) fm |= S_IWGRP ;
		    rs = u_fchmod(op->fd,fm) ;
	        } /* end if (needed update) */
	    } /* end if (stat) */
	} /* end if (magic) */
	return (rs >= 0) ? rv : rs ;
}
/* end subroutine (uterm_setpop) */


/* private subroutines */

static int uterm_loadterms(uterm *op,cchar *ut) noex {
	int		rs = SR_FAULT ;
	if (ut) {
	    rs = SR_OK ;
	    memcpy(op->rterms,ut,fieldterm_tabsize) ;
	}
	return rs ;
}

static int uterm_attrbegin(uterm *op) noex {
	cint		fd = op->fd ;
	int		rs ;

	if ((rs = uc_tcattrget(fd,&op->ts_old)) >= 0) {
	    TERMIOS	*tp = &op->ts_new ;
	    op->ts_new = op->ts_old ;

	tp->c_iflag &= 
	    (~ (INLCR | ICRNL | IXANY | ISTRIP | INPCK | PARMRK)) ;
	tp->c_iflag |= IXON ;

	tp->c_cflag &= (~ (CSIZE)) ;
	tp->c_cflag |= CS8 ;

	tp->c_lflag &= (~ (ICANON | ECHO | ECHOE | ECHOK | ECHONL)) ;
#if	CF_SIGNAL
	tp->c_lflag &= (~ (ISIG)) ;
#endif

	tp->c_oflag &= (~ (OCRNL | ONOCR | ONLRET)) ;

	tp->c_cc[VMIN] = TTY_MINCHARS ;
	tp->c_cc[VTIME] = TTY_MINTIME ;

	tp->c_cc[VINTR] = CH_ETX ;	/* Control-C */
	tp->c_cc[VQUIT] = CH_EM ;	/* Control-Y */
	tp->c_cc[VERASE] = CH_DEL ;	/* Delete */
	tp->c_cc[VKILL] = CH_NAK ;	/* Control-U */
	tp->c_cc[VSTART] = CH_DC1 ;	/* Control-Q */
	tp->c_cc[VSTOP] = CH_DC3 ;	/* Control-S */
	tp->c_cc[VSUSP] = CH_SUB ;	/* Control-Z */
	tp->c_cc[VREPRINT] = CH_DC2 ;	/* Control-R */
	tp->c_cc[VDISCARD] = CH_SO ;	/* Control-O */

/* set the new attributes */

	    rs = uc_tcattrset(fd,TCSADRAIN,tp) ;
	    if (rs < 0) {
		uc_tcattrset(fd,TCSADRAIN,&op->ts_old) ;
	    }
	} /* end if */

	return rs ;
}
/* end subroutine (uterm_attrbegin) */

static int uterm_attrend(uterm *op) noex {
	cint		fd = op->fd ;
	int		rs = SR_OK ;
	int		rs1 ;
	{
	    rs1 = uc_tcattrset(fd,TCSADRAIN,&op->ts_old) ;
	    if (rs >= 0) rs = rs1 ;
	}
	return rs ;
}
/* end subroutine (uterm_attrend) */

static int uterm_qbegin(uterm *op) noex {
	int		rs ;
	if ((rs = charq_start(&op->taq,TA_SIZE)) >= 0) {
	    rs = charq_start(&op->ecq,EC_SIZE) ;
	    if (rs < 0)
		charq_finish(&op->taq) ;
	}
	return rs ;
}
/* end subroutine (uterm_qbegin) */

static int uterm_qend(uterm *op) noex {
	int		rs = SR_OK ;
	int		rs1 ;
	{
	    rs1 = charq_finish(&op->taq) ;
	    if (rs >= 0) rs = rs1 ;
	}
	{
	    rs1 = charq_finish(&op->ecq) ;
	    if (rs >= 0) rs = rs1 ;
	}
	return rs ;
}
/* end subroutine (uterm_qend) */

static int uterm_controlmode(uterm *op) noex {
	cint		m = op->mode ;
	int		rs = SR_OK ;
	op->f.nosig = ((m & fm_nosig) != 0) ;
	return rs ;
}
/* end subroutine (uterm_controlmode) */

static int uterm_writeproc(uterm *op,cchar *buf,int buflen) noex {
	int		rs = SR_OK ;
	int		rs1 ;
	int		tlen = 0 ;

	tlen = buflen ;
	if (cchar *tp ; (tp = strnchr(buf,buflen,'\n')) != nullptr) {
	    buffer	pb ;

	    if ((rs = buffer_start(&pb,(buflen + 10))) >= 0) {
	        int	bl = buflen ;
	        cchar	*bp = buf ;

	        buffer_buf(&pb,bp,(tp - bp)) ;
	        buffer_chr(&pb,'\r') ;
	        buffer_chr(&pb,'\n') ;

	        bl -= ((tp + 1) - bp) ;
	        bp = (tp + 1) ;

	        while ((tp = strnchr(bp,bl,'\n')) != nullptr) {
	            buffer_buf(&pb,bp,(tp - bp)) ;
	            buffer_chr(&pb,'\r') ;
	            buffer_chr(&pb,'\n') ;
	            bl -= ((tp + 1) - bp) ;
	            bp = (tp + 1) ;
	        } /* end while */

	        if (bl > 0) {
	            buffer_buf(&pb,bp,bl) ;
	        }

	        if (cchar *sp ; (rs = buffer_get(&pb,&sp)) > 0) {
	            rs = u_write(op->fd,sp,rs) ;
		}

	        rs1 = buffer_finish(&pb) ;
		if (rs >= 0) rs = rs1 ;
	    } /* end if (initialize buffer) */

	} else {
	    rs = u_write(op->fd,buf,buflen) ;
	}

	return (rs >= 0) ? tlen : rs ;
}
/* end subroutine (uterm_writeproc) */

static int tty_wps(uterm *op,cchar *ubuf,int ulen) noex {
	int		rs = SR_OK ;
	int		rs1 ;
	if (ulen < 0) ulen = strlen(ubuf) ;
	if (ulen > 0) {
	    if (int ci ; (ci = sinotprint(ubuf,ulen)) >= 0) {
	        if (buffer pb ; (rs = buffer_start(&pb,ulen)) >= 0) {
	            int		bl = ulen ;
	            cchar	*bp = ubuf ;
	            if (ci > 0) {
	                buffer_buf(&pb,bp,ci) ;
		    }
	            bp += (ci + 1) ;
	            bl -= (ci + 1) ;
	            while ((bl > 0) && ((ci = sinotprint(bp,bl)) >= 0)) {
	                if (ci > 0) buffer_buf(&pb,bp,ci) ;
	                bp += (ci + 1) ;
	                bl -= (ci + 1) ;
	            } /* end while */
	            if (bl > 0) {
	                buffer_buf(&pb,bp,bl) ;
		    }
	            if (cchar *sp ; (rs = buffer_get(&pb,&sp)) > 0) {
	                rs = u_write(op->fd,sp,rs) ;
		    }
	            rs1 = buffer_finish(&pb) ;
		    if (rs >= 0) rs = rs1 ;
	        } /* end if (initialize buffer) */
	    } else {
	        rs = u_write(op->fd,ubuf,ulen) ;
	    }
	} /* end if (non-zero) */
	return (rs >= 0) ? ulen : rs ;
}
/* end subroutine (tty_wps) */

static int tty_loadchar(uterm *op,cchar *pbuf,int pbuflen) noex {
	int		rs = SR_OK ;
	int		c = 0 ;
	for (int i = 0 ; (rs >= 0) && (i < pbuflen) ; i += 1) {
	    cint	ch = mkchar(pbuf[i]) ;
	    if (isprintlatin(ch)) {
	        c += 1 ;
	        rs = charq_ins(&op->taq,ch) ;
	    }
	} /* end for */
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (tty_loadchar) */

static int tty_wait(uterm *op,int timeout) noex {
	POLLFD		fds[2] ;
	time_t		daytime = getustime ;
	time_t		lasttime ;
	int		rs ;
	int		i ;
	int		len = 0 ;
	int		nfds ;
	int		polltime ;
	int		f_starting, f_looping ;
	char		cbuf[TTY_READCHARS+1] ;

/* initialize the POLL structure */

	nfds = 0 ;
	fds[nfds].fd = op->fd ;
	fds[nfds].events = POLLIN ;
	nfds += 1 ;
	fds[nfds].fd = -1 ;
	fds[nfds].events = POLLIN ;

	if (timeout < 0)
	    timeout = INT_MAX ;

	polltime = MIN(3000,(timeout * 1000)) ;

	op->timeout = timeout ;
	lasttime = daytime ;

#if	CF_FIRSTREAD

/* try it out the first time */

	rs = u_read(op->fd,cbuf,TTY_READCHARS) ;
	len = rs ;
	f_starting = true ;
	goto enter ;

#endif /* CF_FIRSTREAD */

/* loop it */
loop:
	f_starting = false ;

/* zero out the buffer so that we can tell if Solaris screws us later */

	for (int i = 0 ; i < TTY_READCHARS ; i += 1) {
	    cbuf[i] = '\0' ;
	}

/* wait for read attention */

	rs = u_poll(fds,1,polltime) ;

	if (rs == SR_INTR) {
	    goto loop ;
	}

/* do the system-call read */

	if ((rs >= 0) && (fds[0].revents & POLLIN)) {
	    rs = u_read(op->fd,cbuf,TTY_READCHARS) ;
	    len = rs ;
	}  /* end if */

enter:
	if (rs < 0)
	    goto ret0 ;

	op->loopcount += 1 ;
	if (len < 0)
	    goto ret0 ;

	if (len == 0) {
	    daytime = time(nullptr) ;
	    if (op->timeout >= 0) {
	        op->timeout -= (daytime - lasttime) ;
	        if (op->timeout <= 0)
	            return SR_OK ;

	    }

	    if ((! f_starting) && 
	        ((daytime - op->ti_start) >= TO_HANGUP)) {

	        f_looping = (op->loopcount > MAXLOOPS) ;
	        op->ti_start = daytime ;
	        op->loopcount = 0 ;
	        if (f_looping) {

	            rs = SR_NOANODE ;
	            goto ret0 ;
	        }

	    } /* end if (looping check) */

	} else {
	    int		i ; /* used-afterwards */
/* skip over leading zero characters fabricated by Solaris SVR4 */
	    for (i = 0 ; (i < len) && (cbuf[i] == '\0') ; i += 1) {
	    } /* end for */
/* call the Receive-Interrupt-Service-Routine with what we do have */
	    if ((len - i) > 0) {
	        rs = tty_risr(op,(cbuf + i),(len - i)) ;
	   }
	} /* end if */

/* should we go around again? */

	lasttime = daytime ;
	if ((rs >= 0) &&
	    (len <= 0) && ((op->timeout < 0) || (op->timeout > 0)))
	    goto loop ;

/* we-re out of here */
ret0:
	return (rs >= 0) ? len : rs ;
}
/* end subroutine (tty_wait) */

static int tty_risr(uterm *op,cchar *sp,int sl) noex {
	int		rs = SR_OK ;
	int		f_dle = false ;
	for (int i = 0 ; i < sl ; i += 1) {
	    cint	ch = mkchar(sp[i]) ;
	    if (op->f.nosig) {
	        rs = charq_ins(&op->taq,ch) ;
	        op->f.rw = true ;
	    } else {
	        switch (ch) {
	        case CH_XOFF:
	            op->f.suspend = true ;
	            break ;
	        case CH_XON:
	            op->f.suspend = false ;
	            break ;
	        case CH_SO:
	            if (op->f.cntl_o) {
	                op->f.cntl_o = false ;
	            } else {
	                op->f.cntl_o = true ;
		    	if (! op->f.nosigecho) {
	                    rs = tty_echo(op," ^O\r\n",5) ;
			}
	            }
	            break ;
	        case CH_ETX:
		    if (! op->f.nosigecho) {
	                rs = tty_echo(op," ^C\r\n",5) ;
		    }
	            op->f.cntl_c = true ;
	            op->f.rw = true ;
	            break ;
	        case CH_EM:
		    if (! op->f.nosigecho) {
	                rs = tty_echo(op," ^Y\r\n",5) ;
		    }
	            op->f.cntl_c = true ;
	            op->f.rw = true ;
	            break ;
	        case CH_DLE:
	            f_dle = true ;
	            break ;
/* Control-Z (substitute) */
	        case CH_SUB:
		    if (op->f.noctty) {
		        op->f.cntl_z = true ;
		    } else {
			if_constexpr (f_subunix) {
		            rs = uc_raise(SIGTSTP) ;
			} else {
		            op->f.cntl_z = true ;
			} /* end if_constexpr (f_subunix) */
		    } /* end if */
	            break ;
	        default:
	            if ((! op->f.read) && (ch == CH_CAN))  {
	                char	dch ;
	                while (charq_rem(&op->taq,&dch) >= 0) ;
	            } else {
	                rs = charq_ins(&op->taq,ch) ;
	                op->f.rw = true ;
	            }
	            break ;
	        } /* end switch */
	    } /* end if (signal-generation or not) */
	    if (rs < 0) break ;
	} /* end for */
	return (rs >= 0) ? f_dle : rs ;
}
/* end subroutine (tty_risr) */

static int tty_echo(uterm *op,cchar *ebuf,int elen) noex {
	int		rs = SR_OK ;
	if (elen < 0) elen = strlen(ebuf) ;
	if (elen > 0) {
	    rs = u_write(op->fd,ebuf,elen) ;
	}
	return rs ;
}
/* end subroutine (tty_echo) */

static int sinotprint(cchar *sp,int sl) noex {
	int		i = 0 ; /* used-afterwards */
	bool		f = false ;
	for (i = 0 ; (i < sl) && sp[0] ; i += 1) {
	    cint	ch = mkchar(sp[0]) ;
	    f = isprintlatin(ch) ;
	    f = f || (ch == CH_SI) || (ch == CH_SO) ;
	    if (! f) break ;
	} /* end for */
	return (f) ? -1 : i ;
}
/* end subroutine (sinotprint) */


