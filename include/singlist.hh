/* singlist HEADER */
/* lang=C++98 */

/* regular (no-frills) singly-linked pointer queue (not-circular) */
/* version %I% last-modified %G% */


/* revision history:

	= 2013-03-03, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2013 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This is a container object (elements are stored within it).
	This also is implemented as a single-linked list of nodes.
	This object is very useful for normal queue operations
	(insert at tail, remove at head).  The following operations
	are supported:

	+ instail		insert at tail
	+ inshead		insert at head
	+ remhead		remove from head

	The only major operation (for relatively normal queues)
	which is *not* supported is:

	+ remtail		remove from tail

	Enjoy.

*******************************************************************************/

#ifndef	SINGLIST_INCLUDE
#define	SINGLIST_INCLUDE
#ifdef	__cplusplus /* everything is C++ only */


#include	<envstandards.h>	/* MUST be first to configure */
#include	<new>
#include	<initializer_list>
#include	<usystem.h>


template <typename T>
class singlist ;

template <typename T>
class singlist_iter ;

template <typename T>
class singlist_node {
	singlist_node<T>	*next = nullptr ;
	T			val ;
	singlist_node(const singlist_node<T> &other) = delete ;
	singlist_node &operator = (const singlist_node<T> &other) = delete ;
	singlist_node(const T &av) noex : val(av) { } ;
	~singlist_node() { } ;
 	friend singlist<T> ;
 	friend singlist_iter<T> ;
} ; /* end class (singlist_node) */

template <typename T>
class singlist_iter {
	singlist_node<T>	*n = nullptr ;
	mutable T		defval ;
public:
	singlist_iter() noex { } ;
	singlist_iter(singlist_node<T>* an) noex : n(an) { } ;
	singlist_iter(const singlist_iter<T> &it) noex {
	    if (this != &it) {
	        n = it.n ;
	    }
	} ;
	singlist_iter(singlist_iter<T> &&it) noex {
	    if (this != &it) {
	        n = it.n ;
		it.n = nullptr ;
	    }
	} ;
	singlist_iter &operator = (const singlist_iter<T> &it) noex {
	    if (this != &it) {
	        n = it.n ;
	    }
	    return (*this) ;
	} ;
	singlist_iter &operator = (singlist_iter<T> &&it) noex {
	    if (this != &it) {
	        n = it.n ;
		it.n = nullptr ;
	    }
	    return (*this) ;
	} ;
	singlist_iter &operator = (const singlist_iter<T> *ip) noex {
	    if (this != ip) {
	        n = ip->n ;
	    }
	    return (*this) ;
	} ;
	~singlist_iter() {
	    n = nullptr ;
	} ;
	friend bool operator == (const singlist_iter<T> &i1,
		const singlist_iter<T> &i2) noex {
	    return (i1.n == i2.n) ;
	} ;
	friend bool operator != (const singlist_iter<T> &i1,
		const singlist_iter<T> &i2) noex {
	    return (i1.n != i2.n) ;
	} ;
	T &operator * () const noex {
	    T &rv = defval ;
	    if (n != nullptr) {
		rv = n->val ;
	    }
	    return rv ;
	} ;
	singlist_iter &operator ++ () noex { /* pre */
	    if (n != nullptr) {
	        n = n->next ;
	    }
	    return (*this) ;
	} ;
	singlist_iter &operator ++ (int) noex { /* post */
	    singlist_iter	pre(*this) ; 
	    if (n != nullptr) {
	        n = n->next ;
	    }
	    return pre ;
	} ;
	singlist_iter &operator += (int inc) noex {
	    if (n != nullptr) {
		while ((n != nullptr) && (inc-- > 0)) {
	            n = n->next ;
		}
	    }
	    return (*this) ;
	} ;
	operator int() noex {
	    return (n != nullptr) ;
	} ;
	operator bool() noex {
	    return (n != nullptr) ;
	} ;
} ; /* end class (singlist_iter) */

