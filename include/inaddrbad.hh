/* inaddrbad HEADER */
/* lang=C20 */

/* create an "inaddrbad" constant */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	INADDRBAD_INCLUDE
#define	INADDRBAD_INCLUDE
#ifdef	__cplusplus /* everything is C++ only */


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>		/* <- for |in_addr_t| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


consteval in_addr_t mkinaddrbad() noex {
	in_addr_t	a = 0 ;
	return (~a) ;
}


#endif	/* __cplusplus */
#endif /* INADDRBAD_INCLUDE */


