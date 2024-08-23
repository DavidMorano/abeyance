/* bfliner HEADER */
/* lang=C20 */

/* BFILE-liner */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#ifndef	BFLINER_INCLUDE
#define	BFLINER_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>		/* |off_t| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<bfile.h>


#define	BFLINER		struct bfliner_head


struct bfliner_head {
	bfile		*ifp ;
	char		*lbuf ;
	off_t		poff ;		/* file-offset previous */
	off_t		foff ;		/* file-offset current */
	int		to ;		/* read time-out */
	int		llen ;
	int		ll ;
} ;

typedef	BFLINER		bfliner ;

EXTERNC_begin

extern int bfliner_start(bfliner *,bfile *,off_t,int) noex ;
extern int bfliner_readpending(bfliner *) noex ;
extern int bfliner_readln(bfliner *,int,cchar **) noex ;
extern int bfliner_readover(bfliner *) noex ;
extern int bfliner_getpoff(bfliner *,off_t *) noex ;
extern int bfliner_finish(bfliner *) noex ;

EXTERNC_end


#endif /* BFLINER_INCLUDE */


