/* ucsysauxinfo HEADER */
/* lang=C20 */

/* UNIX® system-auxillary-information */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-02-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#ifndef	UCSYSAUXINFO_INCLUDE
#define	UCSYSAUXINFO_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysauxinfo.h>		/* <- from |libu| */


EXTERNC_begin

extern int uc_sysauxinfo(char *,int,int) noex ;

EXTERNC_end


#endif /* UCSYSUAUXINFO_INCLUDE */


