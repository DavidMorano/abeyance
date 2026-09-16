/* dialuux SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* perform remote UUX service execution */
/* version %I% last-modified %G% */

#define	CF_DEBUG	0		/* compile-time debugging */
#define	CF_GETPROGROOT	1		/* use |getprogroot(3dam)| */

/* revision history:

	= 1998-07-10, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	dialuux

	Description:
	This is a dialer to connect to the UUX facility.

	Synopsis:
	int dialuux(cc *pr,cc *node,cc *svc,mv argv,cc *u,cc *g,int opts) noex

	Arguments:
	pr		program-root
	node		target node
	svc		target service
	argv		arguments to program
	u		c-string user-name
	g		c-string group-name
	opts		options

	Returns:
	>=0		file descriptor to program STDIN and STDOUT
	<0		error code (system-return)

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/param.h>		/* POSIX® */
#include	<sys/stat.h>		/* POSIX® */
#include	<unistd.h>		/* POSIX® */
#include	<fcntl.h>		/* POSIX® */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstring>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<uclibmem.h>		/* LIBUC */
#include	<getpwd.h>		/* LIBUC */
#include	<getprogroot.h>		/* LIBUC */
#include	<vecstr.h>		/* LIBUC */
#include	<storebuf.h>		/* LIBUC */
#include	<sncpyx.h>		/* LIBUC */
#include	<strn.h>		/* LIBUC */
#include	<strw.h>		/* LIBUC */
#include	<mkpathx.h>		/* LIBUC */
#include	<pathclean.h>		/* LIBUC */
#include	<matxstr.h>		/* LIBUC */
#include	<uuname.h>		/* LIBUC */
#include	<strx.h>		/* LIBUC */
#include	<vardefs.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */
#include	<libdebug.h>		/* LIBDEBUG |DEBUGPRINTF(3debug)| */

#include	"dialuux.h"


/* local defines */

#ifndef	DEFINITFNAME
#define	DEFINITFNAME	"/etc/default/init"
#endif

#ifndef	DEFLOGFNAME
#define	DEFLOGFNAME	"/etc/default/login"
#endif

#ifndef	NULLGNAME
#define	NULLGNAME	"/dev/null"
#endif

#ifndef	VARPRUUX
#define	VARPRUUX	"UUX_PROGRAMROOT"
#endif

#define	BUFLEN		MAXPATHLEN

#define	PROG_UUX	"uux"

#define	NENVS		120

#ifndef	CF_DEBUG
#define	CF_DEBUG	0		/* compile-time debugging */
#endif


/* imported namespaces */

using libuc::libmem ;			/* variable */


/* local typedefs */


/* external subroutines */

extern "C" {
   extern int	prgetprogpath	(cchar *,char *,cchar *,int) noex ;
}


/* external variables */


/* local structures */

struct envpop {
	cchar	*name ;
	cchar	*sub1dname ;
	cchar	*sub2dname ;
} ; /* end struct */


/* forward reference */

local int	vecstr_defenvs(vecstr *,cchar **) noex ;
local int	vecstr_loadpath(vecstr *,cchar *) noex ;
local int	mkpathval(vecstr *,char *,int) noex ;

local int	procenvpaths(cchar *,vecstr *) noex ;
local int	mknodesvc(char *,int,cchar *,cchar *) noex ;
local int	havenode(cchar *,cchar *) noex ;


/* local variables */

constexpr cpcchar	prnames[] = {
	"LOCAL",
	"NCMP",
	"EXTRA",
	"PCS",
	nullptr
} ; /* end array */

constexpr cpcchar	envdefs[] = {
	"PATH",
	"LD_LIBRARY_PATH",
	"MAIL",
	"MAILDIR",
	nullptr
} ; /* end array */

constexpr envpop	envpops[] = {
	{ VARPATH,	"bin",		"sbin" },
	{ VARLIBPATH,	"lib",		nullptr },
	{ VARMANPATH,	"man",		nullptr },
	{ nullptr,	nullptr,	nullptr }
} ; /* end array */

