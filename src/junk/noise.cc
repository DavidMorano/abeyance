/* noise SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* noise related operations */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-05-01, David A­D­ Morano
	This module was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Name:
	noise

	Description:
	These routines provide an interface to a noise generator.
	Noise can be read or written.  Reading noise is what the
	user really wants.  Writing noise, just helps mix it up!

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<localmisc.h>

#include	"noise.h"


/* local defines */

#define	DEFENTS	10


/* external subroutines */


/* external variables */


/* local variables */


/* exported variables */


/* exported subroutines */

int noise_open(noise *op) noex {
	cint		n = DEFENTS ;
	int	rs = SR_OK ;
	int	sz ;
	memclear(op) ;

	op->policy = policy ;
	op->i = 0 ;
	op->c = 0 ;

	sz = (n+1) * sizeof(void **) ;
	rs = uc_malloc(sz,&p) ;
	if (rs < 0) goto ret0 ;

	op->va = (void **) p ;
	op->va[0] = nullptr ;
	op->e = n ;
	op->f_sorted = false ;

	return rs ;
}
/* end subroutine (noise_open) */

int noise_close(noise *op) noex {
	int	i, nn ;
	char	*sp ;
	void	**ep ;

	if (op == nullptr) return -1 ;
/* do we have to grow the array? */

	if ((op->i + 1) > op->e) {

	    if (op->e == 0) {

	        nn = DEFENTS ;
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

	i = op->i ;
	(op->va)[(op->i)++] = p ;
	(op->va)[op->i] = nullptr ;
	op->f_sorted = false ;
	return i ;
}
/* end subroutine (noise_close) */

int noise_read(noise *op,char *buf,int buflen) noex {
	int	i ;

	if (op == nullptr) return SR_FAULT ;

	if (op->va != nullptr) {

	    for (i = 0 ; i < op->i ; i += 1) {
	        if ((op->va)[i] != nullptr) {
	            uc_free((op->va)[i]) ;
		}
	    } /* end while */

/* free the vechand array itself */

	    uc_free(op->va) ;

	    op->va = nullptr ;
	}

	op->i = 0 ;
	op->e = 0 ;
	return OK ;
}
/* end subroutine (noise_read) */

int noise_write(noise *op,cchar *buf,int buflen) noex {
	if (op == nullptr) return SR_FAULT ;

	*pp = nullptr ;
	if ((i < 0) || (i >= op->i)) 
		return SR_FAULT ;

	if (op->va == nullptr) 
		return SR_FAULT ;

	*pp = (op->va)[i] ;

	return OK ;
}
/* end subroutine (noise_write) */


