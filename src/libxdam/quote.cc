/* quote SUPPORT (XXX junk -- COPY FROM CALYEARS) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* quote database operations */
/* version %I% last-modified %G% */

#define	CF_SAFE		1		/* normal safety */
#define	CF_SAFE2	1		/* extra safety */
#define	CF_EMPTYTERM	1		/* terminate entry on empty line */
#define	CF_TMPPRNAME	1		/* put under a PRNAME in /tmp */
#define	CF_SAMECITE	0		/* same entry citation? */
#define	CF_ALREADY	1		/* do not allow duplicate results */

/* revision history:

	- 2008-10-01, David A­D­ Morano
	This object module was originally written.

*/

/* Copyright © 2008 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Object:
	quote

	Descrption:
	This module implements an interface (a trivial one) that
	allows access to the QUOTE datbase.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<sys/mman.h>
#include	<climits>		/* |UINT_MAX| + |UCHAR_MAX| */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<usyscalls.h>
#include	<uclibmem.h>
#include	<bufsizeget.h>
#include	<mktmp.h>
#include	<vecobj.h>
#include	<sbuf.h>
#include	<ids.h>
#include	<vecstr.h>
#include	<tmtime.hh>
#include	<fsdir.h>
#include	<getusername.h>
#include	<txtindexmk.h>
#include	<textlook.h>
#include	<hash.h>		/* |hash_elf(3dam)| */
#include	<strn.h>
#include	<strwcpy.h>
#include	<char.h>
#include	<localmisc.h>

#include	"quote.h"

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |lenstr(3u)| */
import uconstants ;

/* local defines */

#define	QUOTE_DBSUF	"calendar"
#define	QUOTE_CAL	quote_qdir
#define	QUOTE_NLE	1		/* default number line entries */
#define	QUOTE_DMODE	0777

#define	QU		quote
#define	QU_EL		quote_eline
#define	QU_EFL		quote_eflags
#define	QU_Q		ccharpp
#define	QU_ENT		quute_ent
#define	QU_CUR		quute_cur

#define	QDIR		quote_dir
#define	QDIR_DBDIR	".quotes"
#define	QDIR_DBDIRMODE	0777
#define	QDIR_QUOTES	"share/quotes"

#define	TL		textlook
#define	TL_ENT		textlook_ce
#define	TL_CUR		textlook_cur
#define	TL_Q		textlook_cq

#define	WR		worder

#define	SI		subinfo

#define	IDXDNAME	"quote"
#define	IDXNAME		"quote"
#define	IDXSUF		"cyi"

#define	HOLBUFLEN	100

#ifndef	VARTMPDNAME
#define	VARTMPDNAME	"TMPDIR"
#endif

#ifndef	TMPDNAME
#define	TMPDNAME	"/tmp"
#endif

#ifndef	TMPVARDNAME
#define	TMPVARDNAME	"/var/tmp"
#endif

#undef	NLINES
#define	NLINES		20

#define	CEBUFLEN	(NLINES * 3 * szof(int))

#define	TO_FILEMOD	(60 * 24 * 3600)
#define	TO_MKWAIT	(5 * 50)
#define	TO_CHECK	4



/* external subroutines */


/* local structures */

struct subinfo_fl {
	uint		id : 1 ;
	uint		defdirs : 1 ;
	uint		dom : 1 ;
	uint		hols : 1 ;
} ; /* end struct */

struct subinfo {
	ids		id ;
	vecstr		defdirs ;
	quote		*op ;
	cchar		*tmpdname ;
	char		*tudname ;
	char		*userhome ;
	cchar		**dirnames ;
	char		*username ;
	time_t		daytime ;
	subinfo_fl	init ;
	subinfo_fl	fl ;
	int		year ;
	int		isdst ;
	int		gmtoff ;
} ; /* end struct */

struct quote_dfl {
	uint		tind : 1 ;
} ; /* end struct */

struct quote_dir {
	char		*dirname ;
	textlook	looker ;
	time_t		ti_mtime ;		/* latest for all entries */
	quote_dfl	fl ;
	int		nentries ;		/* DB entries */
	int		cidx ;			/* ordinal */
} ; /* end struct */

struct quote_qdfl {
	uint		writedbdir : 1 ;
} ; /* end struct */

struct quote_qdir {
	char		*dirname ;
	char 		*calname ;		/* DB file-name */
	char		*mapdata ;		/* DB memory-map address */
	quote_qdfl	fl ;
	TL		vind ;			/* verse-index */
	time_t		ti_db ;			/* DB file modification */
	time_t		ti_map ;		/* DB map */
	time_t		ti_lastcheck ;		/* DB last check */
	time_t		ti_vind ;		/* verse-index */
	uint		filesize ;		/* DB file size */
	uint		mapsize ;		/* DB map length */
	int		nentries ;		/* DB entries */
	int		cidx ;			/* ordinal */
} ; /* end struct (quote_qdir) */

struct quote_eline {
	uint		loff ;
	uint		llen ;
} ; /* end struct */

struct quote_eflags {
	uint		hash : 1 ;
} ; /* end struct */

struct quote_ent {
	quote_eline	*lines ;
	quote_eflags	fl ;
	uint		voff ;
	uint		vlen ;
	uint		hash ;
	int		e, i ;
	int		cidx ;
	uchar		m, d ;
} ; /* end struct */

struct quote_citer {
	int		i, e ;
} ; /* end struct */

struct worder {
	quote_eline	*lines ;
	cchar		*mp ;
	cchar		*sp ;
	int		sl ;
	int		i ;
	int		nlines ;
} ; /* end struct */


/* forward references */

