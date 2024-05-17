/* uunamerec SUPPORT */
/* lang=C++20 */

/* string uunamerec object */
/* version %I% last-modified %G% */

#define	CF_FASTGROW	1
#define	CF_UCMALLOC	1

/* revision history:

	= 1994-03-24, David A­D­ Morano
	This object module was morphed from some previous one.
	I do not remember what the previous one was.

*/

/* Copyright © 1994 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This object module creates and manages a string table object.
	This string table can later be written to a file or otherwise
	stored some way so that it can be used in-place later.  This
	is often useful for cache files or ELF code object files.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/types.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<usystem.h>
#include	<hash.h>
#include	<hashindex.h>
#include	<nextpowtwo.h>
#include	<localmisc.h>		/* |MODP2| */

#include	"uunamerec.h"


/* local defines */

#define	UUNAMEREC_STARTLEN	100	/* starting number records */


/* external subroutines */


/* forward references */

static int	uunamerec_extend(uunamerec *) noex ;


/* exported variables */


/* exported subroutines */

int uunamerec_start(uunamerec *op,int startlen) noex {
	int		rs = SR_FAULT ;
	if (op) {
	    void	*vp{} ;
	    memclear(op) ;
	    if (startlen < UUNAMEREC_STARTLEN) {
	        startlen = UUNAMEREC_STARTLEN ;
	    }
	    if ((rs = uc_malloc(startlen,&vp)) >= 0) {
		op->rectab = intp(vp) ;
	        op->i = 1 ;
	        op->rectab[0] = 0 ;
	        op->e = startlen ;
	        op->c = 0 ;
	    } /* end if (memory-allocation) */
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (uunamerec_start) */

int uunamerec_add(uunamerec *op,int val) noex {
	int		rs = SR_FAULT ;
	if (op) {
	    rs = SR_NOTOPEN ;
	    if (op->i >= 0) {
/* do we need to extend the table? */
	        if ((op->i + 1) > op->e) {
	            rs = uunamerec_extend(op) ;
	        } /* end if */
	        if (rs >= 0) {
/* copy the new one in */
	            int		i = op->i ;
	            op->rectab[i] = val ;
	            op->i = i + 1 ;
	            op->c += 1 ;
	            rs = i ;
		}
	    } /* end if (valid) */
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (uunamerec_add) */

int uunamerec_already(uunamerec *op,int val) noex {
	int		i ; /* used-afterwards */

	if (op->i < 0)
	    return op->i ;

	for (i = 1 ; i < op->i ; i += 1) {

	    if (val == op->rectab[i])
	        break ;

	} /* end for */

	return (i < op->i) ? i : SR_NOTFOUND ;
}
/* end subroutine (uunamerec_already) */

int uunamerec_count(uunamerec *op) noex {
	if (op == NULL)
	    return SR_FAULT ;

	return op->c ;
}
/* end subroutine (uunamerec_count) */

int uunamerec_gettab(uunamerec *op,int **rpp) noex {
	int		sz ;


	if (op == NULL)
	    return SR_FAULT ;

	if (rpp != NULL)
	    *rpp = op->rectab ;

	sz = op->i * sizeof(uint) ;
	return sz ;
}
/* end subroutine (uunamerec_gettab) */

int uunamerec_indexlen(uunamerec *op) noex {
	int		n ;
	if (op == NULL)
	    return SR_FAULT ;

	n = nextpowtwo(op->i) ;

	return n ;
}
/* end subroutine (uunamerec_indexlen) */

int uunamerec_indexsize(uunamerec *op) noex {
	int		n ;
	int		sz ;

	if (op == NULL)
	    return SR_FAULT ;

	n = nextpowtwo(op->i) ;

	sz = n * 2 * sizeof(uint) ;
	return sz ;
}
/* end subroutine (uunamerec_indexlen) */

int uunamerec_mkindex(uunamerec *op,cchar *s,int it[][2],int itsize) noex {
	uint		rhash, hi ;
	int		rs ;
	int		n, sz ;
	cchar		*sp ;


	if (op == NULL)
	    return SR_FAULT ;

	if (s == NULL)
	    return SR_FAULT ;

	n = nextpowtwo(op->i) ;

	sz = n * 2 * sizeof(uint) ;
	if (sz > itsize)
	    return SR_TOOBIG ;

	memset(it,0,sz) ;

	for (int i = 1 ; i < op->i ; i += 1) {

	    sp = s + op->rectab[i] ;
	    rhash = hash_elf(sp,-1) ;

	    hi = hashindex(rhash,n) ;

	    if (it[hi][0] != 0) {
	        int	lhi ;

	        while (it[hi][1] != 0) {
	            hi = it[hi][1] ;
		}
	        lhi = hi ;
	        hi = hashindex((hi + 1),n) ;

	        while (it[hi][0] != 0) {
	            hi = hashindex((hi + 1),n) ;
		}
	        it[lhi][1] = hi ;

	    } /* end if (had a hash collison) */

	    it[hi][0] = i ;
	    it[hi][1] = 0 ;

	} /* end while (looping through records) */

	rs = SR_OK ;

	return (rs >= 0) ? n : rs ;
}
/* end subroutine (uunamerec_mkindex) */

int uunamerec_finish(uunamerec *op) noex {
	int		rs ;
	if (op == NULL)
	    return SR_FAULT ;

	if (op->rectab != NULL)
	    free(op->rectab) ;

	rs = op->i ;
	op->e = 0 ;
	op->i = 0 ;
	return rs ;
}
/* end subroutine (uunamerec_finish) */


/* private subroutines */

/* extend the => record table <= */
static int uunamerec_extend(uunamerec *op) noex {
	int		rs ;
	int		sz ;
	int		*nrt ;

#if	CF_FASTGROW
	op->e = (op->e * 2) ;
#else
	op->e = (op->e + UUNAMEREC_STARTLEN) ;
#endif /* CF_FASTGROW */

	sz = op->e * sizeof(uint) ;

#if	CF_UCMALLOC
	if ((rs = uc_realloc(op->rectab,sz,&nrt)) < 0) {

	    op->i = SR_NOMEM ;
	    return rs ;
	}
#else
	if ((nrt = (uint *) realloc(op->buf,sz)) == NULL) {

	    op->i = SR_NOMEM ;
	    return SR_NOMEM ;
	}
#endif /* CF_UCMALLOC */

	op->rectab = nrt ;
	return (op->e) ;
}
/* end subroutine (uunamerec_extend) */


