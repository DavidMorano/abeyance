/* ucgethost SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 */

/* interface components for UNIX® library-3c */
/* subroutine to get a single "host" entry (raw) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This program was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	uc_gethostbyname

	Description:
	This subroutine is a platform independent subroutine to get
	an INET host address entry, but does it dumbly on purpose.

	Synopsis:
	int uc_gethostbyname(ucentho *hep,char *hebuf,int helen,cc *name) noex

	Arguments:
	- hep		pointer to 'hostent' structure
	- hebuf		user supplied buffer to hold result
	- helen		length of user supplied buffer
	- name		name to lookup

	Returns:
	0		host was found OK
	SR_FAULT	address fault
	SR_TIMEDOUT	request timed out (bad network someplace)
	SR_NOTFOUND	host could not be found


	Name:
	uc_gethostbyaddr

	Description:
	This subroutine is a platform independent subroutine to get
	an INET host address entry, but does it dumbly on purpose.

	Synopsis:
	int uc_gethostbyaddr(ucentho *hep,char *hebuf,int helen,
			int af,cc *ap,int al) noex

	Arguments:

	- hep		pointer to 'hostent' structure
	- hebuf		user supplied buffer to hold result
	- helen		length of user supplied buffer
	- af		address-family of address to look up
	- ap		address to lookup
	- al		length if the supplied address

	Returns:
	0		host was found OK
	SR_FAULT	address fault
	SR_TIMEDOUT	request timed out (bad network someplace)
	SR_NOTFOUND	host could not be found

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<unistd.h>
#include	<netdb.h>
#include	<cerrno>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<usystem.h>
#include	<usupport.h>
#include	<storeitem.h>
#include	<hostent.h>
#include	<localmisc.h>

#include	"ucgethost.h"


/* local defines */

#if	defined(SYSHAS_GETHOXXXR) && (SYSHAS_GETHOXXXR > 0)
#define	CF_REENT	1
#else
#define	CF_REENT	0
#endif /* SYSHAS_GETHOXXXR */

#define	NLOOPS		3


/* external subroutines */


/* external variables */

#if	(CF_REENT == 0)
extern int	h_errno ;
#endif


/* local structures */


/* forward references */

static int	gethosterr(int) noex ;


/* local variables */

constexpr bool	f_reent = CF_REENT ;


/* exported variables */


/* exported subroutines */

int uc_gethostbegin(int stayopen) noex {
	int		rs = SR_INVALID ;
	if (stayopen >= 0) {
	    errno = 0 ;
	    sethostent(stayopen) ;
	    rs = (- errno) ;
	}
	return rs ;
}
/* end subrouttine (uc_gethostbegin) */

int uc_gethostend() noex {
	errno = 0 ;
	endhostent() ;
	return (- errno) ;
}
/* end subrouttine (uc_gethostend) */

