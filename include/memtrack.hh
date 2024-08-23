/* memtrack HEADER */
/* lang=C++20 */

/* track memory chunks */
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
	memtrack::start
	memtrack::count
	memtrack::finish
	memtrack::ins
	memtrack::rem
	memtrack::present
	memtrack::get
	memtrack::istart
	memtrack::icount
	memtrack::ifinish

	Description:
	Reack memory blocks.

*******************************************************************************/

#ifndef	MEMTRACK_INCLUDE
#define	MEMTRACK_INCLUDE
#ifdef	__cplusplus /* everything is C++ only */


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdint>		/* |uintptr_t| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<mapblock.hh>


#define	MEMTRACK_MAGIC	0x65821293


enum memtrackmems {
	memtrackmem_start,
	memtrackmem_count,
	memtrackmem_finish,
	memtrackmem_overlast
} ;

struct memtrack_ent {
	cvoid		*addr ;
	int		asize ;
} ;

struct memtrack ;

struct memtrack_co {
	memtrack	*op = nullptr ;
	int		w = -1 ;
	constexpr void operator () (memtrack *p,int m) noex {
	    op = p ;
	    w = m ;
	} ;
	int operator () (int = 0) noex ;
	operator int () noex {
	    return operator () () ;
	} ;
} ; /* end struct (memtrack_co) */

struct memtrack {
	typedef memtrack_ent	ent ;
	typedef mapblock<uintptr_t,memtrack_ent> track_t ;
	mapblock<uintptr_t,memtrack_ent>	*tp = nullptr ;
	memtrack_co	start ;
	memtrack_co	count ;
	memtrack_co	finish ;
	uint		magic = 0 ;
	constexpr memtrack() noex {
	    start(this,memtrackmem_start) ;
	    finish(this,memtrackmem_finish) ;
	    count(this,memtrackmem_count) ;
	} ; /* end ctor */
	memtrack(const memtrack &) = delete ;
	memtrack &operator = (const memtrack &) = delete ;
	int	ins(cvoid *,int) noex ;
	int	rem(cvoid *) noex ;
	int	present(cvoid *) noex ;
	int	get(cvoid *,ent *) noex ;
	int	istart(int = 0) noex ;
	int	ifinish() noex ;
	int	icount() noex ;
	void	dtor() noex ;
	~memtrack() noex {
	    dtor() ;
	} ; /* end if (dtor) */
} ; /* end struct (memtrack) */


#endif	/* __cplusplus */
#endif /* MEMTRACK_INCLUDE */


