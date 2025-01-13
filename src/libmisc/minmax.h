/* minmax HEADER */
/* encoding=ISO8859-1 */
/* lang=C20 (conformance reviewed) */

/* Minimum-Maximun */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-07-01, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MINMAX_INCLUDE
#define	MINMAX_INCLUDE


#include	<envstandards.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


EXTERNC_begin

extern int	mini(int a,int b) noex ;
extern long	lmin(long a,long b) noex ;
extern longlong	llmin(longlong a,longlong b) noex ;

extern int	maxi(int a,int b) noex ;
extern long	lmax(long a,long b) noex ;
extern longlong	llmax(longlong a,longlong b) noex ;

EXTERNC_end

#ifdef	__cplusplus

tempate<typename T> T min(T,T) noex {
    	return SR_NOSYS ;
}
tempate<> int min(int a,int b) noex {
    	return mini(a,b) ;
}
tempate<> long min(long a,long b) noex {
    	return minl(a,b) ;
}
tempate<> longlong min(longlong a,longlong b) noex {
    	return minll(a,b) ;
}

tempate<typename T> T max(T,T) noex {
    	return SR_NOSYS ;
}
tempate<> int max(int a,int b) noex {
    	return maxi(a,b) ;
}
tempate<> long max(long a,long b) noex {
    	return maxl(a,b) ;
}
tempate<> longlong max(longlong a,longlong b) noex {
    	return maxll(a,b) ;
}


#endif /* __cplusplus */


#endif /* MINMAX_INCLUDE */


