/* uopen SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* translation layer interface for UNIX® equivalents */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services
	(RNS).

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Names:
	u_open
	u_openat
	u_socket
	u_accept
	u_acceptpass
	u_dup
	u_dupmin
	u_dupminer
	u_dup2
	u_socketpair
	u_pipe
	u_pipe2
	u_piper


	Name:
	u_open

	Description:
	**left as exercise for the reader**

	Note:
	Every OS has its own problems (sometimes quite bad ones).
	Solatis® has the problem that is does not support an atomic
	open with the O_CLOEXEC flag.  Actually, Solaris® does not
	support te O_CLOEXEC open-flag at all!  So this has to be
	emulated for Solaris®.  What a flipping embarrassment!

*******************************************************************************/

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<poll.h>
#include	<climits>		/* |INT_MAX| */
#include	<cerrno>
#include	<cstddef>		/* |nullptr_t| */
#include	<numeric>		/* |saturate_cast(3c++)| */
#include	<usystem.h>
#include	<usupport.h>
#include	<usysflag.h>
#include	<errtimer.hh>
#include	<aflag.hh>
#include	<localmisc.h>

#include	"uopen.h"


/* local defines */


/* imported namespaces */

using usys::unonblock ;			/* subroutine */


/* local typedefs */


/* local structures */

enum flavors {
	flavor_single,
	flavor_pipes,
	flavor_overlast
} ;

namespace {
    struct opener ;
    typedef int (opener::*opener_m)(cchar *,int,mode_t) noex ;
    struct opener {
	opener_m	m ;
	SOCKADDR	*sap ;
	int		*pipes ;
	cchar		*fname ;
	int		*lenp ;
	int		dfd ;
	int		tfd ;
	int		pf ;
	int		st ;
	int		pr ;
	flavors		flavor{} ;
	bool		fcloseonexec = false ;
	opener() noex { } ;
	opener(int adfd,int atfd = -1) noex : dfd(adfd), tfd(atfd) { } ;
	opener(int apf,int ast,int apr,int *ap = nullptr) noex : pf(apf) {
	    st = ast ;
	    pr = apr ;
	    pipes = ap ;
	    if (pipes) {
		pipes[0] = -1 ;
		pipes[1] = -1 ;
	    }
	} ;
	opener(int afd,SOCKADDR *fp,int *lp) noex : dfd(afd), sap(fp) {
	   lenp = lp ;
	} ;
	opener(int *apipes,int mfd = 0) noex : pipes(apipes), tfd(mfd) { 
	    if (pipes) {
		pipes[0] = -1 ;
		pipes[1] = -1 ;
	    }
	} ;
	int operator () (cchar *fn,int of,mode_t om) noex {
	    return openreg(fn,of,om) ;
	} ;
	operator int () noex {
	    cnullptr	np{} ;
	    return openreg(np,0,0) ;
	} ;
	int openreg(cchar *,int,mode_t) noex ;
	int openjack(cchar *,int,mode_t) noex ;
	int callstd(cchar *,int,mode_t) noex ;
	int iopen(cchar *,int,mode_t) noex ;
	int iopenat(cchar *,int,mode_t) noex ;
	int isocket(cchar *,int,mode_t) noex ;
	int iaccept(cchar *,int,mode_t) noex ;
	int iacceptpass(cchar *,int,mode_t) noex ;
	int idup1(cchar *,int,mode_t) noex ;
	int idup2(cchar *,int,mode_t) noex ;
	int idupmin(cchar *,int,mode_t) noex ;
	int idupminer(cchar *,int,mode_t) noex ;
	int isocketpair(cchar *,int,mode_t) noex ;
	int ipipe(cchar *,int,mode_t) noex ;
	int ipipe2(cchar *,int,mode_t) noex ;
	int ipiper(cchar *,int,mode_t) noex ;
	int icloseonexec(int) noex ;
	void fderror(int) noex ;
    } ; /* end struct (opener) */
    struct openlock {
	aflag		fmx ;
    } ; /* end struct (openlock) */
} /* end namespace */


/* forward references */


/* local variables */

static aflag		uopenmx ;

constexpr bool		f_sunos = F_SUNOS ;


/* exported variables */


/* exported subroutines */

namespace uopen {
    sysret_t uopen_lockbegin() noex {
	return uopenmx.lockbegin ;
    }
    sysret_t uopen_lockend () noex {
	return uopenmx.lockend ;
    }
} /* end namespace */

