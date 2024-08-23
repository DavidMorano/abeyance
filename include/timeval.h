/* timeval HEADER */
/* lang=C20 */

/* time-value object methods */
/* version %I% last-modified %G% */


/* Copyright © 1998,2014 David A­D­ Morano.  All rights reserved. */

#ifndef	TIMEVAL_INCLUDE
#define	TIMEVAL_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/time.h>		/* |TIMEVAL| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern int timeval_load(TIMEVAL *,time_t,int) noex ;
extern int timeval_add(TIMEVAL *,CTIMEVAL *,CTIMEVAL *) noex ;
extern int timeval_sub(TIMEVAL *,CTIMEVAL *,CTIMEVAL *) noex ;

EXTERNC_end

#ifdef	__cplusplus

struct timeval_t : timeval {
	timeval_t &operator += (int v) noex {
	    tv_sec += v ;
	    return *this ;
	} ;
	timeval_t(time_t s,int us) noex {
	    tv_sec = s ;
	    tv_usec = us ;
	} ;
	timeval_t &operator += (const timeval_t &) noex ;
	timeval_t &operator -= (const timeval_t &) noex ;
} ;

timeval operator + (const timeval &,const timeval &) noex ;
timeval operator - (const timeval &,const timeval &) noex ;

#endif /* __cplusplus */


#endif /* TIMEVAL_INCLUDE */


