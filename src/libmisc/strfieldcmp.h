/* strfieldcmp HEADER */
/* lang=C20 */

/* string field comparisons */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	STRFIELDCMP_INCLUDE
#define	STRFIELDCMP_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>


EXTERNC_begin

extern int	strnkeycmp(cchar *,cchar *,int) noex ;
extern int	strnvaluecmp(cchar *,cchar *,int) noex ;

EXTERNC_end


#endif /* STRFIELDCMP_INCLUDE */


