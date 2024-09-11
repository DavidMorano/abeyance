/* bfliner HEADER */
/* lang=C20 */

/* BFILE-liner */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#ifndef	BFLINER_INCLUDE
#define	BFLINER_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>		/* |off_t| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<bfile.h>


#define	BFLINER		struct bfliner_head


struct bfliner_head {
	bfile		*ifp ;
	char		*lbuf ;
	off_t		poff ;		/* file-offset previous */
	off_t		foff ;		/* file-offset current */
	int		to ;		/* read time-out */
	int		llen ;
	int		ll ;
} ;

#ifdef	__cplusplus
enum bflinermems {
	bflinermem_readpending,
	bflinermem_readover,
	bflinermem_finish,
	bflinermem_overlast
} ;
struct bfliner ;
struct bfliner_co {
	bfliner		*op = nullptr ;
	int		w = -1 ;
	void operator () (bfliner *p,int m) noex {
	    op = p ;
	    w = m ;
	} ;
	operator int () noex ;
	int operator () () noex { 
	    return operator int () ;
	} ;
} ; /* end struct (bfliner_co) */
struct bfliner : bfliner_head {
	bfliner_co	readpending ;
	bfliner_co	readover ;
	bfliner_co	finish ;
	bfliner() noex {
	    readpending(this,bflinermem_readpending) ;
	    readover(this,bflinermem_readover) ;
	    finish(this,bflinermem_finish) ;
	} ;
	bfliner(const bfliner &) = delete ;
	bfliner &operator = (const bfliner &) = delete ;
	int start(bfile *,off_t = 0z,int = -1) noex ;
	int getln(cchar ** = nullptr) noex ;
	int getlns(cchar ** = nullptr) noex ;
	int getpoff(off_t *) noex ;
	void dtor() noex ;
	~bfliner() noex {
	    dtor() ;
	} ;
} ; /* end struct (bfliner) */
#else	/* __cplusplus */
typedef BFLINER		bfliner ;
#endif /* __cplusplus */

EXTERNC_begin

extern int bfliner_start(bfliner *,bfile *,off_t,int) noex ;
extern int bfliner_readpending(bfliner *) noex ;
extern int bfliner_getln(bfliner *,cchar **) noex ;
extern int bfliner_getlns(bfliner *,cchar **) noex ;
extern int bfliner_readover(bfliner *) noex ;
extern int bfliner_getpoff(bfliner *,off_t *) noex ;
extern int bfliner_finish(bfliner *) noex ;

EXTERNC_end


#endif /* BFLINER_INCLUDE */


