/* ucprochave HEADER */
/* lang=C20 */

/* is a proceess (given by a PID) in the system? */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UCHAVEPEOC_INCLUDE
#define	UCHAVEPEOC_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>


EXTERNC_begin

extern int	uc_prochave(pid_t) noex ;

static inline int isproc(pid_t pid) noex {
	return uc_prochave(pid) ;
}

EXTERNC_end


#endif /* UCHAVEPEOC_INCLUDE */


