/* logtwo HEADER */
/* charset=ISO8859-1 */
/* lang=C20 */

/* program to get time from a network time server host */
/* version %I% last-modified %G% */


/* Copyright © 2009 David A­D­ Morano.  All rights reserved. */

#ifndef	LOGTWO_INCLUDE
#define	LOGTWO_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>


EXTERNC_begin

extern double	logtwo(double) noex ;

static inline double log2(double v) noex {
    return logtwo(v) ;
}

EXTERNC_end


#endif /* LOGTWO_INCLUDE */


