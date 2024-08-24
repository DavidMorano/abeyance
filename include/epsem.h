/* psem HEADER */
/* lang=C20 */

/* POSIX© unnamed Semaphore (PSEM) */
/* version %I% last-modified %G% */


/* revision history:

	= 1999-07-28, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1999 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	These are "unnamed" POSIX® semaphores.

	This module implements an emulated POSIX® semaphore.  I have
	to write a look-alike implementation of POSIX semaphores
	myself because the Apple Darwin implemention does not allow
	for the un-named semaphore use case!  Yes, once and (and again,
	and again) the Apple Darwin UNIX-like implementation sucks
	cock meat. F*ck Apple Darwin.

*******************************************************************************/

#ifndef	PSEM_INCLUDE
#define	PSEM_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>
#include	<csem.h>		/* <- couting semaphore (DAM) */


#define	PSEM		csem		/* <- the "money" shot */


#ifndef	TYPEDEF_PSEM
#define	TYPEDEF_PSEM
typedef PSEM		psem ;
#endif

EXTERNC_begin

extern int	psem_create(psem *,int,int) noex ;
extern int	psem_destroy(psem *) noex ;
extern int	psem_wait(psem *) noex ;
extern int	psem_waiter(psem *,int) noex ;
extern int	psem_trywait(psem *) noex ;
extern int	psem_post(psem *) noex ;

EXTERNC_end


#endif /* PSEM_INCLUDE */


