/* partitionai HEADER */
/* lang=C++20 */


/* revision history:

	= 2001-10-04, David A­D­ Morano
	This was originally written.

*/

/* Copyright © 2001 David A­D­ Morano.  All rights reserved. */

#ifndef	PARTITIONAI_INCLUDE
#define	PARTITIONAI_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<usyscalls.h>


EXTERNC_begin

extern int	partitionai(int *,int,int (*)(int,int),int) noex ;

EXTERNC_end


#endif /* PARTITIONAI_INCLUDE */


