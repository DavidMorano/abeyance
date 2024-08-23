/* gethz HEADER */
/* lang=C20 */

/* get the HZ ("hertz") value from the operating system */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETHZ_INCLUDE
#define	GETHZ_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


enum gethzes {
	gethz_any,
	gethz_const,
	gethz_env,
	gethz_tck,
	gethz_conf,
	gethz_guess,
	gethz_overlast
} ;

EXTERNC_begin

extern int	gethz(int) noex ;

EXTERNC_end


#endif /* GETHZ_INCLUDE */


