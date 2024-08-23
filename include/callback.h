/* callback HEADER */
/* lang=C99 */

/* time-out interface */
/* version %I% last-modified %G% */


/* revision history:

	= 2014-04-04, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 2014 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This file provides the definition of the CALLBACK object, and its
	method declarations.

*******************************************************************************/

#ifndef	CALLBACK_INCLUDE
#define	CALLBACK_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>


#define	CALLBACK	struct callback_entry


EXTERNC_begin

typedef int (*callback_f)(void *,int) noex ;

EXTERNC_end

struct callback_entry {
	void		*objp ;		/* object pointer */
	callback_f	metf ;		/* function method (C-linkage) */
	int		arg ;		/* function argument */
} ;

typedef CALLBACK	callback ;

EXTERNC_begin

extern int callback_load(callback *,void *,callback_f,int) noex ;

EXTERNC_end


#endif /* CALLBACK_INCLUDE */


