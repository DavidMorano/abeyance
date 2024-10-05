/* bopenprog SUPPORT */
/* lang=C++20 */

/* "Basic I-O" package */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-07-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998,1999 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Open a "program" and pass the standard output to a BFILE
	object as if it was opened by BFILE itself.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/param.h>
#include	<sys/stat.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<climits>		/* |INT_MAX| */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<algorithm>		/* |min(3c++)| + |max(3c++)| */
#include	<usystem.h>
#include	<bufsizevar.hh>
#include	<sysval.hh>
#include	<stdfnames.h>
#include	<getfdfile.h>
#include	<snx.h>
#include	<cfdec.h>
#include	<intsat.h>
#include	<intceil.h>
#include	<mkchar.h>
#include	<ischarx.h>
#include	<localmisc.h>

#include	"bfile.h"


/* local defines */


/* imported namespaces */

using std::nullptr_t ;			/* type */
using std::min ;			/* subroutine-template */
using std::max ;			/* subroutine-template */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int bopenprog(bfile *op,cc *pname,cc *os,mainv argv,mainv envv) noex {
	int		rs = SR_FAULT ;
	if (op && pname && os) {
	    cint	osl = strlen(os) ;
	    cmode	om = 0 ;
	    memclear(op) ;
	    rs = SR_INVALID ;
	    if (pname[0]) {
		char	nos[(osl+2)] ;
		if ((rs = sncpy(nos,(osl+2),"p",os)) >= 0) {
		    sub_bopen	bo(op,pname,nos,om,-1) ;
		    rs = bo(argv,envv) ;
		}
	    } /* end if (valid) */
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (bopenprog) */

int bopenprog(bfile *op,cc *pname,cc *os,mainv argv,mainv envv) noex {
	int		rs = SR_OK ;
	int		oflags = 0 ;
	int		boflags = 0 ;
	cchar		*args[2] ;
	char		progfname[MAXPATHLEN+1] ;

	if (op == nullptr) return SR_FAULT ;
	if (pname == nullptr) return SR_FAULT ;
	if (os == nullptr) return SR_FAULT ;

	if (pname[0] == '\0') return SR_INVALID ;
	if (os[0] == '\0') return SR_INVALID ;

	memclear(op) ;
	op->fd = -1 ;
	op->f.notseek = true ;

	oflags = mkoflags(os,&boflags) ;
	oflags |= O_CLOEXEC ;

	if (argv == nullptr) {
	    int	i = 0 ;
	    argv = args ;
	    args[i++] = pname ;
	    args[i] = nullptr ;
	}

	if (strchr(pname,'/') == nullptr) {
	    rs = findfilepath(nullptr,progfname,pname,X_OK) ;
	    if (rs > 0) pname = progfname ;
	}

	if (rs >= 0) {
	if ((rs = uc_openprog(pname,oflags,argv,envv)) >= 0) {
	    op->fd = rs ;
	    if ((rs = bfile_opts(op,oflags,0)) >= 0) {
		    cint	bsize = MIN(LINEBUFLEN,2048) ;
	            if ((rs = bfile_bufbegin(op,bsize)) >= 0) {
			op->of = oflags ;
		        op->bm = bfilebm_line ;
	                op->magic = BFILE_MAGIC ;
	            } /* end if (buffer-allocation) */
	    }
	    if (rs < 0) {
		u_close(op->fd) ;
		op->fd = -1 ;
	    }
	} /* end if (opened) */
	} /* end if (ok) */

	return rs ;
}
/* end subroutine (bopenprog) */