cbool			f_debug		= CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int dialuux(cc *pr,cc *node,cc *svc,mainv argv,cc *u,cc *g,int opts) noex {
	vecstr		args ;
	vecstr		envs ;
	int		rs = SR_OK ;
	int		i ;
	int		oflags ;
	int		prlen = 0 ;
	int		fd = -1 ;
	cchar		*varpruux = VARPRUUX ;
	char		progfname[MAXPATHLEN + 1] ;
	cchar	*pn = PROG_UUX ;
	cchar	**av ;
	cchar	**ev ;

	if (pr == nullptr) return SR_FAULT ;
	if (node == nullptr) return SR_FAULT ;
	if (svc == nullptr) return SR_FAULT ;
	if (pr[0] == '\0') return SR_INVALID ;
	if (svc[0] == '\0') return SR_INVALID ;

#if	CF_DEBUG
	DEBUGPRINTF("dialuux: pr=%s\n",pr) ;
	DEBUGPRINTF("dialuux: node=%s\n",node) ;
	DEBUGPRINTF("dialuux: svc=%s\n",svc) ;
#endif

/* check node */

	rs = havenode(pr,node) ;

#if	CF_DEBUG
	DEBUGPRINTF("dialuux: havenode() rs=%d\n",rs) ;
#endif

	if (rs < 0)
	    goto ret0 ;

/* initialize */

	rs = vecstr_start(&envs,10,0) ;
	if (rs < 0)
	    goto ret0 ;

/* search for the program (executable file) */

#if	CF_GETPROGROOT
	rs = getprogroot(progfname,pr,prnames,pn) ;

#if	CF_DEBUG
	DEBUGPRINTF("getprogroot() rs=%d pr=%t\n",
		rs,progfname,prlen) ;
#endif

	if (rs == 0)
	    rs = mkpath1(progfname,pn) ;

#ifdef	COMMENT
	if ((rs >= 0) && (prlen > 0)) {
	    rs = vecstr_envadd(&envs,varpruux,progfname,prlen) ;
	} else if (rs >= 0)
	    rs = vecstr_envadd(&envs,varpruux,op->pr,-1) ;
#endif /* COMMENT */

#else /* CF_GETPROGROOT */
	rs = prgetprogpath(pr,progfname,pn,-1) ;
	if (rs == 0)
	    rs = mkpath1(progfname,pn) ;
#endif /* CF_GETPROGROOT */

	if (rs < 0)
	    goto ret1 ;

/* set default environment variables */

#if	CF_DEBUG
	DEBUGPRINTF("dialuux: defenvs\n") ;
#endif

	if (rs >= 0)
	    rs = procenvpaths(pr,&envs) ;

	if (rs >= 0)
	    rs = vecstr_envadd(&envs,varpruux,pr,-1) ;

	if (rs >= 0)
	    rs = vecstr_defenvs(&envs,prnames) ;

	if (rs >= 0)
	    rs = vecstr_defenvs(&envs,envdefs) ;

/* build the program arguments */

#if	CF_DEBUG
	DEBUGPRINTF("dialuux: program arguments \n") ;
#endif

	if (rs >= 0)
	    rs = vecstr_start(&args,10,0) ;

#if	CF_DEBUG
	DEBUGPRINTF("dialuux: vecstr_start(&args) rs=%d\n",rs) ;
#endif

	if (rs < 0)
	    goto ret1 ;

	if (rs >= 0)
	    rs = vecstr_add(&args,pn,-1) ;

/* set some program options */

	if (rs >= 0) {
	    rs = vecstr_add(&args,"-p",2) ;
	}
	if ((rs >= 0) && (opts & DIALUUX_OQUEUE)) {
	    rs = vecstr_add(&args,"-r",2) ;
	}
	if ((rs >= 0) && (opts & DIALUUX_ONOREPORT)) {
	    rs = vecstr_add(&args,"-n",2) ;
	}
	if ((rs >= 0) && (u != nullptr) && (u[0] != '\0')) {
	    rs = vecstr_add(&args,"-a",2) ;
	    if (rs >= 0) {
	        rs = vecstr_add(&args,u,-1) ;
	    }
	}
	if ((rs >= 0) && (g != nullptr) && (g[0] != '\0')) {
	    rs = vecstr_add(&args,"-g",2) ;
	    if (rs >= 0) {
	        rs = vecstr_add(&args,g,-1) ;
	    }
	}
	/* load up the node and service (as they are available) */
	if (rs >= 0) {
	    char	buf[BUFLEN + 1] ;
	    rs = mknodesvc(buf,BUFLEN,node,svc) ;
	    if (rs >= 0) {
	        rs = vecstr_add(&args,buf,rs) ;
	    }
	} /* end if */
	/* load up any supplied arguments */
	if ((rs >= 0) && (argv != nullptr)) {
	    for (i = 0 ; argv[i] != nullptr ; i += 1) {
	        rs = vecstr_add(&args,argv[i],-1) ;
	        if (rs < 0) break ;
	    } /* end for */
	} /* end if */

	if (rs < 0)
	    goto ret2 ;

/* execute */

#if	CF_DEBUG
	DEBUGPRINTF("dialuux: execute progfname=%s\n",progfname) ;
#endif

	vecstr_getvec(&args,&av) ;
	vecstr_getvec(&envs,&ev) ;
	oflags = O_WRONLY ;
	rs = uc_openprog(progfname,oflags,av,ev) ;
	fd = rs ;

ret2:
	vecstr_finish(&args) ;

ret1:
	vecstr_finish(&envs) ;

ret0:

#if	CF_DEBUG
	DEBUGPRINTF("dialuux: ret rs=%d fd=%u\n",rs,fd) ;
#endif

	return (rs >= 0) ? fd : rs ;
} /* end subroutine (dialuux) */


