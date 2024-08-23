/* uctimer HEADER */
/* lang=C20 */

/* interface component for UNIX® library-3c */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UCTIMER_INCLUDE
#define	UCTIMER_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<signal.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>


EXTERNC_begin

extern int uc_timercreate(clockid_t,SIGEVENT *,timer_t *) noex ;
extern int uc_timerdestroy(timer_t) noex ;
extern int uc_timerset(timer_t,int,CITIMERSPEC *,ITIMERSPEC *) noex ;
extern int uc_timerget(timer_t,ITIMERSPEC *) noex ;
extern int uc_timerover(timer_t) noex ;

EXTERNC_end


#endif /* UCTIMER_INCLUDE */


