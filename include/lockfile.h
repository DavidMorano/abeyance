/* lockfile HEADER */
/* lang=C20 */

/* sister subroutine to |uc_lockf(3uc)| */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	LOCKFILE_INCLUDE
#define	LOCKFILE_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>		/* |off_t| */
#include	<usystem.h>


EXTERNC_begin

extern int	lockfile(int,int,off_t,off_t,int) noex ;

EXTERNC_end


#endif /* LOCKFILE_INCLUDE */


