/* intsat HEADER */
/* lang=C20 */

/* Integer Saturation (clamping) */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#ifndef	INTSAT_INCLUDE
#define	INTSAT_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<stddef.h>
#include	<stdint.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<stdintx.h>


EXTERNC_begin

static inline int intsati(int v) noex {
	return v ;
}

extern int intsatl(long) noex ;
extern int intsato(off_t) noex ;
extern int intsatll(longlong) noex ;

extern int intsatui(uint) noex ;
extern int intsatul(ulong) noex ;
extern int intsats(size_t) noex ;
extern int intsatull(ulonglong) noex ;

EXTERNC_end

#ifdef	__cplusplus

static inline int intsat(int v) noex {
	return intsati(v) ;
}
static inline int intsat(long v) noex {
	return intsatl(v) ;
}
static inline int intsat(off_t v) noex {
	return intsato(v) ;
}
static inline int intsat(longlong v) noex {
	return intsatll(v) ;
}

static inline int intsat(uint v) noex {
	return intsatui(v) ;
}
static inline int intsat(ulong v) noex {
	return intsatul(v) ;
}
#ifdef	COMMENT /* GCC says that this is an alias of |ulong| */
static inline int intsat(size_t v) noex {
	return intsats(v) ;
}
#endif /* COMMENT */
static inline int intsat(ulonglong v) noex {
	return intsatull(v) ;
}

#endif /* __cplusplus */


#endif /* INTSAT_INCLUDE */


