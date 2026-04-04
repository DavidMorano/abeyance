/* spellchecks SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* SPELLCHECKS object implementation */
/* version %I% last-modified %G% */

#define	CF_SAFE		1		/* normal safety */
#define	CF_SAFE2	1		/* extra safety */
#define	CF_EMPTYTERM	1		/* terminate entry on empty line */
#define	CF_TMPPRNAME	1		/* put under a PRNAME in /tmp */
#define	CF_SAMECITE	0		/* same entry citation? */
#define	CF_ALREADY	1		/* do not allow duplicate results */
#define	CF_TRANSHOL	1		/* translate holidays */
#define	CF_GETPWUSER	1		/* use |getpwusername(3dam)| */

/* revision history:

	- 2008-10-01, David A­D­ Morano
	This object module was originally written.

*/

/* Copyright © 2008 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Object:
	spellchecks

	Description:
	This module manages access and maintenance for the spell-check
	facility.  This facility may contain several spelling lists
	that may need to have their indices rebuilt as needed.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/param.h>
#include	<sys/stat.h>
#include	<sys/mman.h>
#include	<tzfile.h>		/* for TM_YEAR_BASE */
#include	<climits>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<getbufsize.h>
#include	<getusername.h>
#include	<getuserhome.h>
#include	<endian.h>
#include	<estrings.h>
#include	<vecobj.h>
#include	<sbuf.h>
#include	<ids.h>
#include	<vecstr.h>
#include	<vechand.h>
#include	<tmtime.hh>
#include	<mkdirs.h>
#include	<mktmp.h>
#include	<mkpathx.h>
#include	<mkfnamesuf.h>
#include	<permx.h>
#include	<fsdir.h>
#include	<paramfile.h>
#include	<ascii.h>
#include	<hash.h>		/* |hash_elf(3dam)| */
#include	<strn.h>
#include	<sfx.h>
#include	<six.h>
#include	<snx.h>
#include	<strwcpy.h>
#include	<cfdec.h>
#include	<strlist.h>
#include	<strlistmk.h>
#include	<matxstr.h>		/* |matpstr(3uc)| */
#include	<char.h>
#include	<isnot.h>
#include	<localmisc.h>		/* |TIMEBUFLEN| */

#include	"spellchecks.h"

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |lenstr(3u)| */

/* local defines */

#define	SC		spellchecks

#define	SC_DBSUF	"calendar"
#define	SC_NLE		1	/* default number line entries */
#define	SC_DMODE	0777
#define	SC_DBDIR	"share/calendar"
#define	SC		spellchecks
#define	SC_LE		struct spellchecks_list
#define	SC_LEF		struct spellchecks_lflags
#define	SC_CD		struct spellchecks_cachedir
#define	SC_CDF		struct spellchecks_cdflags
#define	SC_ENT		struct spellchecks_entry

#define	SI		subinfo
#define	SI_FL		subinfo_flags

#define	DB		struct spellchecks_list
#define	DB_NFS		3

#define	STRDESC		struct strdesc

#define	CONFIG		struct config

#define	CACHEDIR	struct spellchecks_cachedir
#define	CACHEDIR_NFS	2

#undef	WORDER
#define	WORDER		struct worder

#define	IDXDNAME	".spellchecks"
#define	IDXSUF		"cyi"

#ifndef	KBUFLEN
#define	KBUFLEN		(4 * MAXPATHLEN)
#endif

#ifndef	VBUFLEN
#define	VBUFLEN		(4 * MAXPATHLEN)
#endif

#ifndef	PBUFLEN
#define	PBUFLEN		(KBUFLEN + VBUFLEN + MAXPATHLEN)
#endif

#ifndef	EBUFLEN
#define	EBUFLEN		(4 * MAXPATHLEN)
#endif

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

#ifndef	VCNAME
#define	VCNAME		"var"
#endif

#undef	NLINES
#define	NLINES		20

#define	CEBUFLEN	(NLINES * 3 * szof(int))

#define	TO_FILEMOD	(60 * 24 * 3600)
#define	TO_MKWAIT	(5 * 50)
#define	TO_CHECK	4


/* external subroutines */

extern "C" {
    extern int	prmkfname(cc *,char *,cc *,int,cc *,cc *,cc *) noex ;
}


/* external variables */


/* local structures */

struct subinfo ;

struct strdesc {
	cchar		*sp ;
	int		sl ;
} ; /* end struct */

struct config {
	subinfo		*sip ;
	paramfile	p ;
	expcook		c ;
	uint		f_p:1 ;
	uint		f_c:1 ;
} ; /* end struct */

struct subinfo_flags {
	uint		stores:1 ;
	uint		dbs:1 ;
	uint		cachedirs:1 ;
	uint		logsize:1 ;
	uint		lfname:1 ;
	uint		id:1 ;
	uint		dom:1 ;
	uint		hols:1 ;
} ; /* end struct */

struct subinfo {
	vecstr		stores ;
	vechand		dbs ;
	vechand		cachedirs ;
	ids		id ;
	SI_FL		init, fl ;
	SI_FL		open ;
	spellchecks	*op ;
	config		*cfp ;
	cchar		*pr ;
	cchar		*sn ;
	cchar		*dbfname ;
	cchar		*tmpdname ;
	cchar		*tudname ;
	cchar		*userhome ;
	cchar		*lfname ;
	time_t		daytime ;
	int		logsize ;
	char		username[USERNAMELEN + 1] ;
} ; /* end struct (subinfo) */

struct spellchecks_lflags {
	uint		open:1 ;
} ; /* end struct */

struct spellchecks_list {
	cchar		*a ;		/* allocation */
	cchar		*idxname ;	/* index file name */
	cchar		*dbfname ;	/* DB (actual list) file-name */
	cchar		*cdname ;	/* cache directory name */
	SC_LEF		f ;
	STRLIST		idx ;		/* the STRLIST object */
} ; /* end struct */

struct spellchecks_cdflags {
	uint		dummy:1 ;
} ; /* end struct */

struct spellchecks_cachedir {
	cchar		*sname ;	/* symbolic-name */
	cchar		*dname ;	/* directory-name */
	cchar		*a ;		/* memory-allocation */
} ; /* end struct */

struct spellchecks_calflags {
	uint		vind:1 ;
} ; /* end struct */

struct spellchecks_cal {
	cchar		*dirname ;
	cchar 		*calname ;		/* DB file-name */
	cchar		*mapdata ;		/* DB memory-map address */
	spellchecks_calflags	fl ;
	time_t		ti_db ;			/* DB file modification */
	time_t		ti_map ;		/* DB map */
	time_t		ti_lastcheck ;		/* DB last check */
	time_t		ti_vind ;		/* verse-index */
	size_t		filesize ;		/* DB file size */
	size_t		mapsize ;		/* DB map length */
	int		nentries ;		/* DB entries */
	int		cidx ;			/* ordinal */
} ; /* end struct */

struct spellchecks_eline {
	uint		loff ;
	uint		llen ;
} ; /* end struct */

struct spellchecks_eflags {
	uint		hash:1 ;
} ; /* end struct */

struct spellchecks_entry {
	spellchecks_eline	*lines ;
	spellchecks_eflags	fl ;
	uint		voff ;
	uint		vlen ;
	uint		hash ;
	int		e, i ;
	int		cidx ;
	uchar		m, d ;
} ; /* end struct */

struct spellchecks_citer {
	int		i, e ;
} ; /* end struct */

struct worder {
	spellchecks_eline	*lines ;
	cchar		*mp ;
	cchar		*sp ;
	int		sl ;
	int		i ;
	int		nlines ;
} ; /* end struct */


/* forward references */

local int	spellchecks_dirnamescreate(SC *,cchar **) noex ;
local int	spellchecks_dirnamesdestroy(SC *) noex ;

local int	spellchecks_checkupdate(SC *,time_t) noex ;
local int	spellchecks_loadbuf(SC *,SC_ENT *,
			char *,int) noex ;
local int	spellchecks_tmpfrees(SC *) noex ;
local int	spellchecks_calscreate(SC *,SI *,
			cchar **) noex ;
local int	spellchecks_calscreater(SC *,SI *,
			cchar *,cchar **) noex ;
local int	spellchecks_calsdestroy(SC *) noex ;
local int	spellchecks_listcreate(SC *,SI *,
			cchar *,cchar *) noex ;
local int	spellchecks_listdestroy(SC *,SC_CAL *) noex ;

#ifdef	COMMENT
local int	spellchecks_mksysvarsi(SC *,cchar *) noex ;
#endif

local int	spellchecks_resultfins(SC *,SC_CUR *) noex ;
local int	spellchecks_calcite(SC *,vecobj *,SC_CAL *,
			SC_QUERY *) noex ;
local int	spellchecks_mkresults(SC *,vecobj *,
			SC_CUR *) noex ;
local int	spellchecks_already(SC *,vecobj *,
			SC_ENT *) noex ;

local int	cal_open(SC_CAL *,SI *,int,
			cchar *,cchar *) ;
local int	cal_close(SC_CAL *) ;
local int	cal_dbloadbegin(SC_CAL *,SI *) ;
local int	cal_dbloadend(SC_CAL *) ;
local int	cal_indopen(SC_CAL *,SI *) ;
local int	cal_dbmapcreate(SC_CAL *,time_t) ;
local int	cal_dbmapdestroy(SC_CAL *) ;
local int	cal_indopenperm(SC_CAL *,SI *) ;
local int	cal_indopentmp(SC_CAL *,SI *) ;

#ifdef	COMMENT
local int	cal_idxset(SC_CAL *,int) ;
#endif

local int	cal_idxget(SC_CAL *) ;
local int	cal_indopencheck(SC_CAL *,cchar *,int,int) ;
local int	cal_mkdirs(SC_CAL *,cchar *,int) ;
local int	cal_audit(SC_CAL *) ;

local int	cal_indmk(SC_CAL *,SI *,cchar *,
			int,time_t) ;
local int	cal_indmkdata(SC_CAL *,SI *,cchar *,
			mode_t,int) ;
local int	cal_indclose(SC_CAL *) ;

local int	cal_loadbuf(SC_CAL *,SC_ENT *,char *,int) ;
local int	cal_mapdata(SC_CAL *,cchar **) ;

local int	subinfo_start(SI *,SC *,
			cchar *,cchar *) ;
local int	subinfo_finish(SI *) ;
local int	subinfo_setentry(SI *,cchar **,cchar *,int) ;
local int	subinfo_userbegin(SI *) ;
local int	subinfo_userend(SI *) ;
local int	subinfo_confbegin(SI *,CONFIG *) ;
local int	subinfo_confread(SI *) ;
local int	subinfo_confend(SI *) ;
local int	subinfo_cachedir(SI *,CACHEDIR *) ;
local int	subinfo_cachedirfins(SI *) ;
local int	subinfo_db(SI *,DB *) ;
local int	subinfo_dbfins(SI *) ;
local int	subinfo_ids(SI *) ;
local int	subinfo_cachedir(SI *,cchar *,int) ;
local int	subinfo_tmpuserdir(SI *) ;
local int	subinfo_mkdirnames(SI *) ;
local int	subinfo_havedir(SI *,char *) ;
local int	subinfo_loadnames(SI *,vecstr *,cchar *) ;
local int	subinfo_havestart(SI *,
			SC_QUERY *,cchar *,int) ;
local int	subinfo_year(SI *) ;
local int	subinfo_mkday(SI *,int,cchar *,int) ;
local int	subinfo_transhol(SI *,SC_CITE *,
			cchar *,int) ;
local int	subinfo_checkdname(SI *,cchar *) ;

