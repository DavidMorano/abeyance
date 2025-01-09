/* makedirs HEADER */
/* encoding=ISO8859-1 */
/* lang=C20 (conformance reviewed) */

/* object to handle parameter files */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-15, David A­D­ Morano
	This code was started for Levo related work.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MAKEDIRS_INCLUDE
#define	MAKEDIRS_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


EXTERNC_begin

extern int	makedirs(cchar *,int,mode_t) noex ;

EXTERNC_end


#endif /* MAKEDIRS_INCLUDE */


