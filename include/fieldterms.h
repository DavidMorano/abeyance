/* fieldterms HEADER */
/* lang=C20 */

/* manage field-terminator blocks */
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

	Name:
	fieldterms

	Description:
	This is a classic, ported forward from the old VAX-11/780
	days.  This was translated from VAX assembly language.

*******************************************************************************/

#ifndef	FIELDTERMS_INCLUDE
#define	FIELDTERMS_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<limits.h>		/* |UCHAR_MAX| + |CHAR_BIT| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


EXTERNC_begin

extern int	fieldterms(char *,int,cchar *) noex ;
extern int	fieldtermsx(char *,int,int,...) noex ;

EXTERNC_end

#ifdef	__cplusplus

constexpr int	fieldterms_termsize = ((UCHAR_MAX + 1) / CHAR_BIT) ;

template<typename ... Args>
static inline int fieldterms(char *t,int f,Args ... args) noex {
	cint		na = npack(Args) ;
	return fieldtermsx(t,f,na,args ...) ;
}

#endif /* __cplusplus */


#endif /* FIELDTERMS_INCLUDE */


