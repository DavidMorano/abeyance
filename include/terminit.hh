/* terminit HEADER */
/* lang=C20 */

/* terminator character initialization */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-05-01, David A­D­ Morano
	This code module was originally written in VAX assembly
	(back around 1980 or so).  It was then written into C-language
	perhaps around 1983 (at AT&T Bell Laboratories).  This
	(below) is a new incarnation based on that older C-language
	code.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This is a classic, ported forward from the old VAX-11/780
	days.  This was translated from VAX assembly language.

*******************************************************************************/

#ifndef	TERMINIT_INCLUDE
#define	TERMINIT_INCLUDE
#ifdef	__cplusplus


#include	<envstandards.h>	/* ordered first to configure */
#include	<climits>		/* |UCHAR_MAX| | |CHAR_BIT| */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<baops.h>


namespace {
    constexpr int	termsize = ((UCHAR_MAX+1)/CHAR_BIT) ;
    struct terminit {
	char		terms[termsize] = {} ;
	constexpr terminit(cchar *s) noex {
	    while (*s) {
		cint	ch = int(*s++ & UCHAR_MAX) ;
		baset(terms,ch) ;
	    }
	} ;
    } ; /* end struct (terminit) */
}


#endif /* __cplusplus */
#endif /* TERMINIT_INCLUDE */


