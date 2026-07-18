/* devpermfile SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* read in a file of parameters */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-02-05, David A­D­ Morano
	Some code for this subroutine was taken from something that
	did something similar to what we are doing here. The rest
	was originally written for LevoSim.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	devpermfile

	Description:
	This object reads in the parameter file and makes the
	parameter pairs available thought a key search.

	Documentation:
	See |logindevperm(5)| and the source files under either
	Solaris® or Illumos® with file names that contain 'devperm'.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/stat.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<ctime>
#include	<cstddef>		/* |nullptr_t(3c++)| */
#include	<cstdlib>
#include	<cstring>		/* |strncmp(3c)| */
#include	<new>			/* |nothrow(3c++)| */
#include	<clanguage.h>
#include	<usysbase.h>
#include	<usyscalls.h>
#include	<uclibmem.h>
#include	<bufsizeget.h>
#include	<bfile.h>
#include	<field.h>
#include	<vecobj.h>
#include	<storebuf.h>
#include	<fsdir.h>
#include	<buffer.h>
#include	<nulstr.h>
#include	<pathclean.h>
#include	<cfnum.h>
#include	<sfx.h>
#include	<absfn.h>
#include	<strwcpy.h>
#include	<char.h>
#include	<hasx.h>
#include	<localmisc.h>

#include	"devpermfile.h"

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |lenstr(3u)| */

/* local defines */

#define	DP_ICHECKINT	2	/* file check interval (seconds) */
#define	DP_ICHANGEINT	2	/* wait change interval (seconds) */

#define	DP_KA		szof(mode_t)
#define	DP_BO(v)	((DP_KA - ((v) % DP_KA)) % DP_KA)

#define	DP		devpermfile
#define	DP_ENT		devpermfile_ent
#define	DP_CUR		devpermfile_cur
#define	DP_KEY		devpermfile_key
#define	DP_IE		devpermfile_ie


/* imported namespaces */

using std::nothrow ;			/* constant */


/* local typedefs */


/* external subroutines */

extern "C" {
    extern int uc_stat(cchar *,ustat *) noex ;
}


/* external variables */


/* local structures */

struct devpermfile_key {
	cchar		*console ;
	int		conlen ;
	int		count ;
} ;

struct devpermfile_ie {
	cchar		*dev ;		/* device string */
	int		ci ;		/* console index */
	int		devlen ;	/* device length */
	mode_t		dmode ;
} ;

namespace {
    struct vars {
	int		maxpathlen ;
	int		maxlinelen ;
	operator int () noex ;
    } ; /* end strcut (vars) */
} /* end namespace */

/* forward references */

