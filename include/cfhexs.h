/* cfhexs HEADER */
/* lang=C20 */

/* convert from a HEX string to the value (string) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-07-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	CFHEXS_INCLUDE
#define	CFHEXS_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


EXTERNC_begin

extern int cfhexs(cchar *,int,uchar *) noex ;

EXTERNC_end


#endif /* CFHEXS_INCLUDE */


