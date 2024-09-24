/* mkcexsync HEADER */
/* lang=C20 */

/* make the synchronization string used for CEX */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MKCEXSYNC_INCLUDE
#define	MKCEXSYNC_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


#define	MKCEXSYNC_MKLEN		10	/* length to create (in bytes) */
#define	MKCEXSYNC_REQLEN	6	/* required length */
#define	MKCEXSYNC_FINLEN	2	/* number of finishing bytes */


EXTERNC_begin

extern int	mkcexsync(char *,int) noex ;

EXTERNC_end


#endif /* MKCEXSYNC_INCLUDE */


