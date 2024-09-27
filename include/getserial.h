/* getserial HEADER */
/* lang=C20 */

/* get a (system-wide) serial number from a file */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETSERIAL_INCLUDE
#define	GETSERIAL_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


EXTERNC_begin

extern int	getserial(cchar *) noex ;

EXTERNC_end


#endif /* GETSERIAL_INCLUDE */


