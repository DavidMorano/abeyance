/* umask HEADER */
/* lang=C20 */

/* UNIX® information (a cache for 'uname(2)' and sisters) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UMASK_INCLUDE
#define	UMASK_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>


EXTERNC_begin

extern int umask_init() noex ;
extern int umask_fini() noex ;

extern int umaskset(mode_t) noex ;
extern int umaskget() noex ;

EXTERNC_end


#endif /* UMASK_INCLUDE */


