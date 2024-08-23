/* cfcharss HEADER */
/* lang=C++20 */

/* convert a decimal digit string to its binary integer value */
/* version %I% last-modified %G% */


/* revision history:

	= 2023-10,10, David A-D- Morano
	This is originally written.

*/

/* Copyright © 2023 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Subroutines to convert digit strings to binary integers.


*******************************************************************************/

#ifndef	CFCHARSX_INCLUDE
#define	CFCHARSX_INCLUDE
#ifdef	__cplusplus /* everything is C++ only */


#include	<envstandards.h>	/* MUST be first to configure */
#include	<charconv>
#include	<usystem.h>
#include	<stdintx.h>
#include	<localmisc.h>


template<typename T>
int cfcharsx(cchar *sp,int sl,int b,T *rp) noex {
	using std::from_chars ;
	using std::from_chars_result ;
	using std::errc ;
	int		rs = SR_FAULT ;
	if (sp && rp) {
	    std::from_chars_result	r ;
	    constexpr std::errc	ec_ok = errc() ;
	    T		v{} ;
	    rs = SR_OK ;
	    if (r = from_chars(sp,(sp+sl),v,b) ; (r.ec == ec_ok)) {
		*rp = v ;
	    } else {
		using enum	std::errc ;
		switch (r.ec) {
		case result_out_of_range:
		    rs = SR_RANGE ;
		    break ;
		default:
		    rs = SR_INVALID ;
		    break ;
		} /* end switch */
	    } /* end if (failed) */
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine-template (cfcharsx) */


#endif	/* __cplusplus */
#endif /* CFCHARSX_INCLUDE */


