/* getenver HEADER */
/* lang=C20 */

/* UNIX® Environment-Variable support */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This file contains some support for the UNIX® environment
	variable operations.

*******************************************************************************/

#ifndef	GETENVER_INCLUDE
#define	GETENVER_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>


EXTERNC_begin

extern cchar	*getenver(cchar *,int) noex ;

EXTERNC_end


#endif /* GETENVER_INCLUDE */


