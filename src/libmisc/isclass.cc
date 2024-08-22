/* isclass SUPPORT */
/* lang=C++20 */

/* is a character one of a certain character class? */
/* version %I% last-modified %G% */


/* revision history:

	= 1996-03-01, David A­D­ Morano
	The subroutine set was written from scratch to do what the
	previous program by the same name did.

*/

/* Copyright © 1996 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

        These subroutines check a character to see if it is part of a special
        character class.  See the code for details!

*******************************************************************************/

#include	<envstandards.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstring>		/* |is{x}(3c)| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<ischarx.h>
#include	<localmisc.h>

#include	"isclass.h"


/* local defines */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* exported variables */


/* exported subroutines */

/* is it 7-bit text (no controls or other weirdo) */
int is7bit(int c) noex {
	int		f = FALSE ;
	if ((c >= 0) && (c < 0x100)) {
	    f = isprintlatin(c) ;
	}
	return f ;
}
/* end subroutine (is7bit) */

/* is it 8-bit text (no controls or other weirdo) */
int is8bit(int c) noex {
	return ((c & 0x80) && ((c & (~ 31)) != 0x80)) ;
}
/* end subroutine (is8bit) */

int isbinary(int c) noex {
	int		f = FALSE ;
	if (! iswhite(c)) {
	    f = (((c & (~ 31)) == 0x00) || ((c & (~ 31)) == 0x80)) ;
	}
	return f ;
}
/* end subroutine (isbinary) */


