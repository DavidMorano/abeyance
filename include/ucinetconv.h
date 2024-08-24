/* uxinetconv HEADER */
/* lang=C20 */

/* UNIX® UCINETCONV support */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

	= 2017-08-01, David A­D­ Morano
	Updated for lack of interfaces in Apple-Darwin

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This file contains some support for the UNIX® UCINETCONV related
	operations.

*******************************************************************************/

#ifndef	UCINETCONV_INCLUDE
#define	UCINETCONV_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern int uc_inetnetpton(void *,int,int,cchar *) noex ;
extern int uc_inetpton(void *,int,cchar *) noex ;
extern int uc_inetntop(char *,int,int,cvoid *) noex ;

EXTERNC_end


#endif /* UCINETCONV_INCLUDE */


