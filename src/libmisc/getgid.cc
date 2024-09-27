/* getgid SUPPORT */
/* lang=C++20 */

/* get the GID for a given group-name */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-08-20, David A­D­ Morano
	This was written to collect this code into one subroutine.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	getgid_name

	Description:
	This subroutine returns a GID for a specified group-name. 

	Synopsis:
	int getgid_name(cchar *np,int nl) noex

	Arguments:
	np		name of group to look up 
	nl		length of given string

	Returns:
	<0		error
	>=0		GID of given group name


	Name:
	getgid_def

	Description:
	This subroutine returns a GID for a specified groupname.
	A default GID is returned if the groupname does not exist.

	Synopsis:
	int getgid_def(cchar *gname,gid_t gid) noex

	Arguments:
	gname		groupname to lookup
	gid		default GID if lookup fails

	Returns:
	>=0		GID found or the default GID
	<0		error (system-return)

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<usystem.h>
#include	<mallocxx.h>
#include	<nulstr.h>
#include	<getax.h>
#include	<cfdec.h>
#include	<hasx.h>
#include	<localmisc.h>

#include	"getgid.h"


/* local defines */


/* local namespaces */


/* local typedefs */


/* external subroutines */


/* local variables */

constexpr gid_t		gidend = -1 ;


/* exported variables */


/* exported subroutines */

int getgid_name(cchar *sp,int sl) noex {
	int		rs = SR_FAULT ;
	int		rs1 ;
	int		gid = 0 ;
	if (sp) {
	    rs = SR_INVALID ;
	    if (sp[0] && (sl > 0)) {
	        nulstr	ns ;
	        cchar	*name{} ;
	        if ((rs = ns.start(sp,sl,&name)) >= 0) {
	            char	*grbuf{} ;
		    if ((rs = malloc_gr(&grbuf)) >= 0) {
	                cint	grlen = rs ;
		        {
	                    GROUP	gr{} ;
	                    rs = getgr_name(&gr,grbuf,grlen,name) ;
	                    gid = gr.gr_gid ;
		        }
	                rs1 = uc_free(grbuf) ;
	                if (rs >= 0) rs = rs1 ;
	            } /* end if (m-a-f) */
	            rs1 = ns.finish ;
	            if (rs >= 0) rs = rs1 ;
	        } /* end if (nulstr) */
	    } /* end if (valid) */
	} /* end if (non-null) */
	return (rs >= 0) ? gid : rs ;
}
/* end subroutine (getgid_name) */

int getgid_group(cchar *sp,int sl) noex {
	int		rs = SR_FAULT ;
	if (sp) {
	    rs = SR_INVALID ;
	    if (sp[0] && (sl > 0)) {
	        if (hasalldig(sp,sl)) {
	            if (int v{} ; (rs = cfdeci(sp,sl,&v)) >= 0) {
		        rs = v ;
	            }
	        } else {
	            rs = getgid_name(sp,sl) ;
	        }
	    } /* end if (valid) */
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (getgid_group) */

int getgid_def(cchar *gname,gid_t gid) noex {
	cint		rsn = SR_NOTFOUND ;
	int		rs = SR_FAULT ;
	if (gname) {
	    if ((rs = getgid_group(gname,-1)) == rsn) {
	        if (gid == gidend) {
	            rs = getgid() ;
	        } else {
	            rs = gid ;
	        }
	    }
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (getgid_def) */


