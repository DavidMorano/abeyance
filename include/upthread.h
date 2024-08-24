/* upthread HEADER */
/* lang=C20 */

/* additional UNIX® limits support */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

	= 2017-08-01, David A­D­ Morano
	Updated for lack of interfaces in Apple-Darwin

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Additional (or supplemental) support for UNIX® limits.

*******************************************************************************/

#ifndef	UPTHREAD_INCLUDE
#define	UPTHREAD_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<signal.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<usystem.h>


EXTERNC_begin

#ifndef	TYPEDEF_VOIDF
#define	TYPEDEF_VOIDF
typedef void (*void_f)() noex ;
#endif

EXTERNC_end


#endif /* UPTHREAD_INCLUDE */


