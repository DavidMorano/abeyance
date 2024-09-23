/* gettmpdname HEADER */
/* lang=C20 */

/* get the name of the TMPDIR (however one can get it) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETTMPDNAME_INCLUDE
#define	GETTMPDNAME_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>


EXTERNC_begin

extern cchar	*gettmpdnamex(cpccharp) noex ;

EXTERNC_end

#ifdef	__cplusplus

static inline cchar *gettmpdname(cpccharp envv = nullptr) noex {
	return gettmpdnamex(envv) ;
}

#else /* __cplusplus */

static inline cchar *gettmpdname(cpccharp envv) noex {
	return gettmpdnamex(envv) ;
}

#endif /* __cplusplus */


#endif /* GETTMPDNAME_INCLUDE */


