/* plainq HEADER */
/* lang=C20 */

/* plain self-relative double-linked queue */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	PLAINQ_INCLUDE
#define	PLAINQ_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<stddef.h>		/* <- for |ptrdiff_t| */
#include	<usystem.h>


#define	PLAINQ		struct plainq_head
#define	PLAINQ_ENT	struct plainq_entry
#define	PLAINQ_MAGIC	0x76925634


struct plainq_entry {
	ptrdiff_t	next ;
	ptrdiff_t	prev ;
} ;

struct plainq_head {
	ptrdiff_t	head ;
	ptrdiff_t	tail ;
	uint		magic ;
	int		count ;
} ;

typedef PLAINQ		plainq ;
typedef PLAINQ_ENT	plainq_ent ;

EXTERNC_begin

extern int plainq_start(plainq *) noex ;
extern int plainq_finish(plainq *) noex ;
extern int plainq_ins(plainq *,plainq_ent *) noex ;
extern int plainq_insgroup(plainq *,plainq_ent *,int,int) noex ;
extern int plainq_inshead(plainq *,plainq_ent *) noex ;
extern int plainq_unlink(plainq *,plainq_ent *) noex ;
extern int plainq_rem(plainq *,plainq_ent **) noex ;
extern int plainq_gethead(plainq *,plainq_ent **) noex ;
extern int plainq_remtail(plainq *,plainq_ent **) noex ;
extern int plainq_gettail(plainq *,plainq_ent **) noex ;
extern int plainq_count(plainq *) noex ;
extern int plainq_audit(plainq *) noex ;

EXTERNC_end


#endif /* PLAINQ_INCLUDE */


