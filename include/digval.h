/* digval HEADER */
/* lang=C20 */

/* get the value of a single hexadecimal digit */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	DIGVAL_INCLUDE
#define	DIGVAL_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


EXTERNC_begin

extern int	digval(int) noex ;

extern int	digvalbin(int) noex ;
extern int	digvaloct(int) noex ;
extern int	digvaldec(int) noex ;
extern int	digvalhex(int) noex ;

EXTERNC_end


#endif /* DIGVAL_INCLUDE */


