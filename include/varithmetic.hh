/* varithmetic HEADER */
/* lang=C++20 */

/* Vector-Arithmetic */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2017 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#ifndef	VARITHMETIC_INCLUDE
#define	VARITHMETIC_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>
#include	<stdintx.h>


typedef longlong	digit ;


constexpr int vcmpu(int n,digit *v1,digit *v2) noex {
	int		rc = 0 ;
	int		i{} ;
	for (i = (n-1) ; i >= 0 ; i -= 1) {
	   if (v1[i] != v2[i]) break ;
	}
	if (i > 0) {
	    rc = (v1[i] > v2[i]) ? 1 : -1 ;
	}
	return rc ;
}


#endif /* VARITHMETIC_INCLUDE */




