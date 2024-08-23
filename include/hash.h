/* hash HEADER */
/* lang=C20 */

/* determine if file-name (just a string) has an approved file-extension */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	HASH_INCLUDE
#define	HASH_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>		/* <- is this really needed? */
#include	<utypedefs.h>
#include	<clanguage.h>


EXTERNC_begin

extern uint hash_again(uint,int,int) noex ;
extern uint hash_elf(cchar *,int) noex ;
extern uint hash_hsieh(cchar *,int) noex ;

EXTERNC_end


#endif /* HASH_INCLUDE */


