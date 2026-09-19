/* mkpathcd SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* try to make a prefix-variable path of type CDPATH */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	mkpathcd

	Description:
	This subroutine possibly expands the given path string if
	it is prefixed with the CDPATH indicator character.

	Synopsis:
	int mkpathcd(char *ebuf,cchar *pp,int pl) noex

	Arguments:
	ebuf		result buffer (should be MAXPATHLEN+1 long)
	pp		source path pointer
	pl		source path length

	Returns:
	>0		expansion
	==0		no expansion
	<0		error (system-return)

	Implementation note:
	Yes, we do not add extra slash characters between components
	of file paths (reasonably).  And we are not ashamed of this
	practice.  We do not though, remove extra slashes that are
	already preent (although we could if we wanted, to be extra
	smart about it).

	Form:
	¬[<varname>]/<path>

	Given (for example):
	CDPATH=/home/tools:/somewhere
	OTHER=/home/tools:/other/place

	Example:
	¬/stage/daytime
	¬cdpath/stage/daytime
	¬other/stage/daytime

	Results:
	/home/tools/stage/daytime
	/home/tools/stage/daytime
	/other/place/stage/daytime

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |getenv(3c)| */
#include	<new>			/* |nothrow(3c++) */
#include	<clanguage.h>
#include	<usysbase.h>
#include	<usyscalls.h>
#include	<bufsize.hh>
#include	<storebuf.h>
#include	<sfx.h>
#include	<strn.h>		/* |strnchr(3uc)| */
#include	<pathadd.h>
#include	<strwcpy.h>
#include	<mkchar.h>
#include	<isnot.h>
#include	<localmisc.h>

#include	"mkx.h"
#include	"mkpathxx.h"

#pragma		GCC dependency	"mod/libutil.ccm"
#pragma		GCC dependency	"mod/uconstants.ccm"

import libutil ;
import uconstants ;

/* local defines */

#define	MKCDPATH_MP	(4*1024)

#define	CHX_EXP		MKCHAR('¬')


/* imported namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */

namespace {
    class mksub {
	cchar		*plist = nullptr ;
	cchar		*vp = nullptr ;
	cchar		*sp ;
	cchar		*bp = nullptr ;
	char		*ebuf ;	/* caller-supplied argument */
	int		vl = 0 ;
	int		sl ;
	int		bl = 0 ;
	int		el = 0 ;
    public:
	mksub(char *µebuf,cchar *µsp,int µsl) noex : sp(µsp), sl(µsl) {
	    ebuf = µebuf ;
	    vp = sp ;
	} ; /* end ctor */
	int getvarname() noex {
	    if (cchar *tp ; (tp = strnchr(sp,sl,'/')) != nullptr) {
		vl = intconv(tp - sp) ;
		sl -= intconv((tp + 1) - sp) ;
		sp = (tp + 1) ;
	    }
	    return vl ;
	} ; /* end method (getvarname) */
	int getplist() noex {
	    cnothrow	nt{} ;
	    cnullptr	np{} ;
	    int		rs = SR_OK ;
	    if (vl > 0) {
		if (char *vn ; (vn = new(nt) char [vl+1]) != np) {
		    strwcpyuc(vn,vp,vl) ;
		    plist = getenver(vn,vl) ;
		    delete [] vn ;
		} else {
		    rs = SR_NOMEM ;
	 	} /* end if (m-a-f) */
	    } else {
		static cchar	*vvp = getenv(varname.cdpath) ;
		plist = vvp ;
	    }
	    return rs ;
	} ; /* end method (getplist) */
	int getbasename() noex {
	    if ((bl = sfbasename(sp,sl,&bp)) > 0) {
		sl = intconv(bp - sp - 1) ;
	    }
	    return sl ;
	} ; /* end method (getbasename) */
	int testpath(cchar *,int) noex ;
	int mkjoin(cchar *,int) noex ;
	int testpaths() noex ;
	int mkresult() noex ;
    } ; /* end class (mksub) */
    typedef int (mksub::*mksub_m)() noex ;
} /* end namespace */


