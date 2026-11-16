/* strfilemks SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* make a STRFILE database */
/* version %I% last-modified %G% */

#define	CF_FIRSTHASH	0		/* arrange for first-attempt hashing */
#define	CF_MINMOD	1		/* ensure minimum file mode */
#define	CF_LATE		0		/* late open */

/* revision history:

	= 1998-03-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	strfilemks

	Description:
	This subroutine creates a STRFILE database file.

	Synopsis:
	int strfilemks_open(strfilemks *op,cc *dbn,int of,mode_t om,int n) noex

	Arguments:
	op		object pointer
	dbn		name of (path-to) DB
	of		open-flags
	om		open-mode
	n		starting estimate of numbers of variables

	Returns:
	>=0		OK
	<0		error code

	Notes:

	= possible returns to an open attempt
	- OK (creating)
	- already exists
	- doesn't exist but is in progress
	- exists and is in progress

	= open-flags

			if DB exits	if NDB exists	returns
	___________________________________________________________________

	-		no		no		SR_OK (created)
	-		no		yes		SR_INPROGRESS
	-		yes		no		SR_OK
	-		yes		yes		SR_INPROGRESS

	O_CREAT|O_EXCL	no		no		SR_OK (created)
	O_CREAT|O_EXCL	no		yes		SR_INPROGRESS
	O_CREAT|O_EXCL	yes		no		SR_EXIST
	O_CREAT|O_EXCL	yes		yes		SR_INPROGRESS

	O_CREAT		x		x		SR_OK (created)

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/param.h>		/* POSIX® */
#include	<sys/stat.h>		/* POSIX® */
#include	<unistd.h>		/* POSIX® */
#include	<fcntl.h>		/* POSIX® */
#include	<ctime>			/* CSTD */
#include	<climits>		/* CSTD |INT_MAX| */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstring>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<nulstr.h>		/* LIBU */
#include	<intsat.h>		/* LIBU */
#include	<ucmem.h>		/* LIBUC */
#include	<vecobj.h>		/* LIBUC */
#include	<strtab.h>		/* LIBUC */
#include	<filer.h>		/* LIBUC */
#include	<opentmp.h>		/* LIBUC */
#include	<hash.h>		/* LIBUC */
#include	<sncpyx.h>		/* LIBUC */
#include	<mkpath.h>		/* LIBUC */
#include	<sfx.h>			/* LIBUC */
#include	<strn.h>		/* LIBUC */
#include	<strwcpy.h>		/* LIBUC */
#include	<endian.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */

#include	"strfilemks.h"
#include	"strlisthdr.h"

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |memclear(3u)| */

/* local defines */

#define	SFM		strfilemks
#define	SFM_OBJ		strfilemks_obj
#define	SFM_SIZEMULT	4
#define	SFM_NSKIP	5
#define	SFM_INDPERMS	0664
#define	SFM_FSUF	STRLISTHDR_FSUF

#define	RM		recmgr
#define	RM_ENT		recmgr_ent

#define	MAPFILE		mapfile

#undef	RECTAB
#define	RECTAB		rectab

#ifndef	KEYBUFLEN
#define	KEYBUFLEN	120
#endif

#define	BUFLEN		(szof(STRLISTHDR) + 128)

#define	FSUF_IND	STRLISTHDR_FSUF

#define	TO_OLDFILE	(5 * 60)

#define	MODP2(v,n)	((v) & ((n) - 1))

#define	DEBFNAME	"strfilemks.deb"

#ifndef	CF_FIRSTHASH
#define	CF_FIRSTHASH	0		/* arrange for first-attempt hashing */
#endif
#ifndef	CF_MINMOD
#define	CF_MINMOD	1		/* ensure minimum file mode */
#endif
#ifndef	CF_LATE
#define	CF_LATE		0		/* late open */
#endif


/* imported namespaces */

using libuc::mem ;			/* variable */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */

struct recmgr {
	vecobj		recs ;
	int		bso ;		/* base string-offiset */
	int		so ;		/* string-offset */
} ; /* end struct */

struct recmgr_ent {
	int		si ;
	int		sl ;
} ; /* end struct */

struct idx_fl {
	uint		fb:1 ;
} ; /* end struct */

struct idx {
	cchar		*idname ;	/* idx dir-name */
	cchar		*ibname ;	/* idx base-name */
	cchar		*nfname ;	/* new idx file-name */
	cchar		*ai ;
	strlisthdr	hdr ;
	idx_fl		fl ;
	filer		fb ;
	int		fd ;
	uint		fo ;
} ; /* end struct */

struct mapfile {
	voidp		mdata ;
	size_t		msize ;
} ; /* end struct */

struct strentry {
	uint		khash ;
	uint		ri ;
	uint		ki ;
	uint		hi ;
} ; /* end struct */


/* forward references */

local int	strfilemks_recbegin(SFM *) noex ;
local int	strfilemks_recend(SFM *) noex ;

local int	strfilemks_idxbegin(SFM *,cchar *) noex ;
local int	strfilemks_idxend(SFM *) noex ;

local int	strfilemks_filesbegin(SFM *) noex ;
local int	strfilemks_filesend(SFM *,int) noex ;

local int	strfilemks_listbegin(SFM *,int) noex ;
local int	strfilemks_listend(SFM *) noex ;

local int	strfilemks_nfcreate(SFM *,cchar *) noex ;
local int	strfilemks_nfcreatecheck(SFM *,
			cchar *,cchar *) noex ;
local int	strfilemks_nfdestroy(SFM *) noex ;
local int	strfilemks_nfstore(SFM *,cchar *) noex ;
local int	strfilemks_fexists(SFM *) noex ;

local int	strfilemks_addfiler(SFM *,MAPFILE *) noex ;

local int	strfilemks_mkvarfile(SFM *) noex ;
local int	strfilemks_wrvarfile(SFM *) noex ;
local int	strfilemks_mkind(SFM *,cchar *,uint (*)[3],int) noex ;
local int	strfilemks_renamefiles(SFM *) noex ;

local int	rectab_start	(RECTAB *,int) noex ;
local int	rectab_add	(RECTAB *,uint,uint) noex ;
local int	rectab_done	(RECTAB *) noex ;
local int	rectab_getvec	(RECTAB *,uint (**)[2]) noex ;
local int	rectab_extend	(RECTAB *) noex ;
local int	rectab_finish	(RECTAB *) noex ;

#ifdef	COMMENT
local int	rectab_count	(RECTAB *) noex ;
#endif

