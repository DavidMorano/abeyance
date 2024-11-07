/* vecpstr_addpath SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 */

/* add a "path" compnent to the string-list */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-06-01, David A­D­ Morano
	This code was originally written.

	= 2023-10-27, David A­D­ Morano
	I changed to make the MAXPATHLEN value dynamic.

*/

/* Copyright © 1998,2023 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	------------------------------------------------------------------------
	Name:
	vecpstr_addpathclean

	Description:
	This subroutine adds a "path" componment to the vector-string
	list.  It cleans up the path-component first by passing it
	through 'pathclean(3dam)'.

	Synopsis:
	int vecpstr_addpathclean(vecpstr *lp,cchar *pp,int pl) noex

	Arguments:
	lp		vector-string list object pointer
	pp		path-string pointer
	pl		length of given string

	Returns:
	>=0		OK
	<0		error (system-return)


	------------------------------------------------------------------------
	Name:
	vecpstr_addcspath

	Description:
	This subroutine will add (uniquely) the Condig-String (CS) 
	PATH value to the vector-list.

	Synopsis:
	int vecpstr_addcspath(vecpstr *) noex

	Arguments:
	vsp		pointer to VECSTR object

	Returns:
	>=0		number of elements loaded
	<0		error (system-return)

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/param.h>
#include	<unistd.h>
#include	<climits>		/* |INT_MAX| */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>		/* for |strlen(3c)| */
#include	<usystem.h>
#include	<bufsizevar.hh>
#include	<libmallocxx.h>		/* <- currently unused */
#include	<strn.h>
#include	<pathclean.h>
#include	<localmisc.h>

#include	"vecpstr.h"


/* local defines */

#define	NPATH	4			/* buffer multiply-factor */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */

static bufsizevar	maxpathlen(getbufsize_mp) ;


/* exported variables */


/* exported subroutines */

int vecpstr_addpathclean(vecpstr *vlp,cchar *lp,int ll) noex {
	int		rs = SR_FAULT ;
	int		rs1 ;
	int		c = 0 ;
	if (vlp && lp) {
	    rs = SR_OK ;
	    if (ll < 0) ll = strlen(lp) ;
	    if (ll > 0) {
		if ((rs = maxpathlen) >= 0) {
		    cint	dlen = rs ;
		    if (char *dbuf ; (rs = uc_libmalloc((dlen+1),&dbuf)) >= 0) {
	                cchar	*tp ;
	                while ((tp = strnpbrk(lp,ll,":;")) != nullptr) {
		            if ((tp-lp) >= 0) {
	    	                if ((rs = pathclean(dbuf,lp,(tp-lp))) >= 0) {
		                    rs = vecpstr_adduniq(vlp,dbuf,rs) ;
		                    if (rs < INT_MAX) c += 1 ;
		                }
		            }
		            ll -= ((tp+1)-lp) ;
		            lp = (tp+1) ;
		            if (rs < 0) break ;
	                } /* end while */
	                if ((rs >= 0) && (ll > 0)) {
	    	            if ((rs = pathclean(dbuf,lp,ll)) >= 0) {
		                rs = vecpstr_adduniq(vlp,dbuf,rs) ;
		                if (rs < INT_MAX) c += 1 ;
		            }
	                }
			rs1 = uc_libfree(dbuf) ;
			if (rs >= 0) rs = rs1 ;
		    } /* end if (m-a-f) */
		} /* end if (maxpathlen) */
	    } /* end if (non-zero) */
	} /* end if (non-null) */
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (vecpstr_addpathclean) */

int vecpstr_addpath(vecpstr *vlp,cchar *lp,int ll) noex {
	int		rs = SR_FAULT ;
	int		c = 0 ;
	if (vlp && lp) {
	    rs = SR_OK ;
	    if (ll < 0) ll = strlen(lp) ;
	    if (ll > 0) {
	        cchar	*tp ;
	        while ((tp = strnpbrk(lp,ll,":;")) != nullptr) {
		    if ((tp-lp) >= 0) {
		        rs = vecpstr_adduniq(vlp,lp,(tp-lp)) ;
		        if (rs < INT_MAX) c += 1 ;
		    }
		    ll -= ((tp+1)-lp) ;
		    lp = (tp+1) ;
		    if (rs < 0) break ;
	        } /* end while */
	        if ((rs >= 0) && (ll > 0)) {
		    rs = vecpstr_adduniq(vlp,lp,ll) ;
		    if (rs < INT_MAX) c += 1 ;
	        }
	    } /* end if (non-zero) */
	} /* end if (non-null) */
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (vecpstr_addpath) */

int vecpstr_addcspath(vecpstr *vsp) noex {
	int		rs = SR_FAULT ;
	int		rs1 ;
	int		c = 0 ;
	if (vsp) {
	    if ((rs = maxpathlen) >= 0) {
		cint	plen = (NPATH * rs) ;
	        if (char *pbuf{} ; (rs = uc_libmalloc((plen+1),&pbuf)) >= 0) {
		    cint	req = _CS_PATH ;
	            if ((rs = uc_sysconfstr(pbuf,plen,req)) >= 0) {
	                rs = vecpstr_addpath(vsp,pbuf,rs) ;
	                c += rs ;
	            } /* end if */
	            rs1 = uc_libfree(pbuf) ;
		    if (rs >= 0) rs = rs1 ;
	        } /* end if (m-a-f) */
	    } /* end if (maxpathlen) */
	} /* end if (non-null) */
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (vecpstr_addcspath) */


