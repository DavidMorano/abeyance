/* kinfo SUPPORT */
/* lang=C++20 */

/* kernel information access (for Sun Solaris®) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-12-01, David A­D­ Morano
	Module was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This object provides access to some kernel-related information.

	Extra notes for the observant:

	You might note that the KSTAT(3kstat) stuff is NOT reentrant
	nor thread safe.  Yes, its true, they are not!  Blame Sun
	Microsystems for that!

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<kstat.h>
#include	<time.h>
#include	<stdlib.h>
#include	<string.h>

#if	(defined(SYSHAS_LOADAVG) && (SYSHAS_LOADAVG > 0))
#include	<sys/loadavg.h>
#endif

#include	<usystem.h>
#include	<timestr.h>
#include	<localmisc.h>

#include	"kinfo.h"


/* local defines */

#define	KINFO_DEFENTS	10
#define	KINFO_MAGIC		0x98743251

#define	TO_KSYSMISC	4		/* time between system_misc gets */
#define	TO_KLOADAVE	1		/* time between LOADAVE gets */
#define	TO_KUPDATE	(5 * 60)	/* time before a chain update */
#define	TO_KMAXIDLE	(10 * 60)	/* maximum idle time allowed */

#ifndef	TIMEBUFLEN
#define	TIMEBUFLEN	80
#endif


/* external subroutines */


/* external variables */


/* local structures */


/* forward referecens */

static int	kinfo_kopen(KINFO *,time_t) noex ;
static int	kinfo_kclose(KINFO *) noex ;
static int	kinfo_kupdate(KINFO *,time_t) noex ;
static int	kinfo_ksysmisc(KINFO *,time_t) noex ;
static int	kinfo_kloadave(KINFO *,time_t) noex ;


/* local variables */

static constexpr cpcchar	avenruns[] = {
	"avenrun_1min",
	"avenrun_5min",
	"avenrun_15min",
	nullptr
} ;


/* exported variables */


/* exported subroutines */

int kinfo_open(KINFO *sp,time_t ti_daytime) noex {
	int	rs = SR_OK ;

#if	CF_SAFE
	if (sp == nullptr)
	    return SR_FAULT ;
#endif

	memset(sp,0,sizeof(KINFO)) ;

	sp->tosysmisc = TO_KSYSMISC ;
	sp->toloadave = TO_KLOADAVE ;

	sp->magic = KINFO_MAGIC ;
	return rs ;
}
/* end subroutine (kinfo_open) */

int kinfo_boottime(KINFO *sp,time_t ti_daytime,KINFO _DA *kdp) noex {
	kstat_t		*ksp = nullptr ;
	int		rs = SR_OK ;

#if	CF_SAFE
	if (sp == nullptr)
	    return SR_FAULT ;

	if (sp->magic != KINFO_MAGIC)
	    return SR_NOTOPEN ;

	if (kdp == nullptr)
	    return SR_FAULT ;
#endif

	if (! sp->f.kopen) {
	    rs = kinfo_kopen(sp,ti_daytime) ;
	}

/* too tired, just do this! */

	if (rs >= 0) {
	    rs = kinfo_sysmisc(sp,ti_daytime,kdp) ;
	}
	return rs ;
}
/* end subroutine (kinfo_boottime) */

