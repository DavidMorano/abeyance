/* sfill HEADER */
/* lang=C20 */

/* text fill */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-01, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	SFILL_INCLUDE
#define	SFILL_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>
#include	<bfile.h>
#include	<fifostr.h>


#define	SFILL		struct sfill_head


struct sfill_head {
	bfile		*ofp ;
	fifostr		*fsp ;
	int		clen ;
	int		indent ;
} ;

typedef SFILL		sfill ;

EXTERNC_begin

extern int	sfill_start(sfill *,int,bfile *) noex ;
extern int	sfill_remaining(sfill *) noex ;
extern int	sfill_proc(sfill *,int,cchar *,int) noex ;
extern int	sfill_wline(sfill *,int) noex ;
extern int	sfill_finish(sfill *) noex ;

EXTERNC_end


#endif /* SFILL_INCLUDE */


