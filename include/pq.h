/* pq HEADER */
/* lang=C20 */

/* regular (no-frills) pointer queue */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-03, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	PQ_INCLUDE
#define	PQ_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<usystem.h>


#define	PQ		struct pq_head
#define	PQ_ENT		struct pq_entry
#define	PQ_CUR		struct pq_cursor


struct pq_cursor {
	PQ_ENT		*entp ;
} ;

struct pq_entry {
	PQ_ENT		*next ;
	PQ_ENT		*prev ;
} ;

struct pq_head {
	PQ_ENT		*head ;
	PQ_ENT		*tail ;
	int		count ;
} ;

typedef PQ		pq ;
typedef PQ_ENT		pq_ent ;
typedef PQ_CUR		pq_cur ;

EXTERNC_begin

extern int pq_start(pq *) noex ;
extern int pq_ins(pq *,pq_ent *) noex ;
extern int pq_insgroup(pq *,pq_ent *,int,int) noex ;
extern int pq_gettail(pq *,pq_ent **) noex ;
extern int pq_rem(pq *,pq_ent **) noex ;
extern int pq_remtail(pq *,pq_ent **) noex ;
extern int pq_unlink(pq *,pq_ent *) noex ;
extern int pq_curbegin(pq *,pq_cur *) noex ;
extern int pq_curend(pq *,pq_cur *) noex ;
extern int pq_enum(pq *,pq_cur *,pq_ent **) noex ;
extern int pq_count(pq *) noex ;
extern int pq_audit(pq *) noex ;
extern int pq_finish(pq *) noex ;

EXTERNC_end


#endif /* PQ_INCLUDE */


