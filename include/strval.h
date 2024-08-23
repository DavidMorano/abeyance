/* strval HEADER */
/* lang=C20 */

/* return (calculate) the numeric value of a given string */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	STRVAL_INCLUDE
#define	STRVAL_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern cchar	*strval(char *,int) noex ;

EXTERNC_end


#endif /* STRVAL_INCLUDE */


