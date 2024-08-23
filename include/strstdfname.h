/* strstdfname HEADER */
/* lang=C20 */

/* return a c-string for a standard filename */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	STRSTDFNAME_INCLUDE
#define	STRSTDFNAME_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<stdfnames.h>


EXTERNC_begin

extern cchar	*strstdfname(int,cchar *) noex ;

EXTERNC_end


#endif /* STRSTDFNAME_INCLUDE */


