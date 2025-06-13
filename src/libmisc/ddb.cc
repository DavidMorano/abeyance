/* ddb SUPPORT (unneeded, unfinished) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* domain data-base */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-10-01, David A­D­ Morano
	I made up this idea for supporting multiple domains on the
	same machine at the same time!  We'll see where this idea
	leads.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/******************************************************************************

  	Object:
	ddb

	Description:
	This subroutine looks up the given username and returns the
	domainname for that user.  Per-user domain names are options
	and are administered through the file 'etc/udomains' located
	relative to the programroot directory that is optionally
	supplied.  If no programroot is supplied, then '/' is used.

******************************************************************************/ 

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/param.h>
#include	<sys/stat.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<netdb.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<usystem.h>
#include	<estrings.h>
#include	<bfile.h>
#include	<vecstr.h>
#include	<hdb.h>
#include	<sfx.h>
#include	<mkpathx.h>
#include	<localmisc.h>

#include	"ddb.h"


/* local defines */


/* external subroutines */


/* external variables [subroutines */


/* exported variables */


/* exported subroutines */

int ddb_open(DDB *op,cc *pr,cc *fname) noex {
	int		rs = SR_FAULT ;
	if (op && pr && fname) {
	    rs = SR_OK ;
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (ddb_open) */

int ddb_search(DDB *op,cchar *key,cchar *value) noex {
	int	rs = SR_OK ;


	return rs ;
}
/* end subroutine (ddb_search) */

int ddb_close(DDB *op) noex {
	hdb_cur		cur ;
	hdb_dat		key ;
	hdb_dat		value ;
	int		rs = SR_OK ;

	hdb_curbegin(&op->db,&cur) ;

	while (hdb_curenum(&op->db,&cur,&key,&value) >= 0) {

		if (value.buf != NULL)
			uc_free(value.buf) ;

	} /* end while */

	hdb_curend(&op->db,&cur) ;

	hdb_free(&op->db) ;

	vecstr_free(&keys) ;

	if (op->fname != NULL) {
	    uc_free(op->fname) ;
	    op->fname = NULL ;
	}

	return rs ;
}
/* end subroutine (ddb_close) */


/* private subroutines */

static int ddb_parse(DDB *op,cchar *fname) noex {
	bfile	udfile ;

	int	rs ;
	int	len ;
	int	sl, cl ;
	int	ml = 0 ;

	cchar	*sp, *cp ;
	cchar	*fname ;

	char	udfname[MAXPATHLEN + 1] ;
	char	linebuf[LINEBUFLEN + 1] ;

	if ((pr != NULL) && (pr[0] != '\0')) {
		fname = udfname ;
		mkpath2(udfname,pr,UDOMASTDFNIN) ;
	} else {
		fname = UDOMASTDFNIN ;
	}

	domainname[0] = '\0' ;
	if ((rs = bopen(&udfile,fname,"r",0)) >= 0) {
	ml = 0 ;
	while ((rs = breadln(&udfile,linebuf,LINEBUFLEN)) > 0) {

	    len = rs ;
	    if (linebuf[len - 1] == '\n')
	        len -= 1 ;

	    linebuf[len] = '\0' ;

	    sp = linebuf ;
	    sl = len ;
	    cl = nextfield(sp,sl,&cp) ;

	    if ((cl <= 0) || (cp[0] == '#'))
	        continue ;

	    if (strncmp(username,cp,cl) == 0) {

	        sl -= ((cp + cl) - sp) ;
	        sp = (cp + cl) ;

	        cl = nextfield(sp,sl,&cp) ;

	        if (cl > 0) {

	            ml = MIN(cl,MAXHOSTNAMELEN) ;
	            strwcpy(domainname,cp,ml) ;

	            break ;

	        } /* end if (got a domainname) */

	    } /* end if (username match) */

	} /* end while (reading lines) */

	bclose(&udfile) ;
	} /* end if (bfile) */

	return (rs >= 0) ? ml : rs ;
}
/* end subroutine (ddb_parse) */


