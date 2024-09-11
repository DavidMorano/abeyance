/* termcharset HEADER */
/* lang=C20 */

/* terminal-character-setter */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	TERMCHARSET_INCLUDE
#define	TERMCHARSET_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


EXTERNC_begin

extern int termcharset(char *,int,int,int,cchar *) noex ;

EXTERNC_end


#endif /* TERMCHARSET_INCLUDE */


