/* dialuux SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 */

/* perform remote UUX service execution */
/* version %I% last-modified %G% */

#define	CF_DEBUGS	0		/* compile-time debugging */
#define	CF_GETPROGROOT	1		/* use 'getprogroot(3dam)' */

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
#include	<sys/param.h>
#include	<sys/stat.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<usystem.h>
#include	<getpwd.h>
#include	<vecstr.h>
#include	<storebuf.h>
#include	<sncpyx.h>
#include	<strn.h>
#include	<strw.h>
#include	<mkpathx.h>
#include	<pathclean.h>
#include	<matxstr.h>
#include	<uuname.h>
#include	<localmisc.h>

#include	"dialuux.h"


/* local defines */

#ifndef	DEFINITFNAME
#define	DEFINITFNAME	"/etc/default/init"
#endif

#ifndef	DEFLOGFNAME
#define	DEFLOGFNAME	"/etc/default/login"
#endif

#ifndef	nullptrFNAME
#define	nullptrFNAME	"/dev/null"
#endif

#ifndef	VARUSERNAME
#define	VARUSERNAME	"USERNAME"
#endif

#ifndef	VARHOME
#define	VARHOME		"HOME"
#endif

#ifndef	VARPWD
#define	VARPWD		"PWD"
#endif

#ifndef	VARMAIL
#define	VARMAIL		"MAIL"
#endif

#ifndef	VARPATH
#define	VARPATH		"PATH"
#endif

#ifndef	VARLIBPATH
#define	VARLIBPATH	"LD_LIBRARY_PATH"
#endif

#ifndef	VARMANPATH
#define	VARMANPATH	"MANPATH"
#endif

#ifndef	VARPRLOCAL
#define	VARPRLOCAL	"LOCAL"
#endif

#ifndef	VARPRNCMP
#define	VARPRNCMP	"NCMP"
#endif

#ifndef	VARDISPLAY
#define	VARDISPLAY	"DISPLAY"
#endif

#ifndef	VARPRUUX
#define	VARPRUUX	"UUX_PROGRAMROOT"
#endif

#define	BUFLEN		MAXPATHLEN

#define	PROG_UUX	"uux"

#define	NENVS		120


/* external subroutines */

extern int	strkeycmp(cchar *,cchar *) noex ;
extern int	vstrkeycmp(cvoid **,cvoid **) noex ;
extern int	prgetprogpath(cchar *,char *,cchar *,int) noex ;
extern int	getprogroot(cchar *,cchar **,int *,char *,cchar *) noex ;

#if	CF_DEBUGS
extern int	debugprintf(cchar *,...) noex ;
#endif


/* external variables */


/* local structures */

struct envpop {
	cchar	*name ;
	cchar	*sub1dname ;
	cchar	*sub2dname ;
} ;


/* forward reference */

static int	vecstr_defenvs(vecstr *,cchar **) noex ;
static int	vecstr_loadpath(vecstr *,cchar *) noex ;
static int	mkpathval(vecstr *,char *,int) noex ;

static int	procenvpaths(cchar *,vecstr *) noex ;
static int	mknodesvc(char *,int,cchar *,cchar *) noex ;
static int	havenode(cchar *,cchar *) noex ;


/* local variables */

constexpr cpcchar	prnames[] = {
	"LOCAL",
	"NCMP",
	"EXTRA",
	"PCS",
	nullptr
} ;

constexpr cpcchar	envdefs[] = {
	"PATH",
	"LD_LIBRARY_PATH",
	"MAIL",
	"MAILDIR",
	nullptr
} ;

constexpr envpop	envpops[] = {
	{ VARPATH, "bin", "sbin" },
	{ VARLIBPATH, "lib", nullptr },
	{ VARMANPATH, "man", nullptr },
	{ nullptr, nullptr, nullptr }
} ;


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
	cchar	*varpruux = VARPRUUX ;
	char		progfname[MAXPATHLEN + 1] ;
	cchar	*pn = PROG_UUX ;
	cchar	**av ;
	cchar	**ev ;

	if (pr == nullptr) return SR_FAULT ;
	if (node == nullptr) return SR_FAULT ;
	if (svc == nullptr) return SR_FAULT ;
	if (pr[0] == '\0') return SR_INVALID ;
	if (svc[0] == '\0') return SR_INVALID ;

#if	CF_DEBUGS
	debugprintf("dialuux: pr=%s\n",pr) ;
	debugprintf("dialuux: node=%s\n",node) ;
	debugprintf("dialuux: svc=%s\n",svc) ;
