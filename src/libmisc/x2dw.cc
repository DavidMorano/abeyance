/* dw SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 */

/* directory watch */
/* version %I% last-modified %G% */

#define	CF_FNAMECMP	1		/* ? */

/* revision history:

	= 1998-07-01, David A­D­ Morano
	This subroutine was written for use in the 'rbbpost' daemon
	program.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Object:
	dw

	Description:
	This object is used to watch a directory path for additions
	or changes in the file objects under that path.  Subdirectories
	are allowed.  All files under the directory path (including
	those in subdirectories) are treated the same as an entry.

*******************************************************************************/

#include	<envstandards.h>	/* must be ordered first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/stat.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<climits>
#include	<ctime>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<usystem.h>
#include	<getbufsize.h>
#include	<bufsizevar.hh>
#include	<mallocxx.h>
#include	<vecobj.h>
#include	<vecstr.h>
#include	<fsdir.h>
#include	<sncpyx.h>
#include	<mkpathx.h>
#include	<pathadd.h>
#include	<strwcpy.h>
#include	<strdcpy.h>
#include	<localmisc.h>

#include	"dw.h"


/* local defines */

#define	IENTRY		struct dw_ientry

#define	MAXOPENTIME	300		/* maximum FD cache time */
#define	MINCHECKTIME	2		/* minumun check interval (seconds) */
#define	MAXIDLETIME	240		/* maximum allowable idle time */

#ifndef	CF_FNAMECMP
#define	CF_FNAMECMP	0
#endif


/* imported namespaces */

using std::nullptr_t ;			/* type */
using std::nothrow ;			/* constant */


/* local typedefs */

extern "C" {
    typedef void (*dwcallback_f)(DW_ENT *,int,void *) noex ;
}


/* external subroutines */

extern "C" {
    int dw_callback(DW *,dwcallback_f,void *) noex ;
}


/* external variables */


/* local structure */

namespace {
    struct vars {
	int		maxpathlen ;
	operator int () noex ;
    } ; /* end struct (vars) */
}


/* forward references */

