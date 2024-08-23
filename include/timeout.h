/* timeout HEADER */
/* lang=C99 */

/* time-out interface */
/* version %I% last-modified %G% */


/* revision history:

	= 2014-04-04, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 2014 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This file provides the definition of the TIMEOUT object, and its
	method declarations.

*******************************************************************************/

#ifndef	TIMEOUT_INCLUDE
#define	TIMEOUT_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<time.h>		/* |time_t| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


#define	TIMEOUT		struct timeout_entry


EXTERNC_begin

typedef int (*timeout_f)(void *,uint,int) noex ;

EXTERNC_end

enum timeoutcmds {
	timeoutcmd_set,
	timeoutcmd_cancel,
	timeoutcmd_overlast
} ;

struct timeout_entry {
	timeout_f	metf ;		/* method function (C-linkage) */
	void		*objp ;		/* object pointer */
	time_t		val ;
	uint		tag ;
	int		arg ;
	int		id ;		/* created by the system */
} ;

typedef TIMEOUT		timeout ;

EXTERNC_begin

extern int timeout_load(timeout *,time_t,void *,timeout_f,uint,int) noex ;

extern int uc_timeout(int,timeout *) noex ;

EXTERNC_end


#endif /* TIMEOUT_INCLUDE */


