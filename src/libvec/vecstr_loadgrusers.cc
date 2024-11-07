/* vecstr_loadgrusers SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 */

/* find and load UNIX® users who have the given group as their default */
/* version %I% last-modified %G% */


/* revision history:

	= 2004-01-10, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 2004 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	vecstr_loadgrusers

	Description:
	This subroutine finds all users who have the given specified
	group as their default group.

	Synopsis:
	int vecstr_loadgrusers(vecstr *,gid_t) noex

	Returns:
	>=0	ok
	<0	error (system-return)

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/param.h>
#include	<sys/mman.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<climits>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<usystem.h>
#include	<strn.h>
#include	<cfdec.h>
#include	<ascii.h>
#include	<numsign.h>
#include	<localmisc.h>

#include	"vecstr.h"


/* local defines */

#define	SUBINFO		struct subinfo

#ifndef	SYSPASSWD
#define	SYSPASSWD	"/sysdb/passwd"
#endif


/* external subroutines */


/* local structures */

struct subinfo {
	vecstr		*ulp ;
	void		*mapdata ;
	size_t		mapsize ;
	size_t		fsize ;
	gid_t		sgid ;
} ;


/* forward references */

static int	subinfo_start(SUBINFO *,vecstr *,gid_t) noex ;
static int	subinfo_pwmapbegin(SUBINFO *) noex ;
static int	subinfo_pwmapload(SUBINFO *) noex ;
static int	subinfo_pwmapend(SUBINFO *) noex ;
static int	subinfo_finish(SUBINFO *) noex ;

static int	pwentparse(cchar *,int,gid_t *) noex ;


/* local template-subroutines */


/* local variables */


/* local subroutines */


/* exported variables */


/* exported subroutines */

int vecstr_loadgrusers(vecstr *ulp,gid_t sgid) noex {
	int		rs = SR_FAULT ;
	int		rs1 ;
	int		c = 0 ;
	if (ulp) {
	    SUBINFO	si, *sip = &si ;
	    if (numsign(sgid)) sgid = getgid() ;
	    if ((rs = subinfo_start(sip,ulp,sgid)) >= 0) {
		{
	            rs = subinfo_pwmapload(sip) ;
	            c = rs ;
		}
	        rs1 = subinfo_finish(sip) ;
	        if (rs >= 0) rs = rs1 ;
	    } /* end if (subinfo) */
	} /* end if (non-null) */
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (vecstr_loadgrusers) */


/* local subroutines */

static int subinfo_start(SUBINFO *sip,vecstr *ulp,gid_t sgid) noex {
    	int		rs = SR_BUGCHECK ;
	if (sip && ulp) {
	    rs = memclear(sip) ;
	    sip->ulp = ulp ;
	    sip->sgid = sgid ;
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (subinfo_start) */

static int subinfo_finish(SUBINFO *sip) noex {
	int		rs = SR_FAULT ;
	if (sip) {
	    rs = SR_OK ;
	}
	return rs ;
}
/* end subroutine (subinfo_finish) */

static int subinfo_pwmapload(SUBINFO *sip) noex {
	int		rs ;
	int		rs1 ;
	int		c = 0 ;
	if ((rs = subinfo_pwmapbegin(sip)) >= 0) {
	    int		ml = sip->fsize ;
	    cchar	*mp = charp(sip->mapdata) ;
	    cchar	*tp ;
	    while ((tp = strnchr(mp,ml,CH_NL)) != nullptr) {
	        cint	len = (tp - mp) ;
	        if (gid_t gid{} ; (rs = pwentparse(mp,len,&gid)) > 0) {
		    cint	ul = rs ;
		    if (sip->sgid == gid) {
	                c += 1 ;
	                rs = vecstr_adduniq(sip->ulp,mp,ul) ;
	            }
	        } /* end if (pwentparse) */
	        ml -= ((tp+1)-mp) ;
	        mp = (tp+1) ;
	        if (rs < 0) break ;
	    } /* end while (reading lines) */
	    rs1 = subinfo_pwmapend(sip) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (grmems-pwmap) */
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (subinfo_pwmapload) */

static int subinfo_pwmapbegin(SUBINFO *sip) noex {
	int		rs = SR_OK ;
	int		rs1 ;
	if (sip->mapdata == nullptr) {
	    cmode	om = 0666 ;
	    cint	of = O_RDONLY ;
	    cchar	*fn = SYSPASSWD ;
	    if ((rs = uc_open(fn,of,om)) >= 0) {
	        cint	fd = rs ;
	        if ((rs = uc_fsize(fd)) >= 0) {
		    cnullptr	np{} ;
	            csize	ms = rs ;
	            int		mp = PROT_READ ;
	            int		mf = MAP_SHARED ;
	            sip->fsize = rs ;
	            if (void *md ; (rs = u_mmap(np,ms,mp,mf,fd,0z,&md)) >= 0) {
	                cint		madv = MADV_SEQUENTIAL ;
			const caddr_t	ma = caddr_t(md) ;
	                if ((rs = u_madvise(ma,ms,madv)) >= 0) {
	                    sip->mapdata = md ;
	                    sip->mapsize = ms ;
	                } /* end if (advise) */
	                if (rs < 0) {
	                    u_munmap(md,ms) ;
			}
	            } /* end if (mmap) */
	        } /* end if (file-size) */
	        rs1 = u_close(fd) ;
		if (rs >= 0) rs = rs1 ;
	    } /* end if (file-open) */
	} /* end if (need mapping) */
	return rs ;
}
/* end subroutine (subinfo_pwmapbegin) */

static int subinfo_pwmapend(SUBINFO *sip) noex {
	int		rs = SR_OK ;
	int		rs1 ;
	if (sip->mapdata) {
	    csize	ms = sip->mapsize ;
	    void	*md = sip->mapdata ;
	    rs1 = u_munmap(md,ms) ;
	    if (rs >= 0) rs = rs1 ;
	    sip->mapdata = nullptr ;
	    sip->mapsize = 0 ;
	}
	return rs ;
}
/* end subroutine (subinfo_pwmapend) */

/* PASSWD entry parsing */
static int pwentparse(cchar *lbuf,int llen,gid_t *gp) noex {
	int		rs = SR_OK ;
	int		fi{} ;		/* <- used afterwards */
	int		ll = llen ;
	int		ul = 0 ;
	cchar		*lp = lbuf ;
	for (fi = 0 ; fi < 4 ; fi += 1) {
	    if (cchar *tp ; (tp = strnchr(lp,ll,':')) != nullptr) {
	        switch (fi) {
	        case 0:
	            ul = (tp-lp) ;
	            break ;
	        case 3:
	            {
	                if (int v{} ; (rs = cfdeci(lp,(tp-lp),&v)) >= 0) {
	                    *gp = gid_t(v) ;
	                } else {
	                    ul = 0 ;
			}
	            } /* end block */
	            break ;
	        } /* end switch */
	        ll -= ((tp+1)-lp) ;
	        lp = (tp+1) ;
	    } /* end if (had separator) */
	} /* end for (looping through fields) */
	if (fi < 4) ul = 0 ;
	return (rs >= 0) ? ul : rs ;
}
/* end subroutine (pwentparse) */


