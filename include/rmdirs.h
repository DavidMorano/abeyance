/* rmdirs HEADER */
/* lang=C20 */

/* make a series of possibly hierarchical directories */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	RMDIRS_INCLUDE
#define	RMDIRS_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


EXTERNC_begin

extern int removes(cchar *) noex ;
extern int rmdirfiles(cchar *,cchar *,int) noex ;

static inline int rmdirs(cchar *dn) noex {
	return removes(dn) ;
}

EXTERNC_end


#endif /* RMDIRS_INCLUDE */


