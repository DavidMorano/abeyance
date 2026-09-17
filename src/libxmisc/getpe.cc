/* getpr SUPPORT */
/* lang=C++20 */

/* get protocol entry */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-06-16, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	These subroutines were was written to provide a more consistent
	interface to the system 'protocols" database.


*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>

#include	"getpr.h"


/* local defines */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int getpr_begin(int sf) noex {
	return uc_getprbegin(sf) ;
}
/* end subroutine (getpr_begin) */

int getpr_end() noex {
	return uc_getprend() ;
}
/* end subroutine (getpr_end) */

int getpr_ent(ucentpr *pp,char *rbuf,int rlen) noex {
	cint		rsn = SR_NOTFOUND ;
	int		rs ;
	if ((rs = uc_getprent(pp,rbuf,rlen)) == rsn) {
	    rs = SR_OK ;
	}
	return rs ;
}
/* end subroutine (getpr_ent) */

int getpr_name(ucentpr *pp,char *rbuf,int rlen,cchar *name) noex {
	return uc_getprnam(pp,rbuf,rlen,name) ;
}
/* end subroutine (getpr_name) */

int getpr_num(ucentpr *pp,char *rbuf,int rlen,int num) noex {
	return uc_getprnum(pp,rbuf,rlen,num) ;
}
/* end subroutine (getpr_num) */


