/* getnw SUPPORT */
/* lang=C++20 */

/* get protocol entry */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-06-16, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	These subroutines were was written so that we could use a
	single interface to access the 'netent' database on all
	UNIX® platforms. This code module provides a platform
	independent implementation of UNIX® 'netent' database access
	subroutines.

	These are the preferred interfaces:

	preferred interfaces: getnw_name(), getnw_num() ;
	preferred interfaces: getgr_name(), getgr_gid() ;

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>

#include	"getnw.h"


/* local defines */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported subroutines */

int getnw_begin(int sf) noex {
	return uc_getnwbegin(sf) ;
}
/* end subroutine (getnw_begin) */

int getnw_end() noex {
	return uc_getnwend() ;
}
/* end subroutine (getnw_end) */

int getnw_ent(ucentnw *nep,char *rbuf,int rlen) noex {
	cint		rsn = SR_NOTFOUND ;
	int		rs ;
	if ((rs = uc_getnwent(nep,rbuf,rlen)) == rsn) {
	    rs = SR_OK ;
	}
	return rs ;
}
/* end subroutine (getnw_ent) */

int getnw_name(ucentnw *nep,char *rbuf,int rlen,cchar *name) noex {
	return uc_getnwnam(nep,rbuf,rlen,name) ;
}
/* end subroutine (getnw_name) */

int getnw_addr(ucentnw *nep,char *rbuf,int rlen,int af,int num) noex {
	return uc_getnwnum(nep,rbuf,rlen,af,num) ;
}
/* end subroutine (getnw_addr) */


