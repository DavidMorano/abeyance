/* ucopenpsem SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 */

/* interface component for UNIX® library-3c */
/* open a Posix Semaphore (PSEM) */


/* revision history:

	= 1999-07-23, David A­D­ Morano
	This module was originally written.

*/

/* Copyright © 1999 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Name:
	ucopenpsem

	Description:
	This module provides a sanitized version of the standard
	POSIX semaphore facility provided with some new UNIX®i.
	Some operating system problems are managed within these
	routines for the common stuff that happens when a poorly
	configured OS gets overloaded!

	Enjoy!

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/stat.h>
#include	<unistd.h>
#include	<semaphore.h>
#include	<cerrno>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<usystem.h>
#include	<libmallocxx.h>
#include	<sncpyx.h>
#include	<localmisc.h>

#include	"psem.h"


/* local defines */

#define	TO_NOSPC	5
#define	TO_MFILE	5
#define	TO_INTR		5

#ifndef	PSEM_NAMELEN
#define	PSEM_NAMELEN	MAXNAMELEN
#endif


/* local namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int uc_openpsem(cchar *name,int of,mode_t om,uint count,PSEM **rpp) noex {
	int		rs ;
	int		to_mfile = TO_MFILE ;
	int		to_nospc = TO_NOSPC ;
	int		f_exit = FALSE ;
	char		altname[PSEM_NAMELEN + 1] ;

	if (rpp == NULL) return SR_FAULT ;
	if (name == NULL) return SR_FAULT ;

	if (name[0] == '\0') return SR_INVALID ;

	if (name[0] != '/') {
	    sncpy2(altname,PSEM_NAMELEN,"/",name) ;
	    name = altname ;
	}

	memclear(*rpp) ;

	repeat {
	    rs = SR_OK ;
	    if ((*rpp = sem_open(name,of,om,count)) == SEM_FAILED) {
		rs = (- errno) ;
	    }
	    if (rs < 0) {
	        switch (rs) {
	        case SR_NFILE:
	            if (to_mfile-- > 0) {
	                msleep(1000) ;
		    } else {
			f_exit = true ;
		    }
	            break ;
	        case SR_NOSPC:
	            if (to_nospc-- > 0) {
	                msleep(1000) ;
		    } else {
			f_exit = true ;
		    }
	            break ;
	        case SR_INTR:
	            break ;
		default:
		    f_exit = true ;
		    break ;
	        } /* end switch */
	    } /* end if (error) */
	} until ((rs >= 0) || f_exit) ;

	return rs ;
}
/* end subroutine (uc_openpsem) */


