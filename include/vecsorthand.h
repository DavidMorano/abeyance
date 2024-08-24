/* vecsorthand HEADER */
/* lang=C20 */

/* vector of sorted handles */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-28,  David A-D- Morano
	Module was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	VECSORTHAND_INCLUDE
#define	VECSORTHAND_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>


#define	VECSORTHAND		struct vecsorthand_head


#ifndef	TYPEDEF_VECENTCMP
#define	TYPEDEF_VECENTCMP
EXTERNC_begin

typedef int (*vecsorthand_vcf)(cvoid *,cvoid *) noex ;

EXTERNC_end
#endif /* TYPEDEF_VECENTCMP */

struct vecsorthand_head {
	vecsorthand_vcf	vcf ;
	void		**va ;
	int		c ;		/* count of items in list */
	int		i ;		/* highest index */
	int		e ;		/* extent of array */
} ;

#ifdef	__cplusplus
enum vecsorthandmems {
	vecsorthandmem_count,
	vecsorthandmem_del,
	vecsorthandmem_finish,
	vecsorthandmem_overlast
} ;
struct vecsorthand_iter {
	void		**va = nullptr ;
	int		i = -1 ;
	int		ii = -1 ;
	vecsorthand_iter() = default ;
	vecsorthand_iter(void **ov,int oi,int oii) noex : va(ov), i(oi) {
	    ii = oii ;
	} ;
	vecsorthand_iter(const vecsorthand_iter &oit) noex {
	    if (this != &oit) {
		va = oit.va ;
		i = oit.i ;
		ii = oit.ii ;
	    }
	} ;
	vecsorthand_iter &operator = (const vecsorthand_iter &oit) noex {
	    if (this != &oit) {
		va = oit.va ;
		i = oit.i ;
		ii = oit.ii ;
	    }
	    return *this ;
	} ;
	bool operator != (const vecsorthand_iter &) noex ;
	bool operator == (const vecsorthand_iter &) noex ;
	void *operator * () noex {
	    void	*rp = nullptr ;
	    if (i < ii) rp = va[i] ;
	    return rp ;
	} ;
	vecsorthand_iter operator + (int) const noex ;
	vecsorthand_iter operator += (int) noex ;
	vecsorthand_iter operator ++ () noex ; /* pre */
	vecsorthand_iter operator ++ (int) noex ; /* post */
	void increment(int = 1) noex ;
} ; /* end struct vecsorthand_iter) */
struct vecsorthand ;
struct vecsorthand_co {
	vecsorthand	*op = nullptr ;
	int		w = -1 ;
	void operator () (vecsorthand *p,int m) noex {
	    op = p ;
	    w = m ;
	} ;
	int operator () (int = 0) noex ;
	operator int () noex {
	    return operator () () ;
	} ;
} ; /* end struct (vecsorthand_co) */
struct vecsorthand : vecsorthand_head {
	vecsorthand_co	count ;
	vecsorthand_co	del ;
	vecsorthand_co	finish ;
	vecsorthand() noex {
	    count(this,vecsorthandmem_count) ;
	    del(this,vecsorthandmem_del) ;
	    finish(this,vecsorthandmem_finish) ;
	} ;
	vecsorthand(const vecsorthand &) = delete ;
	vecsorthand &operator = (const vecsorthand &) = delete ;
	int start(int,vecsorthand_vcf) noex ;
	int add(cvoid *) noex ;
	int get(int,void *) noex ;
	int delhand(cvoid *) noex ;
	int search(cvoid *,void *) noex ;
	vecsorthand_iter begin() noex {
	    vecsorthand_iter	it(va,0,i) ;
	    return it ;
	} ;
	vecsorthand_iter end() noex {
	    vecsorthand_iter	it(va,i,i) ;
	    return it ;
	} ;
	void dtor() noex ;
	~vecsorthand() noex {
	    dtor() ;
	} ;
} ; /* end struct (vecsorthand) */
#else	/* __cplusplus */
typedef VECSORTHAND		vecsorthand ;
#endif /* __cplusplus */

EXTERNC_begin

typedef int (*vecsorthand_f)(cvoid **,cvoid **) noex ;

extern int vecsorthand_start(vecsorthand *,int,vecsorthand_vcf) noex ;
extern int vecsorthand_finish(vecsorthand *) noex ;
extern int vecsorthand_add(vecsorthand *,cvoid *) noex ;
extern int vecsorthand_get(vecsorthand *,int,void *) noex ;
extern int vecsorthand_del(vecsorthand *,int) noex ;
extern int vecsorthand_delhand(vecsorthand *,cvoid *) noex ;
extern int vecsorthand_count(vecsorthand *) noex ;
extern int vecsorthand_search(vecsorthand *,cvoid *,void *) noex ;

EXTERNC_end


#endif /* VECSORTHAND_INCLUDE */