template<typename ... Args>
static int dw_ctor(dw *op,Args ... args) noex {
    	DW		*hop = op ;
	int		rs = SR_FAULT ;
	if (op && (args && ...)) {
	    cnullptr	np{} ;
	    rs = SR_NOMEM ;
	    memclear(hop) ;
	    if ((op->sdp = new(nothrow) vecstr) != np) {
	        if ((op->elp = new(nothrow) vecobj) != np) {
		    rs = SR_OK ;
	        } /* end if (new-vecobj) */
		if (rs < 0) {
		    delete op->sdp ;
		    op->sdp = nullptr ;
		}
	    } /* end if (new-vecstr) */
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (dw_ctor) */

static int dw_dtor(dw *op) noex {
	int		rs = SR_FAULT ;
	if (op) {
	    rs = SR_OK ;
	    if (op->elp) {
		delete op->elp ;
		op->elp = nullptr ;
	    }
	    if (op->sdp) {
		delete op->sdp ;
		op->sdp = nullptr ;
	    }
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (dw_dtor) */

template<typename ... Args>
static inline int dw_magic(dw *op,Args ... args) noex {
	int		rs = SR_FAULT ;
	if (op && (args && ...)) {
	    rs = (op->magic == DW_MAGIC) ? SR_OK : SR_NOTOPEN ;
	}
	return rs ;
}
/* end subroutine (dw_magic) */

static int	dw_scanfull(DW *) noex ;
static int	dw_scansub(DW *,cchar *,time_t) noex ;
static int	dw_scansuber(DW *,cchar *,int,time_t) noex ;
static int	dw_findi(DW *,cchar *,IENTRY **) noex ;

static int	ientry_start(IENTRY *,DW *,cchar *,USTAT *) noex ;
static int	ientry_finish(IENTRY *,DW *) noex ;

static int	entry_load(DW_ENT *,IENTRY *,cchar *) noex ;

extern "C" {
    static int	vcmpfn(cvoid **,cvoid **) noex ;
}


/* local variables */

static vars		var ;

constexpr int		rsn = SR_NOTFOUND ;

constexpr bool		f_fnamecmp = CF_FNAMECMP ;


/* exported variables */


/* exported subroutines */

int dw_start(DW *op,cchar *dirname) noex {
	int		rs ;
	if ((rs = dw_ctor(op,dirname)) >= 0) {
	    rs = SR_INVALID ;
	    if (dirname[0]) {
		static cint	rsv = var ;
		if ((rs = rsv) >= 0) {
	            cint	sz = szof(DW_ENT) ;
	            cint	vn = 10 ;
	            cint	vo = (VECOBJ_OSTATIONARY | VECOBJ_OCONSERVE) ;
	            op->fd = -1 ;
	            op->count_new = 0 ;
	            op->count_checkable = 0 ;
	            op->checkint = DW_INTCHECK ;
	            op->f.subdirs = false ;
                    /* initialize */
	            if ((rs = vecobj_start(op->elp,sz,vn,vo)) >= 0) {
		        auto		mall = uc_mallocstrw ;
	                custime		dt = getustime ;
	                op->timod = 0 ;
	                op->opentime = 0 ;
	                op->checktime = dt ;
	                op->removetime = dt ;
	                if (cchar *cp ; (rs = mall(dirname,-1,&cp)) >= 0) {
	                    if ((rs-1) <= var.maxpathlen) {
	                        op->dirname = cp ;
	                        rs = dw_scanfull(op) ;
	                        if (rs == SR_NOENT) rs = SR_OK ;
				if (rs >= 0) {
	                            op->magic = DW_MAGIC ;
				}
	                    } else {
	                        rs = SR_TOOBIG ;
	                    }
	                    if (rs < 0) {
	                        uc_free(cp) ;
		            }
	                } /* end if (m-a) */
	                if (rs < 0) {
	                    vecobj_finish(op->elp) ;
	                }
	            } /* end if (vecobj-start) */
		} /* end if (vars) */
	    } /* end if (valid) */
	    if (rs < 0) {
		dw_dtor(op) ;
	    }
	} /* end if (dw_ctor) */
	return rs ;
}
/* end subroutine (dw_start) */

int dw_finish(DW *op) noex {
	int		rs ;
	int		rs1 ;
	if ((rs = dw_magic(op)) >= 0) {
	    if (op->elp) {
		vecobj	*elp = op->elp ;
	        void	*vp{} ;
	        for (int i = 0 ; elp->get(i,&vp) >= 0 ; i += 1) {
		    IENTRY	*iep = (IENTRY *) vp ;
	            if (vp) {
	                rs1 = ientry_finish(iep,op) ;
	                if (rs >= 0) rs = rs1 ;
	            }
	        } /* end for */
	        {
	            rs1 = vecobj_finish(op->elp) ;
	            if (rs >= 0) rs = rs1 ;
		}
	    }
	    if (op->dirname) {
	        rs1 = uc_free(op->dirname) ;
	        if (rs >= 0) rs = rs1 ;
	        op->dirname = nullptr ;
	    }
	    if (op->fd >= 0) {
	        rs1 = u_close(op->fd) ;
	        if (rs >= 0) rs = rs1 ;
	        op->fd = -1 ;
	    }
	    if (op->f.subdirs) {
	        op->f.subdirs = false ;
	        rs1 = vecstr_finish(op->sdp) ;
	        if (rs >= 0) rs = rs1 ;
	    } /* end if */
	    {
		rs1 = dw_dtor(op) ;
	        if (rs >= 0) rs = rs1 ;
	    }
	    op->magic = 0 ;
	} /* end if (magic) */
	return rs ;
}
/* end subroutine (dw_finish) */

int dw_curbegin(DW *op,DW_CUR *curp) noex {
    	int		rs ;
	if ((rs = dw_magic(op,curp)) >= 0) {
	    curp->i = -1 ;
	} /* end if (magic) */
	return rs ;
}
/* end subroutine (dw_curbegin) */

int dw_curend(DW *op,DW_CUR *curp) noex {
    	int		rs ;
	if ((rs = dw_magic(op)) >= 0) {
	    curp->i = -1 ;
	} /* end if (magic) */
	return rs ;
}
/* end subroutine (dw_curend) */

int dw_curenum(DW *op,DW_CUR *curp,DW_ENT *dep,char *rbuf,int rlen) noex {
	int		rs ;
	int		nlen = 0 ;
	if ((rs = dw_magic(op,curp)) >= 0) {
	    /* get the next entry (any one) */
	    IENTRY	*iep = nullptr ;
	    int		i ;
	    if ((curp == nullptr) || (curp->i < 0)) {
	        i = 0 ;
	    } else {
	        i = curp->i + 1 ;
	    }
	    void	*vp{} ;
	    while ((rs = vecobj_get(op->elp,i,&vp)) >= 0) {
	        iep = (IENTRY *) vp ;
	        if (vp) break ;
	        i += 1 ;
	    } /* end while */
	    if ((rs >= 0) && iep) {
	        if ((rs >= 0) && dep) {
	            rs = entry_load(dep,iep,rbuf) ;
		    nlen = rs ;
	        }
		if ((rs >= 0) && rbuf) {
		    rs = sncpy(rbuf,rlen,iep->name) ;
		    nlen = rs ;
		}
	        if (rs >= 0) {
	            curp->i = i ;
	        }
	    } /* end if (ok) */
	    if (rs >= 0) {
	        curp->i = i ;
	    }
	} /* end if (magic) */
	return (rs >= 0) ? nlen : rs ;
}
/* end subroutine (dw_curenum) */

/* enumerate those entries that are "checkable" */
int dw_curenumcheck(DW *op,DW_CUR *curp,DW_ENT *dep,char *rbuf,int rlen) noex {
	int		rs ;
	int		i = 0 ;
	if ((rs = dw_magic(op)) >= 0) {
	    IENTRY	*iep = nullptr ; /* used across blocks */
	    /* get the next entry with a checkable file */
	    if ((curp == nullptr) || (curp->i < 0)) {
	        i = 0 ;
	    } else {
	        i = curp->i + 1 ;
	    }
	    void	*vp{} ;
	    while ((rs = vecobj_get(op->elp,i,&vp)) >= 0) {
	        if (vp) {
		    iep = (IENTRY *) vp ;
		    if (iep->state == DW_SCHECK) break ;
	        }
	        i += 1 ;
	    } /* end while */
	    if (rs >= 0) {
	        if (dep && iep) {
	            rs = entry_load(dep,iep,rbuf) ;
	        }
		if ((rs >= 0) && rbuf) {
		    rs = sncpy(rbuf,rlen,iep->name) ;
		}
	        if ((rs >= 0) && curp) {
	            curp->i = i ;
	        }
	    } /* end if */
	} /* end if (magic) */
	return (rs >= 0) ? i : rs ;
}
/* end subroutine (dw_enumcheckable) */

int dw_del(DW *op,DW_CUR *curp) noex {
	int		rs ;
	int		rs1 ;
	if ((rs = dw_magic(op,curp)) >= 0) {
	    void	*vp{} ;
	    if ((rs = vecobj_get(op->elp,curp->i,&vp)) >= 0) {
	        if (vp) {
		    IENTRY	*iep = (IENTRY *) vp ;
		    {
	                rs1 = ientry_finish(iep,op) ;
		        if (rs >= 0) rs = rs1 ;
		    }
		    {
	                rs1 = vecobj_del(op->elp,curp->i) ;
		        if (rs >= 0) rs = rs1 ;
		    }
	        }
	    } /* end if */
	} /* end if (magic) */
	return rs ;
}
/* end subroutine (dw_del) */

int dw_find(DW *op,cchar *name,DW_ENT *dep,char *rbuf,int rlen) noex {
	int		rs ;
	int		i = 0 ;
	if ((rs = dw_magic(op,name)) >= 0) {
	    rs = SR_INVALID ;
	    if (name[0]) {
		vecobj		*elp = op->elp ;
	        IENTRY		ie{} ;
	        IENTRY		*iep = nullptr ;
	        void		*vp{} ;
		if_constexpr (f_fnamecmp) {
	            ie.name = charp(name) ;
	            if ((rs = elp->search(&ie,vcmpfn,&vp)) >= 0) {
	                iep = (IENTRY *) vp ;
	            }
		} else {
	            for (i = 0 ; (rs = elp->get(i,&vp)) >= 0 ; i += 1) {
	                if (vp) {
		            iep = (IENTRY *) vp ;
	                    if (strcmp(name,iep->name) == 0) break ;
	                }
	            } /* end for (looping through entries) */
		} /* end if_constexpr (f_fnamecmp) */
	        if ((rs >= 0) && dep && iep) {
	            rs = entry_load(dep,iep,rbuf) ;
	        }
		if ((rs >= 0) && rbuf) {
		    rs = sncpy(rbuf,rlen,iep->name) ;
		}
	    } /* end if (valid) */
	} /* end if (magic) */
	return (rs >= 0) ? i : rs ;
}
/* end subroutine (dw_find) */

/* check if the directory (and any subdirectories) has changed */
int dw_check(DW *op,time_t dt) noex {
	USTAT sb{} ; 
	int		rs = SR_OK ;
	int		i ;
	int		n = 0 ;

	if (op == nullptr) return SR_FAULT ;

	if (op->magic != DW_MAGIC) return SR_NOTOPEN ;

	if (dt <= 0) dt = getustime ;

/* should we even check? */

	if ((dt - op->checktime) <= MINCHECKTIME)
	    goto ret0 ;

/* perform the directory time check */

	if (op->fd < 0) {

	    rs = u_open(op->dirname,O_RDONLY,0666) ;
	    op->fd = rs ;
	    if (rs >= 0) {
	        op->opentime = dt ;
	        rs = uc_closeonexec(op->fd,true) ;
	    }

	} /* end if (opened FD for caching) */
	if (rs < 0) goto ret0 ;

	if ((rs = u_fstat(op->fd,&sb)) < 0) {
	    u_close(op->fd) ;
	    op->fd = -1 ;
	    goto done ;
	}

	if ((sb.st_mtime > op->timod) ||
	    ((dt - op->checktime) > MAXIDLETIME)) {

	    op->timod = sb.st_mtime ;
	    rs = dw_scansub(op,"",dt) ;
	    if (rs >= 0) n = rs ;

	} else if ((dt - op->opentime) > MAXOPENTIME) {

	    u_close(op->fd) ;
	    op->fd = -1 ;

	} /* end if */

/* OK, look through the subdirectories and see if any of them need scanning */

	if (op->f.subdirs) {
	    cchar	*dnp ;
	    char	dnamebuf[MAXPATHLEN + 1], *dbp ;


	    dbp = dnamebuf ;
	    dbp = strwcpy(dbp,op->dirname,-1) ;

	    *dbp++ = '/' ;
	    for (i = 0 ; vecstr_get(op->sdp,i,&dnp) >= 0 ; i += 1) {
	        if (dnp != nullptr) {

	        {
	            int	rl = (MAXPATHLEN - (dbp-dnamebuf)) ;
	            strdcpy1(dbp,rl,dnp) ;
	        }

	        if ((u_stat(dnamebuf,&sb) >= 0) &&
	            ((sb.st_mtime > op->checktime) ||
	            ((dt - op->checktime) > MAXIDLETIME))) {

	                rs = dw_scansub(op,dnp,dt) ;
	                if (rs >= 0) n += 1 ;

	            } /* end if (scanning subdirectory) */

		}
	        if (rs < 0) break ;
	    } /* end for */

	} /* end if (subdirectories) */

/* OK, now check all files that are 'NEW' and see if they are older! */

	if ((rs >= 0) && (op->count_new > 0)) {
	    char	dnamebuf[MAXPATHLEN + 1], *dbp ;

	    dbp = dnamebuf ;
	    dbp = strwcpy(dbp,op->dirname,-1) ;

	    *dbp++ = '/' ;
	    void	*vp{} ;
	    for (i = 0 ; vecobj_get(op->elp,i,&vp) >= 0 ; i += 1) {
	        if (vp) {
		    IENTRY	*iep = (IENTRY *) vp ;
	            if (iep->state == DW_SNEW) {
	                if ((dt - iep->itime) > (op->checkint / 4)) {
	                    {
	                        cint	rl = (MAXPATHLEN - (dbp-dnamebuf)) ;
	                        strdcpy1(dbp,rl,iep->name) ;
	                    }
	                    if ((u_stat(dnamebuf,&sb) >= 0) &&
	                        ((dt - sb.st_mtime) > op->checkint)) {

	                        iep->state = DW_SCHECK ;
	                        op->count_new -= 1 ;
	                        op->count_checkable += 1 ;
	                        n += 1 ;

	                    } /* end if */
	                } /* end if (checkint) */
		    } /* end if (equal) */
		} /* end if (non-null) */
	    } /* end for */

	} /* end if */

/* OK, we are on a roll now!, check for files that have been removed! */

	if ((rs >= 0) && ((dt - op->removetime) > MAXIDLETIME) &&
	    (vecobj_count(op->elp) > 0)) {

	    char	dnamebuf[MAXPATHLEN + 1], *dbp ;

	    op->removetime = dt ;
	    dbp = dnamebuf ;
	    dbp = strwcpy(dbp,op->dirname,-1) ;

	    *dbp++ = '/' ;
	    void	*vp{} ;
	    for (i = 0 ; vecobj_get(op->elp,i,&vp) >= 0 ; i += 1) {
		if (vp) {
		    IENTRY	*iep = (IENTRY *) vp ;
	            if ((dt - iep->itime) >= MAXIDLETIME) {
	                iep->itime = dt ;
	                {
	                    cint	rl = (MAXPATHLEN - (dbp-dnamebuf)) ;
	                    strdcpy1(dbp,rl,iep->name) ;
	                }
	                if (u_stat(dnamebuf,&sb) < 0) {
	                    ientry_finish(iep,op) ;
	                    vecobj_del(op->elp,i--) ;
	                } /* end if (could not 'stat') */
		    } /* end if (got time-out) */
		} /* end if (non-null) */
	    } /* end for */

	} /* end if (checking for removed files) */

done:
	op->checktime = dt ;

ret0:
	return (rs >= 0) ? n : rs ;
}
/* end subroutine (dw_check) */

int dw_callback(DW *op,dwcallback_f func,void *argp) noex {
    	int		rs ;
	if ((rs = dw_magic(op)) >= 0) {
	    op->callback = func ;
	    op->argp = argp ;
	} /* end if (magic) */
	return rs ;
}
/* end subroutine (dw_callback) */

extern int dw_state(DW *op,int i,int state) noex {
	int		rs ;
	int		state_prev = 0 ;
	if ((rs = dw_magic(op)) >= 0) {
	    rs = SR_INVALID ;
	    if (state >= 0) {
	        void	*vp{} ;
	        if ((rs = vecobj_get(op->elp,i,&vp)) >= 0) {
	            IENTRY	*iep = (IENTRY *) vp ;
	            state_prev = iep->state ;
	            iep->state = state ;
	        }
	    } /* end if (valid) */
	} /* end if (magic) */
	return (rs >= 0) ? state_prev : rs ;
}
/* end subroutine (dw_state) */


/* private subroutines */

static int dw_scanfull(DW *op) noex {
	USTAT		sb ;
	IENTRY		ie ;
	IENTRY		*iep ;
	fsdir		d ;
	fsdir_ent	ds ;
	time_t		dt = getustime ;
	int		rs ;
	int		rs1 ;
	int		n = 0 ;
	char		dnamebuf[MAXPATHLEN + 1], *dbp ;

	if (op->dirname == nullptr) return SR_FAULT ;

	if (op->dirname[0] == '\0') return SR_INVALID ;

/* "do" the outer directory */

	if (char *nbuf{} ; (rs = malloc_mn(&nbuf)) >= 0) {
	    cint	nlen = 0 ;
	if ((rs = fsdir_open(&d,op->dirname)) >= 0) {
	    dbp = dnamebuf ;
	    dbp = strwcpy(dbp,op->dirname,-1) ;

	    *dbp++ = '/' ;
	    while ((rs = fsdir_read(&d,&ds,nbuf,nlen)) > 0) {
	    cint	nl = rs ;
	        if (ds.name[0] == '.') continue ;

	        {
	            int	rl = (MAXPATHLEN - (dbp-dnamebuf)) ;
	            strdcpy1(dbp,rl,ds.name) ;
	        }

	        if (u_stat(dnamebuf,&sb) < 0) continue ;

	        if (S_ISDIR(sb.st_mode)) {

	            if (! op->f.subdirs) {
			cint	vo = VECSTR_OCOMPACT ;
	                rs = vecstr_start(op->sdp,10,vo) ;
	                op->f.subdirs = (rs >= 0) ;
	            }

	            if (rs >= 0) {
			vecstr	*slp = op->sdp ;
	                if (vecstr_find(slp,dbp) == rsn) {
	                    rs = vecstr_add(slp,dbp,nl) ;
			}
	            }

	        } else if (dw_findi(op,dbp,&iep) < 0) {

	            op->count_new += 1 ;
	            ientry_start(&ie,op,dbp,&sb) ;

	            rs = vecobj_add(op->elp,&ie) ;

	        } else if ((iep->state == DW_SNEW) &&
	            ((dt - sb.st_mtime) > op->checkint)) {

	            iep->state = DW_SCHECK ;
	            op->count_new -= 1 ;
	            op->count_checkable += 1 ;
	            n += 1 ;

	        } /* end if */

	    } /* end while (reading directory entries) */

	    rs1 = fsdir_close(&d) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (outer directory) */
	    rs1 = uc_free(nbuf) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (m-a-f) */

/* do the subdirectories */

	if ((rs >= 0) && op->f.subdirs) {
	    cchar	*dnp ;
	    for (int i = 0 ; vecstr_get(op->sdp,i,&dnp) >= 0 ; i += 1) {
	        if (dnp) {
	            rs = dw_scansub(op,dnp,dt) ;
	            n += rs ;
	        }
	        if (rs < 0) break ;
	    } /* end for */
	} /* end if (subdirectories) */

	return (rs >= 0) ? n : rs ;
}
/* end subroutine (dw_scanfull) */

static int dw_scansub(DW *op,cchar *subdname,time_t dt) noex {
	int		rs ;
	int		n = 0 ;
	if ((rs = dw_magic(op)) >= 0) {
	    if (char *dbuf ; (rs = malloc_mp(&dbuf)) >= 0) {
		char	*dbp = dbuf ;
		char	*sdbp ;
	        /* put it together */
	        dbp = strwcpy(dbp,op->dirname,-1) ;
	        *dbp++ = '/' ;
	        {
	            sdbp = dbp ;
	            if ((subdname != nullptr) && (subdname[0] != '\0')) {
	                sdbp = strwcpy(sdbp,subdname,-1) ;
	                *sdbp++ = '/' ;
	            }
	            *sdbp = '\0' ;
	        }
                /* "do" the subdirectory */
		if ((rs = dw_scansuber(op,dbuf,(sdbp - dbuf),dt)) >= 0) {
		    n = rs ;
		}
	        rs = rsfree(rs,dbuf) ;
	    } /* end if (m-a-f) */
	} /* end if (magic) */
	return (rs >= 0) ? n : rs ;
}
/* end subroutine (dw_scansub) */

/* "do" the subdirectory */
static int dw_scansuber(DW *op,cchar *dbuf,int dl,time_t dt) noex {
    	int		rs ;
	int		rs1 ;
	int		n = 0 ;
	if (char *nbuf{} ; (rs = malloc_mn(&nbuf)) >= 0) {
	    cint	nlen = 0 ;
	    if (fsdir d ; (rs = fsdir_open(&d,dbuf)) >= 0) {
	        fsdir_ent	ds ;
	        cint		rsn = SR_NOENT ;
		while ((rs = fsdir_read(&d,&ds,nbuf,nlen)) > 0) {
		    if (ds.name[0] != '.') {
			if ((rs = pathadd(dbuf,dl,ds.name)) >= 0) {
                        USTAT       sb ;
                        IENTRY      ie, *iep ;
                        int         dlen ;
                        cint        nl = rs ;
                        if (u_stat(dbuf,&sb) < 0) continue ;
                        if (S_ISDIR(sb.st_mode)) {
                            vecstr  *slp = op->sdp ;
                            if (! op->f.subdirs) {
                                cint        vo = VECSTR_OCOMPACT ;
                                rs = vecstr_start(op->sdp,10,vo) ;
                                op->f.subdirs = (rs >= 0) ;
                            }
                            if (rs >= 0) {
                                if ((rs = vecstr_find(slp,dbp)) == rsn) {
                                    rs = vecstr_add(slp,dbp,dlen) ;
                                }
                            }
                        } else if ((rs = dw_findi(op,dbp,&iep)) == rsn) {
                            op->count_new += 1 ;
                            ientry_start(&ie,op,dbp,&sb) ;
                            rs = vecobj_add(op->elp,&ie) ;
                        } else if (iep->state == DW_SNEW) {
                            iep->itime = dt ;
                            if ((dt - sb.st_mtime) > op->checkint) {
                                iep->state = DW_SCHECK ;
                                op->count_new -= 1 ;
                                op->count_checkable += 1 ;
                                n += 1 ;
                            } /* end if */
                        } else {
                            iep->itime = dt ;
                        }
			} else if (rs == SR_OVERFLOW) {
			    rs = SR_OK ;
			}
		    } /* end if (non-dot) */
	    	} /* end while (reading directory entries) */
		rs1 = fsdir_close(&d) ;
		if (rs >= 0) rs = rs1 ;
	    } /* end if (fsdir) */
	    rs1 = uc_free(nbuf) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (m-a-f) */
	return (rs >= 0) ? n : rs ;
}
/* end subroutine (dw_scansuber) */

#ifdef	COMMENT

static int dw_finddelete(DW *op,cchar *name) noex {
	int		rs ;
	int		i = 0 ;
	IENTRY		ie ;
	IENTRY		*iep ;
	ie.name = name ;
	if ((rs = vecobj_search(op->elp,&ie,vcmpfn,&iep)) >= 0) {
	    i = rs ;
	    rs = vecobj_del(op->elp,i) ;
	}
	return (rs >= 0) ? i : rs ;
}
/* end subroutine (dw_finddelete) */

#endif /* COMMENT */

static int dw_findi(DW *op,cchar *name,IENTRY **iepp) noex {
	int		rs ;
	IENTRY		ie ;
	ie.name = charp(name) ;
	void		*vp{} ;
	if ((rs = vecobj_search(op->elp,&ie,vcmpfn,&vp)) >= 0) {
	    IENTRY	*iep = (IENTRY *) vp ;
	    *iepp = iep ;
	}
	return rs ;
}
/* end subroutine (dw_findi) */

/* initialize an entry */
static int ientry_start(IENTRY *iep,DW *op,cchar *name,USTAT *sbp) noex {
	int		rs ;
	iep->state = DW_SNEW ;
	if (cchar *cp ; (rs = uc_mallocstrw(name,-1,&cp)) >= 0) {
	    iep->name = cp ;
	    /* do we need to get some status on the file? */
	    if (sbp == nullptr) {
		if (char *dbuf ; (rs = malloc_mp(&dbuf)) >= 0) {
	            if ((rs = mkpath(dbuf,op->dirname,name)) >= 0) {
		        if (USTAT sb ; (rs = u_stat(dbuf,&sb)) >= 0) {
	                    sbp = &sb ;
		        }
	            }
		    rs = rsfree(rs,dbuf) ;
		} /* end if (m-a-f) */
	    } /* end if (non-null) */
	    iep->itime = ((sbp) ? sbp->st_mtime : 0) ;
	} /* end if (memory-allocation) */
	return rs ;
}
/* end subroutine (ientry_start) */

static int ientry_finish(IENTRY *iep,DW *op) noex {
	int		rs = SR_OK ;
	int		rs1 ;
	if (iep->state == DW_SNEW) {
	    op->count_new -= 1 ;
	} else if (iep->state == DW_SCHECK) {
	    op->count_checkable -= 1 ;
	}
	if (iep->name) {
	    rs1 = uc_free(iep->name) ;
	    if (rs >= 0) rs = rs1 ;
	    iep->name = nullptr ;
	}
	return rs ;
}
/* end subroutine (ientry_finish) */

static int entry_load(DW_ENT *dep,IENTRY *iep,cchar *rbuf) noex {
	int		rs = SR_FAULT ;
	if (dep && iep) {
	    rs = SR_OK ;
	    dep->itime = iep->itime ;
	    dep->timod = iep->timod ;
	    dep->fsize = iep->fsize ;
	    dep->state = iep->state ;
	    dep->name = rbuf ;
	    if (rbuf) {
		rs = cstrlen(rbuf) ;
	    }
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (entry_load) */

vars::operator int () noex {
    	int		rs ;
	if ((rs = getbufsize(getbufsize_mp)) >= 0) {
	    maxpathlen = rs ;
	} /* end if (getbufsize) */
    	return rs ;
}
/* end method (vars::operator) */

static int vcmpfn(cvoid **v1pp,cvoid **v2pp) noex {
	IENTRY		**e1pp = (IENTRY **) v1pp ;
	IENTRY		**e2pp = (IENTRY **) v2pp ;
	int		rc = 0 ;
	{
	    IENTRY	*e1p = *e1pp ;
	    IENTRY	*e2p = *e2pp ;
	    if (e1p || e2p) {
	        if (e1p) {
	            if (e2p) {
	                rc = strcmp(e1p->name,e2p->name) ;
	            } else {
	                rc = -1 ;
		    }
	        } else {
	            rc = +1 ;
	        }
	    }
	} /* end block */
	return rc ;
}
/* end subroutine (vcmpfn) */


