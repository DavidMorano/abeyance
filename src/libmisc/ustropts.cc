/* ustropts SUPPORT */
/* lang=C++20 */

/* provide some UNIX® STREAMS subroutine stubs */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
        This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	ustropts

	Description:
	I provide some stubs for some UNIX® STREAMS subroutines.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>

#include	"ustropts.h"		/* <- the money shot */


/* local defines */


/* external subroutines */


/* external variables */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

#if	defined(SYSHAS_STREAMS) && (SYSHAS_STREAMS > 0)

/* we have it: do nothing for now */

#else /* defined(SYSHAS_STREAMS) && (SYSHAS_STREAMS > 0) */

int getmsg(int,STRBUF *,STRBUF *,int *) noex {
	return SR_NOSYS ;
}

int getpmsg(int,STRBUF *,STRBUF *,int *,int *) noex {
	return SR_NOSYS ;
}

int putmsg(int,STRBUF *,STRBUF *,int *) noex {
	return SR_NOSYS ;
}

int putpmsg(int,STRBUF *,STRBUF *,int *,int *) noex {
	return SR_NOSYS ;
}

#endif /* defined(SYSHAS_STREAMS) && (SYSHAS_STREAMS > 0) */


