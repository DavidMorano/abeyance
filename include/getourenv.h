/* getourenv HEADER */
/* lang=C20 */

/* get an environment variable from our local (passed) environment */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETOURENV_INCLUDE
#define	GETOURENV_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>


EXTERNC_begin

extern cchar	*getourenv(mainv,cchar *) noex ;

EXTERNC_end


#endif /* GETOURENV_INCLUDE */


