/* ciq HEADER */
/* lang=C++20 */

/* circular (really doubly linked) interlocked queue */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-27, David A­D­ Morano
	This module was adapted from the PPI/LPPI OS code.

*/

/* Copyright © 1999 David A­D­ Morano.  All rights reserved. */

#ifndef	CIQ_INCLUDE
#define	CIQ_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>
#include	<ptm.h>
#include	<pq.h>


#define	CIQ_MAGIC	0x9635230
#define	CIQ		struct ciq_head


struct ciq_head {
	ptm		*mxp ;
	pq		*fifop ;
	pq		*freep ;
	uint		magic ;
} ;

typedef CIQ		ciq ;

EXTERNC_begin

extern int ciq_start(ciq *) noex ;
extern int ciq_ins(ciq *,void *) noex ;
extern int ciq_rem(ciq *,void *) noex ;
extern int ciq_gettail(ciq *,void *) noex ;
extern int ciq_remtail(ciq *,void *) noex ;
extern int ciq_rement(ciq *,void *) noex ;
extern int ciq_count(ciq *) noex ;
extern int ciq_audit(ciq *) noex ;
extern int ciq_finish(ciq *) noex ;

EXTERNC_end


#endif /* CIQ_INCLUDE */


