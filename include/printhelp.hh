/* printhelp HEADER */
/* lang=C++20 */

/* print out a help file if we have one */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	PRINTHELP_INCLUDE
#define	PRINTHELP_INCLUDE
#ifdef	__cplusplus /* C++ only */


#include	<envstandards.h>	/* MUST be first to configure */
#include	<ostream>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


EXTERNC_begin

extern int printhelp(std::ostream *,cchar *,cchar *,cchar *) noex ;

EXTERNC_end


#endif /* __cplusplus */
#endif /* PRINTHELP_INCLUDE */


