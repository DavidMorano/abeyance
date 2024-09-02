/* ucmallox HEADER */
/* lang=C20 */

/* interface component for UNIX® library-3c */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-85, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	The following subroutines are made available:

	uc_mallocsys
	uc_mallocbuf
	uc_mallocstrw

*******************************************************************************/

#ifndef	UCMALLOX_INCLUDE
#define	UCMALLOX_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>


EXTERNC_begin

extern int uc_mallocsys(int,char **) noex ;
extern int uc_mallocbuf(cvoid *,int,cvoid **) noex ;
extern int uc_mallocstrw(cchar *,int,cchar **) noex ;

EXTERNC_end


#endif /* UCMALLOX_INCLUDE */


