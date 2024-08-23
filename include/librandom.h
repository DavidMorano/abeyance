/* librandom HEADER */
/* lang=C20 */

/* LIBRANDOM object */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	LIBRANDOM_INCLUDE
#define	LIBRANDOM_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


#define	LIBRANDOM		struct librandom_head
#define	LIBRANDOM_NTYPES	5		/* number of types supported */


struct librandom_head {
	ulong		*fptr ;
	ulong		*rptr ;
	ulong		*end_ptr ;
	ulong		state[64] ;
	int		rand_type ;
	int		rand_deg ;
	int		rand_sep ;
} ;

typedef LIBRANDOM	librandom ;

EXTERNC_begin

extern int	librandom_start(librandom *,int,uint) noex ;
extern int	librandom_finish(librandom *) noex ;
extern int	librandom_getuint(librandom *,uint *) noex ;
extern int	librandom_getulong(librandom *,ulong *) noex ;

EXTERNC_end


#endif /* LIBRANDOM_INCLUDE */


