/* mkaddrfrom SUPPORT */
/* charset=ISO8859-1 */
/* lang=C20 */

/* try to divine the best "from" address from a raw source string */
/* version %I% last-modified %G% */

#define	CF_MASSAGE	0		/* allow for massaging */

/* revision history:

	= 1998-06-01, David A­D­ Morano
	This code piece was part of the |pcsmailcheck(3pcs)|
	subroutine and I pulled it out to make a subroutine that
	can be used in multiple places.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	mkaddrfrom

	Description:
	This subroutine extracts the "best" from-address out of an
	ema-type of address specification (given in raw string
	form).

	Synopsis:
	int mkaddrfrom(char *fbuf,int flen,cchar *sp,int sl) noex

	Arguments:
	fbuf		result buffer
	flen		result buffer length
	sp		source string
	sl		source string length

	Returns:
	>=0		length of resulting string
	<0		error code (system-return)

	Notes:
	+ Massaging the result:
	In the old days, before header fields could be encoded in
	wacko ways, the result here was the final result.  It could
	therefore be massaged to get rid of some cruft that certain
	mailers (who will remain nameless -- for now) would add to
	the field string value.  But now-a-days, the result here
	could still be wackily encoded, so massaging will at best
	do nothing, and at worst break the encoded format.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<estrings.h>
#include	<ema.h>
#include	<isoneof.h>
#include	<localmisc.h>

#include	"mkx.h"

import libutil ;

/* local defines */

#ifndef	CF_MASSAGE
#define	CF_MASSAGE	0		/* allow for massaging */
#endif


/* imported namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */

enum atypes {
	atype_comment,
	atype_address,
	atype_route,
	atype_overlast
} ;


/* forward references */

static int	mkaddrx(char *,int,cchar *,int) noex ;
static int	emaentry_bestfrom(ema_ent *,char *,int) noex ;

static bool	isBadAddr(int) noex ;


/* local variables */

static constexpr int	rsbadaddr[] = {
	SR_INVALID,
	SR_DOM,
	0
} ;

cbool		f_massage = CF_MASSAGE ;


/* exported variables */


/* exported subroutines */

int mkaddrfrom(char *fbuf,int flen,cchar *sp,int sl) noex {
	int		rs = SR_FAULT ;
	int		len = 0 ;
	if (fbuf && sp) ylikely {
	    rs = SR_INVALID ;
	    fbuf[0] = '\0' ;
	    if (sp[0]) ylikely {
	        if (sl < 0) sl = lenstr(sp) ;
	        if (sl > 0) ylikely {
	            rs = mkaddrx(fbuf,flen,sp,sl) ;
		    len = rs ;
	        } /* end if (non-zero source) */
	    } /* end if (valid) */
	} /* end if (non-null) */
	return (rs >= 0) ? len : rs ;
}
/* end subroutine (mkaddrfrom) */


/* local subroutines */

static int mkaddrx(char *rbuf,int rlen,cchar *sp,int sl) noex {
	int		rs ;
	int		rs1 ;
	int		len = 0 ;
	if (ema a ; (rs = ema_start(&a)) >= 0) ylikely {
            if ((rs = ema_parse(&a,sp,sl)) >= 0) ylikely {
		ema_ent		*ep ;
                auto        eg = ema_get ;
                cint        rsn = SR_NOTFOUND ;
                for (int i = 0 ; (rs1 = eg(&a,i,&ep)) >= 0 ; i += 1) {
                    rs = emaentry_bestfrom(ep,rbuf,rlen) ;
                    len = rs ;
                    if (rs != 0) break ;
                } /* end while (ema_get) */
                if ((rs >= 0) && (rs1 != rsn)) rs = rs1 ;
            } else if (isBadAddr(rs)) {
                rs = SR_OK ;
            } /* end if (ema_parse) */
            rs1 = ema_finish(&a) ;
            if (rs >= 0) rs = rs1 ;
        } /* end if (ema) */
	return (rs >= 0) ? len : rs ;
}
/* end subroutine (mkaddrx) */

static int emaentry_bestfrom(ema_ent *ep,char *fbuf,int flen) noex {
	int		rs = SR_OK ;
	int		nl = 0 ;
	int		atype = -1 ;
	int		len = 0 ;
	cchar		*rp = nullptr ;
	if ((rp == nullptr) || (nl == 0)) {
	    if (ep->cp != nullptr) {
	        atype = atype_comment ;
	        nl = sfshrink(ep->cp,ep->cl,&rp) ;
	    }
	}
	if ((rp == nullptr) || (nl == 0)) {
	    if (ep->ap != nullptr) {
	        atype = atype_address ;
	        nl = sfshrink(ep->ap,ep->al,&rp) ;
	    }
	}
	if ((rp == nullptr) || (nl == 0)) {
	    if (ep->rp != nullptr) {
	        atype = atype_route ;
	        nl = sfshrink(ep->rp,ep->rl,&rp) ;
	    }
	}
	if_constexpr (f_massage) {
	    if ((rp != nullptr) && (nl > 0)) {
	        int	cl ;
	        cchar	*cp ;
	        switch (atype) {
	        case atype_comment:
	            if ((cl = sfsubstance(rp,nl,&cp)) > 0) {
	                rs = snwcpy(fbuf,flen,cp,cl) ;
	                len = rs ;
	            }
	            break ;
	        case atype_address:
	            rs = mkaddrdisp(fbuf,flen,rp,nl) ;
	            len = rs ;
	            break ;
	        case atype_route:
	            rs = snwcpy(fbuf,flen,rp,nl) ;
	            len = rs ;
		    break ;
	        } /* end switch */
	    } /* end if (positive) */
	} else {
	    if ((rp != nullptr) && (nl > 0)) ylikely {
	        switch (atype) {
	        case atype_comment:
	        case atype_address:
	        case atype_route:
	            rs = snwcpy(fbuf,flen,rp,nl) ;
	            len = rs ;
		    break ;
	        } /* end switch */
	    } /* end if (positive) */
	} /* end if_constexpr (f_massage) */
	return (rs >= 0) ? len : rs ;
}
/* end subroutine (emaentry_bestfrom) */

static bool isBadAddr(int rs) noex {
	return isOneOf(rsbadaddr,rs) ;
}
/* end subroutine (emaentry_bestfrom) */


