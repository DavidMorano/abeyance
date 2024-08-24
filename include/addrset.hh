/* addrset HEADER */
/* lang=C++20 */

/* track memory addresses */
/* version %I% last-modified %G% */


/* revision history:

	= 2011-04-12, David A­D­ Morano
	This subroutine was originally written. This is a sort of
	test to replace the previous memory tracking implementation
	inside of the |ucmemalloc(3uc)| facility (so loved).

*/

/* Copyright © 2011 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Names:
	addrset::start
	addrset::count
	addrset::finish
	addrset::ins
	addrset::rem
	addrset::present
	addrset::get
	addrset::curbegin
	addrset::curenum
	addrset::curend

	addrset::istart
	addrset::icount
	addrset::ifinish

	Description:
	Reack memory blocks.

*******************************************************************************/

#ifndef	ADDRSET_INCLUDE
#define	ADDRSET_INCLUDE
#ifdef	__cplusplus /* everything is C++ only */


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<utility>		/* |hash(3c++)| */
#include	<usysdefs.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<mapblock.hh>


#define	ADDRSET_MAGIC	0x65821293


enum addrsetmems {
	addrsetmem_start,
	addrsetmem_count,
	addrsetmem_finish,
	addrsetmem_overlast
} ;

struct addrset_ent {
	cvoid		*addr ;
	size_t		asize ;
} ;

namespace std {
    typedef const addrset_ent		cent ;
    template<> struct hash<addrset_ent> {
	size_t operator() (cent &di) const noex {
	    csize	hv = size_t(di.addr) ;
	    return hv ;
	} ;
    } ; /* end struct-template (hash<addrset_ent>) */
    template<> struct equal_to<addrset_ent> {
	size_t operator() (cent &lhs,cent &rhs) const noex {
	    return (lhs.addr == rhs.addr) ;
	} ;
    } ; /* end struct-template (hash<addrset_ent>) */
}

struct addrset ;

struct addrset_co {
	addrset		*op = nullptr ;
	int		w = -1 ;
	constexpr void operator () (addrset *p,int m) noex {
	    op = p ;
	    w = m ;
	} ;
	int operator () (int = 0) noex ;
	operator int () noex {
	    return operator () () ;
	} ;
} ; /* end struct (addrset_co) */

struct addrset_cur {
	void		*vitcp ;		/* iterator-current */
	void		*vitep ;		/* iterator-end */
} ;

struct addrset {
	friend		addrset_co ;
	typedef addrset_ent	ent ;
	addrset_co	start ;
	addrset_co	count ;
	addrset_co	finish ;
	void		*setp ;
	uint		magic = 0 ;
	constexpr addrset() noex {
	    start(this,addrsetmem_start) ;
	    finish(this,addrsetmem_finish) ;
	    count(this,addrsetmem_count) ;
	} ; /* end ctor */
	addrset(const addrset &) = delete ;
	addrset &operator = (const addrset &) = delete ;
	int	ins(cvoid *,size_t) noex ;
	int	rem(cvoid *) noex ;
	int	present(cvoid *) noex ;
	int	get(cvoid *,ent *) noex ;
	int	curbegin(addrset_cur *) noex ;
	int	curenum(addrset_cur *,ent *) noex ;
	int	curend(addrset_cur *) noex ;
	~addrset() noex {
	    dtor() ;
	} ; /* end if (dtor) */
    private:
	int	istart(int = 0) noex ;
	int	ifinish() noex ;
	int	icount() noex ;
	void	dtor() noex ;
} ; /* end struct (addrset) */


#endif	/* __cplusplus */
#endif /* ADDRSET_INCLUDE */