int kinfo_loadave(KINFO *sp,time_t ti_daytime,KINFO_DATA *kdp) noex {
	kstat_t		*ksp ;
	kid_t		kid ;
	int		rs = SR_OK ;

#if	CF_SAFE
	if (sp == nullptr)
	    return SR_FAULT ;

	if (sp->magic != KINFO_MAGIC)
	    return SR_NOTOPEN ;

	if (kdp == nullptr)
	    return SR_FAULT ;
#endif

	sp->ti_access = ti_daytime ;
	if ((ti_daytime - sp->ti_loadave) >= sp->toloadave) {

	    rs = kinfo_kloadave(sp,ti_daytime) ;

	    if ((rs == SR_NOSYS) || (rs == SR_NOENT)) {
	        rs = SR_OK ;
	        if (! sp->f.kopen) {
	            rs = kinfo_kopen(sp,ti_daytime) ;
		} else {
	            rs = kinfo_kupdate(sp,ti_daytime) ;
		}
	        if (rs >= 0) {
	            rs = kinfo_ksysmisc(sp,ti_daytime) ;
		}
	    } /* end if (alternative loadave information) */

	} /* end if (loadave information) */

	if ((rs >= 0) && (kdp != nullptr)) {
	    *kdp = sp->d ;
	}

	return rs ;
}
/* end subroutine (kinfo_loadave) */

int kinfo_sysmisc(KINFO *sp,time_t ti_daytime,KINFO_DATA *kdp) noex {
	kstat_t		*ksp ;
	kid_t		kid ;
	int		rs = SR_OK ;
	bool		f ;

#if	CF_SAFE
	if (sp == nullptr)
	    return SR_FAULT ;

	if (sp->magic != KINFO_MAGIC)
	    return SR_NOTOPEN ;

	if (kdp == nullptr)
	    return SR_FAULT ;
#endif

	rs = SR_TIMEDOUT ;
	sp->ti_access = ti_daytime ;
	f = ((ti_daytime - sp->ti_loadave) >= sp->toloadave) &&
	    ((ti_daytime - sp->ti_sysmisc) < sp->tosysmisc) ;

	if (f) {
	    rs = kinfo_kloadave(sp,ti_daytime) ;
	}
	if ((rs == SR_NOSYS) || (rs == SR_NOENT) ||
	    ((ti_daytime - sp->ti_sysmisc) >= sp->tosysmisc)) {

	    rs = SR_OK ;
	    if (! sp->f.kopen) {
	        rs = kinfo_kopen(sp,ti_daytime) ;
	    } else {
	        rs = kinfo_kupdate(sp,ti_daytime) ;
	    }
	    if (rs >= 0) {
	        rs = kinfo_ksysmisc(sp,ti_daytime) ;
	    }
	} /* end if (extended information) */

	if ((rs >= 0) && (kdp != nullptr)) {
	    *kdp = sp->d ;
	}

	return rs ;
}
/* end subroutine (kinfo_sysmisc) */

int kinfo_check(KINFO *sp,time_t ti_daytime) noex {
	int	rs = SR_OK ;

#if	CF_SAFE
	if (sp == nullptr)
	    return SR_FAULT ;

	if (sp->magic != KINFO_MAGIC)
	    return SR_NOTOPEN ;
#endif

/* check on the weirdo 'K' stuff */

	if (sp->f.kopen) {

	    if ((ti_daytime - sp->ti_access) >= TO_KMAXIDLE) {
	        kinfo_kclose(sp) ;
	    } /* end if */

	    if (sp->f.kopen)
	        rs = kinfo_kupdate(sp,ti_daytime) ;

	} /* end if (KOPEN) */

/* we're out of here */

	return rs ;
}
/* end subroutine (kinfo_check) */

int kinfo_close(KINFO *sp) noex {
	int		rs ;

#if	CF_SAFE
	if (sp == nullptr)
	    return SR_FAULT ;

	if (sp->magic != KINFO_MAGIC)
	    return SR_NOTOPEN ;
#endif

	rs = kinfo_kclose(sp) ;

	sp->magic = 0 ;
	return rs ;
}
/* end subroutine (kinfo_close) */


/* private subroutines */

static int kinfo_kopen(KINFO *sp,time_t ti_daytime) noex {
	int		rs = SR_OK ;
	if (! sp->f.kopen) {

	    sp->kcp = kstat_open() ;

	    if (sp->kcp != nullptr) {
	        sp->ti_access = ti_daytime ;
	        sp->ti_update = ti_daytime ;
	        sp->f.kopen = TRUE ;
	        sp->nactive += 1 ;
	    } else {
	        rs = SR_NOANODE ;
	    }
	} /* end if (was not open) */

	return rs ;
}
/* end subroutine (kinfo_kopen) */

