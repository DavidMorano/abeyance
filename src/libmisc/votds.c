/* votds SUPPORT (VOTD system Shared-memory management) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* VOTDs system Cache management */
/* version %I% last-modified %G% */

#define	CF_DEBUGS	0		/* compile-time debug print-outs */
#define	CF_GETACOUNT	0		/* |votds_getacount()| */
#define	CF_UPDATE	0		/* |votds_update()| */

/* revision history:

	= 1998-05-01, David A­D­ Morano
	This was created along with the DATE object.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Name:
	votds

	Description:
	This modules provides management for the system Verse-of-the-Day
	(VOTD) cache.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/stat.h>
#include	<sys/mman.h>
#include	<unistd.h>
#include	<climit.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstdarg>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<uclibmem.h>
#include	<intceil.h>
#include	<estrings.h>
#include	<filer.h>
#include	<storebuf.h>
#include	<ptma.h>
#include	<ptm.h>
#include	<sigblocker.h>
#include	<endian.h>
#include	<localmisc.h>

#include	"votds.h"
#include	"votdshdr.h"
#include	"cvtdater.h"
#include	"shmalloc.h"


/* local defines */

#define	VOTDS_OBJNAME		"votds"
#define	VOTDS_SHMPOSTFIX	"votds"
#define	VOTDS_PERMS		0666
#define	VOTDS_MUSIZE		sizeof(PTM)
#define	VOTDS_LANGSIZE		(VOTDS_NLANGS*sizeof(VOTDS_LANG))
#define	VOTDS_BOOKSIZE		(VOTDS_NBOOKS*sizeof(VOTDS_BOOK))
#define	VOTDS_VERSESIZE		(VOTDS_NVERSES*sizeof(VOTDS_VERSE))
#define	VOTDS_MINSIZE		\
				VOTDS_LANGSIZE+ \
				VOTDS_BOOKIZE+ \
				VOTDS_VERSESIZE+ \
				VOTDS_BSTRSIZE+ \
				VOTDS_VSTRSIZE+ \
				(2*sizeof(SHMALLOC))
#define	VOTDS_BOOKLEN		80 /* should match 'BIBLEBOOK_LEN' */

#ifndef	LOGICVAL
#define	LOGICVAL(v)	((v)!=0)
#endif

#ifndef	LINEBUFLEN
#ifdef	LINE_MAX
#define	LINEBUFLEN	MAX(LINE_MAX,2048)
#else
#define	LINEBUFLEN	2048
#endif
#endif

#ifndef	SHMNAMELEN
#define	SHMNAMELEN	14		/* shared-memory name length */
#endif

#ifndef	SHMPREFIXLEN
#define	SHMPREFIXLEN	8
#endif

#ifndef	SHMPOSTFIXLEN
#define	SHMPOSTFIXLEN	4
#endif

#define	HDRBUFLEN	(sizeof(VOTDSHDR) + MAXNAMELEN)

#ifndef	TO_WAITSHM
#define	TO_WAITSHM	(1*60)		/* seconds */
#endif

#define	TO_LASTCHECK	5		/* seconds */
#define	TO_DBWAIT	1		/* seconds */
#define	TO_DBPOLL	300		/* milliseconds */


/* external subroutines */


/* exported variables */

VOTDS_OBJ	votds = {
	VOTDS_OBJNAME,
	sizeof(VOTDS)
} ;


/* local structures */


/* forward references */

local int	votds_shmhandbegin(VOTDS *,cchar *) ;
local int	votds_shmhandend(VOTDS *) ;

local int	votds_shmbegin(VOTDS *,int,mode_t) ;
local int	votds_shmend(VOTDS *) ;

local int	votds_mapbegin(VOTDS *,time_t,int) ;
local int	votds_mapend(VOTDS *) ;

local int	votds_shmhdrin(VOTDS *,VOTDSHDR *) ;
local int	votds_shmprep(VOTDS *,time_t,int,mode_t,VOTDSHDR *) ;
local int	votds_shmpreper(VOTDS *,time_t,int,mode_t,VOTDSHDR *) ;
local int	votds_shmwriter(VOTDS *,time_t,int fd,VOTDSHDR *,
			cchar *,int) ;
local int	votds_allocinit(VOTDS *,VOTDSHDR *) ;
local int	votds_mutexinit(VOTDS *) ;
local int	votds_verify(VOTDS *) ;

local int	votds_bookslotfind(VOTDS *,cchar *) ;
local int	votds_bookslotload(VOTDS *,time_t,int,cchar *,
			cchar **) ;
local int	votds_bookslotdump(VOTDS *,int) ;
local int	votds_verselangdump(VOTDS *,int) ;

local int	votds_booklanghave(VOTDS *,cchar *) ;
local int	votds_versehave(VOTDS *,int,int) ;
local int	votds_verseslotfind(VOTDS *) ;
local int	votds_verseslotfinder(VOTDS *) ;

local int	votds_mktitles(VOTDS *,cchar *,int) ;
local int	votds_titlematcher(VOTDS *,int,int,cchar *,int) ;
local int	votds_titlevalid(VOTDS *,int) ;
local int	votds_titletouse(VOTDS *) ;
local int	votds_access(VOTDS *) ;
local int	votds_getwcount(VOTDS *) ;
local int	votds_titlefins(VOTDS *) ;

#if	CF_GETACOUNT
local int	votds_getacount(VOTDS *) ;
#endif /* CF_GETACOUNT */

#if	CF_UPDATE
local int	votds_update(VOTDS *) ;
#endif /* CF_UPDATE */

local int	verse_dump(VOTDS_VERSE *,SHMALLOC *,int) ;
local int	verse_match(VOTDS_VERSE *,int,int) ;
local int	verse_read(VOTDS_VERSE *,char *,VOTDS_CITE *,char *,int) ;
local int	verse_load(VOTDS_VERSE *,time_t,int,SHMALLOC *,char *,
			VOTDS_CITE *,int,cchar *,int) ;
local int	verse_empty(VOTDS_VERSE *) ;
local int	verse_younger(VOTDS_VERSE *,time_t *) ;

local int	book_load(VOTDS_BOOK *,SHMALLOC *,char *,time_t,int,
			cchar *,cchar **) ;
local int	book_dump(VOTDS_BOOK *,SHMALLOC *) ;
local int	book_getwmark(VOTDS_BOOK *) ;
local int	book_getwmarklang(VOTDS_BOOK *,cchar **) ;
local int	book_read(VOTDS_BOOK *,char *,int,char *,int,int) ;

local int	titlecache_load(VOTDS_TC *,int,cchar *,char *,int *) ;
local int	titlecache_release(VOTDS_TC *) ;

local int	mkshmname(char *,int,cchar *,int,cchar *) ;


/* local variables */

#ifdef	COMMENT
static cint	loadrs[] = {
	SR_NOENT,
	SR_NOTSUP,
	SR_NOSYS,
	0
} ;
#endif /* COMMENT */


/* exported subroutines */


int votds_open(VOTDS *op,cchar *pr,cchar *lang,int of)
{
	int		rs ;

#if	CF_DEBUGS
	debugprintf("votds_open: ent\n") ;
	debugprintf("votds_open: bstrsize=%d\n",VOTDS_BSTRSIZE) ;
	debugprintf("votds_open: vstrsize=%d\n",VOTDS_VSTRSIZE) ;
	{
	    char	obuf[100+1] ;
	    snflagsopen(obuf,100,of) ;
	    debugprintf("votds_open: of=%s\n",obuf) ;
	}
#endif /* CF_DEBUGS */

	if (op == NULL) return SR_FAULT ;
	if (pr == NULL) return SR_FAULT ;

	if ((lang == NULL) || (lang[0] == '\0'))
 	    lang = VOTDS_DEFLANG ;

#if	CF_DEBUGS
	debugprintf("votds_open: pr=%s lang=%s\n",pr,lang) ;
#endif

	of &= (~ O_ACCMODE) ;
	of |= O_RDWR ;

	memset(op,0,sizeof(VOTDS)) ;
	op->pagesize = getpagesize() ;
	op->fd = -1 ;

	if ((rs = votds_shmhandbegin(op,pr)) >= 0) {
	    cchar	*cp ;
	    if ((rs = uc_mallocstrw(lang,-1,&cp)) >= 0) {
		const mode_t	om = VOTDS_PERMS ;
		op->lang = cp ;
	        if ((rs = votds_shmbegin(op,of,om)) >= 0) {
	   	    op->magic = VOTDS_MAGIC ;
	        } /* end if (votds_shmbegin) */
	        if (rs < 0) {
		    uc_free(op->lang) ;
		    op->lang = NULL ;
		}
	    } /* end if (memory-allocation) */
	    if (rs < 0)
		votds_shmhandend(op) ;
	} /* end if (votds-shmname) */

#if	CF_DEBUGS
	debugprintf("votds_open: ret rs=%d\n",rs) ;
#endif

	return rs ;
}
/* end subroutine (votds_open) */


