/* netgroupcheck HEADER */
/* lang=C20 */

/* Make-a-Quoted c-string (from a source c-string) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	NETGROUPCHECK_INCLUDE
#define	NETGROUPCHECK_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<vecstr.h>


EXTERNC_begin

extern int netgroupcheck(cchar *,vecstr *,vecstr *) noex ;

EXTERNC_end


#endif /* NETGROUPCHECK_INCLUDE */


