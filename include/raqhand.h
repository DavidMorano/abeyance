/* raqhand HEADER */
/* lang=C20 */

/* Random-Access Queue Handler */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-12-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	RAQHAND_INCLUDE
#define	RAQHAND_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


#define	RAQHAND_DEFENTS	10
#define	RAQHAND		struct raqhand_head
#define	RAQHAND_FL	struct raqhand_flags

/* options */
#define	RAQHAND_ODEFAULT	0
#define	RAQHAND_OREUSE		(1 << 0)	/* reuse empty slots */
#define	RAQHAND_OCOMPACT	(1 << 1)	/* means NOHOLES */
#define	RAQHAND_OSWAP		(1 << 2)	/* use swapping */
#define	RAQHAND_OSTATIONARY	(1 << 3)	/* entries should not move */
#define	RAQHAND_OCONSERVE	(1 << 4)	/* conserve space */
#define	RAQHAND_OSORTED		(1 << 5)	/* keep sorted */
#define	RAQHAND_OORDERED	(1 << 6)	/* keep ordered */


struct raqhand_flags {
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

struct raqhand_head {
	cvoid		**va ;
	RAQHAND_FL	f ;
	int		c ;		/* count of items in list */
	int		n ;		/* extent of array */
	int		hi ;		/* head */
	int		ti ;		/* tail */
} ;

typedef RAQHAND		raqhand ;
typedef RAQHAND_FL	raqhand_fl ;

EXTERNC_begin

extern int raqhand_start(raqhand *,int,int) noex ;
extern int raqhand_ins(raqhand *,cvoid *) noex ;
extern int raqhand_rem(raqhand *,void **) noex ;
extern int raqhand_del(raqhand *,int) noex ;
extern int raqhand_delall(raqhand *) noex ;
extern int raqhand_count(raqhand *) noex ;
extern int raqhand_acc(raqhand *,int,void **) noex ; 
extern int raqhand_acclast(raqhand *,void **) noex ; 
extern int raqhand_get(raqhand *,int,void **) noex ; 
extern int raqhand_ent(raqhand *,cvoid *) noex ;
extern int raqhand_finish(raqhand *) noex ;

EXTERNC_end


#endif /* RAQHAND_INCLUDE */


