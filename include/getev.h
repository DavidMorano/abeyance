/* getev HEADER */
/* lang=C20 */

/* UNIX® Environment-Variable support */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

	= 2017-08-01, David A­D­ Morano
	Updated for lack of interfaces in Apple-Darwin

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This file contains some support for the UNIX® environment
	variable operations.

*******************************************************************************/

#ifndef	GETEV_INCLUDE
#define	GETEV_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern int	getev(mainv,cchar *,int,cchar **) noex ;

EXTERNC_end


#endif /* GETEV_INCLUDE */


