/* sysmiscs SUPPORT */
/* lang=C++20 */

/* return SYSMISC information from the system */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This subroutine will find and return the number of CPUs in
	the present system.

	Synopsis:
	int sysmiscs(cchar *pr) noex

	Arguments:
	pr		program root

	Returns:

	>0		OK and this is the number of CPUs in the system
	==0		could not determine the number of CPUs
	<0		error code (system-return)

*******************************************************************************/

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/param.h>
#include	<sys/stat.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<ctime>
#include	<climits>
#include	<cstdlib>
#include	<cstring>
#include	<usystem.h>
#include	<vecobj.h>
#include	<msfile.h>
#include	<spawnproc.h>
#include	<hash.h>
#include	<localmisc.h>


/* local defines */

#ifndef	KEYBUFLEN
#define	KEYBUFLEN	120
#endif

#define	TO_OLDFILE	(5 * 60)
#define	TO_MSOLD	10

#define	MSVARDNAME	"var"
#define	MSFNAME		"ms"
#define	MSBINDNAME	"bin"

#define	DEBFNAME	"sysvar.deb"


/* external subroutines */

extern int	sncpy2(char *,int,cchar *,cchar *) ;
extern int	sncpy3(char *,int,cchar *,cchar *,cchar *) ;
extern int	sncpy4(char *,int,cchar *,cchar *,cchar *,
			cchar *) ;
extern int	sncpy5(char *,int,cchar *,cchar *,cchar *,
			cchar *,cchar *) ;
extern int	sncpy6(char *,int,cchar *,cchar *,cchar *,
			cchar *,cchar *,cchar *) ;
extern int	snwcpy(char *,int,cchar *,int) ;
extern int	mkpath1(char *,cchar *) ;
extern int	mkpath2(char *,cchar *,cchar *) ;
extern int	mkpath3(char *,cchar *,cchar *,cchar *) ;
extern int	mkpath1w(char *,cchar *,int) ;
extern int	sfbasename(cchar *,int,cchar **) ;
extern int	sfdirname(cchar *,int,cchar **) ;
extern int	sfshrink(cchar *,int,cchar **) ;
extern int	sfword(cchar *,int,cchar **) ;
extern int	strnnlen(cchar *,int,int) ;
extern int	cfdeci(cchar *,int,int *) ;
extern int	cfdecui(cchar *,int,uint *) ;
extern int	cfhexi(cchar *,int,uint *) ;
extern int	getnodename(char *,int) ;
extern int	getpwd(char *,int) ;
extern int	perm(cchar *,uid_t,gid_t,gid_t *,int) ;
extern int	hasuc(cchar *,int) ;
extern int	vstrkeycmp(cchar *,cchar *) ;

#if	CF_DEBUGS
extern int	debugprintf(cchar *,...) ;
#endif

extern char	*strwcpy(char *,cchar *,int) ;
extern char	*strwcpylc(char *,cchar *,int) ;
extern char	*strnchr(cchar *,int,int) ;
extern char	*strnpbrk(cchar *,int,cchar *) ;


/* external variables */


/* exported variables */

MODLOAD_MID	sysmiscs_mod = {
	"sysmiscs",
	sizeof(sysmiscs)
} ;


/* local structures */


/* forward references */

static int	sysmiscs_msopen(sysmiscs *) ;
static int	sysmiscs_msget(sysmiscs *,time_t) ;
static int	sysmiscs_msgetone(sysmiscs *,time_t,sysmiscs_d *) ;
static int	sysmiscs_nodename(sysmiscs *) ;


/* exported variables */

SYSMISCS_OBJ	sysmiscs_mod = {
	"sysmiscs",
	sizeof(SYSMISCS)
} ;


/* local variables */

static cchar	*prbins[] = {
	"bin",
	"sbin",
	NULL
} ;


/* exported variables */

/* exported subroutines */

