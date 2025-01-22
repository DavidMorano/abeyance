/* nodesfile SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 */

/* read (process) a standard UNIX® "nodes" file */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	nodesfile

	Description:
	This little object supports reading the cluster 'nodes'
	file by mapping it into memory.  No data is copied out of
	the file map!  This is assumed to provide some performance
	advantage over reading it line by line and then allocating
	space for found strings.  Duplicate node entries are ignored.

	File-format:
	|
	| <node0>
	| <node1> <node2> <node2>
	| <node4>
	| 

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>		/* |caddr_t| */
#include	<sys/stat.h>
#include	<sys/mman.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<climits>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>		/* |strlen(3c)| */
#include	<ctime>			/* |time(2)| */
#include	<algorithm>		/* |min(3c++)| + |max(3c++)| */
#include	<usystem.h>
#include	<estrings.h>
#include	<sfx.h>
#include	<hdb.h>
#include	<strwcpy.h>
#include	<intceil.h>
#include	<localmisc.h>

#include	"nodesfile.h"


/* local defines */

#define	NF		nodesfile
#define	NF_CUR		nodesfile_cur
#define	NF_DEFNODES	200

#define	TO_CHECK	4
#define	TO_HOLD		2


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
static inline int nodesfile_ctor(nodesfile *op,Args ... args) noex {
    	NODESFILE	*hop = op ;
	int		rs = SR_FAULT ;
	if (op && (args && ...)) {
	    memclear(hop) ;
	    rs = SR_NOMEM ;
	    if ((op->nlp = new(nothrow) hdb) != nullptr) {
		rs = SR_OK ;
	    } /* end if (new-hdb) */
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (nodesfile_ctor) */

static int nodesfile_dtor(nodesfile *op) noex {
	int		rs = SR_FAULT ;
	if (op) {
	    rs = SR_OK ;
	    if (op->nlp) {
		delete op->nlp ;
		op->nlp = nullptr ;
	    }
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (nodesfile_dtor) */

static int	nodesfile_opens(NF *,cchar *) noex ;
static int	nodesfile_opener(NF *) noex ;
static int	nodesfile_parse(NF *) noex ;
static int	nodesfile_filechanged(NF *,time_t) noex ;
static int	nodesfile_filemapbegin(NF *) noex ;
static int	nodesfile_filemapend(NF *) noex ;

static int	hdb_release(hdb *) noex ;


/* local variables */


/* exported variables */


/* exported subroutines */

int nodesfile_open(NF *op,cchar *fname,int maxsize) noex {
	int		rs ;
	if ((rs = nodesfile_ctor(op,fname)) >= 0) {
	    rs = SR_INVALID ;
	    if (fname[0] && (maxsize > 0)) {
		if ((rs = ucpagesize) >= 0) {
		    op->pagesize = rs ;
		    op->maxsize = maxsize ;
		    rs = nodesfile_opens(op,fname) ;
		} /* end if (ucpagesize) */
	    } /* end if (valid) */
	    if (rs < 0) {
		nodesfile_dtor(op) ;
	    }
	} /* end if (nodesfile_ctor) */
	return rs ;
}
/* end subroutine (nodesfile_open) */

int nodesfile_close(NF *op) noex {
	int		rs = SR_FAULT ;
	int		rs1 ;
	if (op) {
	    rs = SR_OK ;
	    if (op->nlp) {
		rs1 = hdb_finish(op->nlp) ;
		if (rs >= 0) rs = rs1 ;
	    }
	    if (op->mapbuf) {
		rs1 = nodesfile_filemapend(op) ;
	        if (rs >= 0) rs = rs1 ;
	    }
	    if (op->fi.fname) {
	        rs1 = uc_free(op->fi.fname) ;
	        if (rs >= 0) rs = rs1 ;
	        op->fi.fname = nullptr ;
	    }
	    {
		rs1 = nodesfile_dtor(op) ;
		if (rs >= 0) rs = rs1 ;
	    }
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (nodesfile_close) */

int nodesfile_check(NF *op,time_t dt) noex {
	int		rs = SR_FAULT ;
	int		f_changed = false ;
	if (op) {
	    rs = SR_OK ;
	    if (dt == 0) dt = getustime ;
	    if ((dt - op->ti_check) >= TO_CHECK) {
	        op->ti_check = dt ;
	        if ((rs = nodesfile_filechanged(op,dt)) >= 0) {
	            f_changed = true ;
	            hdb_release(op->nlp) ;
	            if ((rs = nodesfile_parse(op)) >= 0) {
	                op->ti_load = dt ;
		    }
	        } /* end if */
	    } /* end if (timeout) */
	} /* end if (non-null) */
	return (rs >= 0) ? f_changed : rs ;
}
/* end subroutine (nodesfile_check) */

int nodesfile_search(NF *op,cchar *nodep,int nodel) noex {
	int		rs = SR_FAULT ;
	if (op) {
	    rs = SR_NOTOPEN ;
	    if (op->mapbuf) {
	        hdb_datum	key ;
	        hdb_datum	val{} ;
	        if (nodel < 0) nodel = strlen(nodep) ;
	        key.buf = nodep ;
	        key.len = nodel ;
	        rs = hdb_fetch(op->nlp,key,nullptr,&val) ;
	    } /* end if (non-null) */
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (nodesfile_search) */

int nodesfile_curbegin(NF *op,NF_CUR *curp) noex {
	int		rs = SR_FAULT ;
	if (op && curp) {
	    cint	sz = szof(hdb_cur) ;
	    if ((void *vp ; (rs = uc_malloc(sz,&vp)) >= 0) {
		curp->hcp = (hdb_cur *) vp ;
	        rs = hdb_curbegin(op->nlp,curp->hcp) ;
		if (rs < 0) {
		    uc_free(curp->hcp) ;
		    curp->hcp = nullptr ;
		}
	    } /* end if (m-a) */
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (nodesfile_curbegin) */

int nodesfile_curend(NF *op,NF_CUR *curp) noex {
	int		rs = SR_FAULT ;
	int		rs1 ;
	if (op && curp) {
	    rs = SR_OK ;
	    if (curp->hcp) {
		{
	            rs1 = hdb_curend(op->nlp,curp->hcp) ;
		    if (rs >= 0) rs = rs1 ;
	        }
	        {
		    rs1 = uc_free(curp->hcp) ;
		    if (rs >= 0) rs = rs1 ;
		    curp->hcp = nullptr ;
	        }
	    } /* end if (non-null cursor) */
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (nodesfile_curend) */

int nodesfile_curenum(NF *op,NF_CUR *curp,char *rbuf,int rlen) noex {
	int		rs = SR_FAULT ;
	int		cl = 0 ;
	if (op && curp) {
	    hdb_datum	key{} ;
	    hdb_datum	val{} ;
	    if ((rs = hdb_curenum(op->nlp,curp->hcp,&key,&val)) >= 0) {
		cint	cl = key.len ;
	        cchar	*cp = charp(key.buf) ;
		rs = sncpyw(rbuf,rlen,cp,cl) ;
	    }
	} /* end if (non-null) */
	return (rs >= 0) ? cl : rs ;
}
/* end subroutine (nodesfile_curenum) */


/* private subroutines */

static int nodesfile_opens(NF *op,cc *fn) noex {
    	cint		of = O_RDONLY ;
    	int		rs ;
	int		rs1 ;
	if ((rs = uc_open(fn,of,0)) >= 0) {
	    cint	fd = rs ;
	    if (USTAT sb ; (rs = uc_fstat(fd,&sb)) >= 0) {
		rs = SR_PROTO ;
		if (S_ISREG(sb.st_mode)) {
		    rs = SR_TOOBIG ;
		    if (sb.st_size < op->maxsize) {
			op->fi.oflags = of ;
			if (cc *cp{} ; (rs = uc_mallocstrw(fn,-1,&cp)) >= 0) {
			    op->fi.fname = cp ;
			    op->fi.timod = sb.st_mtime ;
			    op->fi.ino = sb.st_ino ;
			    op->fi.dev = sb.st_dev ;
			    op->filesize = sb.st_size ;
			    rs = nodesfile_opener(op) ;
			    if (rs < 0) {
			        uc_free(op->fi.fname) ;
			        op->fi.fname = nullptr ;
			    }
			} /* end if (m-a) */
		    } /* end if (size OK) */
		} /* end if (type-of-file) */
	    } /* end if (stat-file) */
	    rs1 = uc_close(fd) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (open-file) */
	return rs ;
}
/* end subroutine (nodesfile_opens) */

static int nodesfile_opener(nodesfile *op) noex {
	cnullptr	np{} ;
	int		rs ;
	if ((rs = nodesfile_filemapbegin(op)) >= 0) {
	    cint	ne = NF_DEFNODES ;
	    if ((rs = hdb_start(op->nlp,ne,0,np,np)) >= 0) {
		rs = nodesfile_parse(op) ;
		if (rs < 0) {
		    hdb_finish(op->nlp) ;
		}
	    } /* end if (hdb) */
	    if (rs < 0) {
		nodesfile_filemapend(op) ;
	    }
	} /* end if (map-file) */
	return rs ;
}
/* end subroutine (nodesfile_opener) */

static int nodesfile_parse(NF *op) noex {
	hdb_datum	key ;
	hdb_datum	value ;
	int		rs = SR_OK ;
	int		n = 0 ;
	int		sl = int(op->filesize) ;
	int		cl ;
	cchar		*sp = op->mapbuf ;
	cchar		*cp ;
	cchar		*ep ;
	value.buf = nullptr ;
	value.len = 0 ;
	ep = (sp + sl) ;
	while (sp < ep) {
	    while ((cl = sfnext(sp,sl,&cp)) > 0) {
	        if (cp[0] == '#') {
	            while ((cp < ep) && (*cp != '\n')) {
	                cp += 1 ;
		    }
	            sl -= (cp - sp) ;
	            sp = cp ;
	        } else {
	            sl -= ((cp + cl) - sp) ;
	            sp = (cp + cl) ;
		    /* remove trailing comments */
		    for (int i = 0 ; i < cl ; i += 1) {
			if (cp[i] == '#') {
			    cl = i ;
			    break ;
			}
		    } /* end for */
		    /* store it */
	            key.buf = cp ;
	            key.len = cl ;
	            rs = hdb_store(op->nlp,key,value) ;
	            n += 1 ;
	        } /* end if */
	        if (rs < 0) break ;
	    } /* end while (fields) */
	    cp = sp ;
	    while ((cp < ep) && (*cp != '\n')) {
	        cp += 1 ;
	    }
	    if ((cp < ep) && (*cp == '\n')) {
	        cp += 1 ;
	    }
	    sl -= (cp - sp) ;
	    sp = cp ;
	    if (rs < 0) break ;
	} /* end while (reading lines) */
	return (rs >= 0) ? n : rs ;
}
/* end subroutine (nodesfile_parse) */

static int nodesfile_filechanged(NF *op,time_t daytime) noex {
	int		rs ;
	int		f = false ;
	if (USTAT sb ; (rs = uc_stat(op->fi.fname,&sb)) >= 0) {
	    cuint	fsz = uint(sb.st_size) ;
	    f = (op->fi.timod > sb.st_mtime) ;
	    f = f || (op->fi.ino != sb.st_ino) ;
	    f = f || (op->fi.dev != sb.st_dev) ;
	    if (f) {
	        f = f && ((daytime - op->fi.timod) >= TO_HOLD) ;
	    }
	    if (f) {
	        op->filesize = fsz ;
	        op->fi.timod = sb.st_mtime ;
	        op->fi.ino = sb.st_ino ;
	        op->fi.dev = sb.st_dev ;
	        if (fsz > op->mapsize) {
	            if ((rs = nodesfile_filemapend(op)) >= 0) {
	                rs = nodesfile_filemapbegin(op) ;
		    }
	        }
	    } /* end if (file changed) */
	} /* end if (uc_stat) */
	return (rs >= 0) ? f : rs ;
}
/* end subroutine (nodesfile_filechanged) */

static int nodesfile_filemapbegin(NF *op) noex {
	cnullptr	np{} ;
	int		rs ;
	int		rs1 ;
	cint		of = op->fi.oflags ;
	cchar		*fn = op->fi.fname ;
	if ((rs = uc_open(fn,of,0666)) >= 0) {
	    cint	fd = rs ;
	    if (USTAT sb ; (rs = uc_fstat(fd,&sb)) >= 0) {
		cuint	fsz = uint(sb.st_size) ;
		cuint	msz = uceil(uint(sb.st_size),op->pagesize) ;
		op->filesize = fsz ;
	        rs = SR_TOOBIG ;
	        if (fsz <= op->maxsize) {
	            csize	ms = size_t(msz) ;
	            cint	mp = PROT_READ ;
	            cint	mf = MAP_SHARED ;
	            void	*ma{} ; 
		    if ((rs = u_mmapbegin(np,ms,mp,mf,fd,0z,&ma)) >= 0) {
		        op->mapbuf = charp(ma) ;
		        op->mapsize = uint(ms) ;
	            }
	        } /* end if (file-size) */
	    } /* end if (stat) */
	    rs1 = uc_close(fd) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (file-open) */
	return rs ;
}
/* end subroutine (nodesfile_filemapbegin) */

static int nodesfile_filemapend(NF *op) noex {
	int		rs = SR_OK ;
	int		rs1 ;
	if (op->mapbuf) {
	    caddr_t	ma = caddr_t(op->mapbuf) ;
	    csize	ms = size_t(op->mapsize) ;
	    rs1 = u_mmapend(ma,ms) ;
	    if (rs >= 0) rs = rs1 ;
	    op->mapbuf = nullptr ;
	    op->mapsize = 0 ;
	}
	return rs ;
}
/* end subroutine (nodesfile_filemapend) */

static int hdb_release(hdb *hsp) noex {
	int		rs = SR_FAULT ;
	if (hsp) {
	    if (hdb_cur cur{} ; (rs = hdb_curbegin(hsp,&cur)) >= 0) {
	        while (hdb_curenum(hsp,&cur,nullptr,nullptr) >= 0) {
	            hdb_curdel(hsp,&cur,0) ;
	        }
	        hdb_curend(hsp,&cur) ;
	    } /* end if (cursor) */
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (hdb_release) */


