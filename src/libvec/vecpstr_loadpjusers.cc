/* vecpstr_loadpjusers SUPPORT */
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
	vecpstr_loadpjusers

	Description:
	This subroutine finds all users who have the given specified
	project.

	Synopsis:
	int vecpstr_loadpjusers(vecpstr *,cchar *) noex

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

#include	"vecpstr.h"


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

static int	vecpstr_loadpjnent(vecpstr *,ent *,cchar *) noex ;


/* local variables */


/* exported variables */


/* exported subroutines */

int vecpstr_loadpjusers(vecpstr *ulp,cchar *pjn) noex {
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
	                ucenumua	eua ;
	                if ((rs = ucenumua_open(&eua,nullptr)) >= 0) {
		            re_f	re = ucenumua_readent ;
	                    ent		ua{} ;
	                    while ((rs = re(&eua,&ua,uab,ual)) > 0) {
	                        rs = vecpstr_loadpjnent(ulp,&ua,pjn) ;
	                        c += rs ;
	                        if (rs < 0) break ;
	                    } /* end while */
	                    rs1 = ucenumua_close(&eua) ;
	                    if (rs >= 0) rs = rs1 ;
	                } /* end if (sysuserattr) */
	                rs1 = uc_libfree(uab) ;
		        if (rs >= 0) rs = rs1 ;
	            } /* end if (memory-allocation) */
	        } /* end if (getbufsize) */
	    } /* end if (valid) */
	} /* end if (non-null) */
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (vecpstr_loadpjusers) */


/* local subroutines */

static int vecpstr_loadpjnent(vecpstr *ulp,ent *uap,cchar *pjn) noex {
	int		rs ;
	int		c = 0 ;
	cchar		*k = "project" ;
	cchar		*vp{} ;
	if ((rs = uc_kvamatch(uap->attr,k,&vp)) >= 0) {
	    if (strwcmp(pjn,vp,rs) == 0) {
	        rs = vecpstr_adduniq(ulp,uap->name,-1) ;
	        if (rs < INT_MAX) c += 1 ;
	    }
	} else if (isNotPresent(rs)) {
	    rs = SR_OK ;
	}
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (vecpstr_loadpjnent) */


