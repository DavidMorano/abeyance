/* fdt HEADER */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* File-Descriptor-Table */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services
	(RNS).

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	FDT_INCLUDE
#define	FDT_INCLUDE


#include	<envstandards.h>	/* must be ordered fist to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<vecobj.h>

#include	"ucb.h"


#define	FDT		struct fdt_head
#define	FDT_ENT		struct fdt_ent
#define	FDT_MAGIC	0x77336556


struct fdt_ent {
	UCB		ucbp ;
	int		fd ;
} ;

struct fdt_head {
	vecobj		*elp ;
	uint		magic ;
} ;

typedef FDT		fdt ;
typedef FDT_ENT		fdt_ent ;

EXTERNC_begin

extern int	fdt_alloc(fdt *,int,UCB **) noex ;
extern int	fdt_get(fdt *,int,UCB **) noex ;
extern int	fdt_free(fdt *,int) noex ;
extern int	fdt_getentry(fdt *,int,fdt_ent *) noex ;

EXTERNC_end


#endif /* FDT_INCLUDE */


