/* fmq SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 */

/* File Message Queue (FMQ) */
/* version %I% last-modified %G% */

#define	CF_SENDCREATE	0		/* sender creates also */

/* revision history:

	= 1999-07-23, David A­D­ Morano
	This module was originally written.

*/

/* Copyright © 1999 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Object:
	fmq

	Description:
	This module implements a file message queue facility.
	Enjoy!

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/stat.h>
#include	<sys/uio.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<ctime>
#include	<climits>		/* |INT_MAX| */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>		/* |memset(3c)| + |memcpy(3c)| */
#include	<algorithm>		/* |min(3c++)| + |max(3c++)| */
#include	<usystem.h>
#include	<endian.h>
#include	<absfn.h>
#include	<stdorder.h>
#include	<lockfile.h>
#include	<sfx.h>			/* |sfnamecomp(3uc)| */
#include	<strwcpy.h>
#include	<intceil.h>
#include	<isfiledesc.h>
#include	<localmisc.h>

#include	"fmq.h"


/* local defines */

#define	FMQ_OPENTIME	30	/* seconds */

#define	FMQ_IDLEN	(16 + 4)
#define	FMQ_HEADLEN	(8 * 4)
#define	FMQ_TOPLEN	(FMQ_IDLEN + FMQ_HEADLEN)

#define	FMQ_IDOFF	0
#define	FMQ_HEADOFF	FMQ_IDLEN
#define	FMQ_BUFOFF	(FMQ_HEADOFF + FMQ_HEADLEN)

#define	FMQ_BUFSIZE	((1 * 1024) + 4)
#define	FMQ_RBUFSIZE	((1 * 1024) + 4)
#define	FMQ_WBUFSIZE	((1 * 1024) + 4)

#define	TO_OPEN		(60 * 60)	/* maximum file-open time */
#define	TO_ACCESS	(2 * 60)	/* maximum access idle time */
#define	TO_LOCK		10		/* seconds */

#define	TI_MINUPDATE	4		/* minimum time between updates */

#define	FBUFLEN		(FMQ_TOPLEN + 9)


/* imported namespaces */

using std::nullptr_t ;			/* type */
using std::min ;			/* subroutine-template */
using std::max ;			/* subroutine-template */
using std::nothrow ;			/* constant */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */

