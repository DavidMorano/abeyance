/* lastlogfile SUPPORT */
/* lang=C++20 */

/* manage reading or writing a LASTLOG file */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-08-22, David A­D­ Morano
	This subroutine module was adopted for use from some previous
	code that performed the similar sorts of functions.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	lastlogfile

	Description:
	This code is used to manage one LASTLOG type file.  This
	sort of file is usually used to track the last time that a
	person has logged in.  This function was implemented as
	part of PCS long before it was adopted as standard (or
	pseudo standard) practice in UNIX® proper.  This code
	represents a shift for PCS related software from using the
	older proprietary LASTLOG feature to the newer UNIX® standard
	(pseudo standard -- whatever) mechanism.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/param.h>
#include	<sys/stat.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<ctime>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<usystem.h>
#include	<sysval.hh>
#include	<strwcpy.h>
#include	<localmisc.h>

#include	"lastlogfile.h"


/* local defines */

#define	LASTLOGFILE_ENTSIZE	sizeof(LASTLOGFILE_ENT)
#define	LASTLOGFILE_OPENTIME	30	/* seconds */

#define	LLF			LASTLOGFILE
#define	LLF_ENT			LASTLOGFILE_ENT


/* imported namespaces */


/* local typedefs */


/* external subroutines */

extern "C" {
    int		lastlogfile_close(LLF *) noex ;
}


/* external variables */


/* local structures */


/* forward references */

