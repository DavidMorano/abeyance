/* bopenmod SUPPORT */
/* lang=C++20 */

/* "Basic I-O" package similiar to some other thing whose initials is "stdio" */
/* version %I% last-modified %G% */

#define	CF_DEBUGS	0		/* compile-time debug print-outs */

/* revision history:

	= 1998-07-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	We open with a minimum mode equal to the mode passed to the
	open call.  Otherwise everything is identical to |bopen(3b)|.

*******************************************************************************/


#include	<envstandards.h>	/* MUST be first to configure */
#include	<unistd.h>
#include	<fcntl.h>
#include	<cstring>
#include	<usystem.h>
#include	<hasx.h>
#include	<localmisc.h>

#include	"bfile.h"


/* local defines */


/* external subroutines */

#if	CF_DEBUGS
extern int	debugprintf(cchar *,...) ;
extern int	strlinelen(cchar *,int,int) ;
#endif


/* external variables */


/* forward references */


/* local variables */


/* exported subroutines */

int bopenmod(bfile *fp,cchar *fname,cchar *of,mode_t om) noex {
	int		rs ;

#if	CF_DEBUGS
	debugprintf("bopenmod: fname=%s\n",fname) ;
	debugprintf("bopenmod: of=%s\n",of) ;
#endif

	if ((rs = bopen(fp,fname,of,om)) >= 0) {
	    if (strchr(of,'M') == NULL) { /* not already done! */
	        if ((rs = hasallof(of,-1,"wc")) > 0) {
	            fp->of |= O_MINMODE ;
	            rs = uc_fminmod(fp->fd,om) ;
	        }
	    }
	    if (rs < 0)
	        bclose(fp) ;
	} /* end if (bopen) */

#if	CF_DEBUGS
	debugprintf("bopenmod: ret rs=%d\n",rs) ;
#endif

	return rs ;
}
/* end routine (bopenmod) */


