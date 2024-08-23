/* sysnoise HEADER */
/* lang=C20 */

/* retrieve some system noise (pswudo-random data) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	SYSNOISE_INCLUDE
#define	SYSNOISE_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern int	sysnoise(uchar *,int) noex ;

EXTERNC_end


#endif /* SYSNOISE_INCLUDE */