template<typename ... Args>
static int fmq_ctor(fmq *op,Args ... args) noex {
	int		rs = SR_FAULT ;
	if (op && (args && ...)) {
	    rs = memclear(op) ;
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (fmq_ctor) */

static int fmq_dtor(fmq *op) noex {
	int		rs = SR_FAULT ;
	if (op) {
	    rs = SR_OK ;
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (fmq_dtor) */

static int	fmq_opener(fmq *,time_t) noex ;
static int	fmq_fnbegin(fmq *,cchar *) noex ;
static int	fmq_fnend(fmq *) noex ;

static int	fmq_isend(fmq *,cvoid *,int,int) noex ;
static int	fmq_irecv(fmq *,void *,int,int) noex ;
static int	fmq_filecheck(fmq *,time_t,int,int) noex ;
static int	fmq_filebegin(fmq *,time_t) noex ;
static int	fmq_filechanged(fmq *) noex ;
static int	fmq_lockacquire(fmq *,time_t,int) noex ;
static int	fmq_lockrelease(fmq *) noex ;
static int	fmq_fileready(fmq *,time_t) noex ;
static int	fmq_filecreate(fmq *) noex ;
static int	fmq_fileopen(fmq *,time_t) noex ;
static int	fmq_fileclose(fmq *) noex ;
static int	fmq_bufbegin(fmq *) noex ;
static int	fmq_bufend(fmq *) noex ;
static int	fmq_headwrite(fmq *) noex ;
static int	fmq_di(fmq *,sigset_t *) noex ;
static int	fmq_ei(fmq *,sigset_t *) noex ;

#ifdef	COMMENT
static int	fmq_bufadj(fmq *) noex ;
#endif

#ifdef	COMMENT
static int	fmq_headread(fmq *) noex ;
#endif

static int	filemagic(char *,int,fmq_fm *) noex ;

static int filehead_wr(fmq_fh *,cchar *) noex ;
static int filehead_rd(const fmq_fh *,char *) noex ;


/* local variables */


/* exported variables */


/* exported subroutines */

int fmq_open(fmq *op,cchar *fname,int of,mode_t om,int bsz) noex {
	int		rs ;
	int		f_create = false ;
	if ((rs = fmq_ctor(op,fname)) >= 0) {
	    rs = SR_INVALID ;
	    if (fname[0]) {
		if ((rs = ucpagesize) >= 0) {
		    op->pagesize = rs ;
		    op->bufsize = (bsz >= 0) ? rs : max(rs,FMQ_BUFSIZE) : rs ;
		    of = (of & (~ O_TRUNC)) ;
		    op->f.create = bool(of & O_CREAT) ;
		    op->f.ndelay = bool(of & O_NDELAY) ;
		    op->f.nonblock = bool(of & O_NONBLOCK) ;
		    of = (of & (~ (O_NDELAY | O_NONBLOCK))) ;
		    op->oflags = of ;
		    op->operm = om ;
		    if ((rs = fmq_fnbegin(op,fname)) >= 0) {
		        if ((rs = fmq_bufbegin(op)) >= 0) {
			    custime	dt = getustime ;
			    if ((rs = fmq_fileopen(op,dt)) >= 0) {
				f_create = op->f.created ;
				{
    				    rs = fmq_opener(op,dt) ;
				}
				if (rs < 0) {
				    fmq_fileclose(op) ;
				}
			    } /* end if (fmq_fileopen) */
			    if (rs < 0) {
			        fmq_bufend(op) ;
			    }
		        } /* end if (fmq_bufbegin) */
		        if (rs < 0) {
			    fmq_fnend(op) ;
		        }
		    } /* end if (fmq_fnbegin) */
		} /* end if (ucpagesize) */
	    } /* end if (valid) */
	    if (rs < 0) {
		fmq_dtor(op) ;
	    }
	} /* end if (fmq_ctor) */
	return (rs >= 0) ? f_create : rs ;
}
/* end subroutine (fmq_open) */

int fmq_close(fmq *op) noex {
	int		rs ;
	int		rs1 ;
	if ((rs = fmq_magic(op)) >= 0) {
	    {
	        rs1 = fmq_bufend(op) ;
	        if (rs >= 0) rs = rs1 ;
	    }
	    {
	       rs1 = fmq_fileclose(op) ;
	       if (rs >= 0) rs = rs1 ;
	    }
	    {
	       rs1 = fmq_fnend(op) ;
	       if (rs >= 0) rs = rs1 ;
	    }
	    {
	       rs1 = fmq_dtor(op) ;
	       if (rs >= 0) rs = rs1 ;
	    }
	    op->magic = 0 ;
	} /* end if (magic) */
	return rs ;
}
/* end subroutine (fmq_close) */

int fmq_count(fmq *op) noex {
	int		rs ;
	int		c = 0 ;
	if ((rs = fmq_magic(op)) >= 0) {
	    c = op->count ;
	}
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (fmq_count) */

int fmq_send(fmq *op,cvoid *buf,int buflen) noex {
	int		rs ;
	int		tlen = 0 ;
	if ((rs = fmq_magic(op,buf)) >= 0) {
	    rs = SR_RDONLY ;
	    if (op->f.writable) {
	        cint	to = -1 ;
	        rs = fmq_sende(op,buf,buflen,to,0) ;
	        tlen = rs ;
	    } /* end if (valid) */
	} /* end if (magic) */
	return (rs >= 0) ? tlen : rs ;
}
/* end subroutine (fmq_send) */

int fmq_recv(fmq *op,void *buf,int buflen) noex {
	int		rs ;
	int		tlen = 0 ;
	if ((rs = fmq_magic(op,buf)) >= 0) {
	    cint	to = -1 ;
	    rs = fmq_recve(op,buf,buflen,to,0) ;
	    tlen = rs ;
	} /* end if (magic) */
	return (rs >= 0) ? tlen : rs ;
}
/* end subroutine (fmq_recv) */

int fmq_sende(fmq *op,cvoid *ubuf,int ulen,int to,int opts) noex {
	int		rs ;
	int		tlen = 0 ;
	if ((rs = fmq_magic(op,ubuf)) >= 0) {
	    time_t	dt = getustime ;
	    bool	f_inf = false ;
	    if (to < 0) {
	        f_inf = true ;
	        to = INT_MAX ;
	    }
	    rs = SR_RDONLY ;
	    if (op->f.writable) {
	        time_t	tiend = (dt + to) ;
	        forever {
	            rs = fmq_isend(op,ubuf,ulen,opts) ;
	            tlen = rs ;
	            if (rs >= 0) break ;
	            if (rs != SR_AGAIN) break ;
	            if (f_inf && (op->f.ndelay || op->f.nonblock)) break ;
	            msleep(10) ;
	            dt = getustime ;
	            if (dt >= tiend) break ;
	        } /* end forever */
	        if ((rs == SR_AGAIN) && op->f.ndelay) {
	            tlen = 0 ;
	            rs = SR_OK ;
	        }
	    } /* end if (valid) */
	} /* end if (magic) */
	return (rs >= 0) ? tlen : rs ;
}
/* end subroutine (fmq_sende) */

int fmq_recve(fmq *op,void *buf,int buflen,int to,int opts) noex {
	int		rs ;
	int		tlen = 0 ;
	if ((rs = fmq_magic(op,buf)) >= 0) {
	    time_t	dt = getustime ;
	    bool	f_inf = false ;
	    if (to < 0) {
	        f_inf = true ;
	        to = INT_MAX ;
	    }
	    {
		time_t	tiend = (dt + to) ;
	        while (to >= 0) {
	            rs = fmq_irecv(op,buf,buflen,opts) ;
	            tlen = rs ;
	            if (rs >= 0) break ;
	            if (rs != SR_AGAIN) break ;
	            if (f_inf && (op->f.ndelay || op->f.nonblock)) break ;
	            msleep(10) ;
		    dt = getustime ;
		    if (dt >= tiend) break ;
	        } /* end while */
	        if ((rs == SR_AGAIN) && op->f.ndelay) {
	            tlen = 0 ;
	            rs = SR_OK ;
	        }
	    } /* end block */
	} /* end if (magic) */
	return (rs >= 0) ? tlen : rs ;
}
/* end subroutine (fmq_recve) */

int fmq_check(fmq *op,time_t dt) noex {
	int		rs ;
	int		f = false ;
	if ((rs = fmq_magic(op)) >= 0) {
	    if (op->fd >= 0) {
	        if ((! op->f.readlocked) && (! op->f.writelocked)) {
	            if ((dt - op->accesstime) >= TO_ACCESS) {
	                f = true ;
		        rs = fmq_fileclose(op) ;
		    }
	        }
	    }
	} /* end if (magic) */
	return (rs >= 0) ? f : rs ;
}
/* end subroutine (fmq_check) */


/* private subroutines */

static int fmq_fnbegin(fmq *op,cchar *fname) noex {
    	int		rs = SR_OK ;
	int		rs1 ;
	cchar		*fnp{} ;
	if (int fnl ; (fnl = sfnamecomp(fname,0,&fnp)) > 0) {
	    cchar	*afn{} ;
	    if (absfn af ; (rs = af.start(fnp,fnl,&afn)) >= 0) {
	        if (cchar *cp{} ; (rs = uc_mallocstrw(afn,rs,&cp)) >= 0) {
		    op->fname = cp ;
		} /* end if (memory-allocation) */
		rs1 = af.finish ;
		if (rs >= 0) rs = rs1 ;
	    } /* end if (absfn) */
	} /* end if (sfnamecomp) */
	return rs ;
}
/* end subroutine (fmq_fnbegin) */

static int fmq_fnend(fmq *op) noex {
    	int		rs = SR_OK ;
	int		rs1 ;
	if (op->fname) {
	    rs1 = uc_free(op->fname) ;
	    if (rs >= 0) rs = rs1 ;
	    op->fname = nullptr ;
	}
	return rs ;
}
/* end subroutine (fmq_fnend) */

static int fmq_opener(fmq *op,time_t dt) noex {
	int		rs ;
	op->opentime = dt ;
	op->accesstime = dt ;
	if (USTAT sb ; (rs = u_fstat(op->fd,&sb)) >= 0) {
	    if (sb.st_size <= INT_MAX) {
	        op->mtime = sb.st_mtime ;
	        op->filesize = int(sb.st_size) ;
	        /* local or remote */
	        if ((rs = isfsremote(op->fd)) >= 0) {
	            op->f.remote = (rs > 0) ;
	            /* setup for disabling signals */
	            if ((rs = uc_sigsetfill(&op->sigmask)) >= 0) {
		        if ((rs = fmq_filebegin(op,dt)) >= 0) {
			    op->magic = FMQ_MAGIC ;
		        }
		    }
	        } /* end if (isfsremote) */
	    } else {
		rs = SR_TOOBIG ;
	    }
	} /* end if (u_fstat) */
	return rs ;
}
/* end subroutine (fmq_opener) */

static int fmq_isend(fmq *op,cvoid *buf,int buflen,int opts) noex {
	IOVEC		v[3] ;
	sigset_t	oldsigmask ;
	off_t		uoff ;
	time_t		dt = getustime ;
	uint		eoff ;
	int		llen, dlen, len ;
	int		rs ;
	char		lenbuf[4 + 1] ;
	char		*cbuf = (char *) buf ;
	(void) opts ;
	fmq_di(op,&oldsigmask) ;
	if ((rs = fmq_filecheck(op,dt,0,0)) >= 0) {
/* is the file initialized? */
	if (! op->f.fileinited) {

#if	CF_SENDCREATE
	    rs = SR_ACCESS ;
	    if (! op->f.create)
	        goto ret1 ;
#endif /* CF_SENDCREATE */

	    if (dt == 0) dt = getustime ;

	    rs = fmq_filebegin(op,dt) ;
	    if (rs < 0)
	        goto ret1 ;

	}
/* prepare the message header (the length) */
	llen = stdorder_wui(lenbuf,buflen) ;
/* can we even write this message? */
	if ((buflen + llen) > (op->h.bsz - op->h.blen)) {
	    rs = ((buflen + llen) > op->h.bsz) ? SR_TOOBIG : SR_AGAIN ;
	    goto ret1 ;
	}
/* prepare to write */
	if (op->h.wi < op->h.ri) {
	    dlen = op->h.ri - op->h.wi ;
	} else {
	    dlen = op->h.bsz - op->h.wi ;
	}
	dlen -= llen ;
	if (buflen < dlen) {
	    dlen = buflen ;
	}
/* set up the write buffers */
	v[0].iov_base = lenbuf ;
	v[0].iov_len = llen ;
	v[1].iov_base = (caddr_t) cbuf ;
	v[1].iov_len = dlen ;
	v[2].iov_base = nullptr ;
	v[2].iov_len = 0 ;
	eoff = FMQ_BUFOFF + op->h.wi ;
	uoff = eoff ;
	rs = u_seek(op->fd,uoff,SEEK_SET) ;
	if (rs >= 0) {
	    rs = u_writev(op->fd,v,2) ;
	}
	if ((rs >= 0) && (dlen < buflen)) {
	    v[0].iov_base = (caddr_t) (cbuf + dlen) ;
	    v[0].iov_len = (buflen - dlen) ;
	    v[1].iov_base = nullptr ;
	    v[1].iov_len = 0 ;
	    eoff = FMQ_BUFOFF ;
	    uoff = eoff ;
	    if ((rs = u_seek(op->fd,uoff,SEEK_SET)) >= 0) {
	        rs = u_writev(op->fd,v,1) ;
	    }
	} /* end if (wrapped around) */
	if (rs > 0) {
	    len = uceil((llen + buflen),llen) ;
	    op->h.wi = (op->h.wi + len) % op->h.bsz ;
	    op->h.blen += len ;
	    op->h.len += buflen ;
	    op->h.nmsg += 1 ;
	    if (dt == 0) dt = getustime ;
	    op->h.wcount += 1 ;
	    op->h.wtime = dt ;

	    rs = fmq_headwrite(op) ;

	    if ((rs >= 0) && op->f.remote) {
	        u_fsync(op->fd) ;
	    }
	} /* end if (data write was successful) */

ret1:
	fmq_lockrelease(op) ;

ret0:
	fmq_ei(op,&oldsigmask) ;

	} /* end if (filecheck) */
	return (rs >= 0) ? buflen : rs ;
}
/* end subroutine (fmq_isend) */

static int fmq_irecv(fmq *op,void *buf,int buflen,int opts) noex {
	IOVEC		v[3] ;
	USTAT		sb ;
	sigset_t	oldsigmask ;
	off_t		uoff ;
	time_t		dt = 0 ;
	uint		eoff ;
	uint		llen, dlen, mlen, len ;
	int		rs = SR_OK ;
	int		tlen = 0 ;
	int		f_changed ;
	char		lenbuf[4 + 1] ;
	char		*cbuf = (char *) buf ;
	/* are we in optional slow-poll mode? */
	if ((opts & FM_SLOWPOLL) && (op->h.nmsg == 0)) {

	    rs = u_fstat(op->fd,&sb) ;
	    if (rs < 0)
	        goto ret0 ;

	    f_changed = (sb.st_size != op->filesize) ||
	        (sb.st_mtime != op->mtime) ;

	    rs = SR_AGAIN ;
	    if (! f_changed)
	        goto ret0 ;

	} /* end if (optional slow-poll mode) */

/* continue with a regular operation */

	fmq_di(op,&oldsigmask) ;

/* do we have proper file access? */

	if (dt == 0) dt = getustime ;

	rs = fmq_filecheck(op,dt,0,opts) ;
	if (rs < 0)
	    goto ret2 ;

/* is the file initialized? */

	if (! op->f.fileinited) {
	    if (dt == 0) dt = getustime ;
	    rs = fmq_filebegin(op,dt) ;
	    if (rs < 0)
	        goto ret2 ;

	}

/* are there any messages to receive? */

	if (op->h.nmsg == 0) {
	    rs = SR_AGAIN ;
	    goto ret2 ;
	}

	llen = szof(uint) ;

/* prepare to read */

	if (op->h.ri >= op->h.wi) {
	    dlen = op->h.wi - op->h.ri ;
	} else {
	    dlen = op->h.bsz - op->h.ri ;
	}

	dlen -= llen ;
	if (buflen < dlen)
	    dlen = buflen ;

/* set up the read buffers */

	v[0].iov_base = lenbuf ;
	v[0].iov_len = llen ;
	v[1].iov_base = (caddr_t) cbuf ;
	v[1].iov_len = dlen ;
	v[2].iov_base = nullptr ;
	v[2].iov_len = 0 ;

	eoff = FMQ_BUFOFF + op->h.ri ;
	uoff = eoff ;
	if ((rs = u_seek(op->fd,uoff,SEEK_SET)) >= 0) {
	    rs = u_readv(op->fd,v,2) ;
	}

	if (rs >= llen) {

	    tlen = rs - llen ;
	    stdorder_rui(lenbuf,&mlen) ;

	    if (mlen > tlen) {

	        if (buflen >= mlen) {

	            v[0].iov_base = (caddr_t) (cbuf + tlen) ;
	            v[0].iov_len = (mlen - tlen) ;

	            v[1].iov_base = nullptr ;
	            v[1].iov_len = 0 ;

	            eoff = FMQ_BUFOFF ;
		    uoff = eoff ;
	            rs = u_seek(op->fd,uoff,SEEK_SET) ;

	            if (rs >= 0)
	                rs = u_readv(op->fd,v,1) ;

	            if (rs >= 0)
	                tlen += rs ;

	        } else
	            rs = SR_OVERFLOW ;

	    } else
	        tlen = mlen ;

	} else
	    rs = SR_BADFMT ;

	if (rs >= 0) {

	    len = uceil((llen + mlen),llen) ;

	    op->h.ri = (op->h.ri + len) % op->h.bsz ;
	    op->h.blen -= len ;
	    op->h.len -= mlen ;
	    op->h.nmsg -= 1 ;

	    if (dt == 0)
	        dt = getustime ;

	    op->h.wcount += 1 ;
	    op->h.wtime = dt ;

	    rs = fmq_headwrite(op) ;

	    if ((rs >= 0) && op->f.remote) {
	        u_fsync(op->fd) ;
	    }
	} /* end if (we were able to turn the buffer) */

ret2:
	fmq_lockrelease(op) ;

ret1:
	fmq_ei(op,&oldsigmask) ;

ret0:
	return (rs >= 0) ? tlen : rs ;
}
/* end subroutine (fmq_irecv) */

static int fmq_filecheck(fmq *op,time_t dt,int f_read,int opts) noex {
	int		rs ;
	int		f_changed = false ;
	(void) opts ;
	if (dt == 0) dt = getustime ;
	if ((rs = fmq_fileready(op,dt)) >= 0) {
	    if ((! op->f.readlocked) && (! op->f.writelocked)) {
	        if ((rs = fmq_lockacquire(op,dt,f_read)) >= 0) {
	            rs = fmq_filechanged(op) ;
	            f_changed = (rs > 0) ;
		    if (rs < 0) {
			fmq_lockrelease(op) ;
		    }
	        } /* end if (lockget) */
	    } /* end if (capture lock) */
	} /* end if (fileready) */
	return (rs >= 0) ? f_changed : rs ;
}
/* end subroutine (fmq_filecheck) */

/* has the file changed at all? */
static int fmq_filechanged(fmq *op) noex {
	int		rs ;
	int		fch = false ;
	if (USTAT sb ; (rs = u_fstat(op->fd,&sb)) >= 0) {
	    if (sb.st_size < FMQ_BUFOFF) {
		op->f.fileinited = false ;
	    }
	    fch = fch || (! op->f.fileinited) ;
	    fch = fch || (sb.st_size != op->filesize) ;
	    fch = fch || (sb.st_mtime != op->mtime) ;
	    if (fch) {
	        op->f.bufvalid = false ;
	        op->filesize = int(sb.st_size) ;
	        op->mtime = sb.st_mtime ;
	    }
	} /* end if (stat) */
	return (rs >= 0) ? fch : rs ;
}
/* end subroutine (fmq_filechanged) */

static int fmq_bufbegin(fmq *op) noex {
        cint		bsz = op->bufsize ;
	int		rs = SR_OK ;
	if (op->b.buf == nullptr) {
	    op->f.bufvalid = false ;
	    op->b = {} ;
	    if (void *vp{} ; (rs = uc_malloc(bsz,&vp)) >= 0) {
	        op->b.buf = charp(vp) ;
	        op->b.bsz = bsz ;
	    }
	} /* end block */
	return rs ;
}
/* end subroutine (fmq_bufbegin) */

static int fmq_bufend(fmq *op) noex {
	int		rs = SR_OK ;
	int		rs1 ;
	if (op->b.buf) {
	    rs1 = uc_free(op->b.buf) ;
	    if (rs >= 0) rs = rs1 ;
	    op->b.buf = nullptr ;
	}
	op->b.bsz = 0 ;
	op->b.len = 0 ;
	op->b.i = 0 ;
	return rs ;
}
/* end subroutine (fmq_bufend) */

/* initialize the file header (either read it only or write it) */
static int fmq_filebegin(fmq *op,time_t dt) noex {
	fmq_fm		fm ;
	sigset_t	oldsigmask ;
	int		rs = SR_OK ;
	int		bl ;
	int		f_locked = false ;
	char		fbuf[FBUFLEN + 1] ;

	fmq_di(op,&oldsigmask) ;

	if (op->filesize == 0) {

	    u_seek(op->fd,0L,SEEK_SET) ;

	    op->f.fileinited = false ;
	    if (op->f.writable && op->f.create) {

	        if (! op->f.writelocked) {

	            rs = fmq_lockacquire(op,dt,0) ;
	            if (rs < 0)
	                goto ret0 ;

	            f_locked = true ;
	        }

/* write the file header stuff */

	        strwcpy(fm.magic,FMQ_FILEMAGIC,15) ;

	        fm.vetu[0] = FMQ_FILEVERSION ;
	        fm.vetu[1] = FMQ_ENDIAN ;
	        fm.vetu[2] = 0 ;
	        fm.vetu[3] = 0 ;
	        bl = 0 ;
	        bl += filemagic((fbuf + bl),0,&fm) ;
	        op->h = {} ;
	        op->h.bsz = op->bufsize ;
	        /* bl += filehead((fbuf + bl),0,&op->h) ; */
	        bl += filehead_rd(&op->h,(fbuf + bl)) ;
	        if ((rs = u_pwrite(op->fd,fbuf,bl,0z)) > 0) {
	            op->filesize = rs ;
	            op->mtime = dt ;
	            if (op->f.remote) {
	                u_fsync(op->fd) ;
		    }
	        }
	        op->f.fileinited = (rs >= 0) ;
	    } /* end if (writing) */

	} else if (op->filesize >= FMQ_BUFOFF) {
	    int	f ;

		/* read the file header */

	    if (! op->f.readlocked) {

	        rs = fmq_lockacquire(op,dt,0) ;
	        if (rs < 0)
	            goto ret0 ;

	        f_locked = true ;
	    }

	    rs = u_pread(op->fd,fbuf,FBUFLEN,0z) ;

	    if (rs >= FMQ_TOPLEN) {

	        bl = 0 ;
	        bl += filemagic((fbuf + bl),1,&fm) ;

	        /* filehead((fbuf + bl),1,&op->h) ; */
	        filehead_wr(&op->h,(fbuf + bl)) ;

	        f = (strcmp(fm.magic,FMQ_FILEMAGIC) == 0) ;
	        f = f && (fm.vetu[0] <= FMQ_FILEVERSION) ;
	        f = f && (fm.vetu[1] == FMQ_ENDIAN) ;
	        if (! f)
	            rs = SR_BADFMT ;

	        op->f.fileinited = f ;

	    } /* end if (read was big enough) */

	} /* end if */

/* if we locked, we unlock it, otherwise leave it ! */

	if (f_locked)
	    fmq_lockrelease(op) ;

/* we're out of here */
ret0:
	fmq_ei(op,&oldsigmask) ;

	return rs ;
}
/* end subroutine (fmq_filebegin) */

static int fmq_lockacquire(fmq *op,time_t dt,int f_read) noex {
	int		rs ;
	int		f_already = false ;
	if ((rs = fmq_fileready(op,dt)) >= 0) {
	    int		lockcmd{} ;
	    if (f_read || (! op->f.writable)) {
	        f_already = op->f.readlocked ;
	        op->f.readlocked = true ;
	        op->f.writelocked = false ;
	        lockcmd = F_RLOCK ;
	    } else {
	        f_already = op->f.writelocked ;
	        op->f.readlocked = false ;
	        op->f.writelocked = true ;
	        lockcmd = F_WLOCK ;
	    }
    	    /* get out if we have the lock that we want already */
	    if (! f_already) {
	        coff	fs = off_t(op->filesize) ;
	        rs = lockfile(op->fd,lockcmd,0z,fs,TO_LOCK) ;
	    }
	} /* end if (fmq_fileready) */
	return rs ;
}
/* end subroutine (fmq_lockacquire) */

static int fmq_lockrelease(fmq *op) noex {
	int		rs = SR_OK ;
	if ((op->f.readlocked || op->f.writelocked)) {
	    if (op->fd >= 0) {
		coff	fs = off_t(op->filesize) ;
	        rs = lockfile(op->fd,F_ULOCK,0z,fs,TO_LOCK) ;
	    }
	    op->f.readlocked = false ;
	    op->f.writelocked = false ;
	}
	return rs ;
}
/* end subroutine (fmq_lockrelease) */

static int fmq_fileready(fmq *op,time_t dt) noex {
	int		rs = SR_OK ;
	if (op->fd < 0) {
	    if (dt == 0) dt = getustime ;
	    rs = fmq_fileopen(op,dt) ;
	}
	return rs ;
}
/* end subroutine (fmq_filready) */

static int fmq_fileopen(fmq *op,time_t dt) noex {
	int		rs = SR_OK ;
	if (op->fd < 0) {
	    if ((rs = fmq_filecreate(op)) >= 0) {
		if ((rs = uc_closeonexec(op->fd,true)) >= 0) {
		    op->opentime = dt ;
		}
		if (rs < 0) {
		    u_close(op->fd) ;
		    op->fd = -1 ;
		}
	    } /* end if (fmq_filecreate) */
	} /* end if (needed open) */
	return rs ;
}
/* end subroutine (fmq_fileopen) */

static int fmq_filecreate(fmq *op) noex {
    	cint		rsn = SR_NOTFOUND ;
	cint		am = int(op->operm & O_ACCMODE) ;
    	int		rs ;
	int		of = op->oflags & (~ O_CREAT) ;
	cmode		om = op->operm ;
	op->f.writable = ((am == O_WRONLY) || (am == O_RDWR)) ;
	if ((rs = u_open(op->fname,of,om)) >= 0) {
	    op->fd = rs ;
	} else if ((rs == rsn) && (op->oflags & O_CREAT)) {
	    of |= O_CREAT ;
	    if ((rs = u_open(op->fname,of,om)) >= 0) {
	        op->fd = rs ;
	        op->f.created = true ;
	    }
	} /* end if (creating file) */
	return rs ;
}
/* end subroutine (fmq_filecreate) */

static int fmq_fileclose(fmq *op) noex {
	int		rs = SR_OK ;
	int		rs1 ;
	if (op->fd >= 0) {
	    rs1 = u_close(op->fd) ;
	    if (rs >= 0) rs = rs1 ;
	    op->fd = -1 ;
	}
	return rs ;
}
/* end subroutine (fmq_fileclose) */

static int fmq_headwrite(fmq *op) noex {
	coff		uoff = FMQ_HEADOFF ;
	int		rs ;
	char		fbuf[FBUFLEN + 1] ;
	if ((rs = filehead_rd(&op->h,fbuf)) >= 0) {
	    rs = u_pwrite(op->fd,fbuf,rs,uoff) ;
	}
	return rs ;
}
/* end subroutine (fmq_headwrite) */

static int fmq_di(fmq *op,sigset_t *smp) noex {
	int		rs = SR_BADFMT ;
	if (op && smp) {
	    rs = u_sigmask(SIG_BLOCK,&op->sigmask,smp) ;
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (fmq_di) */

static int fmq_ei(fmq *op,sigset_t *smp) noex {
	int		rs = SR_BADFMT ;
	if (op && smp) {
	    rs = u_sigmask(SIG_SETMASK,smp,nullptr) ;
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (fmq_ei) */

#ifdef	COMMENT
static int fmq_bufadj(fmq *op) noex {
    	int		rs = SR_OK ;
	if (cint sz ; (sz = uceil(op->bufsize,szof(int))) != op->bufsize) {
	    op->bufsize = sz ;
	}
	return rs ;
}
/* end subroutine (fmq_bufadj) */
#endif /* COMMENT */

static int filemagic(char *buf,int f_read,fmq_fm *mp) noex {
	int		rs = SR_BADFMT ;
	if (buf && mp) {
	    char	*bp = buf ;
	    rs = 20 ;
	    if (f_read) {
	        bp[15] = '\0' ;
	        strncpy(mp->magic,bp,15) ;
	        if (char *cp ; (cp = strchr(mp->magic,'\n')) != nullptr) {
	            *cp = '\0' ;
	        }
	        bp += 16 ;
	        memcpy(mp->vetu,bp,4) ;
	    } else {
	        bp = strwcpy(bp,mp->magic,15) ;
	        *bp++ = '\n' ;
	        memset(bp,0,(16 - (bp - buf))) ;
	        bp = buf + 16 ;
	        memcpy(bp,mp->vetu,4) ;
	    } /* end if */
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (filemagic) */

/* encode or decode the file header */
static int filehead_wr(fmq_fh *hp,cchar *buf) noex {
	const uint	*table = (uint *) buf ;
	int		rs = SR_BADFMT ;
	if (buf) {
	        stdorder_rui(charp(table + 0),&hp->wcount) ;
	        stdorder_rui(charp(table + 1),&hp->wtime) ;
	        stdorder_rui(charp(table + 2),&hp->nmsg) ;
	        stdorder_rui(charp(table + 3),&hp->bsz) ;
	        stdorder_rui(charp(table + 4),&hp->blen) ;
	        stdorder_rui(charp(table + 5),&hp->len) ;
	        stdorder_rui(charp(table + 6),&hp->ri) ;
	        stdorder_rui(charp(table + 7),&hp->wi) ;
	    rs = FMQ_HEADLEN ;
	}
	return rs ;
}
/* end subroutine (filehead_wr) */
static int filehead_rd(const fmq_fh *hp,char *buf) noex {
	uint		*table = (uint *) buf ;
	int		rs = SR_BADFMT ;
	if (buf) {
	        stdorder_wui(charp(table + 0),hp->wcount) ;
	        stdorder_wui(charp(table + 1),hp->wtime) ;
	        stdorder_wui(charp(table + 2),hp->nmsg) ;
	        stdorder_wui(charp(table + 3),hp->bsz) ;
	        stdorder_wui(charp(table + 4),hp->blen) ;
	        stdorder_wui(charp(table + 5),hp->len) ;
	        stdorder_wui(charp(table + 6),hp->ri) ;
	        stdorder_wui(charp(table + 7),hp->wi) ;
	    rs = FMQ_HEADLEN ;
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (filehead_rd) */


