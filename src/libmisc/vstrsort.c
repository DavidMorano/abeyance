/* vstrsort SUPPORT */
/* lang=C20 */

/* an insertion sort? on strings */
/* version %I% last-modified %G% */


/*******************************************************************
*                                                                  *
*             This software is part of the ast package             *
*                Copyright (c) 1985-2002 AT&T Corp.                *
*        and it may only be used by you under license from         *
*                       AT&T Corp. ("AT&T")                        *
*         A copy of the Source Code Agreement is available         *
*                at the AT&T Internet web site URL                 *
*                                                                  *
*       http://www.research.att.com/sw/license/ast-open.html       *
*                                                                  *
*    If you have copied or used this software without agreeing     *
*        to the terms of the license you are infringing on         *
*           the license and copyright and are violating            *
*               AT&T's intellectual property rights.               *
*                                                                  *
*            Information and Software Systems Research             *
*                        AT&T Labs Research                        *
*                         Florham Park NJ                          *
*                                                                  *
*               Glenn Fowler <gsf@research.att.com>                *
*                David Korn <dgk@research.att.com>                 *
*                 Phong Vo <kpv@research.att.com>                  *
*                                                                  *
*******************************************************************/

/*
 *  vstrsort -- heap sort an array of pointers using fn
 *
 *	fn follows vstrcmp(3) conventions
 *
 *   David Korn
 *   AT&T Bell Laboratories
 *
 *  derived from Bourne Shell
 */


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<localmisc.h>


/* local typedefs */

extern "C" {
    typedef int (*vcmp_f)(cchar **,cchar **) noex ;
}


/* local variables */


/* exported variables */


/* exported subroutines */

void vstrsort(cchar **argv,int n,vcmp_f fn) noex {
	int 		i ;
	int 		j ;
	int 		m ;
	int		c ;
	int 		k ;
	char**		ap ;
	char*		s ;

/* compute value for 'j' */

	for (j = 1 ; j <= n ; j *= 2) ;

/* do it */

	for (m = 2 * j - 1 ; m /= 2 ; /* CSTYLED */ ) {
	    for ((j = 0, k = n - m) ; j < k ; j += 1) {
	        for (i = j ; i >= 0 ; i -= m) {
	            ap = &argv[i] ;
	            c = (*fn)((cchar **) &ap[m],(cchar **) &ap[0]) ;
		    if (c >= 0) break ;
	            s = ap[m] ;
	            ap[m] = ap[0] ;
	            ap[0] = s ;
	        } /* end for */
	    } /* end for */
	} /* end for */

/* VOIDRETURN */

}
/* end subroutine (vstrsort) */


