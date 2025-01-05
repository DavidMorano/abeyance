/* cfdouble HEADER */
/* encoding=ISO8859-1 */
/* lang=C20 */

/* convert a floating point digit string to its double value */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	CFDOUNLE_INCLUDE
#define	CFDOUNLE_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<stdintx.h>


EXTERNC_begin

extern int cfdouble(cchar *,int,double *) noex ;

EXTERNC_end


#endif /* CFDOUNLE_INCLUDE */


