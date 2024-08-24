/* termtypemat HEADER */
/* lang=C20 */

/* match on a terminal-type */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-07-19, David A­D­ Morano
	Originally written for Rightcore Network Services.

	= 2017-12-16, David A­D­ Morano
	Updated.

*/

/* Copyright © 2000,2017 David A­D­ Morano.  All rights reserved. */

#ifndef	TERMTYPEMAT_INCLUDE
#define	TERMTYPEMAT_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<localmisc.h>


#define	TERMTYPE	struct termtype_head


struct termtype_head {
	cchar		*name ;
	short		pv[4] ;
	short		sv[4] ;
} ;

typedef	TERMTYPE	termtype ;

EXTERNC_begin

extern int	termtypemat(const termtype *,cshort *,cshort *) noex ;

EXTERNC_end


#endif /* TERMTYPEMAT_INCLUDE */