int u_open(cchar *fname,int of,mode_t om) noex {
	opener		oo ;
	oo.m = &opener::iopen ;
	oo.flavor = flavor_single ;
	return oo(fname,of,om) ;
}

int u_openat(int dfd,cchar *fname,int of,mode_t om) noex {
	opener		oo(dfd) ;
	oo.m = &opener::iopenat ;
	oo.flavor = flavor_single ;
	return oo(fname,of,om) ;
}

int u_creat(cchar *fname,mode_t om) noex {
	cint		of = (O_CREAT | O_TRUNC | O_WRONLY) ;
	return u_open(fname,of,om) ;
}

int u_socket(int pf,int st,int pr) noex {
	opener		oo(pf,st,pr) ;
	oo.m = &opener::isocket ;
	oo.flavor = flavor_single ;
	return oo ;
}

int u_accept(int fd,SOCKADDR *fromp,int *fromlenp) noex {
	opener		oo(fd,fromp,fromlenp) ;
	oo.m = &opener::iaccept ;
	oo.flavor = flavor_single ;
	return oo ;
}

int u_acceptpass(int fd) noex {
	opener		oo(fd) ;
	oo.m = &opener::iacceptpass ;
	oo.flavor = flavor_single ;
	return oo ;
}

int u_dup(int sfd) noex {
	opener		oo(sfd) ;
	oo.m = &opener::idup1 ;
	return oo ;
}
/* end subroutine (u_dup) */

int u_dupmin(int sfd,int mfd) noex {
	opener		oo(sfd,mfd) ;
	oo.m = &opener::idupmin ;
	return oo ;
}
/* end subroutine (u_dupmin) */

int u_dupminer(int sfd,int mfd,int of) noex {
	opener		oo(sfd,mfd) ;
	cnullptr	np{} ;
	oo.m = &opener::idupminer ;
	if (of & O_CLOEXEC) oo.fcloseonexec = true ;
	return oo(np,of,0) ;
}
/* end subroutine (u_dupminer) */

int u_dup2(int sfd,int tfd) noex {
	opener		oo(sfd,tfd) ;
	oo.m = &opener::idup2 ;
	return oo ;
}
/* end subroutine (u_dup2) */

int u_socketpair(int pf,int st,int pr,int *pipes) noex {
	opener		oo(pf,st,pr,pipes) ;
	oo.m = &opener::isocketpair ;
	oo.flavor = flavor_pipes ;
	return oo ;
}

int u_pipe(int *pipes) noex {
	opener		oo(pipes) ;
	oo.m = &opener::ipipe ;
	oo.flavor = flavor_pipes ;
	return oo ;
}

int u_pipe2(int *pipes,int of) noex {
	cnullptr	np{} ;
	opener		oo(pipes) ;
	oo.m = &opener::ipipe2 ;
	oo.flavor = flavor_pipes ;
	return oo(np,of,0) ;
}

int u_piper(int *pipes,int of,int mfd) noex {
	cnullptr	np{} ;
	opener		oo(pipes,mfd) ;
	oo.m = &opener::ipiper ;
	oo.flavor = flavor_pipes ;
	return oo(np,of,0) ;
}


/* local subroutines */