int uc_gethostent(HOSTENT *hep,char *hebuf,int helen) noex {
	int		rs = SR_FAULT ;
	if (hep && hebuf) {
	    rs = SR_OVERFLOW ;
	    if (helen > 0) {
	        /* do the real work */
	        HOSTENT		*lp ;
	        if_constexpr (f_reent) {
	            int		herr ; 
		    auto get = gethostent_r ;
	            for (int i = 0 ; i < NLOOPS ; i += 1) {
	                if (i > 0) msleep(1000) ;
	                rs = SR_OK ;
	                errno = 0 ;
			herr = 0 ;
			lp = get(hep,hebuf,helen,&herr) ;
	                if (lp != nullptr) break ;
	                rs = gethosterr(herr) ;
	                if (rs != SR_AGAIN) break ;
	            } /* end for */
	            if (rs >= 0) {
	                rs = hostent_size(hep) ;
	            } else if (rs == SR_AGAIN) {
	                rs = SR_TIMEDOUT ;
	            }
	        } else {
		    auto get = gethostent ;
	            for (int i = 0 ; i < NLOOPS ; i += 1) {
	                if (i > 0) msleep(1000) ;
	                rs = SR_OK ;
	                errno = 0 ;
	                h_errno = 0 ;
	                lp = get() ;
	                if (lp != nullptr) break ;
	                rs = gethosterr(h_errno) ;
	                if (rs != SR_AGAIN) break ;
	            } /* end for */
	            if (rs >= 0) {
	                rs = hostent_load(hep,hebuf,helen,lp) ;
	            } else if (rs == SR_AGAIN) {
	                rs = SR_TIMEDOUT ;
	            }
	        } /* end if_constexpr (f_reent) */
	        if (rs == SR_PROTONOSUPPORT) rs = SR_OK ;
	    } /* end if (valid) */
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (uc_gethostent) */

int uc_gethostbyname(HOSTENT *hep,char *hebuf,int helen,cc *name) noex {
	int		rs = SR_FAULT ;
	if (hep && hebuf && name) {
	    rs = SR_OVERFLOW ;
	    if (helen > 0) {
		/* do the real work */
		HOSTENT		*lp ;
	        if_constexpr (f_reent) {
	            int		herr ; 
		    auto get = gethostbyname_r ;
	            for (int i = 0 ; i < NLOOPS ; i += 1) {
	                if (i > 0) msleep(1000) ;
	                rs = SR_OK ;
	                errno = 0 ;
	                herr = 0 ;
	                lp = get(name,hep,hebuf,helen,&herr) ;
	                if (lp != nullptr) break ;
	                rs = gethosterr(herr) ;
	                if (rs != SR_AGAIN) break ;
	            } /* end for */
	            if (rs >= 0) {
	                rs = hostent_size(hep) ;
	            } else if (rs == SR_AGAIN) {
	                rs = SR_TIMEDOUT ;
	            }
	        } else {
		    auto get = gethostbyname ;
	            for (int i = 0 ; i < NLOOPS ; i += 1) {
	                if (i > 0) msleep(1000) ;
	                rs = SR_OK ;
	                errno = 0 ;
	                h_errno = 0 ;
	                lp = get(name) ;
	                if (lp != nullptr) break ;
	                rs = gethosterr(h_errno) ;
	                if (rs != SR_AGAIN) break ;
        
	            } /* end for */
	            if (rs >= 0) {
	                rs = hostent_load(hep,hebuf,helen,lp) ;
	            } else if (rs == SR_AGAIN) {
	                rs = SR_TIMEDOUT ;
	            }
	        } /* end if_constexpr (f_reent) */
	    } /* end if (valid) */
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (uc_gethostbyname) */

int uc_gethostbyaddr(HOSTENT *hep,char *hebuf,int helen,
		int af,cc *ap,int al) noex {
	int		rs = SR_FAULT ;
	if (hep && hebuf && ap) {
	    rs = SR_OVERFLOW ;
	    if (helen > 0) {
	        /* do the real work */
		HOSTENT		*lp ;
	        if_constexpr (f_reent) {
	            int		herr ;
		    auto get = gethostbyaddr_r ;
	            for (int i = 0 ; i < NLOOPS ; i += 1) {
	                if (i > 0) msleep(1000) ;
	                rs = SR_OK ;
	                errno = 0 ;
	                herr = 0 ;
	                lp = get(ap,al,af,hep,hebuf,helen,&herr) ;
	                if (lp != nullptr) break ;
	                rs = gethosterr(herr) ;
	                if (rs != SR_AGAIN) break ;
	            } /* end for */
	            if (rs >= 0) {
	                rs = hostent_size(hep) ;
	            } else if (rs == SR_AGAIN) {
	                rs = SR_TIMEDOUT ;
	            }
	        } else {
		    auto get = gethostbyaddr ;
	            for (int i = 0 ; i < NLOOPS ; i += 1) {
	                if (i > 0) msleep(1000) ;
	                rs = SR_OK ;
	                errno = 0 ;
	                h_errno = 0 ;
	                lp = get(ap,al,af) ;
	                if (lp != nullptr) break ;
	                rs = gethosterr(h_errno) ;
	                if (rs != SR_AGAIN) break ;
	            } /* end for */
	            if (rs >= 0) {
	                rs = hostent_load(hep,hebuf,helen,lp) ;
	            } else if (rs == SR_AGAIN) {
	                rs = SR_TIMEDOUT ;
	            }
	        } /* end if_constexpr (f_reent) */
	    } /* end if (valid) */
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (uc_gethostbyaddr) */


/* local subroutines */

static int gethosterr(int h_errno) noex {
	int		rs = SR_OK ;
	if (errno != 0) {
	    rs = (- errno) ;
	} else {
	    switch (h_errno) {
	    case TRY_AGAIN:
	        rs = SR_AGAIN ;
	        break ;
	    case NO_DATA:
	        rs = SR_HOSTUNREACH ;
	        break ;
	    case NO_RECOVERY:
	        rs = SR_IO ;
	        break ;
	    case HOST_NOT_FOUND:
	        rs = SR_NOTFOUND ;
	        break ;
	    case NETDB_INTERNAL:
	        rs = SR_AFNOSUPPORT ;	/* suggested from Solaris® */
	        break ;
	    default:
	        rs = SR_PROTONOSUPPORT ;
	        break ;
	    } /* end switch */
	} /* end if (errno) */
	return rs ;
}
/* end subroutine (gethosterr) */


