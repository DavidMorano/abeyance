/* proginfo SUPPORT */
/* lang=C++20 */

/* program information */
/* version %I% last-modified %G% */

#define	CF_GETEXECNAME	1		/* use 'getexecname()' */

/* revision history:

	= 1998-03-17, David A­D­ Morano
	I enhanced this somewhat from my previous version.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	proginfo

	Description:
	This group of subroutines help find and set from variables
	for program start-up type functions.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<unistd.h>		/* |gethostid(3c)| */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>		/* |strnlen(3c)| */
#include	<algorithm>		/* |min(3c++)| + |max(3c++)| */
#include	<usystem.h>
#include	<mallocxx.h>
#include	<getnodename.h>
#include	<getpwd.h>
#include	<getourenv.h>
#include	<getev.h>
#include	<vecstr.h>
#include	<shellunder.h>
#include	<sfx.h>
#include	<snx.h>
#include	<rmx.h>
#include	<mkpathx.h>
#include	<snwcpy.h>
#include	<strn.h>
#include	<strw.h>
#include	<matxstr.h>
#include	<mkchar.h>
#include	<hasx.h>
#include	<localmisc.h>

#include	"proginfo.hh"


/* local defines */

#ifndef	NODENAMELEN
#define	NODENAMELEN	256
#endif

#define	NOPROGNAME	"NP"

#ifndef	VAREXECFNAME
#define	VAREXECFNAME	"_EF"
#endif

#ifndef	VARUNDER
#define	VARUNDER	"_"
#endif


/* imported namespaces */

using std::nullptr_t ;			/* type */
using std::min ;			/* subroutine-template */
using std::max ;			/* subroutine-template */
using std::nothrow ;			/* constant */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */

