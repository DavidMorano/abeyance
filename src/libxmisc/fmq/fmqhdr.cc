/* fmqhdr SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* File-Message-Queue-Header (FMQ header) file */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-01, David A­D­ Morano
	This code was originally written.

	= 2017-08-17, David A­D­ Morano
	I enhanced to use |hasValidMagic()|.

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Group:
	fmqhdr_rd
	fmqhdr_wr

	Description:
	This subroutine reads from and write to a buffer which
	ropresents a FMQ file header when written out to a file.

	Synopsis:
	int fmqhdr_rd(pwdhdr *op,char *hbuf,int hlen) noex
	int fmqhdr_wr(pwdhdr *op,cchar *hbuf,int hlen) noex

	Arguments:
	- op		object pointer
	- hbuf		buffer containing object
	- hlen		length of buffer

	Returns:
	>=0		OK
	<0		error code (system-return)

*******************************************************************************/

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>		/* |memcpy(3c)| */
#include	<usystem.h>
#include	<endian.h>
#include	<mkmagic.h>
#include	<hasx.h>
#include	<localmisc.h>

#include	"fmqhdr.h"


/* local defines */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */

constexpr int		tabsize = (fmqhdr_overlast * szof(uint)) ;
constexpr int		magicsize = FMQHDR_MAGICSIZE ;
constexpr char		magicstr[] = FMQHDR_MAGICSTR ;


/* exported variables */


/* exported subroutines */

int fmqhdr_rd(fmqhdr *op,char *hbuf,int hlen) noex {
	int		rs = SR_FAULT ;
	int		len = 0 ;
	if (op && hbuf) {
	    int		bl = hlen ;
	    char	*bp = hbuf ;
	    if (bl >= (magicsize + 4)) {
	        if ((rs = mkmagic(bp,magicsize,magicstr)) >= 0) {
	            bp += magicsize ;
	            bl -= magicsize ;
	    	    memcpy(bp,op->vetu,4) ;
	    	    bp[0] = FMQHDR_VERSION ;
	    	    bp[1] = ENDIAN ;
	    	    bp += 4 ;
	    	    bl -= 4 ;
	    	    if (bl >= tabsize) {
	        	uint	*header = uintp(bp) ;
			header[fmqhdr_nmsg] = 	op->nmsg ;
			header[fmqhdr_wtime] = 	op->wtime ;
			header[fmqhdr_wcount] =	op->wcount ;
			header[fmqhdr_bsz] = 	op->bsz ;
			header[fmqhdr_blen] = 	op->blen ;
			header[fmqhdr_len] = 	op->len ;
			header[fmqhdr_ri] = 	op->ri ;
			header[fmqhdr_wi] = 	op->wi ;
	        	bp += tabsize ;
	        	bl -= tabsize ;
			len = (bp - hbuf) ;
	            } else {
	                rs = SR_OVERFLOW ;
	            }
	        } /* end if (mkmagic) */
	    } else {
	        rs = SR_OVERFLOW ;
	    }
	} /* end if (non-null) */
	return (rs >= 0) ? len : rs ;
}
/* end subroutine (fmqhdr_rd) */

int fmqhdr_wr(fmqhdr *op,cchar *hbuf,int hlen) noex {
	int		rs = SR_FAULT ;
	int		len = 0 ;
	if (op && hbuf) {
	    int		bl = hlen ;
	    cchar	*bp = hbuf ;
	    if ((bl > magicsize) && hasValidMagic(bp,magicsize,magicstr)) {
		rs = SR_OK ;
	        bp += magicsize ;
	        bl -= magicsize ;
	        /* read out the VETU information */
	        if (bl >= 4) {
	            memcpy(op->vetu,bp,4) ;
	            if (op->vetu[0] != FMQHDR_VERSION) {
	                rs = SR_PROTONOSUPPORT ;
		    }
	            if ((rs >= 0) && (op->vetu[1] != ENDIAN)) {
	                rs = SR_PROTOTYPE ;
		    }
	            bp += 4 ;
	            bl -= 4 ;
	            if ((rs >= 0) && (bl >= tabsize)) {
			const uint	*header = uintp(bp) ;
			op->nmsg = 	header[fmqhdr_nmsg] ; 
			op->wtime =	header[fmqhdr_wtime] ; 
			op->wcount =	header[fmqhdr_wcount] ; 
			op->bsz =	header[fmqhdr_bsz] ; 
			op->blen =	header[fmqhdr_blen] ; 
			op->len =	header[fmqhdr_len] ; 
			op->ri =	header[fmqhdr_ri] ; 
			op->wi =	header[fmqhdr_wi] ; 
	                bp += tabsize ;
	                bl -= tabsize ;
			len = (bp - hbuf) ;
	            } else {
	                rs = SR_ILSEQ ;
		    }
	        } else {
	            rs = SR_ILSEQ ;
	        } /* end if (ok) */
	    } else {
		rs = SR_ILSEQ ;
	    } /* end if (hasValidMagic) */
	} /* end if (non-null) */
	return (rs >= 0) ? len : rs ;
}
/* end subroutine (fmqhdr_wr) */

int fmqhdr::rd(char *rbuf,int rlen) noex {
    	return fmqhdr_rd(this,rbuf,rlen) ;
}

int fmqhdr::wr(cchar *wbuf,int wlen) noex {
    	return fmqhdr_wr(this,wbuf,wlen) ;
}


