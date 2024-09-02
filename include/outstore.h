/* outstore HEADER */
/* lang=C20 */

/* manage some dynamic output storage (mostly for SHIO use) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	OUTSTORE_INCLUDE
#define	OUTSTORE_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>


#define	OUTSTORE	struct outstore_head
#define	OUTSTORE_SLEN	128


struct outstore_head {
	char		*dbuf ;	/* dynamically sized (allocated) */
	int		dlen ;
	int		len ;
	char		sbuf[OUTSTORE_SLEN+1] ; /* "static" or "stack" */
} ;

typedef OUTSTORE	outstore ;

EXTERNC_begin

extern int	outstore_start(outstore *) noex ;
extern int	outstore_strw(outstore *,cchar *,int) noex ;
extern int	outstore_get(outstore *,cchar **) noex ;
extern int	outstore_clear(outstore *) noex ;
extern int	outstore_finish(outstore *) noex ;

EXTERNC_end


#endif /* OUTSTORE_INCLUDE */