#ifdef	COMMENT
local int	subinfo_username(SI *) ;
#endif

local int	cachedir_start(CACHEDIR *,STRDESC *,int) ;
local int	cachedir_finish(CACHEDIR *) ;

local int	db_start(DB *,STRDESC *,int) ;
local int	db_finish(DB *) ;

local int	entry_start(SC_ENT *,SC_CITE *,int,int) ;
local int	entry_setidx(SC_ENT *,int) ;
local int	entry_add(SC_ENT *,uint,uint) ;
local int	entry_finish(SC_ENT *) ;
local int	entry_mkhash(SC_ENT *,SC *) ;
local int	entry_sethash(SC_ENT *,uint) ;
local int	entry_samehash(SC_ENT *,SC *,
			SC_ENT *) ;
local int	entry_same(SC_ENT *,SC *,SC_ENT *) ;
local int	entry_loadbuf(SC_ENT *,cchar *,char *,int) ;

#if	CF_SAMECITE
local int	entry_samecite(SC_ENT *,SC *,
			SC_ENT *) ;
#endif

local int	mkbve_start(CYIMK_ENT *,SI *,SC_ENT *) ;
local int	mkbve_finish(CYIMK_ENT *) ;

local int	worder_start(WORDER *,SC *,SC_ENT *) ;
local int	worder_finish(WORDER *) ;
local int	worder_get(WORDER *,cchar **) ;

local int	config_start(CONFIG *,SI *,cchar *) ;
local int	config_read(CONFIG *) ;
local int	config_finish(CONFIG *) ;
local int	config_cookbegin(CONFIG *) ;
local int	config_cookend(CONFIG *) ;
local int	config_setlfname(CONFIG *,cchar *,int) ;
local int	config_cachedir(CONFIG *,cchar *,int) ;
local int	config_cachedirone(CONFIG *,STRDESC *,int,cchar *,int) ;
local int	config_db(CONFIG *,cchar *,int) ;
local int	config_dbone(CONFIG *,STRDESC *,int,cchar *,int) ;

static bool	isempty(cchar *,int) noex ;

extern "C" {
    local int	vrcmp(cvoid **,cvoid **) noex ;
}


/* exported variables */

extern const SC_OBJ	spellchecks_modinfo = {
	"spellchecks",
	szof(spellchecks),
	szof(spellchecks_cur)
} ;


/* local variables */

constexpr cpcchar	sched1[] = {
	"%p/%e/%n/%n.%f",
	"%p/%e/%n/%f",
	"%p/%e/%n.%f",
	"%p/%n.%f",
	nullptr
} ;

enum cparams {
	cparam_cachedir,
	cparam_db,
	cparam_logfile,
	cparam_logsize,
	cparam_overlast
} ;

constexpr cpcchar	cparams[] = {
	"cachedir",
	"db",
	"logfile",
	"logsize",
	nullptr
} ;

enum cooks {
	cook_pr,
	cook_pn,
	cook_bn,
	cook_overlast
} ;

constexpr cpcchar	cooks[] = {
	"pr",
	"pn",
	"bn",
	nullptr
} ;


/* exported variables */


/* exported subroutines */

int spellchecks_start(SPELLCHECK *op,cchar *pr,cchar *dbfname) noex {
	SI	si, *sip = &si ;
	int	rs ;
	int	c = 0 ;

#if	CF_SAFE
	if (op == nullptr) return SR_FAULT ;
#endif

	if (pr == nullptr) return SR_FAULT ;

	if (pr[0] == '\0') return SR_INVALID ;

	memclear(op) ;
	op->pr = pr ;
	op->tmpdname = TMPDNAME ;

	if ((rs = subinfo_start(sip,op,pr,dbfname)) >= 0) {
	    c = rs ;
	    op->magic = SC_MAGIC ;
	    subinfo_finish(sip) ;
	} /* end if (subinfo) */

	return (rs >= 0) ? c : rs ;
}
/* end subroutine (spellchecks_start) */

int spellchecks_finish(SPELLCHECK *op) noex {
	int		rs = SR_OK ;
	int		rs1 ;

#if	CF_SAFE
	if (op == nullptr)
	    return SR_FAULT ;

	if (op->magic != SC_MAGIC)
	    return SR_NOTOPEN ;
#endif

	rs1 = spellchecks_listfins(op) ;
	if (rs >= 0) rs = rs1 ;

	rs1 = vechand_finish(&op->lists) ;
	if (rs >= 0) rs = rs1 ;

	op->nlists = 0 ;
	op->magic = 0 ;
	return rs ;
}
/* end subroutine (spellchecks_finish) */

int spellchecks_count(SC *op) noex {
	int		rs ;


#if	CF_SAFE
	if (op == nullptr)
	    return SR_FAULT ;

	if (op->magic != SC_MAGIC)
	    return SR_NOTOPEN ;
#endif

	rs = op->nlists ;

	return rs ;
}
/* end subroutine (spellchecks_count) */

int spellchecks_audit(SC *op) noex {
	SC_LE	*lep ;
	int		rs = SR_OK ;
	int		c = 0 ;

#if	CF_SAFE
	if (op == nullptr)
	    return SR_FAULT ;

	if (op->magic != SC_MAGIC)
	    return SR_NOTOPEN ;
#endif

	for (int i = 0 ; vechand_get(&op->lists,i,&lep) >= 0 ; i += 1) {
	    STRLIST	*slp ;
	    if (lep == nullptr) continue ;
	    slp = &lep->sl ;
	    c += 1 ;
	    rs = strlist_audit(slp) ;
	    if (rs < 0) break ;
	} /* end for */

	return (rs >= 0) ? c : rs ;
}
/* end subroutine (spellchecks_audit) */

int spellchecks_curbegin(SC *op,SC_CUR *curp) noex {
	int		rs = SR_OK ;

#if	CF_SAFE
	if (op == nullptr)
	    return SR_FAULT ;

	if (op->magic != SC_MAGIC)
	    return SR_NOTOPEN ;
#endif

	if (curp == nullptr)
	    return SR_FAULT ;

	memclear(curp) ;

	op->ncursors += 1 ;

	curp->i = -1 ;
	curp->magic = SC_MAGIC ;
	return rs ;
}
/* end subroutine (spellchecks_curbegin) */

int spellchecks_curend(SC *op,SC_CUR *curp) noex {
	int		rs = SR_OK ;
	int		rs1 ;

#if	CF_SAFE
	if (op == nullptr)
	    return SR_FAULT ;

	if (op->magic != SC_MAGIC)
	    return SR_NOTOPEN ;
#endif

	if (curp == nullptr)
	    return SR_FAULT ;

	if (curp->magic != SC_MAGIC)
	    return SR_NOTOPEN ;

	if (curp->results != nullptr) {
	    rs1 = spellchecks_resultfins(op,curp) ;
	    if (rs >= 0) rs = rs1 ;
	    rs1 = uc_free(curp->results) ;
	    if (rs >= 0) rs = rs1 ;
	    curp->results = nullptr ;
	}

	if (op->ncursors > 0) {
	    op->ncursors -= 1 ;
	}

	curp->magic = 0 ;
	return rs ;
}
/* end subroutine (spellchecks_curend) */

local int spellchecks_resultfins(SC *op,SC_CUR *curp) noex {
	SC_ENT		*ep = (SC_ENT *) curp->results ;
	int		rs = SR_OK ;
	int		rs1 ;
	if (ep != nullptr) {
	    int	i ;
	    for (i = 0 ; i < curp->nresults ; i += 1) {
		rs1 = entry_finish(ep + i) ;
		if (rs >= 0) rs = rs1 ;
	    }
	} /* end if */
	return rs ;
}
/* end subroutine (spellchecks_resultfins) */

int spellchecks_lookcite(op,curp,qvp)
SPELLCHECKS	*op ;
SC_CUR	*curp ;
SC_QUERY	*qvp ;
{
	SC_CAL	*calp ;
	vecobj		res ;
	int		rs = SR_OK ;
	int		i ;
	int		opts ;
	int		sz ;
	int		c = 0 ;

#if	CF_SAFE
	if (op == nullptr)
	    return SR_FAULT ;

	if (op->magic != SC_MAGIC)
	    return SR_NOTOPEN ;
#endif

	if (curp == nullptr) return SR_FAULT ;
	if (qvp == nullptr) return SR_FAULT ;

	if (curp->magic != SC_MAGIC) return SR_NOTOPEN ;

	if (curp->results != nullptr) {
	    spellchecks_resultfins(op,curp) ;
	    uc_free(curp->results) ;
	    curp->results = nullptr ;
	}

	opts = 0 ;
	opts |= VECOBJ_OORDERED ;
	opts |= VECOBJ_OSTATIONARY ;
	sz = szof(SC_ENT) ;
	rs = vecobj_start(&res,sz,0,opts) ;
	if (rs < 0)
	    goto ret0 ;

	for (i = 0 ; vechand_get(&op->cals,i,&calp) >= 0 ; i += 1) {
	    if (calp == nullptr) continue ;

	    rs = spellchecks_calcite(op,&res,calp,qvp) ;
	    c += rs ;
	    if (rs < 0) break ;
	} /* end for */

	if (rs >= 0) {
	    rs = spellchecks_mkresults(op,&res,curp) ;
	}

	if ((rs < 0) || (c > 0)) {
	    SC_ENT	*ep ;
	    for (i = 0 ; vecobj_get(&res,i,&ep) >= 0 ; i += 1) {
		if (ep == nullptr) continue ;
		entry_finish(ep) ;
	    }
	}

ret1:
	vecobj_finish(&res) ;

ret0:

	return (rs >= 0) ? c : rs ;
}
/* end subroutine (spellchecks_lookcite) */


int spellchecks_read(op,curp,qvp,rbuf,rlen)
SPELLCHECKS	*op ;
SC_CUR	*curp ;
SC_CITE	*qvp ;
char		*rbuf ;
int		rlen ;
{
	SC_ENT	*ep ;

	int	rs = SR_OK ;
	int	i ;
	int	len = 0 ;


#if	CF_SAFE
	if (op == nullptr)
	    return SR_FAULT ;

	if (op->magic != SC_MAGIC)
	    return SR_NOTOPEN ;
#endif

	if (curp == nullptr) return SR_FAULT ;
	if (qvp == nullptr) return SR_FAULT ;

	if (curp->magic != SC_MAGIC) return SR_NOTOPEN ;

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

	ep = (SC_ENT *) curp->results ;
	qvp->m = ep->m ;
	qvp->d = ep->d ;
	if (rbuf != nullptr) {
	    rs = spellchecks_loadbuf(op,(ep + i),rbuf,rlen) ;
	    len = rs ;
	} /* end if */

	if (rs >= 0)
	    curp->i = (i + 1) ;

ret0:
	return (rs >= 0) ? len : rs ;
}
/* end subroutine (spellchecks_read) */


/* ARGSUSED */
int spellchecks_check(op,daytime)
SPELLCHECKS	*op ;
time_t		daytime ;
{
	int	rs = SR_OK ;


#if	CF_SAFE
	if (op == nullptr)
	    return SR_FAULT ;

	if (op->magic != SC_MAGIC)
	    return SR_NOTOPEN ;
#endif

#ifdef	COMMENT
	rs = spellchecks_checkupdate(op,daytime) ;
#endif

	return rs ;
}
/* end subroutine (spellchecks_check) */


/* private subroutines */


local int spellchecks_dirnamescreate(op,dirnames)
SPELLCHECKS	*op ;
cchar	**dirnames ;
{
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
	rs = uc_malloc(sz,&p) ;
	if (rs < 0)
	    goto bad0 ;

	op->dirnames = (char **) p ;
	rs = uc_malloc(strsize,&p) ;
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

/* bad stuff */
bad1:
	uc_free(op->dirnames) ;
	op->dirnames = nullptr ;

bad0:
	goto ret0 ;
}
/* end subroutine (spellchecks_dirnamescreate) */


