/* hashindex HEADER */
/* lang=C20 */

/* hash-index */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	HASHINDEX_INCLUDE
#define	HASHINDEX_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<localmisc.h>		/* |MODP2| */


EXTERNC_begin

static inline int hashindex(uint i,int n) noex {
	int		hi = MODP2(i,n) ;
	if (hi == 0) hi = 1 ;
	return hi ;
}

EXTERNC_end


#endif /* HASHINDEX_INCLUDE */


