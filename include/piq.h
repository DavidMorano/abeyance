/* piq HEADER */
/* lang=C20 */

/* pointer interlocked queue */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	PIQ_INCLUDE
#define	PIQ_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>
#include	<ptm.h>
#include	<pq.h>


#define	PIQ		struct piq_head
#define	PIQ_ENT		struct piq_ent
#define	PIQ_MAGIC	0x9635230


struct piq_ent {
	PIQ_ENT		*next ;
	PIQ_ENT		*prev ;
} ;

struct piq_head {
	ptm		*mxp ;
	pq		*freep ;
	uint		magic ;
} ;

typedef	PIQ		piq ;

EXTERNC_begin

extern int piq_start(piq *) noex ;
extern int piq_ins(piq *,void *) noex ;
extern int piq_rem(piq *,void *) noex ;
extern int piq_count(piq *) noex ;
extern int piq_audit(piq *) noex ;
extern int piq_finish(piq *) noex ;

EXTERNC_end


#endif /* PIQ_INCLUDE */


