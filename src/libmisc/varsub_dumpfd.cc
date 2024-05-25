/* varsub_dumpfd SUPPORT */
/* lang=C++20 */

/* dump the substitution variables of the object */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-05-23, David A­D­ Morano
        This subroutine was written to provide some helper support for
        substitution setup.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<usystem.h>
#include	<localmisc.h>

#include	"varsub.h"


/* local defines */


/* external subroutines */

extern "C" {
    extern int	fdprintf(int,...) noex ;
}


/* local variables */


/* exported variables */


/* exported subroutines */

#ifdef	COMMENT
int varsub_dumpfd(varsub *op,int fd) noex {
	int		rs = SR_FAULT ;
	if (op) {
	    if (vshp->vsa != nullptr) {
	        varsub_ent	*vsa = vshp->vsa ;
	        if (fd < 0) fd = egetfd() ;
	        for (int i = 0 ; i < vshp->i ; i += 1) {
	            if (vsa[i].kp == nullptr) {
	                fdprintf(fd,"varsub_dumpfd nullptr\n") ;
	            } else {
	                fdprintf(fd,"varsub_dumpfd key=%t val=%t\n",
	                vsa[i].kp,vsa[i].klen,
	                vsa[i].vp,vsa[i].vlen) ;
	            }
	        } /* end for */
	    } /* end if (non-null) */
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (varsub_dumpfd) */
#else /* COMMENT */
int varsub_dumpfd(varsub *op,int fd) noex {
	int		rs = SR_FAULT ;
	if (op) {
	    rs = SR_BADFD ;
	    if (fd >= 0) {
	        rs = SR_OK ;
	    }
	}
	return rs ;
}
#endif /* COMMENT */


