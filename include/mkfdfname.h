/* mkfdfname HEADER */
/* lang=C20 */

/* make an "fd" filename */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MKFDFNAME_INCLUDE
#define	MKFDFNAME_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


EXTERNC_begin

extern int mkfdfname(char *,int,int) noex ;

EXTERNC_end


#endif /* MKFDFNAME_INCLUDE */


