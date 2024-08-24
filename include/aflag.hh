/* aflag HEADER */
/* lang=C++20 */

/* atomic-flag */
/* version %I% last-modified %G% */


/* revision history:

	= 2020-01-13, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 2020 David A­D­ Morano.  All rights reserved. */

#ifndef	AFLAG_INCLUDE
#define	AFLAG_INCLUDE
#ifdef	__cplusplus			/* C++ only */


#include	<envstandards.h>	/* MUST be first to configure */
#include	<atomic>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


enum aflagmems {
	aflagmem_set,
	aflagmem_clear,
	aflagmem_test,
	aflagmem_testandset,
	aflagmem_wait,
	aflagmem_notify,
	aflagmem_notifyall,
	aflagmem_overlast
} ;
enum aflagmxs {
	aflagmx_lockbegin,
	aflagmx_lockend,
	aflagmx_overlast
} ;
struct aflag ;
struct aflag_co {
	aflag		*op = nullptr ;
	int		w = -1 ;
	constexpr void operator () (aflag *p,int m) noex {
	    op = p ;
	    w = m ;
	} ;
	bool operator () () noex ;
	bool operator () (bool) noex ;
	operator bool () noex {
	    return operator () () ;
	} ;
} ; /* end struct (aglag_co) */
struct aflag_mx {
	aflag		*op = nullptr ;
	int		w = -1 ;
	constexpr void operator () (aflag *p,int m) noex {
	    op = p ;
	    w = m ;
	} ;
	int operator () (int = -1) noex ;
	operator int () noex {
	    return operator () () ;
	} ;
} ; /* end struct (aglag_mx) */
struct aflag {
	friend		aflag_mx ;
	aflag_co	set ;
	aflag_co	clear ;
	aflag_co	test ;
	aflag_co	testandset ;
	aflag_co	wait ;
	aflag_co	notify ;
	aflag_co	notifyall ;
	aflag_mx	lockbegin ;
	aflag_mx	lockend ;
	std::atomic_flag	af{} ;
	constexpr aflag() noex {
	    set(this,aflagmem_set) ;
	    clear(this,aflagmem_clear) ;
	    test(this,aflagmem_test) ;
	    testandset(this,aflagmem_testandset) ;
	    wait(this,aflagmem_wait) ;
	    notify(this,aflagmem_notify) ;
	    notifyall(this,aflagmem_notifyall) ;
	    lockbegin(this,aflagmx_lockbegin) ;
	    lockend(this,aflagmx_lockend) ;
	} ;
	operator bool () const noex {
	    return af.test() ;
	} ;
	bool operator = (const bool f) noex {
	    bool	rf = false ;
	    if (f) {
		rf = af.test_and_set() ;
	    } else {
		rf = af.test() ;
	        af.clear() ;
	    }
	    return rf ;
	} ;
private:
	int ilockbegin(int = -1) noex ;
	int ilockend() noex ;
} ; /* end struct (aflag) */


#endif /* __cplusplus */
#endif /* AFLAG_INCLUDE */


