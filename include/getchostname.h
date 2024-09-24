/* getchostname HEADER */
/* lang=C20 */

/* get a cannical host-name */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETCHOSTNAME_INCLUDE
#define	GETCHOSTNAME_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


EXTERNC_begin

extern int getchostname(char *,cchar *) noex ;

static inline int getcname(char *cbuf,cchar *name) noex {
	return getchostname(cbuf,name) ;
}

EXTERNC_end


#endif /* GETCHOSTNAME_INCLUDE */


