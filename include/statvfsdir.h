/* statvfsdir HEADER */
/* lang=C20 */

/* like |statvfs(2)| but will not return zero blocks on automounts */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-01, David A­D­ Morano
	The subroutine was written from scratch.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	STATVFSDIR_INCLUDE
#define	STATVFSDIR_INCLUDE


#include	<envstandards.h>
#include	<sys/types.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern int	statvfsdir(cchar *,STATVFS *) noex ;

EXTERNC_end


#endif /* STATVFSDIR_INCLUDE */


