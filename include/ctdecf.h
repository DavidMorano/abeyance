/* ctdecf HEADER */
/* lang=C++20 */

/* subroutines to convert an floating-value to a decimal string */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	CTDECF_INCLUDE
#define	CTDECF_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<stdintx.h>


EXTERNC_begin

extern int	ctdecf(char *,int,double,int,int,int,int) noex ;

EXTERNC_end


#endif /* CTDECF_INCLUDE */


