/* mallcompactstr SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* memocy-allocate a de-quoted and compacted c-string */
/* version %I% last-modified %G% */

#define	CF_REG		1		/* use regular allocation */

/* revision history:

	= 1998-03-01, David A­D­ Morano
	This object module was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Object:
	mallcompactstr

	Description:
	This subroutine allocates (in regular heap memory) a 
	de-quoted and compacted c-string.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<usystem.h>
#include	<mallocstuff.h>
#include	<strn.h>
#include	<mkchar.h>
#include	<char.h>
#include	<localmisc.h>

#include	"mallcompactstr.h"

#pragma		GCC dependency	"mod/libutil.ccm"
#pragma		GCC dependency	"mod/asstr.ccm"

import libutil ;
import asstr ;

/* local defines */

#ifndef	CF_REG
#define	CF_REG		1		/* use regular allocation */
#endif


/* imported namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */

local int mallcompactstr_reg(cchar *,int,char **) noex ;
local int mallcompactstr_other(cchar *,int,char **) noex ;


/* local variables */

cbool		f_reg =		CF_REG ;


/* exported variables */


/* exported subroutines */

int mallcompactstr(cchar *sp,int sl,char **rpp) noex {
	int		rs = SR_FAULT ;
	int		sz ;
	int		len = 0 ; /* return-value */
	if (sp && rpp) {
	    if (sl < 0) sl = lenstr(sp) ;
	    if_constexpr (f_reg) {
		rs = mallcompactstr_reg(sp,sl,rpp) ;
		len = rs ;
	    } else {
		rs = mallcompactstr_reg(sp,sl,rpp) ;
		len = rs ;
	    } /* end if_constexpr (f_reg) */
	} /* end if (non-null) */
	return (rs >= 0) ? len : rs ;
}
/* end subroutine (mallcompactstr) */


/* local subroutines */

local int mallcompactstr_reg(cchar *sp,int sl,char **rpp) noex {
    	int		rs = SR_OK ;
        bool    	f_quote = false ;
        sz = (sl + 1) ;
        if (char *buf ; (rs = uc_malloc(sz,&buf)) >= 0) {
            char        *bp = buf ;
            while (sl > 0) {
                switch (cint ch = mkchar(*sp) ; ch) {
                case CH_DQUOTE:
                    f_quote = (! f_quote) ;
                     fallthrough ;
                    /* FALLTHROUGH */
                default:
                    if (f_quote || (! CHAR_ISWHITE(ch))) {
                        *bp++ = char(ch) ;
                    }
                    break ;
                } /* end switch */
                sp += 1 ;
                sl -= 1 ;
            } /* end while */
            *bp = '\0' ;
            len = (bp - buf) ;
        } /* end if (memory-allocation) */
        *rpp = (rs >= 0) ? buf : nullptr ;
	return (rs >= 0) ? len : rs ;
} /* end subroutine (mallcompactstr_reg) */

local int mallcompactstr_other(cchar *sp,int sl,char **rpp) noex {
    	int		rs ;
        if (asstr s ; (rs = asstr_start(&s)) >= 0) {
            bool        f_quote = false ;
            while ((rs >= 0) && (sl > 0)) {
                if (cint ch = mkchar(*sp) ; ch) {
                case CH_DQUOTE:
                    f_quote = (! f_quote) ;
                    fallthrough ;
                    /* FALLTHROUGH */
                default:
                    if (f_quote || (! CHAR_ISWHITE(ch))) {
                        rs = asstr_addchr(&s,ch) ;
                    }
                    break ;
                } /* end switch */
                sp += 1 ;
                sl -= 1 ;
            } /* end while */
            len = s.sl ;
            if (rpp) {
                *rpp = (rs >= 0) ? mallocstrw(s.sp,s.sl) : nullptr ;
            }
            rs1 = asstr_finish(&s) ;
            if (rs >= 0) rs = rs1 ;
        } /* end if (asstr) */
	return (rs >= 0) ? len : rs ;
} /* end subroutine (mallcompactstr_other) */


