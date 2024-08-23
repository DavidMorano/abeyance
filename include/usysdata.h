/* usysdata HEADER (UNIX® system operations) */
/* lang=C20 */

/* translation layer interface for UNIX® equivalents */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services
	(RNS).

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Names:

	Description:
	These subroutines mange the operating system itself.

*******************************************************************************/

#ifndef	USYSDATA_INCLUDE
#define	USYSDATA_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/types.h>		/* system types */
#include	<sys/utsname.h>		/* |UTSNAME| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>

#include	<usysauxinfo.h>		/* the request codes */


EXTERNC_begin

extern int u_uname(UTSNAME *) noex ;
extern int u_getnodename(char *,int) noex ;
extern int u_getauxinfo(char *,int,int) noex ;
extern int u_gethostid(ulong *) noex ;

EXTERNC_end

#ifdef	__cplusplus

namespace libu {
    extern int loadhostid(char *,int) noex ;
    extern int ugethostid(ulong *) noex ;
}

#endif /* __cplusplus */


#endif /* USYSDATA_INCLUDE */


