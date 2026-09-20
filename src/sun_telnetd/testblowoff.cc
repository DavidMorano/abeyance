/* testblowoff */
/* charset=ISO8859-1 */
/* lang=C89 */

#define	CF_REAL	1

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<cstddef>
#include	<cstdlib>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<bfile.h>
#include	<filer.h>
#include	<localmisc.h>

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |lenstr(3u)| */

#ifndef	LINEBUFLEN
#define	LINEBUFLEN	MAX(MAXPATHLEN,2048)
#endif

#define	DFNAME	"here"

extern "C" {
    extern int	nprintf(cchar *,cchar *,...) noex ;
    extern int	bufprintf(cchar *,...) noex ;
}

int main(int argc,con mainv argv,con mainv envv) {
	filer	b ;
	bfile	src, *sfp = &src ;
	cchar	fd = 1 ;
	int	rs ;
	int	wlen = 0 ;
	cchar	*fn = "/usr/extra/etc/telnetd/blowoff.txt" ;
	(void) argc ;
	(void) argv ;
	(void) envv ;

	{
	    cchar	*resp = "hello there\r\n" ;
	    u_write(fd,resp,strlen(resp)) ;
	}

	{
		ustat	sb ;
		int	tlen = LINEBUFLEN ;
		int	tl ;
		char	tbuf[LINEBUFLEN+1] ;
	rs = u_stat(fn,&sb) ;
		tl = bufprintf(tbuf,tlen,"rs=%d\r\n",rs) ;
	    u_write(fd,tbuf,tl) ;
	}

#if	CF_REAL
	if ((rs = bopen(sfp,fn,"r",0666)) >= 0) {
	    if ((rs = filer_start(&b,fd,0z,512,0)) >= 0) {
		cint	llen = LINEBUFLEN ;
		char	lbuf[LINEBUFLEN+3] ;

		while ((rs = breadln(sfp,lbuf,llen)) > 0) {
		    int	len = rs ;

		    if (lbuf[len-1] == '\n') len -= 1 ;

		    lbuf[len++] = '\r' ;
		    lbuf[len++] = '\n' ;
		    rs = filer_write(&b,lbuf,len) ;
		    wlen += rs ;

		    if (rs < 0) break ;
		} /* end while (reading lines) */

		filer_finish(&b) ;
	    } /* end if (filer) */
	    bclose(sfp) ;
	} /* end if (open source) */
#else /* CF_REAL */
	rs = bopen(sfp,fn,"r",0666) ;
	nprintf(DFNAME,"bopen() rs=%d\n",rs) ;
	if (rs >= 0) {
	    if ((rs = filer_start(&b,fd,0z,512,0)) >= 0) {
		cint	llen = LINEBUFLEN ;
		char	lbuf[LINEBUFLEN+3] ;

		while (rs >= 0) {
		    int	len ;
		    rs = breadln(sfp,lbuf,llen) ;
	nprintf(DFNAME,"breadln() rs=%d\n",rs) ;
		    if (rs <= 0) break ;
		    len = rs ;

		    if (lbuf[len-1] == '\n') len -= 1 ;	

		    lbuf[len++] = '\r' ;
		    lbuf[len++] = '\n' ;
		    rs = filer_write(&b,lbuf,len) ;
		    wlen += rs ;

		    if (rs < 0) break ;
		} /* end while (reading lines) */

		filer_finish(&b) ;
	    } /* end if (filer) */
	    bclose(sfp) ;
	} /* end if (open source) */
	    if ((rs = filer_start(&b,fd,0z,512,0)) >= 0) {
	    cchar	*resp = "hello there\r\n" ;
		    rs = filer_write(&b,resp,strlen(resp)) ;
		filer_finish(&b) ;
	    }
#endif /* CF_REAL */

	{
	    cchar	*resp = "good bye\r\n" ;
	    u_write(fd,resp,strlen(resp)) ;
	}

	return 0 ;
}
/* end subroutine (main) */


