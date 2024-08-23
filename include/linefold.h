/* linefold HEADER */
/* lang=C20 */

/* manage folding of a line */
/* version %I% last-modified %G% */


/* revision history:

	= 2009-04-10, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2009 David A­D­ Morano.  All rights reserved. */

#ifndef	LINEFOLD_INCLUDE
#define	LINEFOLD_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>
#include	<vecobj.h>


#define	LINEFOLD_MAGIC		0x88431773
#define	LINEFOLD		struct linefold_head
#define	LINEFOLD_FL		struct linefold_flags
#define	LINEFOLD_MCARRIAGE	0x0001


struct linefold_flags {
	uint		dummy:1 ;
} ;

struct linefold_head {
	vecobj		*llp ;
	LINEFOLD_FL	f ;
	uint		magic ;
} ;

#ifdef	__cplusplus
enum linefoldmems {
	linefoldmem_count,
	linefoldmem_finish,
	linefoldmem_overlast
} ;
struct linefold ;
struct linefold_iter {
	linefold	*op = nullptr ;
	int		i = -1 ;
	linefold_iter() = default ;
	linefold_iter(linefold *p,int ai) noex : op(p), i(ai) { } ;
	linefold_iter(const linefold_iter &oit) noex {
	    if (this != &oit) {
		op = oit.op ;
		i = oit.i ;
	    }
	} ;
	linefold_iter &operator = (const linefold_iter &oit) noex {
	    if (this != &oit) {
		op = oit.op ;
		i = oit.i ;
	    }
	    return *this ;
	} ;
	bool operator != (const linefold_iter &) noex ;
	bool operator == (const linefold_iter &) noex ;
	cchar *operator * () noex ;
	linefold_iter operator + (int) const noex ;
	linefold_iter operator += (int) noex ;
	linefold_iter operator ++ () noex ; /* pre */
	linefold_iter operator ++ (int) noex ; /* post */
	void idx(int ai) noex {
	    i = ai ;
	} ;
	void increment(int = 1) noex ;
} ; /* end struct linefold_iter) */
struct linefold_co {
	linefold	*op = nullptr ;
	int		w = -1 ;
	void operator () (linefold *p,int m) noex {
	    op = p ;
	    w = m ;
	} ;
	operator int () noex ;
	int operator () () noex { 
	    return operator int () ;
	} ;
} ; /* end struct (linefold_co) */
struct linefold : linefold_head {
	linefold_co	count ;
	linefold_co	finish ;
	linefold() noex {
	    count(this,linefoldmem_count) ;
	    finish(this,linefoldmem_finish) ;
	} ;
	linefold(const linefold &) = delete ;
	linefold &operator = (const linefold &) = delete ;
	int start(int,int,cchar *,int = -1) noex ;
	int get(int,cchar **) noex ;
	int getln(int,cchar **) noex ;
	linefold_iter begin() noex {
	    linefold_iter	it(this,0) ;
	    return it ;
	} ;
	linefold_iter end() noex {
	    linefold_iter	it(this,0) ;
	    if (int rs ; (rs = count) >= 0) {
		it.idx(rs) ;
	    }
	    return it ;
	} ;
	void dtor() noex ;
	~linefold() noex {
	    dtor() ;
	} ;
} ; /* end struct (linefold) */
#else	/* __cplusplus */
typedef LINEFOLD	linefold ;
#endif /* __cplusplus */

typedef	LINEFOLD_FL	linefold_fl ;

EXTERNC_begin

extern int linefold_start(linefold *,int,int,cchar *,int) noex ;
extern int linefold_get(linefold *,int,cchar **) noex ;
extern int linefold_getln(linefold *,int,cchar **) noex ;
extern int linefold_count(linefold *) noex ;
extern int linefold_finish(linefold *) noex ;

EXTERNC_end


#endif /* LINEFOLD_INCLUDE */


