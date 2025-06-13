/* getenv3 SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* get the value of an environment variable */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This subroutine was written from scratch.  There are (or
	may) be some other standard ones floating around like it
	but I could not find one that was exactly what I needed
	(sigh).

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	getenv3

	Description:
	This subroutine is like |getenv(3c)}| except that it also
	takes an argument that specifies the length of the environment
	variable string to look up in the environment array.  This
	subroutine also returns a pointer to the entire string (key
	and value pair) as it is found (if found) in the environment
	array.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/types.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<localmisc.h>

#include	"getenv3.h"


/* local defines */


/* external subroutines */


/* external variables */

extern mainv	environ ;


/* local variables */


/* exported variables */


/* exported subroutines */

const char *getenv3(cchar *name,int namelen,cchar **epp) noex {
	cchar		*rp = nullptr ;
	if (environ && name) {
	    int		len ;
	    cchar	*sp ;
	    cchar	*cp ;
	    if (namelen < 0) namelen = strlen(name) ;
	    for (sp = name ; 
	        (sp < (name + namelen)) && *sp && (*sp != '=') ; sp += 1) ;
    
	    len = (sp - name) ;
	    for (mainv p = environ ; *p ; p += 1) {
		int	i ;
		sp = name ;
	        cp = *p ;
	        for (i = len ; i && *cp ; i -= 1) {
	            if (*cp++ != *sp++) break ;
	        }
	        if ((i == 0) && (*cp++ == '=')) {
	            if (epp) *epp = *p ;
		    rp = cp ;
		    break ;
	        } /* end if */
	    } /* end for */
	} /* end if (non-null) */
	return rp ;
}
/* end subroutine (getenv3) */


