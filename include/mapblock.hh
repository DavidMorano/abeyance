/* mapblock HEADER */
/* lang=C++20 */

/* implement a map container of blocks (of a given structure) */
/* version %I% last-modified %G% */


/* revision history:

	= 2011-04-12, David A­D­ Morano
	This subroutine was originally written.  Only the introduction
	of C++11 has allowed this (finally), due to the addition
	(in C++11) of |unordered_map(3c++)|.

*/

/* Copyright © 2011 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	mapblock

	Description:
	This object implements a map from a "key" type (|K|)
	to a given "block" type (|B|).

	Symopsis:
	int mapblock_start<typename K,typename B>(int n = 0) noex

	Arguments:
	n		suggested starting possible number of elements

	Returns:
	>=0		ok
	<0		error (system-return)

*******************************************************************************/

#ifndef	MAPBLOCK_INCLUDE
#define	MAPBLOCK_INCLUDE
#ifdef	__cplusplus /* everything is C++ only */


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<new>
#include	<utility>
#include	<unordered_map>
#include	<functional>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


template<typename K,typename B> class mapblock ;

template <typename K,typename B>
class mapblock_iter {
	typedef mapblock<K,B>		mb_t ;
	typedef typename std::unordered_map<K,B>::iterator	mapit_type ;
	typedef std::pair<const K,B>		value_type ;
	mapit_type		mit ;
public:
	mapblock_iter() noex { } ;
	mapblock_iter(const mapblock_iter<K,B> &oit) noex {
	    if (this != &oit) {
	        mit = oit.mit ;
	    }
	} ;
	mapblock_iter(mapblock_iter<K,B> &&oit) noex {
	    if (this != &oit) {
	        mit = oit.mit ;
	    }
	} ;
	mapblock_iter(mb_t *mbp,bool fend) noex {
	    if (mbp->mp) {
	        if (fend) {
	            mit = mbp->mp->end() ;
	        } else {
	            mit = mbp->mp->begin() ;
	        }
	    }
	} ;
	mapblock_iter<K,B> &operator = (const mapblock_iter<K,B> &oit) noex {
	    if (this != &oit) {
	        mit = oit.mit ;
	    }
	    return *this ;
	} ;
	mapblock_iter<K,B> &operator = (mapblock_iter<K,B> &&oit) noex {
	    if (this != &oit) {
	        mit = oit.mit ;
	    }
	    return *this ;
	} ;
	mapblock_iter<K,B> &operator = (const mapblock_iter<K,B> *oip) noex {
	    if (this != oip) {
	        mit = oip->mit ;
	    }
	    return *this ;
	} ;
	std::pair<const K,B> &operator * () const noex {
	    return *mit ;
	} ;
	mapblock_iter<K,B> &operator ++ () noex { /* pre-increment */
	    ++mit ;
	    return *this ;
	} ;
	mapblock_iter<K,B> operator ++ (int) noex { /* post-increment */
	    mapblock_iter<K,B>	tmp = *this ;
	    mit++ ;
	    return tmp ; /* returns previous PRVALUE */
	} ;
	mapblock_iter<K,B> &operator += (int inc) noex {
	    mit += inc ;
	    return *this ;
	} ;
	mapblock_iter<K,B> &operator + (int inc) const noex {
	    mapblock_iter<K,B>	tmp = *this ;
	    tmp.mit + inc ;
	    return tmp ;
	} ;
	friend bool operator == (const mapblock_iter<K,B> &i1,
		const mapblock_iter<K,B> &i2) noex {
	    return (i1.mit == i2.mit) ;
	} ;
	friend mapblock<K,B> ;
} ; /* end class (mapblock_iter) */

enum mapblockmems {
	mapblockmem_start,
	mapblockmem_finish,
	mapblockmem_count,
	mapblockmem_overlast
} ;

template<typename K,typename B>
struct mapblock_co {
	typedef mapblock<K,B>	mb_t ;
	mb_t		*op = nullptr ;
	int		w = -1 ;
	constexpr void operator () (mb_t *p,int m) noex {
	    op = p ;
	    w = m ;
	} ;
	int operator () (int = 0) noex ;
	operator int () noex {
	    return operator () () ;
	} ;
} ; /* end struct (mapblock_co) */

