/* vecstr_loadfile SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 */

/* load strings from a file */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-09-10, David A­D­ Morano
	This module was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	vecstr_loadfile

	Description:
	This subroutine will read (process) a file and put all of
	the strings found into the string (supplied) list, consisting
	of a vecstr object.

	Synopsis:
	int vecstr_loadfile(vecstr *vsp,int fu,cchar *fname) noex

	Arguments:
	vsp		pointer to vecstr object
	fu		flag specifying uniqueness
	fname		file to load

	Returns:
	>=0		number of elements loaded
	<0		error (system-return)

	Notes:
	Why use filer over BFILE? Yes, filer is a tiny bit more
	lightweight than BFILE -- on a good day. But the real reason
	may be so that we do not need to load BFILE in code that
	resides very deep in a software stack if we do not need it
	-- like deep inside loadable modules. Anyway, just a thought!

	Why are we using field as opposed to |sffield(3uc)| or
	something similar?  Because our sematics are to process
	quoted strings as a single vecstr entry!

	Note_on_uniqueness:

	The 'fu' argument:
		0=no_unique
		1=unique

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/param.h>
#include	<sys/stat.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<climits>		/* <- for |UCHAR_MAX| + |CHAR_BIT| */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<algorithm>		/* |min(3c++)| + |max(3c++)| */
#include	<usystem.h>
#include	<bufsizevar.hh>
#include	<filer.h>
#include	<field.h>
#include	<fieldterms.h>
#include	<localmisc.h>

#include	"vecstr.h"


/* local defines */

#define	LINEBUFMULT	5		/* line-buffer size multiplier */

#ifndef	FD_STDIN
#define	FD_STDIN	0
#endif

#define	DEFBUFLEN	1024

#define	TO_READ		-1		/* read timeout */


/* imported namespaces */

using std::min ;			/* subroutine-template */
using std::max ;			/* subroutine-template */


/* local typedefs */


/* external subroutines */

extern "C" {
    extern int vecstr_loadfile(vecstr *,int,cchar *) noex ;
}


/* external variables */


/* local structures */

namespace {
    struct vars {
        int             linebuflen ;
    } ;
}


/* forward references */

static int	vecstr_loadfiler(vecstr *,int,cchar *) noex ;
static int	vecstr_loadfd(vecstr *,int,int) noex ;
static int	vecstr_loadline(vecstr *,int,cchar *,int) noex ;
static int	mkterms() noex ;
static int	mkvars() noex ;


/* local variables */

constexpr int		termsize = ((UCHAR_MAX+1)/CHAR_BIT) ;

static bufsizevar	maxlinelen(getbufsize_ml) ;

static char		fterms[termsize] ;

static vars		var ;


/* exported variables */


/* exported subroutines */

