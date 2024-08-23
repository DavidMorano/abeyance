/* termios_cf HEADER */
/* lang=C20 */

/* convert a single character to a given case */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	TERMIOS_INCLUDE
#define	TERMIOS_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<termios.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern int termios_cfsetispeed(TERMIOS *,speed_t) noex ;
extern int termios_cfsetospeed(TERMIOS *,speed_t) noex ;

EXTERNC_end


#endif /* TERMIOS_INCLUDE */


