/* getmjd HEADER */
/* lang=C20 */

/* get (calculate) a Modified-Julian-Day (MJD) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETMJD_INCLUDE
#define	GETMJD_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


EXTERNC_begin

extern int	getmjd(int,int,int) noex ;
extern int	getyrd(int,int,int) noex ;

EXTERNC_end


#endif /* GETMJD_INCLUDE */


