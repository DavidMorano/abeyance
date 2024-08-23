/* matkeystr HEADER */
/* lang=C20 */

/* match the key part of a string */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright (c) 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MATKEYSTR_INCLUDE
#define	MATKEYSTR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<localmisc.h>


EXTERNC_begin

extern int matkeystr(mainv,cchar *,int) noex ;

EXTERNC_end


#endif /* MATKEYSTR_INCLUDE */


