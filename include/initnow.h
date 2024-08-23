/* initnow HEADER */
/* lang=C20 */

/* initiali a NOW structure */
/* version %I% last-modified %G% */


/* revision history:

	= 1999-03-01, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1999 David A­D­ Morano.  All rights reserved. */

#ifndef	INITNOW_INCLUDE
#define	INITNOW_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/timeb.h>		/* |TIMEB| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


EXTERNC_begin

extern int initnow(TIMEB *,char *,int) noex ;

EXTERNC_end


#endif /* INITNOW_INCLUDE */


