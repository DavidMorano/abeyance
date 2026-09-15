/* debugging SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* variaous particular debgging utilities */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/utsname.h>
#include	<sys/stat.h>
#include	<unistd.h>
#include	<pwd.h>
#include	<grp.h>
#include	<ctime>
#include	<cerrno>
#include	<csignal>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstdio>
#include	<cstring>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<baops.h>
#include	<logfile.h>
#include	<bfile.h>
#include	<timestr.h>
#include	<localmisc.h>

#include	"config.h"
#include	"defs.h"
#include	"prompt.h"
#include	"header.h"


/* local defines */


/* external subroutines */


/* external variables */

extern struct global	g ;


/* exported variables */


/* exported subroutines */

void fileinfo(cchar *fname,cchar *w) noex {
	bfile		msgfile, *mfp = &msgfile ;
	USTAT		sb ;
	int	i, j, rs, len, l ;

	char	linebuf[LINELEN + 1] ;
	char	buf1[LINELEN + 1], buf2[LINELEN + 2] ;


	if ((w != nullptr) && (w[0] != '\0'))
	    logfile_printf(&g.eh,"fileinfo: where=\"%s\"\n",w) ;

	if ((fname || fname[0]) {

	    logfile_printf(&g.eh,"fileinfo: fname=\"%s\"\n",fname) ;

	    if (stat(fname,&sb) < 0) {

	        logfile_printf(&g.eh,"fileinfo: bad stat errno=%d\n",errno) ;

	    } else {

	        logfile_printf(&g.eh,
	            "fileinfo: len=%ld atime=%s mtime=%s\n",
	            sb.st_size,
	            timestr_log(sb.st_atime,buf1),
	            timestr_log(sb.st_mtime,buf2)) ;

	    }

	    if ((rs = bopen(mfp,fname,"r",0666)) >= 0) {

		len = 0 ;
	        i = 0 ;

/* do all of the header lines */

	        while ((l = breadln(mfp,linebuf,LINELEN)) > 0) {

	            len += l ;

	            logfile_printf(&g.eh,"fileinfo: h %2d-%2d> %W",
	                i,l,linebuf,l) ;

	            if (linebuf[0] == '\n') break ;

	            i += 1 ;

	        } /* end while (header lines) */

/* do some of the body */

		j = 0 ;
	        while ((j < 5) && ((l = breadln(mfp,linebuf,LINELEN)) > 0)) {

	            len += l ;

	            logfile_printf(&g.eh,"fileinfo: b %2d-%2d> %W",
	                i,l,linebuf,l) ;

	            if (linebuf[0] == '\n') break ;

	            i += 1 ;
			j += 1 ;

	        } /* end while (body lines) */

	        logfile_printf(&g.eh,"fileinfo: %d header bytes, EOF=%d\n",
	            len,(l == 0)) ;

	        bclose(mfp) ;

	    } else {

	        logfile_printf(&g.eh,
	            "fileinfo: could not open (rs %d)\n",rs) ;

	    }

	} else {
	    logfile_printf(&g.eh,"fileinfo: file was nullptr\n") ;
	}

}
/* end subroutine (fileinfo) */


