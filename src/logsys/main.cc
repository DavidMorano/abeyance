/* main SUPPORT (liblkcmd) */
/* lang=C++20 */

/* generic front-end for SHELL built-ins */
/* version %I% last-modified %G% */

#define	CF_UTIL		0		/* run the utility worker */

/* revision history:

	= 2001-11-01, David A­D­ Morano
	This subroutine was written for use as a front-end for Korn
	Shell (KSH) commands that are compiled as stand-alone
	programs.

*/

/* Copyright © 2001 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This is the front-end to make the various SHELL (KSH)
	built-in commands into stand-alone programs.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<unistd.h>
#include	<ucontext.h>
#include	<dlfcn.h>
#include	<climits>
#include	<csignal>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<usystem.h>
#include	<intceil.h>
#include	<sighand.h>
#include	<mapex.h>
#include	<exitcodes.h>
#include	<localmisc.h>

#include	"kshlib.h"
#include	"maininfo.h"


/* local defines */

#if	defined(KSHBUILTIN) && (KSHBUILTIN > 0)
#define	CF_LOCKMEMALLOC		0	/* formerly =1 */
#else
#define	CF_LOCKMEMALLOC		0
#endif

#define	SIGCODE		struct sigcode

#define	NDF		"main.deb"


/* imported namespaces */


/* local typedefs */


/* external subroutines */

extern int	snwcpy(char *,int,cchar *,int) ;
extern int	sncpy2(char *,int,cchar *,cchar *) ;
extern int	sncpy2w(char *,int,cchar *,cchar *,int) ;
extern int	sncpylc(char *,int,cchar *) ;
extern int	sncpyuc(char *,int,cchar *) ;
extern int	sfbasename(cchar *,int,cchar **) ;
extern int	ucontext_rtn(ucontext_t *,long *) ;
extern int	bufprintf(char *,int,cchar *,...) ;
extern int	msleep(int) ;
extern int	haslc(cchar *,int) ;
extern int	hasuc(cchar *,int) ;

extern cchar	*getourenv(cchar **,cchar *) ;
extern cchar	*strsigabbr(int) ;


/* external variables */


/* local structures */

struct sigcode {
	int	code ;
	cchar	*name ;
} ;


/* forward references */

static void	main_sighand(int,siginfo_t *,void *) ;
static int	main_sigdump(siginfo_t *) ;

static cchar	*strsigcode(const SIGCODE *,int) ;


/* local variables */

static const MAPEX	mapexs[] = {
	{ SR_NOENT, EX_NOUSER },
	{ SR_AGAIN, EX_TEMPFAIL },
	{ SR_DEADLK, EX_TEMPFAIL },
	{ SR_NOLCK, EX_TEMPFAIL },
	{ SR_TXTBSY, EX_TEMPFAIL },
	{ SR_ACCESS, EX_NOPERM },
	{ SR_REMOTE, EX_PROTOCOL },
	{ SR_NOSPC, EX_TEMPFAIL },
	{ SR_INTR, EX_INTR },
	{ SR_EXIT, EX_TERM },
	{ SR_DOM, EX_NOPROG },
	{ 0, 0 }
} ;

static cint	sigcatches[] = {
	SIGILL, 
	SIGSEGV,
	SIGBUS,
	SIGQUIT,
	SIGABRT,
	0
} ;

static const SIGCODE	sigcode_ill[] = {
	{ ILL_ILLOPC, "ILLOPC" },
	{ ILL_ILLOPN, "ILLOPN" },
	{ ILL_ILLADR, "ILLADR" },
	{ ILL_ILLTRP, "ILLTRP" },
	{ ILL_PRVOPC, "PRBOPC" },
	{ ILL_PRVREG, "PRVREG" },
	{ ILL_COPROC, "COPROC" },
	{ ILL_BADSTK, "BADSTK" },
	{ 0, nullptr }
} ;

static const SIGCODE	sigcode_segv[] = {
	{ SEGV_MAPERR, "MAPERR" },
	{ SEGV_ACCERR, "ACCERR" },
	{ 0, nullptr }
} ;

static const SIGCODE	sigcode_bus[] = {
	{ BUS_ADRALN, "ADRALN" },
	{ BUS_ADRERR, "ADRERR" },
	{ BUS_OBJERR, "OBJERR" },
	{ 0, nullptr }
} ;


/* exported variables */


/* exported subroutines */

