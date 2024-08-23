/* addsat HEADER */
/* lang=C20 */

/* Integer Add-Saturated */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	ADDSAT_INCLUDE
#define	ADDSAT_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<stdint.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<stdintx.h>


EXTERNC_begin

extern int	iaddsat(int,int) noex ;
extern long	laddsat(long,long) noex ;
extern longlong	lladdsat(longlong,longlong) noex ;

EXTERNC_end


#endif /* ADDSAT_INCLUDE */


