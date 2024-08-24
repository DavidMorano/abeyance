/* bstree HEADER */
/* lang=C++11 */

/* binary search tree */
/* version %I% last-modified %G% */


/* revision history:

	= 2013-03-03, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2013 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Binary-Search-Tree (without rebalancing)

	Notes:

	Q. How do we handle iterative traversal?
	A. There are at least three popular ways to handle iterative
	traveral:
	1. maintain a stack of pointers to previous nodes at each
	   level of the tree; space would be O(depth)
	2. use a so-called "threaded" tree structure where each
	   dangling right-side node (with no additional right-child)
	   actually has a pointer to its in-order successor
	3. use the "parent" method where each node has a pointer
	   to its own parent; we use this method below

	The "parent" scheme:
	If we find that there is no right-child (from our current
	node), we traverse back up to our parent, checking (at each
	step) if we (the current node) is equal to the right-child
	node of our parent. If we arrive at our parent from its
	left-child, then our parent becomes the next current node.
	If we arrive at our parent from its right-child node, then
	we continue to go up in the tree until we either arrive at
	our parent from a left-child or we reach the top of the
	tree (the parent itself has no parent). At any node, we try
	to go down a right-child (if it exists) and then its
	left-child, if it exists.

	This, so-called, "parent" scheme uses up an extra pointer-amount
	of space in each node, O(n) more space, but even though the
	"stack" scheme only uses up O(depth), we prefer the "parent"
	scheme since we do not have to go through the trouble of
	instantiating a stack in the first place.

	For reference, here is a stack solution (pseudo code):

	class iterator {
	    stack<node>	stack = new stack<node> ;
	    node	n ;
	    iterator(node an) : n(an) { } ;
	    iterator &findnext() {
		iterator	it(nullptr) ;
	        while (n != nullptr) {
		    stack.push(n) ;
		    n = n->left ;
		}
		n = stack.pop() ;
		it = n ;
		n = n->right ;
		return it ;
	    } ;
	} ;

*******************************************************************************/

#ifndef	BSTREE_INCLUDE
#define	BSTREE_INCLUDE
#ifdef	__cplusplus /* everything is C++ only */


#include	<envstandards.h>	/* MUST be first to configure */
#include	<climits>
#include	<new>
#include	<initializer_list>
#include	<algorithm>
#include	<functional>
#include	<stack>
#include	<vector>
#include	<usystem.h>
#include	<localmisc.h>


template <typename T,typename Comp = std::less<T>>
class bstree ;

template <typename T,typename Comp = std::less<T>>
class bstree_iter ;

template <typename T,typename Comp = std::less<T>>
class bstree_node {
	bstree_node<T,Comp>	*parent = nullptr ;
	bstree_node<T,Comp>	*left = nullptr ;
	bstree_node<T,Comp>	*right = nullptr ;
	T			val ;
	void SetVal(const T v) noex {
	    val = v ;
	} ;
public:
	bstree_node(T av) : val(av) noex { } ;
	bstree_node(const bstree_node<T> &other) = delete ;
	bstree_node &operator = (const bstree_node<T> &other) = delete ;
	~bstree_node() {
	} ;
 	friend bstree<T,Comp> ;
 	friend bstree_iter<T,Comp> ;
} ; /* end class (bstree_node) */

