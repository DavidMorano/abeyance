/* cfa26 SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 */

/* convert from Alpha (a base-26 numeric representation) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-10-01, David A­D­ Morano
	This subroutine was written adapted from assembly.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Names:
	cfa26i			(integer)
	cfa26l			(long-integer)
	cfa26ll			(longlong-integer)
	cfa26ui			(unsigned-integer)
	cfa26ul			(unsigned-long-integer)
	cfa26ull		(unsigned-longlong-integer)

	Description:
	These subroutines convert numbers represented in a special
	alphameric c-string scheme to their binary integer format.

	Example:
	alpha-representation	value-in-base-10
	----------------------------------------
	a			0
	b			1
	z			25
	A			0
	Z			25

	Questions:
	Q. What was this ever used for?
	A. This represetnation was used for file-names that had a large
	amount of information in its alphæmeric name.
	Q. When was this invented?
	A. Somewhere in the early to middle 1990s (back at AT&T).

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<stdintx.h>

#include	"cfalphax.hh"		/* <- the money shot! */
#include	"cfa26.h"


/* local defines */

#define	OURBASE		26		/* base-26 */


/* imported namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */

constexpr int		base = OURBASE ;


/* exported variables */


/* exported subroutines */

int cfa26i(cchar *sp,int sl,int *rp) noex {
	return cfalphax(sp,sl,base,rp) ;
}
/* end subroutine (cfa26i) */

int cfa26l(cchar *sp,int sl,long *rp) noex {
	return cfalphax(sp,sl,base,rp) ;
}
/* end subroutine (cfa26l) */

int cfa26ll(cchar *sp,int sl,longlong *rp) noex {
	return cfalphax(sp,sl,base,rp) ;
}
/* end subroutine (cfa26ll) */

int cfa26ui(cchar *sp,int sl,uint *rp) noex {
	int		*rrp = reinterpret_cast<int *>(rp) ;
	return cfalphax(sp,sl,base,rrp) ;
}
/* end subroutine (cfa26ui) */

int cfa26ul(cchar *sp,int sl,ulong *rp) noex {
	long		*rrp = reinterpret_cast<long *>(rp) ;
	return cfalphax(sp,sl,base,rrp) ;
}
/* end subroutine (cfa26ul) */

int cfa26ull(cchar *sp,int sl,ulonglong *rp) noex {
	longlong	*rrp = reinterpret_cast<longlong *>(rp) ;
	return cfalphax(sp,sl,base,rrp) ;
}
/* end subroutine (cfa26ull) */


