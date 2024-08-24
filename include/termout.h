/* termout HEADER */
/* lang=C20 */

/* terminal-output management */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	TERMOUT_INCLUDE
#define	TERMOUT_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>


#define	TERMOUT_MAGIC	0x13f3c201
#define	TERMOUT		struct termout_head
#define	TERMOUT_FL	struct termout_flags


struct termout_flags {
	uint		isterm:1 ;
} ;

struct termout_head {
	void		*cvp ;		/* character-vector-pointer */
	void		*lvp ;		/* line-vector-pointer */
	TERMOUT_FL	f ;
	uint		magic ;
	uint		termattr ;	/* mask of terminal attributes */
	int		ncols ;		/* terminal columns */
	int		ncol ;
} ;

typedef TERMOUT		termout ;
typedef TERMOUT_FL	termout_fl ;

EXTERNC_begin

extern int termout_start(termout *,cchar *,int,int) noex ;
extern int termout_load(termout *,cchar *,int) noex ;
extern int termout_getline(termout *,int,cchar **) noex ;
extern int termout_finish(termout *) noex ;

EXTERNC_end


#endif /* TERMOUT_INCLUDE */


