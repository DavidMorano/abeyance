/* matparam HEADER */
/* lang=C20 */

/* does the parameter array have a given value? */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MATPARAM_INCLUDE
#define	MATPARAM_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>


EXTERNC_begin

extern bool	matparam(cshort *,int,int) noex ;

EXTERNC_end


#endif /* MATPARAM_INCLUDE */