template <typename T,typename Comp>
class bstree_iter {
	typedef bstree_node<T,Comp>	node ;
	bstree_node<T,Comp>	*n = nullptr ;
	mutable T		defval ;
	bstree_iter<T,Comp>	&findnext(int) ;
	typedef bstree_iter	bit ;
public:
	bstree_iter() noex { } ;
	bstree_iter(node *an) : n(an) noex { } ;
	bstree_iter(const bstree_iter<T,Comp> &it) noex {
	    if (this != &it) {
	        n = it.n ;
	    }
	} ;
	bstree_iter(bstree_iter<T,Comp> &&it) noex {
	    if (this != &it) {
	        n = it.n ;
		it.n = nullptr ;
	    }
	} ;
	bstree_iter<T,Comp> &operator = (const bstree_iter<T,Comp> &it) noex {
	    if (this != &it) {
	        n = it.n ;
	    }
	    return (*this) ;
	} ;
	bstree_iter<T,Comp> &operator = (bstree_iter<T,Comp> &&it) noex {
	    if (this != &it) {
	        n = it.n ;
		it.n = nullptr ;
	    }
	    return (*this) ;
	} ;
	bstree_iter<T,Comp> &operator = (const bstree_iter<T,Comp> *ip) noex {
	    if (this != ip) {
	        n = ip->n ;
	    }
	    return (*this) ;
	} ;
	bstree_iter<T,Comp> &operator = (const node *nn) noex {
	    n = nn ; /* possible nullptr */
	    return (*this) ;
	} ;
	~bstree_iter() {
	    n = nullptr ;
	} ;
	void setnode(node *nn) noex {
	    n = nn ; /* possible nullptr */
	} ;
	T &operator * () const noex {
	    T &rv = defval ;
	    if (n != nullptr) {
		rv = n->val ;
	    }
	    return rv ;
	} ;
	bstree_iter<T,Comp> &operator ++ () noex { /* pre-increment */
	    return findnext(1) ;
	} ;
	bstree_iter<T,Comp> operator ++ (int) noex { /* post-increment */
	    btree_iter<T.Comp>	tmp(*this) ;
	    findnext(1) ;
	    return tmp ; /* returns previous value */
	} ;
	bstree_iter<T,Comp> &operator += (int inc) noex {
	    return findnext(inc) ;
	} ;
	bstree_iter<T,Comp> &operator + (int inc) noex {
	    return findnext(inc) ;
	} ;
	operator int() const noex {
	    return (n != nullptr) ;
	} ;
	operator bool() const noex {
	    return (n != nullptr) ;
	} ;
	friend bool operator == (const bstree_iter<T,Comp> &i1,
		const bstree_iter<T,Comp> &i2) noex {
	    return (i1.n == i2.n) ;
	} ;
	friend bool operator != (const bstree_iter<T,Comp> &i1,
		const bstree_iter<T,Comp> &i2) noex {
	    return (i1.n != i2.n) ;
	} ;
	friend bstree<T,Comp> ;
} ; /* end class (bstree_iter) */

template <typename T,typename Comp>
bstree_iter<T,Comp> &bstree_iter<T,Comp>::findnext(int inc) noex {
	if (n != nullptr) {
	    if (inc > 1) {
		findnext(1) ;
		findnext(inc-1) ;
	    } else if (inc > 0) {
   	        if (n->right != nullptr) {
      		    n = n->right ;
      		    while (n->left != nullptr) {
        	        n = n->left ;
        	    }
     	        } else {
		    bstree_node<T,Comp> *p = n->parent ;
		    while ((p != nullptr) && (n == p->right)) {
           	        n = p ;
           	        p = p->parent;
         	    }
		    n = p ;
		}
	    } /* end if (inc) */
        } /* end if (not-nullptr) */
 	return (*this) ;
} /* end method (bstree_iterator::findnext) */

struct bstree_depth {
	int		dmin = INT_MAX ;
	int		dmax = 0 ;
	void clear() noex {
	    dmin = INT_MAX ;
	    dmax = 0 ;
	} ;
} /* end method (bstree_depth) */

