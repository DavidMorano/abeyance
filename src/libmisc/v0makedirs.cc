/* makedirs SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* make directories (within a single path) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-10-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Name:
	makedirs

	Description:
	This subroutine creates a directory and all of its parent
	directories if they do not exist, and if it is possible to
	create them.

	Synopsis:
	int makedirs(cchar *dirp,int dirl,mode_t mode) noex

	Arguments:
	dirp		path to the directory to create
	dirl		length of directory path string
	mode		the file permission mode to create the directories

	Returns:
	>0		directory was created
	0		directory already existed
	<0		error (system-return)

*******************************************************************************/

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/stat.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<usystem.h>
#include	<ids.h>
#include	<xperm.h>
#include	<strdcpyx.h>
#include	<localmisc.h>

#include	"makedirs.h"


/* local defines */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */

static int	procdir(ids *,cchar *,mode_t) noex ;


/* local variables */


/* exported variables */


/* exported subroutines */

int makedirs(cchar *dirp,int dirl,mode_t mode) noex {
	ids		id ;
	int		rs ;
	int		rs1 ;
	int		c = 0 ;

	if (dirp == NULL) return SR_FAULT ;

	if ((rs = ids_load(&id)) >= 0) {
	    cchar	*dp ;
	    char	dirbuf[MAXPATHLEN + 1] ;
	    char	*bp ;

	    if (dirl < 0) {

	        rs = procdir(&id,dirp,mode) ;
	        c += rs ;
	        if (rs == SR_NOENT)
	            dirl = strdcpy1w(dirbuf,MAXPATHLEN,dirp,-1) - dirbuf ;

	    } else {

	        strdcpy1w(dirbuf,MAXPATHLEN,dirp,dirl) ;
	        rs = procdir(&id,dirbuf,mode) ;
	        c += rs ;

	    } /* end if */

	    if (rs == SR_NOENT) {
	        rs = SR_OK ;

	        dp = dirbuf ;
	        while ((bp = strchr(dp,'/')) != NULL) {

	            *bp = '\0' ;
	            if (((bp - dp) > 0) && (strcmp(dp,".") != 0)) {
	                rs = procdir(&id,dirbuf,mode) ;
	                c += rs ;
	            } /* end if */

	            *bp = '/' ;
	            dp = bp + 1 ;

	            if (rs < 0) break ;
	        } /* end while */

	        if ((rs >= 0) && (*dp != '\0')) {
	            rs = procdir(&id,dirbuf,mode) ;
	            c += rs ;
	        }

	    } /* end if (needed some creations) */

	    rs1 = ids_release(&id) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (ids) */

	return (rs >= 0) ? c : rs ;
}
/* end subroutine (makedirs) */


/* local subroutines */

static int procdir(ids *idp,cchar *dirbuf,mode_t mode) noex {
	int		rs ;
	if (USTAT sb ; (rs = u_stat(dirbuf,&sb)) >= 0) {
	    if (S_ISDIR(sb.st_mode)) {
	        rs = sperm(idp,&sb,X_OK) ;
	        if (rs > 0) rs = 0 ;
	    } else {
	        rs = SR_NOTDIR ;
	    }
	} else if (rs == SR_NOENT) {
	    rs = u_mkdir(dirbuf,mode) ;
	    if (rs >= 0) rs = 1 ;
	} /* end if */
	return rs ;
}
/* end subroutine (procdir) */


