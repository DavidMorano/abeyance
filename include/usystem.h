/* usystem HEADER */
/* lang=C20 */

/* version %I% last-modified %G% */
/* virtual-system definitions */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

	= 2017-08-01, David A­D­ Morano
	Updated for lack of interfaces in MacOS Darwin

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

#ifndef	USYSTEM_INCLUDE
#define	USYSTEM_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */

#include	<sys/types.h>
#include	<sys/utsname.h>
#include	<sys/uio.h>
#include	<sys/time.h>		/* for |u_adjtime(3u)| */
#include	<sys/timeb.h>		/* for |uc_ftime(3uc)| */
#include	<sys/resource.h>
#include	<sys/stat.h>
#include	<sys/statvfs.h>
#include	<sys/socket.h>
#include	<sys/poll.h>
#include	<sys/socket.h>

#if	defined(SYSHAS_ACL) && (SYSHAS_ACL > 0)
#include	<sys/acl.h>
#endif

#include	<signal.h>
#include	<ucontext.h>
#include	<limits.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<utime.h>		/* for |u_utime(2)| */
#include	<pthread.h>
#include	<termios.h>
#include	<time.h>
#include	<errno.h>
#include	<netdb.h>
#include	<pwd.h>
#include	<grp.h>
#include	<dirent.h>

#include	<usys.h>	/* <- auxilllary OS support */

#include	<clanguage.h>
#include	<usysdefs.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<usupport.h>
#include	<stdintx.h>

#include	<uinet.h>
#include	<uopen.h>
#include	<usyscalls.h>
#include	<uxti.h>
#include	<upthread.h>

#include	<ucent.h>
#include	<ucfunctioncodes.h>
#include	<ucopen.h>
#include	<uclibsubs.h>



#endif /* USYSTEM_INCLUDE */