int votds_close(op)
VOTDS		*op ;
{
	int	rs = SR_OK ;
	int	rs1 ;

#if	CF_DEBUGS
	debugprintf("votds_close: ent\n") ;
#endif
	if (op == NULL) return SR_FAULT ;

	if (op->magic != VOTDS_MAGIC) return SR_NOTOPEN ;

	rs1 = votds_titlefins(op) ;
	if (rs >= 0) rs = rs1 ;

	rs1 = votds_shmend(op) ;
	if (rs >= 0) rs = rs1 ;

	if (op->lang != NULL) {
	    rs1 = uc_free(op->lang) ;
	    if (rs >= 0) rs = rs1 ;
	    op->lang = NULL ;
	}

	rs1 = votds_shmhandend(op) ;
	if (rs >= 0) rs = rs1 ;

	op->magic = 0 ;
#if	CF_DEBUGS
	debugprintf("votds_close: ret rs=%d\n",rs) ;
#endif
	return rs ;
}
/* end subroutine (votds_close) */

#ifdef	COMMENT
int votds_langfetch(VOTDS *op,char *rbuf,int rlen,int li) noex {
	ptm		*mxp = op->mp ;
	int	rs ;

	if (op == NULL) return SR_FAULT ;
	if (rbuf == NULL) return SR_FAULT ;

	if (op->magic != VOTDS_MAGIC) return SR_NOTOPEN ;

	if ((li < 0) || (li >= VOTDS_NLANGS)) return SR_NOTFOUND ;

	rbuf[0] = '\0' ;
	if ((rs = mxp->lockbegin) >= 0) {
	    cchar	*lang = op->langs[li].lang ;
	    if (lang[0] != '\0') {
		rs = sncpy1(rbuf,rlen,lang) ;
	    } else {
		rs = SR_NOTFOUND ;
	    }
	    mxp->lockend() ;
	} /* end if (mutex) */

	return rs ;
}
/* end subroutine (votds_langfetch) */
#endif /* COMMENT */


/* loads all book-titles with one call */
int votds_titleloads(VOTDS *op,cchar *lang,cchar **tv) noex {
	ptm		*mxp = op->mp ;
	SIGBLOCK	s ;
	int		rs ;
#if	CF_DEBUGS
	debugprintf("votds_titleloads: ent lang=%s\n",lang) ;
#endif

	if (op == NULL) return SR_FAULT ;
	if (lang == NULL) return SR_FAULT ;
	if (tv == NULL) return SR_FAULT ;

	if (op->magic != VOTDS_MAGIC) return SR_NOTOPEN ;

	if (lang[0] == '\0') return SR_INVALID ;

	if ((rs = sigblocker_start(&s,NULL)) >= 0) {
	    if ((rs = mxp->lockbegin) >= 0) {
#if	CF_DEBUGS
	debugprintf("votds_titleloads: locked\n") ;
#endif
		if ((rs = votds_access(op)) >= 0) {
		    const time_t	dt = time(NULL) ;
	            if ((rs = votds_bookslotfind(op,lang)) >= 0) {
	    	        rs = votds_bookslotload(op,dt,rs,lang,tv) ;
	            } /* end if (votds_findslot) */
		} /* end if (votds_access) */
	        mxp->lockend() ;
	    } /* end if (mutex) */
	    sigblocker_finish(&s) ;
	} /* end if (sigblock) */

#if	CF_DEBUGS
	debugprintf("votds_titleloads: ret rs=%d\n",rs) ;
#endif
	return rs ;
}
/* end subroutine (votds_titleloads) */

/* do we have a specified title in a language? */
int votds_titlelang(VOTDS *op,cchar *lang) noex {
	ptm		*mxp = op->mp ;
	SIGBLOCK	s ;
	int		rs ;
	int		f = FALSE ;

#if	CF_DEBUGS
	debugprintf("votds_titlelang: ent\n",rs) ;
#endif
	if (op == NULL) return SR_FAULT ;
	if (lang == NULL) return SR_FAULT ;

#if	CF_DEBUGS
	debugprintf("votds_titlelang: lang=%s\n",lang) ;
#endif
	if (op->magic != VOTDS_MAGIC) return SR_NOTOPEN ;

	if (lang[0] == '\0') return SR_INVALID ;

	if ((rs = sigblocker_start(&s,NULL)) >= 0) {
	    if ((rs = mxp->lockbegin) >= 0) {
	            int		bi ;
	            cchar	*blang ;
#if	CF_DEBUGS
		    debugprintf("votds_titlelang: inside\n") ;
#endif
	            for (bi = 0 ; bi < VOTDS_NBOOKS ; bi += 1) {
		        blang = op->books[bi].lang ;
		        f = (strcasecmp(blang,lang) == 0) ;
		        if (f) break ;
	            } /* end for */
	        mxp->lockend() ;
	    } /* end if (mutex) */
	    sigblocker_finish(&s) ;
	} /* end if (sigblock) */

#if	CF_DEBUGS
	debugprintf("votds_titlelang: ret rs=%d f=%u\n",rs,f) ;
#endif

	return (rs >= 0) ? f : rs ;
}
/* end subroutine (votds_titlelang) */

int votds_titlefetch(VOTDS *op,char *rbuf,int rlen,cchar *lang,int ti) noex {
	ptm		*mxp = op->mp ;
	SIGBLOCK	s ;
	int		rs ;

	if (op == NULL) return SR_FAULT ;
	if (rbuf == NULL) return SR_FAULT ;
	if (lang == NULL) return SR_FAULT ;

	if (op->magic != VOTDS_MAGIC) return SR_NOTOPEN ;

	if (lang[0] == '\0') return SR_INVALID ;
	if ((ti < 0) || (ti >= VOTDS_NTITLES)) return SR_INVALID ;

	rbuf[0] = '\0' ;
	if ((rs = sigblocker_start(&s,NULL)) >= 0) {
	    if ((rs = mxp->lockbegin) >= 0) {
		if ((rs = votds_access(op)) >= 0) {
		    cint	ac = rs ;
	            int		bi ;
	            int		f = FALSE ;
	            cchar	*blang ;
	            for (bi = 0 ; bi < VOTDS_NBOOKS ; bi += 1) {
		        blang = op->books[bi].lang ;
		        f = (strcasecmp(blang,lang) == 0) ;
		        if (f) break ;
	            } /* end for */
	            if (f) {
			VOTDS_BOOK	*bep = (op->books+bi) ;
			char		*bstr = op->bstr ;
			rs = book_read(bep,bstr,ac,rbuf,rlen,ti) ;
		    } else
		        rs = SR_NOTFOUND ;
		} /* end if (votds_access) */
	        mxp->lockend() ;
	    } /* end if (mutex) */
	    sigblocker_finish(&s) ;
	} /* end if (sigblock) */

	return rs ;
}
/* end subroutine (votds_titlefetch) */

