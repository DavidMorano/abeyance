/* usysdarwintty SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* Darwin thread-safe version of |ttyname(3c)| */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Name:
	usysdarwintty

	Description:
	This is the hack needed for Apple-Darwin in order to get
	a thread-safe version of |ttyname(3c)|.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<unistd.h>		/* |ttyname(3c)| */
#include	<csignal>		/* |sig_atomic_t| */
#include	<climits>		/* |INT_MAX| */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |stpncpy(3c)| */
#include	<usystem.h>
#include	<aflag.hh>
#include	<timewatch.hh>
#include	<ptm.h>
#include	<localmisc.h>

import usigblock ;

/* local defines */


/* imported namespaces */


/* local typedefs */


/* exported variables */


/* external subroutines */


/* local structures */

namespace {
    struct usysdarwinttyr {
	ptm		mx ;		/* data mutex */
	aflag		fvoid ;
	aflag		finit ;
	aflag		finitdone ;
	int init() noex ;
	int fini() noex ;
	int get() noex ;
	int setmode(mode_t) noex ;
	void forkbefore() noex {
	    mx.lockbegin() ;
	} ;
	void forkafter() noex {
	    mx.lockend() ;
	} ;
	int getttyname(char *,int,int) noex ;
	destruct usysdarwinttyr() {
            if (cint rs = fini() ; rs < 0) {
                ulogerror("usysdarwintty",rs,"dtor-fini") ;
            }
	} ;
    } ; /* end struct (usysdarwinttyr) */
} /* end namespace */


/* forward references */

extern "C" {
    static void	usysdarwintty_atforkbefore() noex ;
    static void	usysdarwintty_atforkafter() noex ;
    static void	usysdarwintty_exit() noex ;
}


/* local variables */

static usysdarwinttyr	usysdarwintty_data ;


/* exported variables */


/* exported subroutines */

int usysdarwintty_init() noex {
	return usysdarwintty_data.init() ;
}
/* end subroutine (usysdarwintty_init) */

int usysdarwintty_fini() noex {
	return usysdarwintty_data.fini() ;
}
/* end subroutine (usysdarwintty_fini) */

namespace libu {
    sysret_t darwin_ttyname(int fd,char *rbuf,int rlen) noex {
	int		rs ;
	int		rs1 ;
	int		rv = 0 ;
	if (usigblock b ; (rs = b.start) >= 0) {
	    {
		rs = usysdarwintty_data.getttyname(rbuf,rlen,fd) ;
		rv = rs ;
	    }
	    rs1 = b.finish ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (usigblock) */
	return (rs >= 0) ? rv : rs ;
    } /* end subroutine (darwin_ttyname) */
} /* end namespace (libu) */


/* local subroutines */

int usysdarwinttyr::init() noex {
	int		rs = SR_NXIO ;
	int		f = false ;
	if (! fvoid) {
	    cint	to = utimeout[uto_busy] ;
	    rs = SR_OK ;
	    if (! finit.testandset) {
	        if ((rs = mx.create) >= 0) {
	            void_f	b = usysdarwintty_atforkbefore ;
	            void_f	a = usysdarwintty_atforkafter ;
	            if ((rs = uc_atfork(b,a,a)) >= 0) {
			void_f	e = usysdarwintty_exit ;
	                if ((rs = uc_atexit(e)) >= 0) {
	    	            finitdone = true ;
		            f = true ;
		        }
		        if (rs < 0) {
		            uc_atforkexpunge(b,a,a) ;
			}
	            } /* end if (uc_atfork) */
	 	    if (rs < 0) {
		        mx.destroy() ;
		    }
	        } /* end if (ptm_create) */
	        if (rs < 0) {
	            finit = false ;
		}
            } else if (! finitdone) { 
                timewatch       tw(to) ;
                auto lamb = [this] () -> int {
                    int         rsl = SR_OK ;
                    if (!finit) {
                        rsl = SR_LOCKLOST ;              /* <- failure */
                    } else if (finitdone) {
                        rsl = 1 ;                        /* <- OK ready */
                    }                       
                    return rsl ;
                } ; /* end lambda (lamb) */ 
                rs = tw(lamb) ;         /* <- time-watching occurs in there */
	    } /* end if */
	} /* end if (not-voided) */
	return (rs >= 0) ? f : rs ;
}
/* end subroutine (usysdarwintty_init) */

int usysdarwinttyr::fini() noex {
	int		rs = SR_OK ;
	int		rs1 ;
	if (finitdone && (! fvoid.testandset)) {
	    {
	        void_f	b = usysdarwintty_atforkbefore ;
	        void_f	a = usysdarwintty_atforkafter ;
	        rs1 = uc_atforkexpunge(b,a,a) ;
		if (rs >= 0) rs = rs1 ;
	    }
	    {
	        rs1 = mx.destroy ;
		if (rs >= 0) rs = rs1 ;
	    }
	    finit = false ;
	    finitdone = false ;
	} /* end if (atexit registered) */
	return rs ;
}
/* end method (usysdarwinttyr::fini) */

int usysdarwinttyr::getttyname(char *rbuf,int rlen,int fd) noex {
	int		rs ;
	int		rs1 ;
	int		rv = 0 ;
	if ((rs = init()) >= 0) {
	    if ((rs = mx.lockbegin) >= 0) {
		csize	rsize = size_t(rlen) ;
	        if (char *p ; (p = ttyname(fd)) != nullptr) {
		    char	*dp = stpncpy(rbuf,p,rsize) ;
		    *dp = '\0' ;
		    rs = intconv(dp - rbuf) ;
	        } else {
		    rbuf[0] = '\0' ;
		    rs = (- errno) ;
	        } /* end if (ttyname) */
	        rs1 = mx.lockend ;
		if (rs >= 0) rs = rs1 ;
	    } /* end if (mutex) */
	} /* end if (init) */
	return (rs >= 0) ? rv : rs ;
}
/* end method (usysdarwinttyr::getttyname) */

static void usysdarwintty_atforkbefore() noex {
	usysdarwintty_data.forkbefore() ;
}
/* end subroutine (usysdarwintty_atforkbefore) */

static void usysdarwintty_atforkafter() noex {
	usysdarwintty_data.forkafter() ;
}
/* end subroutine (usysdarwintty_atforkafter) */

static void usysdarwintty_exit() noex {
	usysdarwintty_data.fini() ;
}
/* end subroutine (usysdarwintty_exit) */


