/* strlocktype HEADER */
/* lang=C20 */

/* provide c-string for a given UNIX® file-lock type */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	STRLOCKTYPE_INCLUDE
#define	STRLOCKTYPE_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern cchar *strlocktype(int) noex ;

EXTERNC_end


#endif /* STRLOCKTYPE_INCLUDE */


