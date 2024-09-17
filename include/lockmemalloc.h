/* lockmemalloc HEADER */
/* lang=C20 */

/* memory allocation facility w/ locking */
/* version %I% last-modified %G% */


/* revision history:

	= 2015-04-06, David A­D­ Morano
	Written to have a place for the various KSH initialization subroutines.

*/

/* Copyright © 2015 David A­D­ Morano.  All rights reserved. */

#ifndef	LOCKMEMALLOC_INCLUDE
#define	LOCKMEMALLOC_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


enum lockmemallocsets {
    lockmemallocset_end,
    lockmemallocset_begin,
    lockmemallocset_overlast
} ;


EXTERNC_begin

extern int	lockmemalloc_set(int) noex ;

EXTERNC_end


#endif /* LOCKMEMALLOC_INCLUDE */