int votds_titlematch(VOTDS *op,cchar *lang,cchar *sp,int sl) noex {
	ptm		*mxp = op->mp ;
	SIGBLOCK	s ;
	int		rs ;
	int		bi = 0 ;

	if (op == NULL) return SR_FAULT ;
	if (lang == NULL) return SR_FAULT ;
	if (sp == NULL) return SR_FAULT ;

	if (op->magic != VOTDS_MAGIC) return SR_NOTOPEN ;

	if (lang[0] == '\0') return SR_INVALID ;
	if (sp[0] == '\0') return SR_INVALID ;

	if ((rs = sigblocker_start(&s,NULL)) >= 0) {
	    if ((rs = mxp->lockbegin) >= 0) {
		if ((rs = votds_access(op)) >= 0) {
		    cint	ac = rs ;
	            int		f = FALSE ;
	            cchar	*blang ;
	            for (bi = 0 ; bi < op->hdr.booklen ; bi += 1) {
		        blang = op->books[bi].lang ;
		        f = (strcasecmp(blang,lang) == 0) ;
		        if (f) break ;
	            } /* end for */
	            if (f) {
		        cint	clen = VOTDS_BOOKLEN ;
		        int		cl ;
		        char	cbuf[VOTDS_BOOKLEN+1] ;
		        cl = strwcpyopaque(cbuf,sp,MIN(clen,sl)) - cbuf ;
		        if ((rs = votds_mktitles(op,lang,bi)) >= 0) {
			    rs = votds_titlematcher(op,ac,rs,cbuf,cl) ;
			    bi = rs ;
		        }
	            } else
		        rs = SR_NOTFOUND ;
		} /* end if (votds_access) */
	        mxp->lockend() ;
	    } /* end if (mutex) */
	    sigblocker_finish(&s) ;
	} /* end if (sigblock) */

	return (rs >= 0) ? bi : rs ;
}
/* end subroutine (votds_titlematch) */


int votds_versefetch(op,citep,rbuf,rlen,lang,mjd)
VOTDS		*op ;
VOTDS_CITE	*citep ;
char		*rbuf ;
int		rlen ;
cchar	*lang ;
int		mjd ;
{
	ptm		*mxp = op->mp ;
	SIGBLOCK	s ;
	int		rs ;
	int		vl = 0 ;
#if	CF_DEBUGS
	debugprintf("votds_versefetch: ent mjd=%u\n",mjd) ;
#endif
	if (op == NULL) return SR_FAULT ;
	if (citep == NULL) return SR_FAULT ;
	if (rbuf == NULL) return SR_FAULT ;
	if (lang == NULL) return SR_FAULT ;
	if (lang[0] == '\0') return SR_INVALID ;
	if (mjd < 0) return SR_INVALID ;
	if ((rs = sigblocker_start(&s,NULL)) >= 0) {
	    if ((rs = mxp->lockbegin) >= 0) {
	        if ((rs = votds_booklanghave(op,lang)) >= 0) {
	            int	li = rs ;
		    if ((rs = votds_versehave(op,li,mjd)) >= 0) {
		        VOTDS_VERSE	*vep = (op->verses+rs) ;
			char		*vstr = op->vstr ;
		        rs = verse_read(vep,vstr,citep,rbuf,rlen) ;
			vl = rs ;
		    } /* end if (votds_versehave) */
	        } /* end if (votds_booklanghave) */
	        mxp->lockend() ;
	    } /* end if (mutex) */
	    sigblocker_finish(&s) ;
	} /* end if (sigblock) */
#if	CF_DEBUGS
	if (rs >= 0) {
	debugprintf("votds_versefetch: found mjd=%u b=%u\n",mjd,citep->b) ;
	}
	debugprintf("votds_versefetch: ret rs=%d vl=%u\n",rs,vl) ;
#endif
	return (rs >= 0) ? vl : rs ;
}
/* end subroutine (votds_versefetch) */


int votds_verseload(op,lang,citep,mjd,vp,vl)
VOTDS		*op ;
cchar	*lang ;
VOTDS_CITE	*citep ;
int		mjd ;
cchar	*vp ;
int		vl ;
{
	ptm		*mxp = op->mp ;
	SIGBLOCK	s ;
	int		rs ;
#if	CF_DEBUGS
	debugprintf("votds_verseload: ent mjd=%u\n",mjd) ;
	debugprintf("votds_verseload: lang=%s\n",lang) ;
	debugprintf("votds_verseload: cite=%u:%u:%u\n",
		citep->b,citep->c,citep->v) ;
#endif
	if (op == NULL) return SR_FAULT ;
	if (lang == NULL) return SR_FAULT ;
	if (citep == NULL) return SR_FAULT ;
	if (vp == NULL) return SR_FAULT ;
	if (vp[0] == '\0') return SR_INVALID ;
	if (mjd < 0) return SR_INVALID ;
	if ((rs = sigblocker_start(&s,NULL)) >= 0) {
	    if ((rs = mxp->lockbegin) >= 0) {
		if ((rs = votds_access(op)) >= 0) {
		    cint	ac = rs ;
	            if ((rs = votds_booklanghave(op,lang)) >= 0) {
		        SHMALLOC	*vap = op->vall ;
		        const time_t	dt = time(NULL) ;
			cint	nrs = SR_NOTFOUND ;
	                int		li = rs ;
		        int		vi = -1 ;
		        char		*vstr = op->vstr ;
			citep->l = li ;
		        if ((rs = votds_versehave(op,li,mjd)) >= 0) {
			    VOTDS_VERSE	*vep = (op->verses+rs) ;
			    vi = rs ;
			    rs = verse_dump(vep,vap,li) ;
		        } else if (rs == nrs) {
			    rs = SR_OK ;
			}
		        if (rs >= 0) {
#if	CF_DEBUGS
			    debugprintf("votds_verseload: vi=%d\n",vi) ;
#endif
			    if (vi < 0) {
			        if ((rs = votds_verseslotfind(op)) == nrs) {
				    if ((rs = votds_verseslotfinder(op)) >= 0) {
			    		VOTDS_VERSE	*vep = (op->verses+rs) ;
			            	vi = rs ;
			    		rs = verse_dump(vep,vap,li) ;
				    }
			        } else
			            vi = rs ;
#if	CF_DEBUGS
				debugprintf("votds_verseload: "
					"_verseslotfind() rs=%d\n",rs) ;
#endif
			    } /* end if (need slot) */
#if	CF_DEBUGS
				debugprintf("votds_verseload: "
				"rs=%d load vi=%d\n",rs,vi) ;
#endif
			    if (rs >= 0) {
			        VOTDS_VERSE	*vep = (op->verses+vi) ;
				VOTDS_CITE	*cp = citep ;
		                rs = verse_load(vep,dt,ac,vap,vstr,
					cp,mjd,vp,vl) ;
#if	CF_DEBUGS
	if (rs >= 0) {
	debugprintf("votds_verseload: verse_load() rs=%d mjd=%u b=%u\n",
		rs,vep->mjd, vep->book) ;
	}
#endif
			    }
		        } /* end if (ok) */
	            } /* end if (votds_booklanghave) */
		} /* end if (votds_access) */
	        mxp->lockend() ;
	    } /* end if (mutex) */
	    sigblocker_finish(&s) ;
	} /* end if (sigblock) */
#if	CF_DEBUGS
	debugprintf("votds_verseload: ret rs=%d\n",rs) ;
#endif
	return rs ;
}
/* end subroutine (votds_verseload) */

int votds_info(votds *op,votd_info *bip) noex {
	ptm		*mxp = op->mp ;
	SIGBLOCK	s ;
	int		rs ;

	if (op == NULL) return SR_FAULT ;
	if (bip == NULL) return SR_FAULT ;

	if (op->magic != VOTDS_MAGIC) return SR_NOTOPEN ;

	if ((rs = sigblocker_start(&s,NULL)) >= 0) {
	    if ((rs = mxp->lockbegin) >= 0) {
	        VOTDSHDR	*hdrp = &op->hdr ;
	        int		n, i ;
	        bip->wtime = (hdrp->wtime & UINT_MAX) ;
	        bip->atime = (hdrp->atime & UINT_MAX) ;
	        {
	            VOTDS_LANG	*vlp = (VOTDS_LANG *) op->langs ;
		    n = 0 ;
	            for (i = 0 ; i < op->hdr.lanlen ; i += 1) {
		        if (vlp[i].lang[0] != '\0') n += 1 ;
	            } /* end for */
	            bip->nlangs = n ;
	        }
	        {
	            VOTDS_BOOK	*vbp = (VOTDS_BOOK *) op->books ;
		    n = 0 ;
	            for (i = 0 ; i < op->hdr.booklen ; i += 1) {
		        if (vbp[i].b[0] != '\0') n += 1 ;
	            } /* end for */
	            bip->nbooks = n ;
	        }
	        {
	            VOTDS_VERSE	*vvp = (VOTDS_VERSE *) op->verses ;
		    n = 0 ;
	            for (i = 0 ; i < op->hdr.reclen ; i += 1) {
		        if (vvp[i].voff != '\0') n += 1 ;
	            } /* end for */
	            bip->nverses = n ;
	        }
	        mxp->lockend() ;
	    } /* end if (mutex) */
	    sigblocker_finish(&s) ;
	} /* end if (sigblock) */

	return rs ;
}
/* end subroutine (votds_info) */


