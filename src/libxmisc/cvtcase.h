/* cvtcase HEADER */
/* charset=ISO8859-1 */
/* lang=C20 */

/* convert a single character to a given case */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	CVTCASE_INCLUDE
#define	CVTCASE_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>

EXTERNC_begin

extern char	*cup(int,cchar *,char *) noex ;
extern char	*clow(int,cchar *,char *) noex ;

EXTERNC_end


#endif /* CVTCASE_INCLUDE */


