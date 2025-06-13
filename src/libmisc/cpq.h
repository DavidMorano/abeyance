/* cpq HEADER */
/* charset=ISO8859-1 */
/* Circular-Pointer-Queue */

/* regular (no-frills) pointer queue */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-01, David A­D­ Morano
	This code was modeled after assembly.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	CPQ_INCLUDE
#define	CPQ_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


#define	CPQ		struct cpq_head
#define	CPQ_ENT		struct cpq_entry


struct cpq_entry {
	CPQ_ENT		*next ;
	CPQ_ENT		*prev ;
} ;

struct cpq_head {
	CPQ_ENT		*next ;
	CPQ_ENT		*prev ;
} ;

typedef	CPQ		cpq ;
typedef	CPQ_ENT		cpq_ent ;

EXTERNC_begin

extern int cpq_start(cpq *) noex ;
extern int cpq_ins(cpq *,cpq_ent *) noex ;
extern int cpq_insgroup(cpq *,cpq_ent *,int,int) noex ;
extern int cpq_rem(cpq *,cpq_ent **) noex ;
extern int cpq_remtail(cpq *,cpq_ent **) noex ;
extern int cpq_gettail(cpq *,cpq_ent **) noex ;
extern int cpq_audit(cpq *) noex ;
extern int cpq_finish(cpq *) noex ;

EXTERNC_end


#endif /* CPQ_INCLUDE */


