/* sortlist SUPPORT */
/* lang=C++20 */

/* sorted list operations */
/* version %I% last-modified %G% */


/* revision history:

	 = 2007-12-01, David A.D. Morano
	Module was originally written.

*/

/* Copyright © 2007 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	sortlist

	Description:
	These routines are used when the caller just wants to store
	an item in a sorted list.  The item us usually just a pointer
	to the user's real data.  Items have keys and values, like
	with a hash table structure except that we use a balanced
	binary tree to store everything.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<usyscalls.h>
#include	<localmisc.h>

#include	"sortlist.h"


/* local defines */

#define	SL		sortlist


/* imported namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */

template<typename ... Args>
static int sortlist_ctor(sortlist *op,Args ... args) noex {
	int		rs = SR_FAULT ;
	if (op && (args && ...)) {
	    cnullptr	np{} ;
	    rs = SR_OK ;

	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (sortlist_ctor) */

static int sortlist_dtor(sortlist *op) noex {
	int		rs = SR_FAULT ;
	if (op) {
	    rs = SR_OK ;
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (sortlist_dtor) */

template<typename ... Args>
static inline int sortlist_magic(sortlist *op,Args ... args) noex {
	int		rs = SR_FAULT ;
	if (op && (args && ...)) {
	    rs = (op->magic == SORTLIST_MAGIC) ? SR_OK : SR_NOTOPEN ;
	}
	return rs ;
}
/* end subroutine (sortlist_magic) */


/* local variables */

struct subclass {
	int
} ;


/* exported variables */


/* exported subroutines */

int sortlist_start(SL *op,sortlist_f cmpfunc) noex {
	int		rs = SR_FAULT ;
	if ((rs = sortlist_ctor(op,cmpfunc)) >= 0) {
	    op->balance = 0 ;
	    op->root = nullptr ;
	    op->magic = SORTLIST_MAGIC ;
	    if (rs < 0) {
		sortlist_dtor(op) ;
	    }
	} /* end if (sortlist_ctor) */
	return rs ;
}
/* end subroutine (sortlist_start) */

int sortlist_finish(SL *op) noex {
	int		rs = SR_OK ;

	if (op == nullptr) return BAD ;

	if (op->va != nullptr) {

	    for (int i = 0 ; i < op->i ; i += 1) {

	        if ((op->va)[i] != nullptr)
	            free((op->va)[i]) ;

	    } /* end while */

/* free the sortlist array itself */

	    free(op->va) ;

	    op->va = nullptr ;
	}

	op->i = 0 ;
	op->e = 0 ;
	return OK ;
}
/* end subroutine (sortlist_finish) */

int sortlist_add(op,p,cmpfunc)
sortlist	*op ;
void		*p ;
int		(*cmpfunc)() ;
{
	int		rs ;
	int		i, nn ;
	int		j, bot, top, ii ;
	char		*sp ;
	void		**ep ;

#if	CF_DEBUGS
	debugprintf("sortlistadd: ent\n") ;
#endif

	if (op == nullptr) return -1 ;

#if	CF_DEBUGS
	debugprintf("sortlistadd: ent, i=%d\n",op->i) ;
#endif

/* do we have to grow the sortlist array ? */

	if ((op->i + 1) > op->e) {

	    if (op->e == 0) {

	        nn = SORTLIST_DEFENTRIES ;
	        ep = (void **)
	            malloc(sizeof(char **) * (nn + 1)) ;

	    } else {

	        nn = op->e * 2 ;
	        ep = (void **)
	            realloc(op->va,sizeof(char **) * (nn + 1)) ;

	    }

	    if (ep == nullptr) return -1 ;

	    op->va = ep ;
	    op->e = nn ;

	} /* end if */

/* do the regular thing */

	op->c += 1 ;			/* increment list count */

/* link into the list structure */

	if (cmpfunc == nullptr) cmpfunc = strcmp ;

/* find the place in the existing list where this new item should be added */

	bot = 0 ;
	top = MAX((op->i - 1),0) ;
	ii = (bot + top) / 2 ;

#if	CF_DEBUGS
	debugprintf("sortlistadd: bot=%d top=%d ii=%d\n",bot,top,ii) ;
#endif

	while ((top - bot) > 0) {

	    if ((rs = (*cmpfunc)(p,op->va[ii])) < 0) {
	        top = ii - 1 ;

	    } else if (rs > 0) {
	        bot = ii + 1 ;

	    } else
	        break ;

	    ii = (bot + top) / 2 ;

	} /* end while */

#if	CF_DEBUGS
	debugprintf("sortlistadd: found bot=%d top=%d ii=%d\n",bot,top,ii) ;
#endif

	if (ii < op->i) {

	    if ((*cmpfunc)(p,op->va[ii]) > 0)
	        ii += 1 ;

/* move all entries from "ii" through "op->i - 1" down one */

	    for (j = (op->i - 1) ; j >= ii ; j -= 1) {
	        (op->va)[j + 1] = (op->va)[j] ;
	    }

	} /* end if */

/* load the new entry */

	(op->va)[ii] = p ;
	op->i += 1 ;
	(op->va)[op->i] = nullptr ;

	return ii ;
}
/* end subroutine (sortlist_add) */


/* get an entry (enumerated) from the vector list */
int sortlist_get(op,i,pp)
sortlist	*op ;
int		i ;
void		**pp ;
{

#if	CF_DEBUGS
	debugprintf("sortlistget: ent\n") ;
#endif

	if (op == nullptr) return BAD ;

#if	CF_DEBUGS
	debugprintf("sortlistget: i=%d\n",i) ;
#endif

	*pp = nullptr ;
	if ((i < 0) || (i >= op->i)) return BAD ;

#if	CF_DEBUGS
	debugprintf("sortlistget: 2\n") ;
#endif

	if (op->va == nullptr) return BAD ;

#if	CF_DEBUGS
	debugprintf("sortlistget: 3\n") ;
#endif

	*pp = (op->va)[i] ;

#if	CF_DEBUGS
	debugprintf("sortlistget: 4\n") ;
#endif

	return OK ;
}
/* end subroutine (sortlist_get) */


/* delete an entry */
int sortlist_del(op,i)
sortlist	*op ;
int		i ;
{
	int		j ;

	if (op == nullptr) return BAD ;

	if ((i < 0) || (i >= op->i)) return BAD ;

	if (op->va == nullptr) return OK ;

	op->i -= 1 ;
	for (j = i ; j < op->i ; j += 1) {
	    (op->va)[j] = (op->va)[j + 1] ;
	}

	(op->va)[op->i] = nullptr ;

	op->c -= 1 ;		/* decrement list count */
	return OK ;
}
/* end subroutine (sortlist_del) */


/* return the count of the number of items in this list */
int sortlist_count(op)
sortlist	*op ;
{

	if (op == nullptr) return BAD ;

	return op->c ;
}
/* end subroutine (sortlist_count) */


/* search for an entry in the vector list */
int sortlist_search(op,ep,cmpfunc,pp)
sortlist	*op ;
void		*ep ;
int		(*cmpfunc)() ;
void		**pp ;
{
	int		rs ;
	int		i ;
	void		*ep2 ;
	void		**rp ;

	if (op == nullptr) return BAD ;
	if (ep == nullptr) return BAD ;
	if (pp == nullptr) return BAD ;

	if (op->va == nullptr) return BAD ;

	rp = (void **) bsearch(&ep,op->va,op->i,
	    sizeof(void *),cmpfunc) ;

	rs = BAD ;
	if (rp != nullptr) {

	    i = (rp - op->va) ;
	    rs = OK ;

	}

	*pp = nullptr ;
	if (rs >= 0) *pp = op->va[i] ;

	return (rs >= 0) ? i : rs ;
}
/* end subroutine (sortlist_search) */


