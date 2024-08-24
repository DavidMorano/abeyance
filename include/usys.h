/* usys HEADER */
/* lang=C20 */

/* version %I% last-modified %G% */
/* auxillary operating system support */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

	= 2017-08-01, David A­D­ Morano
	Updated for lack of interfaces in MacOS Darwin

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This file contains the UNIX® system types that the brain-damaged
	MacOS operating system does NOT have.  We are trying in a very
	small way to make up for some of the immense brain-damage within
	the Apple Darwin operating system.

*******************************************************************************/

#ifndef	USYS_INCLUDE
#define	USYS_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */

#include	<usys_typedefs.h>	/* should be ordered first */

#include	<usys_xxx.h>
#include	<usys_sunos.h>
#include	<usys_darwin.h>
#include	<usys_linux.h>

/* utilities */
#include	<usys_ufcntl.h>
#include	<usys_ugetdents.h>
#include	<usys_ugetnisdom.h>
#include	<usys_usendfile.h>
#include	<usys_ufstype.h>

/* missing operating system calls */
#include	<usys_mqueue.h>
#include	<usys_gethrtime.h>
#include	<usys_getrandom.h>
#include	<usys_ttynamerp.h>
#include	<usys_stime.h>
#include	<usys_resolvepath.h>
#include	<usys_waitid.h>
#include	<usys_sigx.h>
#include	<usys_streams.h>
#include	<usys_pipes.h>
#include	<usys_stat.h>
#include	<usys_libstr.h>


#endif /* USYS_INCLUDE */


