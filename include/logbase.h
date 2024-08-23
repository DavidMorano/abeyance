/* logbase HEADER */
/* lang=C20 */

/* Integer-Remaider */
/* version %I% last-modified %G% */


/* revision history:

	= 2003-03-04, David A.D. Morano
	This was written from scratch.

*/

/* Copyright © 2003 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Names:
	logbasef
	logbase
	logbasel

	Description:
	Find the log-base-(b) of a number (v).

	Synopsis:
	float		logbase(float b,float v) noex
	double		logbase(double b,double v) noex
	long double	logbase(long double b,long double v) noex

	Arguments:
	b		base
	v		number to take the log-base-(b) of

	Returns:
	-		result

*******************************************************************************/

#ifndef	LOGBASE_INCLUDE
#define	LOGBASE_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern float		logbasef(float,float) noex ;
extern double		logbase(double,double) noex ;
extern long double	logbasel(long double,long double) noex ;

EXTERNC_end

#ifdef	__cplusplus

static inline float		logbase(float b,float v) noex {
	return logbasef(b,v) ;
}
static inline long double	logbase(long double b,long double v) noex {
	return logbasel(b,v) ;
}

#endif /* __cplusplus */


#endif /* LOGBASE_INCLUDE */