/* local subroutines */

local int vecstr_defenvs(vecstr *elp,mainv ea) noex {
	int		rs = SR_OK ;
	int		c = 0 ;
	for (int i = 0 ; ea[i] ; i += 1) {
	    if (cchar *cp = getenver(ea[i]) ; cp) {
		c += 1 ;
		rs = vecstr_envadd(elp,ea[i],cp,-1) ;
	    }
	    if (rs < 0) break ;
	} /* end for */
	return (rs >= 0) ? c : rs ;
} /* end subroutine (vecstr_defenvs) */

local int vecstr_loadpath(vecstr *clp,cchar *pp) noex {
    	cnullptr	np{} ;
	int		rs = SR_OK ;
	int		rs1 ;
	int		cl ;
	int		c = 0 ;
	cchar	*cp ;
	char		tmpfname[MAXPATHLEN + 1] ;

	while ((cp = strbrk(pp,":;")) != np) {
	    cl = pathclean(tmpfname,pp,(cp - pp)) ;

	    rs1 = vecstr_findn(clp,tmpfname,cl) ;
	    if (rs1 == SR_NOTFOUND) {
	        c += 1 ;
		rs = vecstr_add(clp,tmpfname,cl) ;
	    }

	    if ((rs >= 0) && (cp[0] == ';')) {
		rs = vecstr_adduniq(clp,";",1) ;
	    }

	    pp = (cp + 1) ;
	    if (rs < 0) break ;
	} /* end while */

	if ((rs >= 0) && (pp[0] != '\0')) {

	    cl = pathclean(tmpfname,pp,-1) ;

	    rs1 = vecstr_findn(clp,tmpfname,cl) ;
	    if (rs1 == SR_NOTFOUND) {
	        c += 1 ;
	        rs = vecstr_add(clp,tmpfname,cl) ;
	    }

	} /* end if (trailing one) */

	return (rs >= 0) ? c : rs ;
} /* end subroutine (vecstr_loadpath) */

local int mkpathval(vecstr *clp,char *vbuf,int vbuflen) noex {
	int		rs = SR_OK ;
	int		i ;
	int		sch ;
	int		c = 0 ;
	int		rlen = 0 ;
	int		f_semi = false ;
	cchar	*cp ;

	if (vbuflen < 0) {
	    rs = SR_NOANODE ;
	    goto ret0 ;
	}

	vbuf[0] = '\0' ;
	for (i = 0 ; vecstr_get(clp,i,&cp) >= 0 ; i += 1) {
	    if (cp == nullptr) continue ;
	    if (cp[0] != ';') {
	        if (c++ > 0) {
	            if (f_semi) {
	                f_semi = false ;
	                sch = ';' ;
	            } else {
	                sch = ':' ;
		    }
	            rs = storebuf_chr(vbuf,vbuflen,rlen,sch) ;
	            rlen += rs ;
	        } /* end if */

	        if (rs >= 0) {
	            rs = storebuf_strw(vbuf,vbuflen,rlen,cp,-1) ;
	            rlen += rs ;
	        }
	    } else {
	        f_semi = true ;
	    }
	    if (rs < 0) break ;
	} /* end for */

ret0:
	return (rs >= 0) ? rlen : rs ;
} /* end subroutine (mkpathval) */

