/* parts HEADER */
/* lang=C++20 */

/* AS-String (parts) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-01, David A­D­ Morano
	This object module was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This is an email address handling module object.  It can
	parse out and store hierarchically organized EMAs.

*******************************************************************************/

#ifndef	PARTS_INCLUDE
#define	PARTS_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/param.h>
#include	<unistd.h>
#include	<cstdlib>
#include	<cstring>		/* for |strlen(3c)| */
#include	<usystem.h>
#include	<mallocstuff.h>
#include	<strn.h>
#include	<char.h>
#include	<ascii.h>
#include	<localmisc.h>

#include	"asstr.hh"


namespace emaobj {
    extern int	partsbegin(asstr *) noex ;
    extern int	partslen(asstr *) noex ;
    extern int	partsend(asstr *) noex ;
}


#endif /* PARTS_INCLUDE */


