/* uc_ptsname SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* interface component for UNIX® library-3c */
/* get the filename (path) of a slave-pseudo terminal device */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-01, David A­D­ Morano
	This is written to get a portable (reentrant and thread-safe)
	version of PTRNAME as we can get.

	= 2018-10-03, David A-D- Morano
	I modernized this by replacing custom path creation crap
	with a call to the |snsd(3uc)| subroutine.

*/

/* Copyright © 1998,2018 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Name:
	uc_ptsname

	Description:
	This code only has meaning on the newer System V UNIX®.
	releases with the PTS dirver.  This is now needed to get the
	filename of the slave side device of the new pseudo-terminal
	clone multiplexor driver. A new slave-side filename looks
	something like '/dev/pts/26'.

	Unlike other versions of this sort of function, this is
	thread-safe!

	The algorithm (from SVR3 docs) is:

	Check that the FD argument is a file descriptor of an opened
	master.  Do this by sending an ISPTM ioctl message down
	stream.  Ioctl() will fail if: (1) FD is not a valid file
	descriptor, (2) the file represented by FD does not understand
	ISPTM (not a master device). If we have a valid master, get
	its minor number via |fstat(2)|.  Concatenate it to PTSPREFIX
	and return it as the name of the slave device.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/stream.h>
#include	<sys/stat.h>
#include	<sys/ptms.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<usystem.h>
#include	<snx.h>
#include	<localmisc.h>


/* local defines */

#define	PTSPREFIX	"/dev/pts/"	/* slave name */
#define	PTSPREFIXLEN	9		/* length of above string */
#define	PTSMAXLEN	32		/* slave name length */
#define	PTSMAXDEVS	100000000	/* rather arbitrary */


/* external subroutines */


/* forward references */


/* exported subroutines */

int uc_ptsname(int fd,char *nbuf,int nlen) noex {
	int		rs = SR_FAULT ;
	int		len = 0 ;
	if (nbuf) {
	    STRIOCTL	istr{} ;
	    istr.ic_cmd = ISPTM ;
	    istr.ic_len = 0 ;
	    istr.ic_timout = 0 ;
	    istr.ic_dp = nullptr ;
	    if ((rs = u_ioctl(fd,I_STR,&istr)) >= 0) {
	        if (ustat sb ; (rs = u_fstat(fd,&sb)) >= 0) {
		    uint	minordev = minor(sb.st_rdev) ;
		    if (minordev < PTSMAXDEVS) {
		        if ((rs = snsd(nbuf,nlen,PTSPREFIX,minordev)) >= 0) {
			    len = rs ;
		            rs = u_access(nbuf,0) ;
		        }
		    } else {
	    	        rs = SR_INVALID ;
		    }
	        } /* end if (u_fstat) */
	    } /* end if (u_ioctl) */
	} /* end if (non-null) */
	return (rs >= 0) ? len : rs ;
}
/* end subroutine (uc_ptsname) */


