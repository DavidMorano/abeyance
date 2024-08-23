/* entry HEADER */
/* lang=C++20 */

/* AS-String (entry) */
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

#ifndef	ENTRY_INCLUDE
#define	ENTRY_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<cstring>		/* for |strlen(3c)| */
#include	<usystem.h>
#include	<localmisc.h>

#include	"ema.h"


namespace emaobj {
    extern int	entry_start(ema_ent *) noex ;
    extern int	entry_finish(ema_ent *) noex ;
    extern int	entry_startload(ema_ent *,ema_ent *) noex ;
}


#endif /* ENTRY_INCLUDE */


