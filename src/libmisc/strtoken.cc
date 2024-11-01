/* strtoken SUPPORT (deprecated) */
/* encoding=ISO8859-1 */
/* lang=C++20 */

/* break a string out into tokens */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-08-10, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Name:
	strtoken (this subroutine is deprecated)

	Description:
	This routine returns a pointer within the given string to
	the start of the next tokenized substring.  This routine
	is similar to the standard UNIX 'strtok' routine except
	that this one takes additional arguments so that the
	subroutine can be reentrant.

	Synopsis:
	char *strtoken(char *s,cchar *ts,int *lp) noex

	Arguments:
	s	input string to break into tokens (same as UNIX version
		except that this can never be NULL)
	ts	string containing token characters (same as UNIX version)
	lp	pointer to an integer for the subroutine to maintain state

	Returns:
	-	pointer to the token string just tokenized!

	Notes:
	This subroutine is deprecated.  This subroutine was used
	in the (very) old PCS READMAIL program.  I did not write
	that and it is probably unknown who did write it.  But it
	was a (bad) mistake then and it would be a mistake if it
	was ever used in any other code.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<localmisc.h>


/* local defines */


/* local namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

char *strtoken(char *s,cchar *ts,int *lp) noex {
	char		*rp = nullptr ;
	if (s && lp) {
	    if (s[*lp]) {
	        int	si = *lp ;
	        while (s[*lp]) {
	            cchar 	*tp = ts ;
	            while (*tp) {
		        if (s[*lp] == *tp++) {
	                    s[*lp] = '\0' ;
	                    break ;
	                } /* end if */
	            } /* end while */
	            (*lp) += 1 ;
	        } /* end while */
	        rp = (s + si) ;
	    } /* end if (non-null) */
	} /* end if (non-null) */
	return rp ;
}
/* end subroutine (strtoken) */