template <typename T,typename Comp>
class bstree {
	typedef bstree_depth		depth ;
	typedef bstree_node<T,Comp>	node ;
	using std:nothrow ;
	bstree_node<T,Comp>	*root = nullptr ;
	Comp			keycmp ;
	int			c = 0 ;
        bstree_iter<T,Comp> FindNodeByVal(node *n,const T &v) const noex {
	    bstree_iter<T,Comp>	it ;
	    if (root != nullptr) {
	        if (keycmp(v,n->val)) { /* less */
	            if (n->left != nullptr) {
		        it = FindNodeByVal(n->left,v) ;
	            }
	        } else if (keyequal(n->val,v)) { /* equal */
	            it.setnode(n) ;
	        } else {
	            if (n->right != nullptr) {
		        it = FindNodeByVal(n->right,v) ;
	            }
	        }
	    } /* end if non-null root) */
	    return it ;
        } ;
	void ReplaceUsInParent(node *np,node *c) noex {
	    node 	*p = np->parent ;
	    if (p->left == np) {
		p->left = c ;
	    } else {
		p->right = c ;
	    }
	    if (c != nullptr) c->parent = p ;
	} ;
	node *GetChild(node *np) const noex {
	    return (np->left != nullptr) ? np->left : np->right ;
	} ;
	node *FindMinNode(node *np) const noex {
	    while (np->left != nullptr) {
		np = np->left ;
	    }
	    return np ;
	} ;
	int delnodes(node *n) noex {
	    int		i = 0 ;
	    if (n != nullptr) {
		i += 1 ;
	        c += delnodes(n->left) ;
	        c += delnodes(n->right) ;
		delete n ;
	    }
	    return i ;
	} ;
	int insert(node *n,node *nn) noex {
	    int		d = 0 ;
	    if (keycmp(nn->val,n->val)) {
		if (n->left != nullptr) {
	            d = insert(n->left,nn) ;
		} else {
		    nn->parent = n ;
		    n->left = nn ;
		}
	    } else {
		if (n->right != nullptr) {
	            d = insert(n->right,nn) ;
		} else {
		    nn->parent = n ;
		    n->right = nn ;
		}
	    }
	    return d ;
	} ;
	int walk(std::vector<T> &vl,node *n) const noex {
	    int		i = 0 ;
	    if (n != nullptr) {
		if (n->left) {
		    i += walk(vl,n->left) ;
		}
	        vl.push_back(n->val) ;
	        i += 1 ;
	        if (n->right) {
		    i += walk(vl,n->right) ;
		}
	    }
	    return i ;
	} ;
	bool keyequal(const T &v1,const T &v2) const noex { /* equal */
	    bool 	f = true ;
	    f = f && (! keycmp(v1,v2)) ;
	    f = f && (! keycmp(v2,v1)) ;
	    return f ;
	} ;
public:
	typedef		bstree_iter<T,Comp> iterator ;
	typedef		T value_type ;
	bstree() { } ;
	bstree(const bstree<T,Comp> &al) noex {
	    if (this != &al) {
	        bstree_node<T,Comp>	*an = al.root ;
	        if (root != nullptr) clear() ;
	        while (an != nullptr) {
		    add(an->val) ;
	            an = an->next ;
	        }
	    }
	} ;
	bstree(bstree<T,Comp> &&al) noex {
	    if (this != &al) {
	        if (root != nullptr) clear() ;
	        root = al.root ;
	        c = al.c ;
	        al.root = nullptr ;
	        al.c = 0 ;
	    }
	} ;
	bstree &operator = (const bstree<T,Comp> &al) noex {
	    if (this != &al) {
	        bstree_node<T,Comp>	*an = al.root ;
	        if (root != nullptr) clear() ;
	        while (an != nullptr) {
		    add(an->val) ;
	            an = an->next ;
	        }
	    }
	    return (*this) ;
	} ;
	bstree &operator = (bstree<T,Comp> &&al) noex {
	    if (this != &al) {
	        if (root != nullptr) clear() ;
	        root = al.root ;
	        c = al.c ;
	        al.root = nullptr ;
	        al.c = 0 ;
	    }
	    return (*this) ;
	} ;
	bstree(const std::initializer_list<T> &list) noex {
	    if (root != nullptr) clear() ;
	    for (const T &v : list) {
		add(v) ;
	    }
	} ;
	bstree &operator = (const std::initializer_list<T> &list) noex {
	    if (root != nullptr) clear() ;
	    for (const T &v : list) {
		add(v) ;
	    }
	    return (*this) ;
	} ;
	bstree &operator += (const std::initializer_list<T> &list) noex {
	    for (const T &v : list) {
		add(v) ;
	    }
	    return (*this) ;
	} ;
	bstree &operator += (const T &v) noex {
	    add(v) ;
	    return (*this) ;
	} ;
	~bstree() {
	    if (root != nullptr) {
	        delnodes(root) ;
	        root = nullptr ;
	    }
	    c = 0 ;
	} ;
	int clear() noex {
	    int		rc = c ;
	    if (root != nullptr) {
	        delnodes(root) ;
	        root = nullptr ;
	    }
	    c = 0 ;
	    return rc ;
	} ;
	int add(const T &v) noex {
	    bstree_node<T,Comp>	*nn = new(nothrow) bstree_node<T,Comp>(v) ;
	    int			rc = -1 ;
	    if (nn != nullptr) {
		if (root != nullptr) {
	            insert(root,nn) ;
		} else {
		    root = nn ;
		}
	        rc = ++c ;
	    }
	    return rc ;
	} ;
	int add(const std::initializer_list<T> &il) noex {
	    for (const T &v : il) {
		add(v) ;
	    }
	    return c ;
	} ;
	bstree &operator = (const std::initializer_list<T> &il) noex {
	    for (const T &v : il) {
		add(v) ;
	    }
	    return (*this) ;
	} ;
	int add(const bstree<T,Comp> &other) noex {
	    for(const T &v : other) {
		add(v) ;
	    }
	    return c ;
	} ;
	int del(iterator &it) noex {
	    int		rc = -1 ;
	    if (it) {
	        node	*n = it.n ; /* friend */
	        node	*l, *r ;
		l = n->left ;
		r = n->right ;
		if (l || r) { /* 1 or 2 children */
		    if (l  && r) { /* two children */
			node *np = FindMinNode(n->right) ;
			n->SetVal(np->val) ;
	    		ReplaceUsInParent(np,np->right) ;
	    	        delete np ;
		    } else { /* one child */
			node	*child = GetChild(n) ;
		        if (n->parent != nullptr) {
			    ReplaceUsInParent(n,child) ;
			} else {
			    root = child ;
			    if (child != nullptr) child->parent = nullptr ;
			}
			it.setnode(child) ;
			delete n ;
		    }
		} else { /* leaf node */
		    if (n->parent != nullptr) {
			ReplaceUsInParent(n,nullptr) ;
			it.setnode(n->parent) ;
		    } else {
			root = nullptr ;
			it.setnode(nullptr) ;
		    }
		    delete n ;
		}
		rc = --c ;
	    } /* end if (iterator not at end) */
	    return rc ;
	} ;
	int delval(const T &v) noex {
	    int		rc = -1 ;
	    if (root != nullptr) {
		iterator	it ;
	        if (it = FindNodeByVal(root,v)) {
		    rc = del(it) ;
		}
	    }
	    return rc ;
	} ;
	int topval(const T **rpp) const noex {
	    if (root != nullptr) {
	        bstree_node<T,Comp>	*n = root ;
		*rpp = &n->val ;
	    } else {
	        *rpp = nullptr ;
	    }
	    return c ;
	} ;
	int minval(const T **rpp) const noex {
	    if (root != nullptr) {
	        bstree_node<T,Comp>	*n = root ;
		while (n->left != nullptr) {
		    n = n->left ;
		}
		*rpp = &n->val ;
	    } else {
	        *rpp = nullptr ;
	    }
	    return c ;
	} ;
	int maxval(const T **rpp) const noex {
	    if (root != nullptr) {
	        bstree_node<T,Comp>	*n = root ;
		while (n->right != nullptr) {
		    n = n->right ;
		}
		*rpp = &n->val ;
	    } else {
	        *rpp = nullptr ;
	    }
	    return c ;
	} ;
	int count() const noex {
	    return c ;
	} ;
	int empty() const noex {
	    return (c == 0) ;
	} ;
	operator int() const noex {
	    return c ;
	} ;
	operator bool() const noex {
	    return (c != 0) ;
	} ;
	int storevec(std::vector<T> &vl) const noex {
	    int		c = 0 ;
	    if (root != nullptr) {
	        c = walk(vl,root) ;
	    }
	    return c ;
	} ;
	iterator begin() const noex {
	    iterator 	it ;
	    if (root != nullptr) {
	        bstree_node<T,Comp>	*n = root ;
		while (n->left != nullptr) {
		    n = n->left ;
		}
		it = iterator(n) ;
	    }
	    return it ;
	} ;
	iterator end() const noex {
	    iterator it ;
	    return it ;
	} ;
	iterator find(const T& v) const noex {
	    iterator it ;
	    if (root != nullptr) {
		it = FindNodeByVal(root,v) ;
	    }
	    return it ;
	} ;
	int depth(bstree_depth *resp) const noex {
	    int		d = 0 ;
	    if (resp != nullptr) resp->clear() ;
	    d = depthrecurse(resp,0,root) ;
 	    return d ;
        } ; /* end method (depth) */
	int depthrecurse(bstree_depth *resp,int i,node *rp) const noex {
	    int		d = 0 ;
	    if (rp != nullptr) {
	        int	d_left = depthrecurse(resp,(i+1),rp->left) ;
	        int	d_right = depthrecurse(resp,(i+1),rp->right) ;
	        d = 1 ;
	        d += std::max(d_left,d_right) ;
	    } else {
		if (resp != nullptr) {
		     resp->dmin = std::min(resp->dmin,i) ;
		     resp->dmax = std::max(resp->dmax,i) ;
		}
	    }
	    return d ;
    } ; /* end method (depthrecurse) */
} ; /* end class (bstree) */


#endif	/* __cplusplus */
#endif /* BSTREE_INCLUDE */


