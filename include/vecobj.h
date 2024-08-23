/* vecobj HEADER */
/* lang=C20 */

/* vector-object */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	VECOBJ_INCLUDE
#define	VECOBJ_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<lookaside.h>


/* object defines */
#define	VECOBJ			struct vecobj_head
#define	VECOBJ_CUR		struct vecobj_cursor
#define	VECOBJ_FL		struct vecobj_flags
#define	VECOBJ_DEFENTS		10

/* options */
#define	VECOBJ_ODEFAULT		0
#define	VECOBJ_OREUSE		(1 << 0)	/* reuse empty slots */
#define	VECOBJ_OCOMPACT		(1 << 1)	/* means NOHOLES */
#define	VECOBJ_OSWAP		(1 << 2)	/* use swapping */
#define	VECOBJ_OSTATIONARY	(1 << 3)	/* entries should not move */
#define	VECOBJ_OCONSERVE	(1 << 4)	/* conserve space */
#define	VECOBJ_OSORTED		(1 << 5)	/* keep sorted */
#define	VECOBJ_OORDERED		(1 << 6)	/* keep ordered */


struct vecobj_flags {
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

struct vecobj_head {
	void		**va ;
	lookaside	*lap ;
	VECOBJ_FL	f ;
	int		c ;		/* count of items in list */
	int		i ;		/* highest index */
	int		n ;		/* extent of array */
	int		fi ;		/* free index */
	int		esize ;		/* object size */
} ;

struct vecobj_cursor {
	int		i, c ;
} ;

typedef struct vecobj_head	vecobj ;
typedef struct vecobj_cursor	vecobj_cur ;

EXTERNC_begin

typedef int (*vecobj_vcf)(cvoid **,cvoid **) noex ;

extern int vecobj_start(vecobj *,int,int,int) noex ;
extern int vecobj_add(vecobj *,cvoid *) noex ;
extern int vecobj_adduniq(vecobj *,cvoid *) noex ;
extern int vecobj_inorder(vecobj *,cvoid *,vecobj_vcf,int) noex ;
extern int vecobj_del(vecobj *,int) noex ;
extern int vecobj_delall(vecobj *) noex ;
extern int vecobj_count(vecobj *) noex ;
extern int vecobj_sort(vecobj *,vecobj_vcf) noex ;
extern int vecobj_setsorted(vecobj *) noex ;
extern int vecobj_find(vecobj *,cvoid *) noex ;
extern int vecobj_curbegin(vecobj *,vecobj_cur *) noex ;
extern int vecobj_fetch(vecobj *,cvoid *,vecobj_cur *,vecobj_vcf,void **) noex ;
extern int vecobj_curend(vecobj *,vecobj_cur *) noex ;
extern int vecobj_search(vecobj *,cvoid *,vecobj_vcf,void **) noex ;
extern int vecobj_get(vecobj *,int,void **) noex ;
extern int vecobj_store(vecobj *,cvoid *,void **) noex ;
extern int vecobj_getvec(vecobj *,void ***) noex ;
extern int vecobj_audit(vecobj *) noex ;
extern int vecobj_finish(vecobj *) noex ;
extern int vecobj_addnew(vecobj *,void **) noex ;

EXTERNC_end


#endif /* VECOBJ_INCLUDE */


