/* dirs HEADER */
/* lang=C20 */

/* make a series of possibly hierarchical directories */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright (c) 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	DIRS_INCLUDE
#define	DIRS_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>

#include	<mkdirs.h>
#include	<rmdirs.h>


EXTERNC_begin

extern int dirempty(cchar *) noex ;

EXTERNC_end


#endif /* DIRS_INCLUDE */


