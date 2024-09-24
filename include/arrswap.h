/* arrswap HEADER */
/* lang=C20 */

/* get a seed value for use in initializing a true RNG */
/* version %I% last-modified %G% */


/* revision history:

	= 2003-03-04, David A.D. Morano
	This was written from scratch.

*/

/* Copyright © 2003 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	arrswap

	Description:
	This subroutine returns a seed value for use in initializing
	a true RNG.

	Synopsis:
	int arrswap() noex

	Arguments:
	-

	Returns:
	>=0		0=BSD, 1=SYSV
	<0		error (system-return)

*******************************************************************************/

#ifndef	ARRSWAP_INCLUDE
#define	ARRSWAP_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<stdintx.h>


EXTERNC_begin
extern void	arrswapi(int *,int,int) noex ;
extern void	arrswapl(long *,int,int) noex ;
extern void	arrswapll(longlong *,int,int) noex ;
EXTERNC_end


#endif /* ARRSWAP_INCLUDE */


