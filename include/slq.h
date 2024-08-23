/* dpq HEADER */
/* lang=C20 */

/* Double-Pointer-Queue - regular (no-frills) double circular pointer queue */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-01, David A­D­ Morano
	This code was modeled after assembly.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	DPQ_INCLUDE
#define	DPQ_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


#define	DPQ		struct dpq_head
#define	DPQ_ENT		struct dpq_ent


struct dpq_ent {
	DPQ_ENT		*next ;
} ;

struct dpq_head {
	DPQ_ENT		*head ;
	DPQ_ENT		*tail ;
} ;

typedef DPQ		dpq ;
typedef DPQ_ENT		dpq_ent ;

EXTERNC_begin

extern int dpq_start(dpq *) noex ;
extern int dpq_ins(dpq *,dpq_ent *) noex ;
extern int dpq_insgroup(dpq *,void *,int,int) noex ;
extern int dpq_rem(dpq *,dpq_ent **) noex ;
extern int dpq_gettail(dpq *,dpq_ent **) noex ;
extern int dpq_audit(dpq *) noex ;
extern int dpq_finish(dpq *) noex ;

EXTERNC_end


#endif /* DPQ_INCLUDE */


