/* termcmd SUPPORT */
/* lang=C++20 */

/* clear out the TERMCMD object */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	termcmd_clear

	Descrption:
	This subroutine clears out the TERMCMD object.

	Synopsis:
	int termcmd_clear(termcmd *ckp) noex

	Arguments:
	ckp		TERMCMD object pointer (for clearing)

	Returns:
	>=0		OK
	<0		error (system-return)

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<usystem.h>
#include	<ascii.h>
#include	<cfdec.h>
#include	<localmisc.h>

#include	"termcmd.h"


/* local defines */


/* external subroutines */


/* external variables */


/* local structures */


/* forward subroutines */


/* local variables */


/* exported variables */


/* exported subroutines */

int termcmd_clear(termcmd *ckp) noex {
	int		rs = SR_FAULT ;
	if (ckp) {
	    ckp->type = 0 ;
	    ckp->name = 0 ;
	    ckp->istr[0] = '\0' ;
	    ckp->dstr[0] = '\0' ;
	    ckp->f.fpriv = false ;
	    ckp->f.iover = false ;
	    ckp->f.dover = false ;
	    for (int i = 0 ; i < TERMCMD_NP ; i += 1) {
	        ckp->p[i] = TERMCMD_PEOL ;
	    }
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (termcmd_clear) */


