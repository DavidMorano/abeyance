/* vechand HEADER */
/* lang=C20 */

/* vector list structure (Vector Handle) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	VECHAND_INCLUDE
#define	VECHAND_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


/* object defines */
#define	VECHAND		struct vechand_head
#define	VECHAND_FL	struct vechand_flags
#define	VECHAND_DEFENTS	10

/* options */
#define	VECHAND_ODEFAULT	0
#define	VECHAND_OREUSE		(1 << 0)	/* reuse empty slots */
#define	VECHAND_OCOMPACT	(1 << 1)	/* means NOHOLES */
#define	VECHAND_OSWAP		(1 << 2)	/* use swapping */
#define	VECHAND_OSTATIONARY	(1 << 3)	/* entries should not move */
#define	VECHAND_OCONSERVE	(1 << 4)	/* conserve space */
#define	VECHAND_OSORTED		(1 << 5)	/* keep sorted */
#define	VECHAND_OORDERED	(1 << 6)	/* keep ordered */


struct vechand_flags {
	uint		issorted:1 ;
	uint		oreuse:1 ;
	uint		onoholes:1 ;
	uint		oswap:1 ;
	uint		ostationary:1 ;
	uint		ocompact:1 ;
	uint		osorted:1 ;
	uint		oordered:1 ;
	uint		oconserve:1 ;
} ;

struct vechand_head {
	void		**va ;
	int		c ;		/* count of items in list */
	int		i ;		/* highest index */
	int		n ;		/* extent of array */
	int		fi ;		/* free entry index */
	VECHAND_FL	f ;
} ; /* end struct (vechand_head) */

typedef VECHAND		vechand ;

EXTERNC_begin

typedef int (*vechand_vcmp)(cvoid **,cvoid **) noex ;

extern int vechand_start(vechand *,int,int) noex ;
extern int vechand_add(vechand *,cvoid *) noex ;
extern int vechand_count(vechand *) noex ;
extern int vechand_sort(vechand *,vechand_vcmp) noex ;
extern int vechand_setsorted(vechand *) noex ;
extern int vechand_get(vechand *,int,void **) noex ; 
extern int vechand_getlast(vechand *,void **) noex ; 
extern int vechand_search(vechand *,cvoid *,vechand_vcmp,void **) noex ;
extern int vechand_ent(vechand *,cvoid *) noex ;
extern int vechand_issorted(vechand *) noex ;
extern int vechand_del(vechand *,int) noex ;
extern int vechand_delhand(vechand *,cvoid *) noex ;
extern int vechand_delall(vechand *) noex ;
extern int vechand_getvec(vechand *,void *) noex ;
extern int vechand_extent(vechand *) noex ;
extern int vechand_audit(vechand *) noex ;
extern int vechand_finish(vechand *) noex ;

EXTERNC_end


#endif /* VECHAND_INCLUDE */


