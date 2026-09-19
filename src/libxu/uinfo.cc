/* uinfo SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* UNIX® information (a cache for |uname(2)| and sisters) */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-02-01, David A­D­ Morano
	Originally written for Rightcore Network Services.

	= 2020-03-26, David A­D­ Morano
	I refactored the |uinfo_auxload| subroutine below.  It
	previously used a proprietary interface to get that auxillary
	information, but now it uses a generic interface (suitable
	for most all UNIX®-like systems).

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	int uinfo_name
	int uinfo_aux

	Description:
	This module serves as a cache (of sorts) for UNIX® information
	that is related to the underlying machine and which does
	not (easily) change during program exection.  Since we are
	basically dealing with global data, we need to make the
	establishment of it multi-thread safe.  We also want fork
	safety.  Yes, we want everything, including cleanup on
	module unloading (since, yes, we could all be inside a
	loadable and unloadble module!).  For these purposes we
	employ the basic (and not so basic) means of accomplishing
	this.  See the code for our various machinations.

	Synopsis:
	int uinfo_name(uinfo_names *) noex
	int uinfo_aux(uinfo_auxs *) noex

	Q. Do these subroutines (the public ones) need to be 
	multi-thread-safe?
	A. What do you think?

	Q. Did these subroutines need to be async-signal-safe?
	A. No.  I do not think that these needed to be async-signal-safe.

	Q. Is it a "waste" to make these subroutines async-signal-safe?
	A. Yes. Probably.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/utsname.h>		/* POSIX */
#include	<cstddef>		/* CSTD |nullptr_t| */
#include	<cstdlib>		/* CSTD */
#include	<new>			/* C++STD plavement-new(c++) */
#include	<memory>		/* C++STD |destroy_a(3c++)| */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<usupport.h>		/* LIBU */
#include	<umem.hh>		/* LIBU */
#include	<ucsysauxinfo.h>	/* |SAI_{xx}| */
#include	<ucfork.h>
#include	<ucatfork.h>
#include	<ucatexit.h>
#include	<sysconfcmds.h>		/* LIBU */
#include	<ptm.h>			/* LIBU */
#include	<timewatch.hh>		/* LIBU */
#include	<localmisc.h>		/* LIBU */

#include	"uinfo.h"

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |lenstr(3u)| */
import usigblock ;
import usysconf ;
import ulibvals ;			/* variable (currently unused) */

/* local defines */


/* imported namespaces */

using std::destroy_at ;			/* subroutine */
using libu::strwcpy ;			/* subroutine */
using libu::umem ;			/* variable */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */

namespace {
    struct auxinfo {
	char		*a = nullptr ;
	char		*architecture ;
	char		*platform ;
	char		*hwprovider ;
	char		*hwserial ;
	char		*nisdomain ;
        cint		nfields = 5 ;
	int		flen ;		/* length of fields (buffers) above */
	int start() noex ;
	int finish() noex ;
	int load() noex ;
    } ; /* end struct (auxinfo) */
    struct setname {
	uinfo_infoname	tmpname ;
	char		*strp = nullptr ;
	destruct setname() {
	    if (strp) {
	        umem.free(strp) ;
	        strp = nullptr ;
	    } /* end if (memory-release) */
	} ; /* end dtor */
    } ; /* end struct (setname) */
    struct setaux {
	uinfo_infoaux	tmpaux ;
	char		*strp = nullptr ;
	destruct setaux() {
	    if (strp) {
	        umem.free(strp) ;
	        strp = nullptr ;
	    } /* end if (memory-release) */
	} ; /* end dtor */
    } ; /* end struct (setaux) */
    struct uinfo_alloc {
	char		*name ;	/* string allocation for "name" */
	char		*aux ;	/* string allocation for "aux" */
    } ; /* end struct (uinfo_alloc) */
    struct uinfo {
	ptm		mx ;		/* data mutex */
	uinfo_alloc	ao ;		/* memory allocations */
	uinfo_infoname	name ;
	uinfo_infoaux	aux ;
	aflag		fvoid ;
	aflag		finit ;
	aflag		finitdone ;
	int init() noex ;
	int fini() noex ;
	int getname(uinfo_infoname *) noex ;
	int getname_setup() noex ;
	int getname_load(setname *) noex ;
	int getname_install(setname *) noex ;
	int getaux(uinfo_infoaux *) noex ;
	int getaux_setup() noex ;
	int getaux_load(setaux *) noex ;
	int getaux_install(setaux *) noex ;
	void atforkbefore() noex {
	    mx.lockbegin() ;
	} ;
	void atforkafter() noex {
	    mx.lockend() ;
	} ;
	destruct uinfo() noex {
	    if (cint rs = fini() ; rs < 0) {
	        ulogerror("uinfo",rs,"dtor-fini") ;
	    }
	} ; /* end dtor (uinfo) */
    } ; /* end struct (uinfo) */
} /* end namespace */


