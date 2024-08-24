/* ndig HEADER */
/* lang=C20 */

/* calculate number of digits */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	NDIG_INCLUDE
#define	NDIG_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern int ndig(double *,int) noex ;
extern int ndigmax(double *,int,int) noex ;

EXTERNC_end


#endif /* NDIG_INCLUDE */


