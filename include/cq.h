/* cq HEADER */
/* lang=C20 */

/* Container-Queue */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-07-17, David A­D­ Morano
	Oh what a cheap Q!  I do not know why I am doing this!

	= 2017-11-21, David A­D­ Morano
	Added new method |cq_unlink()|.

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

#ifndef	CQ_INCLUDE
#define	CQ_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>
#include	<vechand.h>


#define	CQ_MAGIC	0x65748392
#define	CQ_DEFENTS	10
#define	CQ		struct cq_head
#define	CQ_CUR		struct cq_cursor


struct cq_head {
	vechand		*qp ;
	uint		magic ;
} ;

struct cq_cursor {
	int		i ;
} ;

typedef CQ		cq ;
typedef CQ_CUR		cq_cur ;

EXTERNC_begin

extern int cq_start(cq *) noex ;
extern int cq_finish(cq *) noex ;
extern int cq_ins(cq *,void *) noex ;
extern int cq_rem(cq *,void *) noex ;
extern int cq_unlink(cq *,void *) noex ;
extern int cq_count(cq *) noex ;
extern int cq_curbegin(cq *,cq_cur *) noex ;
extern int cq_curend(cq *,cq_cur *) noex ;
extern int cq_enum(cq *,cq_cur *,void *) noex ;

EXTERNC_end


#endif /* CQ_INCLUDE */