/* forward references */

extern "C" {
    local void	uinfo_atforkbefore() noex ;
    local void	uinfo_atforkafter() noex ;
    local void	uinfo_exit() noex ;
}


/* local variables */

static uinfo		uinfo_data ;

constexpr int		sais[] = {
	SAI_ARCHITECTURE,
	SAI_PLATFORM,
	SAI_HWPROVIDER,
	SAI_HWSERIAL,
	SAI_RPCDOMAIN
} ; /* end array (sais) */


/* exported variables */


/* exported subroutines */

int uinfo_init() noex {
	return uinfo_data.init() ;
}

int uinfo_fini() noex {
	return uinfo_data.fini() ;
}

int uinfo_name(uinfo_infoname *unp) noex {
	return uinfo_data.getname(unp) ;
}

int uinfo_aux(uinfo_infoaux *uxp) noex {
	return uinfo_data.getaux(uxp) ;
}


/* local subroutines */

int uinfo::init() noex {
	int		rs = SR_NXIO ;
	int		f = false ;
	if (!fvoid) {
	    cint	to = utimeout[uto_busy] ;
	    rs = SR_OK ;
	    if (! finit.testandset) {
	        if ((rs = mx.create) >= 0) {
	            void_f	b = uinfo_atforkbefore ;
	            void_f	a = uinfo_atforkafter ;
	            if ((rs = uc_atforkrec(b,a,a)) >= 0) {
	                if ((rs = uc_atexit(uinfo_exit)) >= 0) {
	                    finitdone = true ;
	                    f = true ;
	                }
	                if (rs < 0) {
	                    uc_atforkexp(b,a,a) ;
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
	        timewatch	tw(to) ;
	        cauto lamb = [this] () -> int {
	            int		rsl = SR_OK ;
	            if (!finit) {
		        rsl = SR_LOCKFAIL ;		/* <- failure */
	            } else if (finitdone) {
		        rsl = 1 ;			/* <- OK ready */
	            }
	            return rsl ;
	        } ; /* end lambda (lamb) */
	        rs = tw(lamb) ;		/* <- time-watching occurs in there */
	    } /* end if (initialization) */
	} /* end if (not voided) */
	return (rs >= 0) ? f : rs ;
} /* end subroutine (uinfo::init) */

int uinfo::fini() noex {
	int		rs = SR_OK ;
	int		rs1 ;
	if (finitdone && (! fvoid.testandset)) {
	    {
	        uinfo_alloc	*uap = &ao ;
	        if (uap->name) {
	            rs1 = umem.free(uap->name) ;
		    if (rs >= 0) rs = rs1 ;
	            uap->name = nullptr ;
	        } /* end if (memory-release) */
	        if (uap->aux) {
	            rs1 = umem.free(uap->aux) ;
		    if (rs >= 0) rs = rs1 ;
	            uap->aux = nullptr ;
	        } /* end if (memory-release) */
	    } /* end block */
	    {
	        void_f	b = uinfo_atforkbefore ;
	        void_f	a = uinfo_atforkafter ;
	        rs1 = uc_atforkexp(b,a,a) ;
		if (rs >= 0) rs = rs1 ;
	    } /* end block */
	    {
	        rs1 = mx.destroy ;
		if (rs >= 0) rs = rs1 ;
	    } /* end block */
	    finit = false ;
	    finitdone = false ;
	} /* end if (was initialized) */
	return rs ;
} /* end subroutine (uinfo::fini) */

int uinfo::getname(uinfo_infoname *unp) noex {
	int		rs = SR_FAULT ;
	int		rs1 ;
	if (unp) {
	    memclear(unp) ;
	    if (usigblock b ; (rs = b.start) >= 0) {
	        if ((rs = init()) >= 0) {
		    if ((rs = getname_setup()) >= 0) {
			*unp = name ;
		    }
	        } /* end if (init) */
	        rs1 = b.finish ;
	        if (rs >= 0) rs = rs1 ;
	    } /* end if (usigblock) */
	} /* end if (non-null) */
	return rs ;
} /* end subroutine (uinfo::getname) */

int uinfo::getname_setup() noex {
	int		rs = SR_OK ;
	if (ao.name == nullptr) {
	    if (setname tmp ; (rs = getname_load(&tmp)) >= 0) {
		rs = getname_install(&tmp) ;
	    } /* end if (ok) */
	} /* end if (setup needed) */
	return rs ;
} /* end method (uinfo::getname_setup) */

int uinfo::getname_load(setname *setp) noex {
	cint		usz = szof(utsname) ;
	int		rs ;
	int		rs1 ;
	if (void *vp ; (rs = umem.mall(usz,&vp)) >= 0) {
	    if (utsname *utsp = new(vp) utsname ; utsp) {
                if ((rs = u_uname(utsp)) >= 0) {
                    cint    nlen = (szof(utsp->sysname) - 1) ;
                    int     sz = 0 ;
                    sz += (lenstr(utsp->sysname,nlen) + 1) ;
                    sz += (lenstr(utsp->nodename,nlen) + 1) ;
                    sz += (lenstr(utsp->release,nlen) + 1) ;
                    sz += (lenstr(utsp->version,nlen) + 1) ;
                    sz += (lenstr(utsp->machine,nlen) + 1) ;
                    if (char *bp ; (rs = umem.mall(sz,&bp)) >= 0) {
                        setp->strp = bp ;
                        setp->tmpname.sysname = bp ;
                        bp = (strwcpy(bp,utsp->sysname,nlen) + 1) ;
                        setp->tmpname.nodename = bp ;
                        bp = (strwcpy(bp,utsp->nodename,nlen) + 1) ;
                        setp->tmpname.release = bp ;
                        bp = (strwcpy(bp,utsp->release,nlen) + 1) ;
                        setp->tmpname.version = bp ;
                        bp = (strwcpy(bp,utsp->version,nlen) + 1) ;
                        setp->tmpname.machine = bp ;
                        bp = (strwcpy(bp,utsp->machine,nlen) + 1) ;
                    } /* end if (memory-acquire) */
                } /* end if (u_uname) */
	        destroy_at(utsp) ;
	    } /* end if (utsname) */
	    rs1 = umem.free(vp) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (m-a-f) */
	return rs ;
} /* end method (uinfo::getname_load) */

int uinfo::getname_install(setname *setp) noex {
	int		rs ;
	int		rs1 ;
        if ((rs = uc_forklockbegin(-1)) >= 0) {
            if ((rs = mx.lockbegin) >= 0) {
                if (ao.name == nullptr) {
                    ao.name = setp->strp ;
                    name = setp->tmpname ;
                    setp->strp = nullptr ;
		} else {
		    umem.free(setp->strp) ;
		    setp->strp = nullptr ;
                } /* end if (memory-release) */
                rs1 = mx.lockend ;
                if (rs >= 0) rs = rs1 ;
            } /* end if (mutex) */
            rs1 = uc_forklockend() ;
            if (rs >= 0) rs = rs1 ;
        } /* end if (forklock) */
	return rs ;
} /* end method (uinfo::getname_install) */

int uinfo::getaux(uinfo_infoaux *uxp) noex {
	int		rs = SR_FAULT ;
	int		rs1 ;
	if (uxp) {
	    memclear(uxp) ;
	    if (usigblock b ; (rs = b.start) >= 0) {
	        if ((rs = init()) >= 0) {
		    if ((rs = getaux_setup()) >= 0) {
			*uxp = aux ;
		    }
	        } /* end if (init) */
	        rs1 = b.finish ;
	        if (rs >= 0) rs = rs1 ;
	    } /* end if (usigblock) */
	} /* end if (non-null) */
	return rs ;
} /* end subroutine (uinfo::getaux) */

int uinfo::getaux_setup() noex {
	int		rs = SR_OK ;
	if (ao.name == nullptr) {
	    if (setaux tmp ; (rs = getaux_load(&tmp)) >= 0) {
		rs = getaux_install(&tmp) ;
	    } /* end if (ok) */
	} /* end if (setup needed) */
	return rs ;
} /* end method (uinfo::getaux_setup) */

int uinfo::getaux_load(setaux *setp) noex {
	cint		usz = szof(auxinfo) ;
	int		rs ;
	int		rs1 ;
	if (void *vp ; (rs = umem.mall(usz,&vp)) >= 0) {
	    if (auxinfo *tap = new(vp) auxinfo ; tap) {
	        if ((rs = tap->start()) >= 0) {
                    if ((rs = tap->load()) >= 0) {
                        cint    nlen = tap->flen ;
                        int     sz = 0 ;
                        sz += (lenstr(tap->architecture,nlen) + 1) ;
                        sz += (lenstr(tap->platform,nlen) + 1) ;
                        sz += (lenstr(tap->hwprovider,nlen) + 1) ;
                        sz += (lenstr(tap->hwserial,nlen) + 1) ;
                        sz += (lenstr(tap->nisdomain,nlen) + 1) ;
                        if (char *bp ; (rs = umem.mall(sz,&bp)) >= 0) {
                            cchar   *sp ;
                            setp->strp = bp ;
		            {
                                setp->tmpaux.architecture = bp ;
                                sp = tap->architecture ;
                                bp = (strwcpy(bp,sp,nlen) + 1) ;
		            }
		            {
                                setp->tmpaux.platform = bp ;
                                sp = tap->platform ;
                                bp = (strwcpy(bp,sp,nlen) + 1) ;
		            }
		            {
                                setp->tmpaux.hwprovider = bp ;
                                sp = tap->hwprovider ;
                                bp = (strwcpy(bp,sp,nlen) + 1) ;
		            }
		            {
                                setp->tmpaux.hwserial = bp ;
                                sp = tap->hwserial ;
                                bp = (strwcpy(bp,sp,nlen) + 1) ;
		            }
		            {
                                setp->tmpaux.nisdomain = bp ;
                                sp = tap->nisdomain ;
                                bp = (strwcpy(bp,sp,nlen) + 1) ;
		            }
                        } /* end if (memory-acquire) */
                    } /* end if (uinfo_auxload) */
	    	    rs1 = tap->finish() ;
	            if (rs >= 0) rs = rs1 ;
	        } /* end if (start-finish) */
	        destroy_at(tap) ;
	    } /* end if (auxinfo) */
	    rs1 = umem.free(vp) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (m-a-f) */
	return rs ;
} /* end method (uinfo::getaux_load) */

int uinfo::getaux_install(setaux *setp) noex {
	int		rs ;
	int		rs1 ;
        if ((rs = uc_forklockbegin(-1)) >= 0) {
            if ((rs = mx.lockbegin) >= 0) {
                if (ao.aux == nullptr) {
                    ao.aux = setp->strp ;
                    aux = setp->tmpaux ;
                    setp->strp = nullptr ;
		} else {
		    umem.free(setp->strp) ;
		    setp->strp = nullptr ;
                }
                rs1 = mx.lockend ;
                if (rs >= 0) rs = rs1 ;
            } /* end if (mutex) */
            rs1 = uc_forklockend() ;
            if (rs >= 0) rs = rs1 ;
        } /* end if (forklock) */
	return rs ;
} /* end method (uinfo::getaux_install) */

int auxinfo::start() noex {
    	cint		cmd = _SC_NODENAME_MAX ;
    	int		rs ;
	a = nullptr ;
	flen = 0 ;
	if ((rs = usysconfval(cmd)) >= 0) {
	    cint	sz = (nfields * (rs + 1)) ;
	    flen = rs ;
	    if (void *vp ; (rs = umem.mall(sz,&vp)) >= 0) {
		int	ai = 0 ;
		a = charp(vp) ;
		{
		    architecture =	(a + ((flen + 1) * ai++)) ;
		    platform =		(a + ((flen + 1) * ai++)) ;
		    hwprovider =	(a + ((flen + 1) * ai++)) ;
		    hwserial =		(a + ((flen + 1) * ai++)) ;
		    nisdomain =		(a + ((flen + 1) * ai++)) ;
		}
	    } /* end if (memory-acquire) */
	} /* end if (usysconfval) */
	return rs ;
} /* end subroutine (auxinfo::start) */

int auxinfo::finish() noex {
    	int		rs = SR_OK ;
	int		rs1 ;
	if (a) {
	    rs1 = umem.free(a) ;
	    if (rs >= 0) rs = rs1 ;
	    a = nullptr ;
	}
	flen = 0 ;
	return rs ;
} /* end method (auxinfo::finish) */

int auxinfo::load() noex {
	cint    	nlen = flen ;
	int		rs = SR_BUGCHECK ;
	int		sz = 0 ;
	if (a) {
	    rs = SR_OK ;
	    architecture[0] = '\0' ;
	    platform[0] = '\0' ;
	    hwprovider[0] = '\0' ;
	    hwserial[0] = '\0' ;
	    nisdomain[0] = '\0' ;
	    for (cauto &req : sais) {
	        char	*nbuf = nullptr ;
	        switch (req) {
	        case SAI_ARCHITECTURE:
	            nbuf = architecture ;
		    break ;
	        case SAI_PLATFORM:
	            nbuf = platform ;
		    break ;
	        case SAI_HWPROVIDER:
	            nbuf = hwprovider ;
		    break ;
	        case SAI_HWSERIAL:
	            nbuf = hwserial ;
		    break ;
	        case SAI_RPCDOMAIN:
	            nbuf = nisdomain ;
		    break ;
	        } /* end switch */
	        if ((req >= 0) && nbuf) {
	            if ((rs = uc_sysauxinfo(nbuf,nlen,req)) >= 0) {
		        sz += (rs + 1) ;
		    } else if (rs == SR_NOTFOUND) {
		        rs = SR_OK ;
		        sz += 1 ;		/* for the NUL character */
	                nbuf[0] = '\0' ;
		    }
	        } else {
		    sz += 1 ;
	        } /* end if */
	        if (rs < 0) break ;
	    } /* end for */
	} /* end if (non-null) */
	return (rs >= 0) ? sz : rs ;
} /* end method (auxinfo::load) */

local void uinfo_atforkbefore() noex {
	uinfo_data.atforkbefore() ;
}

local void uinfo_atforkafter() noex {
	uinfo_data.atforkafter() ;
}

local void uinfo_exit() noex {
	if (cint rs = uinfo_data.fini() ; rs < 0) {
	    ulogerror("uinfo",rs,"exit-fini") ;
	}
} /* end subroutine (uinfo_exit) */