local int spellchecks_dirnamesdestroy(op)
SPELLCHECKS	*op ;
{
	int	rs = SR_OK ;
	int	rs1 ;


	if (op->dirnames != nullptr) {
	    rs1 = uc_free(op->dirnames) ;
	    if (rs >= 0) rs = rs1 ;
	    op->dirnames = nullptr ;
	}

	if (op->dirstrtab != nullptr) {
	    rs1 = uc_free(op->dirstrtab) ;
	    if (rs >= 0) rs = rs1 ;
	    op->dirstrtab = nullptr ;
	}

	return rs ;
}
/* end subroutine (spellchecks_dirnamesdestroy) */


local int spellchecks_calcite(op,rlp,calp,qvp)
SPELLCHECKS	*op ;
vecobj		*rlp ;
SC_CAL	*calp ;
SC_QUERY	*qvp ;
{
	SC_ENT	e ;

	CYI		*cip ;
	CYI_CUR		ccur ;
	CYI_QUERY	cq{} ;
	CYI_ENT	ce ;

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

	    rs = cyi_curcite(cip,&ccur,&cq) ;

	    if (rs >= 0) {

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
			    rs = spellchecks_already(op,rlp,&e) ;
			    f_already = (rs > 0) ;
#endif

			    f_ent = false ;
			    if ((rs >= 0) && (! f_already)) {
		                rs = vecobj_add(rlp,&e) ;
		            } else
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
/* end subroutine (spellchecks_calcite) */


local int spellchecks_already(op,rlp,ep)
SPELLCHECKS	*op ;
vecobj		*rlp ;
SC_ENT	*ep ;
{
	SC_ENT	*oep ;

	int	rs = SR_OK ;
	int	i ;
	int	f = false ;


	for (i = 0 ; vecobj_get(rlp,i,&oep) >= 0 ; i += 1) {
	    if (oep == nullptr) continue ;

	    rs = entry_samehash(ep,op,oep) ;
	    if (rs == 0) continue ; /* not the same */

	    if (rs >= 0)
	        rs = entry_same(ep,op,oep) ;

	    f = (rs > 0) ; /* same? */
	    if (f) 
		break ;

	    if (rs < 0)
		break ;

	} /* end for */

	return (rs >= 0) ? f : rs ;
}
/* end subroutine (spellchecks_already) */


local int spellchecks_mkresults(op,rlp,curp)
SPELLCHECKS	*op ;
vecobj		*rlp ;
SC_CUR	*curp ;
{
	SC_ENT	*rp ;
	SC_ENT	*ep ;

	int	rs = SR_OK ;
	int	n ;
	int	i ;
	int	sz ;
	int	c = 0 ;


	vecobj_sort(rlp,vrcmp) ; /* sort results in ascending order */

	n = vecobj_count(rlp) ;
	if (n <= 0)
	    goto ret0 ;

	sz = n * szof(SC_ENT) ;
	rs = uc_malloc(sz,&rp) ;
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
	    uc_free(rp) ;

ret0:

	return (rs >= 0) ? c : rs ;
}
/* end subroutine (spellchecks_mkresults) */


local int spellchecks_tmpfrees(op)
SPELLCHECKS	*op ;
{
	int	i ;

	cchar	*sp ;


	for (i = 0 ; vecstr_get(&op->tmpfiles,i,&sp) >= 0 ; i += 1) {
	    if (sp == nullptr) continue ;
	    if (sp[0] != '\0')
		u_unlink(sp) ;
	} /* end for */

	return SR_OK ;
}
/* end subroutine (spellchecks_tmpfrees) */


local int spellchecks_calscreate(op,sip,calnames)
SPELLCHECKS	*op ;
SI	*sip ;
cchar	*calnames[] ;
{
	int	rs = SR_OK ;
	int	c = 0 ;

	cchar	**dirnames = sip->dirnames ;

	if (dirnames != nullptr) {
	    int	i ;
	    for (i = 0 ; dirnames[i] != nullptr ; i += 1) {
	        if (dirnames[i] == '\0') continue ;
	        rs = spellchecks_calscreater(op,sip,dirnames[i],calnames) ;
	        c += rs ;
	        if (rs < 0) break ;
	    } /* end for (dirnames) */
	} /* end if (dirnames) */

	return (rs >= 0) ? c : rs ;
}
/* end subroutine (spellchecks_calscreate) */


local int spellchecks_calscreater(op,sip,dirname,calnames)
SPELLCHECKS	*op ;
SI	*sip ;
cchar	*dirname ;
cchar	*calnames[] ;
{
	vecstr	cals ;

	int	rs = SR_OK ;
	int	j ;
	int	n = 0 ;
	int	c = 0 ;
	int	f_search = false ;

	cchar	**npp ;
	cchar	**names = nullptr ;


	if (dirname == nullptr)
	    goto ret0 ;

	if (calnames == nullptr) {
	    rs = vecstr_start(&cals,1,0) ;
	    f_search = (rs >= 0) ;
	    if (rs >= 0) {
		rs = subinfo_loadnames(sip,&cals,dirname) ;
		n = rs ;
		if ((rs >= 0) && (n > 0)) {
		    rs = vecstr_getvec(&cals,&npp) ;
		    if (rs >= 0)
			names = npp ;
		}
	    }
	} else {
	    names = calnames ;
	}

	if (rs >= 0) {
	    rs = subinfo_ids(sip) ;
	}

	if ((rs >= 0) && (names != nullptr)) {

	    for (j = 0 ; names[j] != nullptr ; j += 1) {
	        if (names[j][0] == '\0') continue ;

		rs = spellchecks_listcreate(op,sip,dirname,names[j]) ;
		c += rs ;
		if (rs < 0)
		    break ;

	    } /* end for (calnames) */

	} /* end if */

ret1:
	if (f_search)
	    vecstr_finish(&cals) ;

ret0:

	return (rs >= 0) ? c : rs ;
}
/* end subroutine (spellchecks_calscreater) */


local int spellchecks_listfins(op)
SPELLCHECKS	*op ;
{
	SC_LE	*lep ;

	int	rs = SR_OK ;
	int	rs1 ;
	int	i ;


	for (i = 0 ; vechand_get(&op->lists,i,&lep) >= 0 ; i += 1) {
	    if (lep == nullptr) continue ;
	    rs1 = spellchecks_listdestroy(op,lep) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end for */

	return rs ;
}
/* end subroutine (spellchecks_listfins) */


local int spellchecks_listcreate(op,sip,dirname,calname)
SPELLCHECKS	*op ;
SI	*sip ;
cchar	dirname[] ;
cchar	calname[] ;
{
	USTAT	sb ;

	SC_CAL	*calp ;

	cint	sz = szof(SC_CAL) ;

	int	rs = SR_OK ;
	int	rs1 ;
	int	cidx ;
	int	f = false ;

	cchar	*suf = SC_DBSUF ;

	char	cname[MAXNAMELEN + 1] ;
	char	tmpfname[MAXPATHLEN + 1] ;


	rs = snsds(cname,MAXNAMELEN,calname,suf) ;

	if (rs >= 0)
	    rs = mkpath2(tmpfname,dirname,cname) ;

	if (rs < 0)
	    goto bad0 ;

	rs1 = u_stat(tmpfname,&sb) ;

	if (rs1 >= 0)
	    rs1 = permid(&sip->id,&sb,R_OK) ;

	if (rs1 < 0)
	    goto bad0 ;

	f = f || S_ISREG(sb.st_mode) ;
	if (! f)
	    rs = SR_LIBEXEC ; /* or should it be SR_OPNOTSUPP */

	if (rs < 0)
	    goto bad0 ;

	rs = uc_malloc(sz,&calp) ;
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
	uc_free(calp) ;

bad0:
	goto ret0 ;
}
/* end subroutine (spellchecks_listcreate) */


local int spellchecks_listdestroy(op,lep)
SPELLCHECKS	*op ;
SC_LE	*lep ;
{
	int	rs = SR_OK ;
	int	rs1 ;

	if (lep->fl.open) {
	    rs1 = strlist_close(&lep->sl) ;
	    if (rs >= 0) rs = rs1 ;
	}

	if (lep->a != nullptr) {
	    rs1 = uc_free(lep->a) ;
	    if (rs >= 0) rs = rs1 ;
	    lep->a = nullptr ;
	}

	if ((rs1 = vechand_ent(&op->lists,lep)) >= 0) {
	    rs1 = vechand_del(&op->lists,rs1) ;
	    if (rs >= 0) rs = rs1 ;
	}

	rs1 = uc_free(lep) ;
	if (rs >= 0) rs = rs1 ;

	return rs ;
}
/* end subroutine (spellchecks_listdestroy) */

local int spellchecks_loadbuf(op,ep,rbuf,rlen)
SPELLCHECKS	*op ;
SC_ENT	*ep ;
char		rbuf[] ;
int		rlen ;
{
	SC_CAL	*calp ;

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
/* end subroutine (spellchecks_loadbuf) */

local int cal_open(SC_CAL *calp,SI *sip,int cidx,cc *dirname,cc *calname) noex {
	int	rs ;
	memclear(calp) ;

	calp->cidx = cidx ;
	rs = uc_mallocstrw(dirname,-1,&calp->dirname) ;
	if (rs < 0)
	    goto bad0 ;

	rs = uc_mallocstrw(calname,-1,&calp->calname) ;
	if (rs < 0)
	    goto bad1 ;

	rs = cal_dbloadbegin(calp,sip) ;
	if (rs < 0)
	    goto bad2 ;

ret0:

	return rs ;

/* bad stuff */
bad2:
	uc_free(calp->calname) ;

bad1:
	uc_free(calp->dirname) ;

bad0:
	goto ret0 ;
}
/* end subroutine (cal_open) */

local int cal_close(SC_CAL *calp) noex {
	int	rs = SR_OK ;
	int	rs1 ;
	{
	    rs1 = cal_dbloadend(calp) ;
	    if (rs >= 0) rs = rs1 ;
	}
	if (calp->calname) {
	    rs1 = uc_free(calp->calname) ;
	    if (rs >= 0) rs = rs1 ;
	    calp->calname = nullptr ;
	}
	if (calp->dirname) {
	    rs1 = uc_free(calp->dirname) ;
	    if (rs >= 0) rs = rs1 ;
	    calp->dirname = nullptr ;
	}
	return rs ;
}
/* end subroutine (cal_close) */

local int cal_dbloadbegin(SC_CAL *calp,SI *sip) noex {
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
/* end subroutine (cal_dbloadbegin) */

local int cal_dbloadend(SC_CAL *calp) noex {
	int	rs = SR_OK ;
	int	rs1 ;
	{
	rs1 = cal_indclose(calp) ;
	if (rs >= 0) rs = rs1 ;
	}
	{
	rs1 = cal_dbmapdestroy(calp) ;
	if (rs >= 0) rs = rs1 ;
	}
	return rs ;
}
/* end subroutine (cal_dbloadend) */

local int cal_dbmapcreate(SC_CAL *calp,time_t daytime) noex {
	USTAT	sb ;
	int	rs = SR_OK ;
	int	fd ;

	char	cname[MAXNAMELEN + 1] ;
	char	dbfname[MAXPATHLEN + 1] ;

	rs = snsds(cname,MAXNAMELEN,calp->calname,SC_DBSUF) ;
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

	{
	    size_t	msize = (size_t) calp->filesize ;
	    int		mprot = PROT_READ ;
	    int		mflags = MAP_SHARED ;
	    void	*mdata ;
	    if ((rs = u_mmap(nullptr,msize,mprot,mflags,fd,0L,&mdata)) >= 0) {
	        calp->mapdata = mdata ;
	        calp->mapsize = calp->filesize ;
	        calp->ti_map = daytime ;
	        calp->ti_lastcheck = daytime ;
	    } /* end if (u_mmap) */
	} /* end block */

/* close it */
ret1:
	u_close(fd) ;

ret0:
	return rs ;
}
/* end subroutine (cal_dbmapcreate) */

local int cal_dbmapdestroy(SC_CAL *calp) noex {
	int	rs = SR_OK ;
	if (calp->mapdata) {
	    rs = u_munmap(calp->mapdata,calp->mapsize) ;
	    calp->mapdata = nullptr ;
	    calp->mapsize = 0 ;
	}
	return rs ;
}
/* end subroutine (cal_dbmapdestroy) */

local int cal_indopen(SC_CAL *calp,SIP *sip) noex {
	int	rs ;
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

local int cal_indopenperm(SC_CAL *calp,SI *sip) noex {
	int	rs ;
	int	year = sip->year ;
	int	f_search = false ;
	int	f_mkind = false ;
	cchar	*idxdname = IDXDNAME ;
	char	idname[MAXNAMELEN + 1] ;

	rs = mkpath2(idname,calp->dirname,idxdname) ;
	if (rs < 0)
	    goto ret0 ;

try:
	rs = cal_indopencheck(calp,idname,year,f_search) ;

	if (rs == SR_NOTDIR) {
	    f_mkind = true ;
	    rs = cal_mkdirs(calp,idname,SC_DMODE) ;
	}

	f_mkind = f_mkind || (rs == SR_NOENT) ;
	f_mkind = f_mkind || (rs == SR_STALE) ;
	f_mkind = f_mkind || (rs == SR_NOCSI) ; /* zero sized file */
	if (f_mkind) {
	    rs = cal_indmk(calp,sip,idname,f_search,sip->daytime) ;

	    if (rs >= 0) {
		rs = cal_indopencheck(calp,idname,year,f_search) ;
	    }
	} /* end if */

ret0:
	return (rs >= 0) ? f_mkind : rs ;
}
/* end subroutine (cal_indopenperm) */

local int cal_indopentmp(SC_CAL *calp,SI *sip) noex {
	SPELLCHECKS	*op = sip->op ;
	int	rs ;
	int	year = sip->year ;
	int	f_search = true ;
	int	f_mkind = false ;
	cchar	*idxdname = IDXDNAME ;
	char	idname[MAXPATHLEN + 1] ;

#if	CF_TMPPRNAME
	{
	    cchar	*prname ;
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
	    f_mkind = true ;
	    rs = cal_mkdirs(calp,idname,SC_DMODE) ;
	}

	f_mkind = f_mkind || (rs == SR_NOENT) ;
	f_mkind = f_mkind || (rs == SR_STALE) ;
	f_mkind = f_mkind || (rs == SR_NOCSI) ; /* zero sized file */
	if (f_mkind) {
	    rs = cal_indmk(calp,sip,idname,f_search,sip->daytime) ;
	    if (rs >= 0) {
		rs = cal_indopencheck(calp,idname,year,f_search) ;
	    }
	} /* end if */

ret0:
	return (rs >= 0) ? f_mkind : rs ;
}
/* end subroutine (cal_indopentmp) */

local int cal_mkdirs(SC_CAL *calp,cchar *dname,int mode) noex {
	USTAT	sb ;
	int	rs = SR_OK ;
	mode &= S_IAMB ;
	rs = mkdirs(dname,mode) ;
	if (rs >= 0) {
	    rs = u_stat(dname,&sb) ;
	    if ((rs >= 0) && ((sb.st_mode & mode) != mode))
		rs = u_chmod(dname,mode) ;
	}
	return rs ;
}
/* end subroutine (cal_mkdirs) */

local int cal_indopencheck(SC_CAL *calp,cc *dname,int year,int f_search) noex {
	CYI_INFO	binfo ;
	int		rs ;

	if ((rs = cyi_open(&calp->vind,dname,calp->calname,f_search)) >= 0) {
	    if ((rs = cyi_getinfo(&calp->vind,&binfo)) >= 0) {
		bool 	f = false ;
		f = f || (binfo.ctime < calp->ti_db) ;
		f = f || (binfo.mtime < calp->ti_db) ;
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
/* end subroutine (spellchecks_indopencheck) */

#ifdef	COMMENT
local int spellchecks_indopens(SC *op,SI *sip,int oflags) noex {
	int	rs = SR_NOENT ;
	for (int i = 0 ; indopens[i] != nullptr ; i += 1) {
	    rs = (*indopens[i])(op,sip,oflags) ;
	    if ((rs == SR_BADFMT) || (rs == SR_NOMEM))
		break ;

	    if (rs >= 0)
	        break ;

	} /* end for */
	return rs ;
}
/* end subroutine (spellchecks_indopens) */

local int spellchecks_indopenpr(SC *op,SI *sip,int oflags) noex {
	int	rs = SR_OK ;
	char	idname[MAXPATHLEN + 1] ;

	rs = mkpath3(idname,op->pr,VCNAME,IDXDNAME) ;
	if (rs < 0)
	    goto ret0 ;

	rs = spellchecks_indopendname(op,sip,idname,oflags) ;

ret0:
	return rs ;
}
/* end subroutine (spellchecks_indopenpr) */

local int spellchecks_indopentmp(SC *op,SI *sip,int oflags) noex {
	int	rs = SR_OK ;
	cchar	*idxdname = IDXDNAME ;
	char	idname[MAXPATHLEN + 1] ;

#if	CF_TMPPRNAME
	{
	    cchar	*prname ;
	    rs = sfbasename(op->pr,-1,&prname) ;
	    if (rs >= 0)
	        rs = mkpath3(idname,op->tmpdname,prname,idxdname) ;

	}
#else /* CF_TMPPRNAME */

	rs = mkpath2(idname,op->tmpdname,idxdname) ;

#endif /* CF_TMPPRNAME */

	if (rs >= 0)
	    rs = spellchecks_indopendname(op,sip,idname,oflags) ;

ret0:
	return rs ;
}
/* end subroutine (spellchecks_indopentmp) */

local int spellchecks_indopendname(op,sip,dname,oflags)
SPELLCHECKS	*op ;
SI	*sip ;
cchar	dname[] ;
int		oflags ;
{
	int	rs ;
	int	f_ok = false ;
	int	f_mk = false ;

	char	indname[MAXPATHLEN + 1] ;


	rs = mkpath2(indname,dname,op->dbname) ;
	if (rs < 0)
	    goto ret0 ;

	if (oflags & O_CREAT) {

	    rs = spellchecks_indcheck(op,indname,sip->daytime) ;
	    f_ok = (rs > 0) ;

	    if (rs < 0) goto ret0 ;

#ifdef	COMMENT
	    if ((rs < 0) || (! f_ok)) {
	        rs = spellchecks_mksysvarsi(op,dname) ;
	        if (rs >= 0) {
		    f_mk = true ;
	            rs = spellchecks_indcheck(op,indname,sip->daytime) ;
	            f_ok = (rs > 0) ;
	        }
	    }
#endif /* COMMENT */

	    if ((rs < 0) || (! f_ok)) {
	        f_mk = true ;
	        rs = spellchecks_indmk(op,sip,dname,sip->daytime) ;

	    } /* end if */

	    if (rs >= 0) {
	        rs = cyi_open(&op->vind,indname) ;
	        op->fl.vind = (rs >= 0) ;

	    } /* end if */

	    if ((rs < 0) && (rs != SR_BADFMT) && (! f_mk)) {
	        rs = spellchecks_indmk(op,sip,dname,sip->daytime) ;
	        if (rs >= 0) {
		    rs = cyi_open(&op->vind,indname) ;
	            op->fl.vind = (rs >= 0) ;
	        }
	    }

	} else {
	    rs = cyi_open(&op->vind,indname) ;
	    op->fl.vind = (rs >= 0) ;
	} /* end if (open-only or open-create) */

ret0:

	return rs ;
}
/* end subroutine (spellchecks_indopendname) */


local int spellchecks_indcheck(op,indname,daytime)
SPELLCHECKS	*op ;
cchar	indname[] ;
time_t		daytime ;
{
	USTAT	sb ;

	time_t	ti_ind ;

	int	rs ;
	int	rs1 ;
	int	f = false ;

	char	indfname[MAXPATHLEN + 1] ;

	rs = mkfnamesuf2(indfname,indname,IDXSUF,ENDIANSTR) ;
	if (rs < 0)
	    goto ret0 ;

	rs1 = u_stat(indfname,&sb) ;

	ti_ind = sb.st_mtime ;
	if ((rs1 >= 0) && (op->ti_db > ti_ind))
	    rs1 = SR_TIMEDOUT ;

	if ((rs1 >= 0) && ((daytime - ti_ind) >= TO_FILEMOD))
	    rs1 = SR_TIMEDOUT ;

	f = (rs1 >= 0) ;

ret0:
	return (rs >= 0) ? f : rs ;
}
/* end subroutine (spellchecks_indcheck) */

#endif /* COMMENT */

local int cal_indmk(SC_CAL *calp,SI *sip,cc *dname,int f_tmp,
		time_t daytime) noex {
	cmode	operms = 0664 ;
	int	rs = SR_OK ;
	int	c = 0 ;
	/* check the given directory for writability */
	rs = subinfo_checkdname(sip,dname) ;
	if (rs == SR_NOENT) {
	    rs = mkdirs(dname,0777) ; /* will fail if parent is not writable */
	}
	if (rs >= 0) {
	    if ((rs = cal_indmkdata(calp,sip,dname,operms,f_tmp)) >= 0) {
	        c += rs ;
	        calp->ti_vind = daytime ;
	    }
	}

	return (rs >= 0) ? c : rs ;
}
/* end subroutine (cal_indmk) */

local int cal_indmkdata(SC_CAL *calp,SI *sip,cc *dname,
		mode_t operms,int f_tmp) noex {
	SC_ENT		e ;
	SC_QUERY	q ;
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
	cchar	*tp, *mp, *lp ;


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

	    fileoff += len ;
	    ml -= len ;
	    mp += len ;

	    if (rs < 0) break ;
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
	    if (rs1 >= 0) {
		rs = SR_OK ;
		goto ret1 ;
	    } else if (rs1 == SR_EXIST)
		rs1 = SR_OK ;
	    rs = rs1 ;
	} else
	    rs = SR_TIMEDOUT ;

	goto ret0 ;
}
/* end subroutine (cal_indmkdata) */

local int cal_indclose(SC_CAL *calp) noex {
	int	rs = SR_OK ;
	if (calp->fl.vind) {
	    calp->fl.vind = false ;
	    rs = cyi_close(&calp->vind) ;
	}
	return rs ;
}
/* end subroutine (cal_indclose) */

#ifdef	COMMENT
local int cal_idxset(SC_CAL *calp,int cidx) noex {
	calp->cidx = cidx ;
	return SR_OK ;
}
/* end subroutine (cal_idxset) */
#endif /* COMMENT */

local int cal_idxget(SC_CAL *calp) noex {
	int	cidx = calp->cidx ;
	return cidx ;
}
/* end subroutine (cal_idxget) */

local int cal_audit(SC_CAL *calp) noex {
	int	rs = SR_OK ;
	{
	    rs = cyi_audit(&calp->vind) ;
	}
	return rs ;
}
/* end subroutine (cal_audit) */

local int cal_loadbuf(SC_CAL *calp,SC_ENT *ep,char *rbuf,int rlen) noex {
	int	rs ;
	cchar	*mp ;
	if ((rs = cal_mapdata(calp,&mp)) >= 0) {
	    rs = entry_loadbuf(ep,mp,rbuf,rlen) ;
	}
	return rs ;
} 
/* end subroutine (cal_loadbuf) */

local int cal_mapdata(SC_CAL *calp,cchar **mpp) noex {
	int	rs ;
	if (mpp != nullptr)
	    *mpp = calp->mapdata ;

	rs = calp->mapsize ;
	return rs ;
}
/* end subroutine (cal_mapdata) */

local int subinfo_start(SI *sip,SPELLCHECK *op,cc *pr,cc *dbfname) noex {
	CONFIG		cf ;
	int		rs = SR_OK ;
	int		rs1 ;
	int		rv = 0 ;

	memclear(sip) ;
	sip->op = op ;
	sip->pr = pr ;
	sip->sn = SC_SEARCHNAME ;
	sip->dbfname = dbfname ;

	if ((rs = ids_load(&sip->id)) >= 0) {
	    sip->open.id = true ;
	    if ((rs = subinfo_confbegin(sip,&cf)) >= 0) {
		{
	            rs = subinfo_confread(sip) ;
		    rv = rs ;
		}
	        rs1 = subinfo_confend(sip) ;
		if (rs >= 0) rs = rs1 ;
	    } /* end if (subinfo_conf) */
	    if (rs < 0) {
	        sip->open.id = false ;
	        ids_release(&sip->id) ;
	    }
	} /* end if (ids) */

	return rs ;
}
/* end subroutine (subinfo_start) */

local int subinfo_finish(SI *sip) noex {
	int		rs = SR_OK ;
	int		rs1 ;
	{
	    rs1 = subinfo_dbfins(sip) ;
	    if (rs >= 0) rs = rs1 ;
	}
	{
	    rs1 = subinfo_cachedirfins(sip) ;
	    if (rs >= 0) rs = rs1 ;
	}
	if (sip->userhome != nullptr) {
	    rs1 = uc_free(sip->userhome) ;
	    if (rs >= 0) rs = rs1 ;
	    sip->userhome = nullptr ;
	}
	if (sip->open.dbs) {
	    sip->open.dbs = false ;
	    rs1 = vechand_finish(&sip->dbs) ;
	    if (rs >= 0) rs = rs1 ;
	}
	if (sip->open.cachedirs) {
	    sip->open.cachedirs = false ;
	    rs1 = vechand_finish(&sip->cachedirs) ;
	    if (rs >= 0) rs = rs1 ;
	}
	if (sip->open.stores) {
	    sip->open.stores = false ;
	    rs1 = vecstr_finish(&sip->stores) ;
	    if (rs >= 0) rs = rs1 ;
	}
	if (sip->open.id) {
	    sip->open.id = false ;
	    rs1 = ids_release(&sip->id) ;
	    if (rs >= 0) rs = rs1 ;
	}
	return rs ;
}
/* end subroutine (subinfo_finish) */


local int subinfo_setentry(sip,epp,vp,vl)
SI	*sip ;
cchar	**epp ;
cchar	vp[] ;
int		vl ;
{
	int	rs = SR_OK ;
	int	vnlen = 0 ;


	if (lip == nullptr) return SR_FAULT ;
	if (epp == nullptr) return SR_FAULT ;

	if (! sip->open.stores) {
	    rs = vecstr_start(&sip->stores,4,0) ;
	    sip->open.stores = (rs >= 0) ;
	}

	if (rs >= 0) {
	    int	oi = -1 ;

	    if (*epp != nullptr) oi = vecstr_findaddr(&sip->stores,*epp) ;

	    if (vp != nullptr) {
		vnlen = lenstr(vp,vl) ;
	        if ((rs = vecstr_add(&sip->stores,vp,vnlen)) >= 0) {
	            rs = vecstr_get(&sip->stores,rs,epp) ;
	        } /* end if (added new entry) */
	    } /* end if (had a new entry) */

	    if ((rs >= 0) && (oi >= 0))
	        vecstr_del(&sip->stores,oi) ;

	} /* end if */

	return (rs >= 0) ? vnlen : rs ;
}
/* end subroutine (subinfo_setentry) */


#if	CF_GETPWUSER
local int subinfo_userbegin(SI *sip)
{
	int	rs = SR_OK ;

	if (sip->username[0] == '\0') {
	    struct passwd	pw ;
	    cint		pwlen = getbufsize(bufsize_pw) ;
	    char		*pwbuf ;
	    if ((rs = uc_malloc((pwlen+1),&pwbuf)) >= 0) {
	        if ((rs = getpwusername(&pw,pwbuf,pwlen,-1)) >= 0) {
	            cint	ulen = USERNAMELEN ;
		    cchar	**vpp = &sip->userhome ;
		    strwcpy(sip->username,pw.pw_name,ulen) ;
		    rs = subinfo_setentry(sip,vpp,pw.pw_dir,-1) ;
		}
		uc_free(pwbuf) ;
	    } /* end if (memory-allocation) */
	} /* end if (needed) */

	return rs ;
}
/* end subroutine (subinfo_userbegin) */
#else /* CF_GETPWUSER */
local int subinfo_userbegin(SI *sip)
{
	cint	ulen = USERNAMELEN ;
	int		rs ;
	char		*ubuf = sip->username ;

	if ((rs = getusername(ubuf,ulen,-1)) >= 0) {
	    cint	hlen = MAXPATHLEN ;
	    char	hbuf[MAXPATHLEN+1] ;
	    if ((rs == getuserhome(hbuf,hlen,ubuf)) >= 0) {
		cchar	**vpp = &sip->userhome ;
		rs = subinfo_setentry(sip,vpp,hbuf,rs)) >= 0) {
	    }
	}

	return rs ;
}
/* end subroutine (subinfo_userbegin) */
#endif /* CF_GETPWUSER */


/* no need to really do anything here */
local int subinfo_userend(SI *sip)
{
	if (sip == nullptr) return SR_FAULT ;
	return SR_OK ;
}
/* end subroutine (subinfo_userend) */


local int subinfo_confbegin(SI *sip,CONFIG *cfp)
{
	int	rs ;
	cchar	*cfname = SC_CONFNAME ;

	if ((rs = subinfo_userbegin(sip)) >= 0) {
	    if ((rs = config_start(cfp,sip,cfname)) >= 0) {
	        sip->cfp = cfp ;
	    } /* end if (config_start) */
	    if (rs < 0)
		subinfo_userend(sip) ;
	} /* end if (user) */

	return rs ;
}
/* end subroutine (subinfo_confbegin) */


local int subinfo_confend(SI *sip)
{
	CONFIG		*cfp = sip->cfp ;
	int		rs = SR_OK ;
	int		rs1 ;

	if (cfp != nullptr) {
	    rs1 = config_finish(cfp) ;
	    if (rs >= 0) rs = rs1 ;
	    sip->cfp = nullptr ;
	}

	rs1 = subinfo_userend(sip) ;
	if (rs >= 0) rs = rs1 ;

	return rs ;
}
/* end subroutine (subinfo_confend) */


local int subinfo_confread(SUBINF *sip)
{
	CONFIG	*cfp = sip->cfp ;
	int	rs = SR_OK ;

	if (cfp != nullptr) {
	    rs = config_read(cfp) ;
	}

	return rs ;
}
/* end subroutine (subinfo_confread) */


local int subinfo_cachedir(SI *sip,CACHEDIR *cdp)
{
	int	rs = SR_OK ;

	if (! sip->open.cachedirs) {
	    if ((rs = vechand_start(&op->cachedirs,2,0)) >= 0) {
	        sip->open.cachedirs = true ;
	    }
	}

	if (rs >= 0)
	    rs = vechand_add(&sip->cachedirs,cdp) ;

	return rs ;
}
/* end subroutine (subinfo_cachedir) */


local int subinfo_cachedirfins(SI *sip)
{
	int	rs = SR_OK ;
	int	rs1 ;

	if (sip->open.cachedirs) {
	    CACHEDIR	*cdp ;
	    int	i ;
	    for (i = 0 ; vechand_get(&op->cachedirs,i,&cdp) >= 0 ; i += 1) {
		if (cdp == nullptr) continue ;
		rs1 = cachedir_finish(cdp) ;
		if (rs >= 0) rs = rs1 ;
		rs1 = uc_free(cdp) ;
		if (rs >= 0) rs = rs1 ;
	    } /* end for */
	} /* end if (cachedirs) */

	return rs ;
}
/* end subroutine (subinfo_cachedirfins) */


local int subinfo_db(SI *sip,DB *dbp)
{
	int	rs = SR_OK ;

	if (! sip->open.dbs) {
	    if ((rs = vechand_start(&op->dbs,2,0)) >= 0) {
	        sip->open.dbs = true ;
	    }
	}

	if (rs >= 0)
	    rs = vechand_add(&sip->dbs,dbp) ;

	return rs ;
}
/* end subroutine (subinfo_db) */


local int subinfo_dbfins(SI *sip)
{
	int	rs = SR_OK ;
	int	rs1 ;

	if (sip->open.dbs) {
	    DB		*dbp ;
	    int		i ;
	    for (i = 0 ; vechand_get(&op->dbs,i,&dbp) >= 0 ; i += 1) {
		if (dbp == nullptr) continue ;
		rs1 = db_finish(dbp) ;
		if (rs >= 0) rs = rs1 ;
		rs1 = uc_free(dbp) ;
		if (rs >= 0) rs = rs1 ;
	    } /* end for */
	} /* end if (dbs) */

	return rs ;
}
/* end subroutine (subinfo_dbfins) */


local int subinfo_mkdirnames(sip)
SI	*sip ;
{
	SPELLCHECKS	*op = sip->op ;

	int	rs = SR_OK ;
	int	tl ;
	int	c = 0 ;

	cchar	*sharedname = SC_DBDIR ;
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
	    if ((rs = mkpath2(tmpdname,sip->userhome,sharedname)) >= 0) {
	        tl = rs ;
	        if ((rs = subinfo_havedir(sip,tmpdname)) > 0) {
		    c += 1 ;
	            rs = vecstr_add(&sip->defdirs,tmpdname,tl) ;
	        }
	    }
	} /* end if */

/* system area */

	if (rs >= 0) {
	    if ((rs = mkpath2(tmpdname,op->pr,sharedname)) >= 0) {
	        tl = rs ;
	        if ((rs = subinfo_havedir(sip,tmpdname)) > 0) {
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
SI	*sip ;
char		tmpdname[] ;
{
	USTAT	sb ;

	int	rs = SR_OK ;
	int	rs1 ; /* lint-ok */
	int	f = false ;


	if ((rs1 = u_stat(tmpdname,&sb)) >= 0)
	    f = S_ISDIR(sb.st_mode) ? 1 : 0 ;

	return (rs >= 0) ? f : rs ;
}
/* end subroutine (subinfo_havedir) */

local int subinfo_ids(SI *sip) noex {
	int		rs = SR_OK ;
	if (! sip->fl.id) {
	    sip->fl.id = true ;
	    rs = ids_load(&sip->id) ;
	}
	return rs ;
}
/* end subroutine (subinfo_ids) */

local int subinfo_tmpuserdir(SI *sip) noex {
	int		rs ;
	int		dl ;
	cmode		dmode = 0775 ;
	char		tmpdname[MAXPATHLEN + 1] ;

	rs = subinfo_username(sip) ;

	if ((rs >= 0) && (sip->tudname == nullptr)) {

	    rs = mktmpuserdir(tmpdname,sip->username,IDXDNAME,dmode) ;
	    dl = rs ;
	    if (rs >= 0) {
		cchar	*dp ;
	        rs = uc_mallocstrw(tmpdname,dl,&dp) ;
		if (rs >= 0) sip->tudname = dp ;
	    }

	} /* end if */

	return rs ;
}
/* end subroutine (subinfo_tmpuserdir) */


local int subinfo_loadnames(sip,nlp,dirname)
SI	*sip ;
vecstr		*nlp ;
cchar	dirname[] ;
{
	USTAT	sb ;

	FSDIR		dir ;
	FSDIR_ENT	ds ;

	int	rs = SR_OK ;
	int	rs1 ;
	int	nl ;
	int	c = 0 ;

	cchar	*calsuf = SC_DBSUF ;
	cchar	*tp ;
	cchar	*np ;

	char	tmpfname[MAXPATHLEN + 1] ;


	rs = fsdir_open(&dir,dirname) ;
	if (rs < 0)
	    goto ret0 ;

	while (fsdir_read(&dir,&ds) > 0) {
	    if (ds.name[0] == '.') continue ;

	    if ((tp = strrchr(ds.name,'.')) != nullptr) {

		rs1 = mkpath2(tmpfname,dirname,ds.name) ;

	   	if (rs1 >= 0) {
		    rs1 = u_stat(tmpfname,&sb) ;
		}

		if ((rs1 >= 0) && S_ISREG(sb.st_mode)) {

		if (strcmp((tp+1),calsuf) == 0) {

		    np = ds.name ;
		    nl = (tp - ds.name) ;

		    c += 1 ;
		    rs = vecstr_add(nlp,np,nl) ;
	            if (rs < 0)
		        break ;

	        } /* end if (correct file extension) */

		} /* end if (regular file) */

	    } /* end if */

	} /* end while */

ret1:
	fsdir_close(&dir) ;

ret0:
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (subinfo_loadnames) */


local int subinfo_havestart(sip,qp,lp,ll)
SI	*sip ;
SC_CITE	*qp ;
cchar	*lp ;
int		ll ;
{
	int		rs1 = SR_OK ;
	int		ch ;
	int		cl ;
	int		si = 0 ;
	int		f ;
	cchar	*tp, *cp ;

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

#if	CF_TRANSHOL
		rs1 = subinfo_transhol(sip,qp,lp,si) ;
#else
		rs1 = SR_NOTSUP ;
#endif

	} /* end if */

	if (rs1 >= 0) {
	    si += siskipwhite((lp+si),(ll-si)) ;
	}

ret1:
ret0:

	return (rs1 >= 0) ? si : rs1 ;
}
/* end subroutine (subinfo_havestart) */

local int subinfo_year(SI *sip) noex {
	TMTIME		tm ;
	int		rs = SR_OK ;
	if (sip->year == 0) {
	    rs = tmtime_timelocal(&tm,sip->daytime) ;
	    sip->year = (tm.year + TM_YEAR_BASE) ;
	    sip->isdst = tm.isdst ;
	    sip->gmtoff = tm.gmtoff ;
	}
	return rs ;
}
/* end subroutine (subinfo_year) */


local int subinfo_mkday(sip,m,cp,cl)
SI	*sip ;
int		m ;
cchar	*cp ;
int		cl ;
{
	DAYOFMONTH	*dmp ;
	int		rs = SR_OK ;
	dmp = &sip->dom ;

/* open the DAYOFMONTH database (manager?) if it is not already open */

	if (! sip->fl.dom) {
	    rs = dayofmonth_start(dmp,sip->year) ;
	    sip->fl.dom = (rs >= 0) ;
	}

	if (rs >= 0) {
	    rs = dayofmonth_mkday(dmp,m,cp,cl) ;
	}

	return rs ;
}
/* end subroutine (subinfo_mkday) */


local int subinfo_transhol(sip,qp,sp,sl)
SI	*sip ;
SC_CITE	*qp ;
cchar	*sp ;
int		sl ;
{
	HOLIDAYS_CUR	hcur ;
	HOLIDAYS	*holp ;

	SPELLCHECKS	*op ;

	TMTIME		tm{} ;

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
	    cint	hollen = HOLBUFLEN ;
	    char	holbuf[HOLBUFLEN + 1] ;

	    if ((holidays_curbegin(holp,&hcur)) >= 0) {
	
	        rs = holidays_fetchname(holp,sp,sl,&hcur,&hc,holbuf,hollen) ;
	        if (rs >= 0) {
		    f_found = true ;
		    qp->m = hc.m ;
		    qp->d = hc.d ;
	        }

	        holidays_curend(holp,&hcur) ;
	    } /* end if (cursor) */

	} /* end if */

	if ((rs >= 0) && f_found && (nl > 0)) {

	    if (! f_inityear)
		rs = subinfo_year(sip) ;

	    if (rs >= 0) {
		int	odays ;

		if ((rs = cfdeci(np,nl,&odays)) >= 0) {
		    time_t	t ;

		    if (f_negative) odays = (- odays) ;

		    tm = {} ;
		    tm.isdst = sip->isdst ;
		    tm.gmtoff = sip->gmtoff ;
		    tm.year = (sip->year - TM_YEAR_BASE) ;
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


local int subinfo_checkdname(sip,dname)
SI	*sip ;
cchar	dname[] ;
{
	USTAT	sb ;

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
	        rs = permid(&sip->id,&sb,W_OK) ;
	}

ret0:
	return rs ;
}
/* end subroutine (subinfo_checkdname) */


local int cachedir_start(CACHEDIR *cdp,STRDESC *dp,int nf)
{
	int	rs = SR_OK ;
	int	i ;
	int	sz = 0 ;
	char	*bp ;

	{
	    int		cl ;
	    cchar	*cp ;
	    for (i = 0 ; i < nf ; i += 1) {
		cp = dp[i].sp ;
		cl = dp[i].sl ;
		if (cl < 0) cl = lenstr(cp) ;
	        sz += (cl + 1) ;
	    } /* end for */
	}

	if ((rs = uc_malloc(sz,&bp)) >= 0) {
	    cdp->a = bp ;
	    for (i = 0 ; i < nf ; i += 1) {
		switch (i) {
		case 0:
		    cdp->sname = bp ;
		    break ;
		case 1:
		    cdp->dname = bp ;
		    break ;
		} /* end switch */
		if (dp[i].sp != nullptr) {
		    bp = (strwcpy(bp,dp[i].sp,dp[i].sl) + 1) ;
		}
	    } /* end for */
	} /* end if (memory-allocation) */

	return rs ;
}
/* end subroutine (cachedir_start) */


local int cachedir_finish(CACHEDIR *cdp)
{
	int		rs = SR_OK ;
	int		rs1 ;

	if (cdp->a != nullptr) {
	    rs1 = uc_free(cdp->a) ;
	    if (rs >= 0) rs = rs1 ;
	    cdp->a = nullptr ;
	}

	return rs ;
}
/* end subroutine (cachedir_finish) */

local int db_start(DB *dbp,STRDESC *dp,int nf) noex {
	int	rs = SR_OK ;
	int	sz = 0 ;

	memclear(dbp) ;

	{
	    int		cl ;
	    cchar	*cp ;
	    for (int i = 0 ; i < nf ; i += 1) {
		cp = dp[i].sp ;
		cl = dp[i].sl ;
		if (cl < 0) cl = lenstr(cp) ;
	        sz += (cl + 1) ;
	    } /* end for */
	}

	if (char *bp ; (rs = uc_malloc(sz,&bp)) >= 0) {
	    cdp->a = bp ;
	    for (int i = 0 ; i < nf ; i += 1) {
		switch (i) {
		case 0:
		    dbp->idxname = bp ; /* index file name */
		    break ;
		case 1:
		    dbp->dbfname = bp ; /* DB (actual list) file-name */
		    break ;
		case 2:
		    dbp->cdname = bp ; /* cache directory name */
		    break ;
		} /* end switch */
		if (dp[i].sp != nullptr) {
		    bp = (strwcpy(bp,dp[i].sp,dp[i].sl) + 1) ;
		}
	    } /* end for */
	} /* end if (memory-allocation) */

	return rs ;
}
/* end subroutine (db_start) */

local int db_finish(DB *dbp) noex {
	int		rs = SR_OK ;
	int		rs1 ;

	if (dbp->a != nullptr) {
	    rs1 = uc_free(dbp->a) ;
	    if (rs >= 0) rs = rs1 ;
	    dbp->a = nullptr ;
	}

	return rs ;
}
/* end subroutine (db_finish) */

local int entry_start(SC_ENT *ep,SC_CITE *qp,int loff,int llen) noex {
	struct spellchecks_eline	*elp ;

	int		rs = SR_OK ;
	int		ne = SC_NLE ;
	int		sz ;

	if (ep == nullptr)
	    return SR_FAULT ;

	memclear(ep) ;
	ep->cidx = -1 ;
	ep->m = qp->m ;
	ep->d = qp->d ;
	ep->voff = loff ;
	ep->vlen = llen ;

	sz = ne * szof(struct spellchecks_eline) ;
	if ((rs = uc_malloc(sz,&elp)) >= 0) {
	    ep->lines = elp ;
	    ep->e = ne ;
	    elp->loff = loff ;
	    elp->llen = llen ;
	    ep->i += 1 ;
	}

	return rs ;
}
/* end subroutine (entry_start) */


local int entry_setidx(ep,cidx)
SC_ENT	*ep ;
int		cidx ;
{


	if (ep == nullptr)
	    return SR_FAULT ;

	ep->cidx = cidx ;
	return SR_OK ;
}

/* end subroutine (entry_setidx) */


local int entry_add(ep,loff,llen)
SC_ENT	*ep ;
uint		loff, llen ;
{
	struct spellchecks_eline	*elp ;

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
	    ne = (ep->e * 2) + SC_NLE ;
	    sz = ne * szof(struct spellchecks_eline) ;
	    if ((rs = uc_realloc(ep->lines,sz,&elp)) >= 0) {
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


local int entry_finish(ep)
SC_ENT	*ep ;
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
	    rs1 = uc_free(ep->lines) ;
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
SC_ENT	*ep ;
SC_ENT	*oep ;
{
	int	rs1 = SR_OK ;


	if ((ep->m == oep->m) && (ep->d == oep->d))
	    rs1 = 1 ;

	return rs1 ;
}
/* end subroutine (entry_samecite) */

#endif /* CF_SAMECITE */


local int entry_samehash(ep,op,oep)
SC_ENT	*ep ;
SPELLCHECKS	*op ;
SC_ENT	*oep ;
{
	int	rs = SR_OK ;


/* the following checks (code) are not needed in the present implementation! */

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
SC_ENT	*ep ;
SPELLCHECKS	*op ;
{
	SC_CAL	*calp ;

	int	rs = SR_OK ;
	int	sl, cl ;

	cchar	*sp ;
	cchar	*cp ;


	if (ep == nullptr)
	    return SR_FAULT ;

	if (ep->e <= 0)
	    return SR_NOTOPEN ;

	if (ep->lines == nullptr)
	    return SR_NOTOPEN ;

	if ((rs = vechand_get(&op->cals,ep->cidx,&calp)) >= 0) {
	    if (cchar *mp ; (rs = cal_mapdata(calp,&mp)) >= 0) {
		spellchecks_eline	*elp = ep->lines ;
	        uint	hash = 0 ;
		int	i ;
	        for (i = 0 ; i < ep->i ; i += 1) {
	            sp = (mp + elp[i].loff) ;
	            sl = elp[i].llen ;
	            while ((cl = nextfield(sp,sl,&cp)) > 0) {
		        hash += hash_elf(cp,cl) ;
		        sl -= intconv((cp + cl) - sp) ;
		        sp = (cp + cl) ;
	            } /* end while */
	        } /* end for */
	        ep->hash = hash ;
	        ep->fl.hash = true ;
	    } /* end if (cal_mapdata) */
	} /* end if (vechand_get) */

	return rs ;
}
/* end subroutine (entry_mkhash) */

local int entry_sethash(SC_ENT *ep,uint hash) noex {
	ep->hash = hash ;
	ep->fl.hash = true ;
	return SR_OK ;
}
/* end subroutine (entry_sethash) */


local int entry_same(ep,op,oep)
SC_ENT	*ep ;
SPELLCHECKS	*op ;
SC_ENT	*oep ;
{
	WORDER	w1, w2 ;

	int	rs = SR_OK ;
	int	c1l, c2l ;
	int	f = false ;

	cchar	*c1p, *c2p ;


	if ((rs = worder_start(&w1,op,ep)) >= 0) {

	if ((rs = worder_start(&w2,op,oep)) >= 0) {

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
	} /* end if (w2) */

	worder_finish(&w1) ;
	} /* end if (w1) */

	return (rs >= 0) ? f : rs ;
}
/* end subroutine (entry_same) */


local int entry_loadbuf(ep,mp,rbuf,rlen)
SC_ENT	*ep ;
cchar	*mp ;
char		rbuf[] ;
int		rlen ;
{
	struct spellchecks_eline	*lines ;

	SBUF	b ;

	int	rs ;
	int	i ;
	int	nlines ;
	int	len = 0 ;

	lines = ep->lines ;
	nlines = ep->i ; /* number of line elements */

	if ((rs = sbuf_start(&b,rbuf,rlen)) >= 0) {
	    int		ll ;
	    cchar	*lp ;

	    for (i = 0 ; i < nlines ; i += 1) {

	        if (i > 0) sbuf_chr(&b,' ') ;

	        lp = (mp + lines[i].loff) ;
	        ll = lines[i].llen ;

	        rs = sbuf_strw(&b,lp,ll) ;

	        if (rs < 0) break ;
	    } /* end for */

	    len = sbuf_finish(&b) ;
	    if (rs >= 0) rs = len ;
	} /* end if (sbuf) */

	return (rs >= 0) ? len : rs ;
} 
/* end subroutine (entry_loadbuf) */


local int mkbve_start(bvep,sip,ep)
CYIMK_ENT	*bvep ;
SI	*sip ;
SC_ENT	*ep ;
{
	int	rs ;
	int	nlines = 0 ;


	if (ep == nullptr)
	    return SR_FAULT ;

	if ((rs = entry_mkhash(ep,sip->op)) >= 0) {
	    bvep->m = ep->m ;
	    bvep->d = ep->d ;
	    bvep->voff = ep->voff ;
	    bvep->vlen = ep->vlen ;
	    bvep->hash = ep->hash ;
	    bvep->lines = nullptr ;
	    nlines = ep->i ;
	    if (nlines <= UCHAR_MAX) {
		CYIMK_LINE	*lines ;
	        cint	sz = (nlines + 1) * szof(CYIMK_LINE) ;
	        bvep->nlines = nlines ;
	        if ((rs = uc_malloc(sz,&lines)) >= 0) {
		    int	i ;
		    bvep->lines = lines ;
	            for (i = 0 ; i < nlines ; i += 1) {
		        lines[i].loff = ep->lines[i].loff ;
		        lines[i].llen = ep->lines[i].llen ;
	            }
		    lines[i].loff = 0 ;
		    lines[i].llen = 0 ;
	        } /* end if (memory-allocation) */
	    } else
	        rs = SR_TOOBIG ;
	} /* end if ((entry_mkhash) */

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
	    rs1 = uc_free(bvep->lines) ;
	    if (rs >= 0) rs = rs1 ;
	    bvep->lines = nullptr ;
	}

	return rs ;
}
/* end subroutine (mkbve_finish) */


int worder_start(wp,op,ep)
WORDER		*wp ;
SPELLCHECKS	*op ;
SC_ENT	*ep ;
{
	SC_CAL	*calp ;
	int		rs ;

	if ((rs = vechand_get(&op->cals,ep->cidx,&calp)) >= 0) {
	    cchar	*mp ;
	    if ((rs = cal_mapdata(calp,&mp)) >= 0) {
		struct spellchecks_eline	*lines = ep->lines ;
	        wp->i = 0 ;
	        wp->nlines = ep->i ;
	        wp->lines = ep->lines ;
	        wp->mp = mp ;
	        if (lines != nullptr) {
	            wp->sp = (mp + lines[0].loff) ;
	            wp->sl = (lines[0].llen) ;
	        }
	    } /* end if (cal_mapdata) */
	} /* end if (vechand_get) */

	return rs ;
}
/* end subroutine (worder_start) */


/* ARGSUSED */
int worder_finish(wp)
WORDER		*wp ;
{
	if (wp == nullptr) return SR_FAULT ;
	return SR_OK ;
}
/* end subroutine (worder_finish) */


int worder_get(wp,rpp)
WORDER		*wp ;
cchar	**rpp ;
{
	int		cl = 0 ;
	cchar	*cp ;

	while (wp->i < wp->nlines) {

	    cl = nextfield(wp->sp,wp->sl,&cp) ;
	    if (cl > 0) {
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

	if (rpp != nullptr)
	    *rpp = cp ;

	return cl ;
}
/* end subroutine (worder_get) */

local int config_start(config *csp,subinfo *sip,cchar *cfname) noex {
	int	rs = SR_OK ;
	char	tmpfname[MAXPATHLEN+1] = { 0 } ;


	if (csp == nullptr) return SR_FAULT ;

	if (cfname == nullptr) cfname = SC_CONFNAME ;

	memclear(csp) ;
	csp->sip = sip ;

	if (strchr(cfname,'/') == nullptr) {
	    rs = config_findfile(csp,tmpfname,cfname) ;
	    if (rs > 0) cfname = tmpfname ;
	}

	if ((rs >= 0) && (sip->debuglevel > 0))
	    shio_printf(sip->efp,"%s: conf=%s\n",
	        sip->progname,cfname) ;

	if (rs >= 0) {
	    if ((rs = paramfile_open(&csp->p,sip->envv,cfname)) >= 0) {
	        if ((rs = config_cookbegin(csp)) >= 0) {
	            csp->f_p = (rs >= 0) ;
	        }
	        if (rs < 0)
	            paramfile_close(&csp->p) ;
	    } else if (isNotPresent(rs)) {
	        rs = SR_OK ;
	    }
	} else if (isNotPresent(rs)) {
	    rs = SR_OK ;
	}

	return rs ;
}
/* end subroutine (config_start) */

local int config_finish(config *csp) noex {
	subinfo		*sip = csp->sip ;
	int		rs = SR_OK ;
	int		rs1 ;

	if (csp == nullptr) return SR_FAULT ;

	if (csp->f_p) {

	    if (csp->f_c) {
	        rs1 = config_cookend(csp) ;
	        if (rs >= 0) rs = rs1 ;
	    }

	    rs1 = paramfile_close(&csp->p) ;
	    if (rs >= 0) rs = rs1 ;

	    csp->f_p = false ;
	} /* end if (active) */

	return rs ;
}
/* end subroutine (config_finish) */

local int config_cookbegin(config *csp) noex {
	subinfo		*sip = csp->sip ;
	expcook		*ecp = &csp->c ;
	int		rs ;
	int		c = 0 ;

	if ((rs = expcook_start(ecp)) >= 0) {
	    cint	hlen = MAXHOSTNAMELEN ;
	    int		i ;
	    int		kch ;
	    int		vl ;
	    cchar	*ks = "PSNDHRUsrpuh" ;
	    cchar	*vp ;
	    char	hbuf[MAXHOSTNAMELEN+1] ;
	    char	kbuf[2] ;

	    kbuf[1] = '\0' ;
	    for (i = 0 ; (rs >= 0) && (ks[i] != '\0') ; i += 1) {
	        kch = MKCHAR(ks[i]) ;
	        vp = nullptr ;
	        vl = -1 ;
	        switch (kch) {
	        case 'P':
	        case 'p':
	        case 'r':
	            vp = sip->progname ;
	            break ;
	        case 'S':
	        case 's':
	            vp = sip->searchname ;
	            break ;
	        case 'N':
	            vp = sip->nodename ;
	            break ;
	        case 'D':
	            vp = sip->domainname ;
	            break ;
	        case 'H':
	            {
	                cchar	*nn = sip->nodename ;
	                cchar	*dn = sip->domainname ;
	                rs = snsds(hbuf,hlen,nn,dn) ;
	                vl = rs ;
	                if (rs >= 0) vp = hbuf ;
	            }
	            break ;
	        case 'R':
	            vp = sip->pr ;
	            break ;
	        case 'U':
	        case 'u':
	            vp = sip->username ;
	            break ;
		case 'h':
	            vp = sip->userhome ;
	            break ;
	        } /* end switch */
	        if ((rs >= 0) && (vp != nullptr)) {
		    c += 1 ;
	            kbuf[0] = kch ;
	            rs = expcook_add(ecp,kbuf,vp,vl) ;
	        }
	    } /* end for */

	    if (rs >= 0) {
		cchar	*kp ;
	        for (i = 0 ; (rs >= 0) && (i < cook_overlast ; i += 1) {
		    kp = cooks[i] ;
		    vp = nullptr ;
		    vl = -1 ;
		    switch (i) {
		    case cook_pr:
			vp = sip->pr ;
			break ;
		    case cook_pn:
			{
			    int		cl ;
			    cchar	*cp ;
			    if ((cl = sfbasename(sip->pr,-1,&cp)) > 0) {
				vp = cp ;
				vl = cl ;
			    }
			}
			break ;
		    case cook_bn:
			if (sip->dbfname != nullptr) {
			    int		cl ;
			    cchar	*cp ;
			    if ((cl = sfbasename(sip->dbfname,-1,&cp)) > 0) {
				vp = cp ;
				vl = cl ;
			    }
			} else
			    vp = "null" ;
			break ;
		    } /* end switch */
	            if ((rs >= 0) && (vp != nullptr)) {
		        c += 1 ;
	                rs = expcook_add(ecp,kp,vp,vl) ;
	            }
		} /* end for */
	    } /* end if */

	    if (rs >= 0) {
	        op->f_c = true ;
	    } else
	        expcook_finish(ecp) ;
	} /* end if (expcook_start) */

	return (rs >= 0) ? c : rs ;
}
/* end subroutine (config_cookbegin) */

local int config_cookend(config *csp) noex {
	int		rs = SR_OK ;
	int		rs1 ;
	if (csp->f_c) {
	    csp->f_c = false ;
	    rs1 = expcook_finish(&csp->c) ;
	    if (rs >= 0) rs = rs1 ;
	}
	return rs ;
}
/* end subroutine (config_cookend) */

local int config_read(config *op) noex {
	LOCINFO		*lip = op->lip ;
	int		rs = SR_OK ;
	int		rs1 ;

	if (pip == nullptr) return SR_FAULT ;

	lip = sip->lip ;
	if (lip == nullptr) return SR_FAULT ;

	if (op->f_p) {
	    cint	plen = PBUFLEN ;
	    int		sz ;
	    char	*pbuf ;
	    sz = (plen+1) ;
	    if (rs = uc_malloc(sz,&pbuf)) >= 0) {
	        rs = config_reader(op,pbuf,plen) ;
		uc_free(pbuf) ;
	    } /* end if (memory-allocation) */
	}

	return rs ;
}
/* end subroutine (config_read) */

local int config_reader(config *op,char *pbuf,int plen) noex {
	paramfile	*pfp = &op->p ;
	paramfile_ent	pe ;
	int		rs ;

	if (paramfile_cur cur ; (rs = paramfile_curbegin(pfp,&cur)) >= 0) {
	    expcook	*ecp = &op->c ;
	    cint	elen = EBUFLEN ;
	    int		vl, el ;
	    int		ml ;
	    int		pi ;
	    int		v ;
	    cchar	*kp ;
	    cchar	*vp ;
	    char	ebuf[EBUFLEN + 1] ;

	    while (rs >= 0) {
	        kl = paramfile_curenum(pfp,&cur,&pe,pbuf,plen) ;
	        if (kl == SR_NOTFOUND) break ;
	        rs = kl ;
	        if (rs < 0) break ;

	            kp = pe.key ;
	            vp = pe.value ;
	            vl = pe.vlen ;

	            pi = matpstr(params,2,kp,kl) ;
	            if (pi < 0) continue ;

	            ebuf[0] = '\0' ;
	            el = 0 ;
	            if (vl > 0) {
	                el = expcook_exp(ecp,0,ebuf,elen,vp,vl) ;
	                if (el >= 0) ebuf[el] = '\0' ;
	            } /* end if */

	            if (el < 0) continue ;

		switch (pi) {

		case cparam_logsize:
				if (el > 0) {
	                            if (cfdecmfi(ebuf,el,&v) >= 0) {
	                                if (v >= 0) {
	                                    switch (i) {
	                                    case cparam_logsize:
	                                        sip->logsize = v ;
	                                        break ;
	                                    } /* end switch */
	                                }
	                            } /* end if (valid number) */
				}
	                        break ;

		case cparam_logfile:
				if (el > 0) {
	                            if (! sip->final.lfname) {
	                                sip->final.lfname = true ;
	                                sip->have.lfname = true ;
				        rs = config_setlfname(op,ebuf,el) ;
	                            }
				}
	                        break ;

		case cparam_cachedir:
		    if (el > 0) {
			rs = config_cachedir(op,ebuf,el) ;
		    }
		    break ;

		case cparam_db:
		    if (el > 0) {
			rs = config_db(op,ebuf,el) ;
		    }
		    break ;

		} /* end switch */

	    } /* end while (emumerating) */

	    paramfile_curend(pfp) ;
	} /* end if (cursor) */

	return rs ;
}
/* end subroutine (config_reader) */

local int config_setlfname(config *cfp,cchar *vp,int vl) noex {
	subinfo		*sip = cfp->sip ;
	cchar	*lfn ;
	cchar	*pr ;
	cchar	*sn ;
	char		tbuf[MAXPATHLEN_1] ;
	int	rs = SR_OK ;
	int	tl ;

	pr = sip->pr ;
	sn = sip->sn ;
	lfn = sip->lfname ;
	tl = prmkfname(pr,tbuf,vp,vl,true,LOGCNAME,sn,"") ;

	if ((lfn == nullptr) || (strcmp(lfn,tbuf) != 0)) {
	    cchar	**vpp = &sip->lfname ;
	    sip->changed.lfname = true ;
	    rs = subinfo_setentry(sip,vpp,tbuf,-1) ;
	}

	return rs ;
}
/* end subroutine (config_setlfname) */

local int config_cachedir(config *csp,cchar *pp,int pl) noex {
	STRDESC		d[CACHEDIR_NFS] ;
	cint	nf = CACHEDIR_NFS ;
	int		rs = SR_OK ;
	int		fi = 0 ;
	int		si ;
	int		f = false ;

	while ((fi < nf) && ((si = sichr(pp,pl,CH_FS)) >= 0)) {
	    rs = config_cachedirone(csp,d,fi++,pp,si) ;
	    pl -= (si+1) ;
	    pp += (si+1) ;
	    if (rs < 0) break ;
	} /* end while */
	if ((rs >= 0) && (fi < nf) && (pl > 0)) {
	    rs = config_cachedirone(csp,d,fi++,pp,pl) ;
	}

	if ((rs >= 0) && (fi >= nf)) {
	    cint	sz = szof(CACHEDIR) ;
	    void	*p ;
	    if ((rs = uc_malloc(sz,&p)) >= 0) {
		CACHEDIR	*cdp = p ;
	        if ((rs = cachedir_start(cdp,d)) >= 0) {
		    SI	*sip = csp->sip ;
		    f = true ;
		    rs = subinfo_cachedir(sip,cdp) ;
		    if (rs < 0)
			cachedir_finish(cdp) ;
		} /* end if (start) */
		if (rs < 0)
		    uc_free(p) ;
	    } /* end if (memory-allocation) */
	} /* end if (had data for new entry) */

	return (rs >= 0) ? f : rs ;
}
/* end subroutine (config_cachedir) */

local int config_cachedirone(config *csp,STRDESC *dp,int fi,
		cc *pp,int pl) noex {
	int		rs = SR_OK ;
		switch (fi) {
		case 0:
		case 1:
		    dp[fi].sp = pp ;
		    dp[fi].sl = pl ;
		    break ;
		} /* end switch */

	return rs ;
}
/* end subroutine (config_cachedirone) */

local int config_db(config *csp,cchar *ebuf,int el) noex {
	STRDESC		d[DB_NFS] ;
	cint		nf = DB_NFS ;
	int		rs = SR_OK ;
	int		fi = 0 ;
	int		si ;
	int		f = false ;

	while ((fi < nf) && ((si = sichr(pp,pl,CH_FS)) >= 0)) {
	    rs = config_dbone(csp,d,fi++,pp,si) ;
	    pl -= (si+1) ;
	    pp += (si+1) ;
	    if (rs < 0) break ;
	} /* end while */
	if ((rs >= 0) && (fi < nf) && (pl > 0)) {
	    rs = config_dbone(csp,d,fi++,pp,pl) ;
	}

	if ((rs >= 0) && (fi >= nf)) {
	    SI	*sip = csp->sip ;
	    int		sch = (d[1].sp[0] & 0xff) ;
	    char	dbuf[MAXPATHLEN+1] ;
	    if ((sch == '-') && (sip->dbfname != nullptr)) {
		d[1].sp = sip->dbfname ;
		d[1].sl = -1 ;
	    }
	    if ((sch != '/') && (sch != '-')) {
		rs = mkpath2(dbuf,sip->pr,d[1]) ;
		d[1].sl = rs ;
		d[1].sp = dbuf ;
	    }
	    if (rs >= 0) {
		int	f_skip = (sch == '-') ;
		if (USTAT sb ; f_skip || (u_stat(d[1],&sb) >= 0)) {
		    if (f_skip || ((rs = permid(&sip->id,&sb,R_OK)) >= 0)) {
	                cint	sz = szof(DB) ;
	                void	*p ;
	                if ((rs = uc_malloc(sz,&p)) >= 0) {
		            DB	*dbp = p ;
	                    if ((rs = db_start(dbp,d,nf)) >= 0) {
		                SI	*sip = csp->sip ;
		                f = true ;
		                rs = subinfo_db(sip,dbp) ;
		                if (rs < 0) {
			            db_finish(dbp) ;
				}
		            } /* end if (start) */
		            if (rs < 0) {
		                uc_free(p) ;
			    }
	                } /* end if (memory-allocation) */
		    } else (rs == SR_ACCESS) {
			rs = SR_OK ;
		    }
		} /* end if (stat) */
	    } /* end if (ok) */
	} /* end if (had data for new entry) */

	return (rs >= 0) ? f : rs ;
}
/* end subroutine (config_db) */

local int config_dbone(config *csp,STRDESC *dp,int fi,cc *pp,int pl) noex {
	int	rs = SR_OK ;

		switch (fi) {
		case 0:
		case 1:
		case 2:
		    dp[fi].sp = pp ;
		    dp[fi].sl = pl ;
		    break ;
		} /* end switch */

	return rs ;
}
/* end subroutine (config_dbone) */

#if	CF_CONFIGCHECK
local int config_check(config *csp) noex {
	SI	*sip = csp->sip ;
	int	rs = SR_OK ;

	if (csp->f_p) {
	    if ((rs = paramfile_check(&csp->p,sip->daytime)) > 0) {
	        rs = config_read(op) ;
	    }
	}

	return rs ;
}
/* end subroutine (config_check) */
#endif /* CF_CONFIGCHECK */

#ifdef	COMMENT
local int config_findfile(config *csp,char *tbuf,cchar *cfname) noex {
	subinfo		*sip = csp->sip ;
	vecstr		sv ;
	int		rs ;
	int		tl = 0 ;

	tbuf[0] = '\0' ;
	if ((cfname != nullptr) && (cfname[0] != '\0')) {
	    if ((rs = vecstr_start(&sv,6,0)) >= 0) {
	        cint	tlen = MAXPATHLEN ;
	        int		i ;
	        int		vl ;
	        int		kch ;
	        cchar	*ks = "pen" ;
	        cchar	*vp ;
	        char	kbuf[2] ;
	        kbuf[1] = '\0' ;
	        for (i = 0 ; (rs >= 0) && (ks[i] != '\0') ; i += 1) {
		    kch = (ks[i] & 0xff) ;
		    kbuf[0] = kch ;
		    vp = nullptr ;
		    vl = -1 ;
		    switch (kch) {
		    case 'p':
		        vp = sip->pr ;
		        break ;
		    case 'e':
		        vp = "etc" ;
		        break ;
		    case 'n':
		        vp = sip->searchname ;
		        break ;
		    } /* end switch */
		    if (rs >= 0) {
	    	        rs = vecstr_envset(&sv,"p",sip->pr,-1) ;
		    }
	        } /* end for */
	        if (rs >= 0) {
	            rs = permsched(sched1,&sv,tbuf,tlen,cfname,R_OK) ;
	            tl = rs ;
	        }
	        vecstr_finish(&sv) ;
	    } /* end if (finding file) */
	} /* end if (non-null) */

	return (rs >= 0) ? tl : rs ;
}
/* end subroutine (config_findfile) */
#endif /* COMMENT */

static bool isempty(cchar *lp,int ll) noex {
	int		cl ;
	bool		f = false ;
	f = f || (ll == 0) ;
	f = f || (lp[0] == '#') ;
	if ((! f) && CHAR_ISWHITE(*lp)) {
	    cchar	*cp ;
	    cl = sfskipwhite(lp,ll,&cp) ;
	    f = ((cl == 0) || (cp[0] == '#')) ;
	}
	return f ;
}
/* end subroutine (isempty) */

local int mkmonth(cchar *cp,int cl) noex {
	int		rs ;
	int		v = 0 ;
	if ((rs = cfdeci(cp,cl,&v)) >= 0) {
	    v -= 1 ;
	}
	return (rs >= 0) ? v : rs ;
}
/* end subroutine (mkmonth) */

/* for use with |vecobj_sort(3uc)| or similar */
local int vrcmp(cvoid **v1pp,cvoid **v2pp) noex {
	SC_ENT		*e1p = (SC_ENT **) *v1pp ;
	SC_ENT		*e2p = (SC_ENT **) *v2pp ;
	int		rc = 0 ;
	if (e1p || e2p) {
	    rc = +1 ;
	    if (e1p) {
		rc = -1 ;
		if (e2p) {
		    if ((rc = (e1p->m - e2p->m)) == 0) {
	    		rc = (e1p->d - e2p->d) ;
		    }
		}
	    }
	}
	return rc ;
}
/* end subroutine (vrcmp) */


