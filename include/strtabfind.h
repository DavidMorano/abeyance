/* strtabfind HEADER */
/* lang=C20 */

/* find a string in a STRTAB object index table */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	STRTABFIND_INCLUDE
#define	STRTABFIND_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern int strtabfind(cc *,int (*)[3],int,int,cc *,int) noex ;

EXTERNC_end


#endif /* STRTABFIND_INCLUDE */


