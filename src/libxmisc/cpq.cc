/* cpq SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* Circular-Pointer-Queue */
/* a regular (no-frills) pointer queue */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-01, David A­D­ Morano
	This code was modeled after assembly.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Object:
	cpq

	Description:
	This is a regular, pointer based, no-frills circular doubly
	linked list queue.  Note that this object CANNOT be moved
	(copied) since there may be pointers pointing back at the
	list head (located in the object).

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>		/* POSIX® */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */

#include	"cpq.h"


/* local defines */


/* local namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int cpq_start(cpq *qhp) noex {
	if (qhp == nullptr) return SR_FAULT ;

	qhp->next = (cpq_ent *) qhp ;
	qhp->prev = (cpq_ent *) qhp ;

	return SR_OK ;
} /* end subroutine (cpq_start) */

int cpq_finish(cpq *qhp) noex {
	if (qhp == nullptr) return SR_FAULT ;

	qhp->next = nullptr ;
	qhp->prev = nullptr ;

	return SR_OK ;
} /* end subroutine (cpq_finish) */

int cpq_ins(cpq *qhp,cpq_ent *ep) noex {
	cpq_ent		*hp = (cpq_ent *) qhp ;
	cpq_ent		*ep2 ;

	if (qhp == nullptr) return SR_FAULT ;

	ep2 = hp->prev ;
	ep2->next = ep ;
	ep->next = hp ;
	ep->prev = ep2 ;
	qhp->prev = ep ;

	return SR_OK ;
} /* end subroutine (cpq_ins) */

int cpq_insgroup(cpq *qhp,cpq_ent *gp,int sz,int n) noex {
	if (qhp == nullptr) return SR_FAULT ;

	if (n >= 1) {
	    cpq_ent	*hp = (cpq_ent *) qhp ;
	    cpq_ent	*ep, *pep, *nep ;
	    caddr_t	p = (caddr_t) gp ;
	    pep = hp->prev ;
	    for (int i = 0 ; i < n ; i += 1) {
	        ep = (cpq_ent *) p ;
	        pep->next = ep ;
	        ep->prev = pep ;
	        pep = ep ;
	        p += sz ;
	    } /* end for */
	    pep->next = hp ;
	    qhp->prev = pep ;
	} /* end if */

	return SR_OK ;
} /* end subroutine (cpq_insgroup) */

int cpq_rem(cpq *qhp,cpq_ent **epp) noex {
	cpq_ent		*hp = (cpq_ent *) qhp ;
	cpq_ent		*ep, *ep2 ;

	if (qhp == nullptr) return SR_FAULT ;
	if (qhp->next == hp) return SR_NOENT ;

	ep = qhp->next ;
	ep2 = ep->next ;
	ep2->prev = hp ;
	qhp->next = ep2 ;

	*epp = ep ;

	return (qhp->next != hp) ? 1 : 0 ;
} /* end subroutine (cpq_rem) */

int cpq_remtail(cpq *qhp,cpq_ent **epp) noex {
	cpq_ent		*hp = (cpq_ent *) qhp ;
	cpq_ent		*ep, *ep2 ;

	if (qhp == nullptr) return SR_FAULT ;
	if (qhp->next == hp) return SR_NOENT ;

	ep = qhp->prev ;
	ep2 = ep->prev ;
	ep2->next = hp ;
	qhp->prev = ep2 ;

	*epp = ep ;

	return (qhp->next != hp) ? 1 : 0 ;
} /* end subroutine (cpq_remtail) */

int cpq_gettail(cpq *qhp,cpq_ent **epp) noex {
	cpq_ent		*hp = (cpq_ent *) qhp ;
	cpq_ent		*ep ;
	cpq_ent		*ep2 ;

	if (qhp == nullptr) return SR_FAULT ;
	if (qhp->next == hp) return SR_NOENT ;

	*epp = qhp->prev ;

	return (qhp->next != hp) ? 1 : 0 ;
} /* end subroutine (cpq_gettail) */

int cpq_audit(cpq *qhp) noex {
	cpq_ent		*hp = (cpq_ent *) qhp ;
	cpq_ent		*ep, *ep2 ;
	int		rs = SR_OK ;

	if (qhp == nullptr) return SR_FAULT ;

	if ((qhp->next == nullptr) || (qhp->prev == nullptr))
	    return SR_NOTOPEN ;

	ep = qhp->next ;
	ep2 = hp ;
	while ((rs >= 0) && (ep != hp)) {

	    if (ep->prev == ep2) {
	        ep2 = ep ;
	        ep = ep->next ;
	    } else
		rs = SR_BADFMT ;

	} /* end while */

	if ((rs >= 0) && (ep->prev != ep2))
	    rs = SR_BADFMT ;

	return rs ;
} /* end subroutine (cpq_audit) */


