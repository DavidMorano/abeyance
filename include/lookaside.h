/* lookaside HEADER */
/* lang=C++20 */

/* lookaside memory allocation manager */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	LOOKASIDE_INCLUDE
#define	LOOKASIDE_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<utypedefs.h>
#include	<clanguage.h>
#include	<pq.h>


#define	LOOKASIDE		struct lookaside_head
#define	LOOKASIDE_MINENTRIES	4


struct lookaside_head {
	caddr_t		eap ;		/* entry allocation pointer base */
	pq		*cqp ;		/* chunk list queue pointer */
	pq		*esp ;		/* empty-stack queue pointer */
	int		nchunks ;	/* number of chunks allocated */
	int		esize ;		/* entry size */
	int		eaoff ;		/* entry-array offset */
	int		n ;		/* entries per chunk */
	int		i ;		/* current chunk usage (index) */
	int		nfree ;		/* total free entries */
	int		nused ;		/* total entries used */
} ; /* end struct (lookaside_head) */

typedef LOOKASIDE	lookaside ;

EXTERNC_begin

extern int lookaside_start(lookaside *,int,int) noex ;
extern int lookaside_get(lookaside *,void *) noex ;
extern int lookaside_release(lookaside *,void *) noex ;
extern int lookaside_count(lookaside *) noex ;
extern int lookaside_finish(lookaside *) noex ;
extern int lookaside_audit(lookaside *) noex ;

EXTERNC_end


#endif /* LOOKASIDE_INCLUDE */