template<typename ... Args>
local int quote_ctor(quote *op,Args ... args) noex {
    	QUOTE		*hop = op ;
	int		rs = SR_FAULT ;
	if (op && (args && ...)) {
	    rs = memclear(hop) ;
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (quote_ctor) */

local int quote_dtor(quote *op) noex {
	int		rs = SR_FAULT ;
	if (op) {
	    rs = SR_OK ;
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (quote_dtor) */

template<typename ... Args>
local inline int quote_magic(quote *op,Args ... args) noex {
	int		rs = SR_FAULT ;
	if (op && (args && ...)) {
	    rs = (op->magic == QUOTE_MAGIC) ? SR_OK : SR_NOTOPEN ;
	}
	return rs ;
}
/* end subroutine (quote_magic) */

local int	quote_dirnamescreate(QU *,cchar **) noex ;
local int	quote_dirnamesdestroy(QU *) noex ;

local int	quote_checkupdate(QU *,time_t) noex ;
local int	quote_loadbuf(QU *,QU_ENT *,char *,int) noex ;
local int	quote_tmpfrees(QU *) noex ;

local int	quote_dirsopen(QU *,SI *,cchar **,cchar **) noex ;
local int	quote_dirsclose(QU *) noex ;
local int	quote_diropen(QU *,SI *,cchar *,cchar **) noex ;
local int	quote_dirclose(QU *,QDIR *) noex ;

local int	quote_qdirsdestroy(QU *) noex ;
local int	quote_qdircreate(QU *,SI *,cchar *,cchar *) noex ;
local int	quote_qdirdestroy(QU *,QU_CAL *) noex ;

#ifdef	COMMENT
local int	quote_mksysvarsi(QU *,cchar *) noex ;
#endif

local int	quote_freeresults(QU *,QU_CUR *) noex ;
local int	quote_qdircite(QU *,vecobj *,QU_CAL *,QU_Q *) noex ;
local int	quote_mkresults(QU *,vecobj *,QU_CUR *) noex ;
local int	quote_already(QU *,vecobj *,QU_ENT *) noex ;
local int	quote_debugcur(QU *,vecobj *,cchar *) noex ;

local int	cal_open(QU_CAL *,SI *,int,cchar *,cchar *) noex ;
local int	cal_close(QU_CAL *) noex ;
local int	cal_dbloadinit(QU_CAL *,SI *) noex ;
local int	cal_dbloadfree(QU_CAL *) noex ;
local int	cal_indopen(QU_CAL *,SI *) noex ;
local int	cal_dbmapcreate(QU_CAL *,time_t) noex ;
local int	cal_dbmapdestroy(QU_CAL *) noex ;
local int	cal_indopenperm(QU_CAL *,SI *) noex ;
local int	cal_indopentmp(QU_CAL *,SI *) noex ;

#ifdef	COMMENT
local int	cal_idxset(QU_CAL *,int) noex ;
#endif

local int	cal_idxget(QU_CAL *) noex ;
local int	cal_indopencheck(QU_CAL *,cchar *,int,int) noex ;
local int	cal_mkdirs(QU_CAL *,cchar *,mode_t) noex ;
local int	cal_audit(QU_CAL *) noex ;

local int	cal_indmk(QU_CAL *,DI *,cchar *,int,time_t) noex ;
local int	cal_indmkdata(QU_CAL *,DI *,cchar *,int,int) noex ;
local int	cal_indclose(QU_CAL *) noex ;

local int	cal_loadbuf(QU_CAL *,QU_ENT *,char *,int) noex ;
local int	cal_mapdata(QU_CAL *,cchar **) noex ;

local int	subinfo_start(DI *,QU *,time_t,cchar **) noex ;
local int	subinfo_ids(DI *) noex ;
local int	subinfo_finish(DI *) noex ;
local int	subinfo_username(DI *) noex ;
local int	subinfo_tmpuserdir(DI *) noex ;
local int	subinfo_mkdirnames(DI *) noex ;
local int	subinfo_havedir(DI *,char *) noex ;
local int	subinfo_loadnames(DI *,vecstr *,cchar *) noex ;
local int	subinfo_havestart(DI *,QU_Q *,cchar *,int) noex ;
local int	subinfo_year(DI *) noex ;
local int	subinfo_checkdname(DI *,cchar *) noex ;

#ifdef	COMMENT
local int	subinfo_mkday(DI *,int,cchar *,int) noex ;
local int	subinfo_transhol(DI *,QUOTE_CITE *,cchar *,int) noex ;
#endif

local int	entry_start(QU_ENT *,QUOTE_CITE *,int,int) noex ;
local int	entry_setidx(QU_ENT *,int) noex ;
local int	entry_add(QU_ENT *,uint,uint) noex ;
local int	entry_finish(QU_ENT *) noex ;

#ifdef	COMMENT
local int	entry_release(QU_ENT *) noex ;
#endif

local int	entry_mkhash(QU_ENT *,QU *) noex ;
local int	entry_sethash(QU_ENT *,uint) noex ;
local int	entry_samehash(QU_ENT *,QU *,QU_ENT *) noex ;
local int	entry_same(QU_ENT *,QU *,QU_ENT *) noex ;
local int	entry_loadbuf(QU_ENT *,cchar *,char *,int) noex ;

#if	CF_SAMECITE
local int	entry_samecite(QU_ENT *,QU *,QU_ENT *) noex ;
#endif

local int	mkbve_start(CYIMK_ENT *,DI *,QU_ENT *) noex ;
local int	mkbve_finish(CYIMK_ENT *) noex ;

local int	worder_start(WR *,QU *,QU_ENT *) noex ;
local int	worder_finish(WR *) noex ;
local int	worder_get(WR *,cchar **) noex ;

static bool	isempty(cchar *,int) noex ;

local int	mkmonth(cchar *,int) noex ;
local int	dayofmonth_mkday(DAYOFMONTH *,uint,cchar *,int) noex ;

local int	vrcmp(cvoid **,cvoid **) noex ;


/* local variables */

constexpr cint		rsterm[] = {
	SR_FAULT,
	SR_INVALID,
	SR_NOMEM,
	SR_NOANODE,
	SR_BADFMT,
	SR_NOSPC,
	SR_NOSR,
	SR_NOBUFS,
	SR_BADF,
	SR_OVERFLOW,
	SR_RANGE,
	0
} ; /* end array (rsterm) */


/* exported variables */

extern const quote_obj	quote_modinfo = {
	"quote",
	szof(quote),
	szof(QU_CUR)
} ;


/* exported subroutines */

int quote_open(quote *op,cc *pr,cc *dirnames,cc *quotenames) noex {
	int		rs ;
	int		rs1 ;
	int		c = 0 ;
	if ((rs = quote_ctor(op,pr)) >= 0) {
	    rs = SR_INVALID ;
	    if (pr[0]) {
	int		wopts ;
	op->pr = pr ;
	op->tmpdname = getenv(VARTMPDNAME) ;
	if (op->tmpdname == nullptr) {
	    op->tmpdname = TMPDNAME ;
	}

	rs = quote_dirnamescreate(op,dirnames) ;
	if (rs < 0)
	    goto bad0 ;

	rs = vecstr_start(&op->tmpfiles,2,0) ;
	if (rs < 0)
	    goto bad1 ;

	opts = VECHAND_OSTATIONARY ;
	rs = vechand_start(&op->dirs,2,opts) ;
	if (rs < 0)
	    goto bad2 ;

	subinfo		si, *sip = &si ;
	if ((rs = subinfo_start(sip,op,0z,dirnames)) >= 0) {
	    {
	    rs = quote_dirsopen(op,sip,sip->dirnames,quotenames) ;
	    c = rs ;
	    }
	    rs1 = subinfo_finish(sip) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if */

	if (rs < 0)
	    goto bad3 ;

/* done */

	op->nentries = c ;
	op->magic = QUOTE_MAGIC ;

ret0:

	    } /* end if (valid) */
	    if (rs < 0) {
		quote_dtor(op) ;
	    }
	} /* end if (quote_ctor) */
	return (rs >= 0) ? c : rs ;

/* bad stuff */
bad3:
	quote_qdirsdestroy(op) ;
	vechand_finish(&op->dirs) ;

bad2:
	quote_tmpfrees(op) ;
	vecstr_finish(&op->tmpfiles) ;

bad1:
	quote_dirnamesdestroy(op) ;

bad0:
	goto ret0 ;
}
/* end subroutine (quote_open) */

int quote_close(quote *op) noex {
	int	rs ;

#if	CF_SAFE
	if (op == nullptr)
	    return SR_FAULT ;

	if (op->magic != QUOTE_MAGIC)
	    return SR_NOTOPEN ;
#endif

	rs = quote_qdirsdestroy(op) ;

	vechand_finish(&op->cals) ;

	quote_tmpfrees(op) ;
	vecstr_finish(&op->tmpfiles) ;

	quote_dirnamesdestroy(op) ;

	op->nentries = 0 ;
	op->magic = 0 ;
	return rs ;
}
/* end subroutine (quote_close) */

int quote_count(quote *op) noex {
	int		rs ;

#if	CF_SAFE
	if (op == nullptr) return SR_FAULT ;
	if (op->magic != QUOTE_MAGIC) return SR_NOTOPEN ;
#endif

	rs = op->nentries ;

	return rs ;
}
/* end subroutine (quote_count) */

int quote_audit(quote *op) noex {
	QU_CAL	*calp ;
	int	rs = SR_OK ;
	int	c = 0 ;

#if	CF_SAFE
	if (op == nullptr) return SR_FAULT ;
	if (op->magic != QUOTE_MAGIC) return SR_NOTOPEN ;
#endif

	for (int i = 0 ; vechand_get(&op->cals,i,&calp) >= 0 ; i += 1) {
	    if (calp == nullptr) continue ;
	    c += 1 ;
	    rs = cal_audit(calp) ;
	    if (rs < 0)
		break ;
	} /* end for */

	return (rs >= 0) ? c : rs ;
}
/* end subroutine (quote_audit) */

int QU_CURbegin(quote *op,quote_cur *curp) noex {
    	int		rs = SR_OK ;

#if	CF_SAFE
	if (op == nullptr) return SR_FAULT ;
	if (op->magic != QUOTE_MAGIC) return SR_NOTOPEN ;
#endif

	if (curp == nullptr) return SR_FAULT ;
	memclear(curp) ;

	op->ncursors += 1 ;

	curp->i = -1 ;
	curp->magic = QUOTE_MAGIC ;
	return rs ;
}
/* end subroutine (QU_CURbegin) */

int QU_CURend(quote *op,quote_cur *curp) noex {
	int		rs = SR_OK ;

#if	CF_SAFE
	if (op == nullptr) return SR_FAULT ;
	if (op->magic != QUOTE_MAGIC) return SR_NOTOPEN ;
#endif

	if (curp == nullptr) return SR_FAULT ;
	if (curp->magic != QUOTE_MAGIC) return SR_NOTOPEN ;

	if (curp->results != nullptr) {
	    quote_freeresults(op,curp) ;
	    lm_free(curp->results) ;
	    curp->results = nullptr ;
	}

	if (op->ncursors > 0) {
	    op->ncursors -= 1 ;
	}

	curp->magic = 0 ;
	return rs ;
}
/* end subroutine (QU_CURend) */

local int quote_freeresults(quote *op,QU_CUR *curp) noex {
	QU_ENT	*ep ;
	int		rs = SR_OK ;

	ep = (QU_ENT *) curp->results ;
	if (ep != nullptr) {
	    for (int i = 0 ; i < curp->nresults ; i += 1) {
		entry_finish(ep + i) ;
	    }
	} /* end if */

	return rs ;
}
/* end subroutine (quote_freeresults) */

int quote_lookup(QU *op,QU_CUR *curp,int qopts,QU_Q *qvp) noex {
	QU_CAL	*calp ;

	vecobj	res ;

	int	rs = SR_OK ;
	int	i ;
	int	opts ;
	int	sz ;
	int	c = 0 ;

#if	CF_SAFE
	if (op == nullptr) return SR_FAULT ;
	if (op->magic != QUOTE_MAGIC) return SR_NOTOPEN ;
#endif

	if (curp == nullptr) return SR_FAULT ;
	if (curp->magic != QUOTE_MAGIC) return SR_NOTOPEN ;
	if (qvp == nullptr) return SR_FAULT ;

	if (curp->results != nullptr) {
	    quote_freeresults(op,curp) ;
	    lm_free(curp->results) ;
	    curp->results = nullptr ;
	}

	opts = 0 ;
	opts |= VECOBJ_OORDERED ;
	opts |= VECOBJ_OSTATIONARY ;
	sz = szof(QU_ENT) ;
	rs = vecobj_start(&res,sz,0,opts) ;
	if (rs < 0)
	    goto ret0 ;

	for (i = 0 ; vechand_get(&op->cals,i,&calp) >= 0 ; i += 1) {
	    if (calp == nullptr) continue ;

	    rs = quote_qdircite(op,&res,calp,qvp) ;
	    c += rs ;

	    if (rs < 0)
	        break ;

	} /* end for */

	if (rs >= 0) {
	    rs = quote_mkresults(op,&res,curp) ;
	}

	if ((rs < 0) || (c > 0)) {
	    QU_ENT	*ep ;
	    for (i = 0 ; vecobj_get(&res,i,&ep) >= 0 ; i += 1) {
		if (ep == nullptr) continue ;
		entry_finish(ep) ;
	    } /* end for */
	}

ret1:
	vecobj_finish(&res) ;

ret0:
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (quote_lookcite) */

int quote_read(quote *op,QU_CUR *curp,quote_cur *qvp,
		char *rbuf,int rlen) noex {
	QU_ENT	*ep ;
	int	rs = SR_OK ;
	int	i ;
	int	len = 0 ;

#if	CF_SAFE
	if (op == nullptr) return SR_FAULT ;
	if (op->magic != QUOTE_MAGIC) return SR_NOTOPEN ;
#endif

	if (curp == nullptr) return SR_FAULT ;
	if (curp->magic != QUOTE_MAGIC) return SR_NOTOPEN ;
	if (qvp == nullptr) return SR_FAULT ;

	if (curp->results == nullptr) {
	    rs = SR_NOTFOUND ;
	    goto ret0 ;
	}

	i = curp->i ;

	if (i < 0) {
	    rs = SR_NOTFOUND ;
	    goto ret0 ;
	}

	if (i >= curp->nresults) {
	    rs = SR_NOTFOUND ;
	    goto ret0 ;
	}

	ep = (QU_ENT *) curp->results ;
	qvp->m = ep->m ;
	qvp->d = ep->d ;
	if (rbuf != nullptr) {
	    rs = quote_loadbuf(op,(ep + i),rbuf,rlen) ;
	    len = rs ;
	} /* end if */

	if (rs >= 0)
	    curp->i = (i + 1) ;

ret0:
	return (rs >= 0) ? len : rs ;
}
/* end subroutine (quote_read) */

int quote_check(quote *op,time_t dt) noex {
	int	rs = SR_OK ;

#if	CF_SAFE
	if (op == nullptr) return SR_FAULT ;
	if (op->magic != QUOTE_MAGIC) return SR_NOTOPEN ;
#endif

#ifdef	COMMENT
	rs = quote_checkupdate(op,dt) ;
#endif

	return rs ;
}
/* end subroutine (quote_check) */


/* private subroutines */

local int quote_dirnamescreate(quote *op,cchar **dirnames) noex {
	int	rs = SR_OK ;
	int	strsize ;
	int	sz ;
	int	i ;

	char	*p ;
	char	*sp ;


	if (dirnames == nullptr)
	    goto ret0 ;

	strsize = 1 ;
	for (i = 0 ; dirnames[i] != nullptr ; i += 1) {
	    strsize += (lenstr(dirnames[i]) + 1) ;
	} /* end if */

	sz = (i + 1) * szof(char *) ;
	rs = lm_mall(sz,&p) ;
	if (rs < 0)
	    goto bad0 ;

	op->dirnames = (char **) p ;
	rs = lm_mall(strsize,&p) ;
	if (rs < 0)
	    goto bad1 ;

	op->dirstrtab = p ;
	sp = p ;
	*sp++ = '\0' ;
	for (i = 0 ; dirnames[i] != nullptr ; i += 1) {
	    op->dirnames[i] = sp ;
	    sp = strwcpy(sp,dirnames[i],-1) + 1 ;
	} /* end for */
	op->dirnames[i] = nullptr ;

ret0:
	return rs ;

bad1:
	lm_free(op->dirnames) ;
	op->dirnames = nullptr ;

bad0:
	goto ret0 ;
}
/* end subroutine (quote_dirnamescreate) */

local int quote_dirnamesdestroy(quote *op) noex {
	int		rs = SR_OK ;
	if (op->dirnames != nullptr) {
	    lm_free(op->dirnames) ;
	    op->dirnames = nullptr ;
	}

	if (op->dirstrtab != nullptr) {
	    lm_free(op->dirstrtab) ;
	    op->dirstrtab = nullptr ;
	}

	return rs ;
}
/* end subroutine (quote_dirnamesdestroy) */

local int quote_qdircite(QU *op,vecobj *rlp,QU_CAL *calp,QU_Q *qvp) noex {
	QU_ENT	e ;
	TL		*cip ;
	TL_CUR	ccur ;
	TL_Q	cq{} ;
	TL_ENT	ce ;

	uint	loff, llen ;

	int	rs = SR_OK ;
	int	rs1 ;
	int	celen = CEBUFLEN ;
	int	cidx ;
	int	n, i ;
	int	c = 0 ;
	int	f_ent = false ;
	int	f_already = false ;

	char	cebuf[CEBUFLEN + 1] ;


	cip = &calp->vind ;
	rs = cal_idxget(calp) ;
	cidx = rs ;
	if (rs < 0)
	    goto ret0 ;

	cq.m = qvp->m ;
	cq.d = qvp->d ;

	if ((rs = cyi_curbegin(cip,&ccur)) >= 0) {

	    if ((rs = cyi_curcite(cip,&ccur,&cq)) >= 0) {
	        while (rs >= 0) {

	            rs1 = cyi_curread(cip,&ccur,&ce,cebuf,celen) ;

	            if ((rs1 == SR_NOTFOUND) || (rs1 == 0))
		        break ;

		    rs = rs1 ;
		    if (rs < 0)
			break ;

		    if (rs1 > 0) {

			n = 0 ;
			for (i = 0 ; i < ce.nlines ; i += 1) {
			    loff = ce.lines[i].loff ;
			    llen = ce.lines[i].llen ;

			    n += 1 ;
			    if (! f_ent) {
	        		rs = entry_start(&e,qvp,loff,llen) ;
				if (rs >= 0) {
				    f_ent = true ;
				    entry_sethash(&e,ce.hash) ;
				    rs = entry_setidx(&e,cidx) ;
				}
			    } else {
	        		rs = entry_add(&e,loff,llen) ;
			    }
			} /* end for */

			if ((rs >= 0) && (n > 0) && f_ent) {
			    c += 1 ;

#if	CF_ALREADY
			    rs = quote_already(op,rlp,&e) ;
			    f_already = (rs > 0) ;
#endif

			    f_ent = false ;
			    if ((rs >= 0) && (! f_already))
		                rs = vecobj_add(rlp,&e) ;
		            if ((rs < 0) || f_already)
			        entry_finish(&e) ;
			}

		    } /* end if */

	        } /* end while */

		if (f_ent) {
			f_ent = false ;
			entry_finish(&e) ;
	 	}

	    } else if (rs == SR_NOTFOUND)
	        rs = SR_OK ;

	    cyi_curend(cip,&ccur) ;
	} /* end if */

ret0:
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (quote_qdircite) */


local int quote_already(op,rlp,ep)
QUOTE		*op ;
vecobj		*rlp ;
QU_ENT	*ep ;
{
	QU_ENT	*oep ;
	int	rs = SR_OK ;
	int	f = false ;

	for (int i = 0 ; vecobj_get(rlp,i,&oep) >= 0 ; i += 1) {
	    if (oep == nullptr) continue ;

	    rs = entry_samehash(ep,op,oep) ;
	    if (rs == 0) continue ;

	    if (rs >= 0)
	        rs = entry_same(ep,op,oep) ;

	    f = (rs > 0) ;
	    if (f) break ;

	    if (rs < 0)
		break ;

	} /* end for */

	return (rs >= 0) ? f : rs ;
}
/* end subroutine (quote_already) */

local int quote_mkresults(QU *op,vecobj *rlp,QU_CUR *curp) noex {
	QU_ENT	*rp ;
	QU_ENT	*ep ;

	int	rs = SR_OK ;
	int	n ;
	int	i ;
	int	sz ;
	int	c = 0 ;

	vecobj_sort(rlp,vrcmp) ; /* sort results in ascending order */

	n = vecobj_count(rlp) ;
	if (n <= 0)
	    goto ret0 ;

	sz = n * szof(QU_ENT) ;
	rs = lm_mall(sz,&rp) ;
	if (rs < 0)
	    goto ret0 ;

	for (i = 0 ; vecobj_get(rlp,i,&ep) >= 0 ; i += 1) {
	    if (ep == nullptr) continue ;

	    rp[c++] = *ep ;
	    vecobj_del(rlp,i) ; /* entries are stationary */
	} /* end for */

	if (rs >= 0) {
	    curp->results = rp ;
	    curp->nresults = c ;
	    curp->i = 0 ;
	} else
	    lm_free(rp) ;

ret0:
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (quote_mkresults) */

local int quote_tmpfrees(quote *op) noex {
    	int		rs = SR_OK ;
	char		*sp ;
	for (int i = 0 ; vecstr_get(&op->tmpfiles,i,&sp) >= 0 ; i += 1) {
	    if (sp == nullptr) continue ;
	    if (sp[0] != '\0') {
		u_unlink(sp) ;
	    }
	} /* end for */
	return rs ;
}
/* end subroutine (quote_tmpfrees) */

local int quote_dirsopen(op,sip,dirnames,quotenames)
QUOTE		*op ;
DI	*sip ;
cchar	*dirnames[] ;
cchar	*quotenames[] ;
{
	int	rs = SR_OK ;
	int	i ;
	int	c = 0 ;


	if (dirnames == nullptr)
	    goto ret0 ;

	for (i = 0 ; dirnames[i] != nullptr ; i += 1) {
	    if (dirnames[i] == '\0') continue ;

	    rs = quote_diropen(op,sip,dirnames[i],quotenames) ;
	    c += rs ;
	    if (rs < 0)
		break ;

	} /* end for (dirnames) */

ret0:
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (quote_dirsopen) */

local int quote_dirsclose(quote *op) noex {
	QDIR	*qdirp ;
	int	rs = SR_OK ;
	int	rs1 ;
	for (int i = 0 ; vechand_get(&op->cals,i,&qdirp) >= 0 ; i += 1) {
	    if (qdirp == nullptr) continue ;
	    rs1 = quote_dirclose(op,qdirp) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end for */

	return rs ;
}
/* end subroutine (quote_dirsclose) */


local int quote_diropen(op,sip,dirname,quotenames)
QUOTE		*op ;
DI	*sip ;
cchar	*dirname ;
cchar	*quotenames[] ;
{
	int	rs = SR_OK ;
	int	rs1 ;
	int	sz ;
	int	c = 0 ;

	QDIR	*qdirp = nullptr ;

	char	*p ;


	if (dirname == nullptr)
	    goto ret0 ;

	sz = szof(QDIR) ;
	rs = lm_mall(sz,&p) ;
	if (rs < 0)
	    goto bad0 ;

	qdirp = (QDIR *) p ;
	rs1 = qdir_open(qdirp,sip,dirname) ;
	if (rs1 == SR_NOENT)
	    goto bad1 ;

	rs = rs1 ;
	c += rs1 ;
	if (rs < 0)
	    goto bad1 ;

	rs = vechand_add(&op->dirs,qdirp) ;
	if (rs < 0)
	    goto bad1 ;

ret0:
	return (rs >= 0) ? c : rs ;

bad1:
	lm_free(qdirp) ;

bad0:
	goto ret0 ;
}
/* end subroutine (quote_diropen) */

local int quote_dirclose(quote *op,qdir *qdirp) noex {
	int		rs ;
	int		rs1 ;

	rs = cal_close(qdirp) ;

	rs1 = vechand_ent(&op->cals,qdirp) ;
	if (rs1 >= 0)
	    vechand_del(&op->dirs,rs1) ;

	lm_free(qdirp) ;

	return rs ;
}
/* end subroutine (quote_dirclose) */


local int quote_qdircreate(op,sip,dirname,calname)
QUOTE		*op ;
DI	*sip ;
cchar	dirname[] ;
cchar	calname[] ;
{
	ustat	sb ;

	QU_CAL	*calp ;

	int	rs = SR_OK ;
	int	rs1 ;
	int	cidx ;
	int	sz = szof(QU_CAL) ;
	int	f = false ;

	cchar	*suf = QUOTE_DBSUF ;

	char	cname[MAXNAMELEN + 1] ;
	char	tmpfname[MAXPATHLEN + 1] ;


	rs = snsds(cname,MAXNAMELEN,calname,suf) ;

	if (rs >= 0)
	    rs = mkpath2(tmpfname,dirname,cname) ;

	if (rs < 0)
	    goto bad0 ;

	rs1 = u_stat(tmpfname,&sb) ;
	if (rs1 >= 0)
	    rs1 = permids(&sip->id,&sb,R_OK) ;

	if (rs1 < 0)
	    goto bad0 ;

	f = f || S_ISREG(sb.st_mode) ;
	f = f || S_ISCHR(sb.st_mode) ;
	f = f || S_ISSOCK(sb.st_mode) ;
	if (! f)
	    rs = SR_LIBEXEC ; /* or should it be SR_OPNOTSUPP */

	if (rs < 0)
	    goto bad0 ;

	rs = lm_mall(sz,&calp) ;
	if (rs < 0)
	    goto bad0 ;

	rs = vechand_add(&op->cals,calp) ;
	cidx = rs ;
	if (rs < 0)
	    goto bad1 ;

	rs = cal_open(calp,sip,cidx,dirname,calname) ;
	if (rs < 0)
	    goto bad2 ;

	f = true ;

ret0:
	return (rs >= 0) ? f : rs ;

/* bad stuff */
bad2:
	vechand_del(&op->cals,cidx) ;

bad1:
	lm_free(calp) ;

bad0:
	goto ret0 ;
}
/* end subroutine (quote_qdircreate) */


local int quote_qdirdestroy(op,calp)
QUOTE		*op ;
QU_CAL	*calp ;
{
	int	rs ;
	int	rs1 ;


	rs = cal_close(calp) ;

	rs1 = vechand_ent(&op->cals,calp) ;
	if (rs1 >= 0)
	    vechand_del(&op->cals,rs1) ;

	lm_free(calp) ;

	return rs ;
}
/* end subroutine (quote_qdirdestroy) */


#ifdef	COMMENT

local int quote_checkupdate(op,daytime)
QUOTE		*op ;
time_t		daytime ;
{
	DI	si ;

	ustat	sb ;

	int	rs = SR_OK ;
	int	rs1 ;
	int	f = false ;


	if (op->ncursors > 0)
	    goto ret0 ;

	if (daytime <= 0)
	    daytime = time(nullptr) ;

	if ((daytime - op->ti_lastcheck) < TO_CHECK)
	    goto ret0 ;

	op->ti_lastcheck = daytime ;
	rs1 = u_stat(op->dbfname,&sb) ;
	if (rs1 < 0)
	    goto ret0 ;

	if ((sb.st_mtime > op->ti_db) || (sb.st_mtime > op->ti_map)) {

	    f = true ;
	    quote_dbloadfree(op) ;

	    rs = subinfo_start(&si,op,op->daytime,nullptr) ;
	    if (rs >= 0) {

	        rs = quote_dbloadinit(op,&si) ;

		subinfo_finish(&si) ;

	    } /* end if */

	} /* end if (update) */

ret0:
	return (rs >= 0) ? f : rs ;
}
/* end subroutine (quote_checkupdate) */

#endif /* COMMENT */


local int quote_loadbuf(op,ep,rbuf,rlen)
QUOTE		*op ;
QU_ENT	*ep ;
char		rbuf[] ;
int		rlen ;
{
	QU_CAL	*calp ;

	int	rs ;
	int	cidx ;


	cidx = ep->cidx ;

	rs = vechand_get(&op->cals,cidx,&calp) ;
	if (rs < 0)
	    goto ret0 ;

	rs = cal_loadbuf(calp,ep,rbuf,rlen) ;

ret0:
	return rs ;
} 
/* end subroutine (quote_loadbuf) */


local int qdir_open(qdirp,sip,dirname)
QDIR		*qdirp ;
DI	*sip ;
cchar	dirname[] ;
{
	QUOTE	*op = sip->op ;

	TEXTLOOK_INFO	tinfo ;

	time_t	mtime ;

	int	rs = SR_NOENT ;
	int	dbl ;
	int	f_remake = false ;
	int	f_textlook = false ;

	cchar	*basedname ;
	cchar	*dbdir = QDIR_DBDIR ;

	char	dbdname[MAXPATHLEN + 1] ;
	char	dbname[MAXPATHLEN + 1] ;
	char	*dbp ;


	dbl = sfbasename(dirname,-1,&dbp) ;
	if (dbl <= 0)
	    goto ret0 ;

	memclear(qdirp) ;

	rs = mkpath2(dbdname,dirname,dbdir) ;
	if (rs < 0)
	    goto ret0 ;

	rs = mkpath2w(dbname,dbdname,dbp,dbl) ;
	if (rs < 0)
	    goto ret0 ;

	rs = qdir_dbdir(qdirp,sip,dbdname) ;
	if ((rs1 == SR_NOENT) || (rs1 == SR_ACCESS) || (rs1 == SR_NOTDIR))
	    goto ret0 ;

	rs = rs1 ;
	if (rs < 0)
	    goto ret0 ;

	rs = lm_strw(dirname,-1,&qdirp->dirname) ;
	if (rs < 0)
	    goto bad0 ;

	basedname = dirname ;
	rs1 = textlook_open(&qdirp->looker,op->pr,dbname,basedname) ;
	f_textlook = (rs1 >= 0) ;
	if (rs1 == SR_NOENT) {
	    f_remake = true ;
	} else
	    rs = rs1 ;

	if (rs < 0)
	    goto bad1 ;

	if (! f_remake) {

	    rs = textlook_info(&qdirp->looker,&binfo) ;

	    if (rs >= 0) {
		mtime = binfo.mtime ;
	        rs = qdir_newer(qdirp,dirname,mtime) ;
		f_remake = (rs > 0) ;
	    }

	} /* end if */

	if (rs < 0)
	    goto bad2 ;

	if (f_remake) {
	    if (f_textlook) {
		f_textlook = false ;
	        textlook_close(&qdirp->looker) ;
	    }
	    rs = qdir_remake(qdirp,sip,dbname,basedname) ;
	    if (rs >= 0) {
	        rs = textlook_open(&qdirp->looker,op->pr,dbname,basedname) ;
		f_textlook = (rs >= 0) ;
	    }
	}

	if (rs < 0)
	    goto bad2 ;

ret0:
	return rs ;

/* bad stuff */
bad2:
	if (f_textlook) {
		f_textlook = false ;
	        textlook_close(&qdirp->looker) ;
	}

bad1:
	lm_free(qdirp->dirname) ;

bad0:
	goto ret0 ;
}
/* end subroutine (qdir_open) */


local int qdir_close(qdirp)
QDIR		*qdirp ;
{
	int	rs ;


	rs = textlook_close(&qdirp->looker) ;

	if (qdirp->dirname != nullptr) {
	    lm_free(qdirp->dirname) ;
	    qdirp->dirname = nullptr ;
	}

	return rs ;
}
/* end subroutine (qdir_close) */


local int qdir_dbdir(qdirp,sip,dbdname)
QDIR		*qdirp ;
DI	*sip ;
cchar	dbdname[] ;
{
	ustat	sb ;

	cint	dmode = QDIR_DBDIRMODE ;

	int	rs = SR_OK ;
	int	rs1 ;


	rs = u_stat(dbdname,&sb) ;

	if ((rs >= 0) && (! S_ISDIR(sb.st_mode)))
	    rs = SR_NOTDIR ;

	if (rs == SR_NOENT) {
	    dmode |= 0755 ;
	    rs = u_mkdir(dbdname,dmode) ;
	    if (rs >= 0) {
		qdirp->fl.writedbdir = true :
		rs = uc_minmod(dbdname,dmode) ;
	    }
	}

	if ((rs >= 0) && (! qdirp->fl.writedbdir)) {
	    rs = subinfo_ids(sip) ;
	    if (rs >= 0) {
	        rs1 = permids(&sip->id,&sb,W_OK) ;
		qdirp->fl.writedbdir = (rs1 >= 0) ;
	    }
	}

ret0:
	return rs ;
}
/* end subroutine (qdir_dbdir) */


local int qdir_newer(qdirp,dirname,mtime)
QDIR		*qdirp ;
cchar	dirname[] ;
time_t		mtime ;
{
	ustat	sb ;

	FSDIR		d ;

	FSDIR_ENT	de ;

	time_t		mtime = 0 ;

	int	rs = SR_OK ;
	int	rs1 ;
	int	f_dbdir = false ;
	int	f_newer = false ;

	cchar	*dbdir = QDIR_DBDIR ;
	cchar	*denp ;

	char	fname[MAXPATHLEN + 1] ;


	if (dirname[0] == '\0')
	    return SR_NOENT ;

	if ((rs = fsdir_open(&d,dirname)) >= 0) {

	    while (fsdir_read(&d,&de) > 0) {

	        denp = de.name ;
	        if (! f_dbdir) {
	            if (strcmp(denp,dbdir) == 0) 
		        f_dbdir = true ;
	        }

	        if (denp[0] == '.') continue ;

	        rs1 = mkpath2(fname,dirname,denp) ;
	        if (rs1 >= 0) {
	            rs1 = u_stat(fname,&sb) ;
		    if ((rs1 >= 0) && (! S_ISDIR(sb.st_mode))) {
		         if (sb.st_mtime > mtime) {
			    f_newer = true ;
			    break ;
		         }
		    }
	        }

	    } /* end while (reading directory entries) */

	    fsdir_close(&d) ;

	} /* end if (directory traversal) */

ret0:
	return (rs >= 0) ? f_newer : rs ;
}
/* end subroutine (qdir_newer) */


local int qdir_remake(qdirp,sip,dbname,basedname) ;
QDIR		*qdirp ;
DI	*sip ;
cchar	dbname[] ;
cchar	basedname[] ;
{
	QUOTE	*op = sip->op ;

	int	rs = SR_OK ;



	return rs ;
}
/* end subroutine (qdir_remake) */


#ifdef	COMMENT

local int cal_open(calp,sip,cidx,dirname,calname)
QU_CAL	*calp ;
DI	*sip ;
int		cidx ;
cchar	dirname[] ;
cchar	calname[] ;
{
	int	rs ;

	memclear(calp) ;
	calp->cidx = cidx ;
	rs = lm_strw(dirname,-1,&calp->dirname) ;
	if (rs < 0)
	    goto bad0 ;

	rs = lm_strw(calname,-1,&calp->calname) ;
	if (rs < 0)
	    goto bad1 ;

	rs = cal_dbloadinit(calp,sip) ;
	if (rs < 0)
	    goto bad2 ;

ret0:
	return rs ;

/* bad stuff */
bad2:
	lm_free(calp->calname) ;

bad1:
	lm_free(calp->dirname) ;

bad0:
	goto ret0 ;
}
/* end subroutine (cal_open) */


local int cal_close(calp)
QU_CAL	*calp ;
{
	int	rs ;


	rs = cal_dbloadfree(calp) ;

	if (calp->calname != nullptr) {
	    lm_free(calp->calname) ;
	    calp->calname = nullptr ;
	}

	if (calp->dirname != nullptr) {
	    lm_free(calp->dirname) ;
	    calp->dirname = nullptr ;
	}

	return rs ;
}
/* end subroutine (cal_close) */


local int cal_dbloadinit(calp,sip)
QU_CAL	*calp ;
DI	*sip ;
{
	int	rs ;


	rs = cal_dbmapcreate(calp,sip->daytime) ;
	if (rs < 0)
	    goto bad0 ;

	rs = cal_indopen(calp,sip) ;
	if (rs < 0)
	    goto bad1 ;

ret0:
	return rs ;

/* bad stuff */
bad1:
	cal_dbmapdestroy(calp) ;

bad0:
	goto ret0 ;
}
/* end subroutine (cal_dbloadinit) */


local int cal_dbloadfree(calp)
QU_CAL	*calp ;
{
	int	rs = SR_OK ;
	int	rs1 ;


	rs1 = cal_indclose(calp) ;
	if (rs >= 0) rs = rs1 ;

	rs1 = cal_dbmapdestroy(calp) ;
	if (rs >= 0) rs = rs1 ;

	return rs ;
}
/* end subroutine (cal_dbloadfree) */


local int cal_dbmapcreate(calp,daytime)
QU_CAL	*calp ;
time_t		daytime ;
{
	ustat	sb ;

	int	rs = SR_OK ;
	int	fd ;
	int	mprot, mflags ;

	char	cname[MAXNAMELEN + 1] ;
	char	dbfname[MAXPATHLEN + 1] ;
	char	*mp ;


	rs = snsds(cname,MAXNAMELEN,calp->calname,QUOTE_DBSUF) ;
	if (rs < 0)
	    goto ret0 ;

	rs = mkpath2(dbfname,calp->dirname,cname) ;
	if (rs < 0)
	    goto ret0 ;

/* open it */

	rs = u_open(dbfname,O_RDONLY,0666) ;
	fd = rs ;
	if (rs < 0)
	    goto ret0 ;

	rs = u_fstat(fd,&sb) ;
	if (rs < 0)
	    goto ret1 ;

	if (! S_ISREG(sb.st_mode)) {
	    rs = SR_NOTSUP ;
	    goto ret1 ;
	}

	if ((sb.st_size > INT_MAX) || (sb.st_size < 0)) {
	    rs = SR_TOOBIG ;
	    goto ret1 ;
	}

	calp->filesize = sb.st_size ;
	calp->ti_db = sb.st_mtime ;

/* map it */

	mprot = PROT_READ ;
	mflags = MAP_SHARED ;
	rs = u_mmap(nullptr,(size_t) calp->filesize,mprot,mflags,fd,0L,&mp) ;

	if (rs >= 0) {
	    calp->mapdata = mp ;
	    calp->mapsize = calp->filesize ;
	    calp->ti_map = daytime ;
	    calp->ti_lastcheck = daytime ;
	}

/* close it */
ret1:
	u_close(fd) ;

ret0:
	return rs ;
}
/* end subroutine (cal_dbmapcreate) */


local int cal_dbmapdestroy(calp)
QU_CAL	*calp ;
{
	int	rs = SR_OK ;


	if (calp->mapdata != nullptr) {
	    rs = u_munmap(calp->mapdata,calp->mapsize) ;
	    calp->mapdata = nullptr ;
	    calp->mapsize = 0 ;
	}

	return rs ;
}
/* end subroutine (cal_dbmapdestroy) */


local int cal_indopen(calp,sip)
QU_CAL	*calp ;
DI	*sip ;
{
	int	rs = SR_NOENT ;


	rs = subinfo_year(sip) ; /* the current year is needed later */
	if (rs < 0)
	    goto ret0 ;

	rs = cal_indopenperm(calp,sip) ;

	{
	    int	f = false ;

	    f = f || (rs == SR_ACCESS) ;
	    f = f || (rs == SR_STALE) ;
	    f = f || (rs == SR_NOTDIR) ;
	    f = f || (rs == SR_ROFS) ;
	    if (f) {
	        rs = cal_indopentmp(calp,sip) ;

	    }

	} /* end block */

ret0:
	return rs ;
}
/* end subroutine (cal_indopen) */


local int cal_indopenperm(calp,sip)
QU_CAL	*calp ;
DI	*sip ;
{
	int	rs ;
	int	year = sip->year ;
	int	f_search = false ;
	int	f ;

	cchar	*idxdname = IDXDNAME ;

	char	idname[MAXNAMELEN + 1] ;


	rs = mkpath2(idname,calp->dirname,idxdname) ;
	if (rs < 0)
	    goto ret0 ;

try:
	rs = cal_indopencheck(calp,idname,year,f_search) ;

	if (rs == SR_NOTDIR)
	    rs = cal_mkdirs(calp,idname,QUOTE_DMODE) ;

	f = false ;
	f = f || (rs == SR_NOENT) ;
	f = f || (rs == SR_STALE) ;
	f = f || (rs == SR_NOCSI) ; /* zero sized file */
	if (f) {
	    rs = cal_indmk(calp,sip,idname,f_search,sip->daytime) ;
	    if (rs >= 0)
		rs = cal_indopencheck(calp,idname,year,f_search) ;
	}

ret0:
	return rs ;
}
/* end subroutine (cal_indopenperm) */


local int cal_indopentmp(calp,sip)
QU_CAL	*calp ;
DI	*sip ;
{
	QUOTE	*op = sip->op ;

	int	rs ;
	int	year = sip->year ;
	int	f_search = true ;
	int	f ;

	cchar	*idxdname = IDXDNAME ;

	char	idname[MAXPATHLEN + 1] ;


#if	CF_TMPPRNAME
	{

	    char	*prname ;
	

	    rs = sfbasename(op->pr,-1,&prname) ;

	    if (rs >= 0)
	        rs = mkpath3(idname,op->tmpdname,prname,idxdname) ;

	}
#else /* CF_TMPPRNAME */

	rs = mkpath2(idname,op->tmpdname,idxdname) ;

#endif /* CF_TMPPRNAME */

	if (rs < 0)
	    goto ret0 ;

try:
	rs = cal_indopencheck(calp,idname,year,f_search) ;

	if (rs == SR_NOTDIR) {

	    rs = cal_mkdirs(calp,idname,QUOTE_DMODE) ;

	}

	f = false ;
	f = f || (rs == SR_NOENT) ;
	f = f || (rs == SR_STALE) ;
	f = f || (rs == SR_NOCSI) ; /* zero sized file */
	if (f) {
	    rs = cal_indmk(calp,sip,idname,f_search,sip->daytime) ;

	    if (rs >= 0) {

		rs = cal_indopencheck(calp,idname,year,f_search) ;

	    }

	} /* end if */

ret0:
	return rs ;
}
/* end subroutine (cal_indopentmp) */


local int cal_mkdirs(calp,dname,mode)
QU_CAL	*calp ;
cchar	dname[] ;
mode_t		mode ;
{
	ustat	sb ;

	int	rs ;


	mode &= S_IAMB ;
	if ((rs = mkdirs(dname,mode)) >= 0) {
	    rs = u_stat(dname,&sb) ;
	    if ((rs >= 0) && ((sb.st_mode & mode) != mode))
		rs = u_chmod(dname,mode) ;
	}

	return rs ;
}
/* end subroutine (cal_mkdirs) */


local int cal_indopencheck(calp,dname,year,f_search)
QU_CAL	*calp ;
cchar	dname[] ;
int		year ;
int		f_search ;
{
	TEXTLOOK_INFO	binfo ;
	int	rs ;
	if ((rs = cyi_open(&calp->vind,dname,calp->calname,f_search)) >= 0) {
	    if ((rs = cyi_info(&calp->vind,&binfo)) >= 0) {
		bool	f = false ;
		f = f || (binfo.ctime < calp->ti_db) ;
		f = f || (binfo.year < year) ;
		if (f) {
		    rs = SR_STALE ;
	            cyi_close(&calp->vind) ;
		}
	    } /* end if (cyi_open) */
	} /* end if */

	calp->fl.vind = (rs >= 0) ;
	return rs ;
}
/* end subroutine (quote_indopencheck) */

#endif /* COMMENT */


local int quote_debugcur(op,rlp,s)
QUOTE		*op ;
vecobj		*rlp ;
cchar	s[] ;
{
	QU_EL	*lines ;

	QU_ENT		*ep ;

	int	rs = SR_OK ;
	int	n ;
	int	i, j ;


	n = vecobj_count(rlp) ;
	debugprintf("quote_debugcur: %s n=%u\n",s,n) ;
	for (i = 0 ; vecobj_get(rlp,i,&ep) >= 0 ; i += 1) {
		lines = ep->lines ;
	   for (j = 0 ; j < ep->i ; j += 1) {
		debugprintf("quote_debugcur: i=%u loff[%u]=%u\n",
			i,j,lines[j].loff) ;
		debugprintf("quote_debugcur: i=%u llen[%u]=%u\n",
			i,j,lines[j].llen) ;
	    }
	} /* end for */

ret0:
	return rs ;
}
/* end subroutine (quote_debugcur) */

#ifdef	COMMENT

local int cal_indmk(calp,sip,dname,f_tmp,daytime)
QU_CAL	*calp ;
DI	*sip ;
cchar	dname[] ;
int		f_tmp ;
time_t		daytime ;
{
	int	rs = SR_OK ;
	int	operms = 0664 ;
	int	c = 0 ;


/* check the given directory for writability */

	rs = subinfo_checkdname(sip,dname) ;

	if (rs == SR_NOENT)
	    rs = mkdirs(dname,0777) ; /* will fail if parent is not writable */

	if (rs < 0)
	    goto ret0 ;

	rs = cal_indmkdata(calp,sip,dname,operms,f_tmp) ;
	c += rs ;

	if (rs >= 0)
	    calp->ti_vind = daytime ;

ret0:
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (cal_indmk) */


local int cal_indmkdata(calp,sip,dname,operms,f_tmp)
QU_CAL	*calp ;
DI	*sip ;
cchar	dname[] ;
int		operms ;
int		f_tmp ;
{
	QU_ENT	e ;

	QU_Q	q ;

	CYIMK		cyind ;

	CYIMK_ENT	bve ;

	uint	fileoff = 0 ;

	int	rs = SR_NOANODE ;
	int	rs1 ;
	int	oflags ;
	int	ml, ll ;
	int	si ;
	int	len ;
	int	cidx ;
	int	year ;
	int	to ;
	int	c = 0 ;
	int	f_ent = false ;
	int	f ;

	cchar	*cn ;

	char	*tp, *mp, *lp ;


	if (calp->mapdata == nullptr)
	    goto ret0 ;

	rs = subinfo_year(sip) ;
	if (rs < 0)
	    goto ret0 ;

	rs = cal_idxget(calp) ;
	cidx = rs ;
	if (rs < 0)
	    goto ret0 ;

	cn = calp->calname ;
	oflags = 0 ;
	year = sip->year ;
	rs = cyimk_open(&cyind,dname,cn,oflags,operms,year,f_tmp) ;
	if (rs == SR_INPROGRESS)
	    goto retinprogress ;

	if (rs < 0)
	    goto ret0 ;

mkgo:
	mp = calp->mapdata ;
	ml = calp->mapsize ;

	while ((tp = strnchr(mp,ml,'\n')) != nullptr) {

	    len = ((tp + 1) - mp) ;
	    lp = mp ;
	    ll = (len - 1) ;

	    if (! isempty(lp,ll)) {

	        rs1 = subinfo_havestart(sip,&q,lp,ll) ;
		si = rs1 ;

		if (rs1 > 0) { /* start (proper) */

	            if (f_ent) {
	                c += 1 ;
	                if ((rs = mkbve_start(&bve,sip,&e)) >= 0) {
	                    rs = cyimk_add(&cyind,&bve) ;
			    mkbve_finish(&bve) ;
		        }
			f_ent = false ;
			entry_finish(&e) ;
	            }

	            if (rs >= 0) {
	                rs = entry_start(&e,&q,(fileoff + si),(ll - si)) ;
			if (rs >= 0) {
	                    f_ent = true ;
			    rs = entry_setidx(&e,cidx) ;
			}
		    }

	        } else if (rs1 == 0) { /* continuation */

		    if (f_ent)
	                rs = entry_add(&e,fileoff,ll) ;

		} else { /* bad */

		    f = false ;
		    f = f || (rs1 == SR_NOENT) || (rs == SR_NOTFOUND) ;
		    f = f || (rs1 == SR_ILSEQ) ;
		    f = f || (rs1 == SR_INVALID) ;
		    f = f || (rs1 == SR_NOTSUP) ;

	            if (f && f_ent) {
	                c += 1 ;
	                if ((rs = mkbve_start(&bve,sip,&e)) >= 0) {
	                    rs = cyimk_add(&cyind,&bve) ;
			    mkbve_finish(&bve) ;
		        }
			f_ent = false ;
			entry_finish(&e) ;
	            }

	        } /* end if (entry start of add) */

	    } else {

#if	CF_EMPTYTERM
	        if (f_ent) {
	            c += 1 ;
	            if ((rs = mkbve_start(&bve,sip,&e)) >= 0) {
	                rs = cyimk_add(&cyind,&bve) ;
		        mkbve_finish(&bve) ;
		    }
	            f_ent = false ;
	  	    entry_finish(&e) ;
	        }
#else
		rs = SR_OK ;
#endif /* CF_EMPTYTERM */

	    } /* end if (not empty) */

	    if (rs < 0)
	        break ;

	    fileoff += len ;
	    ml -= len ;
	    mp += len ;

	} /* end while (readling lines) */

	if ((rs >= 0) && f_ent) {
	    c += 1 ;
	    if ((rs = mkbve_start(&bve,sip,&e)) >= 0) {
	        rs = cyimk_add(&cyind,&bve) ;
		mkbve_finish(&bve) ;
	    }
	    f_ent = false ;
	    entry_finish(&e) ;
	}

	if (f_ent) {
	    f_ent = false ;
	    entry_finish(&e) ;
	}

ret1:
	rs1 = cyimk_close(&cyind) ;
	if (rs >= 0) rs = rs1 ;

ret0:
	return (rs >= 0) ? c : rs ;

retinprogress:
	rs1 = SR_EXIST ;
	cn = calp->calname ;
	oflags = (O_CREAT | O_EXCL) ;
	for (to = 0 ; to < TO_MKWAIT ; to += 1) {
	    sleep(1) ;
	    rs1 = cyimk_open(&cyind,dname,cn,oflags,operms,year,f_tmp) ;
	    if ((rs1 >= 0) || (rs1 == SR_EXIST))
		break ;
	} /* end while */

	if (to < TO_MKWAIT) {
	    if (rs1 >= 0)
		goto mkgo ;
	    rs = rs1 ;
	} else
	    rs = SR_TIMEDOUT ;

	goto ret0 ;
}
/* end subroutine (cal_indmkdata) */


local int cal_indclose(calp)
QU_CAL	*calp ;
{
	int	rs = SR_OK ;


	if (calp->fl.vind) {
	    calp->fl.vind = false ;
	    rs = cyi_close(&calp->vind) ;
	}

	return rs ;
}
/* end subroutine (cal_indclose) */

#endif /* COMMENT */


#ifdef	COMMENT

local int cal_idxset(calp,cidx)
QU_CAL	*calp ;
int		cidx ;
{


	calp->cidx = cidx ;
	return SR_OK ;
}
/* end subroutine (cal_idxset) */

#endif /* COMMENT */


#ifdef	COMMENT

local int cal_idxget(calp)
QU_CAL	*calp ;
{
	int	cidx = calp->cidx ;


	return cidx ;
}
/* end subroutine (cal_idxget) */


local int cal_audit(calp)
QU_CAL	*calp ;
{
	int	rs = SR_OK ;


	rs = cyi_audit(&calp->vind) ;

	return rs ;
}
/* end subroutine (cal_audit) */


local int cal_loadbuf(calp,ep,rbuf,rlen)
QU_CAL	*calp ;
QU_ENT	*ep ;
char		rbuf[] ;
int		rlen ;
{
	int	rs ;

	cchar	*mp ;


	rs = cal_mapdata(calp,&mp) ;
	if (rs < 0)
	    goto ret0 ;

	rs = entry_loadbuf(ep,mp,rbuf,rlen) ;

ret0:
	return rs ;
} 
/* end subroutine (cal_loadbuf) */


local int cal_mapdata(calp,mpp)
QU_CAL	*calp ;
cchar	**mpp ;
{
	int	rs ;


	if (mpp != nullptr)
	    *mpp = calp->mapdata ;

	rs = calp->mapsize ;
	return rs ;
}
/* end subroutine (cal_mapdata) */

#endif /* COMMENT */


local int subinfo_start(sip,op,daytime,dirnames)
DI	*sip ;
QUOTE		*op ;
time_t		daytime ;
cchar	*dirnames[] ;
{
	int	rs = SR_OK ;


	if (daytime == 0)
	    daytime = time(nullptr) ;

	memclear(sip) ;

	sip->op = op ;
	sip->daytime = daytime ;

	sip->tmpdname = getenv(VARTMPDNAME) ;
	if (sip->tmpdname == nullptr)
	    sip->tmpdname = TMPDNAME ;

	if ((dirnames == nullptr) || (dirnames[0] == nullptr)) {
	    rs = subinfo_mkdirnames(sip) ;
	} else
	    sip->dirnames = op->dirnames ;

	return rs ;
}
/* end subroutine (subinfo_start) */


local int subinfo_mkdirnames(sip)
DI	*sip ;
{
	QUOTE	*op = sip->op ;

	int	rs = SR_OK ;
	int	tl ;
	int	c = 0 ;

	cchar	*sharedname = QDIR_QUOTES ;

	char	tmpdname[MAXPATHLEN + 1] ;


	rs = subinfo_username(sip) ;
	if (rs < 0)
	    goto ret0 ;

	rs = vecstr_start(&sip->defdirs,0,0) ;
	sip->fl.defdirs = (rs >= 0) ;
	if (rs < 0)
	    goto ret0 ;

/* user-home area */

	if (rs >= 0) {

	    rs = mkpath2(tmpdname,sip->userhome,sharedname) ;
	    tl = rs ;
	    if (rs >= 0) {
	        rs = subinfo_havedir(sip,tmpdname) ;
	        if (rs > 0) {
		    c += 1 ;
	            rs = vecstr_add(&sip->defdirs,tmpdname,tl) ;
	        }
	    }

	} /* end if */

/* system area */

	if (rs >= 0) {

	    rs = mkpath2(tmpdname,op->pr,sharedname) ;
	    tl = rs ;
	    if (rs >= 0) {
	        rs = subinfo_havedir(sip,tmpdname) ;
	        if (rs > 0) {
		    c += 1 ;
	            rs = vecstr_add(&sip->defdirs,tmpdname,tl) ;
	        }
	    }

	} /* end if */

/* finish */

	if (rs >= 0) {
	    cchar	**dap ;
	    rs = vecstr_getvec(&sip->defdirs,&dap) ;
	    if (rs >= 0)
	        sip->dirnames = (cchar **) dap ;
	}

ret1:
	if (rs < 0) {
	    if (sip->fl.defdirs) {
		sip->fl.defdirs = false ;
		vecstr_finish(&sip->defdirs) ;
	    }
	}

ret0:
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (subinfo_mkdirnames) */


local int subinfo_havedir(sip,tmpdname)
DI	*sip ;
char		tmpdname[] ;
{
	ustat	sb ;

	int	rs = SR_OK ;
	int	rs1 ;
	int	f = false ;


	rs1 = u_stat(tmpdname,&sb) ;
	if (rs1 >= 0)
	    f = S_ISDIR(sb.st_mode) ? 1 : 0 ;

ret0:
	return (rs >= 0) ? f : rs ;
}
/* end subroutine (subinfo_havedir) */


local int subinfo_ids(sip)
DI	*sip ;
{
	int	rs = SR_OK ;


	if (! sip->fl.id) {
	    sip->fl.id = true ;
	    rs = ids_load(&sip->id) ;
	}

	return rs ;
}
/* end subroutine (subinfo_ids) */


local int subinfo_finish(sip)
DI	*sip ;
{
	int		rs = SR_OK ;
	int		rs1 ;

	if (sip->fl.hols) {
	    sip->fl.hols = false ;
	    rs1 = holidays_close(&sip->hols) ;
	    if (rs >= 0) rs = rs1 ;
	}

	if (sip->fl.dom) {
	    sip->fl.dom = false ;
	    rs1 = dayofmonth_finish(&sip->dom) ;
	    if (rs >= 0) rs = rs1 ;
	}

	if (sip->fl.defdirs) {
	    sip->fl.defdirs = false ;
	    rs1 = vecstr_finish(&sip->defdirs) ;
	    if (rs >= 0) rs = rs1 ;
	}

	if (sip->tudname != nullptr) {
	    rs1 = lm_free(sip->tudname) ;
	    if (rs >= 0) rs = rs1 ;
	    sip->tudname = nullptr ;
	}

	if (sip->userhome != nullptr) {
	    rs1 = lm_free(sip->userhome) ;
	    if (rs >= 0) rs = rs1 ;
	    sip->userhome = nullptr ;
	}

	if (sip->fl.id) {
	    rs1 = ids_release(&sip->id) ;
	    if (rs >= 0) rs = rs1 ;
	    sip->fl.id = false ;
	}

	return rs ;
}
/* end subroutine (subinfo_finish) */


local int subinfo_username(sip)
DI	*sip ;
{
	int		rs = SR_OK ;

	if (sip->username[0] == '\0') {
	    ucentpw	pw ;
	    cint	pwlen = bufsizeget(bufsize_pw) ;
	    char	*pwbuf ;
	    if ((rs = lm_mall((pwlen+1),&pwbuf)) >= 0) {
	        if ((rs = getpwusername(&pw,pwbuf,pwlen,-1)) >= 0) {
	            char	*ap ;
		    strwcpy(sip->username,pw.pw_name,USERNAMELEN) ;
		    if ((rs = lm_strw(pw.pw_dir,-1,&ap)) >= 0) {
		        sip->userhome = ap ;
		    }
		}
		lm_free(pwbuf) ;
	    } /* end if (memory-allocation) */
	} /* end if (needed) */

	return rs ;
}
/* end subroutine (subinfo_username) */


local int subinfo_tmpuserdir(sip)
DI	*sip ;
{
	cint	dmode = 0775 ;
	int	rs ;
	int	dl ;
	char	tmpdname[MAXPATHLEN + 1] ;
	char	*dp ;

	rs = subinfo_username(sip) ;

	if ((rs >= 0) && (sip->tudname == nullptr)) {
	    rs = mktmpuserdir(tmpdname,sip->username,IDXDNAME,dmode) ;
	    dl = rs ;
	    if (rs >= 0) {
	        rs = lm_strw(tmpdname,dl,&dp) ;
		if (rs >= 0) {
		    sip->tudname = dp ;
		}
	    }
	} /* end if */

	return rs ;
}
/* end subroutine (subinfo_tmpuserdir) */


local int subinfo_loadnames(sip,nlp,dirname)
DI	*sip ;
vecstr		*nlp ;
cchar	dirname[] ;
{
	ustat	sb ;

	FSDIR		dir ;

	FSDIR_ENT	ds ;

	int	rs = SR_OK ;
	int	rs1 ;
	int	nl ;
	int	c = 0 ;

	cchar	*calsuf = QUOTE_DBSUF ;
	cchar	*tp ;
	cchar	*np ;

	char	tmpfname[MAXPATHLEN + 1] ;

	rs = fsdir_open(&dir,dirname) ;
	if (rs < 0)
	    goto ret0 ;

	while (fsdir_read(&dir,&ds) > 0) {
	    if (ds.name[0] == '.') continue ;

	    if (strchr(ds.name,'.') != nullptr) continue ; /* just plain names */

	    rs1 = mkpath2(tmpfname,dirname,ds.name) ;

	    if (rs1 >= 0)
	        rs1 = u_stat(ds.name,&db) ;

	    if ((rs1 >= 0) && S_ISREG(sb.st_mode)) {

		    c += 1 ;
		    rs = vecstr_add(nlp,ds.name,-1) ;
	            if (rs < 0)
		        break ;

	    } /* end if (regular file) */

	} /* end while */

ret1:
	fsdir_close(&dir) ;

ret0:
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (subinfo_loadnames) */


local int subinfo_havestart(sip,qp,lp,ll)
DI	*sip ;
QUOTE_CITE	*qp ;
cchar	*lp ;
int		ll ;
{
	int		rs1 = SR_OK ;
	int		ch ;
	int		cl ;
	int		si = 0 ;
	int		f ;
	cchar		*tp, *cp ;

	if (CHAR_ISWHITE(lp[0])) /* continuation */
	    goto ret0 ;

	si = sibrk(lp,ll," \t") ;
	if (si < 3) {
	    rs1 = SR_ILSEQ ;
	    goto ret1 ;
	}

	ch = MKCHAR(lp[0]) ;
	if (isdigitlatin(ch)) {

	    tp = strnchr(lp,ll,'/') ;
	    if (tp != nullptr) {

	        rs1 = mkmonth(lp,(tp - lp)) ;
	        qp->m = (rs1 & UCHAR_MAX) ;

		if (rs1 >= 0) {
	            cp = (tp + 1) ;
	            cl = ((lp + ll) - cp) ;
		    if ((tp = strnbrk(cp,cl," \t")) != nullptr)
			cl = (tp - cp) ;

	            rs1 = subinfo_mkday(sip,qp->m,cp,cl) ;
	            qp->d = (rs1 & UCHAR_MAX) ;

		} else {

		    f = false ;
		    f = f || (rs1 == SR_INVALID) ;
		    if (f)
			rs1 = SR_ILSEQ ;

	        } /* end if */

	    } else
		rs1 = SR_ILSEQ ;

	} else {

		rs1 = SR_NOTSUP ;

	} /* end if */

	if (rs1 >= 0)
	    si += siskipwhite((lp+si),(ll-si)) ;

ret1:
ret0:
	return (rs1 >= 0) ? si : rs1 ;
}
/* end subroutine (subinfo_havestart) */


local int subinfo_year(sip)
DI	*sip ;
{
	TMTIME	tm ;

	int	rs = SR_OK ;


	if (sip->year == 0) {
	    rs = tmtime_timelocal(&tm,sip->daytime) ;
	    sip->year = (tm.year + TMTIME_YEARBASE) ;
	    sip->isdst = tm.tm_isdst ;
	    sip->gmtoff = tm.gmtoff ;
	}

	return rs ;
}
/* end subroutine (subinfo_year) */


#ifdef	COMMENT

local int subinfo_mkday(sip,m,cp,cl)
DI	*sip ;
int		m ;
cchar	*cp ;
int		cl ;
{
	DAYOFMONTH	*dmp ;

	int	rs = SR_OK ;


	dmp = &sip->dom ;

/* open the DAYOFMONTH database (manager?) if it is not already open */

	if (! sip->fl.dom) {
	    rs = dayofmonth_start(dmp,sip->year) ;
	    sip->fl.dom = (rs >= 0) ;
	}

	if (rs >= 0)
	    rs = dayofmonth_mkday(dmp,m,cp,cl) ;

	return rs ;
}
/* end subroutine (subinfo_mkday) */


local int subinfo_transhol(sip,qp,sp,sl)
DI	*sip ;
QUOTE_CITE	*qp ;
cchar	*sp ;
int		sl ;
{
	HOLIDAYS_CUR	hcur ;

	HOLIDAYS	*holp ;

	QUOTE		*op ;

	TMTIME		tm ;

	int	rs = SR_OK ;
	int	nl ;
	int	f_negative = false ;
	int	f_inityear = false ;
	int	f_found = false ;
	int	f ;

	cchar	*tp ;
	cchar	*np ;

	op = sip->op ;

	qp->m = 0 ;
	qp->d = 0 ;

	np = nullptr ;
	nl = 0 ;
	if ((tp = strnbrk(sp,sl,"+-")) != nullptr) {
		np = (tp + 1) ;
		nl = (sl - ((tp + 1) - sp)) ;
		sl = (tp - sp) ;
		f_negative = (tp[0] == '-') ;
	}

	if (sl == 0) {
	    rs = SR_ILSEQ ;
	    goto ret0 ;
	}

	holp = &sip->hols ;

/* open the HOLIDAYS database if it is not already open */

	if (! sip->init.hols) {
	    sip->init.hols = true ;
	    f_inityear = true ;
	    rs = subinfo_year(sip) ;
	    if (rs >= 0) {
	        rs = holidays_open(holp,op->pr,sip->year,nullptr) ;
	        sip->fl.hols = (rs >= 0) ;

	 	f = false ;
		f = f || (rs == SR_BADFMT) ;
		f = f || (rs == SR_NOMSG) ;
		if (f)
		    rs = SR_NOENT ;
	    }
	} /* end if (open database as necessary) */

	if ((rs >= 0) && sip->fl.hols) {
	    HOLIDAYS_CITE	hc ;
	    char	holbuf[HOLBUFLEN + 1] ;

	    holidays_curbegin(holp,&hcur) ;
	
	    rs = holidays_fetchname(holp,sp,sl,&hcur,&hc,holbuf,HOLBUFLEN) ;
	    if (rs >= 0) {
		f_found = true ;
		qp->m = hc.m ;
		qp->d = hc.d ;
	    }

	    holidays_curend(holp,&hcur) ;

	} /* end if */

	if ((rs >= 0) && f_found && (nl > 0)) {

	    if (! f_inityear)
		rs = subinfo_year(sip) ;

	    if (rs >= 0) {
		int	odays ;

		rs = cfdeci(np,nl,&odays) ;

		if (rs >= 0) {
		    time_t	t ;

		    if (f_negative) odays = (- odays) ;

		    memclear(&tm) ;
		    tm.gmtoff = sip->gmtoff ;
		    tm.isdst = sip->isdst ;
		    tm.year = (sip->year - TMTIME_YEARBASE) ;
		    tm.mon = qp->m ;
		    tm.mday = (qp->d + odays) ;
		    rs = tmtime_adjtime(&tm,&t) ;

		    if (rs >= 0) {
			qp->m = tm.mon ;
			qp->d = tm.mday ;
		    }

		} /* end if (odays) */

	    } /* end if (got year) */

	} /* end if (day offset required) */

ret0:
	return (rs >= 0) ? f_found : rs ;
}
/* end subroutine (subinfo_transhol) */

#endif /* COMMENT */


local int subinfo_checkdname(sip,dname)
DI	*sip ;
cchar	dname[] ;
{
	ustat	sb ;

	int	rs = SR_OK ;


	if (dname[0] != '/') {
	    rs = SR_INVALID ;
	    goto ret0 ;
	}

	rs = u_stat(dname,&sb) ;

	if ((rs >= 0) && (! S_ISDIR(sb.st_mode)))
	    rs = SR_NOTDIR ;

	if (rs >= 0) {
	    rs = subinfo_ids(sip) ;
	    if (rs >= 0)
	        rs = permids(&sip->id,&sb,W_OK) ;
	}

ret0:
	return rs ;
}
/* end subroutine (subinfo_checkdname) */


local int entry_start(ep,qp,loff,llen)
QU_ENT	*ep ;
QUOTE_CITE	*qp ;
int		loff, llen ;
{
	QU_EL	*elp ;

	int	rs = SR_OK ;
	int	ne = QUOTE_NLE ;
	int	sz ;


	if (ep == nullptr)
	    return SR_FAULT ;

	memclear(ep) ;

	ep->cidx = -1 ;
	ep->m = qp->m ;
	ep->d = qp->d ;
	ep->voff = loff ;
	ep->vlen = llen ;
	sz = ne * szof(QU_EL) ;
	if ((rs = lm_mall(sz,&elp)) >= 0) {
	    ep->lines = elp ;
	    ep->e = ne ;
	    elp->loff = loff ;
	    elp->llen = llen ;
	    ep->i += 1 ;
	} /* end if (memory-allocation) */

	return rs ;
}
/* end subroutine (entry_start) */


local int entry_setidx(ep,cidx)
QU_ENT	*ep ;
int		cidx ;
{


	if (ep == nullptr)
	    return SR_FAULT ;

	ep->cidx = cidx ;
	return SR_OK ;
}

/* end subroutine (entry_setidx) */


local int entry_add(ep,loff,llen)
QU_ENT	*ep ;
uint		loff, llen ;
{
	QU_EL	*elp ;

	int	rs = SR_OK ;
	int	ne ;
	int	sz ;


	if (ep == nullptr)
	    return SR_FAULT ;

	if (ep->e <= 0)
	    return SR_NOTOPEN ;

	if ((ep->i < 0) || (ep->i > ep->e))
	    return SR_BADFMT ;

	if (ep->i == ep->e) {
	    ne = (ep->e * 2) + QUOTE_NLE ;
	    sz = ne * szof(QU_EL) ;
	    rs = uc_realloc(ep->lines,sz,&elp) ;
	    if (rs >= 0) {
	        ep->e = ne ;
	        ep->lines = elp ;
	    }
	}

	if (rs >= 0) {
	    ep->vlen = ((loff + llen) - ep->voff) ;
	    elp = (ep->lines + ep->i) ;
	    elp->loff = loff ;
	    elp->llen = llen ;
	    ep->i += 1 ;
	}

	return rs ;
}
/* end subroutine (entry_add) */


#ifdef	COMMENT

local int entry_release(ep)
QU_ENT	*ep ;
{


	if (ep == nullptr)
	    return SR_FAULT ;

	if (ep->e <= 0)
	    return SR_NOTOPEN ;

	if ((ep->i < 0) || (ep->i > ep->e))
	    return SR_BADFMT ;

	ep->i = 0 ;
	ep->lines = nullptr ;
	return SR_OK ;
}
/* end subroutine (entry_release) */

#endif /* COMMENT */


local int entry_finish(ep)
QU_ENT	*ep ;
{
	int		rs = SR_OK ;
	int		rs1 ;

	if (ep == nullptr)
	    return SR_FAULT ;

	if (ep->e <= 0)
	    return SR_NOTOPEN ;

	if ((ep->i < 0) || (ep->i > ep->e))
	    return SR_BADFMT ;

	if (ep->lines != nullptr) {
	    rs1 = lm_free(ep->lines) ;
	    if (rs >= 0) rs = rs1 ;
	    ep->lines = nullptr ;
	}

	ep->i = 0 ;
	ep->e = 0 ;
	return rs ;
}
/* end subroutine (entry_finish) */


#if	CF_SAMECITE

local int entry_samecite(ep,oep)
QU_ENT	*ep ;
QU_ENT	*oep ;
{
	int	rs1 = SR_OK ;


	if ((ep->m == oep->m) && (ep->d == oep->d))
	    rs1 = 1 ;

	return rs1 ;
}
/* end subroutine (entry_samecite) */

#endif /* CF_SAMECITE */


local int entry_samehash(ep,op,oep)
QU_ENT	*ep ;
QUOTE	*op ;
QU_ENT	*oep ;
{
	int	rs = SR_OK ;


/* the following checks (code) is not needed in the present implementation! */

	if ((rs >= 0) && (! ep->fl.hash))
	   rs = entry_mkhash(ep,op) ;

	if ((rs >= 0) && (! oep->fl.hash))
	   rs = entry_mkhash(oep,op) ;

/* we continue with the real (needed) work here */

	if (rs >= 0)
	    rs = (ep->hash == oep->hash) ? 1 : 0 ;

	return rs ;
}
/* end subroutine (entry_samehash) */


local int entry_mkhash(ep,op)
QU_ENT	*ep ;
QUOTE	*op ;
{
	QU_EL	*elp ;

	QU_CAL	*calp ;

	uint	hash ;

	int	rs = SR_OK ;
	int	i ;
	int	sl, cl ;

	cchar	*sp ;
	cchar	*mp ;

	char	*cp ;


	if (ep == nullptr)
	    return SR_FAULT ;

	if (ep->e <= 0)
	    return SR_NOTOPEN ;

	if (ep->lines == nullptr)
	    return SR_NOTOPEN ;

	rs = vechand_get(&op->cals,ep->cidx,&calp) ;
	if (rs >= 0)
	    rs = cal_mapdata(calp,&mp) ;

	if (rs < 0)
	    goto ret0 ;

	elp = ep->lines ;
	hash = 0 ;
	for (i = 0 ; i < ep->i ; i += 1) {
	    sp = (mp + elp[i].loff) ;
	    sl = elp[i].llen ;
	    while ((cl = sfnext(sp,sl,&cp)) > 0) {
		hash += hash_elf(cp,cl) ;
		sl -= ((cp + cl) - sp) ;
		sp = (cp + cl) ;
	    } /* end while */
	} /* end for */

	ep->hash = hash ;
	ep->fl.hash = true ;

ret0:
	return rs ;
}
/* end subroutine (entry_mkhash) */


local int entry_sethash(ep,hash)
QU_ENT	*ep ;
uint		hash ;
{


	ep->hash = hash ;
	ep->fl.hash = true ;
	return SR_OK ;
}
/* end subroutine (entry_sethash) */


local int entry_same(ep,op,oep)
QU_ENT	*ep ;
QUOTE		*op ;
QU_ENT	*oep ;
{
	WR	w1, w2 ;

	int	rs = SR_OK ;
	int	c1l, c2l ;
	int	f = false ;

	cchar	*c1p, *c2p ;


	rs = worder_start(&w1,op,ep) ;
	if (rs < 0)
	    goto bad0 ;

	rs = worder_start(&w2,op,oep) ;
	if (rs < 0)
	    goto bad1 ;

	while ((rs >= 0) && (! f)) {

	    c1l = worder_get(&w1,&c1p) ;

	    c2l = worder_get(&w2,&c2p) ;

	    if (c1l != c2l)
		break ;

	    if ((c1l == 0) && (c2l == 0)) {
		f = true ;
		break ;
	    }

	    if (c1p[0] != c2p[0])
		break ;

	    if (strncmp(c1p,c2p,c1l) != 0)
		break ;

	} /* end while */

	worder_finish(&w2) ;

	worder_finish(&w1) ;

ret0:
	return (rs >= 0) ? f : rs ;

/* bad stuff (of course!) :-) */
bad1:
	worder_finish(&w1) ;

bad0:
	goto ret0 ;
}
/* end subroutine (entry_same) */


local int entry_loadbuf(ep,mp,rbuf,rlen)
QU_ENT	*ep ;
cchar	*mp ;
char		rbuf[] ;
int		rlen ;
{
	QU_EL	*lines ;
	sbuf		b ;
	int		rs ;
	int		rs1 ;
	int		i ;
	int		nlines ;
	int		ll ;
	int		len = 0 ;
	cchar	*lp ;

	lines = ep->lines ;
	nlines = ep->i ; /* number of line elements */

	if ((rs = sbuf_start(&b,rbuf,rlen)) >= 0) {

	for (i = 0 ; i < nlines ; i += 1) {

	    if (i > 0)
		sbuf_chr(&b,' ') ;

	    lp = (mp + lines[i].loff) ;
	    ll = lines[i].llen ;

	    rs = sbuf_strw(&b,lp,ll) ;
	    if (rs < 0)
	        break ;

	} /* end for */

	len = sbuf_finish(&b) ;
	if (rs >= 0) rs = len ;
	} /* end if (sbuf) */

	return (rs >= 0) ? len : rs ;
} 
/* end subroutine (entry_loadbuf) */


#ifdef	COMMENT

local int mkbve_start(bvep,sip,ep)
CYIMK_ENT	*bvep ;
DI	*sip ;
QU_ENT	*ep ;
{
	CYIMK_LINE	*lines ;

	uint	nlines = 0 ;

	int	rs = SR_OK ;
	int	sz ;
	int	i ;


	if (ep == nullptr)
	    return SR_FAULT ;

	rs = entry_mkhash(ep,sip->op) ;
	if (rs < 0)
	    goto ret0 ;

	bvep->m = ep->m ;
	bvep->d = ep->d ;
	bvep->voff = ep->voff ;
	bvep->vlen = ep->vlen ;
	bvep->hash = ep->hash ;
	bvep->lines = nullptr ;

	nlines = ep->i ;
	if (nlines <= UCHAR_MAX) {

	    bvep->nlines = nlines ;
	    sz = (nlines + 1) * szof(CYIMK_LINE) ;
	    rs = lm_mall(sz,&lines) ;
	    if (rs >= 0) {

		bvep->lines = lines ;
	        for (i = 0 ; i < nlines ; i += 1) {
		    lines[i].loff = ep->lines[i].loff ;
		    lines[i].llen = ep->lines[i].llen ;
	        }
		lines[i].loff = 0 ;
		lines[i].llen = 0 ;

	    } /* end if (memory-allocation) */

	} else {
	    rs = SR_TOOBIG ;
	}

ret0:
	return (rs >= 0) ? nlines : rs ;
}
/* end subroutine (mkbve_start) */


local int mkbve_finish(bvep)
CYIMK_ENT	*bvep ;
{
	int		rs = SR_OK ;
	int		rs1 ;

	if (bvep == nullptr)
	    return SR_FAULT ;

	if (bvep->lines != nullptr) {
	    rs1 = lm_free(bvep->lines) ;
	    if (rs >= 0) rs = rs1 ;
	    bvep->lines = nullptr ;
	}

	return rs ;
}
/* end subroutine (mkbve_finish) */

#endif /* COMMENT */


int worder_start(wp,op,ep)
WR		*wp ;
QUOTE	*op ;
QU_ENT	*ep ;
{
	QU_EL	*lines ;
	QU_CAL	*calp ;
	int	rs ;
	cchar	*mp ;

	rs = vechand_get(&op->cals,ep->cidx,&calp) ;
	if (rs >= 0)
	    rs = cal_mapdata(calp,&mp) ;

	if (rs < 0)
	    goto ret0 ;

	wp->i = 0 ;
	lines = ep->lines ;
	wp->nlines = ep->i ;
	wp->lines = ep->lines ;
	wp->mp = mp ;
	if (lines != nullptr) {
	    wp->sp = (mp + lines[0].loff) ;
	    wp->sl = (lines[0].llen) ;
	}

ret0:
	return rs ;
}
/* end subroutine (worder_start) */

int worder_finish(WR *wp) noex {
	return SR_OK ;
}
/* end subroutine (worder_finish) */

int worder_get(WR *wp,cc **rpp) noex {
	int		cl = 0 ; /* return-value */
	char		*cp ;
	while (wp->i < wp->nlines) {

	    if ((cl = sfnext(wp->sp,wp->sl,&cp)) > 0) {
		wp->sl -= ((cp + cl) - wp->sp) ;
		wp->sp = (cp + cl) ;
		break ;
	    }

	    wp->i += 1 ;
	    if (wp->i < wp->nlines) {
	        wp->sp = (wp->mp + wp->lines[wp->i].loff) ;
	        wp->sl = (wp->lines[wp->i].llen) ;
	    }

	} /* end while */
	if (rpp) {
	    *rpp = cp ;
	}
	return cl ;
}
/* end subroutine (worder_get) */

static bool isempty(cchar *lp,int ll) noex {
	bool		f = false ;
	f = f || (ll == 0) ;
	f = f || (lp[0] == '#') ;
	if ((! f) && CHAR_ISWHITE(*lp)) {
	    int		cl ;
	    cchar	*cp ;
	    cl = sfskipwhite(lp,ll,&cp) ;
	    f = ((cl == 0) || (cp[0] == '#')) ;
	}
	return f ;
}
/* end subroutine (isempty) */

/* for use with |vecobj_sort(3uc)| or similar */
local int vrcmp(cvoid **v1pp,cvoid **v2pp) noex {
	QU_ENT	**e1pp = (QU_ENT **) v1pp ;
	QU_ENT	**e2pp = (QU_ENT **) v2pp ;
	int	rc = 0 ;
	{
	    QU_ENT	*e1p = (QU_ENT *) *e1pp ;
	    QU_ENT	*e2p = (QU_ENT *) *e2pp ;
	    if (e1p || e2p) {
	        rc = +1 ;
	        if (e1p) {
		    rc = -1 ;
		    if (e2p) {
		        if ((rc = (e1p->m - e2p->m)) == 0) {
	    	            rc = (e1p->d - e2p->d) ;
		        }
			rc = (- rc) ;
		    }
	        }
	    }
	} /* end block */
	return rc ;
}
/* end subroutine (vrcmp) */


