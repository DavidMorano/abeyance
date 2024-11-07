/* vecstr_env SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++23 */

/* environment-type string handling */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-01, David A­D­ Morano
	This module was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	vecstr_envadd

	Description:
	This subroutine extends the VECSTR object to add a key-value
	pair to the vector list. Key-value pairs are two strings
	(the key and the value) joined with an intervening equal
	sign character ('='). Duplicate entries are checked for
	(after all, this was originally intended for environment
	variables) and are not added if already present.

	Synopsis:
	int vecstr_envadd(vecstr *op,cchar *kp,cchar *vp,int vl) noex

	Arguments:
	op		vecstr string to add to
	kp		pointer to key string
	vp		pointer to value string
	bl		length of value string

	Returns:
	>=0		OK
	<0		error (system-return)

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<climits>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstring>		/* for |strlen(3c)| */
#include	<usystem.h>
#include	<strn.h>
#include	<strwcpy.h>
#include	<char.h>
#include	<vstrkeycmpx.h>
#include	<localmisc.h>

#include	"vecstr.h"


/* local defines */

#ifndef	KEYBUFLEN
#define	KEYBUFLEN	120
#endif


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */

static int	vecstr_addwithin(vecstr *,cchar *,int) noex ;


/* local variables */


/* exported variables */


/* exported subroutines */

int vecstr_envadd(vecstr *op,cchar *kp,cchar *vp,int vl) noex {
	cint		rsn = SR_NOTFOUND ;
	int		rs = SR_FAULT ;
	int		i = INT_MAX ;
	if (op && kp) {
	    auto	vcmp = vstrkeycmp ;
	    nullptr_t	n = 0 ;
	    if ((rs = vecstr_finder(op,kp,vcmp,n)) == rsn) {
	        rs = vecstr_addkeyval(op,kp,-1,vp,vl) ;
	        i = rs ;
	    } /* end if (was not found) */
	} /* end if (non-null) */
	return (rs >= 0) ? i : rs ;
}
/* end subroutine (vecstr_envadd) */

int vecstr_envadds(vecstr *op,cchar *sp,int sl) noex {
	int		rs = SR_FAULT ;
	int		c = 0 ;
	if (op && sp) {
	    cchar	*tp ;
	    rs = SR_OK ;
	    if (sl < 0) sl = strlen(sp) ;
	    while ((tp = strnpbrk(sp,sl," \t\r\n,")) != nullptr) {
	        cint	cl = (tp - sp) ;
	        cchar	*cp = sp ;
	        if (cl > 0) {
	            rs = vecstr_addwithin(op,cp,cl) ;
	            if (rs > 0) c += 1 ;
	        } /* end if */
	        sl -= ((tp + 1) - sp) ;
	        sp = (tp + 1) ;
	        if (rs < 0) break ;
	    } /* end while */
	    if ((rs >= 0) && (sl > 0)) {
	        rs = vecstr_addwithin(op,sp,sl) ;
	        if (rs > 0) c += 1 ;
	    } /* end if */
	} /* end if (non-null) */
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (vecstr_envadds) */

int vecstr_envset(vecstr *op,cchar *kp,cchar *vp,int vl) noex {
	int		rs = SR_FAULT ;
	if (op && kp) {
	    auto	vcmp = vstrkeycmp ;
	    nullptr_t	n = 0 ;
	    if ((rs = vecstr_finder(op,kp,vcmp,n)) >= 0) {
	        vecstr_del(op,rs) ;
	    } else if (rs == SR_NOTFOUND) {
	        rs = SR_OK ;
	    }
	    if (rs >= 0) {
		rs = vecstr_addkeyval(op,kp,-1,vp,vl) ;
	    }
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (vecstr_envset) */

int vecstr_envget(vecstr *op,cchar *kp,cchar **rpp) noex {
	int		rs = SR_FAULT ;
	int		vl = 0 ;
	if (op && kp) {
	    cchar	*rp ;
	    if (rpp) *rpp = nullptr ;
	    if ((rs = vecstr_finder(op,kp,vstrkeycmp,&rp)) >= 0) {
	        cchar	*tp ;
	        if ((tp = strchr(rp,'=')) != nullptr) {
	            vl = strlen(tp + 1) ;
	        }
	        if (rpp) {
	            if (tp) {
	                *rpp = (tp + 1) ;
	            } else {
	                *rpp = (rp + strlen(rp)) ;
		    }
	        } /* end if */
	    } /* end if (finder) */
	} /* end if (non-null) */
	return (rs >= 0) ? vl : rs ;
}
/* end subroutine (vecstr_envget) */


/* private subroutines */

static int vecstr_addwithin(vecstr *op,cchar *sp,int sl) noex {
	int		rs = SR_OK ;
	int		f_added = false ;
	if (sl < 0) sl = strlen(sp) ;
	while ((sl > 0) && CHAR_ISWHITE(*sp)) {
	    sp += 1 ;
	    sl -= 1 ;
	}
	while ((sl > 0) && CHAR_ISWHITE(sp[sl - 1])) {
	    sl -= 1 ;
	}
	if (sl > 0) {
	    int		kl = sl ;
	    int		vl = 0 ;
	    int		f_separated = false ;
	    cchar	*kp = sp ;
	    cchar	*vp = nullptr ;
	    cchar	*tp ;
	    if ((tp = strnchr(sp,sl,'=')) != nullptr) {
	        vp = tp + 1 ;
	        vl = (kp + kl) - vp ;
	        kl = tp - kp ;
	        while ((kl > 0) && CHAR_ISWHITE(kp[kl - 1])) {
	            f_separated = true ;
	            kl -= 1 ;
	        }
	        while ((vl > 0) && CHAR_ISWHITE(*vp)) {
	            f_separated = true ;
	            vp += 1 ;
	            vl -= 1 ;
	        }
	        if (kl > 0) {
	            bool	f = false ;
	            char	keybuf[KEYBUFLEN + 1] ;
	            f = f || (! f_separated) ;
		    f = f || (kp[kl] == '\0') ;
		    f = f || (kp[kl] == '=') ;
	            if (! f) {
	                if (kl <= KEYBUFLEN) {
	                    strwcpy(keybuf,kp,kl) ;
	                    kp = keybuf ;
	                } else {
	                    rs = SR_TOOBIG ;
			}
	            } /* end if */
	            if (rs >= 0) {
		        cint		rsn = SR_NOTFOUND ;
			nullptr_t	n = 0 ;
			auto		vs = vstrkeycmp ;
	                if ((rs = vecstr_finder(op,kp,vs,n)) == rsn) {
	                    f_added = true ;
	                    if (f_separated) {
	                        rs = vecstr_addkeyval(op,kp,kl,vp,vl) ;
	                    } else {
	                        rs = vecstr_add(op,sp,sl) ;
			    }
	                } /* end if (was not found) */
	            } /* end if (ok) */
	        } /* end if (non-zero key) */
	    } /* end if (had a value even if NUL) */
	} /* end if (non-zero string) */
	return (rs >= 0) ? f_added : rs ;
}
/* end subroutine (vecstr_addwithin) */


