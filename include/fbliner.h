/* fbliner HEADER */
/* lang=C20 */

/* file-buf (now FILER) file-read line handling */
/* version %I% last-modified %G% */


/* revision history:

	= 2009-01-10, David A­D­ Morano
        This is being written from scratch to finally get an abstracted
        "mailbox" that is fast enough for interactive use.

*/

/* Copyright © 2009 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	fbliner

*******************************************************************************/

#ifndef	FBLINER_INCLUDE
#define	FBLINER_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>		/* |off_t| */
#include	<unistd.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<filer.h>


#define	FBLINER		struct fbliner_head


struct fbliner_head {
	filer		*fbp ;		/* externally-owned */
	char		*lbuf ;		/* allocated */
	off_t		poff ;		/* file-offset previous */
	off_t		foff ;		/* file-offset current */
	int		to ;		/* read time-out */
	int		llen ;
} ;

typedef	FBLINER		fbliner ;

EXTERNC_begin

extern int fbliner_start(fbliner *,filer *,off_t,int) noex ;
extern int fbliner_getln(fbliner *,cchar **) noex ;
extern int fbliner_done(fbliner *) noex ;
extern int fbliner_seek(fbliner *,int) noex ;
extern int fbliner_finish(fbliner *) noex ;

EXTERNC_end


#endif /* FBLINER_INCLUDE */