int vecstr_loadfile(vecstr *op,int fu,cchar *fname) noex {
	int		rs = SR_FAULT ;
	int		c = 0 ;
	if (op && fname) {
	    rs = SR_INVALID ;
	    if (fname[0]) {
	        static cint	srs = mkterms() ;
	        if ((rs = srs) >= 0) {
	            static cint	srv = mkvars() ;
	            if ((rs = srv) >= 0) {
			rs = vecstr_loadfiler(op,fu,fname) ;
			c = rs ;
		    } /* end if (mkvars) */
		} /* end if (mkterms) */
	    } /* end if (valid) */
	} /* end if (non-null) */
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (vecstr_loadfile) */


/* local subroutines */

static int vecstr_loadfiler(vecstr *op,int fu,cchar *fname) noex {
	int		rs = SR_OK ;
	int		rs1 ;
	int		c = 0 ;
        if (strcmp(fname,"-") != 0) {
            cint    of = O_RDONLY ;
            cmode   om = 0666 ;
            if ((rs = uc_open(fname,of,om)) >= 0) {
		cint	fd = rs ;
		{
                    rs = vecstr_loadfd(op,fu,fd) ;
		    c = rs ;
		}
                rs1 = uc_close(fd) ;
		if (rs >= 0) rs = rs1 ;
            } /* end if (read-file) */
        } else {
	    cint	fd = FD_STDIN ;
            rs = vecstr_loadfd(op,fu,fd) ;
            c = rs ;
        } /* end if (file or STDIN) */
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (vecstr_loadfiler) */

static int vecstr_loadfd(vecstr *vsp,int fu,int fd) noex {
	int		rs ;
	int		rs1 ;
	int		to = -1 ;
	int		c = 0 ;
	USTAT		sb ;
	if ((rs = u_fstat(fd,&sb)) >= 0) {
	    csize	fsz = size_t(sb.st_size) ;
	    rs = SR_ISDIR ;
	    if (! S_ISDIR(sb.st_mode)) {
		cint	linelen = var.linebuflen ;
	        cint	fs = ((fsz == 0) ? 1 : int(fsz & INT_MAX)) ;
	        int	fbsize = DEFBUFLEN ;
	        int	fbo = 0 ;
	        if (S_ISREG(sb.st_mode)) {
	            cint	cs = BCEIL(fs,512) ;
	            fbsize = min(cs,1024) ;
	        } else {
	            to = TO_READ ;
	            if (S_ISSOCK(sb.st_mode)) fbo |= FILER_ONET ;
	        }
		if ((rs = maxlinelen) >= 0) {
		    cint	llen = (linelen > 0) ? linelen : rs ;
	            char	*lbuf{} ;
		    if ((rs = uc_libmalloc((llen+1),&lbuf)) >= 0) {
			filer		loadfile, *lfp = &loadfile ;
	        	if ((rs = filer_start(lfp,fd,0z,fbsize,fbo)) >= 0) {
			    auto	rl = filer_readln ;
	                    while ((rs = rl(lfp,lbuf,llen,to)) > 0) {
	                        int	len = rs ;
	                        if (lbuf[len - 1] == '\n') len -= 1 ;
			        if ((len > 0) && (lbuf[0] != '#')) {
			            rs = vecstr_loadline(vsp,fu,lbuf,len) ;
			            c += rs ;
			        }
	                        if (rs < 0) break ;
	                    } /* end while (reading lines) */
	                    rs1 = filer_finish(lfp) ;
		            if (rs >= 0) rs = rs1 ;
	                } /* end if (filer) */
			rs1 = uc_libfree(lbuf) ;
			if (rs >= 0) rs = rs1 ;
		    } /* end if (m-a-f) */
		} /* end if (maxlinelen) */
	    } /* end if (not a directory) */
	} /* end if (stat) */
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (vecstr_loadfd) */

static int vecstr_loadline(vecstr *vsp,int fu,cchar *lbuf,int len) noex {
	field		fsb ;
	int		rs ;
	int		rs1 ;
	int		c = 0 ;
	if ((rs = field_start(&fsb,lbuf,len)) >= 0) {
	    int		fl ;
	    cchar	*fp ;
	    while ((fl = field_get(&fsb,fterms,&fp)) >= 0) {
		if (fl > 0) {
		    if (fu) {
			rs = vecstr_adduniq(vsp,fp,fl) ;
			if (rs < INT_MAX) c += 1 ;
		    } else {
			c += 1 ;
			rs = vecstr_add(vsp,fp,fl) ;
		    }
		} /* end if (got one) */
		if (fsb.term == '#') break ;
		if (rs < 0) break ;
	    } /* end while (fields) */
	    rs1 = field_finish(&fsb) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (fields) */
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (vecstr_loadline) */

static int mkterms() noex {
	return fieldterms(fterms,false,'\n','#') ;
}
/* end subroutine (mkterms) */

static int mkvars() noex {
        int             rs ;
        if ((rs = uc_sysconfmaxline()) >= 0) {
            var.linebuflen = (rs * LINEBUFMULT) ;
        }
        return rs ;
}       
/* end subroutine (mkvars) */


