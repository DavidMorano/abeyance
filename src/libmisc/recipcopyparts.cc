/* recip_copyparts SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* copies parts of a file to another file */
/* version %I% last-modified %G% */


/* revision history:

	= 1990-07-01, David A­D­ Morano
	This program was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Name:
	copyparts

	Description:
	This subroutine copies part of one file (specified by
	a container type) to another file.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<sys/param.h>
#include	<unistd.h>
#include	<fcntl.h>		/* |u_seek(3u)| */
#include	<ctime>
#include	<csignal>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<usystem.h>
#include	<vecitem.h>
#include	<bfile.h>
#include	<mkpathx.h>
#include	<strwcpy.h>
#include	<localmisc.h>

#include	"recip_copyparts.h"


/* local defines */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int copyparts(recip *rp,int tfd,int sfd) noex {
	off_t		uoff ;
	uint		off ;
	int		rs = SR_OK ;
	int		i, clen, tlen ;
	int		len ;
	int		f_contiguous ;
	/* first, figure out if we can do a contiguous copy or not */
	off = 0 ;
	clen = 0 ;
	vecitem		*elp = rp->mdp ;
	recip_ent	*mop{} ;
	for (i = 0 ; (rs = elp->get(i,&mop)) >= 0 ; i += 1) {
	    if (mop) {
	        if (off != mop->offset) break ;
	        off += mop->mlen ;
	        clen += mop->mlen ;
	    }
	} /* end for */

	f_contiguous = (rs == SR_NOTFOUND) ;

	/* OK, do the copying according to whether contiguous or not */

	if (! f_contiguous) {

	    off = 0 ;
	    tlen = 0 ;
	    for (i = 0 ; elp->get(i,&mop) >= 0 ; i += 1) {
	        if (mop) {
	            rs = 0 ;
	            if (mop->mlen > 0) {
	                if (mop->offset != off) {
	                    off = mop->offset ;
			    uoff = off ;
	                    rs = u_seek(tfd,uoff,SEEK_SET) ;
	                }
	                if (rs >= 0) {
	                    rs = uc_copy(tfd,sfd,mop->mlen) ;
			    len = rs ;
		        }
	            }
	            if (len > 0) {
	                off += len ;
	                tlen += len ;
	            }
		} /* end if (non-null) */
		if (rs < 0) break ;
	    } /* end for */

	} else {
	    rs = SR_OK ;
	    if (i > 0) {
	        rs = uc_copy(tfd,sfd,clen) ;
	        tlen = rs ;
	    }
	}

	return (rs >= 0) ? tlen : rs ;
}
/* end subroutine (recip_copyparts) */