local int procenvpaths(cchar *pr,vecstr *elp) noex {
	vecstr	pathcomps ;
	int	rs = SR_OK ;
	int	i ;
	int	opts ;
	int	sz ;
	int	bl, pl ;

	cchar	*subdname ;
	cchar	*nap ;
	cchar	*vap ;

	char	pathbuf[MAXPATHLEN + 1] ;
	char	*bp = nullptr ;


	opts = VECSTR_OORDERED ;
	if ((rs = vecstr_start(&pathcomps,40,opts)) >= 0) {

	for (i = 0 ; envpops[i].name != nullptr ; i += 1) {
	    nap = envpops[i].name ;

	    subdname = envpops[i].sub1dname ;
	    if ((rs >= 0) && (subdname != nullptr)) {
	        if ((rs = mkpath2(pathbuf,pr,subdname)) >= 0) {
	            pl = rs ;
	            rs = vecstr_add(&pathcomps,pathbuf,pl) ;
		}
	    } /* end if */

	    subdname = envpops[i].sub2dname ;
	    if ((rs >= 0) && (subdname != nullptr)) {
	        if ((rs = mkpath2(pathbuf,pr,subdname)) >= 0) {
	            pl = rs ;
	            rs = vecstr_add(&pathcomps,pathbuf,pl) ;
		}
	    } /* end if */

	    if ((rs >= 0) && ((vp = getenv(nap)) != nullptr)) {
	        rs = vecstr_loadpath(&pathcomps,vp) ;
	    }

	    if (rs >= 0) {
	        sz = vecstr_strsize(&pathcomps) ;
	    }

	    if ((rs >= 0) && ((rs = uc_malloc(sz,&bp)) >= 0)) {
	        if ((rs = mkpathval(&pathcomps,bp,(sz-1))) >= 0) {
	            bl = rs ;
	            rs = vecstr_envadd(elp,nap,bp,bl) ;
		}
	        uc_free(bp) ;
	    } /* end if (memory allocation) */
	    vecstr_delall(&pathcomps) ;
	    if (rs < 0) break ;
	} /* end for */
	vecstr_finish(&pathcomps) ;
	} /* end uf (vecstr) */
	return rs ;
} /* end subroutine (procenvpaths) */

local int mknodesvc(char *rbuf,int rlen,cchar *node,cchar *svc) noex {
	int		rs = SR_OK ;
	int		i = 0 ;
	if (node[0] != '\0') {
	    rs = storebuf_strw(rbuf,rlen,i,node,-1) ;
	    i += rs ;
	}
	if (rs >= 0) {
	    rs = storebuf_chr(rbuf,rlen,i,'!') ;
	    i += rs ;
	}
	if (rs >= 0) {
	    rs = storebuf_strw(rbuf,rlen,i,svc,-1) ;
	    i += rs ;
	}
	return (rs >= 0) ? i : rs ;
} /* end subroutine (mknodesvc) */

local int havenode(cchar *pr,cchar *node) noex {
	int		rs = SR_OK ;
	int		rs1 ;
#if	CF_DEBUG
	DEBUGPRINTF("dialuux/havenode: pr=%s\n",pr) ;
	DEBUGPRINTF("dialuux/havenode: node=%s\n",node) ;
	if (node[0]) {
	    if (uuname un ; (rs = uuname_open(&un,pr,"")) >= 0) {
		{
	        rs = uuname_exists(&un,node,-1) ;
		}
		rs1 = uuname_close(&un) ;
		if (rs >= 0) rs = rs1 ;
	    } /* end if (uuname) */
	} /* end if */
	return rs ;
} /* end subroutine (havenode) */


