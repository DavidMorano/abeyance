/* getrandom HEADER */
/* lang=C20 */

/* get some random data (some bytes) of a specified type */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETRANDOM_INCLUDE
#define	GETRANDOM_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>


EXTERNC_begin

extern int getrandom(void *,size_t,uint) noex ;

EXTERNC_end


#endif /* GETRANDOM_INCLUDE */


