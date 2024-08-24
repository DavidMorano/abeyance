/* sigevent HEADER */
/* lang=C99 */

/* signal event object methods */
/* version %I% last-modified %G% */


/* revision history:

	= 2014-04-04, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 2014 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Methods for the signal-event object.

*******************************************************************************/

#ifndef	SIGEVENT_INCLUDE
#define	SIGEVENT_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>


EXTERNC_begin

extern int sigevent_load(SIGEVENT *,int,int,int) noex ;

EXTERNC_end


#endif /* SIGEVENT_INCLUDE */