#endif

/* check node */

	rs = havenode(pr,node) ;

#if	CF_DEBUGS
	debugprintf("dialuux: havenode() rs=%d\n",rs) ;
#endif

	if (rs < 0)
	    goto ret0 ;

/* initialize */

	rs = vecstr_start(&envs,10,0) ;
	if (rs < 0)
	    goto ret0 ;

/* search for the program (executable file) */

#if	CF_GETPROGROOT
	rs = getprogroot(pr,prnames,&prlen,progfname,pn) ;

#if	CF_DEBUGS
	debugprintf("dialuux: getprogroot() rs=%d prlen=%u pr=%t\n",
		rs,prlen,progfname,prlen) ;
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

#if	CF_DEBUGS
	debugprintf("dialuux: defenvs\n") ;
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

#if	CF_DEBUGS
	debugprintf("dialuux: program arguments \n") ;
#endif

	if (rs >= 0)
	    rs = vecstr_start(&args,10,0) ;

#if	CF_DEBUGS
	debugprintf("dialuux: vecstr_start(&args) rs=%d\n",rs) ;
#endif

	if (rs < 0)
	    goto ret1 ;

	if (rs >= 0)
	    rs = vecstr_add(&args,pn,-1) ;

/* set some program options */

	if (rs >= 0)
	    rs = vecstr_add(&args,"-p",2) ;

	if ((rs >= 0) && (opts & DIALUUX_OQUEUE))
	    rs = vecstr_add(&args,"-r",2) ;

	if ((rs >= 0) && (opts & DIALUUX_ONOREPORT))
	    rs = vecstr_add(&args,"-n",2) ;

	if ((rs >= 0) && (u != nullptr) && (u[0] != '\0')) {
	    rs = vecstr_add(&args,"-a",2) ;
	    if (rs >= 0)
	        rs = vecstr_add(&args,u,-1) ;
	}

	if ((rs >= 0) && (g != nullptr) && (g[0] != '\0')) {
	    rs = vecstr_add(&args,"-g",2) ;
	    if (rs >= 0)
	        rs = vecstr_add(&args,g,-1) ;
	}

/* load up the node and service (as they are available) */

	if (rs >= 0) {
	    char	buf[BUFLEN + 1] ;

	    rs = mknodesvc(buf,BUFLEN,node,svc) ;

	    if (rs >= 0)
	        rs = vecstr_add(&args,buf,rs) ;

	} /* end if */

/* load up any supplied arguments */

	if ((rs >= 0) && (argv != nullptr)) {
	    for (i = 0 ; argv[i] != nullptr ; i += 1) {
	        rs = vecstr_add(&args,argv[i],-1) ;
	        if (rs < 0) break ;
	    }
	}

	if (rs < 0)
	    goto ret2 ;

/* execute */

#if	CF_DEBUGS
	debugprintf("dialuux: execute progfname=%s\n",progfname) ;
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

#if	CF_DEBUGS
	debugprintf("dialuux: ret rs=%d fd=%u\n",rs,fd) ;
#endif

	return (rs >= 0) ? fd : rs ;
}
/* end subroutine (dialuux) */


/* local subroutines */

static int vecstr_defenvs(vecstr *elp,mainv ea) noex {
	int		rs = SR_OK ;
	int		c = 0 ;
	cchar		*cp ;

	for (int i = 0 ; ea[i] != nullptr ; i += 1) {
	    if ((cp = getenv(ea[i])) != nullptr)
		rs = vecstr_envadd(elp,ea[i],cp,-1) ;
	    if (rs < 0) break ;
	} /* end for */

	return (rs >= 0) ? c : rs ;
}
/* end subroutine (vecstr_defenvs) */