/* private subroutines */


local int votds_shmbegin(VOTDS *op,int of,mode_t om)
{
	VOTDSHDR	*hdrp = &op->hdr ;
	const time_t	dt = time(NULL) ;
	cint	nrs = SR_NOENT ;
	int		rs = SR_OK ;
	int		rs1 ;
	int		fd = -1 ;
	int		f_needinit = FALSE ;
	cchar	*shmname = op->shmname ;
	char		*newname = NULL ;

#if	CF_DEBUGS
	debugprintf("votds_shmbegin: shm\n") ;
#endif

#ifdef	COMMENT
	of &= (~ O_ACCMODE) ;
	of |= O_RDWR ;
#endif /* COMMENT */

	memset(hdrp,0,sizeof(VOTDSHDR)) ;

	if (shmname[0] != '/') {
	    cint	ns = (sizeof(shmname)+2) ;
	    char	*newname ;
	    if ((rs = uc_malloc(ns,&newname)) >= 0) {
		char	*bp = newname ;
		*bp++ = '/' ;
		strwcpy(bp,shmname,-1) ;
		shmname = newname ;
	    } /* end if (m-a) */
	} /* end if (needed qualification) */
	if (rs >= 0) {
	    mode_t	mof = (of & (~ O_CREAT)) ;
#if	CF_DEBUGS
	debugprintf("votds_loadshm: shmname=%s\n",shmname) ;
#endif
	    if ((rs = uc_openshm(shmname,mof,om)) == nrs) {
	        if (of & O_CREAT) {
	            of |= O_EXCL ;
	            if ((rs = uc_openshm(shmname,of,(om & 0444))) >= 0) {
	                fd = rs ;
	                if ((rs = votds_shmprep(op,dt,fd,om,hdrp)) >= 0) {
	                    f_needinit = TRUE ;
		        }
	            } /* end if (uc_openshm) */
	        } /* end if (create mode) */
	    } else
	        fd = rs ;
	} /* end if (uc_openshm) */

#if	CF_DEBUGS
	debugprintf("votds_loadshm: 1 try rs=%d\n",rs) ;
#endif

	if ((rs == SR_ACCESS) || (rs == SR_EXIST)) {
	    cint	to = TO_WAITSHM ;
	    op->shmsize = 0 ;
	    rs = uc_openshmto(shmname,of,om,to) ;
	    fd = rs ;
	} /* end if (waiting for file to be ready) */

#if	CF_DEBUGS
	debugprintf("votds_loadshm: 2 try rs=%d\n",rs) ;
#endif

	if (rs >= 0) { /* opened */
	    if ((rs = uc_fsize(fd)) > 0) { /* should always be positive */
	        op->shmsize = rs ;
	        if ((rs = votds_mapbegin(op,dt,fd)) >= 0) {
		    if ((rs = votds_shmhdrin(op,hdrp)) >= 0) {
			op->fd = fd ;
		        if (f_needinit) {
	    		    if ((rs = votds_allocinit(op,hdrp)) >= 0) {
	    		        if ((rs = votds_mutexinit(op)) >= 0) {
	        	            rs = u_fchmod(fd,om) ;
			        }
			    }
		        } /* end if (needed it) */
		    } /* end if (votds_shmhdrin) */
		    if (rs < 0)
			votds_mapend(op) ;
		} /* end if (votds_mapbegin) */
	    } /* end if (uc_fsize) */
	    if (rs < 0) {
		u_close(fd) ;
		op->fd = -1 ;
	    }
	} /* end if (ok) */

	if (newname != NULL) {
	    rs1 = uc_free(newname) ;
	    if (rs >= 0) rs = rs1 ;
	}

#if	CF_DEBUGS
	debugprintf("votds_shmbegin: ret rs=%d\n",rs) ;
#endif

	return rs ;
}
/* end subroutine (votds_shmbegin) */


local int votds_shmend(VOTDS *op)
{
	int		rs = SR_OK ;
	int		rs1 ;
	if (op->mapdata != NULL) {
	    rs1 = votds_mapend(op) ;
	    if (rs >= 0) rs = rs1 ;
	}
	if (op->fd >= 0) {
	    rs1 = u_close(op->fd) ;
	    if (rs >= 0) rs = rs1 ;
	    op->fd = -1 ;
	}
	return rs ;
}
/* end subroutine (votds_shmend) */


local int votds_mapbegin(op,dt,fd)
VOTDS		*op ;
time_t		dt ;
int		fd ;
{
	size_t		ms ;
	int		rs ;
	int		mp ;
	int		mf ;
	void		*md ;

	if (fd < 0) return SR_INVALID ;

	if (dt == 0) dt = time(NULL) ;

	ms = op->shmsize ;
	mp = (PROT_READ | PROT_WRITE) ;
	mf = MAP_SHARED ;
	if ((rs = u_mmap(NULL,ms,mp,mf,fd,0L,&md)) >= 0) {
	    op->mapdata = md ;
	    op->mapsize = ms ;
	    op->ti_map = dt ;
	} /* end if (map) */

	return rs ;
}
/* end subroutine (votds_mapbegin) */


local int votds_mapend(op)
VOTDS		*op ;
{
	int		rs = SR_OK ;
	int		rs1 ;

	if (op->mapdata != NULL) {
	    caddr_t	md = op->mapdata ;
	    size_t	ms = op->mapsize ;
	    rs1 = u_munmap(md,ms) ;
	    if (rs >= 0) rs = rs1 ;
	    op->mapdata = NULL ;
	    op->mapsize = 0 ;
	    op->mp = NULL ;
	    op->ti_map = 0 ;
	} /* end if (non-null) */

	return rs ;
}
/* end subroutine (votds_mapend) */


local int votds_shmprep(op,dt,fd,om,hdrp)
VOTDSHDR	*hdrp ;
VOTDS		*op ;
time_t		dt ;
int		fd ;
mode_t		om ;
{
	int		rs ;
	int		foff = 0 ;

	op->shmsize = 0 ;
	if (dt == 0) dt = time(NULL) ;

	hdrp->vetu[0] = VOTDSHDR_VERSION ;
	hdrp->vetu[1] = ENDIAN ;
	hdrp->vetu[2] = 0 ;
	hdrp->vetu[3] = 0 ;
	hdrp->wtime = (utime_t) dt ;

	rs = votds_shmpreper(op,dt,fd,om,hdrp) ;
	foff = rs ;

	return (rs >= 0) ? foff : rs ;
}
/* end subroutine (votds_shmprep) */


local int votds_shmpreper(op,dt,fd,om,hdrp)
VOTDS		*op ;
time_t		dt ;
int		fd ;
mode_t		om ;
VOTDSHDR	*hdrp ;
{
	cint	hlen = HDRBUFLEN ;
	int		rs ;
	int		foff = 0 ;
	char		hbuf[HDRBUFLEN + 1] ;

	op->shmsize = 0 ;
	if (dt == 0) dt = time(NULL) ;

	if ((rs = votdshdr(hdrp,0,hbuf,hlen)) >= 0) {
	    int	hl = rs ;
	    if ((rs = votds_shmwriter(op,dt,fd,hdrp,hbuf,hl)) >= 0) {
	        hdrp->shmsize = foff ;
	        if ((rs = u_rewind(fd)) >= 0) {
	            if ((rs = votdshdr(hdrp,0,hbuf,hlen)) >= 0) {
	                if ((rs = u_write(fd,hbuf,rs)) >= 0) {
	    		    op->shmsize = foff ;
	    		    rs = u_fchmod(fd,om) ;
		        }
		    } /* end if (votdshdr) */
		} /* end if (u_rewind) */
	    } /* end if (votds_shmwriter) */
	} /* end if (votdshdr) */

	return (rs >= 0) ? foff : rs ;
}
/* end subroutine (votds_shmpreper) */


