/* ncpu HEADER */
/* charset=ISO8859-1 */
/* lang=C20 (conformance reviewed) */

/* get the number of (current) CPUs on this system */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	NCPU_INCLUDE
#define	NCPU_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


EXTERNC_begin

extern int	ncpu(cchar *) noex ;

EXTERNC_end


#endif /* NCPU_INCLUDE */


