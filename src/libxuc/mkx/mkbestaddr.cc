/* mkaddrbest SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* get the "best" address out of an EMA type address specification */
/* version %I% last-modified %G% */


/* revision history:

	= 1999-02-01, David A­D­ Morano
	This code was part of another subroutine and I pulled it
	out to make a subroutine that can be used in multiple places.

*/

/* Copyright © 1999 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	mkaddrbest

	Description:
	This subroutine extracts the "best" address out of an
	EMA-type of address specification (given in raw string
	form).

	Synopsis:
	int mkaddrbest(char *rbuf,int rlen,cchar *sp,int sl) noex

	Arguments:
	rbuf		result buffer
	rlen		result buffer length
	sp		source string
	sl		source string length

	Returns:
	>=0		length of resulting string
	<0		error code (system-return)

*******************************************************************************/

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<snwcpy.h>
#include	<sfx.h>
#include	<ema.h>
#include	<localmisc.h>

#include	"mkx.h"


/* local defines */


/* imported namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local subroutines */


/* exported variables */


/* exported subroutines */

int mkaddrbest(char *rbuf,int rlen,cchar *abuf,int alen) noex {
	int		rs = SR_FAULT ;
	int		rs1 ;
	int		len = 0 ;
	if (rbuf && abuf) ylikely {
	    rbuf[0] = '\0' ;
	    if (ema a ; (rs = ema_start(&a)) >= 0) ylikely {
	        if ((rs = ema_parse(&a,abuf,alen)) >= 0) ylikely {
	            ema_ent	*ep ;
	            for (int i = 0 ; ema_get(&a,i,&ep) >= 0 ; i += 1) {
	                if (ep) {
	                    int		sl = 0 ;
	                    cchar	*sp = nullptr ;
			    if (sl == 0) {
	                        if ((ep->rp != nullptr) && (ep->rl > 0)) {
				    sp = ep->rp ;
				    sl = ep->rl ;
			        }
			    }
			    if (sl == 0) {
	                        if ((ep->ap != nullptr) && (ep->al > 0)) {
				    sp = ep->ap ;
				    sl = ep->al ;
	                        }
			    }
	                    if (sl > 0) ylikely {
			        cchar	*ap ;
			        if (int al ; (al = sfshrink(sp,sl,&ap)) > 0) {
	                            rs = snwcpy(rbuf,rlen,ap,al) ;
	                            len = rs ;
			        }
	                    }
	                } /* end if (non-null) */
		        if (len > 0) break ;
		        if (rs < 0) break ;
	            } /* end for */
	        } /* end if (parse) */
	        rs1 = ema_finish(&a) ;
	        if (rs >= 0) rs = rs1 ;
	    } /* end if (ema) */
	} /* end if (non-null) */
	return (rs >= 0) ? len : rs ;
}
/* end subroutine (mkaddrbest) */