template<typename ... Args>
static int devpermfile_ctor(devpermfile *op,Args ... args) noex {
    	DEVPERMFILE	*hop = op ;
	cnullptr	np{} ;
	int		rs = SR_FAULT ;
	if (op && (args && ...)) ylikely {
	    memclear(hop) ;
	    rs = SR_NOMEM ;
	    if ((op->klp = new(nothrow) vecobj) != np) ylikely {
	        if ((op->elp = new(nothrow) vecobj) != np) ylikely {
		    rs = SR_OK ;
	        } /* end if (new-vecobj) */
		if (rs < 0) {
		    delete op->klp ;
		    op->klp = nullptr ;
		}
	    } /* end if (new-vecobj) */
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (devpermfile_ctor) */

static int devpermfile_dtor(devpermfile *op) noex {
	int		rs = SR_FAULT ;
	if (op) ylikely {
	    rs = SR_OK ;
	    if (op->elp) ylikely {
		delete op->elp ;
		op->elp = nullptr ;
	    }
	    if (op->klp) ylikely {
		delete op->klp ;
		op->klp = nullptr ;
	    }
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (devpermfile_dtor) */

template<typename ... Args>
static inline int devpermfile_magic(devpermfile *op,Args ... args) noex {
	int		rs = SR_FAULT ;
	if (op && (args && ...)) ylikely {
	    rs = (op->magval == DEVPERMFILE_MAGIC) ? SR_OK : SR_NOTOPEN ;
	}
	return rs ;
}
/* end subroutine (devpermfile_magic) */

static int	devpermfile_finkeys(DP *) noex ;
static int	devpermfile_finents(DP *) noex ;
static int	devpermfile_parse(DP *,cchar *) noex ;
static int	devpermfile_parseln(DP *,cchar *,int) noex ;
static int	devpermfile_keyadd(DP *,cchar *,int) noex ;
static int	devpermfile_keydel(DP *,int) noex ;
static int	devpermfile_keyincr(DP *,int) noex ;
static int	devpermfile_keydecr(DP *,int) noex ;
static int	devpermfile_entexpand(DP *,int,mode_t,cchar *,int) noex ;
static int	devpermfile_entins(DP *,int,mode_t,cchar *,int) noex ;
static int	devpermfile_entdir(DP *,int,mode_t,cchar *,int) noex ;
static int	devpermfile_entadd(DP *,DP_IE *) noex ;
static int	devpermfile_keymat(DP *,DP_IE *,cchar *) noex ;

static int	key_start(DP_KEY *,cchar *,int) noex ;
static int	key_incr(DP_KEY *) noex ;
static int	key_decr(DP_KEY *) noex ;
static int	key_count(DP_KEY *) noex ;
static int	key_mat(DP_KEY *,cchar *,int) noex ;
static int	key_finish(DP_KEY *) noex ;
static int	key_fake(DP_KEY *,cchar *,int) noex ;

static int	ientry_start(DP_IE *,int,mode_t,cchar *,int) noex ;
static int	ientry_ci(DP_IE *) noex ;
static int	ientry_finish(DP_IE *) noex ;

static int	entry_load(DP_ENT *,char *,int,DP_IE *) noex ;

static int	mkdirfile(char *,cchar *,int,cchar *,int) noex ;

static int	vkeymat(cvoid **,cvoid **) noex ;

static mode_t	modeparse(cchar *,int) noex ;


/* local variables */

static vars		var ;

/* key field terminators (pound, equal, colon, and all white space) */
constexpr char		kterms[32] = {
	0x00, 0x1B, 0x00, 0x00,
	0x09, 0x00, 0x00, 0x20,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00
} ;

/* argument field terminators (pound and all white space) */
constexpr char		aterms[32] = {
	0x00, 0x1B, 0x00, 0x00,
	0x09, 0x00, 0x00, 0x04,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00
} ;


/* exported variables */


/* exported subroutines */

static int devpermfile_opener(DP *) noex ;

int devpermfile_open(DP *op,cc *fname) noex {
	int		rs ;
	int		rs1 ;
	if ((rs = devpermfile_ctor(op,fname)) >= 0) {
	    rs = SR_INVALID ;
	    if (fname[0]) {
		if ((rs = var) >= 0) {
	            op->intcheck = DP_ICHECKINT ;
	            op->intchange = DP_ICHANGEINT ;
	            op->ti_check = getustime ;
	            cchar	*fn ;
	            if (absfn catfn ; (rs = catfn.start(fname,-1,&fn)) >= 0) {
	                if (cc *cp ; (rs = lm_strw(fn,rs,&cp)) >= 0) {
	                    op->fname = cp ;
		            rs = devpermfile_opener(op) ;
			    if (rs < 0) {
			        void *vp = voidp(op->fname) ;
			        lm_free(vp) ;
			        op->fname = nullptr ;
			    } /* end if (error) */
	                } /* end if (memory-acquire) */
	                rs1 = catfn.finish ;
	                if (rs >= 0) rs = rs1 ;
	            } /* end if (absfn) */
		} /* end if (vars) */
	    } /* end if (valid) */
	    if (rs < 0) {
		devpermfile_dtor(op) ;
	    }
	} /* end if (devpermfile_ctor) */
	return rs ;
}
/* end subroutine (devpermfile_open) */

static int devpermfile_opener(DP *op) noex {
	int		vsz = szof(DP_KEY) ;
	cint		vn = 10 ;
	int		vo = vecobjm.stationary ;
    	int		rs ;
	if ((rs = vecobj_start(op->klp,vsz,vn,vo)) >= 0) {
	    /* keep this not-sorted so that the original order is maintained */
	    vsz = szof(DP_IE) ;
	    vo = 0 ;
	    if ((rs = vecobj_start(op->elp,vsz,vn,vo)) >= 0) {
		if ((rs = devpermfile_parse(op,op->fname)) >= 0) {
		    op->magval = DEVPERMFILE_MAGIC ;
		}
		if (rs < 0) {
		    devpermfile_finents(op) ;
		    vecobj_finish(op->elp) ;
		} /* end if (error) */
	    }
	    if (rs < 0) {
		vecobj_finish(op->klp) ;
	    } /* end if (error) */
	} /* end if (keys.start) */
	return rs ;
}
/* end subroutine (devpermfile_opener) */

/* free up the resources occupied by a DP list object */
int devpermfile_close(DP *op) noex {
	int		rs ;
	int		rs1 ;
	if ((rs = devpermfile_magic(op)) >= 0) {
	    {
	        rs1 = devpermfile_finents(op) ;
	        if (rs >= 0) rs = rs1 ;
	    }
	    {
	        rs1 = devpermfile_finkeys(op) ;
	        if (rs >= 0) rs = rs1 ;
	    }
	    {
	        rs1 = vecobj_finish(op->elp) ;
	        if (rs >= 0) rs = rs1 ;
	    }
	    {
	        rs1 = vecobj_finish(op->klp) ;
	        if (rs >= 0) rs = rs1 ;
	    }
	    if (op->fname) {
		void *vp = voidp(op->fname) ;
	        rs1 = lm_free(vp) ;
	        if (rs >= 0) rs = rs1 ;
	        op->fname = nullptr ;
	    }
	    {
		rs1 = devpermfile_dtor(op) ;
	        if (rs >= 0) rs = rs1 ;
	    }
	    op->magval = 0 ;
	} /* end if (magic) */
	return rs ;
}
/* end subroutine (devpermfile_close) */

int devpermfile_curbegin(DP *op,DP_CUR *cp) noex {
    	int		rs ;
	if ((rs = devpermfile_magic(op,cp)) >= 0) {
	    op->ccount += 1 ;
	    cp->i = -1 ;
	} /* end if (magic) */
	return rs ;
}
/* end subroutine (devpermfile_curbegin) */

int devpermfile_curend(DP *op,DP_CUR *cp) noex {
    	int		rs ;
	if ((rs = devpermfile_magic(op,cp)) >= 0) {
	   if (op->ccount > 0) op->ccount -= 1 ;
	   cp->i = -1 ;
	} /* end if (magic) */
	return rs ;
}
/* end subroutine (devpermfile_curend) */

/* search the parameters for a match */
int devpermfile_curfetch(DP *op,cc *key,DP_CUR *curp,DP_ENT *ep,
		char *ebuf,int elen) noex {
	int		rs ;
	int		el = 0 ; /* return-value */
	if ((rs = devpermfile_magic(op,key,curp,ep,ebuf)) >= 0) {
	    rs = SR_INVALID ;
	    if (key[0]) {
		vecobj	*elp = op->elp ;
		DP_IE	*iep{} ;
		cint	j = (curp->i >= 0) ? (curp->i + 1) : 0 ;
		int	i ; /* used-afterwards */
		void	*vp{} ;
	        for (i = j ; (rs = elp->get(i,&vp)) >= 0 ; i += 1) {
		    iep = (DP_IE *) vp ;
	            if (vp) {
	                if (devpermfile_keymat(op,iep,key)) break ;
		    }
	        } /* end for (looping through entries) */
	        if ((rs >= 0) && iep) {
	            if ((rs = entry_load(ep,ebuf,elen,iep)) >= 0) {
			el = rs ;
	                curp->i = i ;
	            }
	        }
	    } /* end if (valid) */
	} /* end if (magic) */
	return (rs >= 0) ? el : rs ;
}
/* end subroutine (devpermfile_curfetch) */

int devpermfile_curenum(DP *op,DP_CUR *curp,DP_ENT *ep,
		char *ebuf,int elen) noex {
	int		rs ;
	int		el = 0 ; /* return-value */
	if ((rs = devpermfile_magic(op,curp,ep,ebuf)) >= 0) {
	    vecobj	*elp = op->elp ;
	    DP_IE	*iep{} ;
	    cint	j = (curp->i >= 0) ? (curp->i + 1) : 0 ;
	    int		i ; /* used-afterwards */
	    void	*vp{} ;
	    for (i = j ; (rs = elp->get(i,&vp)) >= 0 ; i += 1) {
		iep = (DP_IE *) vp ;
	        if (vp) break ;
	    } /* end for */
	    if ((rs >= 0) && iep) {
	        if ((rs = entry_load(ep,ebuf,elen,iep)) >= 0) {
	            el = rs ;
	            curp->i = j ;
	        }
	    }
	} /* end if (magic) */
	return (rs >= 0) ? el : rs ;
}
/* end subroutine (devpermfile_curenum) */

int devpermfile_checkint(DP *op,int intcheck) noex {
    	int		rs ;
	if ((rs = devpermfile_magic(op)) >= 0) {
	    if (intcheck < 1) intcheck = 1 ;
	    op->intcheck = intcheck ;
	} /* end if (magic) */
	return rs ;
}
/* end subroutine (devpermfile_checkint) */

/* check if the parameter file has changed */
int devpermfile_check(DP *op,time_t dt) noex {
	int		rs ;
	int		f_changed = false ; /* return-value */
	if ((rs = devpermfile_magic(op)) >= 0) {
	    if (dt == 0) dt = getustime ;
	    if ((dt - op->ti_check) >= op->intcheck) {
	        op->ti_check = dt ;
	        /* check the files */
	        if (ustat sb ; (rs = uc_stat(op->fname,&sb)) >= 0) {
	    	    bool	f = false ;
	            f = f || (sb.st_mtime > op->ti_mod) ;
	            f = f || (sb.st_size != op->fsize) ;
	            if (f && ((dt - sb.st_mtime) >= op->intchange)) {
	    	        op->ti_mod = sb.st_mtime ;
	    	        op->fsize = sb.st_size ;
	    	        f_changed = true ;
	    	        devpermfile_finents(op) ;
	    	        rs = devpermfile_parse(op,op->fname) ;
		    } /* end if */
		} /* end if (stat) */
	    }
	} /* end if (magic) */
	return (rs >= 0) ? f_changed : rs ;
}
/* end subroutine (devpermfile_check) */


/* private subroutines */

static int devpermfile_parser(DP *op,cchar *fname) noex ;

static int devpermfile_parse(DP *op,cchar *fname) noex {
	int		rs = SR_FAULT ;
	int		c = 0 ; /* return-value */
	if (fname) ylikely {
	    rs = SR_INVALID ;
	    if (fname[0]) {
		rs = devpermfile_parser(op,fname) ;
		c = rs ;
	    } /* end if (valid) */
	} /* end if (non-null) */
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (devpermfile_parse) */

static int devpermfile_parser(DP *op,cchar *fname) noex {
    	cnullptr	np{} ;
    	int		rs ;
	int		rs1 ;
	int		c = 0 ;
	if (char *lbuf ; (rs = lm_ml(&lbuf)) >= 0) {
	    cint	llen = rs ;
	    cmode	om = 0 ;
	    if (bfile lf ; (rs = lf.open(fname,"r",om)) >= 0) {
		if (ustat sb ; (rs = lf.control(BC_STAT,&sb)) >= 0) {
		    op->ti_mod = sb.st_mtime ;
		    op->fsize = sb.st_size ;
		    while ((rs = lf.readlns(lbuf,llen,-1,np)) > 0) {
			cchar	*cp ;
			if (int cl ; (cl = sfcontent(lbuf,rs,&cp)) > 0) {
			    rs = devpermfile_parseln(op,cp,cl) ;
			    c += rs ;
			}
	    		if (rs < 0) break ;
		    } /* end while (reading lines) */
		    if (rs < 0) {
			devpermfile_finents(op) ;
		    }
		} /* end if (bcontrol) */
		rs1 = lf.close ;
		if (rs >= 0) rs = rs1 ;
	    } /* end if (bfile) */
	    rs1 = lm_free(lbuf) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (m-a-f) */
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (devpermfile_parser) */

static int devpermfile_parseln(DP *op,cchar *lp,int ll) noex {
	int		rs ;
	int		rs1 ;
	int		c = 0 ;
	if (field fsb ; (rs = fsb.start(lp,ll)) >= 0) {
	    cchar	*kp ;
	    /* get the "console" field */
	    if (int kl ; (kl = fsb.get(kterms,&kp)) > 0) {
		cchar	*mp ;
		/* get the "mode" field */
		if (int ml ; (ml = fsb.get(kterms,&mp)) > 0) {
		    cchar	*dp ;
		    int		ci = -1 ;
		    bool	f_key = false ;
		    bool	f_mode = false ;
		    mode_t	dm{} ;
		    /* get "devices" */
	    	    for (int dl ; (dl = fsb.get(aterms,&dp)) >= 0 ; ) {
	                if (dl > 0) {
			    if (! f_key) {
			        f_key = true ;
			        rs = devpermfile_keyadd(op,kp,kl) ;
			        ci = rs ;
			    }
		            if ((rs >= 0) && (! f_mode)) {
			        f_mode = true ;
			        dm = modeparse(mp,ml) ; /* cannot fail */
		            }
		            if (rs >= 0) {
				rs = devpermfile_entexpand(op,ci,dm,dp,dl) ;
			        c += rs ;
			    } /* end if */
	                } /* end if (non-empty device field) */
	                if (fsb.term == '#') break ;
		        if (rs < 0) break ;
		    } /* end for (fields) */
		    if (f_key && (c == 0) && (ci >= 0)) {
			devpermfile_keydel(op,ci) ;
		    }
		} /* end if (got mode) */
	    } /* end if (got key) */
	    rs1 = fsb.finish ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (field) */
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (devpermfile_parseln) */

/* add an entry to something */
static int devpermfile_entadd(DP *op,DP_IE *iep) noex {
	vecobj		*elp = op->elp ;
	return elp->add(iep) ;
}
/* end subroutine (devpermfile_entadd) */

/* free up ALL of the keys */
static int devpermfile_finkeys(DP *op) noex {
	vecobj		*klp = op->klp ;
	int		rs = SR_OK ;
	void		*vp{} ;
	for (int i = 0 ; klp->get(i,&vp) >= 0 ; i += 1) {
	    DP_KEY	*kep = (DP_KEY *) vp ;
	    if (vp) {
	        key_finish(kep) ;
	        vecobj_del(klp,i--) ;
	    }
	} /* end for */
	return rs ;
}
/* end subroutine (devpermfile_finkeys) */

/* free up ALL of the entries in this DP list */
static int devpermfile_finents(DP *op) noex {
	vecobj		*elp = op->elp ;
	int		rs = SR_OK ;
	void		*vp{} ;
	for (int i = 0 ; elp->get(i,&vp) >= 0 ; i += 1) {
	    DP_IE	*iep = (DP_IE *) vp ;
	    if (vp) {
	        devpermfile_keydecr(op,iep->ci) ;
	        ientry_finish(iep) ;
	        vecobj_del(elp,i--) ;
	    }
	} /* end for */
	return rs ;
}
/* end subroutine (devpermfile_finents) */

static int devpermfile_keyadd(DP *op,cchar *kp,int kl) noex {
	vecobj		*klp = op->klp ;
	cnullptr	np{} ;
	cint		rsn = SR_NOTFOUND ;
	int		rs ;
	int		rs1 ;
	int		ci = 0 ; /* return-value */
	if (char *tbuf ; (rs = lm_mp(&tbuf)) >= 0) {
	    if ((rs = pathclean(tbuf,kp,kl)) >= 0) {
		cint	cl = rs ;
	        if (DP_KEY k ; (rs = key_fake(&k,tbuf,cl)) >= 0) {
	            if ((rs = klp->search(&k,vkeymat,np)) >= 0) {
			ci = rs ;
		    } else if (rs == rsn) {
	                if ((rs = key_start(&k,tbuf,cl)) >= 0) {
	                    rs = klp->add(&k) ;
	        	    ci = rs ;
	        	    if (rs < 0) {
				key_finish(&k) ;
			    } /* end if (error) */
			} /* end if (key_start) */
		    } /* end if (was not found) */
		} /* end if (key_fake) */
	    } /* end if (pathclean) */
	    rs1 = lm_free(tbuf) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (m-a-f) */
	return (rs >= 0) ? ci : rs ;
}
/* end subroutine (devpermfile_keyadd) */

static int devpermfile_keydel(DP *op,int ci) noex {
	vecobj		*klp = op->klp ;
	int		rs ;
	void		*vp{} ;
	if ((rs = klp->get(ci,&vp)) >= 0) {
	    DP_KEY	*kep = (DP_KEY *) vp ;
	    if ((rs = key_count(kep)) == 0) {
	        key_finish(kep) ;
	        klp->del(ci) ;
	    }
	}
	return rs ;
}
/* end subroutine (devpermfile_keydel) */

static int devpermfile_keyincr(DP *op,int ci) noex {
	vecobj		*klp = op->klp ;
	int		rs ;
	void		*vp{} ;
	if ((rs = klp->get(ci,&vp)) >= 0) {
	    DP_KEY	*kep = (DP_KEY *) vp ;
	    if (vp) {
	        key_incr(kep) ;
	    }
	}
	return rs ;
}
/* end subroutine (devpermfile_keyincr) */

static int devpermfile_keydecr(DP *op,int ci) noex {
	vecobj		*klp = op->klp ;
	int		rs ;
	void		*vp{} ;
	if ((rs = klp->get(ci,&vp)) >= 0) {
	    DP_KEY	*kep = (DP_KEY *) vp ;
	    if (vp) {
	        if ((rs = key_decr(kep)) == 0) { /* equal-zero */
		    key_finish(kep) ;
		    klp->del(ci) ;
		}
	    }
	}
	return rs ;
}
/* end subroutine (devpermfile_keydecr) */

static int devpermfile_entexpand(DP *op,int ci,mode_t dm,cc *dp,int dl) noex {
	int		rs = SR_FAULT ;
	int		c = 0 ; /* return-value */
	if (dp) ylikely {
	    cchar	*bp ;
	    if (dl < 0) dl = lenstr(dp) ;
	    if (int bl ; (bl = sfbasename(dp,dl,&bp)) > 0) ylikely {
	        if ((bl == 1) && (bp[0] == '*')) {
		    cint tl = intconv(bp - 1 - dp) ;
	            rs = devpermfile_entdir(op,ci,dm,dp,tl) ;
	            c += rs ;
	        } else {
	            rs = devpermfile_entins(op,ci,dm,dp,dl) ;
	            c += rs ;
	        }
	    } /* end if (sfbasename) */
	} /* end if (non-null) */
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (devpermfile_entexpand) */

static int devpermfile_entins(DP *op,int ci,mode_t dmode,cc *dp,int dl) noex {
	int		rs ;
	int		c = 0 ; /* return-value */
	if (DP_IE ie ; (rs = ientry_start(&ie,ci,dmode,dp,dl)) >= 0) {
	    if ((rs = devpermfile_keyincr(op,ci)) >= 0) {
		c += 1 ;
		rs = devpermfile_entadd(op,&ie) ;
		if (rs < 0) {
	 	    devpermfile_keydecr(op,ci) ;
		}
	    } /* end if (devpermfile_keyincr) */
	    if (rs < 0) {
		ientry_finish(&ie) ;
	    }
	} /* end if (ientry_start) */
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (devpermfile_entins) */

static int devpermfile_entdirs(DP *,char *,int,mode_t,cchar *,int) noex ;

static int devpermfile_entdir(DP *op,int ci,mode_t dm,cc *dp,int dl) noex {
	int		rs ;
	int		rs1 ;
	int		c = 0 ; /* return-value */
	(void) ci ;
	if (char *tbuf ; (rs = lm_mp(&tbuf)) >= 0) {
	    cchar	*dname ;
	    if (nulstr ns ; (rs = ns.start(dp,dl,&dname)) >= 0) {
		{
	            rs = devpermfile_entdirs(op,tbuf,ci,dm,dname,dl) ;
		    c = rs ;
		}
	        rs1 = ns.finish ;
	        if (rs >= 0) rs = rs1 ;
	    } /* end if (nullstr) */
	    rs1 = lm_free(tbuf) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (m-a-f) */
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (devpermfile_entdir) */

static int devpermfile_entdirs(DP *op,char *tbuf,int ci,mode_t dm,
		cc *dp,int dl) noex {
	int		rs ;
	int		rs1 ;
	int		c = 0 ;
	if (char *nbuf ; (rs = lm_mn(&nbuf)) >= 0) {
	    cint	nlen = rs ;
	    if (fsdir d ; (rs = d.open(dp)) >= 0) {
		for (fsdir_ent de ; (rs = d.read(&de,nbuf,nlen)) > 0 ; ) {
		    cchar	*dnp = nbuf ;
		    cint	dnl = rs ;
		    if (hasnotdots(dnp,dnl)) {
			if ((rs = mkdirfile(tbuf,dp,dl,dnp,dnl)) >= 0) {
	                    rs = devpermfile_entins(op,ci,dm,tbuf,rs) ;
	                    c += rs ;
			}
	 	    }
		    if (rs < 0) break ;
	        } /* end for (reading) */
	        rs1 = d.close ;
	        if (rs >= 0) rs = rs1 ;
	    } /* end if (fsdir_open) */
	    rs1 = lm_free(nbuf) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (m-a-f) */
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (devpermfile_entdir) */

static int devpermfile_keymat(DP *op,DP_IE *iep,cchar *key) noex {
    	vecobj		*klp = op->klp ;
	int		rs ;
	int		f = false ; /* return-value */
	if ((rs = ientry_ci(iep)) >= 0) {
	    cint	ci = rs ;
	    if (void *vp ; (rs = klp->get(ci,&vp)) >= 0) {
	        DP_KEY	*kep = (DP_KEY *) vp ;
	        if (vp) {
		    cint	keylen = lenstr(key) ;
	            f = key_mat(kep,key,keylen) ;
	        }
	    } /* end if (vecobj_get) */
	} /* end if (ientry_ci) */
	return (rs >= 0) ? f : rs ;
}
/* end subroutine (devpermfile_keymat) */

static int key_start(DP_KEY *kep,cchar *conbuf,int conlen) noex {
	int		rs = SR_FAULT ;
	if (kep && conbuf) ylikely {
	    rs = SR_INVALID ;
	    memclear(kep) ;
	    if (conbuf[0]) ylikely {
	        if (conlen < 0) conlen = lenstr(conbuf) ;
	        if (cchar *cp ; (rs = lm_strw(conbuf,conlen,&cp)) >= 0) {
	            kep->console = cp ;
	            kep->conlen = conlen ;
	        }
	    } /* end if (valid) */
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (key_start) */

static int key_incr(DP_KEY *kep) noex {
    	int		rs = SR_FAULT ;
	if (kep) ylikely {
	    kep->count += 1 ;
	    rs = kep->count ;
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (key_incr) */

static int key_decr(DP_KEY *kep) noex {
    	int		rs = SR_FAULT ;
	if (kep) ylikely {
	    if (kep->count > 0) kep->count -= 1 ;
	    rs = kep->count ;
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (key_decr) */

static int key_count(DP_KEY *kep) noex {
    	int		rs = SR_FAULT ;
	if (kep) ylikely {
	    rs = kep->count ;
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (key_count) */

static int key_mat(DP_KEY *kep,cchar *keyp,int keyl) noex {
    	int		rs = SR_FAULT ;
	int		f = false ; /* return-value */
	if (kep && keyp) ylikely {
	    cint	cl = kep->conlen ;
	    cchar	*cp = kep->console ;
	    rs = SR_OK ;
	    if (keyl < 0) keyl = lenstr(keyp) ;
	    f = (keyl == cl) ;
	    f = f && (strncmp(cp,keyp,cl) == 0) ;
	} /* end if (non-null) */
	return (rs >= 0) ? f : rs ;
}
/* end subroutine (key_mat) */

static int key_finish(DP_KEY *kep) noex {
	int		rs = SR_FAULT ;
	int		rs1 ;
	if (kep) ylikely {
	    rs = SR_OK ;
	    if (kep->console) {
	        void *vp = voidp(kep->console) ;
	        rs1 = lm_free(vp) ;
		if (rs >= 0) rs = rs1 ;
	        kep->console = nullptr ;
	    }
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (key_finish) */

static int key_fake(DP_KEY *kep,cchar *keyp,int keyl) noex {
    	int		rs = SR_FAULT ;
	if (kep && keyp) ylikely {
	    if (keyl < 0) keyl = lenstr(keyp) ;
	    kep->console = keyp ;
	    kep->conlen = keyl ;
	    rs = keyl ;
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (key_fake) */

static int ientry_start(DP_IE *iep,int ci,mode_t m,cc *dp,int dl) noex {
	int		rs = SR_FAULT ;
	if (iep && dp) ylikely {
	    rs = SR_INVALID ;
	    memclear(iep) ;
	    if (ci >= 0) {
	        iep->ci = ci ;
	        iep->dmode = m ;
	        if (dl < 0) dl = lenstr(dp) ;
	        if (cchar *cp ; (rs = lm_strw(dp,dl,&cp)) >= 0) {
	            iep->dev = cp ;
	            iep->devlen = rs ;
	        }
	    } /* end if (valid) */
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (ientry_start) */

static int ientry_finish(DP_IE *iep) noex {
    	int		rs = SR_FAULT ;
	int		rs1 ;
	if (iep) ylikely {
	    rs = SR_OK ;
	    if (iep->dev) ylikely {
	        void *vp = voidp(iep->dev) ;
	        rs1 = lm_free(vp) ;
		if (rs >= 0) rs = rs1 ;
	        iep->dev = nullptr ;
	    }
	    iep->devlen = 0 ;
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (ientry_finish) */

static int ientry_ci(DP_IE *iep) noex {
    	int		rs = SR_FAULT ;
	if (iep) {
	    rs = iep->ci ;
	}
	return rs ;
}
/* end subroutine (ientry_ci) */

static int entry_load(DP_ENT *ep,char *ebuf,int elen,DP_IE *iep) noex {
	int		rs = SR_FAULT ;
	int		el = 0 ; /* return-value */
	if (ep && ebuf && iep) ylikely {
	    rs = SR_INVALID ;
	    memclear(ep) ;
	    if (elen > 0) {
	        cint	bo = DP_BO((ulong) ebuf) ;
	        cint	ilen = (iep->devlen + 1) ;
	        char	*bp = ebuf ;
		rs = SR_OK ;
	        ep->devmode = iep->dmode ;
	        ep->devlen = iep->devlen ;
	        bp += bo ;
	        elen -= bo ;
	        if (ilen < elen) {
		    ep->dev = bp ;
	            bp = strwcpy(bp,iep->dev,iep->devlen) + 1 ;
		    elen -= ilen ;
	        } else {
	            rs = SR_OVERFLOW ;
		}
		el = intconv(bp - ebuf) ;
	    } /* end if (valid) */
	} /* end if (non-null) */
	return (rs >= 0) ? el : rs ;
}
/* end subroutine (entry_load) */

static int mkdirfile(char *bufp,cc *dp,int dl,cc *dnp,int dnl) noex {
	cint		bufl = var.maxpathlen ;
	int		rs = SR_OK ;
	int		i = 0 ;
	if (rs >= 0) ylikely {
	    rs = storebuf_strw(bufp,bufl,i,dp,dl) ;
	    i += rs ;
	}
	if ((rs >= 0) && (i > 0) && (bufp[i - 1] != '/')) {
	    rs = storebuf_chr(bufp,bufl,i,'/') ;
	    i += rs ;
	}
	if (rs >= 0) ylikely {
	    rs = storebuf_strw(bufp,bufl,i,dnp,dnl) ;
	    i += rs ;
	}
	return (rs >= 0) ? i : rs ;
}
/* end subroutine (mkdirfile) */

vars::operator int () noex {
    	int		rs ;
	if ((rs = maxpathlen) == 0) {
	    if ((rs = bufsizeget(bufsize_mp)) >= 0) {
	        maxpathlen = rs ;
	        if ((rs = bufsizeget(bufsize_ml)) >= 0) {
	            maxlinelen = rs ;
	        }
	    }
	} /* end if (initialization needed) */
	return rs ;
} /* end method (vars::operator) */

static int keymat(DP_KEY *e1p,DP_KEY *e2p) noex {
    	int		rc ;
	if ((rc = (e1p->console[0] - e2p->console[0])) == 0) {
	    rc = strcmp(e1p->console,e2p->console) ;
	}
	return rc ;
}

static int vkeymat(cvoid **v1pp,cvoid **v2pp) noex {
	DP_KEY		*e1p = (DP_KEY *) *v1pp ;
	DP_KEY		*e2p = (DP_KEY *) *v2pp ;
	int		rc = 0 ;
	if (e1p || e2p) {
	    rc = +1 ;
	    if (e1p) {
		rc = -1 ;
		if (e2p) {
		    rc = keymat(e1p,e2p) ;
		}
	    }
	}
	return rc ;
}
/* end subroutine (vkeymat) */

static mode_t modeparse(cchar *mp,int ml) noex {
	mode_t	m = 0600 ;
	if (ml < 0) ml = lenstr(mp) ;
	if (ml > 0) {
	    if (int v ; cfnumi(mp,ml,&v) >= 0) {
		if (v > 0777) v = 0777 ;
		m = mode_t(v) ;
	    }
	}
	return m ;
}
/* end subroutine (modeparse) */


