/* acceptpass HEADER */
/* lang=C20 */

/* accept a passed file-descriptor (FD) from a UNIX® pipe */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

	= 2017-08-01, David A­D­ Morano
	Updated for lack of interfaces in Apple-Darwin

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This file contains some support for the UNIX® Address-Familt
	(AF) related operations.

*******************************************************************************/

#ifndef	ACCEPTPASS_INCLUDE
#define	ACCEPTPASS_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<usystem.h>


EXTERNC_begin

extern int	acceptpass(int,STRRECVFD *,int) noex ;

EXTERNC_end


#endif /* ACCEPTPASS_INCLUDE */


