/* getuid SUPPORT */
/* lang=C++20 */

/* get a UID by looking up the given name */
/* version %I% last-modified %G% */

#define	CF_UCPWCACHE	1		/* use |ugetpw(3uc)| */
#define	CF_GETUSER	0		/* compile in |getuser_uid()| */

/* revision history:

	= 1998-09-01, David A­D­ Morano
	This program was originally written.

	= 2017-11-22, David A­D­ Morano
	I finally (finally) removed (compiled out) the global
	function symbol |getuser_uid()|.  Good riddance.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	getuid_name

	Description:
	This subroutine will retrieve a UID by looking up a given
	name, assumed to be a user-name.

	Synopsis:
	int getuid_name(cchar *np,int nl) noex

	Arguments:
	np		user-name to lookup
	nl		length of name string

	Returns:
	>=0		retrieved UID
	<0		error (system-return)

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>
#include	<getbufsize.h>
#include	<mallocxx.h>
#include	<nulstr.h>
#include	<getax.h>
#include	<ucpwcache.h>
#include	<cfdec.h>
#include	<hasx.h>
#include	<localmisc.h>

#include	"getuid.h"


/* local defines */

#if	CF_UCPWCACHE
#define	GETPW_NAME	ucpwcache_name
#else
#define	GETPW_NAME	getpw_name
#endif /* CF_UCPWCACHE */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int getuid_name(cchar *sp,int sl) noex {
	int		rs = SR_FAULT ;
	int		rs1 ;
	int		uid = 0 ;
	if (sp) {
	    rs = SR_INVALID ;
	    if (sp[0]) {
	        nulstr	n ;
	        cchar	*name{} ;
	        if ((rs = nulstr_start(&n,sp,sl,&name)) >= 0) {
	            char	*pwbuf{} ;
	            if ((rs = malloc_pw(&pwbuf)) >= 0) {
	                cint	pwlen = rs ;
		        {
	                    PASSWD	pw ;
		            rs = GETPW_NAME(&pw,pwbuf,pwlen,name) ;
	                    uid = pw.pw_uid ;
		        }
	                rs1 = uc_free(pwbuf) ;
		        if (rs >= 0) rs = rs1 ;
	            } /* end if (m-a-f) */
	            rs1 = nulstr_finish(&n) ;
	            if (rs >= 0) rs = rs1 ;
	        } /* end if (nulstr) */
	    } /* end if (valid) */
	} /* end if (non-null) */
	return (rs >= 0) ? uid : rs ;
}
/* end subroutine (getuid_name) */

int getuid_user(cchar *sp,int sl) noex {
	int		rs = SR_FAULT ;
	if (sp) {
	    rs = SR_INVALID ;
	    if (sp[0]) {
	        if (hasalldig(sp,sl)) {
	            if (int v{} ; (rs = cfdeci(sp,sl,&v)) >= 0) {
		        rs = v ;
	            }
	        } else {
	            rs = getuid_name(sp,sl) ;
	        }
	    } /* end if (valid) */
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (getuid_user) */

#if	CF_GETUSER
int getuser_uid(cchar *sp,int sl) noex {
	return getuid_user(sp,sl) ;
}
#endif /* CF_GETUSER */


