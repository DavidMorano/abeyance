/* usys_ufcntl HEADER */
/* lang=C20 */

/* UNIX® system emulated support */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This is a utility function for use by other emulators.

*******************************************************************************/

#ifndef	USYSUFCNTL_INCLUDE
#define	USYSUFCNTL_INCLUDE
#ifdef	__cplusplus


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


namespace usys {
    extern sysret_t ufcntl(int,int,...) noex ;
    extern sysret_t ucloseonexec(int,int) noex ;
    extern sysret_t unonblock(int,int) noex ;
}


#endif /* __cplusplus */
#endif /* USYSUFCNTL_INCLUDE */


