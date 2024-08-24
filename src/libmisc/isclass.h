/* isclass HEADER */
/* lang=C20 */

/* character classes for mail content purposes */
/* version %I% last-modified %G% */


/* revision history:

	= 1996-03-01, David A­D­ Morano
        The subroutine set was written from scratch to do what the previous
        program by the same name did.

*/

/* Copyright © 1996 David A­D­ Morano.  All rights reserved. */

/******************************************************************************

	Name:
	isclass

	Description:
        These subroutines check a character to see if it is part of a special
        character class.  See the code for details!

******************************************************************************/

#ifndef	ISCLASS_INCLUDE
#define	ISCLASS_INCLUDE	


#include	<envstandards.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern int is7bit(int) noex ;
extern int is8bit(int) noex ;
extern int isbinary(int) noex ;

EXTERNC_end


#endif /* ISCLASS_INCLUDE */



