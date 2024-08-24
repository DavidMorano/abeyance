/* strtox HEADER */
/* lang=C20 */

/* numeric-character conversion */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	STRTOX_INCLUDE
#define	STRTOX_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<stdintx.h>
#include	<usysrets.h>


EXTERNC_begin

extern longlong		strtoxll(cchar *,char **,int) noex ;
extern ulonglong	strtoxull(cchar *,char **,int) noex ;

#ifdef	COMMENT
extern intmax		strtoxim(cchar *,char **,int) noex ;
extern uintmax		strtoxuim(cchar *,char **,int) noex ;
#endif /* COMMENT */

EXTERNC_end


#endif /* STRTOX_INCLUDE */