int main(int argc,mainv argv,mainv envv) {
	cint	f_lockmemalloc = CF_LOCKMEMALLOC ;
	cint	f_util = CF_UTIL ;
	int		rs = SR_OK ;
	int		rs1 ;
	int		ex = EX_INFO ;

	if (argv != nullptr) {
	    MAININFO	mi, *mip = &mi ;
	    if ((rs = maininfo_start(mip,argc,argv)) >= 0) {
		maininfohand_t	sh = main_sighand ;
	        if ((rs = maininfo_sigbegin(mip,sh,sigcatches)) >= 0) {
	            if ((rs = lib_initmemalloc(f_lockmemalloc)) >= 0) {
	                if ((rs = lib_mainbegin(envv,nullptr)) >= 0) {
	                    if ((rs = maininfo_utilbegin(mip,f_util)) >= 0) {
	                        cchar	*srch ;

	                        if ((rs = maininfo_srchname(mip,&srch)) >= 0) {
	                            ex = lib_callcmd(srch,argc,argv,envv,nullptr) ;
	                        } /* end if */

	                        rs1 = maininfo_utilend(mip) ;
	                        if (rs >= 0) rs = rs1 ;
	                    } /* end if (maininfo-util) */
	                    rs1 = lib_mainend() ;
	                    if (rs >= 0) rs = rs1 ;
	                } /* end if (lib-main) */
	            } /* end if (lib_initmemalloc) */
	            rs1 = maininfo_sigend(&mi) ;
	            if (rs >= 0) rs = rs1 ;
	        } /* end if (maininfo-sig) */
	        rs1 = maininfo_finish(mip) ;
	        if (rs >= 0) rs = rs1 ;
	    } else {
	        ex = EX_OSERR ;
	    }
	} else {
	    ex = EX_OSERR ;
	}

	if ((rs < 0) && (ex == EX_OK)) {
	    ex = mapex(mapexs,rs) ;
	}

	return ex ;
}
/* end subroutine (main) */


/* local subroutines */

/* ARGSUSED */
static void main_sighand(int sn,siginfo_t *sip,void *vcp) noex {
	if (vcp != nullptr) {
	    Dl_info	dl ;
	    long	ra ;
	    ucontext_t	*ucp = (ucontext_t *) vcp ;
	    void	*rtn ;
	    cint	wlen = LINEBUFLEN ;
	    int		wl ;
	    cchar	*fmt ;
	    char	wbuf[LINEBUFLEN+1] ;
	    ucontext_rtn(ucp,&ra) ;
	    if (ra != 0) {
	        rtn = (void *) ra ;
	        dladdr(rtn,&dl) ;
	        fmt = "rtn=%08lX fn=%s sym=%s\n" ;
	        wl = bufprintf(wbuf,wlen,fmt,ra,dl.dli_fname,dl.dli_sname) ;
	        write(2,wbuf,wl) ;
	    }
	}

	if (sip != nullptr) {
	    main_sigdump(sip) ;
	}
	u_exit(EX_TERM) ;
}
/* end subroutine (main_sighand) */

static int main_sigdump(siginfo_t *sip) noex {
	cint	wlen = LINEBUFLEN ;
	cint	si_signo = sip->si_signo ;
	cint	si_code = sip->si_code ;
	int		wl ;
	cchar	*sn = strsigabbr(sip->si_signo) ;
	cchar	*as = "*na*" ;
	cchar	*scs = nullptr ;
	cchar	*fmt ;
	char		wbuf[LINEBUFLEN+1] ;
	char		abuf[16+1] ;
	switch (si_signo) {
	case SIGILL:
	    scs = strsigcode(sigcode_ill,si_code) ;
	    break ;
	case SIGSEGV:
	    scs = strsigcode(sigcode_segv,si_code) ;
	    bufprintf(abuf,16,"%p",sip->si_addr) ;
	    as = abuf ;
	    break ;
	case SIGBUS:
	    scs = strsigcode(sigcode_bus,si_code) ;
	    bufprintf(abuf,16,"%p",sip->si_addr) ;
	    as = abuf ;
	    break ;
	case SIGQUIT:
	    scs = "¤na¤" ;
	    break ;
	default:
	    scs = "¤default¤" ;
	    break ;
	} /* end switch */
	fmt = "SIG=%s code=%d(%s) addr=%s\n" ;
	wl = bufprintf(wbuf,wlen,fmt,sn,si_code,scs,as) ;
	write(2,wbuf,wl) ;
	return 0 ;
}
/* end subroutine (main_sigdump) */

static cchar *strsigcode(const SIGCODE *scp,int code) noex {
	int		i ;
	bool		f = false ;
	cchar		*sn = "UNKNOWN" ;
	for (i = 0 ; scp[i].code != 0 ; i += 1) {
	    f = (scp[i].code == code) ;
	    if (f) break ;
	}
	if (f) sn = scp[i].name ;
	return sn ;
}
/* end subroutine (strsigcode) */


