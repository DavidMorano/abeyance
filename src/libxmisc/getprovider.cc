/* getprovider SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* get the machine provider c-string */
/* version %I% last-modified %G% */


/* revision history:

	= 2001-04-11, David A­D­ Morano
	This was originally written.

*/

/* Copyright © 2001 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Name:
	getprovider
	getvendor

	Description:
	Get and return the machine provider string.

	Synopsis:
	int getprovider(char *rbuf,int rlen) noex
	int getvendor(char *rbuf,int rlen) noex

	Arguments:
	rbuf		result buffer
	rlen		result buffer length

	Returns:
	>=0		number of characters returned
	<0		error (system-return)

*******************************************************************************/

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/types.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |getenv(3c)| */
#include	<clanguage.h>
#include	<usysbase.h>
#include	<ucinfo.h>
#include	<mallocxx.h>
#include	<sncpy.h>
#include	<sfx.h>
#include	<nleadstr.h>
#include	<localmisc.h>

#include	"getprovider.h"


/* local defines */

#ifndef	VARPROVIDER
#define	VARPROVIDER	"PROVIDER"
#endif

#ifndef	PROVIDER
#define	PROVIDER	"Rightcore Network Services"
#endif


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int getprovider(char *rbuf,int rlen) noex {
	int		rs = SR_FAULT ;
	if (rbuf) {
	    static cchar	*valp = getenv(VARPROVIDER) ;
	    rbuf[0] = '\0' ;
	    if (valp != nullptr) { /* environment */
	        cchar	*cp ;
	        if (int cl ; (cl = sfshrink(valp,-1,&cp)) > 0) {
	            rs = sncpy1w(rbuf,rlen,cp,cl) ;
	        }
	    }
	    if ((rs >= 0) && (rbuf[0] == '\0')) { /* process cache */
	        if (ucinfo_infoaux aux ; (rs = ucinfo_aux(&aux)) >= 0) {
		    if (aux.hwprovider != nullptr) {
	                rs = sncpy1(rbuf,rlen,aux.hwprovider) ;
		    }
	        }
	    }
	    if ((rs >= 0) && (rbuf[0] == '\0')) { /* otherwise */
	        rs = sncpy1(rbuf,rlen,PROVIDER) ;
	    }
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (getprovider) */

int getvendor(char *rbuf,int rlen) noex {
	int		rs = SR_FAULT ;
	int		rl = 0 ;
	if (rbuf) {
	    rbuf[0] = '\0' ;
	    if (char *pbuf{} ; (rs = malloc_mp(&pbuf)) >= 0) {
		cint	plen = rs ;
	        if ((rs = getprovider(pbuf,plen)) >= 0) {
	            cint	pl = rs ;
	            int		i ; /* used-afterwards */
	            int		m ;
	            bool	f = false ;
	            rs = SR_NOTFOUND ;
	            for (i = 0 ; providers[i].codename != nullptr ; i += 1) {
	                cchar	*pn = providers[i].codename ;
	                m = nleadstr(pn,pbuf,pl) ;
	                f = ((m == pl) && (pn[m] == '\0')) ;
	                if (f) break ;
	            } /* end for */
	            if (f) {
		        rs = sncpy1(rbuf,rlen,providers[i].realname) ;
			rl = rs ;
	            }
	        } /* end if (getprovider) */
		rs = rsfree(rs,pbuf) ;
	    } /* end if (m-a-f) */
	} /* end if (non-null) */
	return (rs >= 0) ? rl : rs ;
}
/* end subroutine (getvendor) */