local int	mapfile_start	(MAPFILE *,int,cchar *,int) noex ;
local int	mapfile_end	(MAPFILE *) noex ;

local int	indinsert(uint (*rt)[2],uint (*it)[3],int,strentry *) noex ;
local int	hashindex(uint,int) noex ;


/* local variables */

constexpr char		zerobuf[4] = {
	0, 0, 0, 0 
} ; /* end array */


/* exported variables */

const SFM_OBJ	strfilemks_modinfo = {
	"strfilemks",
	szof(SFM),
	0
} ; /* end initialization */

cbool			f_firsthash	= CF_FIRSTHASH ;
cbool			f_minmod	= CF_MINMOD ;
cbool			f_late		= CF_LATE ;


/* exported variables */


/* exported subroutines */

int strfilemks_open(SFM *op,cc *dbname,int oflags,mode_t om,int n) noex {
	int		rs ;

	if (op == nullptr) return SR_FAULT ;
	if (dbname == nullptr) return SR_FAULT ;
	if (dbname[0] == '\0') return SR_INVALID ;

	if (n < SFM_NENTRIES) {
	    n = SFM_NENTRIES ;
	}

	memclear(op) ;
	op->om = om ;
	op->nfd = -1 ;
	op->gid = -1 ;
	op->pagesz = getpagesize() ;

	op->fl.creat	= !!(oflags & O_CREAT) ;
	op->fl.excl	= !!(oflags & O_EXCL) ;
	op->fl.none	= ((! op->fl.creat) && (! op->fl.excl)) ;

	if ((rs = strfilemks_recbegin(op)) >= 0) {
	    if (cchar *cp ; (rs = mem.strw(dbname,-1,&cp)) >= 0) {
		op->dbname = cp ;
		if ((rs = strfilemks_filesbegin(op)) >= 0) {
		    if ((rs = strfilemks_listbegin(op,n)) >= 0) {
			op->magval = SFM_MAGIC ;
		    }
		    if (rs < 0) {
			strfilemks_filesend(op,false) ;
		    } /* end if (error) */
		} /* end if */
		if (rs < 0) {
	    	    mem.free(op->dbname) ;
	    	    op->dbname = nullptr ;
		} /* end if (error) */
	    } /* end if (memory-allocation) */
	    if (rs < 0) {
	        strfilemks_recend(op) ;
	    } /* end if (error) */
	} /* end if (recmgr) */

	return rs ;
} /* end subroutine (strfilemks_open) */

int strfilemks_close(SFM *op) noex {
	int		rs = SR_OK ;
	int		rs1 ;
	int		f_remove = true ;
	int		nvars = 0 ; /* return-value */
	if (op == nullptr) return SR_FAULT ;
	if (op->magval != SFM_MAGIC) return SR_NOTOPEN ;

	nvars = op->nvars ;
	if (! op->fl.abort) {
	    rs1 = strfilemks_mkvarfile(op) ;
	    f_remove = (rs1 < 0) ;
	    if (rs >= 0) rs = rs1 ;
	}
	if (op->nfd >= 0) {
	    rs1 = u_close(op->nfd) ;
	    if (rs >= 0) rs = rs1 ;
	    op->nfd = -1 ;
	}
	{
	rs1 = strfilemks_listend(op) ;
	if (! f_remove) f_remove = (rs1 < 0) ;
	if (rs >= 0) rs = rs1 ;
	}
	if ((rs >= 0) && (! op->fl.abort)) {
	    rs1 = strfilemks_renamefiles(op) ;
	    if (rs >= 0) rs = rs1 ;
	}
	{
	rs1 = strfilemks_filesend(op,f_remove) ;
	if (rs >= 0) rs = rs1 ;
	}
	if (op->dbname) {
	    rs1 = mem.free(op->dbname) ;
	    if (rs >= 0) rs = rs1 ;
	    op->dbname = nullptr ;
	} /* end if (memory-release) */
	op->magval = 0 ;
	return (rs >= 0) ? nvars : rs ;
} /* end subroutine (strfilemks_close) */