int sysmiscs_open(sysmiscs *op,cchar *pr) noex {
	int	rs = SR_FAULT ;
	if (op && pr) {
	    cchar	*cp ;
	    memclear(op) ;
	    if ((rs = uc_mallocstrw(pr,-1,&cp)) >= 0) {
	        op->pr = cp ;
	        op->magic = SYSMISCS_MAGIC ;
	    }
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (sysmiscs_open) */

int sysmiscs_get(susmiscs *op,time_t daytime,sysmiscs_d *dp) noex {
	int	rs = SR_OK ;
	int	n = 0 ;

	if (op == NULL)
	    return SR_FAULT ;

	if (op->magic != SYSMISCS_MAGIC)
	    return SR_NOTOPEN ;

	if (daytime == 0) daytime = time(NULL) ;

	rs = sysmiscs_msget(op,daytime,dp) ;
	n = rs ;

	return (rs >= 0) ? n : rs ;
}
/* end subroutine (sysmiscs_get) */


int sysmiscs_close(op)
SYSMISCS	*op ;
{
	int	rs = SR_OK ;
	int	rs1 ;


	if (op == NULL)
	    return SR_FAULT ;

	if (op->magic != SYSMISCS_MAGIC)
	    return SR_NOTOPEN ;


	if (op->f.msopen) {
	    op->f.msinit = FALSE ;
	    op->f.msopen = FALSE ;
	    rs1 = msinfo_close(&op->ms) ;
	    if (rs >= 0) rs = rs1 ;
	}

	if (op->nodename != NULL) {
	    uc_free(op->nodename) ;
	    op->nodename = NULL ;
	}

	if (op->pr != NULL) {
	    uc_free(op->pr) ;
	    op->pr = NULL ;
	}

	op->magic = 0 ;
	return rs ;
}
/* end subroutine (sysmiscs_close) */


/* private subroutines */


static int sysmiscs_msget(op,daytime,dp)
SYSMISCS	*op ;
time_t		daytime ;
sysmiscs_d	*dp ;
{
	int	rs = SR_OK ;
	int	nl ;
	int	n = 0 ;

	cchar	*nn ;


	if (! op->f.msinit)
	    rs = sysmiscs_msopen(op) ;

	if (rs < 0)
	    goto ret0 ;

	if (op->f.msopen) {

	    rs = sysmiscs_msgetone(op,daytime,dp) ;

	} /* end if (MS opened) */

	if (rs < 0)
	    goto ret0 ;

	if ((! op->f.msopen) || op->f.msold) {
	    rs = sysmiscs_msdaemon(op) ;
	}

ret0:
	return (rs >= 0) ? n : rs ;
}
/* end subroutine (sysmiscs_msget) */


static int sysmiscs_msopen(op)
SYSMISCS	*op ;
{
	int	rs = SR_OK ;
	int	rs1 ;
	int	oflags = O_RDONLY ;
	int	operms = 0666 ;

	char	fname[MAXPATHLEN + 1] ;


	if (op->f.msinit)
	    goto ret0 ;

	op->f.msinit = TRUE ;
	rs = mkpath3(fname,op->pr,MSVARDNAME,MSFNAME) ;
	if (rs >= 0) {
	    rs1 = msfile_open(&op->msfile,fname,oflags,operm)
	    op->f.msopen = (rs1 >= 0) ;
	}

ret0:
	return rs ;
}
/* end subroutine (sysmiscs_msopen) */


static int sysmiscs_msgetone(op,daytime,dp)
SYSMISCS	*op ;
time_t		daytime ;
sysmiscs_d	*dp ;
{
	MSFILE_ENT	e ;

	int	rs ;
	int	rs1 ;


	rs = sysmiscs_nodename(op) ;
	if (rs < 0)
	    goto ret0 ;

	nn = op->nodename ;
	nl = op->nodenamelen ;
	rs1 = msfile_match(&op->msfile,0L,nn,nl,&e) ;
	
	if (rs1 >= 0) {

	    if (daytime == 0) daytime = time(NULL) ;

	    op->f.msold = ((daytime - e.utime) >= TO_MSOLD) ;

	} else if (rs1 == SR_NOTFOUND) {
	    op->f.msold = TRUE ;
	} else
	    rs = rs1 ;

ret0:
	return rs ;
}
/* end subroutine (sysmiscs_msgetone) */


static int sysmiscs_nodename(op)
SYSMISCS	*op ;
{
	int	rs = SR_OK ;
	int	nlen ;

	char	nbuf[NODENAMELEN + 1] ;
	char	*p ;


	if (op->nodename != NULL)
	    goto ret0 ;

	rs = getnodename(nbuf,NODENAMELEN) ;
	nlen = rs ;
	if (rs >= 0) {
	    rs = uc_mallocstrw(nbuf,nlen,&p) ;
	    if (rs >= 0) {
		op->nodename = p ;
		op->nodenamelen = nlen ;
	    }
	}

ret0:
	return rs ;
}
/* end subroutine (sysmiscs_nodename) */


static int sysmiscs_msdaemon(op)
SYSMISCS	*op ;
{
	SPAWNPROC	ps ;

	pid_t	cpid ;

	int	rs = SR_OK ;
	int	i ;
	int	cstat ;
	int	cex ;

	cchar	*pn = SYSMISCS_PROG ;
	cchar	*av[3] ;
	cchar	**ev ;

	char	progfname[MAXPATHLEN + 1] ;


	rs = mkpath3(progfname,op->pr,MSBINDNAME,pn) ;
	if (rs < 0)
	    goto ret0 ;

	av[0] = pn ;
	av[1] = "-o" ;
	av[2] = "quick" ;
	av[3] = "-d" ;

	vecstr_getvec(&envs,(cchar ***) &ev) ;

	memset(&ps,0,sizeof(SPAWNPROC)) ;

	for (i = 0 ; i < 3 ; i += 1) {
	    ps.disp[i] = (i != 2) ? SPAWNPROC_DCLOSE : SPAWNPROC_DINHERIT ;
	}

	rs = spawnproc(&ps,progfname,av,ev) ;
	cpid = rs ;

ret2:
	vecstr_free(&envs) ;

ret1:
	if (rs < 0)
	    goto ret0 ;

	cstat = 0 ;
	rs = 0 ;
	while (rs == 0) {
	    rs = u_waitpid(cpid,&cstat,0) ;
	    if (rs == SR_INTR) rs = 0 ;
	} /* end while */

	if (rs >= 0) {

	    cex = 0 ;
	    if (WIFSIGNALED(cstat))
	        rs = SR_UNATCH ;	/* protocol not attached */

#if	CF_DEBUGS
	        debugprintf("bibleqs_mkbibleqsi: signaled? rs=%d\n",rs) ;
#endif

	    if ((rs >= 0) && WIFEXITED(cstat)) {

	        cex = WEXITSTATUS(cstat) ;

	        if (cex != 0)
	            rs = SR_LIBBAD ;

#if	CF_DEBUGS
	        debugprintf("bibleqs_mkbibleqsi: exited? cex=%d rs=%d\n",
			cex,rs) ;
#endif

	    }

	} /* end if (process finished) */

ret0:
	return rs ;
}
/* end subroutine (sysmiscs_msdaemon) */


