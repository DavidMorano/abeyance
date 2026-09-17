/* minmax SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* minimum and maximum */
/* version %I% last-modified %G% */

#define	CF_STRENGTH	0		/* use strength reduction */

/* revision history:

	= 1998-07-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Names:
	min
	max

	Description:
	These subroutines calculate the minimum or the maximum
	(respectively) of two (integer) values.

	Synopsis:
	int min(int a,int b) noex
	int max(int a,int b) noex

	Arguments:
	a		value-1
	b		value-2

	Returns:
	-		the minimum of the two values
	-		the maximum of the two values

*******************************************************************************/

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<climits>		/* CSTD |CHAR_BIT| */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<utypedefs.h>		/* LIBU */
#include	<utypealiases.h>	/* LIBU */
#include	<usysdefs.h>		/* LIBU */
#include	<usysrets.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */


/* local defines */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

#if	CF_STRENGTH

template<typename T> T minx(int a,int b) noex {
	const T		sbit = ((szof(T) * CHAR_BIT) - 1) ;
	const T		d = (a - b) ;
	const T		sel = (! (((a - b) >> sbit) & 1)) ;
	return (a - (sel * d)) ;
} /* end */

int mini(int a,int b) noex {
    	return minx(a,b) ;
} /* end */

long minl(long a,long b) noex {
    	return minx(a,b) ;
} /* end */

longlong minl(longlong a,longlong b) noex {
    	return minx(a,b) ;
} /* end */

typedef<typename T> T maxx(T a,T b) noex {
	const T		sbit = ((szof(T) * CHAR_BIT) - 1) ;
	const T		d = (a - b) ;
	const T		sel = (((a - b) >> sbit) & 1) ;
	return (a - (sel * d)) ;
} /* end */

int maxi(int a,int b) noex {
    	return maxx(a,b) ;
} /* end */

long maxl(long a,long b) noex {
    	return maxx(a,b) ;
} /* end */

longlong maxl(longlong a,longlong b) noex {
    	return maxx(a,b) ;
}

#else /* CF_STRENGTH */

template<typename T> T minx(T a,T b) noex {
	T	v = a ;
	if (b < v) v = b ;
	return v ;
} /* end subroutine (minx) */

int mini(int a,int b) noex {
    	return minx(a,b) ;
} /* end */

long minl(long a,long b) noex {
    	return minx(a,b) ;
} /* end */

longlong minl(longlong a,longlong b) noex {
    	return minx(a,b) ;
} /* end */


template<typename T> T maxx(T a,T b) noex {
	int	v = a ;
	if (b > v) v = b ;
	return v ;
} /* end */
/* end subroutine (maxx) */

int maxi(int a,int b) noex {
    	return maxx(a,b) ;
} /* end */

long maxl(long a,long b) noex {
    	return maxx(a,b) ;
} /* end */

longlong maxl(longlong a,longlong b) noex {
    	return maxx(a,b) ;
} /* end */


#endif /* CF_STRENGTH */


