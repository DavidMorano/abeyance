/* bits HEADER */
/* lang=C++20 */

/* perform some bit-array type operations */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-15, David A­D­ Morano
	This code was started.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	BITS_INCLUDE
#define	BITS_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<stdintx.h>


#define	BITS		struct bits_head
#define	BITS_TYPEDIGIT	ulonglong
#define	BITS_SHORTDIGS	2


struct bits_head {
	BITS_TYPEDIGIT	*a ;
	BITS_TYPEDIGIT	na[BITS_SHORTDIGS] ;
	int		n ;		/* bits addressed */
	int		nbits ;		/* allocated */
	int		nwords ;	/* allocated */
} ;

#ifdef	__cplusplus

enum bitsmems {
	bitsmem_start,
	bitsmem_finish,
	bitsmem_set,
	bitsmem_clear,
	bitsmem_test,
	bitsmem_anyset,
	bitsmem_ffbs,
	bitsmem_extent,
	bitsmem_count,
	bitsmem_overlast
} ;
class bits ;
class bits_co {
	friend		bits ;
	bits		*op = nullptr ;
	int		w = -1 ;
	void operator () (bits *p,int m) noex {
	    op = p ;
	    w = m ;
	} ;
public:
	int operator () (int = 0) noex ;
	int operator [] (int = 0) noex ;
	operator int () noex {
	    return operator () (0) ;
	} ;
} ; /* end struct (bits_co) */
struct bits : bits_head {
	bits_co		start ;
	bits_co		finish ;
	bits_co		set ;
	bits_co		clear ;
	bits_co		test ;
	bits_co		anyset ;
	bits_co		ffbs ;
	bits_co		extent ;
	bits_co		count ;
	bits() noex {
	    start(this,bitsmem_start) ;
	    finish(this,bitsmem_finish) ;
	    set(this,bitsmem_set) ;
	    clear(this,bitsmem_clear) ;
	    test(this,bitsmem_test) ;
	    anyset(this,bitsmem_anyset) ;
	    ffbs(this,bitsmem_ffbs) ;
	    extent(this,bitsmem_extent) ;
	    count(this,bitsmem_count) ;
	} ;
	operator int () noex {
	    return count ;
	} ;
	void dtor() noex ;
	~bits() {
	    dtor() ;
	} ;
} ; /* end struct (bits) */

#else /* __cplusplus */

typedef	BITS		bits ;

#endif /* __cplusplus */

EXTERNC_begin

extern int	bits_start(bits *,int) noex ;
extern int	bits_set(bits *,int) noex ;
extern int	bits_clear(bits *,int) noex ;
extern int	bits_test(bits *,int) noex ;
extern int	bits_anyset(bits *) noex ;
extern int	bits_ffbs(bits *) noex ;
extern int	bits_extent(bits *) noex ;
extern int	bits_count(bits *) noex ;
extern int	bits_finish(bits *) noex ;

EXTERNC_end


#endif /* BITS_INCLUDE */


