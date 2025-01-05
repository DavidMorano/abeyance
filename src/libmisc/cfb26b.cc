/* cfb26 SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 */

/* convert a base-26 digit string to its binary integer value */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-10-01, David A­D­ Morano
	This subroutine was written adapted from assembly.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Group:
	cfb26

	Description:
	Subroutines to convert base-26 strings to binary integers.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<climits>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>		/* for |strlen(3c)| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<ucvariables.hh>
#include	<stdintx.h>
#include	<sfx.h>
#include	<char.h>
#include	<ischarx.h>
#include	<localmisc.h>

#include	"cfb26.h"


/* local defines */

#define MAXB26DIG_I	7		/* decimal digits in 'int' */
#define MAXB26DIG_UI	7		/* decimal digits in 'uint' */
#define MAXB26DIG_L	14		/* decimal digits in 'long' */
#define MAXB26DIG_UL	14		/* decimal digits in 'ulong' */
#define MAXB26DIG_LL	28		/* decimal digits in 'longlong ' */
#define MAXB26DIG_ULL	28		/* decimal digits in 'ulonglong ' */

#undef	CFB26_WEIGHT
#define	CFB26_WEIGHT	26


/* local namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */

namespace {
    struct info {
	ulonglong	result ;	/* result */
	ulonglong	imask ;		/* inverse overflow mask */
	int		maxdigs ;	/* maximum digits */
	int		st ;		/* signed type */
    } ; /* end struct (info) */
}


/* forward references */

static int	icfb26(info *,cchar *,int) noex ;
static bool	isbad(bool,int) noex ;


/* local variables */


/* exported variables */


/* exported subroutines */

int cfb26i(cchar *sp,int sl,int *rp) noex {
	int		rs = SR_FAULT ;
	if (sp && rp) {
	    info	is ;
	    is.maxdigs = MAXB26DIG_I ;
	    is.st = true ;
	    is.imask = (~ valuelimit.imax) ;
	    rs = icfb26(&is,sp,sl) ;
	    *rp = int(is.result) ;
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (cfb26i) */

int cfb26l(cchar *sp,int sl,long *rp) noex {
	int		rs = SR_FAULT ;
	if (sp && rp) {
	    info	is ;
	    is.maxdigs = MAXB26DIG_L ;
	    is.st = true ;
	    is.imask = (~ valuelimit.lmax) ;
	    rs = icfb26(&is,sp,sl) ;
	    *rp = long(is.result) ;
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (cfb26l) */

int cfb26ll(cchar *sp,int sl,longlong *rp) noex {
	int		rs = SR_FAULT ;
	if (sp && rp) {
	    info	is ;
	    is.maxdigs = MAXB26DIG_LL ;
	    is.st = true ;
	    is.imask = (~ valuelimit.llmax) ;
	    rs = icfb26(&is,sp,sl) ;
	    *rp = longlong(is.result) ;
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (cfb26ll) */

int cfb26ui(cchar *sp,int sl,uint *rp) noex {
	int		rs = SR_FAULT ;
	if (sp && rp) {
	    info	is ;
	    is.maxdigs = MAXB26DIG_UI ;
	    is.st = false ;
	    is.imask = (~ valuelimit.imax) ;
	    rs = icfb26(&is,sp,sl) ;
	    *rp = uint(is.result) ;
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (cfb26ui) */

int cfb26ul(cchar *sp,int sl,ulong *rp) noex {
	int		rs = SR_FAULT ;
	if (sp && rp) {
	    info	is ;
	    is.maxdigs = MAXB26DIG_UL ;
	    is.st = false ;
	    is.imask = (~ valuelimit.lmax) ;
	    rs = icfb26(&is,sp,sl) ;
	    *rp = ulong(is.result) ;
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (cfb26ul) */

int cfb26ull(cchar *sp,int sl,ulonglong *rp) noex {
	int		rs = SR_FAULT ;
	if (sp && rp) {
	    info	is ;
	    is.maxdigs = MAXB26DIG_ULL ;
	    is.st = false ;
	    is.imask = (~ valuelimit.llmax) ;
	    rs = icfb26(&is,sp,sl) ;
	    *rp = ulonglong(is.result) ;
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (cfb26ull) */


/* local subroutines */

static int icfb26(info *ip,cchar *asp,int asl) noex {
	int		rs = SR_INVALID ;
	cchar		*sp{} ;
	ip->result = 0 ;
	if (int sl ; (sl = sfshrink(asp,asl,&sp)) > 0) {
            ulonglong       val = 0 ;
            ulonglong       weight = 1 ;
            int             n = 0 ;
            int		    cb ;
            int             i{} ;
            bool            fuc = CHAR_ISUC(sp[sl-1]) ;
    /* convert possible digits */
            cb = (fuc) ? 'A' : 'a' ;
	    rs = SR_OK ;
            for (i = (sl - 1) ; (rs >= 0) && (i >= 0) ; i -= 1) {
                cint	ch = sp[i] ;
                if (isplusminus(ch) || CHAR_ISWHITE(ch)) break ;
    /* bad digits? */
                if (isbad(fuc,ch)) {
                    rs = SR_INVALID ;
                }
                if (rs >= 0) {
                    n += 1 ;
                    if ((n > ip->maxdigs) && (ch != cb)) {
                        rs = SR_OVERFLOW ;
                    }
                    if (rs >= 0) {
			const ulonglong		im = ip->imask ;
                        if (n == ip->maxdigs) {
                            ulonglong       adder = ((ch - cb) * weight) ;
                            bool	    f_msb1 = (val & im) ? 1 : 0 ;
                            bool	    f_msb2 = (adder & im) ? 1 : 0 ;
                            bool	    f_msbr ;
                            val += adder ;
                            f_msbr = (val & im) ;
                            if (ip->st) {
                                if (f_msb1 || f_msb2 || f_msbr) {
                                    rs = SR_OVERFLOW ;
			        }
                            } else {
				bool	f = false ;
                                f = f || (f_msb1 && f_msb2) ;
                                f = f || ((f_msb1 || f_msb2) && (! f_msbr)) ;
                                if (f) rs = SR_OVERFLOW ;
                            }
                        } else {
                            val += ((ch - cb) * weight) ;
                        }
                        weight *= CFB26_WEIGHT ;
                    } /* end if */
                } /* end if */
            } /* end for */
            if (rs >= 0) {
                while ((i > 0) && CHAR_ISWHITE(sp[i])) {
                    i -= 1 ;
                }
                if ((i >= 0) && (sp[i] == '-')) {
                    val = (- val) ;
                }
                ip->result = val ;
            } /* end if */
	} /* end if (valid) */
	return rs ;
}
/* end subroutine (icfb26) */

static bool isbad(bool fuc,int ch) noex {
	bool		f ;
	if (fuc) {
	    f = (ch < 'A') || (ch > 'Z') ;
	} else {
	    f = (ch < 'a') || (ch > 'z') ;
	}
	return f ;
}
/* end subroutine (isbad) */


