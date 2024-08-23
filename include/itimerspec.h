/* itimerspec HEADER */
/* lang=C99 */

/* interval-timer object methods */
/* version %I% last-modified %G% */


/* revision history:

	= 2014-04-04, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 2014 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Methods for the ITIMERSPEC object.

*******************************************************************************/

#ifndef	ITIMERSPEC_INCLUDE
#define	ITIMERSPEC_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<time.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<timespec.h>


EXTERNC_begin

extern int itimerspec_load(ITIMERSPEC *,CTIMESPEC *,CTIMESPEC *) noex ;

EXTERNC_end


#endif /* ITIMERSPEC_INCLUDE */


