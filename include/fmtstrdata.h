/* fmtstrdata SUPPORT */
/* lang=C++20 */

/* subroutine to format string output */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-01, David A­D­ Morano
	Of course, this subroutine was inspired by the UNIX®
	equivalent, but this is my own version for a) when I do not
	have the UNIX® libraries around, and b. to customize it to
	what I want!

*/

/* Copyright © 1998 David A-D- Morano.  All rights reserved. */

/*******************************************************************************

	This object supports the FMTSUB object.

*******************************************************************************/

#ifndef	FMTSTRDATA_INCLUDE
#define	FMTSTRDATA_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cwchar>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


#define	FMTSTRDATA	struct fmtstrdata_head
#define	FMTSTRDATA_FL	struct fmtstrdata_flags


struct fmtstrdata_flags {
	uint		wint:1 ;
	uint		wchar:1 ;
} ;

struct fmtstrdata_head {
	const wint_t	*lsp ;
	const wchar_t	*wsp ;
	cchar		*sp ;
	int		sl ;
	FMTSTRDATA_FL	f ;
} ; /* end struct (fmtstrdata) */

typedef	FMTSTRDATA	fmtstrdata ;
typedef	FMTSTRDATA_FL	fmtstrdata_fl ;


#endif /* FMTSTRDATA_INCLUDE */


