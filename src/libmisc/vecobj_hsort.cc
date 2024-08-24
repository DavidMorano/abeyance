/* vecobj_hsort SUPPORT */
/* lang=C++20 */

/* vector object list operations (heapsort) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-12-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This subroutine extends the VECOBJ object to add the
	capability to get the vector-list heap-sorted rather than
	quick-sorted as would be done normally.  There are rare
	occassions when a heap sort (or some sort other than
	Quick-Sort) is desirable.  Those occassions are generally
	only when a Quick-Sort is known to perform poorly (like
	when all of the data is already sorted).

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<cstdlib>
#include	<cstring>
#include	<usystem.h>
#include	<localmisc.h>

#include	"vecobj.h"


/* local defines */


/* external subroutines */

extern "C" {
   typedef int (*heapsort_cf)(cvoid *,cvoid *) noex ;
}


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int vecobj_hsort(vecobj *op,vecobj_vcf cmpfunc) noex {
	int		rs = SR_FAULT ;
	if (op && cmpfunc) {
	    rs = SR_NOTOPEN ;
	    if (op->va) {
		rs = SR_OK ;
	        if (! op->f.issorted) {
	            op->f.issorted = true ;
	            if (op->c > 1) {
			heapsort_cf	hcf = heapsort_cf(cmpfunc) ;
			cint		esz = op->esize ;
	                heapsort(op->va,op->i,esz,hcf) ;
	            }
	        } /* end if (sorting needed) */
		rs = op->c ;
	    } /* end if (open) */
	} /* end if (magic) */
	return rs ;
}
/* end subroutine (vecobj_hsort) */


