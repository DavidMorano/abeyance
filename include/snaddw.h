/* snaddw HEADER */
/* lang=C20 */

/* append a counted c-string to existing counted c-string */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/******************************************************************************

	This subroutine adds a c-string to the end of an existing
	string.  Return the incremental amount added.

******************************************************************************/

#ifndef	SNADDW_INCLUDE
#define	SNADDW_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern int snaddw(char *,int,int,cchar *,int) noex ;

EXTERNC_end

#ifdef	__cplusplus

static inline int snaddw(char *dbuf,int dlen,int dl,cchar *sp) noex {
	return snaddw(dbuf,dlen,dl,sp,-1) ;
}

#endif /* __cplusplus */


#endif /* SNADDW_INCLUDE */