static int vecstr_loadpath(vecstr *clp,cchar *pp) noex {
	int		rs = SR_OK ;
	int		rs1 ;
	int		cl ;
	int		c = 0 ;
	cchar	*cp ;
	char		tmpfname[MAXPATHLEN + 1] ;

	while ((cp = strpbrk(pp,":;")) != nullptr) {

	    cl = pathclean(tmpfname,pp,(cp - pp)) ;

	    rs1 = vecstr_findn(clp,tmpfname,cl) ;
	    if (rs1 == SR_NOTFOUND) {
	        c += 1 ;
		rs = vecstr_add(clp,tmpfname,cl) ;
	    }

	    if ((rs >= 0) && (cp[0] == ';'))
		rs = vecstr_adduniq(clp,";",1) ;

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
}
/* end subroutine (vecstr_loadpath) */

static int mkpathval(vecstr *clp,char *vbuf,int vbuflen) noex {
	int		rs = SR_OK ;
	int		i ;
	int		sch ;
	int		c = 0 ;
	int		rlen = 0 ;
	int		f_semi = FALSE ;
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
	                f_semi = FALSE ;
	                sch = ';' ;
	            } else
	                sch = ':' ;

	            rs = storebuf_chr(vbuf,vbuflen,rlen,sch) ;
	            rlen += rs ;

	        } /* end if */

	        if (rs >= 0) {
	            rs = storebuf_strw(vbuf,vbuflen,rlen,cp,-1) ;
	            rlen += rs ;
	        }

	    } else
	        f_semi = TRUE ;

	    if (rs < 0) break ;
	} /* end for */

ret0:
	return (rs >= 0) ? rlen : rs ;
}
/* end subroutine (mkpathval) */

static int procenvpaths(cchar *pr,vecstr *elp) noex {
	vecstr	pathcomps ;
	int	rs = SR_OK ;
	int	i ;
	int	opts ;
	int	size ;
	int	bl, pl ;

	cchar	*subdname ;
	cchar	*np ;
	cchar	*vp ;

	char	pathbuf[MAXPATHLEN + 1] ;
	char	*bp = nullptr ;


	opts = VECSTR_OORDERED ;
	if ((rs = vecstr_start(&pathcomps,40,opts)) >= 0) {

	for (i = 0 ; envpops[i].name != nullptr ; i += 1) {
	    np = envpops[i].name ;

	    subdname = envpops[i].sub1dname ;
	    if ((rs >= 0) && (subdname != nullptr)) {

	        rs = mkpath2(pathbuf,pr,subdname) ;
	        pl = rs ;
	        if (rs >= 0)
	            rs = vecstr_add(&pathcomps,pathbuf,pl) ;

	    } /* end if */

	    subdname = envpops[i].sub2dname ;
	    if ((rs >= 0) && (subdname != nullptr)) {

	        rs = mkpath2(pathbuf,pr,subdname) ;
	        pl = rs ;
	        if (rs >= 0)
	            rs = vecstr_add(&pathcomps,pathbuf,pl) ;

	    } /* end if */

	    if ((rs >= 0) && ((vp = getenv(np)) != nullptr)) {
	        rs = vecstr_loadpath(&pathcomps,vp) ;
	    }

	    if (rs >= 0) {
	        size = vecstr_strsize(&pathcomps) ;
	    }

	    if ((rs >= 0) && ((rs = uc_malloc(size,&bp)) >= 0)) {

	        rs = mkpathval(&pathcomps,bp,(size-1)) ;
	        bl = rs ;
	        if (rs >= 0)
	            rs = vecstr_envadd(elp,np,bp,bl) ;

	        uc_free(bp) ;
	    } /* end if (memory allocation) */

	    vecstr_delall(&pathcomps) ;

	    if (rs < 0) break ;
	} /* end for */

	vecstr_finish(&pathcomps) ;
	} /* end uf (vecstr) */

	return rs ;
}
/* end subroutine (procenvpaths) */

static int mknodesvc(char *buf,int buflen,cchar *node,cchar *svc) noex {
	int		rs = SR_OK ;
	int		i = 0 ;
	if (node[0] != '\0') {
	    rs = storebuf_strw(buf,buflen,i,node,-1) ;
	    i += rs ;
	}
	if (rs >= 0) {
	    rs = storebuf_chr(buf,buflen,i,'!') ;
	    i += rs ;
	}
	if (rs >= 0) {
	    rs = storebuf_strw(buf,buflen,i,svc,-1) ;
	    i += rs ;
	}
	return (rs >= 0) ? i : rs ;
}
/* end subroutine (mknodesvc) */

static int havenode(cchar *pr,cchar *node) noex {
	UUNAME		un ;
	int		rs = SR_OK ;

#if	CF_DEBUGS
	debugprintf("dialuux/havenode: pr=%s\n",pr) ;
	debugprintf("dialuux/havenode: node=%s\n",node) ;
#endif

	if (node[0] != '\0') {
	    if ((rs = uuname_open(&un,pr,"")) >= 0) {
	        rs = uuname_exists(&un,node,-1) ;
	        uuname_close(&un) ;
	    } /* end if (uuname) */
	} /* end if */

	return rs ;
}
/* end subroutine (havenode) */