template<typename K,typename B>
class mapblock {
	std::unordered_map<K,B>			*mp = nullptr ;
	typedef std::unordered_map<K,B>		maptype ;
	typedef mapblock_co<K,B>		mbco_type ;
public:
	typedef K				key_type ;
	typedef B				mapped_type ;
	typedef std::pair<const K,B>		value_type ;
	typedef mapblock_iter<K,B>		iterator ;
	typedef const mapblock_iter<K,B>	const_iterator ;
	mapblock(const mapblock &) = delete ;
	mapblock &operator = (const mapblock &) = delete ;
	mbco_type	start ;
	mbco_type	finish ;
	mbco_type	count ;
	int		ins(K,const B &) noex ;
	int		rem(K) noex ;
	int		present(K &) noex ;
	int		get(K,B *) noex ;
	int		istart(int) noex ;
	int		ifinish() noex ;
	int		icount() noex ;
	iterator begin() noex {
	    iterator	it(this,false) ;
	    return it ;
	} ;
	iterator end() noex {
	    iterator	it(this,true) ;
	    return it ;
	} ;
	constexpr mapblock() noex {
	    start(this,mapblockmem_start) ;
	    finish(this,mapblockmem_finish) ;
	    count(this,mapblockmem_count) ;
	} ; /* end ctor) */
	~mapblock() noex {
	    if (mp) {
	        delete mp ;
		mp = nullptr ;
	    }
	} ; /* end dtor */
	friend iterator ;
} ; /* end class (mapblock) */

template<typename K,typename B>
int mapblock<K,B>::istart(int n) noex {
	typedef decltype(std::nothrow)	nothrow_t ;
	int		rs = SR_INVALID ;
	if (n >= 0) {
	    rs = SR_NOMEM ;
	    try {
		const nothrow_t		nt = std::nothrow ;
		const nullptr_t		np{} ;
	        if ((mp = new(nt) maptype(n)) != np) {
	            rs = SR_OK ;
	        }
	    } catch (...) {
		rs = SR_NOMEM ;
	    }
	}
	return rs ;
}
/* end method (mapblock::istart) */

template<typename K,typename B>
int mapblock<K,B>::ifinish() noex {
	int		rs = SR_BUGCHECK ;
	if (mp) {
	    delete mp ;
	    mp = nullptr ;
	    rs = SR_OK ;
	}
	return rs ;
}


template<typename K,typename B>
int mapblock<K,B>::ins(K k,const B &v) noex {
	typedef	typename maptype::iterator	mit_t ;
	int		rs = SR_BUGCHECK ;
	if (mp) {
	    rs = SR_OK ;
	    try {
	        std::pair<mit_t,bool>	r = mp->insert({k,v}) ;
	        if (!r.second) rs = SR_EXISTS ;
	    } catch (...) {
	        rs = SR_NOMEM ;
	    }
	} /* end if (non-null) */
	return rs ;
}
/* end method (mapblock::ifinish) */

template<typename K,typename B>
int mapblock<K,B>::rem(K k) noex {
	typedef typename maptype::size_type	mitsize_t ;
	int		rs = SR_BUGCHECK ;
	if (mp) {
	    rs = SR_OK ;
	    try {
	        mitsize_t	r = mp->erase(k) ;
	        if (!r) rs = SR_NOENT ;
	    } catch (...) {
	        rs = SR_NOMEM ;
	    }
	} /* end if (non-null) */
	return rs ;
}

template<typename K,typename B>
int mapblock<K,B>::present(K &k) noex {
	typedef typename maptype::iterator	mit_t ;
	int		rs = SR_BUGCHECK ;
	if (mp) {
	    const mit_t	itend = mp->end() ;
	    mit_t	it = mp->find(k) ;
	    rs = (it != itend) ? SR_OK : SR_NOENT ;
	} /* end if (non-null) */
	return rs ;
}

template<typename K,typename B>
int mapblock<K,B>::get(K k,B *vp) noex {
	typedef typename maptype::iterator	mit_t ;
	int		rs = SR_FAULT ;
	if (vp) {
	    rs = SR_BUGCHECK ;
	    if (mp) {
	        typedef typename maptype::value_type	v_t ;
	        const mit_t		it_end = mp->end() ;
	        const mit_t		it = mp->find(k) ;
	        rs = SR_NOENT ;
	        if (it != it_end) {
		    const v_t	r = *it ;
		    *vp = r.second ;
		    rs = SR_OK ;
	        }
	    } /* end if (non-null) */
	} /* end if (non-null) */
	return rs ;
}

template<typename K,typename B>
int mapblock<K,B>::icount() noex {
	int		rs = SR_BUGCHECK ;
	if (mp) {
	    rs = mp->size() ;
	} /* end if (non-null) */
	return rs ;
}
/* end method (mapblock::icount) */

template<typename K,typename B>
int mapblock_co<K,B>::operator () (int a) noex {
	int		rs = SR_BUGCHECK ;
	switch (w) {
	case mapblockmem_start:
	    rs = op->istart(a) ;
	    break ;
	case mapblockmem_finish:
	    rs = op->ifinish() ;
	    break ;
	case mapblockmem_count:
	    rs = op->icount() ;
	    break ;
	} /* end switch */
	return rs ;
}
/* end method (mapblock_co::operator) */


#endif	/* __cplusplus */
#endif /* MAPBLOCK_INCLUDE */


