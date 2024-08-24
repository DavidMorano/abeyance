/* ffbs HEADER */
/* lang=C20 */

/* Find-First-Bit-Set in various sized integers */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	FFBS_INCLUDE
#define	FFBS_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<stdintx.h>


EXTERNC_begin

extern int	ffbsi(int) noex ;
extern int	ffbsl(long) noex ;
extern int	ffbsll(longlong) noex ;

extern int	ffbsui(uint) noex ;
extern int	ffbsul(ulong) noex ;
extern int	ffbsull(ulonglong) noex ;

EXTERNC_end

#ifdef	__cplusplus

static inline int ffbs(int v) noex {
	return ffbsi(v) ;
}
static inline int ffbs(long v) noex {
	return ffbsl(v) ;
}
static inline int ffbs(longlong v) noex {
	return ffbsll(v) ;
}

static inline int ffbs(uint uv) noex {
	return ffbsui(uv) ;
}
static inline int ffbs(ulong uv) noex {
	return ffbsul(uv) ;
}
static inline int ffbs(ulonglong uv) noex {
	return ffbsull(uv) ;
}

#endif /* __cplusplus */


#endif /* FFBS_INCLUDE */


