/* strdfill SUPPORT */

/* concatenate strings for target insertion */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was originally written.

	= 1999-12-03, David A­D­ Morano
	This was updated to use 'strlcpy(3c)' when it was rumored to be coming
	as new standard.  We are currently using our own implementation of
	that, but when it is supported by vendors this will all seemlessly
	transistion to using the vendor version.

	= 2011-12-09, David A­D­ Morano
	I got rid of the 'strlcpy(3c)' usage.  It was never really needed
	anyway.  The code is certainly cleaner without it.  And I don't really
	think it is a whole lot slower either since the various string lengths
	are usually fairly small.  Other subroutines have gotten rid of
	'strlcpy(3c)' also without any complaints.

*/

/* Copyright © 1998,1999,2011 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	strdfill{n}

	Description:
	This subroutine constructs a single string from one or more
	specificed strings and inserts it into the destination (not
	NUL-terminated).

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<climits>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdarg>
#include	<cstring>
#include	<usystem.h>

#include	"strdfill.h"


/* local defines */


/* external subroutines */


/* external variables */


/* local strutures */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

char *strdfillx(char *dp,int dl,int n,...) noex {
	if (dp) {
	    va_list	ap ;
	    va_begin(ap,n) ;
	    if (dl < 0) dl = INT_MAX ;
	    for (int i = 0 ; (dl > 0) && (i < n) ; i += 1) {
	        cchar	*sp = (cchar *) va_arg(ap,char *) ;
	        while ((dl > 0) && (sp[0] != '\0')) {
		    *dp++ = *sp++ ;
		    dl -= 1 ;
	        } /* end while */
	    } /* end for */
	    va_end(ap) ;
	} /* end if (non-null) */
	return dp ;
}
/* end subroutine (strdfillx) */

char *strdfill1(char *bp,int bl,cchar *s1) noex {
	return strdfillx(bp,bl,1,s1) ;
}
/* end subroutine (strdfill1) */

char *strdfill2(char *bp,int bl,cchar *s1,cchar *s2) noex {
	return strdfillx(bp,bl,2,s1,s2) ;
}
/* end subroutine (strdfill2) */

char *strdfill3(char *bp,int bl,cchar *s1,cchar *s2,cchar *s3) noex {
	return strdfillx(bp,bl,3,s1,s2,s3) ;
}
/* end subroutine (strdfill3) */

char *strdfill4(char *bp,int bl,cchar *s1,cchar *s2,cchar *s3,cchar *s4) noex {
	return strdfillx(bp,bl,4,s1,s2,s3,s4) ;
}
/* end subroutine (strdfill4) */

char *strdfill5(char *bp,int bl,cc *s1,cc *s2,cc *s3,cc *s4,cc *s5) noex {
	return strdfillx(bp,bl,5,s1,s2,s3,s4,s5) ;
}
/* end subroutine (strdfill5) */


