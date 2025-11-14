/* uiname SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* try to divine the best real name from a USERINFO object */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	uiname

	Description:
	We try to divine the best name that we can for the current
	user.  We do this simply by looking through some options
	contained in the USERINFO object.

	Synopsis:
	int uiname(userinfo *uip,char *rbuf,int rlen) noex

	Arguments:
	rbuf		supplied result buffer
	rlen		supplied result buffer length
	uip		pointer to USERINFO object

	Returns:
	>=0		length of resulting name
	<0		error (system-return)

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<userinfo.h>
#include	<sncpyx.h>
#include	<localmisc.h>


/* local defines */


/* imported namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int uiname(userinfo *uip,char *rbuf,int rlen) noex {
	int		rs = SR_OK ;
	int		len = 0 ;
	if (rbuf && uip) ylikely {
	    rs = SR_INVALID ;
	    rbuf[0] = '\0' ;
	    if (rlen >= 0) ylikely {
		cchar	*sp = nullptr ;
		rs = SR_NOTFOUND ;
	        if (uip->fullname && (uip->fullname[0] != '\0')) {
	            sp = uip->fullname ;
	        } else if (uip->name && (uip->name[0] != '\0')) {
	            sp = uip->name ;
	        } else if (uip->mailname && (uip->mailname[0] != '\0')) {
	            sp = uip->mailname ;
	        } else if (uip->username && (uip->username[0] != '\0')) {
	            sp = uip->username ;
	        }
	        if (sp) {
	            rs = sncpy(rbuf,rlen,sp) ;
		    len = rs ;
	        }
	    } /* end if (valid) */
	} /* end if (non-null) */
	return (rs >= 0) ? len : rs ;
}
/* end subroutine (uiname) */


