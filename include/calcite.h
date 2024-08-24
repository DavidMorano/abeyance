/* calcite HEADER */
/* lang=C++20 */

/* calendar citation */
/* version %I% last-modified %G% */


/* Copyright © 2008 David A­D­ Morano.  All rights reserved. */

#ifndef	CALCITE_INCLUDE
#define	CALCITE_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<usyscalls.h>


#define	CALCITE		struct calcite_head


struct calcite_head {
	ushort		y ;
	uchar		m, d ;
} ;

typedef	CALCITE		calcite ;

EXTERNC_begin

extern int	calcite_load(calcite *,int,int,int) noex ;

EXTERNC_end


#endif /* CALCITE_INCLUDE */


