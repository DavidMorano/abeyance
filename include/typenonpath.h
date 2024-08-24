/* typenonpath HEADER */
/* lang=C20 */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	TYPENONPATH_INCLUDE
#define	TYPENONPATH_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>


enum nonpathtypes {
	nonpathtype_not,
	nonpathtype_dialer,
	nonpathtype_fsvc,
	nonpathtype_usvc,
	nonpathtype_overlast
} ;

EXTERNC_begin

extern bool typenonpath(cchar *,int) noex ;

EXTERNC_end


#endif /* TYPENONPATH_INCLUDE */


