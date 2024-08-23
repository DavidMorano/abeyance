/* snwcpy HEADER */
/* lang=C20 */

/* copy a c-string to a sized destination buffer */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	SNWCPY_INCLUDE
#define	SNWCPY_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<snwcpyx.h>


EXTERNC_begin

extern int	snwcpy(char *,int,cchar *,int) noex ;

EXTERNC_end

#ifdef	__cplusplus

inline int snwcpy(char *dbuf,int dlen,cchar *sp) noex {
	return snwcpy(dbuf,dlen,sp,-1) ;
}

#endif /* __cplusplus */


#endif /* SNWCPY_INCLUDE */