int opener::openreg(cchar *fname,int of,mode_t om) noex {
	int		rs ;
	int		rs1 ;
	int		fd = -1 ;
	if ((rs = uopenmx.lockbegin) >= 0) {
	    {
		rs = openjack(fname,of,om) ;
		fd = rs ;
	    }
	    rs1 = uopenmx.lockend ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (uopenmx) */
	if (rs < 0) fderror(fd) ;
	return (rs >= 0) ? fd : rs ;
}
/* end method (opener::openreg) */

int opener::callstd(cchar *fname,int of,mode_t om) noex {
	int		rs ;
	of &= (~ OF_SPECIALMASK) ;
	if ((rs = (this->*m)(fname,of,om)) < 0) {
	    rs = (- errno) ;
	}
	return rs ;
}
/* end method (opener::callstd) */

int opener::openjack(cchar *fname,int of,mode_t om) noex {
	errtimer	to_again	= utimeout[uto_again] ;
	errtimer	to_busy		= utimeout[uto_busy] ;
	errtimer	to_nomem	= utimeout[uto_nomem] ;
	errtimer	to_nosr		= utimeout[uto_nosr] ;
	errtimer	to_nobufs	= utimeout[uto_nobufs] ;
	errtimer	to_mfile	= utimeout[uto_mfile] ;
	errtimer	to_nfile	= utimeout[uto_nfile] ;
	errtimer	to_nolck	= utimeout[uto_nolck] ;
	errtimer	to_nospc	= utimeout[uto_nospc] ;
	errtimer	to_dquot	= utimeout[uto_dquot] ;
	errtimer	to_io		= utimeout[uto_io] ;
	reterr		r ;
	int		rs ;
	int		fd = -1 ;
	repeat {
	    if ((rs = callstd(fname,of,om)) < 0) {
                r(rs) ;                 /* <- default causes exit */
                switch (rs) {
                case SR_AGAIN:
                    r = to_again(rs) ;
                    break ;
                case SR_BUSY:
                    r = to_busy(rs) ;
                    break ;
                case SR_NOMEM:
                    r = to_nomem(rs) ;
                    break ;
                case SR_NOSR:
                    r = to_nosr(rs) ;
                    break ;
                case SR_NOBUFS:
                    r = to_nobufs(rs) ;
                    break ;
                case SR_MFILE:
                    r = to_mfile(rs) ;
                    break ;
                case SR_NFILE:
                    r = to_nfile(rs) ;
                    break ;
                case SR_NOLCK:
                    r = to_nolck(rs) ;
                    break ;
                case SR_NOSPC:
                    r = to_nospc(rs) ;
                    break ;
                case SR_DQUOT:
                    r = to_dquot(rs) ;
                    break ;
                case SR_IO:
                    r = to_io(rs) ;
                    break ;
                case SR_INPROGRESS:
                case SR_INTR:
                    r(false) ;
                    break ;
                } /* end switch */
                rs = r ;
	    } /* end if (error) */
	} until ((rs >= 0) || r.fexit) ;
	fd = rs ;
	if_constexpr (f_sunos) {
	    if ((rs >= 0) && (of & O_CLOEXEC)) {
		rs = icloseonexec(fd) ;
	    }
	} /* end if_constexpr (f_sunos) */
	return (rs >= 0) ? fd : rs ;
}
/* end method (opener::openjack) */

int opener::iopen(cchar *fname,int of,mode_t om) noex {
	int		rs = SR_FAULT ;
	if (fname) {
	    rs = SR_INVALID ;
	    if (fname[0] && (of >= 0)) {
	        if ((rs = open(fname,of,om)) < 0) {
		    rs = (- errno) ;
	        }
	    } /* end if (valid) */
	}
	return rs ;
}
/* end method (opener::iopen) */

int opener::iopenat(cchar *fname,int of,mode_t om) noex {
	int		rs = SR_FAULT ;
	if (fname) {
	    rs = SR_INVALID ;
	    if (fname[0] && (of >= 0)) {
	        if ((rs = openat(dfd,fname,of,om)) < 0) {
		    rs = (- errno) ;
	        }
	    } /* end if (valid) */
	}
	return rs ;
}
/* end method (opener::iopenat) */

int opener::isocket(cchar *,int,mode_t) noex {
	int		rs = SR_INVALID ;
	if ((pf >= 0) && (st >= 0) && (pr >= 0)) {
	    if ((rs = socket(pf,st,pr)) < 0) {
		rs = (- errno) ;
	    }
	} /* end if (valid) */
	return rs ;
}
/* end method (opener::isocket) */

int opener::iaccept(cchar *,int,mode_t) noex {
	int		rs = SR_FAULT ;
	if (sap && lenp) {
	    socklen_t	salen = socklen_t(*lenp) ;
	    if ((rs = accept(dfd,sap,&salen)) < 0) {
		rs = (- errno) ;
	    }
	    if (rs >= 0) {
	        *lenp = int(salen & INT_MAX) ;
	    }
	} /* end if (non-null) */
	return rs ;
}
/* end method (opener::iaccept) */

int opener::iacceptpass(cchar *,int,mode_t) noex {
	return SR_NOSYS ;
}
/* end method (opener::iacceptpass) */

int opener::idup1(cchar *,int,mode_t) noex {
	int		rs ;
	if ((rs = dup(dfd)) < 0) {
	    rs = (- errno) ;
	}
	return rs ;
}
/* end method (opener::idup1) */

int opener::idup2(cchar *,int,mode_t) noex {
	int		rs = SR_BADF ;
	if ((dfd >= 0) && (tfd >= 0)) {
	    if ((rs = dup2(dfd,tfd)) < 0) {
	        rs = (- errno) ;
	    }
	}
	return rs ;
}
/* end method (opener::idup2) */

int opener::idupmin(cchar *,int,mode_t) noex {
	int		rs = SR_BADF ;
	if ((dfd >= 0) && (tfd >= 0)) {
	    cint	cmd = F_DUPFD ;
	    if ((rs = fcntl(dfd,cmd,tfd)) < 0) {
	        rs = (- errno) ;
	    }
	}
	return rs ;
}
/* end method (opener::idupmin) */

int opener::idupminer(cchar *,int of,mode_t) noex {
	int		rs = SR_BADF ;
	int		fd = -1 ;
	if ((dfd >= 0) && (tfd >= 0)) {
	    cint	cmd = (fcloseonexec) ? F_DUPFD_CLOEXEC : F_DUPFD ;
	    if ((rs = fcntl(dfd,cmd,tfd)) >= 0) {
		fd = rs ;
	        if (of & O_NONBLOCK) {
		    rs = unonblock(fd,true) ;
		    if (rs < 0) {
			close(fd) ;
		    }
	        } /* end if (O_NONBLOCK was specified) */
	    } else {
	        rs = (- errno) ;
	    }
	}
	return (rs >= 0) ? fd : rs ;
}
/* end method (opener::idupminer) */

int opener::isocketpair(cchar *,int,mode_t) noex {
	int		rs = SR_FAULT ;
	if (pipes) {
	    rs = SR_INVALID ;
	    if ((pf >= 0) && (st >= 0) && (pr >= 0)) {
	        if ((rs = socketpair(pf,st,pf,pipes)) < 0) {
		    rs = (- errno) ;
	        }
	    } /* end if (valid) */
	} /* end if (non-null) */
	return rs ;
}
/* end method (opener::isocketpair) */

int opener::ipipe(cchar *,int,mode_t) noex {
	int		rs = SR_FAULT ;
	if (pipes) {
	    if ((rs = pipe(pipes)) < 0) {
		rs = (- errno) ;
	    }
	} /* end if (valid) */
	return rs ;
}
/* end method (opener::ipipe) */

int opener::ipipe2(cchar *,int of,mode_t) noex {
	int		rs = SR_FAULT ;
	if (pipes) {
	    if ((rs = pipe2(pipes,of)) < 0) {
		rs = (- errno) ;
	    }
	} /* end if (valid) */
	return rs ;
}
/* end method (opener::ipipe2) */

int opener::ipiper(cchar *,int of,mode_t) noex {
	int		rs = SR_FAULT ;
	if (pipes) {
	    if ((rs = pipe2(pipes,of)) < 0) {
		rs = (- errno) ;
	    }
	} /* end if (valid) */
	return rs ;
}
/* end method (opener::ipiper) */

int opener::icloseonexec(int fd) noex {
	int		rs = SR_OK ;
	int		rs1 ;
	switch (flavor) {
	case flavor_single:
	    if (fd >= 0) {
	        rs = u_closeonexec(fd,true) ;
	        if (rs < 0) u_close(fd) ;
	    }
	    break ;
	case flavor_pipes:
	    if (pipes) {
		for (int i = 0 ; i < 2 ; i += 1) {
		    if (pipes[i] >= 0) {
			rs1 = u_closeonexec(pipes[i],true) ;
			if (rs >= 0) rs = rs1 ;
		    }
	        } /* end for */
	    }
	    break ;
	default:
	    rs = SR_BUGCHECK ;
	    break ;
	} /* end switch */
	return rs ;
}
/* end method (opener::icloseonexec) */

void opener::fderror(int fd) noex {
	switch (flavor) {
	case flavor_single:
	    if (fd >= 0) close(fd) ;
	    break ;
	case flavor_pipes:
	    if (pipes) {
		for (int i = 0 ; i < 2 ; i += 1) {
		    if (pipes[i] >= 0) {
			close(pipes[i]) ;
			pipes[i] = -1 ;
		    }
	        } /* end for */
	    }
	    break ;
	default:
	    break ;
	} /* end switch */
}
/* end method (opener::fderror) */