/* forward references */


/* local variables */

static bufsizevar	maxpathlen(bufsize_mp,MKCDPATH_MP) ;

static const mksub_m	mems[] = {
    &mksub::getvarname,
    &mksub::getplist,
    &mksub::getbasename,
    &mksub::testpaths,
    &mksub::mkresult
} ; /* end array (mems) */


/* exported variables */


/* exported subroutines */

int mkpathcd(char *ebuf,cchar *fp,int fl) noex {
    	cnothrow	nt{} ;
	cnullptr	np{} ;
	int		rs = SR_FAULT ;
	int		el = 0 ;
	if (ebuf && fp) ylikely {
	    cint	chx_ec = CHX_EXP ;
	    ebuf[0] = '\0' ;
	    if (fl < 0) fl = lenstr(fp) ;
	    if ((fl > 0) && (mkchar(fp[0]) == chx_ec)) ylikely {
		cint	sl = (fl + 1) ;
		cchar	*sp = (fp + 1) ;
	        if (mksub *sip ; (sip = new(nt) mksub(ebuf,sp,sl)) != np) {
		    for (cauto &m : mems) {
			rs = (sip->*m)() ;
			if (rs <= 0) break ;
		    } /* end for */
		    el = rs ;
	            delete sip ;
		} /* end if (m-a-f) */
	    } /* end if (have one) */
	} /* end if (non-null) */
	return (rs >= 0) ? el : rs ;
}
/* end subroutine (mkpathcd) */


/* local srubroutines */

int mksub::testpaths() noex {
    	cnullptr	np{} ;
	int		rs = SR_OK ;
	if (plist != nullptr) ylikely {
	    int		pl = lenstr(plist) ;
	    cchar	*pp = plist ;
	    for (cchar *tp ; (tp = strnchr(pp,pl,':')) != np ; ) {
		cint	ll = intconv(tp - pp) ;
		if (ll > 0) ylikely {
		    rs = testpath(pp,ll) ;
		    el = rs ;
	        }
		pl -= intconv((tp + 1) - pp) ;
	        pp = (tp + 1) ;
		if (rs != 0) break ;
	    } /* end for */
	    if ((rs == 0) && (pl > 0)) {
	        rs = testpath(pp,pl) ;
		el = rs ;
	    }
	} /* end if (plist) */
	return (rs >= 0) ? el : rs ;
}
/* end subroutine (mksub::testpaths) */

int mksub::testpath(cchar *cp,int cl) noex {
	int		rs ;
	if ((rs = mkjoin(cp,cl)) >= 0) ylikely {
	    cint	jl = rs ;
	    if (ustat sb ; (rs = u_stat(ebuf,&sb)) >= 0) ylikely {
		if (S_ISDIR(sb.st_mode)) {
		    rs = jl ;
		} else {
		    rs = SR_OK ;
		}
	    } else if (isNotPresent(rs)) {
		rs = SR_OK ;
	    }
	} /* end if (mkjoin) */
	return rs ;
}
/* end subroutine (mksub::testpath) */

int mksub::mkjoin(cchar *cp,int cl) noex {
	int		rs ;
	int		len = 0 ;
	if ((rs = maxpathlen) >= 0) ylikely {
	    if (storebuf sb(ebuf,rs) ; (rs = sb.strw(cp,cl)) >= 0) ylikely {
	        if ((rs > 0) && (ebuf[rs - 1] != '/')) {
	            rs = sb.chr('/') ;
		}
	        if (rs >= 0) ylikely {
	            rs = sb.strw(sp,sl) ;
		    len = sb.idx ;
		}
	    }
	} /* end if (maxpathlen) */
	return (rs >= 0) ? len : rs ;
}
/* end subroutine (mksub::mkjoin) */

int mksub::mkresult() noex {
	return pathaddw(ebuf,el,bp,bl) ;
}
/* end subroutine (mksub::mkresult) */