template<typename ... Args>
static int lastlogfile_ctor(lastlogfile *op,Args ... args) noex {
	int		rs = SR_FAULT ;
	if (op && (args && ...)) {
	    cnullptr	np{} ;
	    rs = SR_OK ;

	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (lastlogfile_ctor) */

static int lastlogfile_dtor(lastlogfile *op) noex {
	int		rs = SR_FAULT ;
	if (op) {
	    rs = SR_OK ;
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (lastlogfile_dtor) */

template<typename ... Args>
static inline int lastlogfile_magic(lastlogfile *op,Args ... args) noex {
	int		rs = SR_FAULT ;
	if (op && (args && ...)) {
	    rs = (op->magic == LASTLOGFILE_MAGIC) ? SR_OK : SR_NOTOPEN ;
	}
	return rs ;
}
/* end subroutine (lastlogfile_magic) */

static int	lastlogfile_checkopen(LLF *) noex ;
static int	lastlogfile_fileclose(LLF *) noex ;


/* local variables */

static sysval		pagesize(sysval_ps) ;


/* exported variables */


/* exported subroutines */

int lastlogfile_open(LLF *op,cchar *fname,int oflags) noex {
	int		rs ;
	if (fname == nullptr) fname = LASTLOGFILE_FILEPATH ;
	if (fname[0] == '\0') fname = LASTLOGFILE_FILEPATH ;
	if ((rs = lastlogfile_ctor(op)) >= 0) {
	    memclear(op) ;
	    op->oflags = oflags ;
	    op->fd = -1 ;
	    if ((rs = pagesize) >= 0) {
	        cchar		*cp ;
	        op->pagesize = rs ;
	        if ((rs = uc_mallocstrw(fname,-1,&cp)) >= 0) {
	            op->fname = cp ;
	            if ((rs = lastlogfile_checkopen(op)) >= 0) {
		        USTAT	sb ;
	                if ((rs = u_fstat(op->fd,&sb)) >= 0) {
	                    op->fsize = size_t(sb.st_size) ;
	                    op->mtime = sb.st_mtime ;
	                    op->magic = LASTLOGFILE_MAGIC ;
		        }
		        if (rs < 0) {
		            lastlogfile_fileclose(op) ;
		        }
	            } /* end if (file-open) */
	            if (rs < 0) {
	                uc_free(op->fname) ;
	                op->fname = nullptr ;
	            }
	        } /* end if (memory-allocation) */
	    } /* end if (pagesize) */
	    if (rs < 0) {
		lastlogfile_dtor(op) ;
	    }
	} /* end if (lastlogfile_ctor) */
	return rs ;
}
/* end subroutine (lastlogfile_open) */

int lastlogfile_close(LLF *op) noex {
	int		rs ;
	int		rs1 ;
	if ((rs = lastlogfile_magic(op)) >= 0) {
	    if (op->fd >= 0) {
	        rs1 = u_close(op->fd) ;
	        if (rs >= 0) rs = rs1 ;
	    }
	    if (op->fname) {
	        rs1 = uc_free(op->fname) ;
	        if (rs >= 0) rs = rs1 ;
	        op->fname = nullptr ;
	    }
	    {
	        rs1 = lastlogfile_dtor(op) ;
	        if (rs >= 0) rs = rs1 ;
	    }
	    op->magic = 0 ;
	} /* end if (magic) */
	return rs ;
}
/* end subroutine (lastlogfile_close) */

int lastlogfile_readentry(LLF *op,uid_t uid,LLF_ENT *ep) noex {
	LASTLOGFILE_ENT	e ;
	off_t	loc ;
	int		rs = SR_OK ;

	if (op == nullptr) return SR_FAULT ;
	if (op->magic != LASTLOGFILE_MAGIC) return SR_NOTOPEN ;

/* check if operation is allowed */

	if (((op->oflags & O_RDONLY) != O_RDONLY) &&
	    ((op->oflags & O_RDWR) != O_RDWR))
	    return SR_ACCESS ;

	loc = uid * LASTLOGFILE_ENTSIZE ;
	if (loc >= op->fsize)
	    return SR_EOF ;

/* proceed with operation */

	if (ep == nullptr)
	    ep = &e ;

	if (op->fd < 0)
	    rs = lastlogfile_checkopen(op) ;

	if (rs >= 0)
	    rs = u_pread(op->fd,ep,LASTLOGFILE_ENTSIZE,loc) ;

	if ((rs >= 0) && (ep->ll_time == 0))
	    rs = SR_BADSLT ;

	return rs ;
}
/* end subroutine (lastlogfile_readentry) */

int lastlogfile_writeentry(LLF *op,uid_t uid,LLF_ENT *ep) noex {
	off_t		loc ;
	int		rs = SR_OK ;

	if (op == nullptr) return SR_FAULT ;
	if (ep == nullptr) return SR_FAULT ;
	if (op->magic != LASTLOGFILE_MAGIC) return SR_NOTOPEN ;

/* check if operation is allowed */

	if (((op->oflags & O_WRONLY) != O_WRONLY) &&
	    ((op->oflags & O_RDWR) != O_RDWR))
	    return SR_ACCESS ;

/* proceed with operation */

	if (op->fd < 0) {
	    rs = lastlogfile_checkopen(op) ;
	}

	if (rs >= 0) {
	    loc = uid * LASTLOGFILE_ENTSIZE ;
	    rs = u_pwrite(op->fd,ep,LASTLOGFILE_ENTSIZE,loc) ;
	}

	return rs ;
}
/* end subroutine (lastlogfile_writeentry) */

int lastlogfile_readinfo(LLF *op,uid_t uid,time_t *tp,char *line,
		char *hostname) noex {
	LASTLOGFILE_ENT	e ;
	off_t	loc ;
	const int	of = op->oflags ;
	const int	esize = LASTLOGFILE_ENTSIZE ;
	int		rs = SR_OK ;

	if (op == nullptr) return SR_FAULT ;
	if (op->magic != LASTLOGFILE_MAGIC) return SR_NOTOPEN ;
	if (uid < 0) return SR_INVALID ;

/* check if operation is allowed */

	if (((of & O_RDONLY) != O_RDONLY) && ((of & O_RDWR) != O_RDWR))
	    return SR_ACCESS ;

	loc = (uid * esize) ;
	if (loc >= op->fsize)
	    return SR_EOF ;

/* proceed with operation */

	if (op->fd < 0)
	    rs = lastlogfile_checkopen(op) ;

	if (rs >= 0) {
	    if ((rs = u_pread(op->fd,&e,esize,loc)) >= 0) {
		if ((rs > 0) && (e.ll_time != 0)) {

	    	    if (tp != nullptr)
	                *tp = e.ll_time ;

	            if (hostname != nullptr)
	                strwcpy(hostname,e.ll_host,LASTLOGFILE_LHOST) ;

	            if (line != nullptr)
	                strwcpy(line,e.ll_line,LASTLOGFILE_LLINE) ;

	        } else {
	            rs = 0 ;

	            if (tp != nullptr)
	                *tp = 0 ;

	            if (hostname != nullptr)
	                hostname[0] = '\0' ;

	            if (line != nullptr)
	                line[0] = '\0' ;

	        } /* end if */
	    } /* end if (u_pread) */
	} /* end if (ok) */

	return rs ;
}
/* end subroutine (lastlogfile_readinfo) */

int lastlogfile_writeinfo(LLF *op,uid_t uid,time_t t,cchar *line,
		cchar *hostname)
{
	LASTLOGFILE_ENT	e ;
	off_t	loc ;
	int		rs = SR_OK ;

	if (op == nullptr) return SR_FAULT ;
	if (op->magic != LASTLOGFILE_MAGIC) return SR_NOTOPEN ;

/* check if operation is allowed */

	if (((op->oflags & O_WRONLY) != O_WRONLY) &&
	    ((op->oflags & O_RDWR) != O_RDWR))
	    return SR_ACCESS ;

/* proceed with operation */

	if (op->fd < 0) {
	    rs = lastlogfile_checkopen(op) ;
	}

	if (rs >= 0) {

	    (void) memset(&e,0,sizeof(LASTLOGFILE_ENT)) ;

	    if (t < 0)
	        t = time(nullptr) ;

	    e.ll_time = t ;

	    if (hostname != nullptr) {
	        strncpy(e.ll_host,hostname,LASTLOGFILE_LHOST) ;
	    }

	    if (line != nullptr) {
	        strncpy(e.ll_line,line,LASTLOGFILE_LLINE) ;
	    }

	    loc = uid * LASTLOGFILE_ENTSIZE ;
	    rs = u_pwrite(op->fd,&e,LASTLOGFILE_ENTSIZE,loc) ;

	} /* end if (ok) */

	return rs ;
}
/* end subroutine (lastlogfile_writeinfo) */

int lastlogfile_check(LLF *op,time_t daytime) noex {
	int		rs ;
	if ((rs = lastlogfile_magic(op)) >= 0) {
	    if (op->fd >= 0) {
	        USTAT		sb ;
	        int		f_close = FALSE ;
	        if ((u_fstat(op->fd,&sb) < 0) || (sb.st_mtime > op->mtime)) {
	            f_close = TRUE ;
	        }
	        if (! f_close) {
	            if (daytime <= 0) daytime = time(nullptr) ;
	            if (daytime > (op->otime + LASTLOGFILE_OPENTIME)) {
	                f_close = TRUE ;
	            }
	        }
	        if (f_close) {
	            rs = u_close(op->fd) ;
	            op->fd = -1 ;
	        }
	    /* end if (needed) */
	} /* end if (magic) */
	return rs ;
}
/* end subroutine (lastlogfile_check) */

int lastlogfile_curbegin(LLF *op,LASTLOGFILE_CUR *curp) noex {
	int		rs ;
	if ((rs = lastlogfile_magic(op,curp)) >= 0) {
	    curp->i = -1 ;
	} /* end if (magic) */
	return rs ;
}
/* end subroutine (lastlogfile_curbegin) */

int lastlogfile_curend(LLF *op,LASTLOGFILE_CUR *curp) noex {
	int		rs ;
	if ((rs = lastlogfile_magic(op,curp)) >= 0) {
	    curp->i = -1 ;
	} /* end if (magic) */
	return rs ;
}
/* end subroutine (lastlogfile_curend) */

int lastlogfile_curenum(LLF *op,LASTLOGFILE_CUR *curp,uid_t *up,
		time_t *tp,char *ln,char *hn) noex {
	int		rs ;
	if ((rs = lastlogfile_magic(op,curp)) >= 0) {
	    int		i = (curp->i < 0) ? 0 : (curp->i + 1) ;
	    while (rs >= 0) {
	        if ((rs = lastlogfile_readinfo(op,i,tp,ln,hn)) > 0) break ;
	        i += 1 ;
	    } /* end while */
	    if (rs >= 0) {
	        if (up != nullptr) *up = i ;
	        curp->i = i ;
	    }
	} /* end if (magic) */
	return rs ;
}
/* end subroutine (lastlogfile_curenum) */


/* private subroutines */

static int lastlogfile_checkopen(LLF *op) noex {
	int		rs = SR_OK ;
	if (op->fd < 0) {
	    rs = u_open(op->fname,op->oflags,0660) ;
	    op->fd = rs ;
	    op->otime = time(nullptr) ;
	}
	return (rs >= 0) ? op->fd : rs ;
}
/* end subroutine (lastlogfile_checkopen) */

static int lastlogfile_fileclose(LLF *op) noex {
	int		rs = SR_OK ;
	int		rs1 ;
	if (op->fd >= 0) {
	    rs1 = u_close(op->fd) ;
	    if (rs >= 0) rs = rs1 ;
	    op->fd = -1 ;
	}
	return rs ;
}
/* end subroutine (lastlogfile_fileclose) */


