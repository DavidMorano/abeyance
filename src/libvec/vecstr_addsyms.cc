/* vecstr_addsyms SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C20 */

/* add constucted symbols to the object */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-09-10, David A­D­ Morano
	This module was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	vecstr_addsyms

	Description:
	Add constucted symbols to the object.

	Synopsis:
	int vecstr_addsyms(vecstr *vlp,cc *objn,mainv syms) noe

	Arguments:
	op		pointer to VECSTR object
	objn		base-name for constructed symbol
	syms		array of pointees to particular parts of symbols

	Returns:
	>=0		number of elements loaded
	<0		error (system-return)

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>		/* for |strlen(3c)| */
#include	<usystem.h>
#include	<estrings.h>
#include	<localmisc.h>		/* |REALNAMELEN| */

#include	"vecstr.h"


/* local defines */

#define	SYMNAMELEN		REALNAMELEN


/* external subroutines */

extern "C" {
    extern int	vecstr_addsyms(vecstr *,cc *,mainv) noex ;
}


/* external variables */


/* forward references */


/* local structures */


/* local variables */


/* exported variables */


/* exported subroutines */

int vecstr_addsyms(vecstr *vlp,cc *objn,mainv syms) noex {
	cint		slen = SYMNAMELEN ;
	int		rs = SR_OK ;
	int		c = 0 ;
	char		sbuf[SYMNAMELEN + 1] ;
	for (int i = 0 ; (rs >= 0) && syms[i] ; i += 1) {
	    cchar	*sn = syms[i] ;
            if ((rs = sncpy(sbuf,slen,objn,"_",sn)) >= 0) {
		c += 1 ;
                rs = vlp->add(sbuf,rs) ;
            }
        } /* end for */
	return rs ;
}
/* end subroutine (vecstr_addsymss) */


