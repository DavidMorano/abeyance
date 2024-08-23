/* mkquoted HEADER */
/* lang=C20 */

/* Make-a-Quoted c-string (from a source c-string) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright (c) 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MKQUOTED_INCLUDE
#define	MKQUOTED_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern int mkquoted(char *,int,cchar *,int) noex ;

EXTERNC_end


#endif /* MKQUOTED_INCLUDE */


