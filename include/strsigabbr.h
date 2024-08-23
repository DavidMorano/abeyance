/* strsigabbr HEADER */
/* lang=C20 */

/* provide c-string abbreviations for UNIX® signals */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	STRSIGABBR_INCLUDE
#define	STRSIGABBR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern cchar *strsigabbr(uint) noex ;

EXTERNC_end


#endif /* STRSIGABBR_INCLUDE */


