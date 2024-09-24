/* dfibonacci HEADER */
/* lang=C20 */

/* calculate double-precision fibonacci */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	DFIBONACCI_INCLUDE
#define	DFIBONACCI_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>


EXTERNC_begin

extern double	dfibonacci(int) noex ;

EXTERNC_end


#endif /* DFIBONACCI_INCLUDE */