int strfilemks_addfile(SFM *op,cchar *sp,int sl) noex {
	cint		ms = STEFILEMK_MAXFILESIZE ;
	int		rs ;
	int		rs1 ;

	if (op == nullptr) return SR_FAULT ;
	if (sp == nullptr) return SR_FAULT ;

	if (op->magval != SFM_MAGIC) return SR_NOTOPEN ;

	if ((rs = mapfile_start(&fm,ms,sp,sl)) >= 0) {
	    {
	    rs = strfilemks_addfiler(op,&fm) ;
	    }
	    rs1 = mapfile_finish(&fm) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (mapfile) */

	return rs ;
} /* end subroutine (strfilemks_addfile) */

local int strfilemks_addfiler(SFM *op,MAPFILE *mfp) noex {
	RM		*rmp = op->recorder ;
	cnullptr	np{} ;
	int		rs ;
	int		rs1 ;
	int		c = 0 ;
	if ((rs = recmgr_grpbegin(rmp)) >= 0) {
	    int		ml = intsat(mfp->msize) ;
	    int		ll ;
	    cchar	*tp, *lp ;
	    cchar	*mp = mfp->mdata ;
	    while ((tp = strnbrk(mp,ml,"\n#")) != np) {
	        lp = mp ;
	        ll = (tp - mp) ;
	        len = ((tp + 1) - mp) ;
	        if (*tp == '#') {
	            if ((tp = strnchr((tp+1),(mp+ml-(tp+1)),'\n')) != np) {
	                len = ((tp + 1) - mp) ;
		    }
	        }
		if (ll > 0) {
		    cint	mo = (intconv(mfp->msize) - ml) ;
		    if ((rs = recmgr_grpadd(rmp,mo,ll)) >= 0) {
			if ((rs = idx_bufstr(op->idx,lp,ll)) >= 0) {
				c += 1 ;
			}
		    }
		} /* end if (non-zero positive) */
	        mp += len ;
	        ml -= len ;
	        if (rs < 0) break ;
	    } /* end while (lines) */
	    rs1 = recmgr_grpend(rmp) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (recgrp) */
	op->nstrs += c ;
	return (rs >= 0) ? c : rs ;
} /* end subroutine (strfilemks_addfiler) */

local int recmgr_start(RM *rmp) noex {
	cint	esz = szof(RM_ENT) ;
	cint	vn = 100 ;
	cint	vo = 0 ;
	memclear(rmp) ;
	return vecobj_start(&rmp->recs,esz,vn,vo) ;
} /* end subroutine (strfilemks_start) */

local int recmgr_finish(RM *rmp) noex {
	return vecobj_finish(&rmp->recs) ;
} /* end subroutine (strfilemks_finish) */

local int recmgr_grpbegin(RM *rmp) noex {
	rmp->bso = rmp->so ;
	return SR_OK ;
} /* end subroutine (strfilemks_grpbegin) */

/* nothing to do */
local int recmgr_grpend(RM *rmp) noex {
	if (rmp == nullptr) return SR_FAULT ;
	return SR_OK ;
} /* end subroutine (strfilemks_grpend) */

local int recmgr_grpadd(RM *rmp,int si,int sl) noex {
	RM_ENT	e ;
	e.si = (si + rmp->bso) ;
	s.sl = sl ;
	rmp->so += (si+1) ;
	return vecobj_add(&rmp->recs,&e) ;
} /* end subroutine (strfilemks_grpadd) */

int strfilemks_abort(SFM	*op) noex {
	if (op == nullptr) return SR_FAULT ;
	if (op->magval != SFM_MAGIC) return SR_NOTOPEN ;
	op->fl.abort = true ;
	return SR_OK ;
} /* end subroutine (strfilemks_abort) */

int strfilemks_chgrp(SFM *op,gid_t gid) noex {
	if (op == nullptr) return SR_FAULT ;
	if (op->magval != SFM_MAGIC) return SR_NOTOPEN ;
	op->gid = gid ;
	return SR_OK ;
} /* end subroutine (strfilemks_chgrp) */


/* private subroutines */

local int strfilemks_recbegin(SFM *op) noex {
	cint	rsz = szof(RM) ;
	int	rs ;
	if (void *p ; (rs = mem.mall(rsz,&p)) >= 0) {
	    RM	*rmp = p ;
	    op->recorder = p ;
	    rs = recmgr_start(rmp) ;
	    if (rs < 0) {
		mem.free(op->recorder) ;
		op->recorder = nullptr ;
	    } /* end if (error) */
	} /* end if (memory-allocation) */
	return rs ;
} /* end subroutine (strfilemks_recbegin) */

local int strfilemks_recend(SFM *op) noex {
	int	rs = SR_OK ;
	int	rs1 ;
	{
	    rs1 = recmg_finish(&op->recorder) ;
	    if (rs >= 0) rs = rs1 ;
	}
	if (op->recorder) {
	    rs1 = mem.free(op->recorder) ;
	    if (rs >= 0) rs = rs1 ;
	    op->recorder = nullptr ;
	} /* end if (meory-release) */
	return rs ;
} /* end subroutine (strfilemks_recend) */

local int strfilemks_idxbegin(SFM *op,cchar *dbname) noex {
	cint	isz = szof(idx) ;
	int	rs ;
	if (void *p ; (rs = mem.mall(isz,&p)) >= 0) {
	    idx		*ixp = p ;
	    op->idx = p ;
	    rs = idx_start(op->idx,dbname) ;
	    if (rs < 0) {
		mem.free(op->idx) ;
		op->idx = nullptr ;
	    } /* end if (error) */
	} /* end if (memory-allocation) */
	return rs ;
} /* end subroutine (strfilemks_idxbegin) */

local int strfilemks_idxend(SFM *op) noex {
	int	rs = SR_OK ;
	int	rs1 ;
	if (op->idx) {
	    {
	        rs1 = idx_finish(op->idx) ;
	        if (rs >= 0) rs = rs1 ;
	    }
	    {
	        rs1 = mem.free(op->idx) ;
	        if (rs >= 0) rs = rs1 ;
	        op->idx = nullptr ;
	    } /* end if (memory-release) */
	}
	return rs ;
} /* end subroutine (strfilemks_idxend) */

local int idx_start(idx *ixp,cchar *dbname) noex {
	int	rs = SR_OK ;
	memclear(ixp) ;
	ixp->fd = -1 ;
	cchar	*dnp ;
	if (int dnl ; (dnl = sfdirname(dbname,-1,&dnp)) >= 0) {
	    int		bnl ;
	    cchar	*bnp ;
	    if ((bnl = sfbasename(dbname,-1,&bnp)) > 0) {
		int	sz = 0 ;
		char	*bp ;
		sz += (dnl+1) ;
		sz += (bnl+1) ;
		if ((rs = mem.mall(sz,&bp)) >= 0) {
		    ixp->ai = bp ;
		    op->idname = bp ;
		    bp = (strwcpy(bp,dnp,dnl) + 1) ;
		    ixp->ibname = bp ;
		    bp = (strwcpy(bp,bnp,bnl) + 1) ;
		    if ((rs = idx_dirwritable(ixp)) >= 0) {
			cchar	*fsuf = STRLISTMKS_FSUF ;
		        rs = idx_create(ixp,fsuf) ;
		    }
		    if (rs < 0) {
			mem.free(idx->ai) ;
			idx->ai = nullptr ;
			idx->idname = nullptr ;
			idx->ibname = nullptr ;
		    } /* end if (error) */
		} /* end if (memory-allocation) */
	    } else {
		rs = SR_INVALID ;
	    } /* end if (error) */
	} else {
	    rs = SR_BADFMT ;
	} /* end if (error) */
	return rs ;
} /* end subroutine (idx_start) */

local int idx_finish(idx *ixp) noex {
	int	rs = SR_OK ;
	int	rs1 ;
	if (ixp->nfname) {
	    rs1 = mem.free(ixp->nfname) ;
	    if (rs >= 0) rs = rs1 ;
	    ixp->nfname = nullptr ;
	} /* end if (memory-release) */
	if (ixp->ai) {
	    rs1 = mem.free(ixp->ai) ;
	    if (rs >= 0) rs = rs1 ;
	    ixp->ai = nullptr ;
	    idx->idname = nullptr ;
	    idx->ibname = nullptr ;
	} /* end if (memory-release) */
	return rs ;
} /* end subroutine (idx_finish) */

local int idx_dirwritable(idx *ixp) noex {
	cint	am = (X_OK|W_OK) ;
	int	rs ;
	cchar	*dname = ixp->idname ;
	{
	if (dname[0] == '\0') dname = "." ;
	rs = perm(dname,-1,-1,nullptr,am) ;
	}
	return rs ;
} /* end subroutine (idx_dirwritable) */

local int idx_create(idx *ixp,cchar *fsuf) noex {
	time_t		dt = time(nullptr) ;
	cint		clen = MAXNAMELEN ;
	int		rs ;
	cchar	*ibname = ixp->ibname ;
	cchar	*end = ENDIANSTR ;
	char		cbuf[MAXNAMELEN+1] ;

	if ((rs = sncpy5(cbuf,clen,ibname,".",fsuf,end,"n")) >= 0) {
	    cchar	*nfname = cbuf ;
	    char	tbuf[MAXPATHLEN+1] ;
	    if (op->idname[0] != '\0') {
		rs = mkpath2(tbuf,op->idname,cbuf) ;
		nfname = tbuf ;
	    }
	    if ((rs = idx_nfopen(ixp,nfname)) == SR_EXISTS) {
		if ((rs = idx_nfold(ixp,dt,nfname)) > 0) {
	    	    rs = idx_nfopen(ixp,nfname) ;
	 	} else (rs >= 0) {
	    	    op->fl.inprogress = true ;
		    rs = idx_nfopentmp(ixp,fsuf) ;
		}
	    }
	    if (rs >= 0) {
		if ((rs = idx_bufbegin(ixp)) >= 0) {
		    rs = idx_creator(ixp) ;
		    if (rs < 0) {
			idx_bufend(ixp) ;
		    } /* end if (error) */
		}
		if (rs < 0) {
		    idx_destroy(ixp) ;
		} /* end if (error) */
	    } /* end if (ok) */
	} /* end if (making component name) */
	return rs ;
} /* end subroutine (idx_create) */

local int idx_creator(idx *ixp) noex {
	int	rs ;
	if ((rs = idx_mapbegin(ixp)) >= 0) {
	    rs = idx_bufhdr(ixp) ;
	}
	return rs ;
} /* end subroutine (idx_creator) */

local int idx_destroy(idx *ixp) noex {
	int	rs = SR_OK ;
	int	rs1 ;
	if (ixp->fd >= 0) {
	    rs1 = u_close(ixp->fd) ;
	    if (rs >= 0) rs = rs1 ;
	    ixp->fd = -1 ;
	}
	if (ixp->nfname) {
	    if (ixp->nfname[0] != '\0') {
		u_unlink(izp->nfname) ;
	    }
	    rs1 = mem.free(ixp->nfname) ;
	    if (rs >= 0) rs = rs1 ;
	    ixp->nfname = nullptr ;
	} /* end if (memory-release) */
	return rs ;
} /* end subroutine (idx_destroy) */

local int idx_nfopen(idx *ixp,cchar *nfname) noex {
	cint	of = (O_CREAT | O_EXCL | O_WRONLY) ;
	int	rs ;
	if ((rs = u_open(nfname,of,op->om)) >= 0) {
	    op->nfd = rs ;
	}
	return rs ;
} /* end subroutine (idx_nfopen) */

local int idx_nfclose(idx *ixp) noex {
	int	rs = SR_OK ;
	int	rs1 ;
	if (ixp->fd >= 0) {
	    rs1 = u_close(op->fd) ;
	    if (rs >= 0) rs = rs1 ;
	    op->fd = -1 ;
	}
	return rs ;
} /* end subroutine (idx_nfclose) */

local int idx_nfold(idx *ixp,time_t dt,cchar *nfname) noex {
	int	rs ;
	int	f = false ;
	if (ustat sb ; (rs = u_stat(nfname,&sb)) >= 0) {
	    if ((dt-sb.st_mtime) >= TO_OLD) {
		if (u_unlink(nfname) >= 0) f = true ;
	    }
	} else if (isNotPresent(rs)) {
	    rs = SR_OK ;
	    f = true ;
	}
	return (rs >= 0) ? f : rs ;
} /* end subroutine (idx_nfold) */

local int idx_nfopentmp(idx *ixp,cchar *fsuf) noex {
	cint	of = (O_WRONLY | O_CREAT) ;
	cint	clen = MAXNAMELEN ;
	int		rs = SR_OK ;
	cchar	*fpre = "sm" ;
	cchar	*xxx = "XXXXXXXX" ;
	cchar	*end = ENDIANSTR ;
	char	cbuf[MAXNAMELEN + 1] ;
	if ((rs = sncpy6(cbuf,clen,fpre,xxx,".",fsuf,end,"n")) >= 0) {
	    char	infname[MAXPATHLEN + 1] ;
	    if (op->idname[0] != '\0') {
		rs = mkpath2(infname,op->idname,cbuf) ;
	    } else {
		rs = mkpath1(infname,cbuf) ;
	    }
	    if (rs >= 0) {
	        char	obuf[MAXPATHLEN + 1] = { 0 } ;
		if ((rs = opentmpfile(infname,of,op->om,obuf)) >= 0) {
	                ixp->nfd = rs ;
		        rs = idx_nfstore(op,obuf) ;
		        if (rs < 0) {
		            if (obuf[0] != '\0') u_unlink(obuf) ;
			    u_close(ixp->nfd) ;
			    ixp->fd = -1 ;
		        } /* end if (error) */
		} /* end if (opentmpfile) */
	    } /* end if (ok) */
	} /* end if (making file-name) */
	return rs ;
} /* end subroutine (idx_nfopentmp) */

local int idx_nfstore(idx *op,cchar *nf) noex {
	int		rs = SR_OK ;
	int		rs1 ;
	if (op->nfname) {
	    rs1 = mem.free(op->nfname) ;
	    if (rs >= 0) rs = rs1 ;
	    op->nfname = nullptr ;
	} /* end if (memory-release) */
	if (rs >= 0) {
	    if (cchar *cp ; (rs = mem.strw(nf,-1,&cp)) >= 0) {
	        op->nfname = cp ;
	    } /* end if (memory-acquire) */
	} /* end if (ok) */
	return rs ;
} /* end subroutine (idx_nfstore) */

local int idx_bufbegin(idx *ixp) noex {
	int	rs ;
	if ((rs = filer_start(&ixp->fb,ixp->fd,0z,0,0)) >= 0) {
	    ixp->fl.fb = true ;
	}
	return rs ;
} /* end subroutine (idx_bufbegin) */

local int idx_bufend(idx *ixp) noex {
	int	rs = SR_OK ;
	int	rs1 ;
	if (ixp->fl.fb) {
	    ixp->fl.fb = false ;
	    rs1 = filer_finish(&ixp->fb) ;
	    if (rs >= 0) rs = rs1 ;
	}
	return rs ;
} /* end subroutine (idx_bufend) */

local int idx_bufwrite(idx *ixp,cvoid *wbuf,int wlen) noex {
	int	rs = filer_write(&ixp->db,wbuf,wlen) ;
	ixp->fo += rs ;
	return rs ;
} /* end subroutine (idx_bufwrite) */

local int idx_bufhdr(idx *ixp) noex {
	cint	hlen = szof(STRLISTHDR) ;
	int	rs ;
	rs = filer_write(&ixp->db,&ixp->hdr,hlen) ;
	ixp->fo += rs ;
	ixp->hdr.stoff = ixp->fo ;
	return rs ;
} /* end subroutine (idx_bufhdr) */

local int idx_bufstr(idx *ixp,cchar *lp,int ll) noex {
	filer	*fbp = &ixp->fb ;
	int	rs ;
	{
	rs = filer_println(fbp,lp,ll) ;
	}
	return rs ;
} /* end subroutine (idx_bufstr) */

local int strfilemks_filesbegin(SFM *op) noex {
	int		rs = SR_INVALID ;
	int		dnl ;
	cchar		*dnp ;
	char		tmpdname[MAXPATHLEN + 1] ;

	if ((dnl = sfdirname(op->dbname,-1,&dnp)) >= 0) {
	    if (cchar *cp ; (rs = mem.strw(dnp,dnl,&cp)) >= 0) {
	        op->idname = cp ;
	        if (dnl == 0) {
	            rs = getpwd(tmpdname,MAXPATHLEN) ;
	            dnl = rs ;
	        } else
	            rs = mkpath1w(tmpdname,dnp,dnl) ;
	        if (rs >= 0) {
	            int	operm = (X_OK | W_OK) ;
	            rs = perm(tmpdname,-1,-1,nullptr,operm) ;
	        }
	        if (rs >= 0) {
	            if ((rs = strfilemks_nfcreate(op,FSUF_IND)) >= 0) {
	                if (op->fl.creat && op->fl.excl) {
	                    rs = strfilemks_fexists(op) ;
	                }
	                if (rs < 0) {
		            strfilemks_nfdestroy(op) ;
			} /* end if (error) */
	            } /* end if (nfcreate) */
	        }
	        if (rs < 0) {
		    if (op->idname != nullptr) {
	    	        mem.free(op->idname) ;
	    	        op->idname = nullptr ;
		    } /* end if (memory-release) */
	        } /* end if (error) */
	    } /* end if (memory-allocation) */
	} /* end if (sfdirname) */
	return rs ;
} /* end subroutine (strfilemks_filesbegin) */

local int strfilemks_filesend(SFM *op,int f) noex {
	int	rs = SR_OK ;
	int	rs1 ;
	(void) f ;
	if (op->nfname) {
	    if (f && (op->nfname[0] != '\0')) {
	        u_unlink(op->nfname) ;
	    }
	    rs1 = mem.free(op->nfname) ;
	    if (rs >= 0) rs = rs1 ;
	    op->nfname = nullptr ;
	} /* end if (memory-release) */
	if (op->idname) {
	    rs1 = mem.free(op->idname) ;
	    if (rs >= 0) rs = rs1 ;
	    op->idname = nullptr ;
	} /* end if (memory-release) */
	return rs ;
} /* end subroutine (strfilemks_filesend) */

/* exclusively create this new file */
local int strfilemks_nfcreate(SFM *op,cchar *fsuf) noex {
	cint	to_old = TO_OLDFILE ;
	int	rs ;
	int	rs1 ;
	int	nfl ;
	int	oflags = (O_CREAT | O_EXCL | O_WRONLY) ;
	cchar	*end = ENDIANSTR ;
	cchar	*cp ;
	char	nfname[MAXPATHLEN + 1] ;

	rs = mkfnamesuf3(nfname,op->dbname,fsuf,end,"n") ;
	nfl = rs ;
	if (rs >= 0) {
	    rs = mem.strw(nfname,nfl,&cp) ;
	    if (rs >= 0) op->nfname = (char *) cp ;
	} /* end if (memory-acquire) */

	if (rs < 0) goto ret0 ;

again:
	rs = u_open(op->nfname,oflags,op->om) ;
	op->nfd = rs ;

	if_constexpr (f_late) {
	if (rs >= 0) {
	    u_close(op->nfd) ;
	    op->nfd = -1 ;
	}
	} /* end if_constexpr (f_late) */

	if (rs == SR_EXIST) {
	    time_t	daytime = time(nullptr) ;
	    int		f_inprogress ;
	ustat	sb ;
	    rs1 = u_stat(op->nfname,&sb) ;
	    if ((rs1 >= 0) && ((daytime - sb.st_mtime) > to_old)) {
		u_unlink(op->nfname) ;
		goto again ;
	    }
	    op->fl.inprogress = true ;
	    f_inprogress = op->fl.none ;
	    f_inprogress = f_inprogress || (op->fl.creat && op->fl.excl) ;
	    rs = (f_inprogress) ? SR_INPROGRESS : SR_OK ;
	} /* end if */

	if (rs >= 0) {
	    op->fl.created = true ;
	} else {
	    if (op->nfname) {
	        mem.free(op->nfname) ;
	        op->nfname = nullptr ;
	    } /* end if (memory-release) */
	} /* end if */

ret0:
	return rs ;
} /* end subroutine (txindexmks_nfcreate) */

local int strfilemks_nfcreatecheck(SFM *op,cc *fpre,cc *fsuf) noex {
	int		rs = SR_OK ;
	if ((op->nfd < 0) || op->fl.inprogress) {
	    int	oflags = O_WRONLY | O_CREAT ;
	    if (op->nfd >= 0) {
		u_close(op->nfd) ;
		op->nfd = -1 ;
	    }
	    if (op->fl.inprogress) {
		char	cname[MAXNAMELEN + 1] ;
		char	infname[MAXPATHLEN + 1] ;
		char	outfname[MAXPATHLEN + 1] ;
		outfname[0] = '\0' ;
		rs = sncpy6(cname,MAXNAMELEN,
			fpre,"XXXXXXXX",".",fsuf,ENDIANSTR,"n") ;
		if (rs >= 0) {
		    if ((op->idname != nullptr) && (op->idname[0] != '\0')) {
		        rs = mkpath2(infname,op->idname,cname) ;
		    } else {
		        rs = mkpath1(infname,cname) ;
		    }
		}
		if (rs >= 0) {
		    rs = opentmpfile(infname,oflags,op->om,outfname) ;
	            op->nfd = rs ;
		    op->fl.created = (rs >= 0) ;
		}
		if (rs >= 0) {
		    rs = strfilemks_nfstore(op,outfname) ;
		} /* end if (ok) */
		if (rs < 0) {
		    if (outfname[0] != '\0') {
			u_unlink(outfname) ;
		    }
		} /* end if (error) */
	    } else {
	        rs = u_open(op->nfname,oflags,op->om) ;
	        op->nfd = rs ;
		op->fl.created = (rs >= 0) ;
	    }
	    if (rs < 0) {
		if (op->nfd >= 0) {
		    u_close(op->nfd) ;
		    op->nfd = -1 ;
		}
	        if (op->nfname != nullptr) {
		    if (op->nfname[0] != '\0') {
			u_unlink(op->nfname) ;
		    }
	            mem.free(op->nfname) ;
	            op->nfname = nullptr ;
		} /* end if (memory-release) */
	    } /* end if (error) */
	} /* end if */

	return rs ;
} /* end subroutine (strfilemks_nfcreatecheck) */

local int strfilemks_nfdestroy(SFM *op) noex {
	int	rs = SR_OK ;
	int	rs1 ;
	if (op->nfd >= 0) {
	    rs1 = u_close(op->nfd) ;
	    if (rs >= 0) rs = rs1 ;
	    op->nfd = -1 ;
	}
	if (op->nfname) {
	    if (op->nfname[0] != '\0') {
		rs1 = u_unlink(op->nfname) ;
	        if (rs >= 0) rs = rs1 ;
	    }
	    rs1 = mem.free(op->nfname) ;
	    if (rs >= 0) rs = rs1 ;
	    op->nfname = nullptr ;
	} /* end if (memory-release) */
	return rs ;
} /* end subroutine (strfilemks_nfdestroy) */

local int strfilemks_nfstore(SFM *op,cchar *outfname) noex {
	int	rs = SR_OK ;
	int	rs1 ;
	if (op->nfname) {
	    rs1 = mem.free(op->nfname) ;
	    if (rs >= 0) rs = rs1 ;
	    op->nfname = nullptr ;
	} /* end if (memory-release) */
	if (cchar *cp ; (rs = = mem.strw(outfname,-1,&cp)) >= 0) {
	    op->nfname = charp(cp) ;
	} /* end if (memory-acquire) */
	return rs ;
} /* end subroutine (strfilemks_nfstore) */

local int strfilemks_fexists(SFM *op) noex {
	int	rs = SR_OK ;
	if (op->fl.creat && op->fl.excl && op->fl.inprogress) {
	    cchar	*suf = FSUF_IND ;
	    cchar	*end = ENDIANSTR ;
	    char	hfname[MAXPATHLEN + 1] ;
	    if ((rs = mkfnamesuf2(hfname,op->dbname,suf,end)) >= 0) {
		ustat	sb ;
	        int	rs1 = u_stat(hfname,&sb) ;
	        if (rs1 >= 0) rs = SR_EXIST ;
	    }
	}
	return rs ;
} /* end subroutine (strfilemks_fexists) */

local int strfilemks_listbegin(SFM *op,int n) noex {
	cint		sz = (n * SFM_SIZEMULT) ;
	int		rs ;
	if ((rs = strtab_start(&op->strs,sz)) >= 0) {
	    rs = rectab_start(&op->rectab,n) ;
	    if (rs < 0) {
		strtab_finish(&op->strs) ;
	    } /* end if (error) */
	} /* end if (strtab-keys) */
	return rs ;
} /* end subroutine (strfilemks_listbegin) */

local int strfilemks_listend(SFM *op) noex {
	int		rs = SR_OK ;
	int		rs1 ;
	{
	    rs1 = rectab_finish(&op->rectab) ;
	    if (rs >= 0) rs = rs1 ;
	}
	{
	    rs1 = strtab_finish(&op->strs) ;
	    if (rs >= 0) rs = rs1 ;
	}
	return rs ;
} /* end subroutine (strfilemks_listend) */

local int strfilemks_mkvarfile(SFM *op) noex {
	int		rs ;
	int		nv = 0 ; /* return-value */
	if ((rs =rectab_done(&op->rectab)) >= 0) {
	    cint	rtl = rs ;
	    if (rtl == (op->nvars + 1)) {
	        rs = strfilemks_wrvarfile(op) ;
	        nv = op->nvars ;
	    } else {
	        rs = SR_BUGCHECK ;
	    }
	} /* end if (rectab_done) */
	return (rs >= 0) ? nv: rs ;
} /* end subroutine (strfilemks_mkvarfile) */

local int strfilemks_wrvarfile(SFM *op) noex {
	STRLISTGDR	hf ;
	filer	varfile ;
	strtab	*ksp = &op->strs ;
	time_t	daytime = time(nullptr) ;
	uint	fileoff = 0 ;
	uint	(*rt)[2] ;
	cint	pagesz = getpagesize() ;
	int	rs = SR_OK ;
	int	rs1 ;
	int	rtl ;
	int	itl ;
	int	sz ;
	int	bl ;
	char	buf[BUFLEN + 1] ;

	rtl = rectab_getvec(&op->rectab,&rt) ;

/* open (create) the STRFILE file */

	rs = strfilemks_nfcreatecheck(op,"nv",FSUF_IND) ;
	if (rs < 0)
	    goto ret0 ;

	op->fl.viopen = true ;
	sz = (pagesz * 4) ;
	rs = filer_start(&varfile,op->nfd,0z,sz,0) ;
	if (rs < 0)
	    goto ret1 ;

/* prepare the file-header */

	hf = {} ;
	hf.vetu[0] = STRLISTHDR_VERSION ;
	hf.vetu[1] = ENDIAN ;
	hf.vetu[2] = 0 ;
	hf.vetu[3] = 0 ;
	hf.wtime = (uint) daytime ;
	hf.nvars = op->nvars ;
	hf.nskip = SFM_NSKIP ;

/* create the file-header */

	rs = strlisthdr(&hf,0,buf,BUFLEN) ;
	bl = rs ;
	if (rs < 0)
	    goto ret2 ;

/* write header */

	if (rs >= 0) {
	    rs = filer_writefill(&varfile,buf,bl) ;
	    fileoff += rs ;
	}

	if (rs < 0)
	    goto ret2 ;

/* write the record table */

	hf.rtoff = fileoff ;
	hf.rtlen = rtl ;

	sz = (rtl + 1) * 2 * szof(uint) ;
	rs = filer_write(&varfile,rt,sz) ;
	fileoff += rs ;

/* make and write out key-string table */

	if (rs >= 0) {
	    sz = strtab_strsize(ksp) ;
	    hf.ksoff = fileoff ;
	    hf.kslen = sz ;
	    if (char *kstab ; (rs = mem.mall(sz,&kstab)) >= 0) {
	        rs = strtab_strmk(ksp,kstab,sz) ;
		/* write out the key-string table */
	        if (rs >= 0) {
	            rs = filer_write(&varfile,kstab,sz) ;
	            fileoff += rs ;
	        }
		/* make and write out the record-index table */
	        if (rs >= 0) {
		    uint	(*indtab)[3] = nullptr ;
	            itl = nextpowtwo(rtl) ;
	            hf.itoff = fileoff ;
	            hf.itlen = itl ;
	            sz = (itl + 1) * 3 * szof(int) ;
	            if ((rs = mem.mall(sz,&indtab)) >= 0) {
			memnset(indtab,sz,0) ;
	                rs = strfilemks_mkind(op,kstab,indtab,itl) ;
	                if (rs >= 0) {
	                    rs = filer_write(&varfile,indtab,sz) ;
	                    fileoff += rs ;
	                }
	                mem.free(indtab) ;
	            } /* end if (memory allocation) */

	        } /* end if (record-index table) */
	        mem.free(kstab) ;
	    } /* end if (m-a-f) */
	} /* end if (key-string table) */

/* write out the header -- again! */
ret2:
	filer_finish(&varfile) ;

	if (rs >= 0) {

	    hf.fsize = fileoff ;

	    rs = strlisthdr(&hf,0,buf,BUFLEN) ;
	    bl = rs ;
	    if (rs >= 0) {
	        rs = u_writep(op->nfd,buf,bl,0z) ;
	    }

	    if_constexpr (f_minmod) {
		if (rs >= 0) {
	    	    rs = uc_fminmod(op->nfd,op->om) ;
		}
	    } /* end if_constexpr (f_minmod) */

	    if ((rs >= 0) && (op->gid >= 0)) {
		rs = u_fchown(op->nfd,-1,op->gid) ;
	    }

	} /* end if (succeeded?) */

/* we're out of here */
ret1:
	{
	op->fl.viopen = false ;
	rs1 = u_close(op->nfd) ;
	if (rs >= 0) rs = rs1 ;
	op->nfd = -1 ;
	}
	if ((rs < 0) && (op->nfname[0] != '\0')) {
	    u_unlink(op->nfname) ;
	    op->nfname[0] = '\0' ;
	} /* end if (error) */

ret0:
	return rs ;
} /* end subroutine (strfilemks_wrvarfile) */

/* make an index table of the record table */
int strfilemks_mkind(SFM *op,cchar *kst, uint (*it)[3],it,int il) noex {
	strentry	ve ;
	uint	ri, ki, hi ;
	uint	khash ;
	uint	(*rt)[2] ;
	int	rs = SR_OK ;
	int	rtl ;
	int	sc = 0 ;
	cchar	*kp ;

	rtl = rectab_getvec(&op->rectab,&rt) ;

	if_constexpr (f_firsthash) {
	    cint	sz = szof(strentry) ;
	    cint	vo = vecobjm.compact ;
	    if (vecobj ves ; (rs = ves.start(sz,rtl,vo)) >= 0) {

	    for (ri = 1 ; ri < rtl ; ri += 1) {

	        ki = rt[ri][0] ;
	        kp = kst + ki ;
	        khash = hash_elf(kp,-1) ;

	        hi = hashindex(khash,il) ;

	        if (it[hi][0] == 0) {
	            it[hi][0] = ri ;
	            it[hi][1] = (khash & INT_MAX) ;
	            it[hi][2] = 0 ;
	            sc += 1 ;
	        } else {
		    ve.ri = ri ;
		    ve.ki = ki ;
	            ve.khash = chash ;
	            ve.hi = hi ;
	            rs = ves.add(&ve) ;
	        } /* end if */

	        if (rs < 0) break ;
	    } /* end for */

	    if (rs >= 0) {
	        strentry	*vep ;
	        for (int i = 0 ; ves.get(i,&vep) >= 0 ; i += 1) {
	            sc += indinsert(rt,it,il,vep) ;
	        } /* end for */
	    } /* end if (ok) */

	    ves.finish() ;
	    } /* end if (ves) */

	} else {
	    for (ri = 1 ; ri < rtl ; ri += 1) {
	        ki = rt[ri][0] ;
	        kp = kst + ki ;
	        khash = hash_elf(kp,-1) ;
	        hi = hashindex(khash,il) ;
	        ve.ri = ri ;
	        ve.ki = ki ;
	        ve.khash = khash ;
	        ve.hi = hi ;
	        sc += indinsert(rt,it,il,&ve) ;
	    } /* end for */
	} /* end if_constexpr (f_firsthash) */

	it[il][0] = UINT_MAX ;
	it[il][1] = 0 ;
	it[il][2] = 0 ;

	if (sc < 0) {
	    sc = 0 ;
	}

	return (rs >= 0) ? sc : rs ;
} /* end subroutine (strfilemks_mkind) */

local int strfilemks_renamefiles(SFM *op) noex {
	int	rs ;
	cchar	*end = ENDIANSTR ;
	char	hashfname[MAXPATHLEN + 1] ;

	if ((rs = mkfnamesuf2(hashfname,op->dbname,FSUF_IND,end)) >= 0) {
	    if ((rs = u_rename(op->nfname,hashfname)) >= 0) {
	        op->nfname[0] = '\0' ;
	    }
	    if (op->nfname[0] != '\0') {
	        u_unlink(op->nfname) ;
	        op->nfname[0] = '\0' ;
	    }
	}

	return rs ;
} /* end subroutine (strfilemks_renamefiles) */

local int rectab_start(RECTAB *rtp,int n) noex {
	int	rs = SR_OK ;
	int	sz ;
	if (n < 10) n = 10 ;
	rtp->i = 0 ;
	rtp->n = n ;
	sz = (n + 1) * 2 * szof(int) ;
	if (void *p ; (rs = mem.mall(sz,&p)) >= 0) {
	    rtp->rectab = p ;
	    rtp->rectab[0][0] = 0 ;
	    rtp->rectab[0][1] = 0 ;
	    rtp->i = 1 ;
	} /* end if (memory-acquire) */
	return rs ;
} /* end subroutine (rectab_start) */

local int rectab_finish(RECTAB *rtp) noex {
	int	rs = SR_OK ;
	int	rs1 ;
	if (rtp->rectab) {
	    rs1 = mem.free(rtp->rectab) ;
	    if (rs >= 0) rs = rs1 ;
	    rtp->rectab = nullptr ;
	} /* end if (memory-release) */
	return rs ;
} /* end subroutine (rectab_finish) */

local int rectab_add(RECTAB *rtp,int ki,int vi) noex {
	int	rs = SR_OK ;
	int	i = rtp->i ;
	if ((i + 1) > rtp->n) {
	    rs = rectab_extend(rtp) ;
	}
	if (rs >= 0) {
	    rtp->rectab[i][0] = ki ;
	    rtp->rectab[i][1] = vi ;
	    rtp->i += 1 ;
	}
	return (rs >= 0) ? i : rs ;
} /* end subroutine (rectab_add) */

local int rectab_extend(RECTAB *rtp) noex {
	int	rs = SR_OK ;
	if ((rtp->i + 1) > rtp->n) {
	    uint	(*va)[2] ;
	    int		nn ;
	    int		sz ;
	    nn = (rtp->n + 1) * 2 ;
	    sz = (nn + 1) * 2 * szof(int) ;
	    if ((rs = mem.real(rtp->rectab,sz,&va)) >= 0) {
	        rtp->rectab = va ;
	        rtp->n = nn ;
	    } /* end if (memory-reallocation) */
	} /* end if */
	return rs ;
} /* end subroutine (rectab_extend) */

local int rectab_done(RECTAB *rtp) noex {
	int	i = rtp->i ;
	rtp->rectab[i][0] = UINT_MAX ;
	rtp->rectab[i][1] = 0 ;
	return rtp->i ;
} /* end subroutine (rectab_done) */

#ifdef	COMMENT
local int rectab_count(RECTAB *rtp) noex {
	return rtp->i ;
} /* end subroutine (rectab_count) */
#endif /* COMMENT */

local int rectab_getvec(RECTAB *rtp,uint (**rpp)[2]) noex {
    	int		rs = SR_OK ;
	*rpp = rtp->rectab ;
	rs = rtp->i ;
	return rs ;
} /* end subroutine (rectab_getvec) */

local int mapfile_start(MAPFILE *mfp,int msz,cchar *sp,int sl) noex {
    	cnullptr	np{} ;
	int		rs ;
	int		rs1 ;
	cchar		*fname ;
	memclear(mfp) ;
	if (nulstr fn ; (rs = nulstr_start(&fn,sp,sl,&fname)) >= 0) {
	    cint	of = O_RDONLY ;
	if ((rs = uc_open(fname,of,0666)) >= 0) {
	    cint	fd = rs ;
	    if (ustat db ; (rs = u_fstat(fd,&sb)) >= 0) {
		csize fsize = size_t(sb.st_size) ;
		if (S_ISREG(sb.st_mode)) {
		    csize	psize = size_t(op->pagesz) ;
		    if ((max > 0) && (sb.st_size <= max)) {
	    	        size_t	ms = MAX(psize,fsize) ;
	    	        int	mp = PROT_READ ;
	    	        int	mf = MAP_SHARED ;
	    	        void	*md ;
		        if ((rs = u_mmap(np,ms,mp,mf,fd,0z,&md)) >= 0) {
			    cint		madv = MADV_SEQUENTIAL ;
			    const caddr_t	ma = md ;
	    		    if ((rs = u_madvise(ma,ms,madv)) >= 0) {
			         mfp->mdata = md ;
			         mfp->msize = ms ;
			    }
			    if (rs < 0) {
				u_munmap(md,ms) ;
			    } /* end if (error) */
	    	        } /* end if (mmap) */
		    } else {
	    	        rs = SR_TOOBIG ;
		    } /* end if (error) */
	        } else {
	            rs = SR_PROTO ;
		} /* end if (error) */
	    } /* end if (stat) */
	    u_close(fd) ;
	} /* end if (file-open) */
	    rs1 = nulstr_finish(&fn) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (file-name) */
	return rs ;
} /* end subroutine (mapfile_begin) */

local int mapfile_end(MAPFILE *mfp) noex {
	int		rs = SR_OK ;
	if (mfp->mapdata != nullptr) {
	    csize	ms = fmp->mapsize ;
	    cvoid	*md = fmp->mapdata ;
	    rs = u_munmap(md,ms) ;
	    mfp->mapdata = nullptr ;
	    mfp->mapsize = 0 ;
	}
	return rs ;
} /* end subroutine (mapfile_end) */

local int filer_writefill(filer *bp,cchar *wbuf,iknt elen) noex {
	int		rs ;
	int		r, nzero ;
	int		len ;
	if (wlen < 0) {
	    wlen = (lenstr(wbuf) + 1) ;
	}
	rs = filer_write(bp,wbuf,wlen) ;
	len = rs ;
	r = (wlen & 3) ;
	if ((rs >= 0) && (r > 0)) {
	    nzero = (4 - r) ;
	    if (nzero > 0) {
	        rs = filer_write(bp,zerobuf,nzero) ;
	        len += rs ;
	    }
	}
	return (rs >= 0) ? len : rs ;
} /* end subroutine (filer_writefill) */

local int indinsert(uint (*rt)[2],uint (*it)[3],int il,strentry *vep) noex {
	uint	nhash, chash ;
	uint	ri, ki ;
	uint	lhi, nhi, hi ;
	int	c = 0 ;

	hi = vep->hi ;
	nhash = vep->khash ;
	chash = (nhash & INT_MAX) ;
	/* CONSTCOND */
	forever {
	    if (it[hi][0] == 0) break ;

	    ri = it[hi][0] ;
	    ki = rt[ri][0] ;
	    if (ki == vep->ki) break ;

	    it[hi][1] |= (compl INT_MAX) ;
	    nhash = hashagain(nhash,c++,SFM_NSKIP) ;

	    hi = hashindex(nhash,il) ;
	} /* end forever */

	if (it[hi][0] > 0) {

	    lhi = hi ;
	    while ((nhi = it[lhi][2]) > 0) {
	        lhi = nhi ;
	    }
	    hi = hashindex((lhi + 1),il) ;

	    while (it[hi][0] > 0) {
	        hi = hashindex((hi + 1),il) ;
	    }
	    it[lhi][2] = hi ;

	} /* end if (same-key continuation) */

	it[hi][0] = vep->ri ;
	it[hi][1] = chash ;
	it[hi][2] = 0 ;

	return c ;
} /* end subroutine (indinsert) */

local int hashindex(uint i,int n) noex {
	int		hi = MODP2(i,n) ;
	if (hi == 0) hi = 1 ;
	return hi ;
} /* end subroutine (hashindex) */


