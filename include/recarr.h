/* recarr HEADER */
/* lang=C20 */

/* record-array management */
/* version %I% last-modified %G% */


/* revision history:

	= 1999-02-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1999 David A­D­ Morano.  All rights reserved. */

#ifndef	RECARR_INCLUDE
#define	RECARR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<stdint.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>


#define	RECARR		struct recarr_head
#define	RECARR_FL	struct recarr_flags

/* options */
#define	RECARR_ODEFAULT		0
#define	RECARR_OREUSE		(1 << 0)	/* reuse empty slots */
#define	RECARR_OCOMPACT		(1 << 1)	/* means NOHOLES */
#define	RECARR_OSWAP		(1 << 2)	/* use swapping */
#define	RECARR_OSTATIONARY	(1 << 3)	/* entries should not move */
#define	RECARR_OCONSERVE	(1 << 4)	/* conserve space */
#define	RECARR_OSORTED		(1 << 5)	/* keep sorted */
#define	RECARR_OORDERED		(1 << 6)	/* keep ordered */

enum recarr_os : uint16_t {
    recarr_odefault 	= RECARR_ODEFAULT,
    recarr_oreuse 	= RECARR_ODEFAULT,
    recarr_ocompact	= RECARR_OCOMPACT,
    recarr_oswap	= RECARR_OSWAP,
    recarr_ostationary	= RECARR_OSTATIONARY,
    recarr_oconserve	= RECARR_OCONSERVE,
    recarr_osorted	= RECARR_OSORTED,
    recarr_oordered	= RECARR_OORDERED
} ;

struct recarr_flags {
	uint		issorted:1 ;
	uint		oreuse:1 ;
	uint		oswap:1 ;
	uint		ostationary:1 ;
	uint		ocompact:1 ;
	uint		osorted:1 ;
	uint		oordered:1 ;
	uint		oconserve:1 ;
} ;

struct recarr_head {
	void		**va ;
	int		c ;		/* count of items in list */
	int		i ;		/* highest index */
	int		n ;		/* extent of array */
	int		fi ;		/* free entry index */
	RECARR_FL	f ;
} ;

typedef	RECARR		recarr ;
typedef	RECARR_FL	recarr_fl ;

EXTERNC_begin

typedef int (*recarr_cf)(cvoid **,cvoid **) noex ;

extern int recarr_start(recarr *,int,int) noex ;
extern int recarr_add(recarr *,cvoid *) noex ;
extern int recarr_count(recarr *) noex ;
extern int recarr_sort(recarr *,recarr_cf) noex ;
extern int recarr_setsorted(recarr *) noex ;
extern int recarr_get(recarr *,int,cvoid *) noex ; 
extern int recarr_getlast(recarr *,cvoid *) noex ; 
extern int recarr_ent(recarr *,cvoid *) noex ;
extern int recarr_search(recarr *,cvoid *,recarr_cf,void *) noex ;
extern int recarr_del(recarr *,int) noex ;
extern int recarr_delhand(recarr *,cvoid *) noex ;
extern int recarr_delall(recarr *) noex ;
extern int recarr_getvec(recarr *,void *) noex ;
extern int recarr_extent(recarr *) noex ;
extern int recarr_audit(recarr *) noex ;
extern int recarr_finish(recarr *) noex ;

EXTERNC_end


#endif /* RECARR_INCLUDE */


