/* udomain SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* get user domain */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	I made up this idea for supporting multiple domains on the
	same machine so that each user could have a different domain
	name. This idea of multiplexing a single machine to appear
	to be multiple different machines is becoming very important
	in the Internet age!

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	udomain

	Description:
	This subroutine looks up the given username and returns the
	domainname for that user.  Per-user domain names are optional
	and are administered through the file 'etc/udomain' located
	relative to the programroot directory that is optionally
	supplied.  If no programroot is supplied, then '/' is used.
	This subroutine uses two different ways to read the UDOMAIN
	DB based on the file it is in.  This is so that in addition
	to the file being "regular" it can also be (secretly) a
	network file or portal of some kind.

	Synopsis:
	int udomain(cchar *pr,char *dbuf,int dlen,cchar *username) noex

	Arguments:
	pr		program-root
	dbuf		buffer to receive results (must be MAXPATHLEN in size)
	dlen		length of supplied buffer
	username	specified username to lookup

	Returns:
	>=0		length of returned domain-name
	<0		error (system-return)

	Notes:
	Format of file entries:
		username	domainname
	Note that this strategy of reading the "udomain" file is obsoleted by
	the use of the 'id' (Internet Domain) key-value pair in the 'user_attr'
	DB of the system!

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<unistd.h>
#include	<fcntl.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<estrings.h>
#include	<snwcpy.h>
#include	<mkpathx.h>
#include	<filemap.h>
#include	<filer.h>
#include	<localmisc.h>

#include	"udomain.h"

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |lenstr(3u)| */

/* local defines */

#ifndef	UDOMASTDFNIN
#define	UDOMASTDFNIN	"/etc/udomain"
#endif

#define	MAXFILESIZE	(2 * 1024 * 1024)


/* local namespaces */


/* local typedefs */


/* external subroutines */

extern "C" {
    int udomain(cchar *,char *,int,cchar *) noex ;
}


/* external variables */


/* local structures */

namespace {
    struct uargs {
	cchar		*un = nullptr ;
	char		*dbuf ;
	int		dlen ;
	int		ul = 0 ;
	int		maxfilesize ;
	uargs(char *dp,int dl,cchar *u,int mf) noex : dbuf(dp) , dlen(dl) {
	    un = u ;
	    if (un) {
	        ul = strlen(un) ;
 	    }
	    maxfilesize = mf ;
	} ; /* end ctor */
	int udomainer(cchar *) noex ;
	int udomainerm(cchar *) noex ;
	int udomainerf(cchar *) noex ;
	int parseline(cchar *,int) noex ;
    } ; /* end struct (uargs) */
}


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int udomain(cchar *pr,char *dbuf,int dlen,cchar *username) noex {
	int		rs = SR_FAULT ;
	int		rs1 ;
	int		len = 0 ;
	if (dbuf && username) {
	    rs = SR_INVALID ;
	    dbuf[0] = '\0' ;
	    if (username[0]) {
	        uargs	a(dbuf,dlen,username,MAXFILESIZE) ;
	        cchar	*fname = UDOMASTDFNIN ;
	        if (pr && (pr[0] != '\0') && (strcmp(pr,"/") != 0)) {
		     if (char *fbuf ; (rs = lm_mp(&fbuf)) >= 0) {
	    	         if ((rs = mkpath(fbuf,pr,fname)) >= 0) {
	             	    rs = a.udomainer(fbuf) ;
		     	    len = rs ;
		         }
		         rs1 = lm_free(fbuf) ;
		         if (rs >= 0) rs = rs1 ;
		     } /* end if (m-a-f) */
	         } else {
	             rs = a.udomainer(fname) ;
		     len = rs ;
	         }
	    } /* end if (valid) */
	} /* end if (non-null) */
	return (rs >= 0) ? len : rs ;
}
/* end subroutine (udomain) */


/* local subroutines */

int uargs::udomainer(cchar *fname) noex {
	int		rs ;
	int		len = 0 ;
	if (USTAT sb ; (rs = u_stat(fname,&sb)) >= 0) {
	    if (S_ISREG(sb.st_mode) && (sb.st_size < maxfilesize)) {
		rs = udomainerm(fname) ;
		len = rs ;
	    } else {
		rs = udomainerf(fname) ;
		len = rs ;
	    } /* end if (type of file) */
	} /* end if (stat) */
	return (rs >= 0) ? len : rs ;
}
/* end subroutine (uargs::udomainer) */

int uargs::udomainerm(cchar *fname) noex {
	csize		mfsize = size_t(maxfilesize) ;
	int		rs ;
	int		rs1 ;
	int		len = 0 ;
	if (filemap udf ; (rs = udf.open(fname,mfsize)) >= 0) {
	    cchar	*lp ;
            while ((rs = udf.getln(&lp)) > 0) {
                cint	ll = rs ;
                {
                    rs = parseline(lp,ll) ;
                    len = rs ;
                }
                if (len > 0) break ;
                if (rs < 0) break ;
            } /* end while (reading lines) */
            rs1 = udf.close ;
            if (rs >= 0) rs = rs1 ;
        } /* end if (opened file) */
	return (rs >= 0) ? len : rs ;
}
/* end method (uargs::udomainerm) */

int uargs::udomainerf(cchar *fname) noex {
	int		rs ;
	int		rs1 ;
	int		len = 0 ;
	if (char *lbuf ; (rs = lm_ml(&lbuf)) >= 0) {
	    cint	llen = rs ;
	    if ((rs = uc_open(fname,O_RDONLY,0666)) >= 0) {
	        cint	fd = rs ;
	        if (filer b ; (rs = b.start(fd,0L,0,0)) >= 0) {
	            while ((rs = b.readln(lbuf,llen,-1)) > 0) {
			{
	                    rs = parseline(lbuf,rs) ;
	                    len = rs ;
			}
	                if (len > 0) break ;
	                if (rs < 0) break ;
	            } /* end while (reading lines) */
	            rs1 = b.finish ;
		    if (rs >= 0) rs = rs1 ;
	        } /* end if (filer) */
	        rs1 = uc_close(fd) ;
		if (rs >= 0) rs = rs1 ;
	    } /* end if (opened file) */
	    rs1 = lm_free(lbuf) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (m-a-f) */
	return (rs >= 0) ? len : rs ;
}
/* end method (uargs::udomainerf) */

int uargs::parseline(cchar *lbuf,int llen) noex {
	int		rs = SR_OK ;
	int		sl = llen ;
	int		cl ;
	int		len = 0 ;
	cchar		*tp ;
	cchar		*sp = lbuf ;
	cchar		*cp ;
	if ((sl > 0) && (sp[sl-1] == '\n')) {
	    sl -= 1 ;
	}
	if ((tp = strnchr(sp,sl,'#')) != nullptr) {
	    sl = (tp - sp) ;
	}
	if ((cl = sfnext(sp,sl,&cp)) > 0) {
	    if ((cl == ul) && (strncmp(un,cp,cl) == 0)) {
	        sl -= ((cp + cl) - sp) ;
	        sp = (cp + cl) ;
	        if ((cl = sfnext(sp,sl,&cp)) > 0) {
	            rs = snwcpy(dbuf,dlen,cp,cl) ;
		    len = rs ;
	        }
	    } /* end if (username match) */
	} /* end if (sfnext) */
	return (rs >= 0) ? len : rs ;
}
/* end subroutine (uargs::parseline) */


