/* vecstr_loadpjusers SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 */

/* find and load UNIX® users who have the given project name */
/* version %I% last-modified %G% */


/* revision history:

	= 2004-01-10, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 2004 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	vecstr_loadpjusers

	Description:
	This subroutine finds all users who have the given specified
	project.

	Synopsis:
	int vecstr_loadpjusers(vecstr *,cchar *) noex

	Returns:
	>=	ok
	<0	bad (system-return)

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<climits>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<usystem.h>
#include	<getbufsize.h>
#include	<ucenumua.h>
#include	<strwcmp.h>
#include	<isnot.h>
#include	<localmisc.h>

#include	"vecstr.h"


/* local defines */


/* imported namespaces */


/* local typedefs */

typedef ucentua		ent ;

extern "C" {
	typedef int (*re_f)(ucenumua *,ent *,char *,int) noex ;
}


/* external subroutines */


/* local structures */


/* forward references */

static int	vecstr_loadpjnent(vecstr *,ent *,cchar *) noex ;


/* local variables */


/* exported variables */


/* exported subroutines */

int vecstr_loadpjusers(vecstr *ulp,cchar *pjn) noex {
    	cnullptr	np{} ;
	int		rs = SR_FAULT ;
	int		rs1 ;
	int		c = 0 ;
	if (ulp && pjn) {
	    rs = SR_INVALID ;
	    if (pjn[0]) {
	        if ((rs = getbufsize(getbufsize_ua)) >= 0) {
	            cint	ual = rs ;
	            char	*uab{} ;
	            if ((rs = uc_libmalloc((ual+1),&uab)) >= 0) {
	                if (ucenumua eua ; ((rs = eua.open) >= 0) {
	                    ent		ua{} ;
	                    while ((rs = eua.readent(&ua,uab,ual)) > 0) {
	                        rs = vecstr_loadpjnent(ulp,&ua,pjn) ;
	                        c += rs ;
	                        if (rs < 0) break ;
	                    } /* end while */
	                    rs1 = ucenumua_close(&eua) ;
	                    if (rs >= 0) rs = rs1 ;
	                } /* end if (sysuserattr) */
	                rs1 = uc_libfree(uab) ;
		        if (rs >= 0) rs = rs1 ;
	            } /* end if (m-a-f) */
	        } /* end if (getbufsize) */
	    } /* end if (valid) */
	} /* end if (non-null) */
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (vecstr_loadpjusers) */


/* local subroutines */

static int vecstr_loadpjnent(vecstr *ulp,ent *uap,cchar *pjn) noex {
	int		rs ;
	int		c = 0 ;
	cchar		*k = "project" ;
	if cchar *vp{} ; (rs = uc_kvamatch(uap->attr,k,&vp)) >= 0) {
	    if (strwcmp(pjn,vp,rs) == 0) {
	        rs = vecstr_adduniq(ulp,uap->name,-1) ;
	        if (rs < INT_MAX) c += 1 ;
	    }
	} else if (isNotPresent(rs)) {
	    rs = SR_OK ;
	}
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (vecstr_loadpjnent) */


