/* ucsys HEADER */
/* lang=C20 */

/* UCSYS object management */
/* version %I% last-modified %G% */


/* revision history:

	= 2001-04-11, David D-A- Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 2001 David A­D­ Morano.  All rights reserved. */

#ifndef	UCSYS_INCLUDE
#define	UCSYS_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>

#include	<spwd.h>		/* <- special */
#include	<userattr.h>		/* <- special */

#include	<ucsyspw.h>
#include	<ucsysgr.h>
#include	<ucsyspj.h>

#include	<ucsyspr.h>
#include	<ucsysnw.h>
#include	<ucsysho.h>
#include	<ucsyssv.h>


EXTERNC_begin

extern int ucsys_getec(int) noex ;

EXTERNC_end


#endif /* UCSYS_INCLUDE */


