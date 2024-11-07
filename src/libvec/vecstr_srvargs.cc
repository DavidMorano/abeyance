/* vecstr_srvargs SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 */

/* process server file program arguments */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-09-01, David A­D­ Morano
	This subroutine was originally written for Rightcore Network
	Services (RNS).

	= 2017-11-30, David A­D­ Morano
	This code has been borrowed from the above.

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Name:
	vecpstr_srvargs

	Description:
	This subroutine is used to parse the server program arguments
	from an expanded (substituted) service file entry. Basically,
	we just "field-SHELL" out arguments and put them into the
	supplied vector-string object.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<climits>		/* for |UCHAR_MAX| + |CHAR_BIT| */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>		/* for |strlen(3c)| */
#include	<usystem.h>
#include	<field.h>
#include	<fieldterms.h>
#include	<localmisc.h>

#include	"vecstr.h"


/* local defines */


/* external subroutines */


/* externals variables */


/* forward references */

static int	vecstr_arger(vecstr *,cchar *) noex ;
static int	mkterms() noex ;


/* local structures */


/* local variables */

constexpr int		termsize = ((UCHAR_MAX+1)/CHAR_BIT) ;

static char		terms[termsize] ;


/* exported variables */


/* exported subroutines */

int vecstr_srvargs(vecstr *alp,cchar *abuf) noex {
	int		rs = SR_FAULT ;
	int		c = 0 ;
	if (alp && abuf) {
	    rs = SR_INVALID ;
	    if (abuf[0]) {
	        static cint	srs = mkterms() ;
	        if ((rs = srs) >= 0) {
		    rs = vecstr_arger(alp,abuf) ;
		    c = rs ;
	        } /* end if (terms) */
	    } /* end if (valid) */
	} /* end if (non-null) */
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (vecstr_srvargs) */


/* local subroutines */

static int vecstr_arger(vecstr *alp,cchar *abuf) noex {
	cint		alen = strlen(abuf) ;
	int		rs ;
	int		rs1 ;
	int		c = 0 ;
	char		*fbuf{} ;
	if ((rs = uc_malloc((alen+1),&fbuf)) >= 0) {
	    field	fsb ;
	    cint	flen = alen ;
	    if ((rs = field_start(&fsb,abuf,alen)) >= 0) {
	        int	fl ;
	        while ((fl = field_sharg(&fsb,terms,fbuf,flen)) >= 0) {
	            c += 1 ;
	            rs = vecstr_add(alp,fbuf,fl) ;
	            if (rs < 0) break ;
	        } /* end while */
	        rs1 = field_finish(&fsb) ;
		if (rs >= 0) rs = rs1 ;
	    } /* end if (field) */
	    rs1 = uc_free(fbuf) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (m-a) */
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (vecstr_arger) */

static int mkterms() noex {
	return fieldterms(terms,false,'\t',' ') ;
}
/* end subroutine (mkterms) */