static int kinfo_kclose(KINFO *sp) noex {
	int		rs = SR_OK ;
	int		rs1 ;
	if (sp->f.kopen) {
	    sp->f.kopen = FALSE ;
	    if (sp->kcp != nullptr) {
	        if ((rs1 = kstat_close(sp->kcp)) < 0) {
		    rs1 = SR_NXIO ;
		}
		if (rs >= 0) rs = rs1 ;
	        sp->kcp = nullptr ;
	    }
	    if (sp->nactive > 0) sp->nactive -= 1 ;
	} /* end if (was open) */
	return rs ;
}
/* end subroutine (kinfo_kclose) */

static int kinfo_kupdate(KINFO *sp,time_t ti_daytime) noex {
	int		rs = SR_OK ;
	if (sp->f.kopen) {
	    if ((ti_daytime - sp->ti_update) >= TO_KUPDATE) {
	        sp->ti_update = ti_daytime ;
	        (void) kstat_chain_update(sp->kcp) ;
	    } /* end if */
	} /* end if (kopen) */
	return rs ;
}
/* end subroutine (kinfo_kupdate) */

static int kinfo_ksysmisc(KINFO *sp,time_t ti_daytime) noex {
	kstat_t		*ksp ;
	kid_t		kid ;
	int		rs = SR_OK ;
	bool		f ;
	ksp = kstat_lookup(sp->kcp,"unix",0,"system_misc") ;

	if ((rs >= 0) && (ksp != nullptr)) {

	    if ((kid = kstat_read(sp->kcp, ksp, nullptr)) >= 0) {
	        kstat_named_t *ksn ;

	        sp->ti_sysmisc = ti_daytime ;
	        sp->ti_loadave = ti_daytime ;
	        ksn = (kstat_named_t *)
	            kstat_data_lookup(ksp,"ncpus") ;

	        if (ksn != nullptr)
	            sp->d.ncpu = ksn->value.ui32 ;

	        ksn = (kstat_named_t *)
	            kstat_data_lookup(ksp,"nproc") ;

	        if (ksn != nullptr) {
	            sp->d.nproc = ksn->value.ui32 ;
		}
	        for (int i = 0 ; i < 3 ; i += 1) {
	            ksn = (kstat_named_t *)
	                kstat_data_lookup(ksp,(char *) avenruns[i]) ;

	            if (ksn != nullptr) {
	                sp->d.la[i] = ksn->value.ui32 ;
		    }
	        } /* end for */

	        if (sp->d.boottime == 0) {

	            ksn = (kstat_named_t *)
	                kstat_data_lookup(ksp,"boot_time") ;

	            if (ksn != nullptr) {
	                sp->d.boottime = ksn->value.ui32 ;
		    }
	        } /* end if */
	        rs = SR_OK ;

	    } /* end if (reading data) */

	} else {
	    rs = SR_NOTFOUND ;
	}

	return rs ;
}
/* end subroutine (kinfo_ksysmisc) */

static int kinfo_kloadave(KINFO *sptime_t ti_daytime) noex {
	int	rs = SR_OK ;

#if	(defined(SYSHAS_LOADAVG) && (SYSHAS_LOADAVG > 0))
	{
	    uint	las[3] ;
	    if ((rs = u_getloadavg(las,3)) >= 0) {
	        sp->ti_loadave = ti_daytime ;
	        for (int i = 0 ; i < 3 ; i += 1) {
	            sp->d.la[i] = las[i] ;
	        }
	    } /* end if (had |loadavg(3c)|) */

	}
#else /* SYSHAS_LOADAVG */

	rs = SR_NOSYS ;

#endif /* SYSHAS_LOADAVG */

	return rs ;
}
/* end subroutine (kinfo_kloadave) */


