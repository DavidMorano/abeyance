/* ucmemla HEADER */
/* lang=C20 */

/* object to provide large0allocation memory */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

	= 2017-08-01, David A­D­ Morano
	Updated for lack of interfaces in Apple-Darwin

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This object provides a large-allocation memory capability.

*******************************************************************************/

#ifndef	UCMEMLA_INCLUDE
#define	UCMEMLA_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>


#define	UCMEMLA		struct ucmemla_head
#define	UCMEMLA_LARGE	(8*4096)


struct ucmemla_head {
	void		*ma ;
	size_t		ms ;
	int		f_large ;
} ;

typedef UCMEMLA		ucmemla ;

EXTERNC_begin

extern int	ucmemla_acquire(ucmemla *,size_t,void *) noex ;
extern int	ucmemla_release(ucmemla *) noex ;

EXTERNC_end


#endif /* UCMEMLA_INCLUDE */


