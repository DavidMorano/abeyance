/* mknoise_addids SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 */

#define	PROCFNAME	"/proc"


/* exported variables */


/* local subroutines */

static int noisedata_addids(NOISEDATA *ndp,cchar *procdname) noex {
	int		rs = SR_FAULT ;
	int		rs1 ;
	if (ndp && procdname) {
	USTAT		sb ;
	fsdir		pdir ;
	fsdir_ent	ds ;
	int		dlen ;
	int		v ;
	char		*bp ;
	char		*dnp ;
	if (char *tbuf{} ; (rs = malloc_mp(&tbuf)) >= 0) {
	    cint	tlen = rs ;

	    bp = strwcpy(tbuf,procdname,tlen) ;
	    *bp++ = '/' ;
	    if (char *nbuf{} ; (rs = malloc_mn(&nbuf)) >= 0) {
		cint	nlen = rs ;
	        if ((rs = fsdir_open(&pdir,procdname)) >= 0) {
	            while ((rs = fsdir_read(&pdir,&ds,nbuf,nlen)) > 0) {
			cint	dlen = rs ;
	    dnp = ds.name ;
	    if (*dnp == '.') {
	        if (dnp[1] == '\0') continue ;
	        if ((dnp[1] == '.') && (dnp[2] == '\0')) continue ;
	    }

#if	CF_STAT
	    strwcpy(bp,dnp,(MAXPATHLEN - (bp - tmpfname))) ;
	    if ((rs1 = u_stat(tmpfname,&sb)) >= 0) {
	        noisedata_add(ndp,(uint) sb.st_mtime) ;
	    }
#endif /* CF_STAT */

	    if ((rs1 = cfdeci(dnp,dlen,&v)) >= 0) {
	        if (ndp->pass & 1) {
	            v = (v << 8) | ((v >> 8) & 255) ;
		}
	        noisedata_add(ndp,v) ;
	    } /* end if (got a PID) */

			} /* end while (reading entries) */
	                rs1 = fsdir_close(&pdir) ;
	                if (rs >= 0) rs = rs1 ;
	            } /* end if (fsdir) */
		    rs1 = uc_free(nbuf) ;
	            if (rs >= 0) rs = rs1 ;
		} /* end if (m-a-f) */
		rs1 = uc_free(tbuf) ;
	        if (rs >= 0) rs = rs1 ;
	    } /* end if (m-a-f) */
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (noisedata_addids) */


