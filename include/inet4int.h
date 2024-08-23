/* inet4int HEADER */
/* lang=C20 */

/* some INET-related subroutine */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

	= 2017-08-01, David A­D­ Morano
	Updated for lack of interfaces in Apple-Darwin

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This file contains some support for the UNIX® INET4INT related
	operations.

*******************************************************************************/

#ifndef	INET4INT_INCLUDE
#define	INET4INT_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>


EXTERNC_begin

extern uint	inet4int(cvoid *) noex ;

EXTERNC_end


#endif /* INET4INT_INCLUDE */


