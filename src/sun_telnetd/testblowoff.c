/* testblowoff */
/* lang=C89 */

#define	CF_REAL	1

#include	<envstandards.h>
#include	<sys/types.h>
#include	<sys/param.h>
#include	<bfile.h>
#include	<filer.h>
#include	<localmisc.h>

#ifndef	LINEBUFLEN
#define	LINEBUFLEN	MAX(MAXPATHLEN,2048)
#endif

#define	DFNAME	"here"

extern int	nprintf(const char *,const char *,...) ;
extern int	bufprintf(const char *,...) ;

int main(int argc,const char **argv,const char **envv)
{
	FILER	b ;

	bfile	src, *sfp = &src ;

	const char	fd = 1 ;

	int	rs ;
	int	wlen = 0 ;

	const char	*fn = "/usr/extra/etc/telnetd/blowoff.txt" ;


	{
	    const char	*resp = "hello there\r\n" ;
	    u_write(fd,resp,strlen(resp)) ;
	}

	{
		struct ustat	sb ;
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
		const int	llen = LINEBUFLEN ;
		char		lbuf[LINEBUFLEN+3] ;

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
	    const char	*resp = "hello there\r\n" ;
		    rs = filer_write(&b,resp,strlen(resp)) ;
		filer_finish(&b) ;
	    }
#endif /* CF_REAL */

	{
	    const char	*resp = "good bye\r\n" ;
	    u_write(fd,resp,strlen(resp)) ;
	}

	return 0 ;
}
/* end subroutine (main) */

