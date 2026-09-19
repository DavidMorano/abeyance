/* fdt SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* File-Descriptor-Table */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services
	(RNS).

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* MUST be first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<vecobj.h>
#include	<localmisc.h>

#include	"fdt.h"
#include	"ucb.h"


/* local defines */


/* local namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */

static int	fdt_get(FDT *,int,UCB **) noex ;
static int	fdt_free(FDT *,int) noex ;


/* local variables */

static FDT	fdt ;


/* exported variables */


/* private subroutines */

static int fdt_ctor(FDT *op) noex {
    	cnullptr	np{} ;
    	int		rs = SR_OK ;
	if (op->magic != FDT_MAGIC) {
	    if ((op->flp = new(nothrow) vecobj) != np) {
		vecobj	*flp = op->flp ;
	        cint sz = szof(FDT_ENT) ;
	        cint ne = 10 ;
	        if ((rs = flp->start(sz,ne,0)) >= 0) {
		    op->magic = FDT_MAGIC ;
		}
		if (rs < 0) {
		    delete op->flp ;
		    op->flp = nullptr ;
		} /* end if (error) */
	    } /* end if (new-vecobj) */
	} /* end if (initialization) */
} /* end subroutine (fdt_ctor) */

static int fdt_alloc(FDT *op,int fd,UCB *rpp) noex {
	int		rs = SR_FAULT ;
	int		sz ;
	if (op) {
	    if ((rs = fdt_ctor(op)) >= 0) {
		vecobj	*flp = op->flp ;
	        while (fdt_getentry(op,fd,&ep) >= 0) {
		   flp->del(0) ;
	        }
	        for (int i = 0 ; flp->get(i,&ep) >= 0 ; i += 1) {
	            if (ep) {
		        if (ep->fd == fd) {
			    rs = 0 ;
		        }
	            }
	        } /* end for */
	    } /* end if (ctor) */
	} /* end if (null) */
	return rs ;
}
/* end subroutine (fdt_alloc) */

static int fdt_getentry(FDT *op,int fd,FDT_ENT **rpp) noex {
	FDT_ENT		*ep = nullptr ;
	vecobj		*flp = &op->entries ;
	int		rs ;
	*rpp = nullptr ;
	for (int i = 0 ; (rs = flp->get(i,&ep)) >= 0 ; i += 1) {
	    if (ep) {
		if (ep->fd == fd) break ;
	    }
	} /* end for */
	if (rs >= 0) *rpp = ep ;
	return rs ;
}
/* end subroutine (fdt_getentry) */