template <typename T>
class singlist {
	singlist_node<T>	*head = nullptr ;
	singlist_node<T>	*tail = nullptr ;
	int			c = 0 ;
public:
	typedef		singlist_iter<T> iterator ;
	typedef		T value_type ;
	singlist() = default ;
	singlist(const singlist<T> &al) noex {
	    if (this != &al) {
	        singlist_node<T>	*an = al.head ;
	        if (head != nullptr) clear() ;
	        while (an != nullptr) {
		    instail(an->val) ;
	            an = an->next ;
	        }
	    }
	} ;
	singlist(singlist<T> &&al) noex {
	    if (this != &al) {
	        if (head != nullptr) clear() ;
	        head = al.head ;
	        tail = al.tail ;
	        c = al.c ;
	        al.head = nullptr ;
	        al.tail = nullptr ;
	        al.c = 0 ;
	    }
	} ;
	singlist &operator = (const singlist<T> &al) noex {
	    if (this != &al) {
	        singlist_node<T>	*an = al.head ;
	        if (head != nullptr) clear() ;
	        while (an != nullptr) {
		    instail(an->val) ;
	            an = an->next ;
	        }
	    }
	} ;
	singlist &operator = (singlist<T> &&al) noex {
	    if (this != &al) {
	        if (head != nullptr) clear() ;
	        head = al.head ;
	        tail = al.tail ;
	        c = al.c ;
	        al.head = nullptr ;
	        al.tail = nullptr ;
	        al.c = 0 ;
	    }
	} ;
	singlist(const std::initializer_list<T> &list) noex {
	    if (head != nullptr) clear() ;
	    for (const T &v : list) {
		instail(v) ;
	    }
	} ;
	singlist &operator = (const std::initializer_list<T> &list) noex {
	    if (head != nullptr) clear() ;
	    for (const T &v : list) {
		instail(v) ;
	    }
	    return (*this) ;
	} ;
	singlist &operator += (const std::initializer_list<T> &list) noex {
	    for (const T &v : list) {
		instail(v) ;
	    }
	    return (*this) ;
	} ;
	singlist &operator += (const T v) noex {
	    instail(v) ;
	    return (*this) ;
	} ;
	~singlist() {
	    singlist_node<T>	*nn, *n = head ;
	    while (n != nullptr) {
		nn = n->next ;
		delete n ;
		n = nn ;
	    } /* end while */
	    head = nullptr ;
	    tail = nullptr ;
	    c = 0 ;
	} ;
	int count() const noex {
	    return c ;
	} ;
	int empty() const noex {
	    return (c == 0) ;
	} ;
	operator int() const noex {
	    return (c != 0) ;
	} ;
	operator bool() const noex {
	    return (c != 0) ;
	} ;
	int clear() noex {
	    singlist_node<T>	*nn, *n = head ;
	    int		rc = c ;
	    while (n != nullptr) {
		nn = n->next ;
		delete n ;
		n = nn ;
		rc += 1 ;
	    } /* end while */
	    head = nullptr ;
	    tail = nullptr ;
	    c = 0 ;
	    return rc ;
	} ;
	int instail(const T &v) noex {
	    singlist_node<T>	*nn = new(std::nothrow) singlist_node<T>(v) ;
	    int			rc = SR_NOMEM ; /* error indication */
	    if (nn != nullptr) {
	        singlist_node<T>	*n = tail ;
	        if (n != nullptr) {
	            n->next = nn ;
	        } else {
	            head = nn ;
	        }
	        tail = nn ;
	        rc = c++ ;		/* return previous value */
	    } /* end if (allocation sycceeded) */
	    return rc ;
	} ;
	int inshead(const T &v) noex {
	    singlist_node<T>	*nn = new(std::nothrow) singlist_node<T>(v) ;
	    int			rc = -1 ;
	    if (nn != nullptr) {
	        singlist_node<T>	*n = head ;
	        if (n != nullptr) {
		    nn->next = n->next ;
	        } else {
	            tail = nn ;
	        }
	        head = nn ;
	        rc = c++ ;		/* return previous value */
	    } /* end if */
	    return rc ;
	} ;
	int insfront(const T &v) noex {
	    return inshead(v) ;
	} ;
	int insback(const T &v) noex {
	    return instail(v) ;
	} ;
	int ins(const T &v) noex {
	    return instail(v) ;
	} ;
	int add(const T &v) noex {
	    return instail(v) ;
	} ;
	int gethead(const T **rpp) const noex {
	    *rpp = (head != nullptr) ? &head->val : nullptr ;
	    return c ;
	} ;
	int gettail(const T **rpp) const noex {
	    *rpp = (tail != nullptr) ? &tail->val : nullptr ;
	    return c ;
	} ;
	int getfront(const T **rpp) const noex {
	    *rpp = (head != nullptr) ? &head->val : nullptr ;
	    return c ;
	} ;
	int getback(const T **rpp) const noex {
	    *rpp = (tail != nullptr) ? &tail->val : nullptr ;
	    return c ;
	} ;
	int remhead(T *vp) noex {
	    int		rs = SR_EMPTY ;
	    if (head != nullptr) {
		singlist_node<T>	*n = head ;
		if (vp != nullptr) *vp = n->val ;
		head = n->next ;
		if (head == nullptr) tail = nullptr ;
		delete n ;
		rs = --c ;
	    }
	    return rs ;
	} ;
	int rem(T *vp) noex {
	    return remhead(vp) ;
	} ;
	iterator begin() const noex {
	    iterator it(head) ;
	    return it ;
	} ;
	iterator end() const noex {
	    iterator it ;
	    return it ;
	} ;
} ; /* end class (singlist) */


#endif	/* __cplusplus */
#endif /* SINGLIST_INCLUDE */


