/* dayspec HEADER */
/* lang=C20 */

/* load a day-specification */
/* version %I% last-modified %G% */


/* revision history:

	= 2013-02-07, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2013 David A­D­ Morano.  All rights reserved. */

#ifndef	DAYSPEC_INCLUDE
#define	DAYSPEC_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<utypedefs.h>
#include	<clanguage.h>


#define	DAYSPEC		struct dayspec_head


struct dayspec_head {
	short		y ;
	schar		m, d ;
} ;

typedef DAYSPEC		dayspec ;

EXTERNC_begin

extern int dayspec_default(dayspec *) noex ;
extern int dayspec_load(dayspec *,cchar *,int) noex ;
extern int dayspec_yday(dayspec *) noex ;

EXTERNC_end


#endif /* DAYSPEC_INCLUDE */


