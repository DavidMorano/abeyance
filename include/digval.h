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


EXTERNC_begin

extern int hexval(int) noex ;
extern int decval(int) noex ;
extern int digval(int) noex ;

EXTERNC_end


#endif /* DIGVAL_INCLUDE */


