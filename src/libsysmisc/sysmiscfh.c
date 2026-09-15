/* sysmiscfh SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* shared-memory for SYSMISC storage */
/* version %I% last-modified %G% */

#define	CF_DEBUGS 	0		/* run-time debugging */

/* revision history:

	= 1998-03-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This subroutine read and writes the NCPU shared-memory segment.

	Synopsis:

	int sysmiscfh(ep,f,buf,buflen)
	SYSMISCFH	*ep ;
	int		f ;
	char		buf[] ;
	int		buflen ;

	Arguments:

	- ep		object pointer
	- f		read=1, write=0
	- buf		buffer containing object
	- buflen	length of buffer

	Returns:

	>=0		OK
	<0		error code


*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<unistd.h>
#include	<climits>
#include	<cstddef>
#include	<cstdlib>
#include	<cstring>
#include	<usystem.h>
#include	<endian.h>
#include	<localmisc.h>

#include	"sysmiscfh.h"


/* local defines */


/* external subroutines */

extern int	sncpy2(char *,int,cchar *,cchar *) ;
extern int	cfhexi(cchar *,int,uint *) ;
extern int	cfdecui(cchar *,int,uint *) ;

#if	CF_DEBUGS
extern int	debugprintf(cchar *,...) ;
#endif

extern char	*strwcpy(char *,cchar *,int) ;
extern char	*strnchr(cchar *,int,int) ;


/* external variables */


/* local structures */


/* forward references */

extern int	mkmagic(char *,int,cchar *) ;


/* local variables */


/* exported subroutines */


int sysmiscfh(ep,f,buf,buflen)
SYSMISCFH	*ep ;
int		f ;
char		buf[] ;
int		buflen ;
{
	uint	*header ;

	int	rs = SR_OK ;
	int	i ;
	int	headsize = (sysmiscfv_overlast + 2) * sizeof(uint) ;
	int	magicsize = SYSMISCFH_MAGICSIZE ;
	int	bl, cl ;
	int	len = 0 ;

	cchar	*magicstr = SYSMISCFH_MAGICSTR ;

	char	*bp ;
	char	*tp, *cp ;


	if (ep == NULL)
	    return SR_FAULT ;

	if (buf == NULL)
	    return SR_FAULT ;

#if	CF_DEBUGS
	debugprintf("sysmiscfh: f=%u\n",f) ;
#endif

	bp = buf ;
	bl = buflen ;
	if (f) {

/* read */

/* the magic string is within the first 15 bytes */

	    if ((rs >= 0) && (bl > 0)) {

	        if (bl >= magicsize) {

	            cp = bp ;
	            cl = magicsize ;
	            if ((tp = strnchr(cp,cl,'\n')) != NULL)
	                cl = (tp - cp) ;

	            bp += magicsize ;
	            bl -= magicsize ;

/* verify the magic string */

	            if (strncmp(cp,magicstr,cl) != 0)
	                rs = SR_NXIO ;

	        } else
	            rs = SR_ILSEQ ;

	    } /* end if (item) */

#if	CF_DEBUGS
	debugprintf("sysmiscfh: magic rs=%d\n",rs) ;
#endif

/* read out the VETU information */

	    if ((rs >= 0) && (bl > 0)) {

	        if (bl >= 4) {

	            memcpy(ep->vetu,bp,4) ;

	            if (ep->vetu[0] != SYSMISCFH_VERSION)
	                rs = SR_PROTONOSUPPORT ;

	            if ((rs >= 0) && (ep->vetu[1] != ENDIAN))
	                rs = SR_PROTOTYPE ;

	            bp += 4 ;
	            bl -= 4 ;

	        } else
	            rs = SR_ILSEQ ;

	    } /* end if (item) */

#if	CF_DEBUGS
	debugprintf("sysmiscfh: VETU rs=%d\n",rs) ;
#endif

/* read everything else */

	    if ((rs >= 0) && (bl > 0)) {

	        if (bl >= headsize) {

	            header = (uint *) bp ;

	            ep->shmsize = header[sysmiscfv_shmsize] ;
	            ep->intstale = header[sysmiscfv_intstale] ;
	            ep->utime = header[sysmiscfv_utime] ;
	            ep->btime = header[sysmiscfv_btime] ;
	            ep->ncpu = header[sysmiscfv_ncpu] ;
	            ep->nproc = header[sysmiscfv_nproc] ;
		    for (i = 0 ; i < 3 ; i += 1)
			ep->la[i] = header[sysmiscfv_la + i] ;

	            bp += headsize ;
	            bl -= headsize ;

	        } else
	            rs = SR_ILSEQ ;

	    } /* end if (item) */

#if	CF_DEBUGS
	debugprintf("sysmiscfh: rem rs=%d\n",rs) ;
#endif

	} else {

/* write */

	    mkmagic(bp, magicsize, magicstr) ;
	    bp += magicsize ;
	    bl -= magicsize ;

	    memcpy(bp,ep->vetu,4) ;
	    bp[0] = SYSMISCFH_VERSION ;
	    bp[1] = ENDIAN ;
	    bp += 4 ;
	    bl -= 4 ;

	    if ((rs >= 0) && (bl >= headsize)) {

	        header = (uint *) bp ;

	        header[sysmiscfv_shmsize] = ep->shmsize ;
	        header[sysmiscfv_intstale] = ep->intstale ;
	        header[sysmiscfv_utime] = ep->utime ;
	        header[sysmiscfv_btime] = ep->btime ;
	        header[sysmiscfv_ncpu] = ep->ncpu ;
	        header[sysmiscfv_nproc] = ep->nproc ;
		    for (i = 0 ; i < 3 ; i += 1)
			header[sysmiscfv_la + i] = ep->la[i] ;

	        bp += headsize ;
	        bl -= headsize ;

	    } /* end if */

	} /* end if */

	len = (bp - buf) ;

#if	CF_DEBUGS
	debugprintf("sysmiscfh: ret rs=%d len=%u\n",rs,len) ;
#endif

	return (rs >= 0) ? len : rs ;
}
/* end subroutine (sysmiscfh) */


/* local subroutines */


static int mkmagic(buf,magicstr,magicsize)
char		buf[] ;
cchar	*magicstr ;
int		magicsize ;
{
	char	*cp = buf ;


	cp = strwcpy(cp,magicstr,(magicsize - 1)) ;
	*cp++ = '\n' ;
	memset(cp,0,(magicsize - (cp - buf))) ;

	return magicsize ;
}
/* end subroutine (mkmagic) */


