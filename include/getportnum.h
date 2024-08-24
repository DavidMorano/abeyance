/* getportnum HEADER */
/* lang=C20 */

/* retrieve an Internet port number */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This file contains some support for the UNIX® Internet-Address
	 related operations.

*******************************************************************************/

#ifndef	GETPORTNUM_INCLUDE
#define	GETPORTNUM_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


EXTERNC_begin

extern int	getportnum(cchar *,cchar *) noex ;

EXTERNC_end


#endif /* GETPORTNUM_INCLUDE */


