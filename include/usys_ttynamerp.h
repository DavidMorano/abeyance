/* usys_ttynamerp HEADER */
/* lang=C20 */

/* miscelllaneous (XXX) operating system support */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This file contains the UNIX® system types that the brain-damaged
	MacOS operating system does NOT have.  We are trying in a very
	small way to make up for some of the immense brain-damage within
	the Apple Darwin (macOS) operating system.


*******************************************************************************/

#ifndef	USYSTTYNAMERP_INCLUDE
#define	USYSTTYNAMERP_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>

#ifndef	SUBROUTINE_TTYNAMERP
#define	SUBROUTINE_TTYNAMERP
EXTERNC_begin

extern errno_t ttyname_rp(int,char *,int) noex ;

EXTERNC_end
#endif /* SUBROUTINE_TTYNAMERP */


#endif /* USYSTTYNAMERP_INCLUDE */


