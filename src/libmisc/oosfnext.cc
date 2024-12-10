/* sfnext SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 */

/* find a sub-string within a larger string (given some criteria) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Names:
	sfnext
	sfnextchr
	sfnextbrk

	Philosophy:
	An explicit terminator (given) is *optional* in order for
	a non-empty result string to be returned.  A new-line (NL)
	character and white-space are always implied terminators
	(this is historic).


	Name:
	sfnext

	Description:
	This subroutine will extract the next white-space-separated
	field from the input buffer.  If an NL is encountered, it
	is treated like a delimiter and all characters before it
	(including zero characters) are returned as the delimited
	field.  The caller should test for zero characters being
	returned.  This condition could indicate either that the
	line has no additional characters, or that a NL was
	encountered.  If the caller determines that there are
	characters left in the line but that zero was returned, a
	check by the caller for a NL character is indicated.  If
	the caller determines that a NL was present, the caller
	should arrange to "step over" the NL before making new calls
	in order to get the fields beyond the NL.
	The returned string is white-space shrunken.

	Synopsis:
	int sfnext(cchar *sp,int sl,cchar **spp) noex

	Arguments:
	sp		pointer to start of user supplied buffer
	sl		length of user supplied buffer
	spp		pointer to pointer of the found field

	Returns:
	>0		length of found field
	==0		no field found or a NL character was encountered


	Name:
	sfnextbrk

	Description:
	This subroutine will extract the next white-space-separated
	or a combination of white-space and a trailing termination
	character c-string from a counted source c-string.
	The returned string is white-space shrunken.

	Synopsis:
	int sfnextbrk(cchar *sp,int sl,cchar *terms,cchar **spp) noex

	Arguments:
	sp		pointer to start of user supplied buffer
	sl		length of user supplied buffer
	terms		terminator characters (in a c-string)
	spp		pointer to pointer of the found field

	Returns:
	>0		length of found field
	==0		no field found or a NL character was encountered

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<cstring>		/* <- for |strchr(3c)| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<char.h>
#include	<mkchar.h>

#include	"sfx.h"


/* local defines */


/* external subroutines */


/* external variables */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int sfnext(cchar *sp,int sl,cchar **spp) noex {
	int		rl = 0 ;
	if (sp && spp) {
	    while (sl && CHAR_ISWHITE(*sp)) {
	        sp += 1 ;
	        sl -= 1 ;
	    } /* end while */
	    *spp = sp ;
	    while (sl && *sp) {
		cint	ch = mkchar(*sp) ;
		bool	f = false ;
		f = f || (ch == '\n') ;
		f = f || CHAR_ISWHITE(ch) ;
		if (f) break ;
	        sp += 1 ;
	        sl -= 1 ;
	    } /* end while */
	    rl = (sp - (*spp)) ;
	} /* end if (non-null) */
	return rl ;
}
/* end subroutine (sfnext) */

int sfnextchr(cchar *sp,int sl,int sch,cchar **spp) noex {
	int		rl = 0 ;
	if (sp && spp) {
	    while (sl && CHAR_ISWHITE(*sp)) {
	        sp += 1 ;
	        sl -= 1 ;
	    } /* end while */
	    *spp = sp ;
	    while (sl && *sp) {
	        cint	ch = mkchar(*sp) ;
		bool	f = false ;
	        f = f || (ch == '\n') ;
	        f = f || CHAR_ISWHITE(ch) ;
	        f = f || (ch == sch) ;
		if (f) break ;
	        sp += 1 ;
	        sl -= 1 ;
	    } /* end while */
	    rl = (sp - (*spp)) ;
	} /* end if (non-null) */
	return rl ;
}
/* end subroutine (sfnextchr) */

int sfnextbrk(cchar *sp,int sl,cchar *terms,cchar **spp) noex {
	int		rl = 0 ;
	if (sp && terms && spp) {
	    while (sl && CHAR_ISWHITE(*sp)) {
	        sp += 1 ;
	        sl -= 1 ;
	    } /* end while */
	    *spp = sp ;
	    while (sl && *sp) {
	        cint	ch = mkchar(*sp) ;
		bool	f = false ;
	        f = f || (ch == '\n') ;
	        f = f || CHAR_ISWHITE(ch) ;
		f = f || (strchr(terms,ch) != nullptr) ;
		if (f) break ;
	        sp += 1 ;
	        sl -= 1 ;
	    } /* end while */
	    rl = (sp - (*spp)) ;
	} /* end if (non-null) */
	return rl ;
}
/* end subroutine (sfnextbrk) */