template<typename ... Args>
static int proginfo_ctor(proginfo *op,Args ... args) noex {
	int		rs = SR_FAULT ;
	if (op && (args && ...)) {
	    cnullptr	np{} ;
	    rs = SR_NOMEM ;
	    if ((op->sdp = new(nothrow) vecstr) != np) {
	        if ((op->idp = new(nothrow) ids) != np) {
	            if ((op->lhp = new(nothrow) ids) != np) {
			rs = SR_OK ;
		    } /* end if (new-logfile) */
		    if (rs < 0) {
		        delete op->idp ;
		        op->idp = nullptr ;
		    }
		} /* end if (new-ids) */
		if (rs < 0) {
		    delete op->sdp ;
		    op->sdp = nullptr ;
		}
	    } /* end if (new-vecstr) */
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (proginfo_ctor) */

static int proginfo_dtor(proginfo *op) noex {
	int		rs = SR_FAULT ;
	if (op) {
	    rs = SR_OK ;
	    if (op->lhp) {
		delete op->lhp ;
		op->lhp = nullptr ;
	    }
	    if (op->idp) {
		delete op->idp ;
		op->idp = nullptr ;
	    }
	    if (op->sdp) {
		delete op->sdp ;
		op->sdp = nullptr ;
	    }
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (proginfo_dtor) */

static int	proginfo_setdefnames(proginfo *) noex ;

#ifdef	COMMENT
static int	proginfo_setdefdn(proginfo *) ;
static int	proginfo_setdefpn(proginfo *) ;
#endif

static bool	hasourbad(cchar *,int) noex ;


/* local variables */


/* exported variables */


/* exported subroutines */

int proginfo::start(mainv av,mainv ev,cc *ver) noex {
	int		rs = SR_FAULT ;
	if (argv && envv && ver) {
	    cint	vo = (VECSTR_OCONSERVE | VECSTR_OREUSE | VECSTR_OSWAP) ;
	    cint	vn = 10 ;
	    argv = av ;
	    envv = ev ;
	    if ((rs = vecstr_start(sdp,vn,vo)) >= 0) {
	        if ((rs = proginfo_pwd(pip)) >= 0) {
	            if (pip->argz != nullptr) {
	                rs = proginfo_setprogname(pip,pip->argz) ;
	            }
	            if (rs >= 0) {
	                if ((rs = proginfo_setdefnames(pip)) >= 0) {
	                    if (ver != nullptr) {
	                        cchar	**vpp = &pip->version ;
	                        rs = proginfo_setentry(pip,vpp,ver,-1) ;
	                    }
	                }
	            } /* end if (ok) */
	        }
	        if (rs < 0) {
	            vecstr_finish(pip->sdp) ;
	        }
	    } /* end if (vecstr-stores) */
	    if (rs < 0) {
		proginfo_dtor(op) ;
	    }
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (proginfo::start) */

int proginfo::ifinish() noex {
	int		rs = SR_OK ;
	int		rs1 ;
	if (lhp) {
	    rs1 = logfile_finish(lhp) ;
	    if (rs >= 0) rs = rs1 ;
	}
	if (idp) {
	    rs1 = ids_finish(idp) ;
	    if (rs >= 0) rs = rs1 ;
	}
	if (sdp) {
	    rs1 = vecstr_finish(sdp) ;
	    if (rs >= 0) rs = rs1 ;
	}
	{
	    rs1 = proginfo_dtor(this) ;
	    if (rs >= 0) rs = rs1 ;
	}
	return rs ;
}
/* end subroutine (proginfo::finish) */

int proginfo::setentry(cchar **epp,cchar *vp,int vl) noex {
	int		rs = SR_FAULT ;
	int		len = 0 ;
	if (epp) {
	    int		oi = -1 ;
	    if (*epp != nullptr) {
	        oi = vecstr_findaddr(sdp,*epp) ;
	    }
	    if (vp != nullptr) {
	        len = strnlen(vp,vl) ;
	        rs = vecstr_store(sdp,vp,len,epp) ;
	    } else {
	        *epp = nullptr ;
	    }
	    if ((rs >= 0) && (oi >= 0)) {
	        vecstr_del(sdp,oi) ;
	    }
	} /* end if (non-null) */
	return (rs >= 0) ? len : rs ;
}
/* end subroutine (proginfo_setentry) */

int proginfo::setversion(cchar *valp) noex {
	int		rs = SR_FAULT ;
	if (ver) {
	    cchar	**vpp = &pip->version ;
	    rs = proginfo_setentry(pip,vpp,valp,-1) ;
	}
	return rs ;
}
/* end subroutine (proginfo::setversion) */

int proginfo::setbanner(cchar *valp) noex {
	int		rs = SR_FAULT ;
	if (valp) {
	    cchar	**vpp = &pip->banner ;
	    rs = proginfo_setentry(pip,vpp,valp,-1) ;
	}
	return rs ;
}
/* end subroutine (proginfo_setbanner) */

int proginfo::setsearchname(cchar *var,cchar *valp) noex {
	int		rs = SR_FAULT ;
	int		cl = -1 ;
	cchar		*cp = valp ;

	if ((cp == nullptr) && (var != nullptr)) {
	    cp = getourenv(envv,var) ;
	    if (hasourbad(cp,-1) || ((cp != nullptr) && (cp[0] == '\0')))
	        cp = nullptr ;
	}

	if ((cp == nullptr) && (pip->progname != nullptr)) {
	    cp = pip->progname ;
	    if (cchar *tp ; (tp = strrchr(cp,'.')) != nullptr) {
	        cl = (tp - cp) ;
	    }
	}

	if ((rs >= 0) && (cp != nullptr)) {
	    char	searchname[MAXNAMELEN+1] ;
	    int		ml = MAXNAMELEN ;
	    if (hasuc(cp,cl)) {
	        if ((cl > 0) && (cl < ml)) ml = cl ;
	        cl = strwcpylc(searchname,cp,ml) - searchname ;
	        cp = searchname ;
	    }
	    {
	        cchar	**vpp = &pip->searchname ;
	        rs = proginfo_setentry(pip,vpp,cp,cl) ;
	    }
	} /* end if */

	return rs ;
}
/* end subroutine (proginfo::setsearchname) */

/* set program directory and program name (as might be possible) */
int proginfo_setprogname(proginfo *pip,cchar *ap) noex {
	int		rs = SR_OK ;
	int		al ;
	int		dl, bl ;
	cchar		*en ;
	cchar		*dn ;
	cchar		*dp, *bp ;

	if (ap == nullptr) return SR_FAULT ;

	en = pip->progename ;
	dn = pip->progdname ;
	al = strlen(ap) ;

	while ((al > 0) && (ap[al-1] == '/')) {
	    al -= 1 ;
	}

	if ((rs >= 0) && (pip->progename == nullptr)) {
	    if (ap[0] == '/') {
	        cchar	**vpp = &pip->progename ;
	        rs = proginfo_setentry(pip,vpp,ap,-1) ;
	    }
	}

	bl = sfbasename(ap,al,&bp) ;

/* set a program dirname? */

	if (rs >= 0) {
	    if (((en == nullptr) || (dn == nullptr)) && 
	        ((dl = sfdirname(ap,al,&dp)) > 0)) {
	        int	f_parent = FALSE ;
	        int	f_pwd = FALSE ;
	        int	f = FALSE ;

	        if (dp[0] == '.') {
	            f_pwd = (strcmp(dp,".") == 0) ;
	            if (! f_pwd) {
	                f_parent = (strcmp(dp,"..") == 0) ;
	            }
	            f = f_pwd || f_parent ;
	        } /* end if */

	        if (f) {
	            if (pip->pwd == nullptr) {
	                rs = proginfo_pwd(pip) ;
	            }
	            if (rs >= 0) {
	                if (f_pwd) {
	                    dp = pip->pwd ;
	                    dl = pip->pwdlen ;
	                } else {
	                    dl = sfdirname(pip->pwd,pip->pwdlen,&dp) ;
	                }
	            } /* end if (PWD or parent) */
	        } /* end if */

	        if ((rs >= 0) && (pip->progdname == nullptr)) {
	            cchar	**vpp = &pip->progdname ;
	            rs = proginfo_setentry(pip,vpp,dp,dl) ;
	        }

	        if ((rs >= 0) && (pip->progename == nullptr)) {
	            if ((bp != nullptr) && (bl > 0)) {
	                char	ename[MAXPATHLEN+1] ;
	                if ((rs = mkpath2w(ename,pip->progdname,bp,bl)) >= 0) {
	                    cchar	**vpp = &pip->progename ;
	                    rs = proginfo_setentry(pip,vpp,ename,-1) ;
	                }
	            } /* end if */
	        } /* end if */

	    } /* end if (have a dirname) */
	} /* end if (ok) */

/* set a program basename? */

	if (rs >= 0) {

	    if ((bp != nullptr) && (bl > 0)) {
	        if ((bl = rmext(bp,bl)) == 0) {
	            bp = NOPROGNAME ;
	            bl = -1 ;
	        }
	    }

	    if ((bp != nullptr) && (bl > 0)) {
	        if (hasourbad(bp,bl)) {
	            bp = nullptr ;
	            bl = 0 ;
	        }
	    }

	    if ((bp != nullptr) && (bl > 0) && (bp[0] == '-')) {
	        pip->pf.progdash = true ;
	        bp += 1 ;
	        bl -= 1 ;
	    }

	    if ((bp != nullptr) && (bl != 0)) {
	        cchar	**vpp = &pip->progname ;
	        rs = proginfo_setentry(pip,vpp,bp,bl) ;
	    }

	} /* end if (basename) */

	return rs ;
}
/* end subroutine (proginfo_setprogname) */

int proginfo_setprogroot(proginfo *pip,cchar *prp,int prl) noex {
	int		rs = SR_OK ;
	char		tbuf[MAXPATHLEN + 1] ;

	if (prp == nullptr) return SR_FAULT ;

	if (prl < 0) prl = strlen(prp) ;

	if (prp[0] != '/') {
	    if ((rs = proginfo_pwd(pip)) >= 0) {
	        rs = mkpath2w(tbuf,pip->pwd,prp,prl) ;
	        prl = rs ;
	        prp = tbuf ;
	    }
	}

	if (rs >= 0) {
	    cchar	**vpp = &pip->pr ;
	    rs = proginfo_setentry(pip,vpp,prp,prl) ;
	}

	return rs ;
}
/* end subroutine (proginfo_setprogroot) */

int proginfo_setexecname(proginfo *pip,cchar *enp) noex {
	int		rs = SR_OK ;

	if (enp == nullptr) return SR_FAULT ;

	if (pip->progename == nullptr) {
	    int		enl = strlen(enp) ;
	    while ((enl > 0) && (enp[enl-1] == '/')) enl -= 1 ;
	    if (enl > 0) {
	        cchar	**vpp = &pip->progename ;
	        rs = proginfo_setentry(pip,vpp,enp,enl) ;
	    }
	} else {
	    if (pip->progename != nullptr) {
	        rs = strlen(pip->progename) ;
	    }
	}

	return rs ;
}
/* end subroutine (proginfo_setexecname) */

int proginfo_pwd(proginfo *pip) noex {
	int		rs = SR_OK ;
	int		pwdlen = 0 ;

	if (pip->pwd == nullptr) {
	    char	pwdname[MAXPATHLEN + 1] ;
	    if ((rs = getpwd(pwdname,MAXPATHLEN)) >= 0) {
	        cchar	**vpp = &pip->pwd ;
	        pwdlen = rs ;
	        pip->pwdlen = pwdlen ;
	        rs = proginfo_setentry(pip,vpp,pwdname,pwdlen) ;
	    }
	} else {
	    pwdlen = pip->pwdlen ;
	}

	return (rs >= 0) ? pwdlen : rs ;
}
/* end subroutine (proginfo_pwd) */

int proginfo_progdname(proginfo *pip) noex {
	int		rs = SR_OK ;

	if (pip->progdname == nullptr) {

	    rs = proginfo_progename(pip) ;

	    if ((rs >= 0) && (pip->progename != nullptr)) {
	        int	dl ;
	        cchar	*dp ;
	        if ((dl = sfdirname(pip->progename,-1,&dp)) == 0) {
	            if (pip->pwd == nullptr) rs = proginfo_pwd(pip) ;
	            if ((rs >= 0) && (pip->pwd != nullptr)) {
	                dp = pip->pwd ;
	                dl = -1 ;
	            }
	        }
	        if ((rs >= 0) && (dl > 0)) {
	            cchar	**vpp = &pip->progdname ;
	            rs = proginfo_setentry(pip,vpp,dp,dl) ;
	        }
	    } /* end if */

	} else {
	    rs = strlen(pip->progdname) ;
	}

	return rs ;
}
/* end subroutine (proginfo_progdname) */

int proginfo_progename(proginfo *pip) noex {
	int		rs = SR_OK ;

	if (pip->progename == nullptr) {
	    shellunder_dat	su ;
	    cchar		*efn = nullptr ;

#if	defined(OSNAME_SunOS) && (OSNAME_SunOS > 0) && CF_GETEXECNAME
	    if ((rs >= 0) && (efn == nullptr)) {
	        efn = getexecname() ;
	    }
#endif /* SOLARIS */

	    if ((rs >= 0) && (efn == nullptr) && (efn[0] != '\0')) {
	        efn = getourenv(pip->envv,VAREXECFNAME) ;
	    }

	    if ((rs >= 0) && (efn == nullptr) && (efn[0] != '\0')) {
		cchar	*cp ;
	        if ((cp = getourenv(pip->envv,VARUNDER)) != nullptr) {
		    if (shellunder_wr(&su,cp) >= 0) {
	                efn = su.progename ;
		    }
	        }
	    }

	    if ((rs >= 0) && (efn != nullptr)) {
	        char	ebuf[MAXPATHLEN+1] ;
	        if (efn[0] != '/') {
	            if (pip->pwd == nullptr) {
			rs = proginfo_pwd(pip) ;
		    }
	            if (rs >= 0) {
	                rs = mkpath2(ebuf,pip->pwd,efn) ;
	                efn = ebuf ;
	            }
	        }
	        if (rs >= 0) {
	            rs = proginfo_setexecname(pip,efn) ;
	        }
	    }

	} else {
	    if (pip->progename != nullptr) {
	        rs = strlen(pip->progename) ;
	    }
	}

	return rs ;
}
/* end subroutine (proginfo_progename) */

int proginfo_nodename(proginfo *pip) noex {
	int		rs = SR_OK ;
	int		rs1 ;
	int		nl = 0 ;
	if (pip->nodename == nullptr) {
	    char	*nbuf{} ;
	    if ((rs = malloc_nn(&nbuf)) >= 0) {
		cint	nlen = rs ;
	        if ((rs = getnodename(nbuf,nlen)) >= 0) {
	            cchar	**vpp = &pip->nodename ;
	            nl = rs ;
	            rs = proginfo_setentry(pip,vpp,nbuf,nl) ;
	        }
		rs1 = uc_free(nbuf) ;
		if (rs >= 0) rs = rs1 ;
	    } /* end if (m-a-f) */
	} else {
	    nl = strlen(pip->nodename) ;
	}
	return (rs >= 0) ? nl : rs ;
}
/* end subroutine (proginfo_nodename) */

int proginfo_getename(proginfo *pip,char *rbuf,int rlen) noex {
	int		rs = SR_OK ;

	if (pip == nullptr) return SR_FAULT ;
	if (rbuf == nullptr) return SR_FAULT ;

	rbuf[0] = '\0' ;
	if ((rs = proginfo_progename(pip)) >= 0) {
	    if (pip->progename != nullptr) {
	        rs = sncpy1(rbuf,rlen,pip->progename) ;
	    }
	}

	return rs ;
}
/* end subroutine (proginfo_getename) */

int proginfo_getpwd(proginfo *pip,char *rbuf,int rlen) noex {
	int		rs = SR_OK ;

	if (pip == nullptr) return SR_FAULT ;
	if (rbuf == nullptr) return SR_FAULT ;

	rbuf[0] = '\0' ;
	if (pip->pwd == nullptr) {
	    rs = proginfo_pwd(pip) ;
	}

	if (rs >= 0) {
	    if (rlen >= pip->pwdlen) {
	        rs = sncpy1(rbuf,rlen,pip->pwd) ;
	    } else {
	        rs = SR_OVERFLOW ;
	    }
	}

	return rs ;
}
/* end subroutine (proginfo_getpwd) */

int proginfo_getenv(proginfo *pip,cchar *sp,int sl,cchar **rpp) noex {
	int		rs = SR_NOTFOUND ;
	if (sp == nullptr) return SR_FAULT ;
	if (pip->envv != nullptr) {
	    rs = getev(pip->envv,sp,sl,rpp) ;
	}
	return rs ;
}
/* end subroutine (proginfo_getenv) */


/* local subroutines */

static int proginfo_setdefnames(proginfo *pip) noex {
	int		rs = SR_OK ;

	if (pip->progname == nullptr) {
	    if ((rs = proginfo_progename(pip)) >= 0) {
	        if (pip->progename != nullptr) {
	            rs = proginfo_setprogname(pip,pip->progename) ;
	        }
	    }
	} /* end if */

	return rs ;
}
/* end subroutine (proginfo_setdefnames) */


#ifdef	COMMENT

/* Set Default (program) Directory-Name */
static int proginfo_setdefdn(proginfo *pip) noex {
	int		rs = SR_OK ;

	if (pip->progdname == nullptr) {
	    int		cl ;
	    cchar	*cp ;
	    if ((rs >= 0) && (pip->progename != nullptr)) {
	        if ((cl = sfdirname(pip->progename,-1,&cp)) > 0) {
	            cchar	**vpp = &pip->progdname ;
	            rs = proginfo_setentry(pip,vpp,cp,cl) ;
	        }
	    } /* end if */
	} /* end if */

	return rs ;
}
/* end subroutine (proginfo_setdefdn) */

/* Set Default Program-Name */
static int proginfo_setdefpn(proginfo *pip) noex {
	int		rs = SR_OK ;

	if (pip->progname == nullptr) {
	    int		cl ;
	    cchar	*cp ;
	    if (pip->progename != nullptr) {
	        if ((cl = sfbasename(pip->progename,-1,&cp)) > 0) {
	            cl = rmext(cp,cl) ;
	            if (cl == 0) {
	                cp = NOPROGNAME ;
	                cl = -1 ;
	            }
	        }
	        if ((cp != nullptr) && (cl != 0)) {
	            cchar	**vpp = &pip->progdname ;
	            rs = proginfo_setentry(pip,vpp,cp,cl) ;
	        }
	    } /* end if */
	} /* end if */

	return rs ;
}
/* end subroutine (proginfo_setdefpn) */

#endif /* COMMENT */

static bool hasourbad(cchar *sp,int sl) noex {
	bool		f = true ;
	if (sp) {
	    if (! (f = hasprintbad(sp,sl))) {
	        if (sl < 0) sl = strlen(sp) ;
	        for (int i = 0 ; i < sl ; i += 1) {
	            cint	sch = mkchar(sp[i]) ;
	            f = (sch >= 128) ;
	            if (f) break ;
	        } /* end for */
	    } /* end if */
	} /* end if */
	return f ;
}
/* end subroutine (hadourbad) */

proginfo_vals::proginfo_vals() noex {
	memclear(this) ;
}

void proginfo_hwser::operator () (proginfo_head *p) noex {
	op = p ;
	val = 0 ;
}

proginfo_hwser::operator uint () noex {
	if (val == 0) {
	    val = (uint) gethostid() ;
	}
	return val ;
}

proginfo_head::proginfo_head() noex {
	argc = 0 ;
	argv = nullptr ;
	envv = nullptr ;
	pwd = nullptr ;
	sdp = nullptr ;
	idp = nullptr ;
	lhp = nullptr ;
	now = {} ;
	hwserial(this) ;
	ncpu(this,proginfomem_ncpu) ;
}

void proginfo_head::args(int ac,mainv av,mainv ev) noex {
	argc = ac ;
	argv = av ;
	envv = ev ;
}

int proginfo_co::operator () (int) noex {
	int		rs = SR_BADFMT ;
	if (op) {
	    switch (w) {
	    case proginfomem_ncpu:
		rs = op->incpu() ;
		break ;
	    } /* end switch */
	}
	return rs ;
}
/* end method (proginfo_co::operator) */

int proginfo_head::incpu() noex {
	int		rs = ncpus ;
	if (rs == 0) {
	    rs = 1 ;
	}
	return rs ;
}
/* end method (proginfo_head::incpu) */