local int votds_shmwriter(op,dt,fd,hdrp,hbuf,hlen)
VOTDS		*op ;
time_t		dt ;
int		fd ;
VOTDSHDR	*hdrp ;
cchar	hbuf[] ;
int		hlen ;
{
	FILER		sfile, *sfp = &sfile ;
	cint	bsize = 2048 ;
	int		rs ;
	int		rs1 ;
	int		size ;
	int		foff = 0 ;

	op->shmsize = 0 ;
	if (dt == 0) dt = time(NULL) ;

	if ((rs = filer_start(sfp,fd,0,bsize,0)) >= 0) {
	    cint	asize = SHMALLOC_ALIGNSIZE ;

	    if (rs >= 0) {
	        rs = filer_write(sfp,hbuf,hlen) ;
	        foff += rs ;
	    }

	    if (rs >= 0) {
	        if ((rs = filer_writealign(sfp,asize)) >= 0) {
	            foff += rs ;
		    size = VOTDS_MUSIZE ;
		    hdrp->muoff = foff ;
		    hdrp->musize = size ;
		    rs = filer_writezero(sfp,size) ;
	            foff += rs ;
	        }
	    }

	    if (rs >= 0) {
	        if ((rs = filer_writealign(sfp,asize)) >= 0) {
	            foff += rs ;
		    size = VOTDS_LANGSIZE ;
		    hdrp->lanoff = foff ;
		    hdrp->lanlen = VOTDS_NLANGS ;
		    rs = filer_writezero(sfp,size) ;
	            foff += rs ;
	        }
	    }

	    if (rs >= 0) {
	        if ((rs = filer_writealign(sfp,asize)) >= 0) {
	            foff += rs ;
		    size = VOTDS_BOOKSIZE ;
		    hdrp->bookoff = foff ;
		    hdrp->booklen = VOTDS_NBOOKS ;
		    rs = filer_writezero(sfp,size) ;
	            foff += rs ;
	        }
	    }

	    if (rs >= 0) {
	        if ((rs = filer_writealign(sfp,asize)) >= 0) {
	            foff += rs ;
		    size = VOTDS_VERSESIZE ;
		    hdrp->recoff = foff ;
		    hdrp->reclen = VOTDS_NVERSES ;
		    rs = filer_writezero(sfp,size) ;
	            foff += rs ;
	        }
	    }

	    if (rs >= 0) {
	        if ((rs = filer_writealign(sfp,asize)) >= 0) {
	            foff += rs ;
		    size = sizeof(SHMALLOC) ;
		    hdrp->balloff = foff ;
		    hdrp->ballsize = size ;
		    rs = filer_writezero(sfp,size) ;
	            foff += rs ;
	        }
	    }

	    if (rs >= 0) {
	        if ((rs = filer_writealign(sfp,asize)) >= 0) {
	            foff += rs ;
		    size = sizeof(SHMALLOC) ;
		    hdrp->valloff = foff ;
		    hdrp->vallsize = size ;
		    rs = filer_writezero(sfp,size) ;
	            foff += rs ;
	        }
	    }

	    if (rs >= 0) {
	        if ((rs = filer_writealign(sfp,asize)) >= 0) {
	            foff += rs ;
		    size = VOTDS_BSTRSIZE ;
		    hdrp->bstroff = foff ;
		    hdrp->bstrlen = size ;
		    rs = filer_writezero(sfp,size) ;
	            foff += rs ;
	        }
	    }

	    if (rs >= 0) {
	        if ((rs = filer_writealign(sfp,asize)) >= 0) {
	            foff += rs ;
		    size = VOTDS_VSTRSIZE ;
		    hdrp->vstroff = foff ;
		    hdrp->vstrlen = size ;
		    rs = filer_writezero(sfp,size) ;
	            foff += rs ;
	        }
	    }

	    if (rs >= 0) {
		size = iceil(foff,op->pagesize) - foff ;
		rs = filer_writezero(sfp,size) ;
	        foff += rs ;
	    }

	    rs1 = filer_finish(sfp) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (filer) */

	hdrp->shmsize = foff ;
	return (rs >= 0) ? foff : rs ;
}
/* end subroutine (votds_shmwriter) */


local int votds_shmhdrin(VOTDS *op,VOTDSHDR *hdrp)
{
	int		rs ;

#if	CF_DEBUGS
	debugprintf("votds_shmhdrin: ent\n") ;
#endif

	if ((rs = votdshdr(hdrp,1,op->mapdata,op->mapsize)) >= 0) {
	    if ((rs = votds_verify(op)) >= 0) {
	        op->mp = (PTM *) (op->mapdata + hdrp->muoff) ;
	        op->langs = (VOTDS_LANG *) (op->mapdata + hdrp->lanoff) ;
	        op->books = (VOTDS_BOOK *) (op->mapdata + hdrp->bookoff) ;
	        op->verses = (VOTDS_VERSE *) (op->mapdata + hdrp->recoff) ;
	        op->ball = (SHMALLOC *) (op->mapdata + hdrp->balloff) ;
	        op->vall = (SHMALLOC *) (op->mapdata + hdrp->valloff) ;
	        op->bstr = (char *) (op->mapdata + hdrp->bstroff) ;
	        op->vstr = (char *) (op->mapdata + hdrp->vstroff) ;
		op->nents = (int) hdrp->reclen ;
	    }
	} /* end if (votdshdr) */

#if	CF_DEBUGS
	debugprintf("votds_shmhdrin: ret rs=%d\n",rs) ;
#endif

	return rs ;
}
/* end subroutine (votds_shmhdrin) */


local int votds_allocinit(VOTDS *op,VOTDSHDR *hdrp)
{
	int		rs ;

	if ((rs = shmalloc_init(op->ball,op->bstr,hdrp->bstrlen)) >= 0) {
	    rs = shmalloc_init(op->vall,op->vstr,hdrp->vstrlen) ;
	    if (rs < 0)
	        shmalloc_fini(op->ball) ;
	} /* end if (SHMALLOC initialization) */

	return rs ;
}
/* end subroutine (votds_allocinit) */

local int votds_mutexinit(VOTDS *op) noex {
	ptm		*mxp = op->mp ;
	PTMA		ma ;
	int		rs ;

#if	CF_DEBUGS
	debugprintf("votds_mutexinit: ent\n") ;
#endif

	if ((rs = ptma_create(&ma)) >= 0) {
	    cint	cmd = PTHREAD_PROCESS_SHARED ;
	    if ((rs = ptma_setpshared(&ma,cmd)) >= 0) {
	        PTM	*mp = (PTM *) op->mp ;

#ifdef	OPTIONAL
	        memset(mp,0,sizeof(PTM)) ;
#endif

	        rs = mxp->create(&ma) ; /* we leave the MUTEX initialized */

	    } /* end if (ptma_setpshared) */
	    ptma_destroy(&ma) ;
	} /* end if (mutex-lock attribute) */

	return rs ;
}
/* end subroutine (votds_mutexinit) */

local int votds_verify(VOTDS *op) noex {
	VOTDSHDR	*hdrp = &op->hdr ;
	int		rs = SR_OK ;
	int		size ;
	int		f = TRUE ;

	f = f && (hdrp->muoff < op->shmsize) ;
	f = f && (hdrp->bookoff < op->shmsize) ;
	f = f && (hdrp->recoff < op->shmsize) ;
	f = f && (hdrp->balloff < op->shmsize) ;
	f = f && (hdrp->valloff < op->shmsize) ;
	f = f && (hdrp->bstroff < op->shmsize) ;
	f = f && (hdrp->vstroff < op->shmsize) ;

	f = f && ((hdrp->muoff + hdrp->musize) < op->shmsize) ;
	size = sizeof(VOTDS_BOOK) ;
	f = f && ((hdrp->bookoff + (hdrp->booklen*size)) < op->shmsize) ;
	size = sizeof(VOTDS_VERSE) ;
	f = f && ((hdrp->recoff + (hdrp->reclen*size)) < op->shmsize) ;
	f = f && ((hdrp->balloff + hdrp->ballsize) < op->shmsize) ;
	f = f && ((hdrp->valloff + hdrp->vallsize) < op->shmsize) ;
	f = f && ((hdrp->bstroff + hdrp->bstrlen) < op->shmsize) ;
	f = f && ((hdrp->vstroff + hdrp->vstrlen) < op->shmsize) ;

	if (! f)
	    rs = SR_BADFMT ;

#if	CF_DEBUGS
	debugprintf("votds_verify: ret rs=%d\n",rs) ;
#endif

	return rs ;
}
/* end subroutine (votds_verify) */


local int votds_shmhandbegin(VOTDS *op,cchar *pr)
{
	int		rs = SR_OK ;
	int		rl ;
	cchar	*rn ;
	if ((rl = sfrootname(pr,-1,&rn)) > 0) {
	    cint	slen = MAXNAMELEN ;
	    cchar	*suf = VOTDS_SHMPOSTFIX ;
	    char	sbuf[MAXNAMELEN+1] ;
	    if ((rs = mkshmname(sbuf,slen,rn,rl,suf)) >= 0) {
	        cchar	*np ;
	        if ((rs = uc_mallocstrw(sbuf,rs,&np)) >= 0) {
	            op->shmname = np ;
	        }
	    } /* end if (mkshmname) */
	} else
	    rs = SR_INVALID ;
	return rs ;
}
/* end subroutine (votds_shmhandbegin) */


local int votds_shmhandend(VOTDS *op)
{
	int		rs = SR_OK ;
	int		rs1 ;
	if (op->shmname != NULL) {
	    rs1 = uc_free(op->shmname) ;
	    if (rs >= 0) rs = rs1 ;
	    op->shmname = NULL ;
	}
	return rs ;
}
/* end subroutine (votds_shmhandend) */


local int votds_bookslotload(op,dt,si,lang,tv)
VOTDS		*op ;
time_t		dt ;
int		si ;
cchar	*lang ;
cchar	**tv ;
{
	int		rs ;

#if	CF_DEBUGS
	{
	    int	i ;
	    debugprintf("votds_bookslotload: ent\n") ;
	    debugprintf("votds_bookslotload: titles¬\n") ;
	    for (i = 0 ; (i < VOTDS_NTITLES) && (tv[i] != NULL) ; i += 1) {
	        debugprintf("votds_bookslotload: title[%02u]=>%s<\n",i,tv[i]) ;
	    }
	}
#endif /* CF_DEBUGS */
	if ((rs = votds_getwcount(op)) >= 0) {
	    VOTDS_BOOK	*blp = (op->books + si) ;
	    SHMALLOC	*bap = op->ball ;
	    cint	wc = rs ;
#if	CF_DEBUGS
	    debugprintf("votds_bookslotload: votds_getwcount() wc=%u\n",wc) ;
#endif
	    rs = book_load(blp,bap,op->bstr,dt,wc,lang,tv) ;
	}

#if	CF_DEBUGS
	debugprintf("votds_bookslotload: ret rs=%d\n",rs) ;
#endif
	return rs ;
}
/* end subroutine (votds_bookslotload) */


local int votds_bookslotfind(VOTDS *op,cchar *lang)
{
	VOTDS_BOOK	*blp = op->books ;
	int		rs = SR_OK ;
	int		i ;
	int		i_empty = -1 ;
	int		f_same = FALSE ;

#if	CF_DEBUGS
	debugprintf("votds_bookslotfind: ent lang=%s\n",lang) ;
#endif
	for (i = 0 ; i < op->hdr.booklen ; i += 1) {
	    cchar	*elang = blp[i].lang ;
	    if (elang[0] != '\0') {
		f_same = (strcmp(elang,lang) == 0) ;
	    } else
		i_empty = i ;
	    if (f_same) break ;
	} /* end for */

#if	CF_DEBUGS
	debugprintf("votds_bookslotfind: mid f_same=%u\n",f_same) ;
#endif
	if (! f_same) {
	    if (i_empty < 0) {
	        time_t	oldest = INT_MAX ;
	        int	oi = 0 ;
	        for (i = 0 ; i < op->hdr.booklen ; i += 1) {
	            if (blp[i].atime < oldest) {
		        oldest = op->books[i].atime ;
		        oi = i ;
		    }
	        } /* end for */
	        rs = votds_bookslotdump(op,oi) ;
		i = oi ;
	    } else
		i = i_empty ;
	} else
	    rs = votds_bookslotdump(op,i) ;

#if	CF_DEBUGS
	debugprintf("votds_bookslotfind: ret rs=%d i=%u\n",rs,i) ;
#endif
	return (rs >= 0) ? i : rs ;
}
/* end subroutine (votds_bookslotfind) */


local int votds_bookslotdump(VOTDS *op,int ei)
{
	int		rs ;

#if	CF_DEBUGS
	debugprintf("votds_bookslotdump: ent ei=%u\n",ei) ;
#endif
	if ((rs = votds_verselangdump(op,ei)) >= 0) {
	    VOTDS_BOOK	*blp = (op->books + ei) ;
	    SHMALLOC	*bap = op->ball ;
	    rs = book_dump(blp,bap) ;
	} /* end if (votds_verselangdump) */
#if	CF_DEBUGS
	debugprintf("votds_bookslotdump: ret rs=%d\n",rs) ;
#endif

	return rs ;
}
/* end subroutine (votds_bookslotdump) */


local int votds_verselangdump(VOTDS *op,int li)
{
	VOTDS_VERSE	*vep = op->verses ;
	SHMALLOC	*vap = op->vall ;
	int		rs = SR_OK ;
	int		i ;
	for (i = 0 ; i < op->hdr.reclen ; i += 1) {
	    rs = verse_dump((vep+i),vap,li) ;
	    if (rs < 0) break ;
	} /* end for */
	return rs ;
}
/* end subroutine (votds_verselangdump) */


local int votds_booklanghave(VOTDS *op,cchar *lang)
{
	VOTDS_BOOK	*bap = op->books ;
	int		rs = SR_NOTFOUND ;
	int		i ;
	for (i = 0 ; i < op->hdr.booklen ; i += 1) {
	    if (strcmp(bap[i].lang,lang) == 0) {
		rs = SR_OK ;
		break ;
	    }
	} /* end for */
#if	CF_DEBUGS
	debugprintf("votds_booklanghave: ret rs=%d i=%u\n",rs,i) ;
#endif
	return (rs >= 0) ? i : rs ;
}
/* end subroutine (votds_booklanghave) */


local int votds_versehave(VOTDS *op,int li,int mjd)
{
	VOTDS_VERSE	*vep = op->verses ;
	int		rs = SR_NOTFOUND ;
	int		i ;
#if	CF_DEBUGS
	debugprintf("votds_versehave: ent li=%u mjd=%u\n",li,mjd) ;
#endif
	for (i = 0 ; i < op->hdr.reclen ; i += 1) {
	    rs = verse_match((vep+i),li,mjd) ;
#if	CF_DEBUGS
	    debugprintf("votds_versehave: i=%u verse_match() rs=%d\n",i,rs) ;
#endif
	    if (rs != SR_NOTFOUND) break ;
	} /* end for */
#if	CF_DEBUGS
	if (rs >= 0) {
	debugprintf("votds_versehave: found mjd=%u b=%u\n",
		(vep+i)->mjd, (vep+i)->book) ;
	}
	debugprintf("votds_versehave: ret rs=%d ii=%u\n",rs,li) ;
#endif
	return (rs >= 0) ? i : rs ;
}
/* end subroutine (votds_versehave) */


local int votds_verseslotfind(VOTDS *op)
{
	VOTDS_VERSE	*vep = op->verses ;
	int		rs = SR_NOTFOUND ;
	int		i ;
	for (i = 0 ; i < op->hdr.reclen ; i += 1) {
	    rs = verse_empty((vep+i)) ;
	    if (rs != SR_NOTFOUND) break ;
	} /* end for */
	return (rs >= 0) ? i : rs ;
}
/* end subroutine (votds_verseslotfind) */


local int votds_verseslotfinder(VOTDS *op)
{
	VOTDS_VERSE	*vep = op->verses ;
	time_t		mt = INT_MAX ;
	int		rs = SR_OK ;
	int		mi = 0 ;
	int		i ;
	for (i = 0 ; i < op->hdr.reclen ; i += 1) {
	    if ((rs = verse_younger((vep+i),&mt)) > 0) {
		mi = i ;
	    } /* end if (verse_younger) */
	    if (rs < 0) break ;
	} /* end for */
#if	CF_DEBUGS
	debugprintf("votds_verseslotfinder: ret rs=%d mi=%u\n",rs,mi) ;
#endif
	return (rs >= 0) ? mi : rs ;
}
/* end subroutine (votds_verseslotfinder) */


local int votds_getwcount(VOTDS *op)
{
	int		rs ;
	char		*mdp = (char *) op->mapdata ;
	int		*htab ;
	int		*wcp ;
	htab = (int *) (mdp+VOTDSHDR_IDLEN) ;
	wcp = (int *) (htab + votdshdrh_wcount) ;
	rs = *wcp ;
	return rs ;
}
/* end subroutine (votds_getwcount) */


local int votds_access(VOTDS *op)
{
	uint		*htab ;
	int		rs ;
	char		*mdp = (char *) op->mapdata ;
#if	CF_DEBUGS
	debugprintf("votds_access: ent\n") ;
#endif
	htab = (uint *) (mdp+VOTDSHDR_IDLEN) ;
	{
	    int	*acp = (int *) (htab + votdshdrh_acount) ;
	    *acp += 1 ;
	    rs = *acp ;
	}
#if	CF_DEBUGS
	debugprintf("votds_access: ret rs=%d\n",rs) ;
#endif
	return rs ;
}
/* end subroutine (votds_access) */


#if	CF_UPDATE
local int votds_update(VOTDS *op)
{
	uint		*htab ;
	int		rs ;
	char		*mdp = (char *) op->mapdata ;
#if	CF_DEBUGS
	debugprintf("votds_update: ent\n") ;
#endif
	htab = (uint *) (mdp + VOTDSHDR_IDLEN) ;
	{
	    int	*wcp = (int *) (htab + votdshdrh_wcount) ;
	    rs = *wcp ;
	    *wcp += 1 ;
	}
#if	CF_DEBUGS
	debugprintf("votds_update: ret rs=%d\n",rs) ;
#endif
	return rs ;
}
/* end subroutine (votds_update) */
#endif /* CF_UPDATE */


#if	CF_GETACOUNT
local int votds_getacount(VOTDS *op)
{
	uint		*htab ;
	int		rs ;
	int		*acp ;
	char		*mdp = (char *) op->mapdata ;
	htab = (uint *) (mdp+VOTDSHDR_IDLEN) ;
	acp = (int *) (htab + votdshdrh_acount) ;
	rs = *acp ;
	return rs ;
}
/* end subroutine (votds_getacount) */
#endif /* CF_GETACOUNT */


local int votds_mktitles(VOTDS *op,cchar *lang,int bi)
{
	cint	nrs = SR_NOTFOUND ;
	int		rs ;
	int		ci = 0 ;

	if ((rs = votds_titlevalid(op,bi)) == nrs) {
	    if ((rs = votds_titletouse(op)) >= 0) {
	        VOTDS_TC	*tcp = (op->tcs+rs) ;
		VOTDS_BOOK	*bep = (op->books+bi) ;
		ci = rs ;
		if ((rs = book_getwmark(bep)) >= 0) {
		    cint	wm = rs ;
		    char	*bstr = op->bstr ;
		    rs = titlecache_load(tcp,wm,lang,bstr,bep->b) ;
		} /* end if (book_getwmark) */
	    } /* end if (votds_titletouse) */
	} else
	    ci = rs ;
	return (rs >= 0) ? ci : rs ;
}
/* end subroutine (votds_mktitles) */


local int votds_titlematcher(VOTDS *op,int ac,int ci,cchar *cbuf,int cl)
{
	VOTDS_TC	*tcp = (op->tcs+ci) ;
	int		rs = SR_NOTFOUND ;
	if (tcp->titles != NULL) {
	    tcp->amark = ac ;
	    if ((rs = matostr(tcp->titles,2,cbuf,cl)) < 0) rs = SR_NOTFOUND ;
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (votds_titlematcher) */


local int votds_titletouse(VOTDS *op)
{
	VOTDS_TC	*tcp = op->tcs ;
	int		rs = SR_OK ;
	int		ci = -1 ;
	int		i ;
	for (i = 0 ; i < VOTDS_NTITLES ; i += 1) {
	    if (tcp[i].lang[0] == '\0') {
		ci = i ;
		break ;
	    }
	} /* end for */
	if (ci < 0) {
	    int		minamark = INT_MAX ;
	    for (i = 0 ; i < VOTDS_NTITLES ; i += 1) {
	        if ((tcp[i].lang[0] != '\0') && (tcp[i].amark < minamark)) {
		    ci = i ;
		    minamark = tcp[i].amark ;
	        }
	    } /* end for */
	} /* end if (find oldest) */
	return (rs >= 0) ? ci : rs ;
}
/* end subroutine (votds_titletouse) */


local int votds_titlevalid(VOTDS *op,int bi)
{
	VOTDS_BOOK	*bep = (op->books+bi) ;
	int		rs ;
	int		i = 0 ;
	cchar	*blang ;
	if ((rs = book_getwmarklang(bep,&blang)) >= 0) {
	    VOTDS_TC	*tcp = op->tcs ;
	    cint	wm = rs ;
	    cint	n = VOTDS_NBOOKS ;
	    int		f = FALSE ;
	    for (i = 0 ; i < n ; i += 1) {
		if ((tcp[i].lang[0] != '\0') && (tcp[i].wmark == wm)) {
		    f = (strcmp(tcp[i].lang,blang) == 0) ;
		    if (f) break ;
		}
	    } /* end for */
	    if (!f) rs = SR_NOTFOUND ;
	} /* end if (votds_getwcount) */
	return (rs >= 0) ? i : rs ;
}
/* end subroutine (votds_titlevalid) */


local int votds_titlefins(VOTDS *op)
{
	cint	n = VOTDS_NBOOKS ;
	int		rs = SR_OK ;
	int		rs1 ;
	int		i ;
	for (i = 0 ; i < n ; i += 1) {
	    rs1 = titlecache_release((op->tcs+i)) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end for */
	return rs ;
}
/* end subroutine (votds_titlefins) */


local int verse_dump(VOTDS_VERSE *vep,SHMALLOC *vap,int li)
{
	int		rs = SR_OK ;
	li &= UCHAR_MAX ;
	if ((vep->lang == li) && (vep->vlen > 0)) {
	    vep->mjd = 0 ;
	    if ((rs = shmalloc_free(vap,vep->voff)) >= 0) {
	        vep->voff = 0 ;
	        vep->vlen = 0 ;
	        vep->ctime = 0 ;
	        vep->atime = 0 ;
	        rs = 1 ;
	    }
	}
	return rs ;
}
/* end subroutine (verse_dump) */


local int verse_match(VOTDS_VERSE *vep,int li,int mjd)
{
	int	rs = SR_NOTFOUND ;
#if	CF_DEBUGS
	debugprintf("verse_match: ent li=%u mjd=%u\n",li,mjd) ;
#endif
#if	CF_DEBUGS
	debugprintf("verse_match: slot li=%u mjd=%u\n",vep->lang,vep->mjd) ;
#endif
	if ((vep->lang == li) && (vep->mjd == mjd)) {
	    rs = SR_OK ;
	}
#if	CF_DEBUGS
	debugprintf("verse_match: ret rs=%d\n",rs) ;
#endif
	return rs ;
}
/* end subroutine (verse_match) */


local int verse_read(vep,vstr,citep,rbuf,rlen)
VOTDS_VERSE	*vep ;
char		*vstr ;
VOTDS_CITE	*citep ;
char		*rbuf ;
int		rlen ;
{
	int		rs ;
	citep->b = vep->book ;
	citep->c = vep->chapter ;
	citep->v = vep->verse ;
	citep->l = vep->lang ;
	rs = sncpy1(rbuf,rlen,(vstr+vep->voff)) ;
	return rs ;
}
/* end subroutine (verse_read) */


local int verse_load(vep,dt,wm,vap,vstr,citep,mjd,vp,vl)
SHMALLOC	*vap ;
time_t		dt ;
int		wm ;
VOTDS_VERSE	*vep ;
char		*vstr ;
VOTDS_CITE	*citep ;
int		mjd ;
cchar	*vp ;
int		vl ;
{
	int		rs ;
	int		voff = 0 ;
	if (vl < 0) vl = strlen(vp) ;
	if ((rs = shmalloc_alloc(vap,(vl+1))) >= 0) {
	    char	*bp = (vstr+rs) ;
	    voff = rs ;
 	    vep->ctime = dt ;
	    vep->atime = dt ;
	    vep->voff = voff ;
	    vep->vlen = vl ;
	    vep->wmark = wm ;
	    vep->book  = citep->b ;
	    vep->chapter = citep->c ;
	    vep->verse = citep->v ;
	    vep->lang = citep->l ;
	    vep->mjd = mjd ;
	    strwcpy(bp,vp,vl) ;
	} /* end if (m-a) */
	return (rs >= 0) ? voff : rs ;
}
/* end subroutine (verse_load) */


local int verse_empty(VOTDS_VERSE *vep)
{
	int		rs = SR_OK ;
	if (vep->mjd > 0) rs = SR_NOTFOUND ;
	return rs ;
}
/* end subroutine (verse_empty) */


local int verse_younger(VOTDS_VERSE *vep,time_t *tp)
{
	int		rs = 0 ;
	if ((vep->mjd == 0) || (vep->atime < *tp)) {
	    rs = 1 ;
	    *tp = vep->atime ;
	}
	return rs ;
}
/* end subroutine (verse_younger) */


local int book_load(blp,bap,bsp,dt,wm,lang,tv)
VOTDS_BOOK	*blp ;
SHMALLOC	*bap ;
char		*bsp ;
time_t		dt ;
int		wm ;
cchar	*lang ;
cchar	**tv ;
{
	int		rs = SR_OK ;
	int		i ;
	char		*bp ;

#if	CF_DEBUGS
	debugprintf("votds/book_load: ent\n") ;
#endif
	strwcpy(blp->lang,lang,VOTDS_LANGLEN) ;
	blp->ctime = dt ;
	blp->atime = dt ;
	blp->wmark = wm ;
	for (i = 0 ; (i < VOTDS_NTITLES) && (tv[i] != NULL) ; i += 1) {
	    int	bl = strlen(tv[i]) ;
#if	CF_DEBUGS
	    debugprintf("votds/book_load: title=>%s<\n",tv[i]) ;
#endif
	    if ((rs = shmalloc_alloc(bap,(bl+1))) >= 0) {
#if	CF_DEBUGS
	    debugprintf("votds/book_load: shmalloc_alloc() rs=%d\n",rs) ;
#endif
		blp->b[i] = rs ;
		bp = (bsp+rs) ;
		strwcpy(bp,tv[i],bl) ;
	    } /* end if (shmalloc_alloc) */
#if	CF_DEBUGS
	    debugprintf("votds/book_load: for-bot rs=%d\n",rs) ;
#endif
	    if (rs < 0) break ;
	} /* end for */

#if	CF_DEBUGS
	debugprintf("votds/book_load: ret rs=%d\n",rs) ;
#endif
	return rs ;
}
/* end subroutine (book_load) */


local int book_dump(blp,bap)
VOTDS_BOOK	*blp ;
SHMALLOC	*bap ;
{
	int		rs = SR_OK ;
	int		i ;

	blp->ctime = 0 ;
	blp->atime = 0 ;
	blp->lang[0] = '\0' ;
	for (i = 0 ; i < VOTDS_NTITLES ; i += 1) {
	    int	toff = blp->b[i] ;
	    if (toff > 0) {
	        rs = shmalloc_free(bap,toff) ;
	    }
	    if (rs < 0) break ;
	} /* end for */

	return rs ;
}
/* end subroutine (book_dump) */


local int book_getwmark(VOTDS_BOOK *bep)
{
	int		rs = SR_NOTFOUND ;
	if (bep->lang[0] != '\0') {
	    rs = bep->wmark ;
	}
	return rs ;
}
/* end subroutine (book_getwmark) */


local int book_getwmarklang(VOTDS_BOOK *bep,cchar **lpp)
{
	int		rs = SR_NOTFOUND ;
	if (bep->lang[0] != '\0') {
	    if (lpp != NULL) *lpp = bep->lang ;
	    rs = bep->wmark ;
	}
	return rs ;
}
/* end subroutine (book_getwmarklang) */


local int book_read(bep,bstr,ac,rbuf,rlen,ti)
VOTDS_BOOK	*bep ;
char		*bstr ;
int		ac ;
char		rbuf[] ;
int		rlen ;
int		ti ;
{
	cint	boff = bep->b[ti] ;
	int		rs ;
	bep->amark = ac ;
	rs = sncpy1(rbuf,rlen,(bstr+boff)) ;
	return rs ;
}
/* end subroutine (book_read) */


local int titlecache_load(tcp,wm,lang,bstr,boffs) 
VOTDS_TC	*tcp ;
int		wm ;
cchar	*lang ;
char		*bstr ;
int		*boffs ;
{
	cint	n = VOTDS_NTITLES ;
	int		rs = SR_OK ;
	int		size = sizeof(cchar *) ;
	int		i ;
	cchar	*np ;
	char		*bp ;
	memset(tcp,0,sizeof(VOTDS_TC)) ;
	tcp->wmark = wm ;
	tcp->amark = 0 ;
	strwcpy(tcp->lang,lang,VOTDS_LANGLEN) ;
	for (i = 0 ; i < n ; i += 1) {
	    np = (bstr + boffs[i]) ;
	    size += sizeof(cchar *) ;
	    size += (strlen(np)+1) ;
	} /* end for */
	if ((rs = uc_malloc(size,&bp)) >= 0) {
	    tcp->a = (cchar *) bp ;
	    tcp->titles = (cchar **) bp ;
	    bp += ((n+1)*sizeof(cchar *)) ;
	    for (i = 0 ; i < n ; i += 1) {
		np = (bstr + boffs[i]) ;
		tcp->titles[i] = np ;
	    } /* end for */
	    tcp->titles[i] = NULL ;
	} /* end if (m-a) */
	return rs ;
}
/* end subroutine (titlecache_load) */


local int titlecache_release(VOTDS_TC *tcp)
{
	int		rs = SR_OK ;
	int		rs1 ;
	if (tcp->a != NULL) {
	    rs1 = uc_free(tcp->a) ;
	    if (rs >= 0) rs = rs1 ;
	    tcp->a = NULL ;
	    tcp->titles = NULL ;
	}
	tcp->lang[0] = '\0' ;
	tcp->wmark = 0 ;
	tcp->amark = 0 ;
	return rs ;
}
/* end subroutine (titlecache_release) */


local int mkshmname(char *rbuf,int rlen,cchar *rn,int rl,cchar *suf)
{
	int		rs = SR_OK ;
	int		i = 0 ;
	if ((rl != 0) && (rn[0] != '/')) {
	    rs = storebuf_chr(rbuf,rlen,i,'/') ;
	    i += 1 ;
	}
	if (rs >= 0) {
	    rs = storebuf_strw(rbuf,rlen,i,rn,rl) ;
	    i += rs ;
	}
	if (rs >= 0) {
	    rs = storebuf_chr(rbuf,rlen,i,'$') ;
	    i += rs ;
	}
	if (rs >= 0) {
	    rs = storebuf_strw(rbuf,rlen,i,suf,-1) ;
	    i += rs ;
	}
	return (rs >= 0) ? i : rs ;
}
/* end subroutine (mkshmname) */


