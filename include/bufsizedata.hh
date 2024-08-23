/* bufsizedata HEADER */
/* lang=C++20 */

/* buffer-size-data (default value database) */
/* version %I% last-modified %G% */


/* revision history:

	= 2014-06-17, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 2014 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This module provides the database from which decisions are made
	for determing buffer sizes.  A decision about how to determine
	any particular buffer size is make at the point when a particular
	buffer size is required.  This data base takes the most simplest
	of forms: an array of structures (|bufsuzeitem|).

	Oh, I almost forgot. I am using the new |constexpr| features
	of C++14. I waited for this C++14 enhancements to |constexpr|
	for these many years. I knew that the embicilic implemention
	of |constexpr| in C+14 needed to be enhanced (and eventually
	so it was).  Merry programming!


*******************************************************************************/

#ifndef	BUFSIZEDATA_INCLUDE
#define	BUFSIZEDATA_INCLUDE
#ifdef	__cplusplus /* everything is C++ only */


#include	<envstandards.h>	/* ordered first to configure */
#include	<unistd.h>		/* |_SC_xx| */
#include	<climits>
#include	<usystem.h>
#include	<localmisc.h>

#include	"getbufsizenames.h"
#include	"usysdefs.h"


#ifndef	_SC_ARG_MAX
#define	_SC_ARG_MAX		-1
#endif
#ifndef	_SC_NAME_MAX
#define	_SC_NAME_MAX		-1
#endif
#ifndef	_SC_PATH_MAX
#define	_SC_PATH_MAX		-1
#endif
#ifndef	_SC_LINE_MAX
#define	_SC_LINE_MAX		-1
#endif
#ifndef	_SC_HOST_NAME_MAX		/* really the "nodename" length */
#define	_SC_HOST_NAME_MAX	-1
#endif
#ifndef	_SC_LOGIN_NAME_MAX
#define	_SC_LOGIN_NAME_MAX	-1
#endif
#ifndef	_SC_GETPW_R_SIZE_MAX
#define	_SC_GETPW_R_SIZE_MAX	-1
#endif
#ifndef	_SC_GETGR_R_SIZE_MAX
#define	_SC_GETGR_R_SIZE_MAX	-1
#endif
#ifndef	_SC_TZNAME_MAX
#define	_SC_TZNAME_MAX		-1
#endif


namespace {
    struct bufsizeitem {
	int	name ;
	int	defval ;
    } ;
    struct bufsizedata {
	bufsizeitem	item[getbufsize_overlast] = {} ;
	constexpr bufsizedata() noex ;
	constexpr bufsizeitem operator [] (int w) const noex {
	    bufsizeitem		def{-1,0} ;
	    bufsizeitem		it = def ;
	    if ((w >= 0) && (w < getbufsize_overlast)) {
	        it = item[w] ;
	    }
	    return it ;
	} ; /* end method (operator) */
   } ; /* end class (bufsizedata) */
}

constexpr bufsizedata::bufsizedata() noex {
	for (int i = 0 ; i < getbufsize_overlast ; i += 1) {
	    bufsizeitem	*ip = (item+i) ;
	    ip->name = -1 ;
	    switch (i) {
	    case getbufsize_ma:
	        ip->name = _SC_ARG_MAX ;
		ip->defval = ARBUFLEN ;
	        break ;
	    case getbufsize_mn:		/* max-name */
	        ip->name = _SC_NAME_MAX ;
		ip->defval = MNBUFLEN ;
	        break ;
	    case getbufsize_mp:		/* max-path */
	        ip->name = _SC_PATH_MAX ;
	        ip->defval = MPBUFLEN ;
	        break ;
	    case getbufsize_ml:		/* max-line */
	        ip->name = _SC_LINE_MAX ;
		ip->defval = MLBUFLEN ;
	        break ;
	    case getbufsize_nn:		/* node-name */
	        ip->name = _SC_HOST_NAME_MAX ; /* <- really is "nodename" */
		ip->defval = NNBUFLEN ;
	        break ;
	    case getbufsize_hn:		/* host-name */
	        ip->defval = HNBUFLEN ;
	        break ;
	    case getbufsize_un:		/* user-name */
		ip->name = _SC_LOGIN_NAME_MAX ;
	        ip->defval = UNBUFLEN ;
	        break ;
	    case getbufsize_gn:		/* group-name */
	        ip->defval = GNBUFLEN ;
	        break ;
	    case getbufsize_pn:		/* project-name */
	        ip->defval = PNBUFLEN ;
	        break ;
	    case getbufsize_pw:
	        ip->name = _SC_GETPW_R_SIZE_MAX ;
		ip->defval = PWBUFLEN ;
	        break ;
	    case getbufsize_sp:
	        ip->defval = SPBUFLEN ;
	        break ;
	    case getbufsize_ua:
	        ip->defval = UABUFLEN ;
	        break ;
	    case getbufsize_gr:
		ip->name = _SC_GETGR_R_SIZE_MAX ;
		ip->defval = GRBUFLEN ;
	        break ;
	    case getbufsize_pj:
		ip->defval = PJBUFLEN ;		/* project-buf */
	        break ;
	    case getbufsize_pr:
		ip->defval = PRBUFLEN ;		/* protocol-buf */
	        break ;
	    case getbufsize_nw:
		ip->defval = NWBUFLEN ;		/* network-buf */
	        break ;
	    case getbufsize_ho:
		ip->defval = HOBUFLEN ;		/* host-buf */
	        break ;
	    case getbufsize_sv:
		ip->defval = SVBUFLEN ;		/* service-buf */
	        break ;
	    case getbufsize_zn:
	        ip->name = _SC_TZNAME_MAX ;
		ip->defval = ZNBUFLEN ;
	        break ;
	    } /* end switch */
	} /* end for */
}
/* end method (bufsizedata:bufsizedata) */


#endif	/* __cplusplus */
#endif /* BUFSIZEDATA_INCLUDE */


